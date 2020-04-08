
#pragma once

#include <iostream>
#include <string>
#include "testtool.h"
#include "testtool_export.h"

TESTTOOL_EXPORT void testtool(int tabs);

static void testtool_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testtool_header: " << testtool_MESSAGE << std::endl;
}