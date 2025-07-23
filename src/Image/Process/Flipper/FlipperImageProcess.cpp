#include <FlipperImageProcess.h>
#include <Log.h>
#include <IImageIO.h>

FlipperImageProcess::FlipperImageProcess()
{
    LOG_DEBUG("Ctr FlipperImageProcess")
}

FlipperImageProcess::~FlipperImageProcess()
{
    LOG_DEBUG("Dtr FlipperImageProcess")
}

void FlipperImageProcess::run(std::shared_ptr<Image>& image)
{
    unsigned char *pixels = (unsigned char*)malloc(image->width() * image->height() * image->bpp() * sizeof(unsigned char));

    int rowStepImage = image->width() * image->bpp();
    unsigned char* dst = pixels + rowStepImage * (image->height() - 1);
    unsigned char* src = image->pixels();
    for (int y = 0; y < image->height(); ++y)
    {
        dst = pixels + rowStepImage * (image->height() - 1 - y);
        src += rowStepImage;
        memcpy(dst, src, rowStepImage);
    }
    auto flippedImage = Factory::Create<Image>(image->name(), image->width(), image->height(), image->bpp(), pixels);
    image = flippedImage;
    // Debug: save flipped
    // FactoryImageIO<>()->write("flipper.jpg", image->pixels(), image->width(), image->height(), image->bpp());
}