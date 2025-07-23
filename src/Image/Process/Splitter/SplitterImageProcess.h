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
    // const std::list<std::shared_ptr<Block>>& getBlocks() const { return _blocks; }

    std::shared_ptr<Block> getBlock()
    {
        auto block = _blocks.front();
        _blocks.pop_front();
        return block;
    }
    bool isEmpty() const { return _blocks.empty(); }

    unsigned int width  ( ) const { return _width; };
    unsigned int height ( ) const { return _height; };
    unsigned int bpp    ( ) const { return _bpp; };
    unsigned int count  ( ) const { return _blocks.size(); }

 private:
    std::list<std::shared_ptr<Block>> _blocks;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
};