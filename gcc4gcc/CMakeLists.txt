
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(gcc LANGUAGES CXX)

include(GenerateExportHeader)
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(zlib REQUIRED)

file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/gcc.h "#pragma once\nconst char* const gcc_MESSAGE=\"${MESSAGE}\";")

add_library(gcc gcc/lib.cpp gcc/lib.h)
target_include_directories(gcc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
generate_export_header(gcc)
target_link_libraries(gcc PUBLIC zlib::zlib )
set_target_properties(gcc PROPERTIES OUTPUT_NAME gcc)



add_executable(gcc_exe gcc_exe/main.cpp)
target_link_libraries(gcc_exe PUBLIC gcc )
set_target_properties(gcc_exe PROPERTIES OUTPUT_NAME gcc_exe)
