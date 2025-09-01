#pragma once

#include "WorldBuilder.hpp"
namespace WB
{

class HierarchyLayer : public Layer
{
public:
    HierarchyLayer(SceneData& sceneData) : Layer(), m_sceneData(sceneData) {}

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

private:
    SceneData& m_sceneData;
};

}
