#include <TextureTask.h>

#include <vector>
#include <algorithm>

#include <Log.h>
#include <DefaultImageIO.h>
#include <DummyImageIO.h>
#include <ResizerImageProcess.h>
#include <FlipperImageProcess.h>

#include <GraphicTexture.h>

#include <ThreadWorker.h>
#include <Utils.h>
#include <Block.h>

TextureTasks::TextureTasks(const GraphicsAPI api, const void* device, const std::string &texturePath, const Utils::Delegate::TextureParameter* textureParameter) : _image{nullptr},
                                                                                                                                                                    ITaskWorker(texturePath)
{
    LOG_DEBUG("Ctr TextureTasks")
    LOG_DEBUG("GraphicsAPI ", (int)api)
    LOG_DEBUG("GUID ", textureParameter->guid)
    _textureParameter = new Utils::Delegate::TextureParameter(*textureParameter);
    LOG_DEBUG("GUID ", _textureParameter->guid)

    // Read image from disk (threaded)
    addTask([&, texturePath]()
    {
        LOG_DEBUG("Read image", texturePath)
        auto reader = FactoryImageIO<>();
        _image = reader->open(texturePath);
        if ((_image != nullptr) && _image->available())
        {
            LOG_INFO("Loaded image from disk texture ", _image->name())
        }
        else
            LOG_ERROR("Loading texture failed: ", texturePath)
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        LOG_DEBUG("END loading ", texturePath)
        return true;
    }, true);
    // Resize image (threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            LOG_DEBUG("Resize image ", _image->name(), _image->width(), _image->height(), _image->bpp())
            auto resizer = Factory::Create<ResizerImageProcess>();
            int width = Utils::SmallestPowerOf2(_image->width());
            int height = Utils::SmallestPowerOf2(_image->height());
            resizer->run(_image, width, height);
            LOG_INFO("Resize image to", _image->width(), _image->height(), _image->bpp())

            if (_textureParameter->yFlip)
            {
                LOG_DEBUG("Flipper image")
                auto flipper = Factory::Create<FlipperImageProcess>();
                flipper->run(_image);
            }
        }
        else LOG_ERROR("Resize failed", "Image is not available")
        return true;
    }, true);
#if 1
    // Split in blocks (threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            LOG_INFO("Split in blocks")
            _splitter = Factory::Create<SplitterImageProcess>();
            _splitter->run(_image, 128, 128);
            // Release the image
        }
        else LOG_ERROR("Split blocks failed", "Image is not available")
        _image.reset();
        return true;
    }, true);
#endif
#if 1
    // Create empty texture (non-threaded)
    addTask([&, api, device]()
    {
        if (_splitter != nullptr)
        {
            LOG_INFO("Create graphic texture ")
            LOG_DEBUG("GraphicsAPI ", (int)api)
            LOG_DEBUG("Texture size", _splitter->width(), _splitter->height(), _splitter->bpp())
            _texture = GraphicTexture::createGraphicTexture(api, _splitter->width(), _splitter->height(), _splitter->bpp(), device);
            if (Utils::Callback::ExportTexture::textureCreated != nullptr)
            {
                LOG_INFO("Send Texture ID ")
                _textureParameter->texId = _texture->getIdPtr();
                _textureParameter->dxPtr = _texture->getDxPtr();
                Utils::Callback::ExportTexture::textureCreated(_textureParameter);
            }
            else
                LOG_INFO("Delegate::textureCreated is NULL")
        }
        else LOG_ERROR("Create graphic texture failed", "Splitter is not available")
        return true;
    }, false);
#endif
#if 1
    // Upload blocks (non-threaded)
    addTask([&]()
    {
        if (_splitter != nullptr && !_splitter->isEmpty())
        {
            auto block = _splitter->getBlock();
            auto image = block->get();
            _texture->upload(image->pixels(), image->width(), image->height(), block->xOffset(), block->yOffset());
            return false;
        }
        _splitter.reset();
        return true;
    }, false);
#endif
}

TextureTasks::~TextureTasks()
{
    LOG_DEBUG("Dtr TextureTasks")
}