#include "../include/file_compress.h"

void compressFile(FILE* src, FILE* dest) {
    // ret — an int used to hold return codes from zlib functions (e.g. deflate, deflateInit).
    // flush — an int used to tell deflate() whether this is the final chunk
    int ret, flush;
    // have — holds the number of bytes produced by deflate() that are written to dest. unsigned int matches zlib’s
    // typical buffer-size types; sometimes size_t is used instead.
    unsigned int have;
    // stream — the main zlib structure that holds state for compression (pointers to input/output buffers, available
    // byte counts, allocator hooks, internal state, etc.
    z_stream stream;
    // in is the read buffer (raw bytes read from src).
    // out is the compressed output buffer to be written to dest.
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    // set z_stream up for compression
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    // Call deflateInit to initialize stream for compression with the default compression level.
    ret = deflateInit(&stream, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK)
        return;

    // compress the File
    do {
        // fread returns the number of elements read; here elements are 1 byte, so it returns the number of bytes
        // actually read (0..CHUNK).
        // stream.avail_in tells zlib how many input bytes are available in stream.next_in (which we set next).
        stream.avail_in = fread(in, 1, CHUNK, src);

        // If fread encountered a read error, ferror(src) is true.Cleanup internal zlib state with deflateEnd
        // and return.
        // (void)casts the return of deflateEnd to void to indicate we ignore it.
        if (ferror(src)) {
            (void)deflateEnd(&stream);
            return;
        }

        // if we reach end of File then Z_FINISH to tell deflate() its the last else Z_NO_FLUSH
        flush = feof(src) ? Z_FINISH : Z_NO_FLUSH;
        // Point stream.next_in at the input buffer we just filled. zlib will read from this buffer
        stream.next_in = in;

        // run deflate() on input untill output buffer not full
        do {
            stream.avail_out = CHUNK;
            stream.next_out = out;
            // At this moment the buffer out[] contains a block of compressed bytes.
            ret = deflate(&stream, flush);

            assert(ret != Z_STREAM_ERROR);

            have = CHUNK - stream.avail_out;
            // This line writes the compressed bytes to the destination file
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                // on error end the process
                (void)deflateEnd(&stream);
                return;
            }
        } while (stream.avail_out == 0);
        assert(stream.avail_in == 0);
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);

    // cleanup
    (void)deflateEnd(&stream);
}

unsigned char* decompressFile(FILE* file, size_t* outSize) {
    int ret;
    unsigned have;
    z_stream stream;
    unsigned char in[CHUNK];

    size_t capacity = CHUNK, size = 0;

    unsigned char* outBuff = malloc(capacity);
    if (!outBuff)
        return NULL;

    // initialize z_stream for decompression
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    ret = inflateInit(&stream);
    if (ret != Z_OK)
        return NULL;

    // Decompress until deflate stream ends or end of file
    do {
        stream.avail_in = fread(in, 1, CHUNK, file);
        if (ferror(file)) {
            (void)inflateEnd(&stream);
            free(outBuff);
            return NULL;
        }
        if (stream.avail_in == 0)  // the file has reached EOF
            break;
        stream.next_in = in;

        // Run inflate() on input until output buffer not full
        do {
            // Ensure capacity can hold next CHUNK output
            if (size + CHUNK > capacity) {
                capacity *= 2;
                unsigned char* newBuff = realloc(outBuff, capacity);
                if (!newBuff) {
                    inflateEnd(&stream);
                    free(outBuff);
                    return NULL;
                }
                outBuff = newBuff;
            }

            stream.avail_out = CHUNK;
            // write output starting at outBuff + size
            stream.next_out = outBuff + size;

            // Perform decompression:
            ret = inflate(&stream, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);

            switch (ret) {
                case Z_NEED_DICT:
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&stream);
                    free(outBuff);
                    return NULL;
            }

            // IMPORTANT:
            // zlib will reduce avail_out as it writes data.
            // If no data was produced, avail_out remains equal to CHUNK.
            // If it wrote some bytes, avail_out goes down.
            // If it filled the entire buffer, avail_out == 0.
            // Hence
            //     ➡️ avail_out counts free space
            //     ➡️ CHUNK is total buffer space
            //     ➡️ CHUNK - free_space = used_space
            have = CHUNK - stream.avail_out;
            size += have;

        } while (stream.avail_out == 0);
    } while (ret != Z_STREAM_END);

    (void)inflateEnd(&stream);
    *outSize = size;
    return outBuff;
}
