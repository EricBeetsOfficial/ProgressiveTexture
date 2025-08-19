#include "sample_dx11.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <iostream>

struct Vertex {
    float x, y, z;
    float u, v;
};

const char* vertexShaderSrc = R"(
struct VS_IN {
    float3 pos : POSITION;
    float2 uv  : TEXCOORD0;
};

struct PS_IN {
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

PS_IN main(VS_IN input) {
    PS_IN output;
    output.pos = float4(input.pos, 1.0);
    output.uv = input.uv;
    return output;
}
)";

const char* pixelShaderSrc = R"(
Texture2D tex0 : register(t0);
SamplerState samp0 : register(s0);

struct PS_INPUT {
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD0;
};

float4 main(PS_INPUT input) : SV_TARGET {
    return tex0.Sample(samp0, input.uv);
}
)";

ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
IDXGISwapChain* swapChain = nullptr;
ID3D11RenderTargetView* rtv = nullptr;
ID3D11InputLayout* inputLayout = nullptr;
ID3D11Buffer* vertexBuffer = nullptr;
ID3D11Buffer* indexBuffer = nullptr;
ID3D11VertexShader* vertexShader = nullptr;
ID3D11PixelShader* pixelShader = nullptr;
ID3D11SamplerState* samplerState = nullptr;

void* dx11ContextInit(void *window)
{
    HWND hwnd = (HWND)window;
    // Swap chain
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = 800;
    scd.BufferDesc.Height = 600;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        nullptr, 0, D3D11_SDK_VERSION, &scd,
        &swapChain, &device, &featureLevel, &context);

    if (FAILED(hr)) {
        std::cerr << "Failed to create D3D11 device and swap chain\n";
        return nullptr;
    }

    // Render target view
    ID3D11Texture2D* backBuffer = nullptr;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) { std::cerr << "GetBuffer failed\n"; return nullptr; }

    hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
    backBuffer->Release();
    if (FAILED(hr)) { std::cerr << "CreateRenderTargetView failed\n"; return nullptr; }

    // Bind RTV to OM (must be done)
    context->OMSetRenderTargets(1, &rtv, nullptr);

    // Viewport
    D3D11_VIEWPORT viewport = {};
    viewport.Width = 800.f;
    viewport.Height = 600.f;
    viewport.MinDepth = 0.f;
    viewport.MaxDepth = 1.f;
    viewport.TopLeftX = 0.f;
    viewport.TopLeftY = 0.f;
    context->RSSetViewports(1, &viewport);

    // Compile shaders
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    hr = D3DCompile(vertexShaderSrc, strlen(vertexShaderSrc), nullptr, nullptr, nullptr,
        "main", "vs_5_0", 0, 0, &vsBlob, &errorBlob);
    if (FAILED(hr)) {
        if (errorBlob) std::cerr << "VS compile error: " << (char*)errorBlob->GetBufferPointer() << "\n";
        return nullptr;
    }

    hr = D3DCompile(pixelShaderSrc, strlen(pixelShaderSrc), nullptr, nullptr, nullptr,
        "main", "ps_5_0", 0, 0, &psBlob, &errorBlob);
    if (FAILED(hr)) {
        if (errorBlob) std::cerr << "PS compile error: " << (char*)errorBlob->GetBufferPointer() << "\n";
        return nullptr;
    }

    hr = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
    if (FAILED(hr)) { std::cerr << "CreateVertexShader failed\n"; return nullptr; }
    hr = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
    if (FAILED(hr)) { std::cerr << "CreatePixelShader failed\n"; return nullptr; }

    // Input layout: POSITION + TEXCOORD
    D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(Vertex, u), D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    hr = device->CreateInputLayout(layoutDesc, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
    vsBlob->Release();
    psBlob->Release();
    if (FAILED(hr)) { std::cerr << "CreateInputLayout failed\n"; return nullptr; }

    Vertex vertices[] = {
        { -0.5f,  0.5f, 0.f, 0.f, 1.f }, // top-left
        {  0.5f,  0.5f, 0.f, 1.f, 1.f }, // top-right
        {  0.5f, -0.5f, 0.f, 1.f, 0.f }, // bottom-right
        { -0.5f, -0.5f, 0.f, 0.f, 0.f }, // bottom-left
    };
    uint16_t indices[] = { 0, 1, 2, 2, 3, 0 };

    // Create vertex buffer
    D3D11_BUFFER_DESC vbDesc = {};
    vbDesc.Usage = D3D11_USAGE_DEFAULT;
    vbDesc.ByteWidth = sizeof(vertices);
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA vbData = {};
    vbData.pSysMem = vertices;
    hr = device->CreateBuffer(&vbDesc, &vbData, &vertexBuffer);
    if (FAILED(hr)) { std::cerr << "CreateBuffer vertex failed\n"; return nullptr; }

    // Create index buffer (16-bit)
    D3D11_BUFFER_DESC ibDesc = {};
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.ByteWidth = sizeof(indices);
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    D3D11_SUBRESOURCE_DATA ibData = {};
    ibData.pSysMem = indices;
    hr = device->CreateBuffer(&ibDesc, &ibData, &indexBuffer);
    if (FAILED(hr)) { std::cerr << "CreateBuffer index failed\n"; return nullptr; }

    // Sampler
    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = sampDesc.AddressV = sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    device->CreateSamplerState(&sampDesc, &samplerState);

    return device;
}

void dx11ContextLoop(void *texIdPtr, void *dxPtr, bool &created)
{
    float clearColor[4] = { 0.2f, 0.3f, 0.4f, 1.f };
    context->ClearRenderTargetView(rtv, clearColor);

    ID3D11Texture2D* texture2D = nullptr;
    ID3D11ShaderResourceView* textureSRV = nullptr;
    // If plugin provided the texture, create SRV once
    if (created && texIdPtr && texIdPtr)
    {
        texture2D = reinterpret_cast<ID3D11Texture2D*>(texIdPtr);
        textureSRV = reinterpret_cast<ID3D11ShaderResourceView*>(dxPtr);
        if (texture2D) {
            HRESULT hr = device->CreateShaderResourceView(texture2D, nullptr, &textureSRV);
            if (FAILED(hr)) {
                std::cerr << "CreateShaderResourceView failed: 0x" << std::hex << hr << "\n";
                textureSRV = nullptr;
            }
        }
        UINT stride = sizeof(Vertex);
        UINT offset = 0;
        context->IASetInputLayout(inputLayout);
        context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
        context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0); // 16-bit indices
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        context->VSSetShader(vertexShader, nullptr, 0);
        context->PSSetShader(pixelShader, nullptr, 0);

        context->PSSetSamplers(0, 1, &samplerState);
        context->PSSetShaderResources(0, 1, &textureSRV);

        context->DrawIndexed(6, 0, 0);
    }

    swapChain->Present(1, 0);
}

void dx11ContextDestroy()
{
    // textureSRV->Release();
    samplerState->Release();
    indexBuffer->Release();
    vertexBuffer->Release();
    inputLayout->Release();
    vertexShader->Release();
    pixelShader->Release();
    rtv->Release();
    swapChain->Release();
    context->Release();
    device->Release();
}
