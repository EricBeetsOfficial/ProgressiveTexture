#pragma once

#include <ExportInterface.h>
#include <Log.h>
#include <Delegate.h>

namespace Utils
{
    namespace Callback
    {
        typedef void(INTERFACE_API* LogCallback) (const char* str, const char* color);
        typedef void(INTERFACE_API* TextureCreated) (Delegate::TextureParameter *);

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
}
