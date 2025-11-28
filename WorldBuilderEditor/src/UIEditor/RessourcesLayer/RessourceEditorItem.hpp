#pragma once

#include "WorldBuilder.hpp"
#include "imgui.h"

namespace WB
{

class RessourceEditorItem
{
public:
    RessourceEditorItem(WeakPtr<class AssetMetaData> metaData, class RessourcesLayer& context);

    virtual void Draw();
    virtual void Open() = 0;

    WB_INLINE const ImVec2& GetSize() const { return m_itemSize; }

protected:
    ImVec2 m_itemSize { 200, 200 };
    WeakPtr<class AssetMetaData> m_metaData;
    WeakPtr<Texture2D> m_icon;
    ImVec2 m_uv0{0, 0}, m_uv1{1, 1};
    RessourcesLayer& m_context;
};

class RessourceEditorFile : public RessourceEditorItem
{
public:
    RessourceEditorFile(WeakPtr<class AssetMetaData> metaData, class RessourcesLayer& context);
    virtual void Open() override;
};

class RessourceEditorFolder : public RessourceEditorItem
{
public:
    RessourceEditorFolder(WeakPtr<class AssetMetaData> metaData, class RessourcesLayer& context);
    virtual void Open() override;

};

class RessourceEditorScene : public RessourceEditorItem
{
public:
    RessourceEditorScene(WeakPtr<class AssetMetaData> metaData, class RessourcesLayer& context);
    virtual void Open() override;
};

}
