#include "../include/sha256.h"
#include <cassert>
#include <iostream>

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
  std::string str;
  std::cout << "Enter string to calc sha256: ";
  std::cin >> str;
  std::cout << sha256(str) << std::endl;
  std::cout << sha256Lib(str) << std::endl;

  std::cout << "Every test executed successfully!\n";
}
