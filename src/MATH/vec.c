#include "vec.h"

#include "math.h"

// 2D vector operations
vec2_t vec2_init(float x, float y) 
{
    vec2_t v;
    v.x = x;
    v.y = y;
    return v;
}

vec2_t vec2_zero()
{
    return vec2_init(0.0f, 0.0f);
}

vec2_t vec2_one()
{
    return vec2_init(1.0f, 1.0f);
}

vec2_t vec2_from_vec3(vec3_t src) 
{
    return vec2_init(src.x, src.y);
}

vec2_t vec2_from_vec4(vec4_t src)
{
    return vec2_init(src.x, src.y);
}

vec2_t vec2_negate(vec2_t v) 
{
    return vec2_init(-v.x, -v.y);
}

vec2_t vec2_add(vec2_t v1, vec2_t v2)
{
    return vec2_init(v1.x + v2.x, v1.y + v2.y);
}

vec2_t vec2_sub(vec2_t v1, vec2_t v2) 
{
    return vec2_init(v1.x - v2.x, v1.y - v2.y);
}

vec2_t vec2_scale(vec2_t v, float s)
{
    return vec2_init(v.x * s, v.y * s);
}

float vec2_len(vec2_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

vec2_t vec2_norm(vec2_t v)
{
    return vec2_scale(v, (float)(1 / vec2_len(v)));
}

// 3D vector operations
vec3_t vec3_init(float x, float y, float z) 
{
    vec3_t v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

vec3_t vec3_zero()
{
    return vec3_init(0.0f, 0.0f, 0.0f);
}

vec3_t vec3_one()
{
    return vec3_init(1.0f, 1.0f, 1.0f);
}

vec3_t vec3_from_vec2(vec2_t src) 
{
    return vec3_init(src.x, src.y, 0.0f);
}

vec3_t vec3_from_vec4(vec4_t src)
{
    return vec3_init(src.x, src.y, src.z);
}

vec3_t vec3_negate(vec3_t v) 
{
    return vec3_init(-v.x, -v.y, -v.z);
}

vec3_t vec3_add(vec3_t v1, vec3_t v2)
{
    return vec3_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2) 
{
    return vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3_t vec3_scale(vec3_t v, float s)
{
    return vec3_init(v.x * s, v.y * s, v.z * s);
}

float vec3_dot(vec3_t v1, vec3_t v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2)
{
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;

    return vec3_init(x, y, z);
}

float vec3_len(vec3_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_norm(vec3_t v)
{
    return vec3_scale(v, (float)(1 / vec3_len(v)));
}

// 4D vector operations
vec4_t vec4_init(float x, float y, float z, float w) 
{
    vec4_t v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

vec4_t vec4_zero()
{
    return vec4_init(0.0f, 0.0f, 0.0f, 0.0f);
}

vec4_t vec4_one()
{
    return vec4_init(1.0f, 1.0f, 1.0f, 1.0f);
}

vec4_t vec4_from_vec3(vec3_t src) 
{
    return vec4_init(src.x, src.y, src.z, 0.0f);
}

vec4_t vec4_from_vec2(vec2_t src)
{
    return vec4_init(src.x, src.y, 0.0f, 0.0f);
}

vec4_t vec4_negate(vec4_t v) 
{
    return vec4_init(-v.x, -v.y, -v.z, -v.w);
}

vec4_t vec4_add(vec4_t v1, vec4_t v2)
{
    return vec4_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

vec4_t vec4_sub(vec4_t v1, vec4_t v2) 
{
    return vec4_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

vec4_t vec4_scale(vec4_t v, float s)
{
    return vec4_init(v.x * s, v.y * s, v.z * s, v.w * s);
}

float vec4_len(vec4_t v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

vec4_t vec4_norm(vec4_t v)
{
    return vec4_scale(v, (float)(1 / vec4_len(v)));
}