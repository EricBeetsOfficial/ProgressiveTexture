#include <SDL3/SDL.h>
#include <windows.h>

#include <iostream>

#include "sample_sdl.h"

SDL_Window* win;
SDL_GLContext ctx;
SDL_Event e;
Context currentContext;

void* sdlContextInit(const char* title, Context context)
{
    currentContext = context;
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL init failed\n";
        return nullptr;
    }
    if (context == Context::OpenGL)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }

    win = SDL_CreateWindow(title, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!win)
    {
        std::cerr << "Failed to create SDL window\n";
        SDL_Quit();
        return nullptr;
    }

    if (context == Context::OpenGL)
    {
        ctx = SDL_GL_CreateContext(win);
    }
    else if (context == Context::D3D11)
    {
        HWND hwnd = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(win), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
        return hwnd;
    }
    return win;
}

void sdlContextLoop(bool &running)
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT) running = false;
    }
    if (currentContext == Context::OpenGL)
    {
        SDL_GL_SwapWindow(win);
    }
}

void sdlContextDestroy()
{
    if (currentContext == Context::OpenGL)
    {
        SDL_GL_DestroyContext(ctx);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
}