#ifndef _DRAW_LINE_H_
#define _DRAW_LINE_H_

#include <stdbool.h>
#include <math.h>

void setpixel(unsigned char* img, int width, int height, int x, int y);

void draw_line_bresenham(unsigned char* img, int width, int height, int x0, int y0, int x1, int y1);

#endif // _DRAW_LINE_H_