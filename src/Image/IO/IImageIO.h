#pragma once

#include <string>
#include <memory>
#include <Factory.h>

class IImageIO
{
 public:
   virtual ~IImageIO ( ) = 0;

 public:
   virtual void open  (const std::string&) { }
   virtual void write (const std::string&) { }
   virtual void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int) { }

 public:
   virtual bool                           available ( ) const { return 0; };
   virtual std::shared_ptr<unsigned char> pixels    ( ) const { return nullptr; };
   virtual unsigned int                   width     ( ) const { return 0; };
   virtual unsigned int                   height    ( ) const { return 0; };
   virtual unsigned int                   bpp       ( ) const { return 0; };

 protected:
   unsigned char * resize(int, int);
};

template<typename T, typename U>
class TFactoryImageIO : public TFactory<T, U>
{
   // Compilation assert, prefered to "std::enable_if_t<std::is_base_of_v<IImageIO, T>, bool> = true"
   // to have a clearer message
   static_assert(std::is_base_of<IImageIO, T>::value, "Primary type must derive from IImageIO");
   static_assert(std::is_base_of<IImageIO, U>::value, "Type must derive from IImageIO");
};
