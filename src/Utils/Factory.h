#pragma once

template <typename T, typename U>
class TFactory
{
 public:

    virtual ~TFactory() = default;

   template <typename... Args>
   static std::shared_ptr<T> Create(Args&&... args)
   {
      // Use a deleter to allows class U has private ctr/dtr
      return std::shared_ptr<T>(new U(std::forward<Args>(args)...), [](T* ptr)
      {
         delete ptr;
      });
   }
};