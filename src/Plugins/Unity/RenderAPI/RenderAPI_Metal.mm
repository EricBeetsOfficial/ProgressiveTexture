#include <RenderAPI.h>
#include <Platform3d.h>
#include <RenderAPI_Metal.h>
// Metal implementation of RenderAPI.

#if SUPPORT_METAL

// #import <Metal/Metal.h>

RenderAPI* CreateRenderAPI_Metal(UnityGfxRenderer apiType)
{
	return new RenderAPI_Metal(apiType);
}

void RenderAPI_Metal::CreateResources()
{
	id<MTLDevice> metalDevice = m_MetalGraphics->MetalDevice();
}


RenderAPI_Metal::RenderAPI_Metal(UnityGfxRenderer apiType) : RenderAPI(apiType)
{
}

void RenderAPI_Metal::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	if (type == UnityGfxDeviceEventType::kUnityGfxDeviceEventInitialize)
	{
		m_MetalGraphics = interfaces->Get<IUnityGraphicsMetal>();
		CreateResources();
	}
	else if (type == UnityGfxDeviceEventType::kUnityGfxDeviceEventShutdown)
	{
		//@TODO: release resources
	}
}

#endif // #if SUPPORT_METAL
