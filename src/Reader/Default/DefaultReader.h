#pragma once

#include <vector>
#include <mutex>
#include <IReader.h>

class DefaultReader : public IReader
{
 public:
    DefaultReader ( );
    ~DefaultReader ( );

 public:
    void open  (const std::string&);
    void write (const std::string&);

 public:
    bool           available ( ) const override { return _available; }
    unsigned char *pixels    ( ) const { return _pixels; }
    unsigned int   width     ( ) const { return _width; }
    unsigned int   height    ( ) const { return _height; }
    unsigned int   bpp       ( ) const { return _bpp; }

 private:
   static std::mutex _mutex;
   bool _available;
   unsigned int _width, _height, _bpp;
   unsigned char *_pixels;
};