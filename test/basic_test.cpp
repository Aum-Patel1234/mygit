#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/init.h"
#include "../include/sha256.h"
#include "../test/test.h"

namespace fs = std::filesystem;

void testBasicFunctions() {
    std::uint32_t a = 28u;
    std::uint32_t b = 16u;

    std::cout << "\nTesting Basic Functions....\n";

    // std::uint32_t res1 = rightRotate(a, 2);
    // std::uint32_t res2 = rightRotate(b, 3);
    assert(rightRotate(a, 2) == 112);
    assert(rightRotate(b, 3) == 128);
    // std::cout << res1 << "\n";
    // std::cout << res2 << "\n";
    // std::string str;
    // std::cout << "Enter string to calc sha256: ";
    // std::cin >> str;
    // std::cout << sha256(str) << std::endl;
    // std::cout << sha256Lib(str) << std::endl;

    const fs::path root = fs::current_path();
    // std::cout << path << std::endl; // will print the current path
    // Check directories
    assert(fs::exists(root / GIT_DIR));
    assert(fs::is_directory(root / GIT_DIR));
    assert(fs::exists(root / OBJECTS_INFO_DIR));
    assert(fs::exists(root / OBJECTS_PACK_DIR));
    assert(fs::exists(root / REFS_HEADS_DIR));
    assert(fs::exists(root / REFS_TAGS_DIR));

    // Check files
    assert(fs::exists(root / HEAD_FILE));
    assert(fs::exists(root / CONFIG_FILE));
    assert(fs::exists(root / DESCRIPTION_FILE));

    std::ifstream headFile(root / HEAD_FILE);
    std::string headContent;
    std::getline(headFile, headContent);
    assert(headContent == "ref: refs/heads/main");
    std::cout << "✅ git init test passed!\n";

    std::cout << "Every test executed successfully!\n";
}
