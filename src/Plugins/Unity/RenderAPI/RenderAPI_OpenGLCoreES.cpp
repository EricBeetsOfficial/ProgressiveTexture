#include <RenderAPI.h>
#include <Platform3d.h>

#include <Log.h>

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
    LOG_INFO("CreateRenderAPI_OpenGLCoreES");
	return new RenderAPI_OpenGLCoreES(apiType);
}

void RenderAPI_OpenGLCoreES::CreateResources()
{
#if SUPPORT_OPENGL_CORE
	if (m_APIType == UnityGfxRenderer::kUnityGfxRendererOpenGLCore)
	{
#if UNITY_WIN
LOG_INFO("gl3wInit !!")
		gl3wInit();
#endif
	}
#endif // if SUPPORT_OPENGL_CORE
	//assert(glGetError() == GL_NO_ERROR);
// INFO("gl3wInit !!")
// 		if(gl3wInit())
// 			ERROR("gl3wInit error")
// 		else
// 			INFO("gl3wInit OK")
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
