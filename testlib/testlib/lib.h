
#pragma once

#include <iostream>
#include "testlib.h"
#include "testlib_export.h"

TESTLIB_EXPORT void testlib(int tabs);

static void testlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testlib_header: " << testlib_MESSAGE << std::endl;
}