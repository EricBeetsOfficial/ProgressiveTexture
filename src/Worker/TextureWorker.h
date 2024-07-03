#include <format>
#include <vector>
#include <algorithm>
#include <TaskWorker.h>
#include <DefaultReader.h>
#include <ThreadWorker.h>

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
            IReader *reader = new DefaultReader();
            reader->open(_texturePath);
            if (reader->available())
            {
                INFO("Loaded image from disk texture ", _texturePath);
                _width = reader->width();
                _height = reader->height();
                _bpp = reader->bpp();
                // Copy pixels, Reader free data
                auto size = _width * _height * _bpp;
                _pixels.reserve(size);
                std::copy(reader->pixels(), reader->pixels() + size, back_inserter(_pixels));
            }
            else
                ERROR(std::format("Loading texture failed: \"{}\"", _texturePath));
            delete reader;
            this_thread::sleep_for(chrono::milliseconds(3000));
            write();
            INFO("END loading");
            return true;
        }, true);
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
        // Upload blocks (non-threaded)
        addTask([&]()
        {
            static int count = 0;
            if (!count)
                INFO("Upload blocks ", _texturePath);
            count++;
            if (count >= 100000)
            {
                INFO("Upload blocks..done ", _texturePath);
                return true;
            }
            return false;
        }, false);
    }

    ~TextureTasks()
    {
        _pixels.clear();
    }

    void write()
    {
        IReader *reader = new DefaultReader();
        DEBUG(_width);
        DEBUG(_height);
        DEBUG(_bpp);
        reader->write("output2.jpg", (unsigned char*)&_pixels[0], _width, _height, _bpp);
        delete reader;
    }
 private:
    std::string _texturePath;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
    std::vector<unsigned char> _pixels;
};