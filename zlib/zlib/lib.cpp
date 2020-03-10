
#include "zlib/lib.h"

void zlib(int tabs) {
    #ifdef zlib_EXPORTS
        std::cout << std::string(tabs, '\t') << "> zlib: shared!" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> zlib" << std::endl;
    #endif
}