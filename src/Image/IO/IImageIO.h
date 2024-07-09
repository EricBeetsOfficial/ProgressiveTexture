#pragma once

#include <Factory.h>
#include <Image.h>

class IImageIO
{
 public:
    IImageIO() {}
    virtual ~IImageIO ( ) = 0 { }

 public:
    virtual std::shared_ptr<Image> open  (const std::string&) { return nullptr; }
    virtual void write (const std::string&) { }
    virtual void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int) { }
};

template<typename T, typename U>
class TFactoryImageIO : public TFactory<T, U>
{
   // Compilation assert, prefered to "std::enable_if_t<std::is_base_of_v<IImageIO, T>, bool> = true"
   // to have a clearer message
   static_assert(std::is_base_of<IImageIO, T>::value, "Primary type must derive from IImageIO");
   static_assert(std::is_base_of<IImageIO, U>::value, "Type must derive from IImageIO");
};