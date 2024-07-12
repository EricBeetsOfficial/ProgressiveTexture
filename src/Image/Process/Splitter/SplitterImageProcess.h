#pragma once

#include <memory>
#include <list>
#include <Image.h>

class Block;

class SplitterImageProcess
{
   friend class Factory;
 private:
    SplitterImageProcess  ( );
    ~SplitterImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image, int blockSizeX = 128, int blockSizeY = 128);

 private:
   std::list<std::shared_ptr<Block>> _blocks;
};