#include <Texture.h>
#include <Log.h>

#include <cassert>

Texture::Texture(GraphicsAPI API, unsigned int width, unsigned int height, unsigned int bpp) : _width { width }, _height { height }, _bpp { bpp }
{
    LOG_DEBUG("Ctr Texture");
    LOG_DEBUG("GraphicsAPI ", (int)API, width, height, bpp)
    if (API == GraphicsAPI::OpenGL)
        LOG_DEBUG("GraphicsAPI::OpenGL")
    else if (API == GraphicsAPI::D3D11)
        LOG_DEBUG("GraphicsAPI::D3D11")
    else if (API == GraphicsAPI::D3D12)
        LOG_DEBUG("GraphicsAPI::D3D12")
    else if (API == GraphicsAPI::Metal)
        LOG_DEBUG("GraphicsAPI::Metal")
    else if (API == GraphicsAPI::Vulkan)
        LOG_DEBUG("GraphicsAPI::Vulkan")
    else
        LOG_DEBUG("Unknown GraphicsAPI")

    glGenTextures(1, &_glTexId);
    glBindTexture(GL_TEXTURE_2D, _glTexId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    check();
}

Texture::~Texture()
{
    LOG_DEBUG("Dtr Texture");
}

void Texture::upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset)
{
    ASSERT(xOffset >= 0);
    ASSERT(yOffset >= 0);
    ASSERT(width > 0 && height > 0);
    ASSERT(xOffset + width <= _width);
    ASSERT(yOffset + height <= _height);
    ASSERT(pixels != nullptr);

    LOG_DEBUG("Texture upload", _glTexId, width, height, xOffset, yOffset);
    glBindTexture(GL_TEXTURE_2D, _glTexId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    check();
}

void Texture::check()
{
    GLenum error = gl3wGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ERROR("Texture::check: ", error);
    }
}

void* Texture::getIdPtr()
{
    return (void*)(size_t)_glTexId;
}

// void* Texture::getIdPtrTest()
// {
//     LOG_INFO("Begin getIdPtr");
//     int x = 0;
//     int y = 0;
//     int width = 128;
//     int height = 128;
//     int bpp = 3;

//     glGenTextures(1, &_glTexId);
//     glBindTexture(GL_TEXTURE_2D, _glTexId);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

//     unsigned char *pixels = (unsigned char*)malloc(sizeof(unsigned char) * width * height * bpp);
//     for (int x = 0; x < width; ++x)
//     {
//         for (int y = 0; y < height; ++y)
//         {
//             pixels[x * bpp + y * width * bpp + 0] = (x * y) % 255;
//             pixels[x * bpp + y * width * bpp + 1] = 0;
//             pixels[x * bpp + y * width * bpp + 2] = 0;
//             // pixels[x * bpp + y * width * bpp + 1] = (x * y) % 255;
//             // pixels[x * bpp + y * width * bpp + 2] = (x * y) % 255;
//             // pixels[(i + j * width) * 4 + 3] = 127;
//         }
//     }
//     glBindTexture(GL_TEXTURE_2D, _glTexId);
//     glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
//     free(pixels);
//     // glActiveTexture(GL_TEXTURE0);
// check();
//     // glGenTextures(1, &_glTexId);
//     // glBindTexture(GL_TEXTURE_2D, _glTexId);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     // // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//     // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
//     // free(pixels);
// check();

// #if false
//     //glGenerateMipmap(GL_TEXTURE_2D);
//     // glBindTexture(GL_TEXTURE_2D, 0);


//     // glBindTexture(GL_TEXTURE_2D, _glTexId);
//     glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
// check();
//     // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataPtr);
//     free(pixels);
// #endif
//     GLenum error = gl3wGetError();
//     if (error != GL_NO_ERROR)
//     {
//         LOG_ERROR("texture upload error: ", error);
//     }
//     // glBindTexture(GL_TEXTURE_2D, 0);
// check();

//     LOG_INFO("texID: ", _glTexId);

//     // return (void*)(intptr_t)_glTexId;
//     return (void*)(size_t)_glTexId;

//     // INFO("");
//     // return nullptr;
// };
