#include <Texture.h>
#include <Log.h>

// Texture::Texture()
// {
//     DEBUG("Ctr");
// }

// Texture::~Texture()
// {
//     DEBUG("Dtr");
// }

void* Texture::getIdPtr()
{
    int x = 0;
    int y = 0;
    int width = 128;
    int height = 128;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_glTexId);
    glBindTexture(GL_TEXTURE_2D, _glTexId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    //glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    unsigned char *pixels = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 4);
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
        {
            pixels[(i + j * width) * 4 + 0] = (i * j) % 255;
            pixels[(i + j * width) * 4 + 1] = (i * j) % 255;
            pixels[(i + j * width) * 4 + 2] = (i * j) % 255;
            pixels[(i + j * width) * 4 + 3] = 127;
        }

    glBindTexture(GL_TEXTURE_2D, _glTexId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, textureWidth, textureHeight, GL_RGBA, GL_UNSIGNED_BYTE, dataPtr);
    free(pixels);
    GLenum error = gl3wGetError();
    if (error != GL_NO_ERROR)
    {
        ERROR("texture upload error: ", error);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    INFO("texID: ", _glTexId);
    return (void*)(size_t)_glTexId;

    // INFO("");
    // return nullptr;
};
