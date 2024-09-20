#pragma once

enum class GraphicsAPI
{
    None,
    OpenGL,
    D3D11,
    D3D12,
    Metal,
    Vulkan
};

// template <GraphicsAPI API>
// class FactoryContext
// {
// public:
//     static Context* createContext() {
//         if constexpr (API == GraphicsAPI::OpenGL)
//             return new GL();
//         else if constexpr (API == GraphicsAPI::D3D11)
//             return new D3D11();
//         else if constexpr (API == GraphicsAPI::D3D12)
//             return new D3D12();
//         else if constexpr (API == GraphicsAPI::Metal)
//             return new Metal();
//         else if constexpr (API == GraphicsAPI::Vulkan)
//             return new Vulkan();
//         else
//             return nullptr; // Handle unsupported case
//     }
// };
