
#include "testtool/lib.h"

// Requires and build_requires (host)
#include "testlib/lib.h"

void testtool(int tabs) {
    #ifdef testtool_EXPORTS
        std::cout << std::string(tabs, '\t') << "> testtool: " << testtool_MESSAGE << " (shared!)" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> testtool: " << testtool_MESSAGE << std::endl;
    #endif

    // Requires and build_requires (host)
    testlib_header(tabs+1);
    testlib(tabs+1);
}
