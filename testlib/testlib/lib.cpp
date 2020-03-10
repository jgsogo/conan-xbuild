
#include "testlib/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void testlib(int tabs) {
    #ifdef testlib_EXPORTS
        std::cout << std::string(tabs, '\t') << "> testlib: " << testlib_MESSAGE << " shared!" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> testlib: " << testlib_MESSAGE << std::endl;
    #endif

    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}