#ifndef IMAGE_PROCESSING_IMAGE_H
#define IMAGE_PROCESSING_IMAGE_H
#include <string>
#include <vector>
using std::string;
using namespace std;
using std::vector;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin = 0;
    short colorMapLength = 0;
    char colorMapDepth = 0;
    short xOrigin = 0;
    short yOrigin = 0;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    short Getwidth();
    short Getheight();
    struct Pixel {
        Pixel(unsigned char r, unsigned char g, unsigned char b);
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };
};




#endif //IMAGE_PROCESSING_IMAGE_H
