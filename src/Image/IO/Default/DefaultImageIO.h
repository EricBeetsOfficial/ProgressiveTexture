#pragma once

#include <mutex>
#include <IImageIO.h>

class DefaultImageIO : public IImageIO
{
   friend class Factory;
 private:
    DefaultImageIO ( );
    ~DefaultImageIO ( );

 public:
    std::shared_ptr<Image> open  (const std::string&);
    void write (const std::string&);
    void write (const std::string&, unsigned char*, unsigned int, unsigned int, unsigned int);

 private:
   static std::mutex _mutex;
   std::shared_ptr<Image> _image;
};