#include "../include/utils.h"

std::string decompressGitObject(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    std::size_t rawSize = 0;
    if (!f)
        throw std::runtime_error("Failed to open file");

    // decompress File
    unsigned char* raw = decompressFile(f, &rawSize);
    fclose(f);
    if (!raw)
        throw std::runtime_error("Failed to decompress Git object");

    std::string rawStr(reinterpret_cast<char*>(raw), rawSize);

    // Free memory allocated by C
    free(raw);

    return rawStr;
}
