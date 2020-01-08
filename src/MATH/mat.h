#ifndef _MAT_H_
#define _MAT_H_

#include "vec.h"

typedef struct {
    union {
        vec3_t vec[3];
        float mat[3][3];
    };
} mat3_t;

typedef struct {
    union {
        vec4_t vec[4];
        float mat[4][4];
    };
} mat4_t;

// Matrix 3x3 operations
mat3_t mat3_identity();
mat3_t mat3_from_vec3(vec3_t col0, vec3_t col1, vec3_t col2);
mat3_t mat3_from_mat4(mat4_t mat);
vec3_t mat3_mul_vec3(mat3_t mat, vec3_t vec);
mat3_t mat3_mul_mat3(mat3_t mat1, mat3_t mat2);
mat3_t mat3_inverse(mat3_t m);
mat3_t mat3_transpose(mat3_t m);

// Matrix 4x4 operations
mat4_t mat4_identity();
mat4_t mat4_from_vec4(vec4_t col0, vec4_t col1, vec4_t col2, vec4_t col3);
mat4_t mat4_from_mat3(mat3_t mat);
vec4_t mat4_mul_vec4(mat4_t mat, vec4_t vec);
mat4_t mat4_mul_mat4(mat4_t mat1, mat4_t mat2);
mat4_t mat4_inverse(mat4_t m);
mat4_t mat4_transpose(mat4_t m);

// Transformations (3D)
mat4_t mat4_translate(mat4_t origin, float x, float y, float z);
mat4_t mat4_rotate(mat4_t origin, vec3_t axis, float angle);
mat4_t mat4_scale(mat4_t origin, float x, float y, float z);
mat4_t mat4_lookat(vec3_t eye, vec3_t target, vec3_t world_up);
mat4_t mat4_ortho(float left, float right, float bottom, float top, float near, float far);
mat4_t mat4_frustum(float left, float right, float bottom, float top, float near, float far);
mat4_t mat4_orthographics(float right, float top, float near, float far);
mat4_t mat4_perspective(float fovy, float aspect, float near, float far);

#endif // _MAT_H_