#pragma once

#include <memory>
#include <type_traits>

class Factory
{
 public:
   template <typename T, typename U = T, typename... Args>
   static std::shared_ptr<T> Create(Args&&... args)
   {
      // Compilation assert, prefered to "std::enable_if_t<std::is_base_of_v<IImageIO, T>, bool> = true"
      // to have a clearer message
      static_assert(std::is_base_of<T, U>::value, "The secondary type must derive from the primary type. ");

      // Use a deleter to allows class T has private ctr/dtr
      return std::shared_ptr<T>(new U(std::forward<Args>(args)...), [](T* ptr)
      {
         delete ptr;
      });
   }
};