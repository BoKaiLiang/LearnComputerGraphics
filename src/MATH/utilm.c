#include "utilm.h"

float utilm_rad(float deg)
{
    return deg * PI / 180.0f;
}

float utilm_deg(float rad)
{
    return rad * 180.0f / PI;
}

float utilm_minf(float a, float b)
{
    return a < b ? a : b;
}

float utilm_maxf(float a, float b)
{
    return a > b ? a : b;
}

void utilm_swapf(float* a, float* b)
{
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

float utilm_lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

float utilm_clamp(float val, float min, float max)
{
    return val < min ? min : (val > max ? max : val);
}