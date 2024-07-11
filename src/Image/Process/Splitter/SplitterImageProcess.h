#pragma once

#include <memory>
#include <Image.h>

class SplitterImageProcess
{
   friend class Factory;
 private:
    SplitterImageProcess  ( );
    ~SplitterImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image);
};