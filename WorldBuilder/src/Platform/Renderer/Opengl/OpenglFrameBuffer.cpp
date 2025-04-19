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
    glGenRenderbuffers(1, &m_renderBuffer);
    Bind();

    glGenTextures(1, &m_frameBufferTextureColor);
    glBindTexture(GL_TEXTURE_2D, m_frameBufferTextureColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_info.width, m_info.height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_frameBufferTextureColor, 0);

    glGenTextures(1, &m_frameBufferTextureDepth);
    glBindTexture(GL_TEXTURE_2D, m_frameBufferTextureDepth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_info.width, m_info.height, 0,
                 GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_frameBufferTextureDepth, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_info.width, m_info.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        CORE_LOG_ERROR("opengl framebuffer is not complete");
    }

    Unbind();
}

void OpenglFrameBuffer::Resize(uint32_t width, uint32_t height)
{
    m_info.width = width;
    m_info.height = width;
    Invalidate();
}

void OpenglFrameBuffer::Bind()
{
    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glViewport(0, 0, m_info.width, m_info.height);
}

void OpenglFrameBuffer::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void OpenglFrameBuffer::TryDestroyFrameBuffer()
{
    if(m_frameBuffer)
    {
        glDeleteFramebuffers(1, &m_frameBuffer);
        glDeleteRenderbuffers(1, &m_renderBuffer);
        glDeleteTextures(1, &m_frameBufferTextureColor);
        glDeleteTextures(1, &m_frameBufferTextureDepth);
    }
}

}
