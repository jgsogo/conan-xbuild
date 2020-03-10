
#pragma once

#include <iostream>
#include "zlib.h"

void zlib(int tabs);

static void zlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> zlib_header: " << zlib_MESSAGE << std::endl;
}