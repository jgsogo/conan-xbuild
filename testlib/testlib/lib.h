
#pragma once

#include <iostream>
#include "testlib.h"

void testlib(int tabs);

static void testlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testlib_header: " << testlib_MESSAGE << std::endl;
}