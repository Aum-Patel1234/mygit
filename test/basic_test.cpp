#include "../include/sha256.h"
#include <bitset>
#include <iostream>

void testBasicFunctions() {
  std::uint32_t a = 28u;
  std::uint32_t b = 16u;

  std::cout << "\nTesting Basic Functions:\n";

  std::uint32_t res1 = rightRotate(a, 2);
  std::uint32_t res2 = rightRotate(b, 3);
  std::cout << res1 << "\n";
  std::cout << res2 << "\n";
}
