// #define SUPPORT_OPENGL_UNIFIED
// // #define UNITY_WIN

// // #if defined (SUPPORT_OPENGL_UNIFIED) || defined(SUPPORT_OPENGL_CORE)
// // # if defined (UNITY_WIN)
// // #  include "gl3w/gl3w.h"
// // # elif defined (UNITY_ANDROID) || defined (UNITY_WEBGL)
// // # include <GLES2/gl2.h>
// // # elif defined (UNITY_IOS) || defined(UNITY_TVOS)
// // #	include <OpenGLES/ES2/gl.h>
// // # elif defined (UNITY_OSX)
// // #	include <OpenGL/gl3.h>
// // # elif defined (UNITY_LINUX)
// // #	define GL_GLEXT_PROTOTYPES
// // #	include <GL/gl.h>
// // # else
// // // #	error Unknown platform
// // # endif
// // #endif
// // #if defined (SUPPORT_D3D11)
// // # include <d3d11.h>
// // #endif

// // #if defined (SUPPORT_D3D12)
// // # include <d3d12.h>
// // #endif

// // #if defined (SUPPORT_METAL)
// // // Need to be included in the .mm file
// // // # import <Metal/Metal.h>
// // #endif

// // #if defined (SUPPORT_VULKAN)
// // //# include <vulkan/vulkan.h>
// // #endif


// class Context {};

// #if defined(SUPPORT_OPENGL_UNIFIED) || defined(SUPPORT_OPENGL_CORE)
// class GL : public Context {};
// #endif

// #if defined(SUPPORT_D3D11)
// class D3D11 : public Context {};
// #endif

// #if defined(SUPPORT_D3D12)
// class D3D12 : public Context {};
// #endif

// #if defined(SUPPORT_METAL)
// class Metal : public Context {};
// #endif

// #if defined(SUPPORT_VULKAN)
// class Vulkan : public Context {};
// #endif

// enum class GraphicsAPI
// {
//     OpenGL,
//     D3D11,
//     D3D12,
//     Metal,
//     Vulkan
// };

// template <GraphicsAPI API>
// class FactoryContext
// {
// public:
//     static Context* createContext() {
//         if constexpr (API == GraphicsAPI::OpenGL)
//             return new GL();
//         else if constexpr (API == GraphicsAPI::D3D11)
//             return new D3D11();
//         else if constexpr (API == GraphicsAPI::D3D12)
//             return new D3D12();
//         else if constexpr (API == GraphicsAPI::Metal)
//             return new Metal();
//         else if constexpr (API == GraphicsAPI::Vulkan)
//             return new Vulkan();
//         else
//             return nullptr; // Handle unsupported case
//     }
// };
