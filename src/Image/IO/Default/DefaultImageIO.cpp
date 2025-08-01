#include <mutex>
#include <DefaultImageIO.h>
#include <Log.h>
// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

// Because stb_image is not thread safe
std::mutex DefaultImageIO::_mutex;

DefaultImageIO::DefaultImageIO()
{
    // DEBUG("Ctr");
}

DefaultImageIO::~DefaultImageIO()
{
    // DEBUG("Dtr");
}

std::shared_ptr<Image> DefaultImageIO::open(const std::string& fileName)
{
    std::unique_lock<std::mutex> lock(_mutex);
    int w, h, b;
    unsigned char* pixels = stbi_load(fileName.c_str(), &w, &h, &b, 0);
    return Factory::Create<Image>(fileName, w, h, b, pixels);
}

void DefaultImageIO::write(const std::string& fileName)
{
    LOG_DEBUG();
    stbi_write_jpg(fileName.c_str(), _image->width(), _image->height(), _image->bpp(), _image->pixels(), _image->width() * _image->bpp());
}

void DefaultImageIO::write(const std::string& fileName, unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp)
{
    LOG_DEBUG("Write image to", fileName);
    stbi_write_jpg(fileName.c_str(), width, height, bpp, pixels, width * bpp);
}