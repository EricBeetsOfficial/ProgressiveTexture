#include <gl3w/gl3w.h>
#include <iostream>
#include <Log.h>

#include "sample_ogl.h"

const char* vsSource = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aUV;
out vec2 TexCoord;
void main() {
    TexCoord = aUV;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)glsl";

// Fragment shader
const char* fsSource = R"glsl(
#version 330 core
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D uTexture;
void main() {
    FragColor = texture(uTexture, TexCoord);
}
)glsl";

GLuint prog;
GLuint vao;

GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << "\n";
    }
    return shader;
}

GLuint createProgram()
{
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSource);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

void* glContextInit(void *)
{
    gl3wInit();
    glClearColor( 0.5, 0.5, 0.5, 0.0 );
    glViewport( 0, 0, 800, 600 );

    prog = createProgram();

        float quad[] = {
        // pos          // uv
        -0.5f, -0.5f, 0.f, 0.f,
         0.5f, -0.5f, 1.f, 0.f,
         0.5f,  0.5f, 1.f, 1.f,
        -0.5f,  0.5f, 0.f, 1.f
    };
    unsigned int idx[] = { 0, 1, 2, 2, 3, 0 };

    GLuint vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    return (void*)0x01;
}

void glContextLoop(void *texIdPtr, void *optPtr, bool &created)
{
    GLuint tex = (GLuint)(size_t)texIdPtr;

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(prog);
    if (created == true)
    {
        glBindTexture(GL_TEXTURE_2D, tex);
    }
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void glContextDestroy()
{
    glDeleteProgram(prog);
}
