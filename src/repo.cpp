#include "../include/repo.h"
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <string>
#include "../include/config_parser.hpp"

namespace fs = std::filesystem;

inline fs::path repoPath(const fs::path& cwd, const fs::path pathToJoin) {
    return cwd / pathToJoin;
}

std::optional<fs::path> repoDir(const fs::path& cwd, const fs::path& path, bool mkdir) {
    fs::path targetPath = cwd / path;

    if (fs::exists(targetPath)) {
        if (fs::is_directory(targetPath))
            return targetPath;
        else
            throw std::runtime_error("Not a directory: " + targetPath.string());
    }

    if (mkdir) {
        fs::create_directories(targetPath);
        return targetPath;
    }

    return std::nullopt;
}

std::optional<fs::path> repoFile(const fs::path& cwd, const fs::path& filePath, bool mkdir) {
    if (repoDir(cwd, filePath.parent_path(), mkdir))
        return repoPath(cwd, filePath);
    return std::nullopt;
}

void repoDefaultConfig() {
    ConfigParser cf;
    const std::string core = "core";
    cf[core].set("repositoryformatversion", "0");
    cf[core].set("fileMode", "false");
    cf[core].set("bare", "false");

    cf.write(CONFIG_FILE);
}

std::optional<fs::path> repoFind(const std::string& pathString, bool required) {
    // not use canonical cause it requires the path to be really present or throws bug
    fs::path path = fs::weakly_canonical(pathString);  // turns string into path

    if (fs::is_directory(path) && fs::is_directory(path / GIT_DIR))
        return path;

    fs::path parent = path.parent_path();

    if (parent == path) {
        if (required)
            throw std::runtime_error("No git directory.\n");
        return std::nullopt;
    }
    return repoFind(parent, required);
}
