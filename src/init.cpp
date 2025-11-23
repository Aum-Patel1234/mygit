#include "../include/init.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../include/repo.h"

namespace fs = std::filesystem;

void gitInit() {
    // fist create .mygit dir
    const fs::path gitPath = GIT_DIR;
    if (fs::exists(GIT_DIR)) {
        std::cout << "Git directory aldready intialized...\n";
        return;
    }
    fs::create_directory(gitPath);

    std::cout << "Initializing an empty .mygit directory\n";
    // create the subdirectories
    fs::create_directories(OBJECTS_INFO_DIR);
    fs::create_directories(OBJECTS_PACK_DIR);
    fs::create_directories(REFS_HEADS_DIR);
    fs::create_directories(REFS_TAGS_DIR);

    // create file HEAD with default content
    std::ofstream(HEAD_FILE) << DEFAULT_HEAD_CONTENT;

    // create empty files
    std::ofstream config(CONFIG_FILE);
    std::ofstream description(DESCRIPTION_FILE);

    if (!description) {
        throw std::runtime_error("Failed to create description file");
    }

    description << "Unnamed repository; edit this file 'description' to name the repository.\n";
    repoDefaultConfig();
}
