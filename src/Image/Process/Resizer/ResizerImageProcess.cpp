#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize2.h>

#include <ResizerImageProcess.h>
#include <Log.h>

ResizerImageProcess::ResizerImageProcess()
{
    DEBUG("Ctr")
}

ResizerImageProcess::~ResizerImageProcess()
{
    DEBUG("Dtr")
}

void ResizerImageProcess::run(std::shared_ptr<Image>& image,  int w, int h)
{
    unsigned char* resized = (unsigned char*)malloc(sizeof(unsigned char) * w * h * image->bpp());
    stbir_resize_uint8_linear(image->pixels(), image->width(), image->height(), 0, resized, w, h, 0, (stbir_pixel_layout)image->bpp());
    auto resizedImage = Factory::Create<Image>(image->name(), w, h, image->bpp(), resized);
    image = resizedImage;
}
