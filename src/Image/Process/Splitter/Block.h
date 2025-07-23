#pragma once

#include <Factory.h>
#include <Image.h>

class Block
{
   friend class Factory;
 private:
    Block(int width, int height, int countX, int countY, std::shared_ptr<Image>& image);
    Block(const Block &);
    ~Block();

 public:
    const std::shared_ptr<Image>& get ( ) const { return _image; }
    const unsigned int xOffset ( ) const { return _xOffset; }
    const unsigned int yOffset ( ) const { return _yOffset; }

 private:
   std::shared_ptr<Image> _image;
   unsigned int _xOffset;
   unsigned int _yOffset;
};
