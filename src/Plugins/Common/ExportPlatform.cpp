#include <IUnityInterface.h>
#include <PlatformBase.h>
#include <RenderAPI.h>

#include <Log.h>
#include <Version.h>

#include <list>
#include <string>
#include <regex>

extern RenderAPI* s_CurrentAPI;

extern "C"
{
    const UNITY_INTERFACE_EXPORT char* UNITY_INTERFACE_API Version()
    {
        return VERSION;
    }

    const UNITY_INTERFACE_EXPORT char* UNITY_INTERFACE_API BuildType()
    {
#if NDEBUG
        return "Release";
#else
        return "Debug";
#endif
    }

    const UNITY_INTERFACE_EXPORT char* UNITY_INTERFACE_API SupportedContext()
    {
        std::string supportedContext = "";
#if SUPPORT_D3D11
        supportedContext += " D3D11 ";
#endif
#if SUPPORT_D3D12
        supportedContext += " D3D12 ";
#endif
#if SUPPORT_OPENGL_UNIFIED
        supportedContext += " OpenGL ";
#endif
#if SUPPORT_METAL
        supportedContext += " Metal ";
#endif
#if SUPPORT_VULKAN
        supportedContext += " Vulkan";
#endif
        supportedContext.erase(0, 1);
        supportedContext.erase(supportedContext.size() - 1);
        supportedContext = std::regex_replace(supportedContext, std::regex("  "), " ");
        supportedContext = std::regex_replace(supportedContext, std::regex(" "), ", ");

        char* str = (char*)malloc(sizeof(char) * supportedContext.size() + 1);
        strcpy(str, supportedContext.c_str());
        *(str + supportedContext.size()) = '\0';
        return str;
    }

    const UNITY_INTERFACE_EXPORT char* UNITY_INTERFACE_API InstanciatedContext()
    {
        std::string instantciatedContext = "";
        if (s_CurrentAPI != NULL)
        {
            if (s_CurrentAPI->getApiType() == kUnityGfxRendererNull)
                instantciatedContext = "NULL API";
            else if (s_CurrentAPI->getApiType() == kUnityGfxRendererD3D11)
                instantciatedContext = "D3D11 API";
            else if (s_CurrentAPI->getApiType() == kUnityGfxRendererD3D12)
                instantciatedContext = "D3D12 API";
            else if (s_CurrentAPI->getApiType() == kUnityGfxRendererOpenGLES30)
                instantciatedContext = "OpenGL3.0 API";
            else if (s_CurrentAPI->getApiType() == kUnityGfxRendererOpenGLCore)
                instantciatedContext = "OpenGLCore API";
            else if (s_CurrentAPI->getApiType() == kUnityGfxRendererVulkan)
                instantciatedContext = "Vulkan API";
            else
                instantciatedContext = "Unsupported context " + std::to_string(s_CurrentAPI->getApiType());
        }
        else
            instantciatedContext = "API is NULL";

        char* str = (char*)malloc(sizeof(char) * instantciatedContext.size() + 1);
        strcpy(str, instantciatedContext.c_str());
        *(str + instantciatedContext.size()) = '\0';
        return str;
    }
}