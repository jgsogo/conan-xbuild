
#include "testlib/lib.h"

void testlib(int tabs) {
    #ifdef testlib_EXPORTS
        std::cout << std::string(tabs, '\t') << "> testlib: shared!" << std::endl;
    #else
        std::cout << std::string(tabs, '\t') << "> testlib" << std::endl;
    #endif
}