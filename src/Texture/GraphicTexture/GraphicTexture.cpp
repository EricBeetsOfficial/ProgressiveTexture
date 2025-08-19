#include <GraphicTexture.h>

#include <GLTexture.h>
#include <D11Texture.h>
#include <D12Texture.h>
#include <MetalTexture.h>
#include <VulkanTexture.h>

std::shared_ptr<GraphicTexture> GraphicTexture::createGraphicTexture(const GraphicsAPI api, unsigned int width, unsigned int height, unsigned int bpp, const void* device)
{
#if (SUPPORT_OPENGL_UNIFIED) || (SUPPORT_OPENGL_CORE)
    if (api == GraphicsAPI::OpenGL)
        return Factory::Create<GLTexture>(width, height, bpp);
#endif
#if (SUPPORT_D3D11)
    if (api == GraphicsAPI::D3D11)
        return Factory::Create<D11Texture>(device, width, height, bpp);
#elif (SUPPORT_D3D12)
    if (api == GraphicsAPI::D3D12)
        return Factory::Create<D12Texture>(width, height, bpp);
#endif
#if (SUPPORT_METAL)
    if (api == GraphicsAPI::Metal)
        LOG_WARN("Metal")
#endif
#if (SUPPORT_VULKAN)
    if (api == GraphicsAPI::Vulkan)
        LOG_WARN("Vulkan")
#endif
    return nullptr;
}

GraphicTexture::GraphicTexture(unsigned int width, unsigned int height, unsigned int bpp) : _width { width }, _height { height }, _bpp { bpp }
{
}

GraphicTexture::~GraphicTexture()
{
}

void GraphicTexture::upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset)
{
    ASSERT(xOffset >= 0);
    ASSERT(yOffset >= 0);
    ASSERT(width > 0 && height > 0);
    ASSERT(xOffset + width <= _width);
    ASSERT(yOffset + height <= _height);
    ASSERT(pixels != nullptr);

    _upload(pixels, width, height, xOffset, yOffset);
    _check();
}