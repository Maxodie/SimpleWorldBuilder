#include "Platform/Renderer/Opengl/OpenglFrameBuffer.hpp"
#include "Core/Log/Log.hpp"
#include <glad/glad.h>

namespace WB
{

OpenglFrameBuffer::OpenglFrameBuffer()
{
    Invalidate();
}

OpenglFrameBuffer::~OpenglFrameBuffer()
{
    TryDestroyFrameBuffer();
}

void OpenglFrameBuffer::Invalidate()
{

    TryDestroyFrameBuffer();

    glCreateFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_frameBufferTextureColor);
    glBindTexture(GL_TEXTURE_2D, m_frameBufferTextureColor);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_info.width, m_info.height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBufferTextureColor, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_frameBufferTextureDepth);
    glBindTexture(GL_TEXTURE_2D, m_frameBufferTextureDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_info.width, m_info.height, 0,
                 GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_frameBufferTextureDepth, 0);

    WB_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "opengl framebuffer is not complete");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenglFrameBuffer::Resize(uint32_t width, uint32_t height)
{
    m_info.width = width;
    m_info.height = height;
    Invalidate();
}

void OpenglFrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_info.width, m_info.height);
}

void OpenglFrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenglFrameBuffer::TryDestroyFrameBuffer()
{
    if(m_frameBuffer)
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
        glDeleteTextures(1, &m_frameBufferTextureColor);
        glDeleteTextures(1, &m_frameBufferTextureDepth);
    }
}

}
