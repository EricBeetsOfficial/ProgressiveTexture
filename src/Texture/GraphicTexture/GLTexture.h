#pragma once

#include <GraphicTexture.h>

#if (SUPPORT_OPENGL_UNIFIED) || (SUPPORT_OPENGL_CORE)

class GLTexture : public GraphicTexture
{
 public:
    GLTexture(unsigned int width, unsigned int height, unsigned int bpp);
    ~GLTexture();

 public:
    void* getIdPtr();

 private:
    void _upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset);
    bool _check();
};
#endif