
#pragma once

#include <iostream>
#include "library.h"

void library(int tabs);

static void library_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> library_header: " << library_MESSAGE << std::endl;
}