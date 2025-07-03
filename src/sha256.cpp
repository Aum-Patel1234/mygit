// refernece from - https://github.com/LekKit/sha256/blob/master/sha256.c

#include "../include/sha256.h"
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <openssl/sha.h>
#include <sstream>
#include <vector>

std::vector<uint8_t> padMessage(const std::string &input) {
  std::vector<uint8_t> padded(input.begin(), input.end());
  uint64_t bit_len = static_cast<uint64_t>(input.size()) * 8;

  // Append the '1' bit
  padded.push_back(0x80);

  // Pad with zeros until length ≡ 56 (mod 64)
  while (padded.size() % 64 != 56) {
    padded.push_back(0x00);
  }

  // Append length in bits as big-endian 64-bit
  for (int i = 7; i >= 0; --i) {
    padded.push_back((bit_len >> (8 * i)) & 0xFF);
  }
  return padded;
}

std::string sha256(const std::string &input) {
  // Initial hash values: first 32 bits of the fractional parts of the square
  // roots
  std::array<std::uint32_t, 8> h = {0x6a09e667, 0xbb67ae85, 0x3c6ef372,
                                    0xa54ff53a, 0x510e527f, 0x9b05688c,
                                    0x1f83d9ab, 0x5be0cd19};

  auto padded = padMessage(input);
  size_t chunks = padded.size() / 64;

  for (size_t c = 0; c < chunks; ++c) {
    std::array<std::uint32_t, 64> w{};
    const uint8_t *chunk = padded.data() + c * 64;

    // Prepare message schedule
    for (int i = 0; i < 16; ++i) {
      w[i] = (uint32_t(chunk[4 * i]) << 24) |
             (uint32_t(chunk[4 * i + 1]) << 16) |
             (uint32_t(chunk[4 * i + 2]) << 8) | (uint32_t(chunk[4 * i + 3]));
    }
    for (int i = 16; i < 64; ++i) {
      uint32_t s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^
                    (w[i - 15] >> 3);
      uint32_t s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^
                    (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Initialize working variables
    auto a = h;

    // Compression function
    for (int i = 0; i < 64; ++i) {
      uint32_t S1 =
          rightRotate(a[4], 6) ^ rightRotate(a[4], 11) ^ rightRotate(a[4], 25);
      uint32_t ch = (a[4] & a[5]) ^ (~a[4] & a[6]);
      uint32_t temp1 = a[7] + S1 + ch + k[i] + w[i];
      uint32_t S0 =
          rightRotate(a[0], 2) ^ rightRotate(a[0], 13) ^ rightRotate(a[0], 22);
      uint32_t maj = (a[0] & a[1]) ^ (a[0] & a[2]) ^ (a[1] & a[2]);
      uint32_t temp2 = S0 + maj;

      a[7] = a[6];
      a[6] = a[5];
      a[5] = a[4];
      a[4] = a[3] + temp1;
      a[3] = a[2];
      a[2] = a[1];
      a[1] = a[0];
      a[0] = temp1 + temp2;
    }

    // Add compressed chunk to current hash value
    for (int i = 0; i < 8; ++i) {
      h[i] += a[i];
    }
  }

  // Produce final hash as hex string
  std::ostringstream oss;
  oss << std::hex << std::setfill('0');
  for (auto val : h) {
    oss << std::setw(8) << val;
  }
  return oss.str();
}

// NOTE: Only below code is working
// # define SHA256_DIGEST_LENGTH    32
// maybe because the length in the library is 32 bit and i have taken code of 64
// bit
std::string sha256Lib(const std::string &inputStr) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  const unsigned char *data = (const unsigned char *)inputStr.c_str();
  SHA256(data, inputStr.size(), hash);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}
