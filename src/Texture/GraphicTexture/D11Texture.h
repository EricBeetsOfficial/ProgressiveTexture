
#pragma once

#include <GraphicTexture.h>
#include <Log.h>

#if (SUPPORT_D3D11)

class D11Texture : public GraphicTexture
{
 public:
    D11Texture(const void* device, unsigned int width, unsigned int height, unsigned int bpp);
    ~D11Texture();

 public:
    void* getIdPtr();
    void* getDxPtr();

 private:
    void _upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset);
    bool _check();
    int _getInternalFormat(unsigned int bpp) const;

 private:
    ID3D11ShaderResourceView* _shaderResourceView;
    ID3D11Device* _device;
    ID3D11DeviceContext* _context;
    bool _failed;
};
#endif