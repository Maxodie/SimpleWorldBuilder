#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "Core/Core.hpp"

namespace WB
{

class Texture2D : public Asset
{
public:
    Texture2D() = default;
    Texture2D(uint32_t width, uint32_t height);

    enum class Filter : uint8_t
    {
        Nearest,
        Linear,
        Length
    };

    static SharedPtr<Texture2D> CreateTexture(uint32_t width, uint32_t height);
    static SharedPtr<Texture2D> CreateTexture(const Path& path);

    int32_t GetWidth() const { return m_width; }
    int32_t GetHeight() const { return m_height; }
    Filter GetFilter() const { return m_filter; }
    virtual uint32_t GetTextureID() const = 0;

    virtual void SetData(void* data, uint32_t size) = 0;
    virtual void Bind(uint32_t slot) = 0;
    WB_INLINE void SetFilter(Filter filter)
    {
        HandleFilterSwitch();
        m_filter = filter;
    }

protected:
    virtual void HandleFilterSwitch() = 0;

protected:
    int32_t m_width, m_height;
    unsigned char* m_data = nullptr;
    Filter m_filter = Filter::Linear;
};

}
