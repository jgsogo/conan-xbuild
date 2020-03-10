
#pragma once

#include <iostream>
#include "cmakelib.h"

void cmakelib(int tabs);

static void cmakelib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmakelib_header: " << cmakelib_MESSAGE << std::endl;
}