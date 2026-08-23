#!/usr/bin/env python3

import argparse
import json
import logging
import os
import pathlib
import re
import subprocess
import sys
from typing import List


LOGGER = logging.getLogger("validate_release_version")

ANSI_RESET = "\033[0m"
ANSI_BOLD = "\033[1m"
ANSI_RED = "\033[31m"
ANSI_GREEN = "\033[32m"
ANSI_YELLOW = "\033[33m"
ANSI_BLUE = "\033[34m"


def should_use_color(color_mode: str) -> bool:
    if color_mode == "always":
        return True
    if color_mode == "never":
        return False
    if os.environ.get("NO_COLOR") is not None:
        return False
    if os.environ.get("FORCE_COLOR") not in (None, "0"):
        return True
    if os.environ.get("GITHUB_ACTIONS") == "true":
        return True
    return sys.stdout.isatty()


class ColorFormatter(logging.Formatter):
    LEVEL_COLORS = {
        logging.DEBUG: ANSI_BLUE,
        logging.INFO: ANSI_GREEN,
        logging.WARNING: ANSI_YELLOW,
        logging.ERROR: ANSI_RED,
        logging.CRITICAL: ANSI_RED,
    }

    def __init__(self, use_color: bool) -> None:
        super().__init__("%(levelname)s: %(message)s")
        self.use_color = use_color

    def format(self, record: logging.LogRecord) -> str:
        message = super().format(record)
        if not self.use_color:
            return message
        color = self.LEVEL_COLORS.get(record.levelno, "")
        if not color:
            return message
        level_name = f"{ANSI_BOLD}{color}{record.levelname}{ANSI_RESET}"
        return message.replace(record.levelname, level_name, 1)


def configure_logging(color_mode: str, log_level: str) -> None:
    handler = logging.StreamHandler()
    handler.setFormatter(ColorFormatter(should_use_color(color_mode)))
    LOGGER.handlers.clear()
    LOGGER.addHandler(handler)
    LOGGER.setLevel(getattr(logging, log_level.upper(), logging.INFO))
    LOGGER.propagate = False


def git_ls_files(patterns: List[str], repo_root: pathlib.Path) -> List[pathlib.Path]:
    args = ["git", "ls-files", "--", *patterns]
    out = subprocess.check_output(args, cwd=str(repo_root), text=True)
    files = [line.strip() for line in out.splitlines() if line.strip()]
    return [repo_root / file for file in files]


def read_text(path: pathlib.Path) -> str:
    return path.read_text(encoding="utf-8")


def git_commit_hashes_for_paths(paths: List[str], repo_root: pathlib.Path) -> List[str]:
    args = ["git", "log", "--format=%H", "--no-renames", "--", *paths]
    out = subprocess.check_output(args, cwd=str(repo_root), text=True)
    hashes: List[str] = []
    seen = set()
    for line in out.splitlines():
        commit_hash = line.strip()
        if commit_hash and commit_hash not in seen:
            seen.add(commit_hash)
            hashes.append(commit_hash)
    return hashes


def git_changed_paths(commit_hash: str, paths: List[str], repo_root: pathlib.Path) -> List[str]:
    args = ["git", "show", "--pretty=format:", "--name-only", "--no-renames", commit_hash, "--", *paths]
    out = subprocess.check_output(args, cwd=str(repo_root), text=True)
    return [line.strip() for line in out.splitlines() if line.strip()]


def git_commit_body(commit_hash: str, repo_root: pathlib.Path) -> str:
    args = ["git", "show", "--quiet", "--format=%B", commit_hash]
    return subprocess.check_output(args, cwd=str(repo_root), text=True)


def git_revision_exists(revision: str, repo_root: pathlib.Path) -> bool:
    args = ["git", "rev-parse", "--verify", "--quiet", revision]
    return subprocess.run(args, cwd=str(repo_root), text=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL).returncode == 0


def git_previous_release_tag(tag: str, repo_root: pathlib.Path) -> str | None:
    current_match = re.fullmatch(r"v(\d+)\.(\d+)\.(\d+)", tag)
    if not current_match:
        return None

    current_version = tuple(int(part) for part in current_match.groups())
    args = ["git", "tag", "--list", "v*", "--sort=-version:refname"]
    out = subprocess.check_output(args, cwd=str(repo_root), text=True)

    for candidate in (line.strip() for line in out.splitlines() if line.strip()):
        candidate_match = re.fullmatch(r"v(\d+)\.(\d+)\.(\d+)", candidate)
        if not candidate_match:
            continue
        candidate_version = tuple(int(part) for part in candidate_match.groups())
        if candidate_version < current_version:
            return candidate

    return None


