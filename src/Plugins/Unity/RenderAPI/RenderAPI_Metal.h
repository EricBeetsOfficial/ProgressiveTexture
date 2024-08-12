#if SUPPORT_METAL
#include "Unity/IUnityGraphicsMetal.h"
#import <Metal/Metal.h>


class RenderAPI_Metal : public RenderAPI
{
public:
	RenderAPI_Metal(UnityGfxRenderer apiType);
	virtual ~RenderAPI_Metal() { }

	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);

private:
	void CreateResources();

public:
    IUnityGraphicsMetal* getMetalGraphics() const { return m_MetalGraphics; }

private:
	IUnityGraphicsMetal* m_MetalGraphics;
};
#endif
