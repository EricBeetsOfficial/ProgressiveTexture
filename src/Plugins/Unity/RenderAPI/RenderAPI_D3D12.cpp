#include <RenderAPI.h>
#include <Platform3d.h>

#include <cmath>

// Direct3D 12 implementation of RenderAPI.
#include "Log/Log.h"

#if SUPPORT_D3D12

#include <assert.h>
#include <d3d12.h>
#include "Unity/IUnityGraphicsD3D12.h"

#include "RenderAPI_D3D12.h"

RenderAPI* CreateRenderAPI_D3D12(UnityGfxRenderer apiType)
{
	return new RenderAPI_D3D12(apiType);
}

RenderAPI_D3D12::RenderAPI_D3D12(UnityGfxRenderer apiType) : RenderAPI(apiType)
                                                           , s_D3D12(NULL)
                                                           , device(NULL)
{
}

void RenderAPI_D3D12::CreateResources()
{
	device = s_D3D12->GetDevice();
}

void RenderAPI_D3D12::ReleaseResources()
{
}

void RenderAPI_D3D12::ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces)
{
	switch (type)
	{
	case UnityGfxDeviceEventType::kUnityGfxDeviceEventInitialize:
		s_D3D12 = interfaces->Get<IUnityGraphicsD3D12v2>();
		CreateResources();
		break;
	case UnityGfxDeviceEventType::kUnityGfxDeviceEventShutdown:
		ReleaseResources();
		break;
	}
}

RenderAPI_D3D12::Command* RenderAPI_D3D12::createCommand()
{
    return new Command(device);
}

RenderAPI_D3D12::Command::Command(ID3D12Device* device) : _commandAllocator(NULL)
                                                        , commandList(NULL)
                                                        , _event(NULL)
                                                        , _fenceValue(0)
{
    HRESULT hr = E_FAIL;

    // Command list
    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_commandAllocator));
    if (FAILED(hr)) {
        Utils::Log::Error("Failed to CreateCommandAllocator");
    }
    hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _commandAllocator, nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(hr)) {
        Utils::Log::Error("Failed to CreateCommandList");
    }
    commandList->Close();

    // Create event and init fence
    _fenceValue = 0;
    _event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    // Don't forget to reset
    reset();
}

RenderAPI_D3D12::Command::~Command()
{
    if (_event)
        CloseHandle(_event);
    SAFE_RELEASE(commandList);
    SAFE_RELEASE(_commandAllocator);
}

void RenderAPI_D3D12::Command::reset()
{
    HRESULT hr = commandList->Reset(_commandAllocator, NULL);
    if (!SUCCEEDED(hr)) {
        Utils::Log::Error("Error ID3D12GraphicsCommandList reset");
    }
}

void RenderAPI_D3D12::Command::executeCommandList(IUnityGraphicsD3D12v2* graphics, ID3D12Resource *resource)
{
    commandList->Close();

    UnityGraphicsD3D12ResourceState resourceState = {};
    resourceState.resource = resource;
    resourceState.expected = D3D12_RESOURCE_STATE_COPY_DEST;
    resourceState.current = D3D12_RESOURCE_STATE_COPY_DEST;
    graphics->ExecuteCommandList(commandList, 1, &resourceState);
}

void RenderAPI_D3D12::Command::waitFence(IUnityGraphicsD3D12v2 *graphics)
{
    graphics->GetFrameFence()->SetEventOnCompletion(0, _event);
    WaitForSingleObject(_event, INFINITE);
}

#endif // #if SUPPORT_D3D12
