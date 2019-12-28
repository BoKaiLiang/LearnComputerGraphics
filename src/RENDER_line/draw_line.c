#include "draw_line.h"

void setpixel(unsigned char* img, int width, int height, int x, int y) 
{
    unsigned char* p = img + (y * width + x) * 3;
    p[0] = p[1] = p[2] = 0;
}

static void swap(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void draw_line_bresenham(unsigned char* img, int width, int height, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (setpixel(img, width, height, x0, y0), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}
