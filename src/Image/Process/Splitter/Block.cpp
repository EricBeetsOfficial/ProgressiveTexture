#include <Block.h>
#include <Log.h>
#include <Factory.h>
#include <IImageIO.h>

Block::Block(int width, int height, int countX, int countY, std::shared_ptr<Image>& image)
{
    // Pixels allocations
    unsigned char *pixels = (unsigned char*)malloc(width * height * image->bpp() * sizeof(unsigned char));
    // Create an Image for the current block
    _image = Factory::Create<Image>(width, height, image->bpp(), pixels);
    // Shortcuts computation
    int rowStepBlock = width * image->bpp();
    int rowStepImage = image->width() * image->bpp();
    int offset = countX * rowStepBlock + countY * height * rowStepImage;
    // Buffer dereferencing
    unsigned char* dst = pixels;
    unsigned char* src = image->pixels() + offset;
    // Copy image to block (line per line)
    for (int y = 0; y < height; ++y, src += rowStepImage, dst += rowStepBlock)
        memcpy(dst, src, rowStepBlock);
    // Debug: save blocks
    // FactoryImageIO<>()->write("output_" + std::to_string(countX) + "_" + std::to_string(countY) + ".jpg", _image->pixels(), _image->width(), _image->height(), _image->bpp());
}

Block::~Block()
{
    // DEBUG("Dtr")
}
