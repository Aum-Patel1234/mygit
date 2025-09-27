#include "../include/init.h"
#include "../include/repo.h"
#include <iostream>

void gitStatus() {
  if (!isGitInitialized()) {
    std::cout << GIT_DIR << " not initialized." << std::endl;
    std::exit(1);
  }
  std::cout << "yet to be implemented but " << GIT_DIR << " initialized"
            << std::endl;
}
