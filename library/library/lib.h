
#pragma once

#include <iostream>

void library(int tabs);

static void library_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> library_header" << std::endl;
}