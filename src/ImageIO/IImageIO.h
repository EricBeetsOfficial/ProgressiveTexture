#pragma once

#include <string>
#include <Factory.h>

class IImageIO
{
 public:
    virtual ~IImageIO ( ) = 0;

 public:
    virtual void open  (const std::string&) = 0;
    virtual void write (const std::string&) = 0;
    virtual void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int) = 0;


 public:
    virtual bool           available ( ) const = 0;
    virtual unsigned char *pixels    ( ) const = 0;
    virtual unsigned int   width     ( ) const = 0;
    virtual unsigned int   height    ( ) const = 0;
    virtual unsigned int   bpp       ( ) const = 0;

 protected:
    unsigned char * resize(int, int);
};

template<typename T, typename U>
class TFactoryImageIO : public TFactory<T, U>
{
   // Compilation assert
   static_assert(std::is_base_of<IImageIO, T>::value, "Primary type must derive from IImageIO");
   static_assert(std::is_base_of<IImageIO, U>::value, "Type must derive from IImageIO");
};
