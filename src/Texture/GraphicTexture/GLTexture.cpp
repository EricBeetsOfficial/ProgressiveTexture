#include <GLTexture.h>

#if (SUPPORT_OPENGL_UNIFIED) || (SUPPORT_OPENGL_CORE)
#include <gl3w/gl3w.h>

#include <Log.h>

GLTexture::GLTexture(unsigned int width, unsigned int height, unsigned int bpp) : GraphicTexture(width, height, bpp)
{
    LOG_INFO("Ctr")
    GLuint glTexId;
    glGenTextures(1, &glTexId);
    glBindTexture(GL_TEXTURE_2D, glTexId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, bpp == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    _glTexId = (void*)(size_t)glTexId;

    _check();
}

GLTexture::~GLTexture()
{
    LOG_INFO("Dtr")
}

void* GLTexture::getIdPtr()
{
    return _glTexId;
}

void GLTexture::_upload(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int xOffset, unsigned int yOffset)
{
    LOG_DEBUG("Texture upload", _glTexId, width, height, xOffset, yOffset);
    glBindTexture(GL_TEXTURE_2D, (GLuint)(size_t)_glTexId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, width, height, _bpp == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

bool GLTexture::_check()
{
    GLenum error = gl3wGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ERROR("Texture::check: ", error);
        return false;
    }
    return true;
}
#endif