#pragma once

#define _shs_SHScore_VERSION_ "v1.2.0"

#pragma message "Current SHScore version is: " _shs_SHScore_VERSION_ "."

namespace shs
{
  static constexpr char SHScore_version[] = _shs_SHScore_VERSION_;
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
*/
