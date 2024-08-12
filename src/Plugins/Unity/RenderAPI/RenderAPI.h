#pragma once

#include "Unity/IUnityGraphics.h"
#include <stddef.h>

struct IUnityInterfaces;


// Super-simple "graphics abstraction". This is nothing like how a proper platform abstraction layer would look like;
// all this does is a base interface for whatever our plugin sample needs. Which is only "draw some triangles"
// and "modify a texture" at this point.
//
// There are implementations of this base class for D3D9, D3D11, OpenGL etc.; see individual RenderAPI_* files.
class RenderAPI
{
public:
	RenderAPI(UnityGfxRenderer apiType) : m_APIType(apiType) {}
	virtual ~RenderAPI() { }
	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces) = 0;

	virtual void* getDevice() const { return NULL; }

	UnityGfxRenderer getApiType() const { return m_APIType; }

protected:
	UnityGfxRenderer m_APIType;
};

// Create a graphics API implementation instance for the given API type.
RenderAPI* CreateRenderAPI(UnityGfxRenderer apiType);

