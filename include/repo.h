#include <filesystem>
#ifndef REPO

std::filesystem::path repoPath(std::filesystem::path& currDir, const char* pathToJoin);

bool isGitInitialized();

#endif  // !GITINIT
