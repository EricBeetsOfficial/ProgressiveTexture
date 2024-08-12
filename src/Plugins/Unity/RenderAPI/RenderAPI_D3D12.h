#include <RenderAPI.h>
#include <Platform3d.h>

#if SUPPORT_D3D12

#include "Unity/IUnityGraphicsD3D12.h"

class RenderAPI_D3D12 : public RenderAPI
{
public:
	RenderAPI_D3D12(UnityGfxRenderer apiType);
	virtual ~RenderAPI_D3D12() { }

	virtual void ProcessDeviceEvent(UnityGfxDeviceEventType type, IUnityInterfaces* interfaces);

private:
	void CreateResources();
	void ReleaseResources();
	void* getDevice() const { return s_D3D12; }

public:
	IUnityGraphicsD3D12v2* s_D3D12;

	ID3D12Device* device;

public:
    class Command
    {
    public:
        Command (ID3D12Device* device);
        ~Command();

    public:
        void reset              ( );
        void executeCommandList (IUnityGraphicsD3D12v2* graphics, ID3D12Resource* resource);
        void waitFence          (IUnityGraphicsD3D12v2* graphics);

    private:
        ID3D12CommandAllocator* _commandAllocator;
        UINT64 _fenceValue;
        HANDLE _event;

    public:
        ID3D12GraphicsCommandList* commandList;
    };
    
    Command* createCommand();
};
#endif