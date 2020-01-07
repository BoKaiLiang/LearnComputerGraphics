#ifndef _UTILM_H_
#define _UTILM_H_

#define PI 3.14159265359

float utilm_rad(float deg);
float utilm_deg(float rad);
float utilm_minf(float a, float b);
float utilm_maxf(float a, float b);
void utilm_swapf(float* a, float* b);
float utilm_lerp(float a, float b, float t);
float utilm_clamp(float val, float min, float max);

#endif // _UTILM_H_