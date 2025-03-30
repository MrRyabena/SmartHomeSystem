# shs_version.h

## General Description

This file contains version definitions and a structure for managing version information within the Smart Home System. It provides a way to encapsulate version numbers in a semantic format and includes functionality for parsing version strings.

## Versions

- **v2.0.0** — created.

---

## Version Definitions

- **`_shs_Project_VERSION_`**
  - Type: `const char*`
  - Description: Represents the current version of the project. The current version is "v2.0.0".

- **`_shs_SHScore_VERSION_`**
  - Type: `const char*`
  - Description: Represents the current version of the SHScore module. The current version is "v2.0.0".

- **`_shs_SHSlibrary_VERSION_`**
  - Type: `const char*`
  - Description: Represents the current version of the SHSlibrary. The current version is "v2.0.0".

---

## Namespace `shs::version`

### Description

The `shs::version` namespace contains the `Version` structure and constants for managing version information in the Smart Home System.

### Structure `Version`

- **Description**: Represents a version number consisting of major, minor, and patch components. The `Version` structure encapsulates version information in a semantic versioning format.

- **Members**:
  - `uint8_t major` — The major version number, incremented for incompatible API changes.
  - `uint8_t minor` — The minor version number, incremented for backward-compatible functionality.
  - `uint8_t patch` — The patch version number, incremented for backward-compatible bug fixes.

- **Constructors**:

  - ##### `Version(uint8_t major, uint8_t minor, uint8_t patch)`

    - Initializes a `Version` instance with specified major, minor, and patch numbers.
  
  - ##### `Version(const char* v_str)`

    - Initializes a `Version` instance by parsing a version string formatted as "vX.Y.Z".

- **Static Methods**:

  - ##### `static constexpr Version parseVersion(const char* version)`

    - Parses a version string and returns a `Version` object representing the parsed version.

### Version History

- **v0.1.0** — Private beta version.
- **v0.2.0** — Development version.
- **v1.0.0** — Release version.
- **v1.1.0** — Added tests.
- **v1.2.0** — Intermediate version.
- **v2.0.0** — Upcoming version.

### Constants

- **`constexpr shs::version::Version project`**
  - Represents the current project version.

- **`constexpr shs::version::Version core`**
  - Represents the current SHScore version.

- **`constexpr shs::version::Version library`**
  - Represents the current SHSlibrary version.

---

## Conclusion

The `shs_version.h` file provides a structured way to manage version information within the Smart Home System. By encapsulating version numbers in the `Version` structure and providing parsing functionality, it ensures consistency and clarity in version management across the codebase.
