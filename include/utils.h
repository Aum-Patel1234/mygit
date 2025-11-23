#ifndef UTILS
#define UTILS

constexpr const char* GIT_DIR = ".mygit";
constexpr const char* HEAD_FILE = ".mygit/HEAD";
constexpr const char* CONFIG_FILE = ".mygit/config";
constexpr const char* DESCRIPTION_FILE = ".mygit/description";

constexpr const char* OBJECTS_DIR = ".mygit/objects";
constexpr const char* OBJECTS_INFO_DIR = ".mygit/objects/info";
constexpr const char* OBJECTS_PACK_DIR = ".mygit/objects/pack";

constexpr const char* REFS_DIR = ".mygit/refs";
constexpr const char* REFS_HEADS_DIR = ".mygit/refs/heads";
constexpr const char* REFS_TAGS_DIR = ".mygit/refs/tags";

constexpr const char* DEFAULT_HEAD_CONTENT = "ref: refs/heads/main\n";

#endif  // !UTILS
