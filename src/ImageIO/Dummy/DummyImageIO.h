#pragma once

#include <IImageIO.h>

class DummyImageIO : public IImageIO
{
 public:
    DummyImageIO ( ) {}
    ~DummyImageIO ( ){}

 public:
    void open  (const std::string&) {}
    void write (const std::string&) {}
    void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int) {}

 public:
    bool           available ( ) const override { return false; }
    unsigned char *pixels    ( ) const { return nullptr; }
    unsigned int   width     ( ) const { return 0; }
    unsigned int   height    ( ) const { return 0; }
    unsigned int   bpp       ( ) const { return 0; }
};