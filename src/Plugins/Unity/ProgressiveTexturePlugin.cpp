#include <cassert>

#include <ExportInterface.h>
#include <IUnityGraphics.h>
#include <PlatformBase.h>
#include <RenderAPI.h>

#include <Callback.h>
#include <Factory.h>
#include <Texture.h>
#include <ThreadWorker.h>
#include <TextureTask.h>

IUnityInterfaces* s_UnityInterfaces = NULL;
IUnityGraphics* s_Graphics = NULL;
UnityGfxRenderer s_RendererType = kUnityGfxRendererNull;

RenderAPI* s_CurrentAPI = NULL;

extern ThreadWorker<TextureTasks> workerTexture;

// --------------------------------------------------------------------------
// UnitySetInterfaces
static void INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(s_CurrentAPI == NULL);
		s_RendererType = s_Graphics->GetRenderer();
		s_CurrentAPI = CreateRenderAPI(s_RendererType);
		// auto texture0 = Factory::Create<Texture>();
        // auto texture0 = Factory::Create<Texture<GraphicsAPI::Vulkan>>();

		std::shared_ptr<Texture> texture;

		switch (s_CurrentAPI->getApiType())
		{
			case kUnityGfxRendererOpenGLCore:
			case kUnityGfxRendererOpenGLES30:
		        texture = Factory::Create<Texture>(GraphicsAPI::OpenGL);
				break;
			case kUnityGfxRendererD3D11:
		        texture = Factory::Create<Texture>(GraphicsAPI::D3D11);
				break;
			case kUnityGfxRendererD3D12:
		        texture = Factory::Create<Texture>(GraphicsAPI::D3D12);
				break;
			case kUnityGfxRendererMetal:
		        texture = Factory::Create<Texture>(GraphicsAPI::Metal);
				break;
			case kUnityGfxRendererVulkan:
		        texture = Factory::Create<Texture>(GraphicsAPI::Vulkan);
			default:
				break;
		}
	}
INFO("")
	// Let the implementation process the device related events
	if (s_CurrentAPI)
	{
		s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete s_CurrentAPI;
		s_CurrentAPI = NULL;
		s_RendererType = kUnityGfxRendererNull;
	}
}

extern "C" void	INTERFACE_EXPORT INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    Utils::Log::Level(Utils::Log::Level_t::Debug);
	DEBUG();
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

#if SUPPORT_VULKAN
	if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
	{
		extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
		RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
	}
#endif // SUPPORT_VULKAN

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void INTERFACE_EXPORT INTERFACE_API UnityPluginUnload()
{
    INFO("UnityPluginUnload")
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.
#include <Platform3d.h>
extern GLuint glTexId;
static void INTERFACE_API OnRenderEvent(int eventID)
{
    // Unknown / unsupported graphics device type? Do nothing
    if (s_CurrentAPI == NULL || s_Graphics == NULL)
     return;

    if (eventID == 1)
    {
    }
    else if (eventID == 2)
    {
        // Logs
        if (Utils::Delegate::ExportLog::logCallback != nullptr)
        {
            while(1)
            {
                auto message = Utils::Log::GetLast();
                if (message.first.empty())
                    break;
                std::cout << message.first << std::endl;
                Utils::Delegate::ExportLog::logCallback(message.first.c_str(), message.second.c_str());
            }
        }
    }
    else if (eventID == 5)
    {
        unsigned char* pixels = (unsigned char*)malloc(sizeof(unsigned char) * 512 * 512 * 4);
        for (int y = 0; y < 512; y++)
        {
            for (int x = 0; x < 512; x++)
            {
                pixels[x * 4 + y * 512 * 4 + 0] = (x * y) % 255;
                pixels[x * 4 + y * 512 * 4 + 1] = (x * y) % 255;
                pixels[x * 4 + y * 512 * 4 + 2] = (x * y) % 255;
                pixels[x * 4 + y * 512 * 4 + 3] = 255;
            }
        }
        glBindTexture(GL_TEXTURE_2D, glTexId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        free(pixels);
    }
}

// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.
extern "C" UnityRenderingEvent INTERFACE_EXPORT INTERFACE_API GetRenderEventFunc()
{
    // workerTexture.tick();
    GLenum error = gl3wGetError();
    if (error != GL_NO_ERROR)
    {
        ERROR("GetRenderEventFunc error: ", error);
    }
    return OnRenderEvent;
}

extern "C" void INTERFACE_EXPORT INTERFACE_API UpdateFrame()
{
    workerTexture.tick();
}