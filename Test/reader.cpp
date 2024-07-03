#include <DefaultReader.h>
#include <Log.h>

int main()
{
    IReader *reader = new DefaultReader();
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
