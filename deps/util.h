#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stb_image.h>
#include <glad/glad.h>

void load_file_to_string(const char* file_path, char** dst);
unsigned int load_texture(const char* file_path);

#endif