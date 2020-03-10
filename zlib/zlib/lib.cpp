
#include "zlib/lib.h"

void zlib(int tabs) {
    #ifdef zlib_EXPORTS
        std::cout << std::string(tabs, '\t') << "> zlib: " << zlib_MESSAGE << " shared!" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> zlib: " << zlib_MESSAGE << std::endl;
    #endif
}