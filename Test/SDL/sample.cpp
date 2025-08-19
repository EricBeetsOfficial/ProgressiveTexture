#include "sample_sdl.h"

#include <ThreadWorker.h>
#include <TextureTask.h>

ThreadWorker<TextureTasks> workerTexture;
bool created = false;
void *texIdPtr = nullptr;
void* optPtr = nullptr;    // possibly SRV or extra pointer from plugin — we'll ignore dxPtr and create SRV from texIdPtr

#if defined (USE_OPENGL)
 #include "sample_ogl.h"
 decltype(&glContextInit) graphicContextInit = &glContextInit;
 decltype(&glContextLoop) graphicContextLoop = &glContextLoop;
 decltype(&glContextDestroy) graphicContextDestroy = &glContextDestroy;
 #define TITLE "SDL3 + OpenGL"
 Context context = Context::OpenGL;
 GraphicsAPI api = GraphicsAPI::OpenGL;
#elif defined(USE_DX11)
 #include "sample_dx11.h"
 decltype(&dx11ContextInit) graphicContextInit = &dx11ContextInit;
 decltype(&dx11ContextLoop) graphicContextLoop = &dx11ContextLoop;
 decltype(&dx11ContextDestroy) graphicContextDestroy = &dx11ContextDestroy;
 #define TITLE "SDL3 + DirectX11"
 Context context = Context::D3D11;
 GraphicsAPI api = GraphicsAPI::D3D11;
#endif

int main(int argc, char** argv)
{
    // Init
    void* window = sdlContextInit(TITLE, context);
    if (window == nullptr)
    {
        sdlContextDestroy();
        return -1;
    }
    void* device = graphicContextInit(window);
    if (device == nullptr)
    {
        sdlContextDestroy();
        return -1;
    }
    // Texture parameters
    Utils::Delegate::TextureParameter textureParameter;
    textureParameter.yFlip = false;
    std::strcpy(textureParameter.guid, "AAAA");
    Utils::Callback::ExportTexture::textureCreated = [](Utils::Delegate::TextureParameter * parameters)
    {
        LOG_INFO("Done !");
        created = true;
        texIdPtr = parameters->texId;
        optPtr = parameters->dxPtr;
    };
    // Texture
    std::string filePath = "../Test/images/pilat.jpg";
    auto textureTask = new TextureTasks(api, (const void* )device, filePath, &textureParameter);
    workerTexture.addWorker(textureTask);
    // Event loop
    bool running = true;
    while (running)
    {
        sdlContextLoop(running);
        if (!workerTexture.isComplete())
        {
            workerTexture.tick();
        }
        graphicContextLoop(texIdPtr, optPtr, created);
    }
    // Destroy contexts
    graphicContextDestroy();
    sdlContextDestroy();
    return 0;
}