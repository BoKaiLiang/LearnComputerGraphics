#include "util.h"

void load_file_to_string(const char* file_path, char** dst)
{
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "fopen %s failed: %d %s\n", file_path, errno, strerror(errno));
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);
    *dst = calloc(length + 1, sizeof(char));
    fread(*dst, 1, length, file);
    fclose(file);
}