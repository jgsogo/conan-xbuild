
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(zlib LANGUAGES CXX)


include(GenerateExportHeader)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/zlib.h "#pragma once\nconst char* const zlib_MESSAGE=\"${MESSAGE}\";")
add_library(zlib zlib/lib.cpp zlib/lib.h)
generate_export_header(zlib)
target_include_directories(zlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set_target_properties(zlib PROPERTIES OUTPUT_NAME zlib)
