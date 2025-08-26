#include "Core/AssetManager/AssetManagerBase.hpp"
#include "Core/Project.hpp"

namespace WB
{

SharedPtr<Asset> AssetManagerBase::GetAsset(AssetID id)
{
    return Project::GetActive()->GetAssetManager()->GetAsset(id);
}

}
