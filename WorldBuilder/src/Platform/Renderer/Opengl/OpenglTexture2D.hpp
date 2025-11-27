#pragma once

#include "Core/Renderer/Texture2D.hpp"
#include "glad/glad.h"

namespace WB
{

class OpenglTexture2D  : public Texture2D
{
public:
    OpenglTexture2D(uint32_t width, uint32_t height);
    OpenglTexture2D(const Path& path);
    ~OpenglTexture2D();

    virtual void SetData(void* data, uint32_t size) override;
    virtual void Bind(uint32_t slot) override;

    virtual uint32_t GetTextureID() const override;

protected:
    virtual void HandleFilterSwitch() override;

protected:
    uint32_t m_rendererID;
    GLenum m_internalFormat, m_dataFormat;
};

}
