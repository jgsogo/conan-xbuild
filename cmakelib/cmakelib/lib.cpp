
#include "cmakelib/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void cmakelib(int tabs) {
    #ifdef cmakelib_EXPORTS
        std::cout << std::string(tabs, '\t') << "> cmakelib: (shared!)" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> cmakelib" << std::endl;
    #endif


    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}