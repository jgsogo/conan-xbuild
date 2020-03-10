
#pragma once

#include <iostream>

void zlib(int tabs);

static void zlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> zlib_header" << std::endl;
}