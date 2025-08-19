project(Texture)

find_package (OpenGL)
set (OPENGL_gl_LIBRARY GLESv2)

include_directories(. ./GraphicTexture)
include_directories(../Utils
                    ../Utils/Delegate
                    ../Utils/Log
                    ../Utils/Pattern
                    ../Utils/Platform)
add_library(Texture
        ../Utils/Platform/gl3w/gl3w.c
        GraphicTexture/GraphicTexture.cpp
        GraphicTexture/GLTexture.cpp
        GraphicTexture/D11Texture.cpp
        GraphicTexture/D12Texture.cpp
        GraphicTexture/MetalTexture.cpp
        GraphicTexture/VulkanTexture.cpp)