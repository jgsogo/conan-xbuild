
#pragma once

#include <iostream>

void app(int tabs);

static void app_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> app_header" << std::endl;
}