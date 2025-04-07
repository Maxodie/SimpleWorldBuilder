#pragma once
#include "Core/Core.hpp"

namespace WB
{

template<typename TValue>
class Buffer
{
public:
    Buffer() = delete;
    Buffer(size_t startBufferCount);

    virtual ~Buffer();

    void AddValue(TValue& vertex);
    virtual void BindBuffer() = 0;

    [[nodiscard]] WB_INLINE constexpr size_t GetCount() const noexcept
    {
        return m_valuesCount;
    }

    [[nodiscard]] WB_INLINE constexpr TValue* GetValues() const noexcept
    {
        return m_values;
    }

    void ResetBuffer();

protected:
    TValue* m_values;
    size_t m_valuesCount;
};

template <typename TVertex>
class VertexBuffer : public Buffer<TVertex>
{
public:
    VertexBuffer() = delete;
    VertexBuffer(size_t startBufferCount);

    virtual void BindBuffer() = 0;

    static SharedPtr<VertexBuffer<TVertex>> Create(size_t bufferSize);
};

template <typename TIndex>
class IndexBuffer : public Buffer<TIndex>
{
public:
    IndexBuffer() = delete;
    IndexBuffer(size_t startBufferCount);

    virtual void BindBuffer() = 0;

    static SharedPtr<IndexBuffer<TIndex>> Create(size_t bufferSize);
};

}
