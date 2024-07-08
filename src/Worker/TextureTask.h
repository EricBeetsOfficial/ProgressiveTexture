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
    {}
};

class TextureTasks : public ITasks
{
 public:
    TextureTasks(const std::string &texturePath = "") :
        // _texturePath {std::move(texturePath)},
        // _width {0},
        // _height {0},
        // _bpp {0},
        _image{std::move(texturePath), 0 , 0, 0, nullptr},
        ITasks(texturePath)
    {
        // Read image from disk (threaded)
        addTask([&]()
        {
            auto reader = FactoryImageIO<>::Create();
            reader->open(_image._texturePath);
            if (reader->available())
            {
                INFO("Loaded image from disk texture ", _image._texturePath);
                _image.width = reader->width();
                _image.height = reader->height();
                _image.bpp = reader->bpp();
                _image._pixels = reader->pixels();
            }
            else
                ERROR(std::format("Loading texture failed: \"{}\"", _image._texturePath));
            delete reader;
            this_thread::sleep_for(chrono::milliseconds(3000));
            INFO("END loading ", _image._texturePath);
            return true;
        }, true);
        // Resize image (threaded)
        addTask([&]()
        {
            if (_image._pixels.get() != nullptr)
            {
                INFO("Resize image ", _image._texturePath);
                auto resizer = FactoryImageProcess<>::Create();
                int width = Utils::SmallestPowerOf2(_image.width);
                int height = Utils::SmallestPowerOf2(_image.height);
                resizer->run(_image, width, height);
                delete resizer;
            }
            return true;
        }, true);
        // Write resized image (threaded)
        addTask([&]()
        {
            if (_image._pixels.get() != nullptr)
            {
                INFO("Write Image on disk ", _image._texturePath);
                auto reader = FactoryImageIO<>::Create();
                reader->write("output_" + Utils::FileName(_image._texturePath) + ".jpg", _image._pixels.get(), _image.width, _image.height, _image.bpp);
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
                INFO("Upload blocks ", _image._texturePath);
            count++;
            if (count >= 35000)
            {
                INFO("Upload blocks..done ", _image._texturePath, " ", count);
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
    Image _image;
};