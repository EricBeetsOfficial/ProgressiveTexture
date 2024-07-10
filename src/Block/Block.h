#pragma once

#include <Factory.h>

class Block
{
  template<typename T, typename U>
  friend class TFactory;

 private:
    Block();
    ~Block();
};

using FactoryBlock = TFactory<Block, Block>;
