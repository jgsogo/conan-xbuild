cmake_minimum_required(VERSION 3.10)
project(testtool LANGUAGES CXX)


include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(testlib REQUIRED)

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/testtool.h "#pragma once\nconst char* const testtool_MESSAGE=\"${MESSAGE}\";")

add_library(testtool testtool/lib.cpp testtool/lib.h)
target_include_directories(testtool
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(testtool PUBLIC testlib::testlib )
set_target_properties(testtool PROPERTIES OUTPUT_NAME testtool)


add_executable(testtool_exe testtool_exe/main.cpp)
target_link_libraries(testtool_exe PUBLIC testtool )
set_target_properties(testtool_exe PROPERTIES OUTPUT_NAME testtool_exe)
