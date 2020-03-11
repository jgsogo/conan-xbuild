
#include "testtool/lib.h"

// Requires and build_requires (host)
#include "testlib/lib.h"

void testtool(int tabs) {
    std::cout << std::string(tabs, '\t') << "> testtool: " << testtool_MESSAGE << std::endl;

    // Requires and build_requires (host)
    testlib_header(tabs+1);
    testlib(tabs+1);
}
