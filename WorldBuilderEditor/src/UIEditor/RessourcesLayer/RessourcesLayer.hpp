#pragma once
#include "WorldBuilder.hpp"

namespace WB
{

class RessourcesLayer : public Layer
{
public:
    RessourcesLayer();

    virtual void Update() override;
    virtual void UpdateGUI() override;
    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void ChangeDirectory(const Path& path);
    void UpdateFile(const Path& metaPath, AssetID assetID);

private:
    void TryAddItem(AssetID assetID);

private:
    Path m_currentViewPath;
    std::vector<SharedPtr<class RessourceEditorItem>> m_items;
};

}
