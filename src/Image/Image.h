#pragma once

#include <string>
#include <memory>

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

class ImageFactory
{
 protected:
    std::shared_ptr<Image> createImage(const std::string& filePath, int width, int height, int bpp, unsigned char* pixels)
    {
      std::shared_ptr<Image> image = std::make_shared<Image>();
      image->_name = filePath;
      image->_width = width;
      image->_height = height;
      image->_bpp = bpp;
      image->_pixels = pixels;
      return image;
    }
};