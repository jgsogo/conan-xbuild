
#pragma once

#include <iostream>

void cmake(int tabs);

static void cmake_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmake_header" << std::endl;
}