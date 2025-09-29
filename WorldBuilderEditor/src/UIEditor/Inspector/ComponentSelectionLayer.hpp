#pragma once
#include "Core/ECS/TransformComponent.hpp"
#include "Core/Renderer/Model.hpp"
#include "WorldBuilder.hpp"

namespace WB
{

using ComponentSelectionLayerCallback = std::function<void(TypeID)>;

class ComponentSelectorLayer : public Layer
{
public:
    ComponentSelectorLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void SetSelectionCallback(ComponentSelectionLayerCallback&& callback) { m_selectionCallback = callback; }

private:
    ComponentSelectionLayerCallback m_selectionCallback;

    TypeID m_componentsID[1] = {
        GetTypeID<ModelComponent>(),
    };
};

}
