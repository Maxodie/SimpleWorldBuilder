#pragma once
#include "WorldBuilder.hpp"
#include "UIEditor/Commons/WindowContextPopup.hpp"

namespace WB
{

using EntitySelectedCallback = std::function<void(Entity)>;
class HierarchyLayer : public Layer
{
public:
    HierarchyLayer(WeakPtr<Scene3D> scene);

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void SetOnEntitySelectedCallback(EntitySelectedCallback&& callback) { m_onEntitySelectedCallback = std::move(callback); }
    WB_INLINE void SetActiveScene(WeakPtr<Scene3D> scene) { m_scene = scene; }

private:
    WeakPtr<Scene3D> m_scene;
    EntitySelectedCallback m_onEntitySelectedCallback;

    WindowContextPopup m_windowContextPopup;
};

}
