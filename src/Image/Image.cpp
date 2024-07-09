#include <Image.h>
#include <Log.h>

Image::Image(const std::string& filePath, int width, int height, int bpp, unsigned char* pixels)
{
    // DEBUG()
    _name = filePath;
    _width = width;
    _height = height;
    _bpp = bpp;
    _pixels = pixels;
}

Image::~Image()
{
    // DEBUG("Dtr ", _width, " ", _height);
    free(_pixels);
}