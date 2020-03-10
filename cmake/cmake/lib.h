
#pragma once

#include <iostream>
#include "cmake.h"

void cmake(int tabs);

static void cmake_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmake_header: " << cmake_MESSAGE << std::endl;
}