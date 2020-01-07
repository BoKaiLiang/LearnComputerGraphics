#ifndef _SHADER_H_
#define _SHADER_H_

#include <stdbool.h>

#include <glad/glad.h>
#include "mat.h"
#include "util.h"

typedef GLuint shader_t;

void create_shader(shader_t* shader, const char* vert_file, const char* frag_file);

void set_uniform_int(shader_t* shader, const char* uni_name, int val);
void set_uniform_float(shader_t* shader, const char* uni_name, float val);
void set_uniform_vec3(shader_t* shader, const char* uni_name, const vec3_t val);
void set_uniform_mat4(shader_t* shader, const char* uni_name, const mat4_t val);
#endif