#include "Core/Renderer/RendererAPI.hpp"
#include "Platform/Renderer/Opengl/OpenglRendererApi.hpp"

namespace WB
{

RendererAPI::RendererAPI(API api)
    : m_api(api)
{

}

UniquePtr<RendererAPI> RendererAPI::CreateRendererAPI(API api)
{
    switch (api) {
        case API::OpenGL:
            return MakeUnique<OpenglRendererAPI>(api);
        break;

        case API::None:
            CORE_LOG_ERROR("Unknown Renderer API : %d", api);
        break;

        default:
            CORE_LOG_ERROR("Unknown Renderer API : %d", api);
        break;
    }

    CORE_LOG_ERROR("Unknown Renderer API : %d", api);
    return nullptr;
}

}
