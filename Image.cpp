#include "Image.h"

Header::Pixel::Pixel(unsigned char r, unsigned char g,unsigned char b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}

short Header::Getheight() {
    return this->height;
}

short Header::Getwidth() {
    return this->width;
}