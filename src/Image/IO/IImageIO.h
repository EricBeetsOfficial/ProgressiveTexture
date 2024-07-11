#pragma once

#include <Factory.h>
#include <Image.h>

class IImageIO
{
   friend class Factory;

 public:
    IImageIO          ( ) { }
    virtual ~IImageIO ( ) = 0 { }

 public:
    virtual std::shared_ptr<Image> open (const std::string&) { return nullptr; }
    virtual void write (const std::string&) { }
    virtual void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int) { }
};

template <typename T = DefaultImageIO>
constexpr auto(*FactoryImageIO)() = &Factory::Create<IImageIO, T>;