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
    LOG_DEBUG("OnGraphicsDeviceEvent");
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(s_CurrentAPI == NULL);
		s_RendererType = s_Graphics->GetRenderer();
		s_CurrentAPI = CreateRenderAPI(s_RendererType);
	}

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
	LOG_INFO("UnityPluginLoad");
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
    LOG_INFO("UnityPluginUnload")
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.
#include <Platform3d.h>
// extern GLuint glTexId;
// int count = 0;

static void INTERFACE_API OnRenderEvent(int eventID)
{
    // Unknown / unsupported graphics device type? Do nothing
    if (s_CurrentAPI == NULL || s_Graphics == NULL)
        return;

    GLenum error = gl3wGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_ERROR("GetRenderEventFunc error: ", error);
    }

    if (eventID == 1)
    {
        if (!workerTexture.isComplete())
        {
            workerTexture.tick();
        }
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
}

// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.
extern "C" UnityRenderingEvent INTERFACE_EXPORT INTERFACE_API GetRenderEventFunc()
{
    return OnRenderEvent;
}