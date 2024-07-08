#include <mutex>
#include <DefaultImageIO.h>
#include <Log.h>
// https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

std::mutex DefaultImageIO::_mutex;

DefaultImageIO::DefaultImageIO() : _pixels (nullptr)
{
    // DEBUG("Ctr");
}

DefaultImageIO::~DefaultImageIO()
{
    // DEBUG("Dtr");
    stbi_image_free(_pixels);
}

void DefaultImageIO::open(const std::string& fileName)
{
    std::unique_lock<std::mutex> lock(_mutex);
    // DEBUG(fileName);
    int w, h, b;
    _pixels = stbi_load(fileName.c_str(), &w, &h, &b, 0);
    _available = _pixels != NULL;
    _width = w;
    _height = h;
    _bpp = b;
    // unsigned char *resized = resize(512, 512);
    // stbi_image_free(_pixels);
    // _pixels = std::move(resized);
    // _width = 512;
    // _height = 512;
}

void DefaultImageIO::write(const std::string& fileName)
{
    stbi_write_jpg(fileName.c_str(), width(), height(), bpp(), pixels(), width() * bpp());
}

void DefaultImageIO::write(const std::string& fileName, unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp)
{
    stbi_write_jpg(fileName.c_str(), width, height, bpp, pixels, width * bpp);
}