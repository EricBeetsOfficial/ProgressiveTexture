#include <ExportInterface.h>
#include <Log.h>

namespace Utils
{
    class ExportLog
    {
     public:
        typedef void(INTERFACE_API* LogCallback) (const char* str, const char* color);
        inline static LogCallback logCallback = nullptr;
    };
}