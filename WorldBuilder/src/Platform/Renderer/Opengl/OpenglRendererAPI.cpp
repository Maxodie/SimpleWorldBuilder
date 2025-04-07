#include "Platform/Renderer/Opengl/OpenglRendererApi.hpp"
#include "Core/Renderer/Buffer.hpp"
#include "Core/Renderer/Vertex.hpp"
#include "glad/glad.h"

namespace WB
{

OpenglRendererAPI::OpenglRendererAPI(API api)
    : RendererAPI(api)
{
}

void OpenglRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    glViewport(x, y, w, h);
}

void OpenglRendererAPI::Draw(SharedPtr<VertexBuffer<Vertex3D>>& vertexBuffer, SharedPtr<IndexBuffer<uint32_t>>& indexBuffer)
{
    //shaders source
    /*const char *vertexShaderSource = "#version 330 core\n"*/
    /*"layout (location = 0) in vec3 aPos;\n"*/
    /*"void main()\n"*/
    /*"{\n"*/
    /*"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"*/
    /*"}\0";*/
    //shaders
    //create
    /*GLuint vertexShader;*/
    /*vertexShader = glCreateShader(GL_VERTEX_SHADER);*/
    //compile shader
    /*glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);*/
    /*glCompileShader(vertexShader);*/

    //check
    /*int  success;*/
    /*char infoLog[512];*/
    /*glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);*/
    /*if(!success)*/
    /*{*/
    /*    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);*/
    /*    CORE_LOG_ERROR("SHADER::VERTEX::COMPILATION_FAILED : %s", infoLog);*/
    /*}*/

    //fragment shader
    /*const char *fragmentShaderSource = "#version 330 core\nout vec4 FragColor;\n"*/
    /*"void main()\n"*/
    /*"{\n"*/
    /*"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"*/
    /*"} \0";*/
    //fragment compilation
    /*unsigned int fragmentShader;*/
    /*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);*/
    /*glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);*/
    /*glCompileShader(fragmentShader);*/

    //shaders
    //shader program
    /*unsigned int shaderProgram;*/
    /*shaderProgram = glCreateProgram();*/
    /*glAttachShader(shaderProgram, vertexShader);*/
    /*glAttachShader(shaderProgram, fragmentShader);*/
    /*glLinkProgram(shaderProgram);*/
    /*glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);*/
    /*if(!success) {*/
    /*    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);*/
    /*    CORE_LOG_ERROR("SHADER::PROGRAM::LINK : %s", infoLog);*/
    /*}*/


    glEnableVertexAttribArray(0);

    vertexBuffer->BindBuffer();
    indexBuffer->BindBuffer();
    //draw
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    //to use shader
    /*glUseProgram(shaderProgram);*/

    glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    //delete shaders
    /*glDeleteShader(vertexShader);*/
    /*glDeleteShader(fragmentShader);*/
}

void OpenglRendererAPI::SetClearColor(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
}

void OpenglRendererAPI::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}
