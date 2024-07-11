#pragma once

#include <memory>
#include <Image.h>

class ResizerImageProcess
{
   friend class Factory;
 private:
    ResizerImageProcess  ( );
    ~ResizerImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image,  int w, int h);
};