#include "Core/Renderer/ShaderProgram.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Platform/Renderer/Opengl/OpenglShaderProgram.hpp"

namespace WB
{

SharedPtr<ShaderProgram> ShaderProgram::Create()
{
    switch(RenderCommand::GetAPI())
    {
        case RendererAPI::API::OpenGL:
            return MakeShared<OpenglShaderProgram>();
        break;

        case RendererAPI::API::None:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;

        default:
            CORE_LOG_ERROR("Unknown RendererAPI : %d", RenderCommand::GetAPI());
        break;

    }

    return nullptr;
}

}
