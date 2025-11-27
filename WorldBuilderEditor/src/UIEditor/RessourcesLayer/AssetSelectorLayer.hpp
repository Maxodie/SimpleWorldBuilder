#pragma once
#include "Core/AssetManager/Asset.hpp"
#include "WorldBuilder.hpp"

namespace WB
{
using AssetSelectionLayerCallback = std::function<void(AssetID)>;

class AssetSelectorLayer : public Layer
{
public:
    AssetSelectorLayer(AssetType type);
    AssetSelectorLayer() = delete;

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    WB_INLINE void SetSelectionCallback(AssetSelectionLayerCallback&& callback) { m_selectionCallback = callback; }

private:
    void HandleAssetSelector(const std::string& name, AssetID id);

private:
    AssetType m_type;
    AssetSelectionLayerCallback m_selectionCallback;
};

}
