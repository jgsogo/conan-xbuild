
#pragma once

#include <iostream>
#include <string>
#include "gcc.h"
#include "gcc_export.h"

GCC_EXPORT void gcc(int tabs);

static void gcc_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> gcc_header: " << gcc_MESSAGE  << std::endl;
}