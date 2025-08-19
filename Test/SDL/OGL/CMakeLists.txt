project(SDL_OGL)

find_package (OpenGL)

set(list_libs Utils Image Texture Worker Plugins SDL3::SDL3 ${OPENGL_gl_LIBRARY})
CompileSample(sample_ogl.cpp USE_OPENGL "${list_libs}")