#include <TextureTask.h>

#include <format>
#include <vector>
#include <algorithm>

#include <Log.h>
#include <DefaultImageIO.h>
#include <DummyImageIO.h>
#include <ResizerImageProcess.h>
#include <Texture.h>
#include <ThreadWorker.h>
#include <Utils.h>
#include <Texture.h>
#include <Callback.h>

TextureTasks::TextureTasks(const GraphicsAPI api, const std::string &texturePath) : _image{nullptr},
                                                                                    ITaskWorker(texturePath)
{
    _texture = Factory::Create<Texture>(api);
    // DEBUG();
    // Read image from disk (threaded)
    addTask([&, texturePath]()
    {
        auto reader = FactoryImageIO<>();
        _image = reader->open(texturePath);
        if ((_image != nullptr) && _image->available())
        {
            INFO("Loaded image from disk texture ", _image->name());
        }
        else
            ERROR(std::format("Loading texture failed: \"{}\"", texturePath));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        INFO("END loading ", texturePath);
        return true;
    }, true);
    // Resize image (threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            INFO("Resize image ", _image->name());
            auto resizer = Factory::Create<ResizerImageProcess>();
            int width = Utils::SmallestPowerOf2(_image->width());
            int height = Utils::SmallestPowerOf2(_image->height());
            resizer->run(_image, width, height);
        }
        return true;
    }, true);
#if !NDEBUG
    // Debug: Write resized image (threaded)
    addTask([&]()
    {
        // if ((_image != nullptr) && _image->available())
        // {
        //     INFO("Write Image on disk ", _image->name());
        //     FactoryImageIO<>()->write("output_" + Utils::FileName(_image->name()) + ".jpg", _image->pixels(), _image->width(), _image->height(), _image->bpp());
        // }
        return true;
    }, true);
#endif
#if 1
    // Split in blocks (threaded)
    addTask([&, texturePath]()
    {
        INFO("Split in blocks ", texturePath);
        _splitter = Factory::Create<SplitterImageProcess>();
        _splitter->run(_image);
        // Release the image
        _image.reset();
        return true;
    }, true);
#endif
#if 0
    // Create empty texture (non-threaded)
    addTask([&, texturePath]()
    {
        INFO("Create texture ", texturePath);
        // auto texture0 = Factory::Create<Texture<GraphicsAPI::OpenGL>>();
        // auto texture0 = Factory::Create<Texture>();
        _texture = Factory::Create<Texture>(api);
        if (Utils::Delegate::ExportTexture::textureTestCreated != nullptr)
        {
            INFO("Send Texture ID ", texturePath);
            Utils::Delegate::ExportTexture::textureTestCreated(_texture->getIdPtr());
        }
        else
            INFO("Delegate::textureTestCreated is NULL");

        return true;
    }, false);
#endif
#if 1
    // Upload blocks (non-threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            static int count = 0;
            if (!count)
                INFO("Upload blocks ", _image->name());
            count++;
            if (count >= 35000)
            {
                INFO("Upload blocks..done ", _image->name(), " ", count);
                return true;
            }
            return false;
        }
        return true;
    }, false);
#endif
}

TextureTasks::~TextureTasks()
{
    // DEBUG();
}

void* TextureTasks::getIdPtr()
{
    return _texture->getIdPtr();
};


TextureTasksTest::TextureTasksTest(const GraphicsAPI api, const std::string &texturePath)
{
}

TextureTasksTest::~TextureTasksTest()
{
}