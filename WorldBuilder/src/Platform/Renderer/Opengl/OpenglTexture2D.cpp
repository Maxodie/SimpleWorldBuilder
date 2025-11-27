#include "Platform/Renderer/Opengl/OpenglTexture2D.hpp"
#include "Core/Log/Log.hpp"
#include "stb_image.h"

namespace WB
{

OpenglTexture2D::OpenglTexture2D(uint32_t width, uint32_t height)
    : Texture2D(width, height)
{
    m_internalFormat = GL_RGBA8;
    m_dataFormat = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
    glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

    glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenglTexture2D::OpenglTexture2D(const Path& path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = nullptr;
    data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
    WB_CORE_ASSERT(data, "Failed to load image!");

    m_width = width;
    m_height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if(channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    m_internalFormat = internalFormat;
    m_dataFormat = dataFormat;

    WB_CORE_ASSERT(internalFormat & dataFormat, "Format not supported !");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
    glTextureStorage2D(m_rendererID, 1, internalFormat, m_width, m_height);

    m_filter = Filter::Linear;
    glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(m_data);
}

OpenglTexture2D::~OpenglTexture2D()
{
    glDeleteTextures(1, &m_rendererID);
}

void OpenglTexture2D::SetData(void* data, uint32_t size)
{
    uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
    WB_CORE_ASSERT(size == m_width * m_height * bpp, "Data must be the entire texture !");
    glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenglTexture2D::Bind(uint32_t slot)
{
    glBindTextureUnit(slot, m_rendererID);
}

uint32_t OpenglTexture2D::GetTextureID() const
{
    return m_rendererID;
}

void OpenglTexture2D::HandleFilterSwitch()
{
    CORE_LOG_ERROR("Does not work for now");
    // switch (m_filter)
    // {
    //     case Filter::Linear:
    //     {
    //         glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //         glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    //     }
    //     case Filter::Nearest:
    //     {
    //         glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //         glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //
    //     }
    //     case Filter::Length:
    //     {
    //             CORE_LOG_ERROR("Texture2D should not have length as filter");
    //     }
    // }
}


}
