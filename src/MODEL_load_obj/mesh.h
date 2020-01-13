#ifndef _MESH_H_
#define _MESH_H_


#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <float.h>

#include "dyarray.h"
#include "../MATH/mat.h"

typedef struct {
    vec3_t* positions;
    vec2_t* texcoords;
    vec3_t* normals;

    unsigned int num_positions;
    unsigned int num_texcoords;
    unsigned int num_normals;
    
} mesh_t;

mesh_t* mesh_load(const char* fpath);
void mesh_release(mesh_t* mesh);

#endif // _MESH_H_