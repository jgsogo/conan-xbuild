
#include "gcc/lib.h"

// Requires and build_requires (host)
#include "zlib/lib.h"

void gcc(int tabs) {
    std::cout << std::string(tabs, '\t') << "> gcc: " << gcc_MESSAGE << std::endl;

    // Requires and build_requires (host)
    zlib_header(tabs+1);
    zlib(tabs+1);
}
