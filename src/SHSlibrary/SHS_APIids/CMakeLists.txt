
cmake_minimum_required(VERSION 3.27)

project(SHS_APIids VERSION 2.4.2 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    shs_lib_APIids.h)

add_library(SHS_APIids ${SOURCES})
add_library(shs::APIids ALIAS SHS_APIids)

target_include_directories(SHS_APIids
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
