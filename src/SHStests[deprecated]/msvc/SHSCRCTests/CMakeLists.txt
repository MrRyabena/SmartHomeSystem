cmake_minimum_required(VERSION 3.27)

project(SHSCRCTests VERSION 1.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(SHSCRC STATIC
  ../../../SHScore/SHSCRC.cpp
  ../../../SHScore/SHSCRC.h
  ../../../SHScore/SHSRandom.h
  ../../../SHScore/SHSdebug.h
  ../../../SHScore/SHSByteCollector.h
)

add_library(SHSutils STATIC
  ../../utils/SHSMultiData.h
  ../../utils/SHSMultiDataTools.h
  ../../utils/SHSMultiDataTools.cpp
)

add_library(SHSCRCTest STATIC
  ../../source/SHSCRCTest.cpp
  ../../source/SHSCRCTest.h
  ../../source/SHSprinter.h
)

add_executable(SHSCRCTests
  SHSCRCTests.cpp
)

target_link_libraries(SHSCRCTest PRIVATE SHSCRC PRIVATE SHSutils)
target_link_libraries(SHSCRCTests PRIVATE SHSCRCTest)

target_include_directories(SHSCRCTests PUBLIC 
  ../../../SHScore/
  ../../utils/
)
