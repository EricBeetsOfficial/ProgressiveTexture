#include <format>
#include <vector>
#include <algorithm>

#include <Image.h>
#include <DefaultImageIO.h>
#include <DefaultImageProcess.h>

#include <TaskWorker.h>
#include <ThreadWorker.h>
#include <Utils.h>

class TextureTasksTest
{
 public:
    TextureTasksTest(const std::string &texturePath = "")
    {
    }

    ~TextureTasksTest()
    {
    }
};

class TextureTasks : public ITasks
{
 public:
    TextureTasks(const std::string &texturePath = "") :
        _image{nullptr},
        ITasks(texturePath)
    {
        DEBUG();
        // Read image from disk (threaded)
        addTask([&, texturePath]()
        {
            auto reader = FactoryImageIO<>::Create();
            _image = reader->open(texturePath);
            if (_image->available())
            {
                INFO("Loaded image from disk texture ", _image->name());
            }
            else
                ERROR(std::format("Loading texture failed: \"{}\"", _image->name()));
            delete reader;
            this_thread::sleep_for(chrono::milliseconds(3000));
            INFO("END loading ", _image->name());
            return true;
        }, true);
        // Resize image (threaded)
        addTask([&]()
        {
            if (_image->available())
            {
                INFO("Resize image ", _image->name());
                auto resizer = FactoryImageProcess<>::Create();
                int width = Utils::SmallestPowerOf2(_image->width());
                int height = Utils::SmallestPowerOf2(_image->height());
                resizer->run(_image, width, height);
                delete resizer;
            }
            return true;
        }, true);
        // Write resized image (threaded)
        addTask([&]()
        {
            if (_image->available())
            {
                INFO("Write Image on disk ", _image->name());
                auto reader = FactoryImageIO<>::Create();
                reader->write("output_" + Utils::FileName(_image->name()) + ".jpg", _image->pixels(), _image->width(), _image->height(), _image->bpp());
                delete reader;
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
        }, false);
#endif
    }

    ~TextureTasks()
    {
        DEBUG();
    }

 private:
    std::shared_ptr<Image> _image;
};