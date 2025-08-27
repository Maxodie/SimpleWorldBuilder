#pragma once
#include "Core/Core.hpp"

namespace WB
{
class Application;

class Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;

    virtual void Update() = 0;
    virtual void UpdateGUI() = 0;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

    WB_INLINE void SetID(TypeID id)
    {
        m_id = id;
    }

    void SetContext(Application* app);

    [[nodiscard]] WB_INLINE constexpr TypeID GetID()
    {
        return m_id;
    }

    [[nodiscard]] WB_INLINE constexpr Application* GetContext()
    {
        return m_context;
    }


private:
    TypeID m_id;
    Application* m_context;
};

class LayerStack
{
public:
    LayerStack(Application& app) : m_context(app) {}
    LayerStack() = delete;
    virtual ~LayerStack() = default;

    template<typename TLayer>
    SharedPtr<TLayer> GetLayer()
    {
        const auto layer = std::find_if(m_layers.begin(), m_layers.end(),
            [](const auto& layer)
            {
                return layer->GetID() == GetTypeID<TLayer>();
            }
        );

        if(layer != m_layers.end())
        {
            return static_pointer_cast<TLayer>(*layer);
        }
        return nullptr;
    }

    template<typename TLayer, typename ... TArgs>
    SharedPtr<TLayer> AddLayer(TArgs&&... args)
    {
        const SharedPtr<Layer> layer = GetLayer<TLayer>();

        if(layer)
        {
            CORE_LOG_WARNING("Trying to add an existing layer to the app");
            return nullptr;
        }

        SharedPtr<TLayer> createdLayer{ MakeShared<TLayer>(std::forward<TArgs>(args)...) };
        createdLayer->SetID(GetTypeID<TLayer>());
        createdLayer->SetContext(&m_context);
        createdLayer->OnAttach();
        m_layers.push_back(createdLayer);
        return createdLayer;
    }

    template<typename TLayer>
    void RemoveLayer()
    {
        m_layers.erase(std::remove_if(m_layers.begin(), m_layers.end(),
            [](const auto& layer)
            {
                bool isRemove = layer->GetID() == GetTypeID<TLayer>();
                if(isRemove)
                {
                    layer->OnDetach();
                }
                return isRemove;
            }
        ));
    }

    void ClearLayers()
    {
        for(auto layer = m_layers.rbegin(); layer != m_layers.rend(); layer++)
        {
            layer->get()->OnDetach();
        }

        m_layers.clear();
    }

    std::vector<SharedPtr<Layer>>& GetLayers()
    {
        return m_layers;
    }

private:
    std::vector<SharedPtr<Layer>> m_layers;
    Application& m_context;
};

}
