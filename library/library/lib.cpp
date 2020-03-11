
#include "library/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void library(int tabs) {
    std::cout << std::string(tabs, '\t') << "> library: " << library_MESSAGE << std::endl;

    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}