#include "../include/status.hpp"

void gitStatus() {
    if (!std::filesystem::exists(GIT_DIR)) {
        std::cout << GIT_DIR << " not initialized." << std::endl;
        std::exit(1);
    }
    std::cout << "yet to be implemented but " << GIT_DIR << " initialized" << std::endl;
}
