// .mygit/
// ├── HEAD
// ├── config
// ├── description
// ├── objects/
// │   ├── info/
// │   └── pack/
// └── refs/
//     ├── heads/
//     └── tags/
// In your C++ project, your mygit init command should:
//
//     Create .mygit/
//
//     Create subdirectories:
//
//         .mygit/objects/info
//
//         .mygit/objects/pack
//
//         .mygit/refs/heads
//
//         .mygit/refs/tags
//
//     Create empty files:
//
//         .mygit/HEAD → with content: ref: refs/heads/main
//
//         .mygit/config → optional, you can initialize later
//
//         .mygit/description → optional

#ifndef GITINIT

constexpr const char *GIT_DIR = ".mygit";
constexpr const char *HEAD_FILE = ".mygit/HEAD";
constexpr const char *CONFIG_FILE = ".mygit/config";
constexpr const char *DESCRIPTION_FILE = ".mygit/description";

constexpr const char *OBJECTS_DIR = ".mygit/objects";
constexpr const char *OBJECTS_INFO_DIR = ".mygit/objects/info";
constexpr const char *OBJECTS_PACK_DIR = ".mygit/objects/pack";

constexpr const char *REFS_DIR = ".mygit/refs";
constexpr const char *REFS_HEADS_DIR = ".mygit/refs/heads";
constexpr const char *REFS_TAGS_DIR = ".mygit/refs/tags";

constexpr const char *DEFAULT_HEAD_CONTENT = "ref: refs/heads/main\n";

void gitInit();

#endif // !GITINIT
