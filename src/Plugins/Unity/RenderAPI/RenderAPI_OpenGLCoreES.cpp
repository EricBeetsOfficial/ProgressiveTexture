#include <RenderAPI.h>
#include <Platform3d.h>

#if SUPPORT_OPENGL_UNIFIED

class RenderAPI_OpenGLCoreES : public RenderAPI
{
public:
	RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
	virtual ~RenderAPI_OpenGLCoreES() { }

	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);

private:
	void CreateResources();
};


RenderAPI* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType)
{
	return new RenderAPI_OpenGLCoreES(apiType);
}

void RenderAPI_OpenGLCoreES::CreateResources()
{
#	if SUPPORT_OPENGL_CORE
	if (m_APIType == UnityGfxRenderer::kUnityGfxRendererOpenGLCore)
	{
#		if UNITY_WIN
		gl3wInit();
#		endif
	}
#	endif // if SUPPORT_OPENGL_CORE
	//assert(glGetError() == GL_NO_ERROR);
}


RenderAPI_OpenGLCoreES::RenderAPI_OpenGLCoreES(UnityGfxRenderer apiType) : RenderAPI(apiType)
{
}


void RenderAPI_OpenGLCoreES::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	if (type == UnityGfxDeviceEventType::kUnityGfxDeviceEventInitialize)
	{
		CreateResources();
	}
	else if (type == UnityGfxDeviceEventType::kUnityGfxDeviceEventShutdown)
	{
		//@TODO: release resources
	}
}

#endif // #if SUPPORT_OPENGL_UNIFIED
