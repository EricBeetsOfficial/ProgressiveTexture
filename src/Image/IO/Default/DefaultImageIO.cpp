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

DefaultImageIO::DefaultImageIO() : _pixels (nullptr)
{
    // DEBUG("Ctr");
}

DefaultImageIO::~DefaultImageIO()
{
    // DEBUG("Dtr ", (void*) _pixels.get());
}

void DefaultImageIO::open(const std::string& fileName)
{
    std::unique_lock<std::mutex> lock(_mutex);
    int w, h, b;
    unsigned char *pixels = stbi_load(fileName.c_str(), &w, &h, &b, 0);
    _pixels = std::shared_ptr<unsigned char>(pixels, [](unsigned char* pixels)
    {
        // DEBUG()
        stbi_image_free(pixels);
        pixels = nullptr;
    });

    _available = _pixels != NULL;
    _width = w;
    _height = h;
    _bpp = b;
}

void DefaultImageIO::write(const std::string& fileName)
{
    stbi_write_jpg(fileName.c_str(), width(), height(), bpp(), pixels().get(), width() * bpp());
}

void DefaultImageIO::write(const std::string& fileName, unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp)
{
    stbi_write_jpg(fileName.c_str(), width, height, bpp, pixels, width * bpp);
}