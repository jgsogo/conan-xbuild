
#pragma once

#include <iostream>
#include <string>
#include "app.h"
#include "app_export.h"

APP_EXPORT void app(int tabs);

static void app_header(int tabs) {
    std::cout << std::string(tabs, '\t') << "> app_header: " << app_MESSAGE  << std::endl;
}