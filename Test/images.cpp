#include <DefaultImageIO.h>
#include <Log.h>

int main()
{
    // IImageIO *reader = new DefaultImageIO();
    IImageIO *reader = FactoryImageIO<>::Create();
    reader->open("Test/images/granular.jpg");
    if (reader->available())
    {
        Utils::Log::Debug(reader->width());
        Utils::Log::Debug(reader->height());
        Utils::Log::Debug(reader->bpp());
        reader->write("Test/images/output.jpg");
    }
    delete reader;
    return 0;
}
