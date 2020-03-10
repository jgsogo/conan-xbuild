
#pragma once

#include <iostream>

void testtool(int tabs);

static void testtool_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testtool_header" << std::endl;
}