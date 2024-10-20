#pragma once

#include <cstddef>
#include <cstdint>


#define _shs_Project_VERSION_    "v2.0.0"
#define _shs_SHScore_VERSION_    "v2.0.0"
#define _shs_SHSlibrary_VERSION_ "v2.0.0"

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
            constexpr Version(uint8_t major, uint8_t minor, uint8_t patch)
                : major(major), minor(minor), patch(patch)
            {}

            const uint8_t major;
            const uint8_t minor;
            const uint8_t patch;

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

        constexpr auto project = Version::parseVersion(_shs_Project_VERSION_);
        constexpr auto core = Version::parseVersion(_shs_SHScore_VERSION_);
        constexpr auto library = Version::parseVersion(_shs_SHSlibrary_VERSION_);
    }
}

/*
    v0.1.0 — private beta-version.
    v0.2.0 — development.
    v1.0.0 — release.
        See release: https://github.com/MrRyabena/SmartHomeSystem/releases/tag/v1.x.x
        New core architecture.
        New library.
        The documentation has been completed.
        The SHScore has not been tested.
        The demo version is incomplete.
        Tests and additions are expected.
    v1.1.0 — added tests.
        Tests have been written and conducted, created the library SHStests.
        A random number generator (shs::Random) has been created.
        Development of a project assembly system.
        shs::ByteCollecor: fixed a critical error in functions get() and reserve().
        shs::CRC: now the function crcBuf(..) writes the result to a variable crc.
        The synchronizer has been replaced with a make.sh.
    v1.2.0 — intermediate version.
        A file system has been developed [beta]:
            - shs::FSAbstract and shs::FileAbstract — interface classes.
            - shs::FS — file system class.
            - shs::File — file class.
            - shs::SHSF — [beta] Smart Home System File (.shsf). It has errors now.
            The File System is poorly tested and isn't fully developed.
        Developed a new ID-type SHSID.
        Added SHSversion.h.
        An important version for the further development of the project.
    v2.0.0
*/
