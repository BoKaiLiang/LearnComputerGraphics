#include "tga_image.h"

void tgaimg_init(TGA_Image* self, int w, int h, int bpp) {
    self->width = w;
    self->height = h;
    self->bytespp = bpp;
    unsigned long nbytes = w * h * bpp;
    self->data = malloc(nbytes * sizeof(unsigned char));
    memset(self->data, 0, nbytes);
}

void tgaimg_copy(TGA_Image* self, const TGA_Image* copy) {
    self->width = copy->width;
    self->height = copy->height;
    self->bytespp = copy->bytespp;
    unsigned long nbytes = copy->width * copy->height * copy->bytespp;
    self->data = malloc(nbytes * sizeof(unsigned char));
    memcpy(self->data, copy->data, nbytes);
}

void tgaimg_destroy(TGA_Image* self) {
    if (self->data) {
        free(self->data);
    }
}

bool tgaimg_read_file(TGA_Image* self, const char* file_path) {
    
}

bool tgaimg_write_file(TGA_Image* self, const char* file_path) {

}

bool tgaimg_flip_horizontally(TGA_Image* self) {

}

bool tgaimg_flip_vertically(TGA_Image* self) {

}

bool tgaimg_scale(TGA_Image* self, int w, int h) {

}

TGA_Color tgaimg_get_color(TGA_Image* self, int x, int y) {

}

bool tgaimg_set_color(TGA_Image* self, int x, int y, TGA_Color c) {

}

void tgaimg_clear(TGA_Image* self) {
    
}