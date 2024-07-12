#include <SplitterImageProcess.h>
#include <Log.h>
#include <Block.h>
#include <Utils.h>

SplitterImageProcess::SplitterImageProcess()
{
    // DEBUG("Ctr")
}

SplitterImageProcess::~SplitterImageProcess()
{
    // DEBUG("Dtr")
}

void SplitterImageProcess::run(std::shared_ptr<Image>& image,int blockSizeX, int blockSizeY)
{
    if (!Utils::IsPowerOf2(image->width()) || !Utils::IsPowerOf2(image->height()))
    {
        ERROR("Image has no power of dimensions");
        return ;
    }
    int countX = image->width() / blockSizeX;
    int countY = image->height() / blockSizeY;
    for (int y = 0; y < countY; ++y)
        for (int x = 0; x < countX; ++x)
        {
            _blocks.push_back(Factory::Create<Block>(blockSizeX, blockSizeY, x, y, image));
        }
}