def validate(tag: str, repo_root: pathlib.Path) -> List[str]:
    expected_version = tag[1:] if tag.startswith("v") else tag
    expected_current_version = f"v{expected_version.rsplit('.', 1)[0]}.X"
    errors: List[str] = []
    target_scheme_paths = [
        "schemes/SHScore-scheme.pdf",
        "schemes/SHScore-scheme.png",
        "schemes/SHScore.xmind",
        "schemes/SHSlibrary-scheme.pdf",
        "schemes/SHSlibrary-scheme.png",
        "schemes/SHSlibrary.xmind",
    ]

    LOGGER.info("Validating release tag %s", tag)

    if not re.fullmatch(r"v\d+\.\d+\.\d+", tag):
        message = f"tag must use vX.Y.Z format, got {tag!r}"
        LOGGER.error(message)
        errors.append(message)
    else:
        LOGGER.info("Tag format is valid")

    version_h_path = repo_root / "src/SHScore/shs_version.h"
    LOGGER.debug("Checking %s", version_h_path.relative_to(repo_root).as_posix())
    version_h = read_text(version_h_path)
    for macro in ("_shs_Project_VERSION_", "_shs_SHScore_VERSION_", "_shs_SHSlibrary_VERSION_"):
        match = re.search(rf'#define\s+{re.escape(macro)}\s+"([^"]+)"', version_h)
        if not match:
            message = f"missing {macro} in src/SHScore/shs_version.h"
            LOGGER.error(message)
            errors.append(message)
        elif match.group(1) != tag:
            message = f"{macro} in src/SHScore/shs_version.h is {match.group(1)!r}, expected {tag!r}"
            LOGGER.error(message)
            errors.append(message)
        else:
            LOGGER.info("%s matches %s", macro, tag)

    cmake_files = git_ls_files(["src/**/CMakeLists.txt", "src/**/CmakeLists.txt"], repo_root)
    for path in cmake_files:
        rel_path = path.relative_to(repo_root).as_posix()
        LOGGER.debug("Checking %s", rel_path)
        content = read_text(path)
        project_match = re.search(r"project\s*\((.*?)\)", content, re.IGNORECASE | re.DOTALL)
        if not project_match:
            LOGGER.info("%s has no project VERSION field", rel_path)
            continue
        version_match = re.search(r"\bVERSION\s+([0-9]+\.[0-9]+\.[0-9]+)\b", project_match.group(1), re.IGNORECASE)
        if version_match and version_match.group(1) != expected_version:
            message = f"{rel_path} has VERSION {version_match.group(1)!r}, expected {expected_version!r}"
            LOGGER.error(message)
            errors.append(message)
        elif version_match:
            LOGGER.info("%s matches %s", rel_path, expected_version)

    library_json_files = git_ls_files(["src/**/library.json"], repo_root)
    for path in library_json_files:
        rel_path = path.relative_to(repo_root).as_posix()
        LOGGER.debug("Checking %s", rel_path)
        data = json.loads(read_text(path))
        version = data.get("version")
        if version != expected_version:
            message = f"{rel_path} has version {version!r}, expected {expected_version!r}"
            LOGGER.error(message)
            errors.append(message)
        else:
            LOGGER.info("%s matches %s", rel_path, expected_version)

    changes_dir = repo_root / "schemes/SHScore-changes"
    change_pattern = f"SHScore-changes-{tag.replace('.', '_')}.*"
    if not any(changes_dir.glob(change_pattern)):
        message = f"missing SHScore-changes artifact for {tag!r}"
        LOGGER.error(message)
        errors.append(message)
    else:
        LOGGER.info("Found SHScore-changes artifact for %s", tag)

    readme_path = repo_root / "README.md"
    LOGGER.debug("Checking %s", readme_path.relative_to(repo_root).as_posix())
    readme_text = read_text(readme_path)
    versions_section_match = re.search(
        r"# Versions\s*(.*?)\s*## Краткий обзор",
        readme_text,
        re.IGNORECASE | re.DOTALL,
    )
    if not versions_section_match:
        message = "README.md does not contain a parseable Versions section"
        LOGGER.error(message)
        errors.append(message)
    else:
        versions_section = versions_section_match.group(1)
        current_summaries = re.findall(
            r"<summary>\s*([^<]+?)\s*—\s*(?:<code><b>|\[current\]).*?\[current\].*?</summary>",
            versions_section,
            re.IGNORECASE | re.DOTALL,
        )
        if len(current_summaries) != 1:
            message = (
                f"README.md Versions section must contain exactly one [current] marker, found {len(current_summaries)}"
            )
            LOGGER.error(message)
            errors.append(message)
        elif current_summaries[0].strip() != expected_current_version:
            message = (
                f"README.md Versions section marks {current_summaries[0].strip()!r} as [current], "
                f"expected {expected_current_version!r} for release tag {tag!r}"
            )
            LOGGER.error(message)
            errors.append(message)
        else:
            LOGGER.info("README.md marks %s as the only current version", expected_current_version)

        LOGGER.debug("Checking release scheme commit for %s", tag)
        previous_tag = git_previous_release_tag(tag, repo_root)
        current_revision = tag if git_revision_exists(tag, repo_root) else "HEAD"
        if current_revision != tag:
            LOGGER.info("Tag %s is not available locally; using %s as the upper range bound", tag, current_revision)
        if previous_tag is None:
            LOGGER.warning("No previous release tag found for %s; checking full history for scheme commit", tag)
            scheme_commit_hashes = git_commit_hashes_for_paths(target_scheme_paths, repo_root)
        else:
            LOGGER.info("Limiting scheme commit search to range %s..%s", previous_tag, current_revision)
            range_filter_args = ["git", "log", "--format=%H", "--no-renames", f"{previous_tag}..{current_revision}", "--", *target_scheme_paths]
            try:
                out = subprocess.check_output(range_filter_args, cwd=str(repo_root), text=True)
            except subprocess.CalledProcessError:
                LOGGER.warning(
                    "Git range %s..%s is not resolvable locally; falling back to full history",
                    previous_tag,
                    current_revision,
                )
                scheme_commit_hashes = git_commit_hashes_for_paths(target_scheme_paths, repo_root)
            else:
                range_hashes: List[str] = []
                seen_hashes = set()
                for line in out.splitlines():
                    commit_hash = line.strip()
                    if commit_hash and commit_hash not in seen_hashes:
                        seen_hashes.add(commit_hash)
                        range_hashes.append(commit_hash)
                scheme_commit_hashes = range_hashes
        matching_commit_hash = None
        ref_pattern = re.compile(rf"(?im)^Ref:\s*{re.escape(tag)}\s*$")
        for commit_hash in scheme_commit_hashes:
            changed_paths = set(git_changed_paths(commit_hash, target_scheme_paths, repo_root))
            if not set(target_scheme_paths).issubset(changed_paths):
                continue
            commit_body = git_commit_body(commit_hash, repo_root)
            if ref_pattern.search(commit_body):
                matching_commit_hash = commit_hash
                break

        if matching_commit_hash is None:
            message = (
                f"no commit found that updates all scheme files together and includes 'Ref: {tag}' in the commit body"
            )
            LOGGER.error(message)
            errors.append(message)
        else:
            LOGGER.info("Found scheme commit %s with Ref: %s", matching_commit_hash[:7], tag)

    if not versions_section_match:
        pass
    elif not re.search(
        rf"<summary>\s*{re.escape(expected_current_version)}\s*—\s*<code><b>\[current\]</b></code>",
        versions_section_match.group(1),
        re.IGNORECASE,
    ):
        message = (
            f"README.md Versions section must mark {expected_current_version!r} as [current] "
            f"for release tag {tag!r}"
        )
        LOGGER.error(message)
        errors.append(message)

    return errors


