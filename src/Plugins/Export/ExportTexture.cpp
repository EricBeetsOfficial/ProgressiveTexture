#include <ExportInterface.h>
#include <RenderAPI.h>
#include <Log.h>

#include <ThreadWorker.h>
#include <TextureTask.h>
#include <Callback.h>

ThreadWorker<TextureTasks> workerTexture;
extern RenderAPI* s_CurrentAPI;

#include <Platform3d.h>
GLuint glTexId;

extern "C"
{
    INTERFACE_EXPORT void INTERFACE_API LoadTexture(const char* filePath, Utils::Delegate::TextureParameter* textureParameter)
    {
        GraphicsAPI api = GraphicsAPI::None;
        switch (s_CurrentAPI->getApiType())
        {
            case UnityGfxRenderer::kUnityGfxRendererOpenGLCore:
            case UnityGfxRenderer::kUnityGfxRendererOpenGLES30:
                api = GraphicsAPI::OpenGL;
                break;
            case UnityGfxRenderer::kUnityGfxRendererD3D11:
                api = GraphicsAPI::D3D11;
                break;
            case UnityGfxRenderer::kUnityGfxRendererD3D12:
                api = GraphicsAPI::D3D12;
                break;
            case UnityGfxRenderer::kUnityGfxRendererMetal:
                api = GraphicsAPI::Metal;
                break;
            case UnityGfxRenderer::kUnityGfxRendererVulkan:
                api = GraphicsAPI::Vulkan;
                break;
        }
        LOG_DEBUG(filePath);
        LOG_DEBUG("GraphicsAPI ", (int)api)
        auto textureTask = new TextureTasks(api, filePath, textureParameter);
        workerTexture.addWorker(textureTask);
    }

    void INTERFACE_EXPORT INTERFACE_API TextureCreatedCallback(Utils::Callback::TextureCreated callback)
    {
        LOG_DEBUG("");
        Utils::Callback::ExportTexture::textureCreated = callback;
    }
}