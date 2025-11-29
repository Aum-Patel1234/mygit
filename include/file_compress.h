#ifndef FILE_COMPRESS_H
#define FILE_COMPRESS_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define CHUNK 16384

#ifdef __cplusplus
extern "C" {
#endif

void compressFile(FILE* src, FILE* dest);
unsigned char* decompressFile(FILE* file, size_t* outSize);

#ifdef __cplusplus
}  // extern "C"
#endif  // !__cplusplus

#endif /* ifndef FILE_COMPRESS */
