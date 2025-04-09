#pragma once
#include "Core/Renderer/Vertex.hpp"
#include <glad/glad.h>

namespace WB
{


template<typename TVertex>
class OpenglVertexArrayBuffer : public VertexArrayBuffer<TVertex>
{
public:
    OpenglVertexArrayBuffer()
    {
        glGenVertexArrays(1, &m_id);
    }

    virtual void AddVertexBuffer(SharedPtr<VertexBuffer<TVertex>>& vertexBuffer) override;

    WB_INLINE void Bind() override { glBindVertexArray(m_id); }

private:
    uint32_t m_id = 0;
};

}
