
#include <iostream>


#include "cmake/lib.h"


int main() {
    std::cout << "> cmake_exe: " << cmake_MESSAGE << std::endl;
    
    cmake_header(0);
    cmake(0);
    
}