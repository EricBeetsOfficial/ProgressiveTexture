#pragma once

#include <vector>
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

 public:
   //  bool                           available ( ) const override { return _available; }
   //  std::shared_ptr<unsigned char> pixels    ( ) const { return _pixels; }
   //  unsigned int                   width     ( ) const { return _width; }
   //  unsigned int                   height    ( ) const { return _height; }
   //  unsigned int                   bpp       ( ) const { return _bpp; }

 private:
   static std::mutex _mutex;
   std::shared_ptr<Image> _image;
   // bool _available;
   // unsigned int _width, _height, _bpp;
   // std::shared_ptr<unsigned char> _pixels;
};

template<typename U = DefaultImageIO>
using FactoryImageIO = TFactoryImageIO<IImageIO, U>;