cmake_minimum_required(VERSION 3.5)

project(GUIapp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHS_CMF_QT ON CACHE BOOL "Enable Qt")
add_definitions(-DSHS_QT_FLAG)

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

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt5 COMPONENTS Charts Core REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets Charts REQUIRED)
find_package(Qt5 COMPONENTS Quick QuickControls2 REQUIRED)

if(ANDROID)
    add_library(GUIapp SHARED
      main.cpp
      qml.qrc
      shs_Engine.h
      shs_Engine.cpp
      gs_config.h
    )
else()
    add_executable(GUIapp
      main.cpp
      qml.qrc
      shs_Engine.h
      shs_Engine.cpp
    )
endif()

add_subdirectory(SHSbuild/SHScore)

target_link_libraries(GUIapp PRIVATE SHScore)
target_include_directories(GUIapp PRIVATE SHSbuild/SHScore)
target_include_directories(GUIapp PRIVATE SHSbuild/SHSconfig)
target_include_directories(GUIapp PRIVATE SHSbuild/SHSqt_core)
target_include_directories(GUIapp PRIVATE SHSbuild/SHSqt_core/SHSqml_core)



target_compile_definitions(GUIapp PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(GUIapp PRIVATE Qt5::Core Qt5::Quick)
target_link_libraries(GUIapp PRIVATE Qt5::Core Qt5::Network)
target_link_libraries(GUIapp PRIVATE Qt5::Quick Qt5::QuickControls2)
target_link_libraries(GUIapp PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)



target_compile_definitions(GUIapp
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(GUIapp
  PRIVATE Qt5::Core Qt5::Quick)
