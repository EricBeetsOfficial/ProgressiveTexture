project(SDL_DX11)

set(list_libs Utils Image Texture Worker Plugins SDL3::SDL3 d3d11 d3dcompiler dxgi dxguid ${OPENGL_gl_LIBRARY})
CompileSample(sample_dx11.cpp USE_DX11 "${list_libs}")

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()