#pragma once

#include <Platform3d.h>
#include <Factory.h>
#include <GraphicAPI.h>

class GraphicTexture
{
 public:
    GraphicTexture(unsigned int width, unsigned int height, unsigned int bpp);
    virtual ~GraphicTexture();
 public:
    virtual void* getIdPtr() = 0;
    virtual void* getDxPtr() { return nullptr; }    // Used for SDL
    void upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset);

 private:
    virtual void _upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset) = 0;
    virtual bool _check() = 0;

 protected:
    unsigned int _width;
    unsigned int _height;
    unsigned int _bpp;
    void* _glTexId;

 public:
    static std::shared_ptr<GraphicTexture> createGraphicTexture(const GraphicsAPI api, unsigned int width, unsigned int height, unsigned int bpp, const void* device);
//     {
// #if (SUPPORT_OPENGL_UNIFIED) || (SUPPORT_OPENGL_CORE)
//     if (api == GraphicsAPI::OpenGL)
//         return Factory::Create<GLTexture>(width, height, bpp);
//         // _graphicTexture = new GLTexture(0, 0, 0);
// #endif
// #if (SUPPORT_D3D11)
//     if (api == GraphicsAPI::D3D11)
//         return Factory::Create<D11Texture>(width, height, bpp);
//         // _graphicTexture = new D11Texture(0, 0, 0);
// #elif (SUPPORT_D3D12)
//     if (api == GraphicsAPI::D3D12)
//         return Factory::Create<D12Texture>(width, height, bpp);
//         // _graphicTexture = new D12Texture(0, 0, 0);
// #endif
// #if (SUPPORT_METAL)
//     if (api == GraphicsAPI::Metal)
//         LOG_WARN("Metal")
// #endif
// #if (SUPPORT_VULKAN)
//     if (api == GraphicsAPI::Vulkan)
//         LOG_WARN("Vulkan")
// #endif
//     }
};