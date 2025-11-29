#ifndef TEST_H
#define TEST_H

#include <string.h>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/init.h"
#include "../include/sha256.h"
extern "C" {
#include "../include/file_compress.h"
}

void testBasicFunctions();
void testCompressDecompress();

#endif  // !TEST
