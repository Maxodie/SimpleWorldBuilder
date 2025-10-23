#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/AssetManagerBase.hpp"

namespace WB
{

class RuntimeAssetManager : public AssetManagerBase
{
public:
    virtual WeakPtr<Asset> GetAsset(AssetID id) override;

private:
    std::vector<AssetID> m_packages;
    //aoivr un registry pour lier des buildindex/AssetID a des fichier package
    //et quand on GetAsset si c'est une scene assetType on load le fichier package
    //
    //import package et un package list lié a un id de scene et quand il tombe sur l'id de scene qui n'est pas load boum
};

}
