cmake_minimum_required(VERSION 3.5)

project(SHSapp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHSCORE_PATH ../../SHScore/)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if(ANDROID)
  add_library(SHSapp SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    tcpclient.cpp
    tcpclient.h
  )
else()
  add_executable(SHSapp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    tcpclient.cpp
    tcpclient.h

  )
endif()

find_library(SHSCORE_LIB NAMES SHScore PATHS ${SHSCORE_PATH}/build/)
if(NOT SHSCORE_LIB)
    message(FATAL_ERROR "Library SHScore not found in ${SHSCORE_PATH}")
else()
    message(STATUS "Library SHScore found: ${SHSCORE_LIB}")
endif()

target_include_directories(SHSapp PUBLIC ${SHSCORE_PATH})
target_link_libraries(SHSapp PUBLIC ${SHSCORE_LIB})

target_link_libraries(SHSapp PRIVATE Qt5::Widgets)
target_link_libraries(SHSapp PRIVATE Qt5::Network)
