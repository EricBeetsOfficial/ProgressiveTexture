
#pragma once

#include <GraphicTexture.h>
#include <Log.h>

#if (SUPPORT_METAL)

class MetalTexture : public GraphicTexture
{
 public:
    MetalTexture(unsigned int width, unsigned int height, unsigned int bpp) : GraphicTexture(width, height, bpp) { LOG_WARN("Not yet implemented") }
    ~MetalTexture() { LOG_WARN("Not yet implemented") }

 public:
    void* getIdPtr() { LOG_WARN("Not yet implemented") return nullptr; }

 private:
    void _upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset) { LOG_WARN("Not yet implemented") }
    bool _check() { LOG_WARN("Not yet implemented")  return false; }
};
#endif