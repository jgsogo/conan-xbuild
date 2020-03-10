
#pragma once

#include <iostream>
#include "testtool.h"

void testtool(int tabs);

static void testtool_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testtool_header: " << testtool_MESSAGE << std::endl;
}