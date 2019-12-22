#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#pragma pack(push,1)
typedef struct {
    char idlength;
	char colormaptype;
	char datatypecode;
	short colormaporigin;
	short colormaplength;
	char colormapdepth;
	short x_origin;
	short y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
} TGA_Header;
#pragma pack(pop)

//// TGA Color ////

typedef struct {
    union {

        struct {
            unsigned char r, g, b, a;
        };
        unsigned char raw[4];
        unsigned int val;
    };
    
    int bytespp;
} TGA_Color;

//// TGA Image ////
typedef struct {
    unsigned char* data;
	int width;
	int height;
	int bytespp;
} TGA_Image;

typedef enum {
    GRAYSCALE = 1, RGB = 3, RGBA = 4
} Format;

void tgaimg_init(TGA_Image* self, int w, int h, int bpp);
void tgaimg_copy(TGA_Image* self, const TGA_Image* copy);
void tgaimg_destroy(TGA_Image* self);

bool tgaimg_read_file(TGA_Image* self, const char* file_path);
bool tgaimg_write_file(TGA_Image* self, const char* file_path);

bool tgaimg_flip_horizontally(TGA_Image* self);
bool tgaimg_flip_vertically(TGA_Image* self);
bool tgaimg_scale(TGA_Image* self, int w, int h);
TGA_Color tgaimg_get_color(TGA_Image* self, int x, int y);
bool tgaimg_set_color(TGA_Image* self, int x, int y, TGA_Color c);
void tgaimg_clear(TGA_Image* self);

#endif // _TGA_IMAGE_H_