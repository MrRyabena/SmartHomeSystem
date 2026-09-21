cmake_minimum_required(VERSION 3.14)
project(ShsCoreTests VERSION 2.4.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHS_CMF_UNUSE_SHS_SETTINGS ON)
add_compile_definitions(
    SHS_SF_UNUSE_SHS_SETTINGS
    SHS_SF_DEBUG
)

enable_testing()

find_package(GTest REQUIRED)

add_subdirectory(../../SHScore SHScore)

add_executable(ShsCoreTests
    ShsCoreTestsMain.cpp
    ShsDtpBusTests.cpp
)

target_link_libraries(ShsCoreTests PRIVATE
    GTest::gtest
    GTest::gtest_main
    SHScore
)
target_include_directories(ShsCoreTests PRIVATE ../../SHScore)

include(GoogleTest)
gtest_discover_tests(ShsCoreTests)
