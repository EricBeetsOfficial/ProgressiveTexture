project(Texture)

find_package (OpenGL)
set (OPENGL_gl_LIBRARY GLESv2)

include_directories(.)
include_directories(../Utils ../Utils/Log ../Utils/Pattern ../Utils/Platform)
add_library(Texture Texture.cpp)