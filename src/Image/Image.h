#pragma once

#include <string>
#include <memory>

struct Image
{
    std::string _texturePath;
    unsigned int width;
    unsigned int height;
    unsigned int bpp;
    std::shared_ptr<unsigned char> _pixels;
};