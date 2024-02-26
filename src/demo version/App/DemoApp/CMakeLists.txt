cmake_minimum_required(VERSION 3.5)

project(DemoApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

if(ANDROID)
  add_library(DemoApp SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

../../../SHScore/

    TCPstream.h
  )
else()
  add_executable(DemoApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ../../../SHScore/SHSCRC.cpp
  ../../../SHScore/SHSCRC.h

  ../../../SHScore/SHSCallbacksKeeper.cpp
    ../../../SHScore/SHSCallbacksKeeper.h

   ../../../SHScore/SHSsettings_private.h

   ../../../SHScore/SHSdtp.cpp
    ../../../SHScore/SHSdtp.h


   # ../../../SHScore/SHSdtp.cpp

    TCPstream.h
  )
endif()
target_link_libraries(DemoApp PRIVATE Qt5::Widgets)
target_link_libraries(DemoApp PRIVATE Qt5::Network)
target_include_directories(DemoApp PRIVATE ../../../SHScore/)

