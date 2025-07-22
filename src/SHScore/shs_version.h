#pragma once

#include <cstddef>
#include <cstdint>

#include <shs_types.h>


#define _shs_Project_VERSION_    "v2.2.1"
#define _shs_SHScore_VERSION_    "v2.2.1"
#define _shs_SHSlibrary_VERSION_ "v2.2.1"

#pragma message "\n" \
"Current Project version is:    " _shs_Project_VERSION_ "\n" \
"Current SHScore version is:    " _shs_SHScore_VERSION_  "\n" \
"Current SHSlibrary version is: " _shs_SHSlibrary_VERSION_ "."

namespace shs
{
    namespace version
    {
        /**
         * @brief Represents a version number consisting of major, minor, and patch components.
         *
         * The Version structure is used to encapsulate version information in a semantic versioning format.
         * It provides a constructor to initialize the version components and a static method to parse
         * version strings formatted as "vX.Y.Z", where X, Y, and Z are non-negative integers.
         *
         * Example usage:
         *
         * ```
         * Version v0 = Version::parseVersion("v2.1.0");
         * ```
         *
         * ```
         * Version v1(2, 1, 0);
         * ```
         *
         * The structure includes:
         *
         * - `major`: The major version number, incremented for incompatible API changes.
         *
         * - `minor`: The minor version number, incremented for backward-compatible functionality.
         *
         * - `patch`: The patch version number, incremented for backward-compatible bug fixes.
         *
         * The `parseVersion` method extracts the version components from a string and returns a
         * Version object representing the parsed version.
            */
        struct Version
        {
            uint8_t major;
            uint8_t minor;
            uint8_t patch;


            constexpr Version(uint8_t major, uint8_t minor, uint8_t patch) : major(major), minor(minor), patch(patch) {}
            constexpr Version(const char* v_str) : Version(parseVersion(v_str)) {}

            constexpr Version(const Version& other) : Version(other.major, other.minor, other.patch) {}
            constexpr Version& operator=(const Version& other)
            {
                major = other.major;
                minor = other.minor;
                patch = other.patch;

                return *this;
            }


            constexpr bool operator==(const Version& other) const
            {
                return major == other.major && minor == other.minor && patch == other.patch;
            }

            constexpr bool operator!=(const Version& other) const
            {
                return !(*this == other);
            }

            constexpr bool operator<(const Version& other) const
            {
                if (major != other.major) return major < other.major;
                if (minor != other.minor) return minor < other.minor;
                return patch < other.patch;
            }

            constexpr bool operator>(const Version& other) const
            {
                return other < *this;
            }

            constexpr bool operator<=(const Version& other) const
            {
                return !(other < *this);
            }

            constexpr bool operator>=(const Version& other) const
            {
                return !(*this < other);
            }


            static constexpr Version parseVersion(const char* version)
            {
                uint8_t major = 0, minor = 0, patch = 0;

                // Skip the 'v' character
                if (version[0] == 'v')
                {
                    version++;
                }

                // Read the major version
                while (*version >= '0' && *version <= '9')
                {
                    major = major * 10 + (*version - '0');
                    version++;
                }

                // Check for the first dot
                if (*version == '.') version++;

                // Read the minor version
                while (*version >= '0' && *version <= '9')
                {
                    minor = minor * 10 + (*version - '0');
                    version++;
                }

                // Check for the second dot
                if (*version == '.') version++;

                // Read the patch version
                while (*version >= '0' && *version <= '9')
                {
                    patch = patch * 10 + (*version - '0');
                    version++;
                }

                return shs::version::Version(major, minor, patch);
            }
        };

        static shs::t::shs_string_t toString(const Version& version)
        {
            shs::t::shs_string_t str = "v";
            str += version.major;
            str += '.';
            str += version.minor;
            str += '.';
            str += version.patch;

            return str;
        }

        /**
         * @brief
         * Version History
         *
         * - v0.1.0 — Private beta version.
         *
         * - v0.2.0 — Development version.
         *
         * - v1.0.0 — Release version.
         *
         * - v1.1.0 — Added tests.
         *
         * - v1.2.0 — Intermediate version.
         *
         * - v2.0.0 — Upcoming version.
         *
         * - v2.1.0 — The core components have been updated. Libraries for working with sensors have been fixed and tested.
         *
         * - v2.2.0 — SHScore has been optimized and debugged. Deprecated code has been removed. Documentation has been updated.
        */
        constexpr shs::version::Version project = _shs_Project_VERSION_;
        constexpr shs::version::Version core = _shs_SHScore_VERSION_;
        constexpr shs::version::Version library = _shs_SHSlibrary_VERSION_;
    }
}
