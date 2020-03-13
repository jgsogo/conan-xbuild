
#pragma once

#include <iostream>
#include <string>
#include "cmake.h"
#include "cmake_export.h"

CMAKE_EXPORT void cmake(int tabs);

static void cmake_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmake_header: " << cmake_MESSAGE << std::endl;
}