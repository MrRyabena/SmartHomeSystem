cmake_minimum_required(VERSION 3.27)

project(SHSFSTests VERSION 1.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)


add_library(SHSFS STATIC
  ../../../SHScore/SHSFileAbstract.h
  ../../../SHScore/SHSFSAbstract.h
  ../../../SHScore/SHSFile.cpp
  ../../../SHScore/SHSFile.h
  ../../../SHScore/SHSshsf.h
  ../../../SHScore/SHSshsf.cpp
  ../../../SHScore/SHSFS.cpp
  ../../../SHScore/SHSFS.h
  ../../../SHScore/SHSRandom.h
  ../../../SHScore/SHSdebug.h
  ../../../SHScore/SHSCRC.cpp
  ../../../SHScore/SHSCRC.h
  ../../../SHScore/SHSsettings_private.h
)

add_library(SHSFSTest STATIC
  ../../source/SHSFSTest.cpp
  ../../source/SHSFSTest.h
  ../../source/SHSprinter.h
)

add_executable(SHSFSTests
  SHSFSTests.cpp
)

target_link_libraries(SHSFSTest PRIVATE SHSFS)
target_link_libraries(SHSFSTests PRIVATE SHSFSTest)
