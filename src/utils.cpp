#include "../include/utils.h"

std::string zlib_decompress(const std::string& compressed) {
    if (compressed.empty())
        return {};

    uLongf destLen = compressed.size() * 4 + 128;  // initial guess
    std::vector<unsigned char> dest(destLen);

    int ret = uncompress(dest.data(),
                         &destLen,
                         reinterpret_cast<const unsigned char*>(compressed.data()),
                         static_cast<uLong>(compressed.size()));

    while (ret == Z_BUF_ERROR) {
        destLen *= 2;
        dest.assign(destLen, 0);
        ret = uncompress(dest.data(),
                         &destLen,
                         reinterpret_cast<const unsigned char*>(compressed.data()),
                         static_cast<uLong>(compressed.size()));
    }

    if (ret != Z_OK) {
        throw std::runtime_error("zlib decompression failed (code " + std::to_string(ret) + ")");
    }

    return std::string(reinterpret_cast<char*>(dest.data()), static_cast<std::size_t>(destLen));
}
