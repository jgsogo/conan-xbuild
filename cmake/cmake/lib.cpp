
#include "cmake/lib.h"

// Requires and build_requires (host)
#include "cmakelib/lib.h"

void cmake(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmake: " << cmake_MESSAGE << std::endl;

    // Requires and build_requires (host)
    cmakelib_header(tabs+1);
    cmakelib(tabs+1);
}