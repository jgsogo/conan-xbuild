
#pragma once

#include <iostream>

void testlib(int tabs);

static void testlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testlib_header" << std::endl;
}