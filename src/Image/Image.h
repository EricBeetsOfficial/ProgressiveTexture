#pragma once

#include <string>
#include <Factory.h>

class Image
{
   friend class Factory;
 private:
    Image  (const std::string& filePath, unsigned int width, unsigned int height, unsigned int bpp, unsigned char* pixels);
    Image  (unsigned int width, unsigned int height, unsigned int bpp, unsigned char* pixels);
    ~Image ( );

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