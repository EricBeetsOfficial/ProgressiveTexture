#include <DefaultImageIO.h>
#include <Log.h>

int main()
{
    auto reader = FactoryImageIO<>();
    auto image = reader->open("Test/images/granular.jpg");
    if (image->available())
    {
        Utils::Log::Debug(image->width());
        Utils::Log::Debug(image->height());
        Utils::Log::Debug(image->bpp());
        reader->write("Test/images/output.jpg");
    }
    return 0;
}
