
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(library LANGUAGES CXX)

find_package(zlib REQUIRED)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/library.h "#pragma once\nconst char* const library_MESSAGE=\"${MESSAGE}\";")

add_library(library library/lib.cpp library/lib.h)
target_include_directories(library
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(library PUBLIC zlib::zlib )

set_target_properties(library PROPERTIES OUTPUT_NAME library)


