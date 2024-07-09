#pragma once

#include <mutex>
#include <IImageIO.h>

class DefaultImageIO : public IImageIO
{
   template <typename T, typename U>
   friend class TFactory;

 private:
    DefaultImageIO ( );
    ~DefaultImageIO ( );

 public:
    std::shared_ptr<Image> open  (const std::string&);
    void write (const std::string&);
    void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int);

 private:
   static std::mutex _mutex;
   std::shared_ptr<Image> _image;
};

template<typename U = DefaultImageIO>
using FactoryImageIO = TFactoryImageIO<IImageIO, U>;