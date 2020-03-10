
#include "library/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void library(int tabs) {
    #ifdef library_EXPORTS
        std::cout << std::string(tabs, '\t') << "> library: (shared!)" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> library" << std::endl;
    #endif

    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}