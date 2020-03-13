
#pragma once

#include <iostream>
#include <string>
#include "zlib.h"
#include "zlib_export.h"

ZLIB_EXPORT void zlib(int tabs);

static void zlib_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> zlib_header: " << zlib_MESSAGE << std::endl;
}