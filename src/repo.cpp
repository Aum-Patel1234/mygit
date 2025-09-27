#include "../include/repo.h"
#include "../include/init.h"
#include <filesystem>

namespace fs = std::filesystem;

fs::path repoPath(fs::path &currDir, const char *pathToJoin) {
  return currDir.append(pathToJoin);
}

bool isGitInitialized() { return fs::exists(GIT_DIR); }
