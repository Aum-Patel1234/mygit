#include "../include/init.h"
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

void gitInit() {
  // fist create .mygit dir
  const fs::path gitPath = GIT_DIR;
  fs::create_directory(gitPath);

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
}
