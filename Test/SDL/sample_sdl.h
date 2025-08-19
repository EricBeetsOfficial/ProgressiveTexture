enum class Context
{
    OpenGL,
    D3D11
};

void* sdlContextInit(const char* title, Context context);
void sdlContextLoop(bool &running);
void sdlContextDestroy();