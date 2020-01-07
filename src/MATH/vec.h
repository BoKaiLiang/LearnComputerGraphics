#ifndef _VEC_H_
#define _VEC_H_

typedef struct {
    union {
        struct { float x, y; };
        float arr[2];
    };
} vec2_t;

typedef struct {
    union {
        struct { float x, y, z; };
        struct { float r, g, b; };
        float arr[3];
    };
} vec3_t;

typedef struct {
    union {
        struct { float x, y, z, w; };
        struct { float r, g, b, a; };
        float arr[4];
    };
} vec4_t;

// 2D vector operations
vec2_t vec2_init(float x, float y);
vec2_t vec2_zero();
vec2_t vec2_one();
vec2_t vec2_from_vec3(vec3_t src);
vec2_t vec2_from_vec4(vec4_t src);
vec2_t vec2_negate(vec2_t v);
vec2_t vec2_add(vec2_t v1, vec2_t v2);
vec2_t vec2_sub(vec2_t v1, vec2_t v2);
vec2_t vec2_scale(vec2_t v, float s);
float vec2_len(vec2_t v);
vec2_t vec2_norm(vec2_t v);

// 3D vector operations
vec3_t vec3_init(float x, float y, float z);
vec3_t vec3_zero();
vec3_t vec3_one();
vec3_t vec3_from_vec2(vec2_t src);
vec3_t vec3_from_vec4(vec4_t src);
vec3_t vec3_negate(vec3_t v);
vec3_t vec3_add(vec3_t v1, vec3_t v2);
vec3_t vec3_sub(vec3_t v1, vec3_t v2);
vec3_t vec3_scale(vec3_t v, float s);
float vec3_dot(vec3_t v1, vec3_t v2);
vec3_t vec3_cross(vec3_t v1, vec3_t v2);
float vec3_len(vec3_t v);
vec3_t vec3_norm(vec3_t v);

// 4D vector operations
vec4_t vec4_init(float x, float y, float z, float w);
vec4_t vec4_zero();
vec4_t vec4_one();
vec4_t vec4_from_vec2(vec2_t src);
vec4_t vec4_from_vec3(vec3_t src);
vec4_t vec4_negate(vec4_t v);
vec4_t vec4_add(vec4_t v1, vec4_t v2);
vec4_t vec4_sub(vec4_t v1, vec4_t v2);
vec4_t vec4_scale(vec4_t v, float s);
float vec4_len(vec4_t v);
vec4_t vec4_norm(vec4_t v);

#endif // _VEC_H_