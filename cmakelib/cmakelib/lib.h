
#pragma once

#include <iostream>
#include <string>
#include "cmakelib.h"
#include "cmakelib_export.h"

CMAKELIB_EXPORT void cmakelib(int tabs);

static void cmakelib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmakelib_header: " << cmakelib_MESSAGE << std::endl;
}