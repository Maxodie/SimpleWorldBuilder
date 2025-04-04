#pragma once
#include "Core/Core.hpp"

namespace WB
{

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void Update() = 0;
    virtual void UpdateGUI() = 0;
    virtual void OnAttach() = 0;
    virtual void OnDettach() = 0;

    WB_INLINE void SetID(TypeID id)
    {
        m_id = id;
    }

    [[nodiscard]] WB_INLINE constexpr TypeID GetID()
    {
        return m_id;
    }

private:
    TypeID m_id;
};

class LayerStack
{
public:
    virtual ~LayerStack() = default;

    template<typename TLayer>
    TLayer* GetLayer()
    {
        const auto layer = std::find_if(m_layers.begin(), m_layers.end(),
            [](const auto layer)
            {
                return layer->GetID() == GetTypeID<TLayer>();
            }
        );

        if(layer != m_layers.end())
        {
            return static_cast<TLayer*>(*layer);
        }
        return nullptr;
    }

    template<typename TLayer, typename ... TArgs>
    void AddLayer(TArgs&&... args)
    {
        const Layer* layer = GetLayer<TLayer>();

        if(layer)
        {
            CORE_LOG_WARNING("Trying to add an existing layer to the app");
            return;
        }

        TLayer* createdLayer{ new TLayer(std::forward<TArgs>(args)...)};
        createdLayer->SetID(GetTypeID<TLayer>());
        createdLayer->OnAttach();
        m_layers.push_back(createdLayer);
    }

    template<typename TLayer>
    void RemoveLayer()
    {
        m_layers.erase(std::remove_if(m_layers.begin(), m_layers.end(),
            [](const auto layer)
            {
                bool isRemove = layer->GetID() == GetTypeID<TLayer>();
                if(isRemove)
                {
                    layer->OnDettach();
                }
                return isRemove;
            }
        ));
    }

    void ClearLayers()
    {
        for(size_t i = 0; i < m_layers.size(); i++)
        {
            m_layers.front()->OnDettach();
            WB_DELETE(m_layers.front());
        }

        m_layers.clear();
    }

    std::vector<Layer*>& GetLayers()
    {
        return m_layers;
    }

private:
    std::vector<Layer*> m_layers;
};

}
