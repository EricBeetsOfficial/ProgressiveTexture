#pragma once

#include <string>
#include <Log.h>
#include <Factory.h>

class Image
{
  template<typename T, typename U>
  friend class TFactory;

 private:
    Image(const std::string& filePath, int width, int height, int bpp, unsigned char* pixels)
    {
      // DEBUG()
      _name = filePath;
      _width = width;
      _height = height;
      _bpp = bpp;
      _pixels = pixels;
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

using FactoryImage = TFactory<Image, Image>;