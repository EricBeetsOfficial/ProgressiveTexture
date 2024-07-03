#pragma once

#include <string>

class IReader
{
 public:
    virtual ~IReader ( ) = 0;

 public:
    virtual void open  (const std::string&) = 0;
    virtual void write (const std::string&) = 0;

 public:
    virtual bool           available ( ) const = 0;
    virtual unsigned char *pixels    ( ) const = 0;
    virtual unsigned int   width     ( ) const = 0;
    virtual unsigned int   height    ( ) const = 0;
    virtual unsigned int   bpp       ( ) const = 0;

 protected:
    unsigned char * resize(int, int);
};