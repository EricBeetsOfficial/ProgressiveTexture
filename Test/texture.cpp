#include <GraphicTexture.h>
#include <Factory.h>
#include <Log.h>

int main()
{
    Utils::Log::Level(Utils::Log::Level_t::Debug);

    gl3wInit();

    auto t0 = GraphicTexture::createGraphicTexture(GraphicsAPI::OpenGL, 0, 0, 0, nullptr);
    auto t1 = GraphicTexture::createGraphicTexture(GraphicsAPI::D3D11, 0, 0, 0, nullptr);
    auto t2 = GraphicTexture::createGraphicTexture(GraphicsAPI::D3D12, 0, 0, 0, nullptr);
    auto t3 = GraphicTexture::createGraphicTexture(GraphicsAPI::Metal, 0, 0, 0, nullptr);
    auto t4 = GraphicTexture::createGraphicTexture(GraphicsAPI::Vulkan, 0, 0, 0, nullptr);
}