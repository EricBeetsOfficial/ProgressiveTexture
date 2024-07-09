#pragma once

#include <memory>
#include <Image.h>

// TODO: Merge with Factory class
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