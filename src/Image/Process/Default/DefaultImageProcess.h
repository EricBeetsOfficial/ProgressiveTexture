#pragma once

#include <memory>
#include <Image.h>

class DefaultImageProcess
{
   friend class Factory;
 private:
    DefaultImageProcess  ( );
    ~DefaultImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image,  int w, int h);
};