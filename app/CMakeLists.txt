
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_ABI_COMPILED 1)

cmake_minimum_required(VERSION 3.10)
project(app LANGUAGES CXX)


include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(library REQUIRED)


add_library(app app/lib.cpp app/lib.h)
target_include_directories(app
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(app PUBLIC library::library )
set_target_properties(app PROPERTIES OUTPUT_NAME app)



add_executable(app_exe app_exe/main.cpp)
target_link_libraries(app_exe PUBLIC app )
set_target_properties(app_exe PROPERTIES OUTPUT_NAME app_exe)
