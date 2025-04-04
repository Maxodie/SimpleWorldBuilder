#pragma once
#include "Core/Renderer/VertexBuffer.hpp"

namespace WB
{

template<typename TVertex>
class OpenglVertexBuffer : public VertexBuffer<TVertex>
{
public:
    OpenglVertexBuffer() = delete;
    OpenglVertexBuffer(size_t startBufferSize);

    virtual void BindBuffer() override;

private:
    uint32_t vertexArrayID;
    uint32_t vertexBuffer;
};

}
