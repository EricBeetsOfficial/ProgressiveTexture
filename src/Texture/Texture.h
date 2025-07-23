#pragma once

// #include <PlatformBase.h>

#include <Log.h>
#include <GraphicAPI.h>

#include <Platform3d.h>

// template <GraphicsAPI API>
class Texture
{
   friend class Factory;
 private:
    Texture  (GraphicsAPI API, unsigned int width, unsigned int height, unsigned int bpp);
//     {
//         // _context = FactoryContext<API>::createContext();
//         DEBUG(typeid(this).name());
// // #if defined(USE_OPENGL)
// //         DEBUG("OPENGL")
// // #endif
// // #ifdef USE_VULKAN
// //         DEBUG("VULKAN")
// // #endif
// // #ifdef USE_D3D
// //         DEBUG("D3D")
// // #endif

//         // if constexpr (SUPPORT_D3D11)
//         // {
//         //     DEBUG("SUPPORT_D3D11")
//         // }
//         // if constexpr (SUPPORT_D3D12)
//         // {
//         //     DEBUG("SUPPORT_D3D12")
//         // }
//         // if constexpr (SUPPORT_OPENGL_UNIFIED)
//         // {
//         //     DEBUG("SUPPORT_OPENGL_UNIFIED")
//         // }

//         // if constexpr (API == GraphicsAPI::OpenGL)
//         //     DEBUG("GraphicsAPI::OpenGL")
//         // else if constexpr (API == GraphicsAPI::D3D11)
//         //     DEBUG("GraphicsAPI::D3D11")
//         // else if constexpr (API == GraphicsAPI::D3D12)
//         //     DEBUG("GraphicsAPI::D3D12")
//         // else if constexpr (API == GraphicsAPI::Metal)
//         //     DEBUG("GraphicsAPI::Metal")
//         // else if constexpr (API == GraphicsAPI::Vulkan)
//         //     DEBUG("GraphicsAPI::Vulkan")
//         // else
//         //     DEBUG("Unknown GraphicsAPI")

//         DEBUG("GraphicsAPI ", (int)API, width, height, bpp)
//         if (API == GraphicsAPI::OpenGL)
//             DEBUG("GraphicsAPI::OpenGL")
//         else if (API == GraphicsAPI::D3D11)
//             DEBUG("GraphicsAPI::D3D11")
//         else if (API == GraphicsAPI::D3D12)
//             DEBUG("GraphicsAPI::D3D12")
//         else if (API == GraphicsAPI::Metal)
//             DEBUG("GraphicsAPI::Metal")
//         else if (API == GraphicsAPI::Vulkan)
//             DEBUG("GraphicsAPI::Vulkan")
//         else
//             DEBUG("Unknown GraphicsAPI")
//     }
    ~Texture ( );//{}

 public:
    // void* getIdPtrTest();
    void* getIdPtr();
    void upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset);

 private:
    GLuint _glTexId;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
    void check();
};