#pragma once

#include <Image.h>

class FlipperImageProcess
{
   friend class Factory;
 private:
    FlipperImageProcess  ( );
    ~FlipperImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image);
};