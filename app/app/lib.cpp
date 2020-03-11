
#include "app/lib.h"

// Requires and build_requires (host)
#include "library/lib.h"

void app(int tabs) {
    std::cout << std::string(tabs, '\t') << "> app: " << app_MESSAGE << std::endl;

    // Requires and build_requires (host)
    library_header(tabs+1);
    library(tabs+1);
}
