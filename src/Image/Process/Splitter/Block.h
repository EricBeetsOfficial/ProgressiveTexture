#pragma once

#include <Factory.h>
#include <Image.h>

class Block
{
   friend class Factory;
 private:
    Block(int width, int height, int countX, int countY, std::shared_ptr<Image>& image);
    ~Block();

 private:
   std::shared_ptr<Image> _image;
};
