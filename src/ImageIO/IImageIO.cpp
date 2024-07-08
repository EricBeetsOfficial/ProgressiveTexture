#include <IImageIO.h>
#include <Log.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb/stb_image_resize2.h>

IImageIO::~IImageIO()
{
    // DEBUG("Dtr");
}

unsigned char *IImageIO::resize(int w, int h)
{
    // DEBUG("resize");
    unsigned char* resized = (unsigned char*)malloc(sizeof(unsigned char) * w * h * bpp());
    stbir_resize_uint8_linear(pixels(), width(), height(), 0, resized, w, h, 0, (stbir_pixel_layout)bpp());
    return resized;
}
