
#pragma once

#include <GraphicTexture.h>
#include <Log.h>

#if (SUPPORT_D3D12)

class D12Texture : public GraphicTexture
{
 public:
    D12Texture(unsigned int width, unsigned int height, unsigned int bpp) : GraphicTexture(width, height, bpp) { LOG_WARN("Not yet implemented") }
    ~D12Texture() { LOG_WARN("Not yet implemented") }

 public:
    void* getIdPtr() { LOG_WARN("Not yet implemented") return nullptr; }

 private:
    void _upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset) { LOG_WARN("Not yet implemented") }
    bool _check() { LOG_WARN("Not yet implemented")  return false; }
};
#endif