#include <ExportInterface.h>
#include <Log.h>

#include <cstdlib>

extern "C"
{
    void INTERFACE_EXPORT INTERFACE_API ReleaseChar(char* ptr)
    {
        free(ptr);
    }
}