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
#include "utils.h"

void gitInit();

#endif  // !GITINIT
