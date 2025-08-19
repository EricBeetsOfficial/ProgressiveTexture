#include <D11Texture.h>
#if (SUPPORT_D3D11)

#include <Log.h>

// #include <RenderAPI.h>

// extern RenderAPI* s_CurrentAPI;

D11Texture::D11Texture(const void* device, unsigned int width, unsigned int height, unsigned int bpp) : GraphicTexture(width, height, bpp)
{
    LOG_INFO("Ctr")

    // _device = (ID3D11Device*)s_CurrentAPI->getDevice();
    _device = (ID3D11Device*)device;
    _device->GetImmediateContext(&_context);
    /////////////////
    ID3D11Texture2D* _tex2D = NULL;
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = desc.ArraySize = 1;
    desc.Format = (DXGI_FORMAT)_getInternalFormat(bpp);
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;

    HRESULT hr = _device->CreateTexture2D(&desc, NULL, &_tex2D);
    if (FAILED(hr)) {
        LOG_ERROR("Error create texture");
        _failed = true;
        return;
    }

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.Format = desc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    HRESULT hrr = _device->CreateShaderResourceView(_tex2D, &shaderResourceViewDesc, &_shaderResourceView);
    if (FAILED(hrr)) {
        LOG_ERROR("Error create resource view");
        _tex2D->Release();
        _failed = true;
        return;
    }
    _failed = false;
    _glTexId = _tex2D;
    _check();
}

D11Texture::~D11Texture()
{
    LOG_INFO("Dtr")
}

void* D11Texture::getIdPtr()
{
    return _glTexId;
}

void* D11Texture::getDxPtr()
{
    return _shaderResourceView;
}

int D11Texture::_getInternalFormat(unsigned int bpp) const
{
    return DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
}

void D11Texture::_upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset)
{
    if (_failed) {
        LOG_ERROR("Upload Texture D3D11 failed cause texture creation failed");
        return;
    }
    D3D11_BOX destRegion;
    destRegion.left = xOffset;
    destRegion.right = xOffset + width;
    destRegion.top = yOffset;
    destRegion.bottom = yOffset + height;
    destRegion.front = 0;
    destRegion.back = 1;

    int rowPitch = width * _bpp * sizeof(unsigned char);

    _device->GetImmediateContext(&_context);
    _context->UpdateSubresource((ID3D11Resource*)_glTexId, 0, &destRegion, pixels, rowPitch, width * height * _bpp);
}

bool D11Texture::_check()
{
    return true;
}
#endif