#pragma once

#include <string>
#include <Log.h>

class IImageIO;

class Image
{
    friend class ImageFactory;

 public:
    Image()
    {
        // DEBUG("Ctr");
    }

    ~Image()
    {
        // DEBUG("Dtr ", _width, " ", _height);
        free(_pixels);
    }

 public:
    bool           available ( ) const { return _pixels != nullptr; }
    std::string    name      ( ) const { return _name; }
    unsigned char* pixels    ( ) const { return _pixels; };
    unsigned int   width     ( ) const { return _width; };
    unsigned int   height    ( ) const { return _height; };
    unsigned int   bpp       ( ) const { return _bpp; };


 private:
    std::string _name;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
    unsigned char* _pixels;
};