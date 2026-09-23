
cmake_minimum_required(VERSION 3.27)

project(SHS_Color VERSION 2.5.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHS_CMF_UNUSE_SHS_SETTINGS ON)
add_compile_definitions(
    SHS_SF_UNUSE_SHS_SETTINGS
    SHS_SF_DEBUG
)

set(SOURCES
    shs_lib_Color_cast.h
    shs_lib_Color_FadeRgbEffect.cpp
    shs_lib_Color_FadeRgbEffect.h
    shs_lib_Color_GammaRgbFilter.h
    shs_lib_Color_HSB888.h
    shs_lib_Color_HSBV8888.h
    shs_lib_Color_Kelvin.h
    shs_lib_Color_RfbEffectType.h
    shs_lib_Color_RGB888.h
    shs_lib_Color_RgbController.cpp
    shs_lib_Color_RgbController.h
    shs_lib_Color_RgbDriver.cpp
    shs_lib_Color_RgbDriver.h
    shs_lib_Color_RgbEffect.h
    shs_lib_Color_RgbFilter.h
    shs_lib_Color_RgbFilterType.h
    shs_lib_Color_RgbManager.cpp
    shs_lib_Color_RgbManager.h
    shs_lib_Color_RGBV8888.h
    shs_lib_Color_Wheel1530Effect.cpp
    shs_lib_Color_Wheel1530Effect.h
    shs_lib_Color_Wheel1530.h
    shs_lib_Color_Wheel256.h
)

add_library(SHS_Color ${SOURCES})

add_subdirectory(../../../SHScore SHScore)

target_link_libraries(SHS_Color PRIVATE
    SHScore
)
target_include_directories(SHS_Color PRIVATE ../../../SHScore)

target_include_directories(SHS_Color
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(SHS_Color PRIVATE cxx_std_17)
