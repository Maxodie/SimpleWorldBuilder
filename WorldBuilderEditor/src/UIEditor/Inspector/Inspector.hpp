#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class InspectorLayer : public Layer
{
public:
    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void SetCurrentEntity(Entity& handle) { m_currentEntity = handle; }

private:
    Entity m_currentEntity;
};

}
