
#include "cmakelib/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void cmakelib(int tabs) {
    std::cout << std::string(tabs, '\t') << "> cmakelib: " << cmakelib_MESSAGE << std::endl;


    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}