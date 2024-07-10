#include <TextureTask.h>

#include <format>
#include <vector>
#include <algorithm>

#include <Log.h>
#include <DefaultImageIO.h>
#include <DummyImageIO.h>
#include <DefaultImageProcess.h>

#include <ThreadWorker.h>
#include <Utils.h>

TextureTasks::TextureTasks(const std::string &texturePath) : _image{nullptr},
                                                             ITaskWorker(texturePath)
{
    // DEBUG();
    // Read image from disk (threaded)
    addTask([&, texturePath]()
    {
        auto reader = FactoryImageIO<>::Create();
        _image = reader->open(texturePath);
        if ((_image != nullptr) && _image->available())
        {
            INFO("Loaded image from disk texture ", _image->name());
        }
        else
            ERROR(std::format("Loading texture failed: \"{}\"", texturePath));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        INFO("END loading ", texturePath);
        return true;
    }, true);
    // Resize image (threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            INFO("Resize image ", _image->name());
            auto resizer = FactoryImageProcess<>::Create();
            int width = Utils::SmallestPowerOf2(_image->width());
            int height = Utils::SmallestPowerOf2(_image->height());
            resizer->run(_image, width, height);
        }
        return true;
    }, true);
    // Write resized image (threaded)
    addTask([&]()
    {
        if ((_image != nullptr) && _image->available())
        {
            INFO("Write Image on disk ", _image->name());
            auto reader = FactoryImageIO<>::Create();
            reader->write("output_" + Utils::FileName(_image->name()) + ".jpg", _image->pixels(), _image->width(), _image->height(), _image->bpp());
        }
        return true;
    }, true);
#if 0
    // Split in blocks (threaded)
    addTask([&]()
    {
        INFO("Split in blocks ", _texturePath);
        return true;
    }, true);
    // Create empty texture (non-threaded)
    addTask([&]()
    {
        INFO("Create texture ", _texturePath);
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

TextureTasksTest::TextureTasksTest(const std::string &texturePath)
{
}

TextureTasksTest::~TextureTasksTest()
{
}