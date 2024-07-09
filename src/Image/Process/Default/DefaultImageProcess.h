#pragma once

#include <memory>
#include <IImageProcess.h>

class DefaultImageProcess : public IImageProcess
{
    template <typename T, typename U>
    friend class TFactory;

 private:
    DefaultImageProcess  ( );
    ~DefaultImageProcess ( );

 public:
    void run (std::shared_ptr<Image>& image,  int w, int h);
};

template<typename U = DefaultImageProcess>
using FactoryImageProcess = TFactoryImageProcess<IImageProcess, U>;