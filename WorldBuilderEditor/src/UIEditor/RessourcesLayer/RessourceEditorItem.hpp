#pragma once

#include "WorldBuilder.hpp"

namespace WB
{

class RessourceEditorItem
{
public:
    RessourceEditorItem(WeakPtr<class AssetMetaData>& metaData);

    virtual void Draw();
    virtual void Open() = 0;

protected:
    float m_itemWidth = 200, m_itemHeight = 200;
    WeakPtr<class AssetMetaData> m_metaData;
};

class RessourceEditorFile : public RessourceEditorItem
{
public:
    RessourceEditorFile(WeakPtr<class AssetMetaData>& metaData);
    virtual void Open() override;
};

class RessourceEditorFolder : public RessourceEditorItem
{
public:
    RessourceEditorFolder(WeakPtr<class AssetMetaData>& metaData, class RessourcesLayer& context);
    virtual void Open() override;

private:
    RessourcesLayer& m_context;
};

class RessourceEditorScene : public RessourceEditorItem
{
public:
    RessourceEditorScene(WeakPtr<class AssetMetaData>& metaData, class RessourcesLayer& context);
    virtual void Open() override;

private:
    RessourcesLayer& m_context;
};

}
