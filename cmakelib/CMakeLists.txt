
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(cmakelib LANGUAGES CXX)

find_package(zlib REQUIRED)

include(GenerateExportHeader)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/cmakelib.h "#pragma once\nconst char* const cmakelib_MESSAGE=\"${MESSAGE}\";")

add_library(cmakelib cmakelib/lib.cpp cmakelib/lib.h)
target_include_directories(cmakelib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
generate_export_header(cmakelib)
target_link_libraries(cmakelib PUBLIC zlib::zlib )

set_target_properties(cmakelib PROPERTIES OUTPUT_NAME cmakelib)


