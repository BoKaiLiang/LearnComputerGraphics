#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "draw_line.h"
#include "svpng.h"

#define PI 3.14159265359f
#define W 512
#define H 512

static unsigned char image[W * H * 3];

int main()
{
    memset(image, 255, sizeof image);
    /*
    float cx = W * 0.5f - 0.5f, cy = H * 0.5f - 0.5f;
    for (int j = 0; j < 5; j++) {
        float r1 = fminf(W, H) * (j + 0.5f) * 0.085f;
        float r2 = fminf(W, H) * (j + 1.5f) * 0.085f;
        float t = j * PI / 64.0f;
        for (int i = 1; i <= 64; i++, t += 2.0f * PI / 64.0f) {
            float ct = cosf(t), st = sinf(t);
            draw_line_bresenham(image, W, H, (int)(cx + r1 * ct), (int)(cy - r1 * st), (int)(cx + r2 * ct), (int)(cy - r2 * st));
        }
    }
    */

    draw_line_bresenham(image, W, H, W / 2 - 60, H / 2 - 60, W / 2 + 60, W / 2 + 60);


    svpng(fopen("line_bresenham.png", "wb"), W, H, image, 0);
}