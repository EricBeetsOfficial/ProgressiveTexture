#include <RenderAPI.h>
#include <PlatformBase.h>
#include <IUnityGraphics.h>

#include <Log.h>

RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType)
{
#if SUPPORT_D3D11
    if (apiType == UnityGfxRenderer::kUnityGfxRendererD3D11)
    {
        WARN("SUPPORT_D3D11");
        extern RenderAPI* CreateRenderAPI_D3D11(UnityGfxRenderer apiType);
        return CreateRenderAPI_D3D11(apiType);
    }
#endif // if SUPPORT_D3D11

#if SUPPORT_D3D12
    if (apiType == UnityGfxRenderer::kUnityGfxRendererD3D12)
    {
        WARN("SUPPORT_D3D12");
        extern RenderAPI* CreateRenderAPI_D3D12(UnityGfxRenderer apiType);
        return CreateRenderAPI_D3D12(apiType);
    }
#endif // if SUPPORT_D3D12

#if SUPPORT_OPENGL_UNIFIED
    if (apiType == UnityGfxRenderer::kUnityGfxRendererOpenGLCore || apiType == UnityGfxRenderer::kUnityGfxRendererOpenGLES30)
    {
        WARN("SUPPORT_OPENGL_UNIFIED");
        extern RenderAPI* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
        return CreateRenderAPI_OpenGLCoreES(apiType);
    }
#endif // if SUPPORT_OPENGL_UNIFIED

#if SUPPORT_METAL
    if (apiType == UnityGfxRenderer::kUnityGfxRendererMetal)
    {
        WARN("SUPPORT_METAL");
        extern RenderAPI* CreateRenderAPI_Metal(UnityGfxRenderer apiType);
        return CreateRenderAPI_Metal(apiType);
    }
#endif // if SUPPORT_METAL

#if SUPPORT_VULKAN
    if (apiType == kUnityGfxRendererVulkan)
    {
        WARN("SUPPORT_VULKAN");
        // extern RenderAPI* CreateRenderAPI_Vulkan();
        // return CreateRenderAPI_Vulkan();
    }
#endif // if SUPPORT_VULKAN
    ERROR("Unknown or unsupported graphics API ", apiType);
    return NULL;
}
