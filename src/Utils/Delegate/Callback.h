#include <ExportInterface.h>
#include <Log.h>

namespace Utils
{
    namespace Delegate
    {
        typedef void(INTERFACE_API* LogCallback) (const char* str, const char* color);
        typedef void(INTERFACE_API* TextureTestCreated) (void *);

        class ExportLog
        {
         public:
            inline static LogCallback logCallback = nullptr;
        };

        class ExportTexture
        {
         public:
            inline static TextureTestCreated textureTestCreated = nullptr;
        };
    }
}