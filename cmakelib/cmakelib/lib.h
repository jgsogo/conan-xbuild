
#pragma once

#include <iostream>

void cmakelib(int tabs);

static void cmakelib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmakelib_header" << std::endl;
}