
#include <iostream>
#include <fstream>
#include <sstream>

#include "gcc/lib.h"


void actual_work(const std::string& project) {
    // Opens 'xxxx/lib.cpp' and add the compilation line
    std::ifstream ifs(project + "/lib.cpp");

    std::string output = "";
    std::string line;
    while (std::getline(ifs, line))
    {
        output += line + "\n";
        if (line.find("(int tabs) {") != std::string::npos) {
            output += std::string("    std::cout << \"Compiled with GCC: ") + gcc_MESSAGE + "\" << std::endl;\n"; 
        }
    }
    ifs.close();

    std::ofstream ofs(project + "/lib.cpp");
    ofs << output;
    ofs.close();
}


int main(int argc, char *argv[]) {
    std::cout << "> gcc_exe" << std::endl;
    
    gcc_header(0);
    gcc(0);

    actual_work(argv[1]);
}