def write_summary(summary_path: str, errors: List[str]) -> None:
    if not summary_path:
        return
    with open(summary_path, "a", encoding="utf-8") as summary:
        summary.write("### Release version validation failed\n\n")
        for error in errors:
            summary.write(f"- {error}\n")


def main() -> int:
    parser = argparse.ArgumentParser(description="Validate release tag against project versions.")
    parser.add_argument("--tag", required=True, help="Release tag in the form vX.Y.Z")
    parser.add_argument("--repo-root", default=".", help="Repository root path")
    parser.add_argument("--summary-path", default="", help="Optional GitHub step summary path")
    parser.add_argument(
        "--color",
        choices=("auto", "always", "never"),
        default="auto",
        help="Colorize log output in the console.",
    )
    parser.add_argument(
        "--log-level",
        choices=("DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"),
        default="INFO",
        help="Set the minimum log level.",
    )
    args = parser.parse_args()

    configure_logging(args.color, args.log_level)
    repo_root = pathlib.Path(args.repo_root).resolve()
    errors = validate(args.tag, repo_root)

    if errors:
        LOGGER.error("Version validation failed with %d issue(s)", len(errors))
        write_summary(args.summary_path, errors)
        return 1

    LOGGER.info("Version validation passed for %s", args.tag)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())