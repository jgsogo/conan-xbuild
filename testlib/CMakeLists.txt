
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(testlib LANGUAGES CXX)

find_package(zlib REQUIRED)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/testlib.h "#pragma once\nconst char* const testlib_MESSAGE=\"${MESSAGE}\";")

add_library(testlib testlib/lib.cpp testlib/lib.h)
target_include_directories(testlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(testlib PUBLIC zlib::zlib )

set_target_properties(testlib PROPERTIES OUTPUT_NAME testlib)


