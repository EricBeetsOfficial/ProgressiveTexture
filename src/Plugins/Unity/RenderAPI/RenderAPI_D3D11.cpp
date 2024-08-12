#include <RenderAPI.h>
#include <Platform3d.h>

// Direct3D 11 implementation of RenderAPI.
#if SUPPORT_D3D11

#include "Unity/IUnityGraphicsD3D11.h"

class RenderAPI_D3D11 : public RenderAPI
{
public:
	RenderAPI_D3D11(UnityGfxRenderer apiType);
	virtual ~RenderAPI_D3D11() { }
	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);

private:
	void CreateResources();
	void ReleaseResources();
	void* getDevice() const { return m_Device; }

private:
	ID3D11Device* m_Device;
};


RenderAPI* CreateRenderAPI_D3D11(UnityGfxRenderer apiType)
{
	return new RenderAPI_D3D11(apiType);
}

RenderAPI_D3D11::RenderAPI_D3D11(UnityGfxRenderer apiType) : RenderAPI(apiType), m_Device(NULL)
{
}

void RenderAPI_D3D11::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	switch (type)
	{
	case UnityGfxDeviceEventType::kUnityGfxDeviceEventInitialize:
	{
		IUnityGraphicsD3D11* d3d = interfaces->Get<IUnityGraphicsD3D11>();
		m_Device = d3d->GetDevice();
		CreateResources();
		break;
	}
	case UnityGfxDeviceEventType::kUnityGfxDeviceEventShutdown:
		ReleaseResources();
		break;
	}
}


void RenderAPI_D3D11::CreateResources()
{
}


void RenderAPI_D3D11::ReleaseResources()
{
}
#endif // #if SUPPORT_D3D11
