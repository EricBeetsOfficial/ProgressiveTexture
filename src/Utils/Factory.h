#pragma once

template <typename T, typename U>
class TFactory
{
 public:
   static T* Create()
   {
      return new U;
   }
};