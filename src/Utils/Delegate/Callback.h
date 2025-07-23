#pragma once

#include <ExportInterface.h>
#include <Log.h>

namespace Utils
{
    #pragma pack(push, 1)
    namespace Delegate
    {
        struct TextureParameter
        {
            void* texturePtr;
            void* texId;
            char guid[64];
        };

        typedef void(INTERFACE_API* LogCallback) (const char* str, const char* color);
        typedef void(INTERFACE_API* TextureCreated) (TextureParameter *);

        class ExportLog
        {
         public:
            inline static LogCallback logCallback = nullptr;
        };

        class ExportTexture
        {
         public:
            inline static TextureCreated textureCreated = nullptr;
        };
    }
    #pragma pack(pop)
}
