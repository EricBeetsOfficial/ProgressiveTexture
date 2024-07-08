#include <format>
#include <vector>
#include <algorithm>
#include <TaskWorker.h>
#include <DefaultImageIO.h>
#include <DummyImageIO.h>
#include <ThreadWorker.h>
#include <Random.h>

// struct free_delete
// {
//     void operator()(void* x)
//     {
//         DEBUG("free_delete ", (void*) x);
//         free(x);
//         x = nullptr;
//         DEBUG();
//     }
// };

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
        _texturePath {std::move(texturePath)},
        _width {0},
        _height {0},
        _bpp {0},
        ITasks(texturePath)
    {
        // Read image from disk (threaded)
        addTask([&]()
        {
            auto reader = FactoryImageIO<>::Create();
            reader->open(_texturePath);
            if (reader->available())
            {
                INFO("Loaded image from disk texture ", _texturePath);
                _width = reader->width();
                _height = reader->height();
                _bpp = reader->bpp();
                _shared = reader->pixels();
            }
            else
                ERROR(std::format("Loading texture failed: \"{}\"", _texturePath));
            delete reader;
            this_thread::sleep_for(chrono::milliseconds(3000));
            if (_shared.get() != nullptr)
                write();
            INFO("END loading ", _texturePath);
            return true;
        }, true);
#if 0
        // Resize image (threaded)
        addTask([&]()
        {
            INFO("Resize image ", _texturePath);
            // if (_pixels != nullptr)
            // {
            // }
            return true;
        }, true);
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
                INFO("Upload blocks ", _texturePath);
            count++;
            if (count >= 35000)
            {
                INFO("Upload blocks..done ", _texturePath, " ", count);
                return true;
            }
            return false;
        }, false);
#endif
    }

    ~TextureTasks()
    {
        DEBUG();
        // _pixels.clear();
    }

    void write()
    {
        auto reader = FactoryImageIO<>::Create();
        // DEBUG(_width);
        // DEBUG(_height);
        // DEBUG(_bpp);
        // reader->write("output2.jpg", (unsigned char*)&_pixels[0], _width, _height, _bpp);
        reader->write("output2.jpg", _shared.get(), _width, _height, _bpp);
        delete reader;
    }
 private:
    std::string _texturePath;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
    // std::vector<unsigned char> _pixels;

    std::shared_ptr<unsigned char> _shared;
};