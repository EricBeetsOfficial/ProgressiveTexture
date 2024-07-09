#pragma once

#include <Image.h>

class IImageProcess : public ImageFactory
{
 public:
   virtual ~IImageProcess ( ) = 0 { }

 public:
   virtual void run (std::shared_ptr<Image>& image, int w, int h) { }
};

template<typename T, typename U>
class TFactoryImageProcess : public TFactory<T, U>
{
   // Compilation assert, prefered to "std::enable_if_t<std::is_base_of_v<IImageIO, T>, bool> = true"
   // to have a clearer message
   static_assert(std::is_base_of<IImageProcess, T>::value, "Primary type must derive from IImageProcess");
   static_assert(std::is_base_of<IImageProcess, U>::value, "Type must derive from IImageIO");
};
