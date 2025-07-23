#include <Image.h>
#include <Log.h>

Image::Image(const std::string& filePath, unsigned int width, unsigned int height, unsigned int bpp, unsigned char* pixels) : _name {filePath},
                                                                                                                              _width {width},
                                                                                                                              _height {height},
                                                                                                                              _bpp {bpp},
                                                                                                                              _pixels {pixels}
{
    LOG_DEBUG("Ctr Image");
}

Image::Image(unsigned int width, unsigned int height, unsigned int bpp, unsigned char* pixels) : _width {width},
                                                                                                 _height {height},
                                                                                                 _bpp {bpp},
                                                                                                 _pixels {pixels}

{
    LOG_DEBUG("Dtr Image")
}

Image::Image(const Image &other)
{
    LOG_ERROR("Ctr Image copy");
}

Image::~Image()
{
    // DEBUG("Dtr ", _width, " ", _height);
    free(_pixels);
}