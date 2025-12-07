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

    WB_INLINE Entity& GetSelectedEntity() { return m_currentEntity; }

    WB_INLINE void SetCurrentEntity(Entity& handle)

    {
        RemoveAsset();
        m_currentEntity = handle;
    }

    WB_INLINE void SetCurrentAsset(SharedPtr<AssetMetaData> metadata)
    {
        RemoveEntity();
        m_metaData = metadata;
    }

    WB_INLINE void RemoveEntity() { m_currentEntity = Entity{}; }
    WB_INLINE void RemoveAsset() { m_metaData = {}; }

private:
    Entity m_currentEntity;
    SharedPtr<AssetMetaData> m_metaData;
};

}
