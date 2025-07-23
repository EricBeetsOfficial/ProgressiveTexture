#include <SplitterImageProcess.h>
#include <Log.h>
#include <Block.h>
#include <Utils.h>

SplitterImageProcess::SplitterImageProcess()
{
    LOG_DEBUG("Ctr SplitterImageProcess")
}

SplitterImageProcess::~SplitterImageProcess()
{
    LOG_DEBUG("Dtr SplitterImageProcess")
}

void SplitterImageProcess::run(std::shared_ptr<Image>& image,int blockSizeX, int blockSizeY)
{
    if (!Utils::IsPowerOf2(image->width()) || !Utils::IsPowerOf2(image->height()))
    {
        LOG_ERROR("Image has no power of dimensions");
        return ;
    }
    LOG_DEBUG("Splitter block size: ", blockSizeX, blockSizeY);
    int countX = image->width() / blockSizeX;
    int countY = image->height() / blockSizeY;
    for (int y = 0; y < countY; ++y)
        for (int x = 0; x < countX; ++x)
        {
            _blocks.push_back(Factory::Create<Block>(blockSizeX, blockSizeY, x, y, image));
        }
    _width = image->width();
    _height = image->height();
    _bpp = image->bpp();
}