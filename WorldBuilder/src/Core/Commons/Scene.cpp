#include "Core/Commons/Scene.hpp"
#include "Core/Commons/Camera.hpp"
#include "Core/Log/Log.hpp"
#include "Core/Project.hpp"
#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/ECS/Entity.hpp"
#include "Core/Serializer/SceneSerializer.hpp"

namespace WB
{

void Scene3D::BeginScene()
{
    RenderCommand::Clear();

    EntityView<Camera, TransformComponent>(
        [&](auto entity, Camera& cam, TransformComponent& transform)
        {
            transform.UpdateModelMatrix();
            cam.UpdateViewMatrix(transform);
            Renderer3D::BeginScene(cam, transform);
        });
}

void Scene3D::UpdateScene()
{
    EntityView<ModelComponent, TransformComponent>(
        [&](auto entity, ModelComponent& model, TransformComponent& transform)
        {
            transform.UpdateModelMatrix();
            Renderer3D::DrawModel(model, transform);
        });
}

void Scene3D::EndScene()
{
    Renderer3D::EndScene();
}

void Scene3D::Clear()
{
    // Project::GetActive()->GetAssetManager()->ClearRegistry();
    // searching throw entity view will not work correctly because it will still be referenced
    EntityView<ModelComponent>(
        [&](EntityHandle handle, ModelComponent& model)
        {
            if(model.asset.lock())
            {
                 Project::GetActive()->GetAssetManager()->UnloadAsset(model.asset.lock()->id);
            }
        }
    );

    m_registry.clear();
    Project::GetActive()->GetAssetManager()->UnloadAsset(id);
    CORE_LOG_DEBUG("Scene asset %zu has been cleared", id);
}

WeakPtr<Scene3D> Scene3D::TransitionToNewPackage(AssetID newSceneID)
{
    if(newSceneID == id)
    {
        return {};
    }

    WeakPtr<Scene3D> sceneAsset = Project::GetActive()->GetAssetManager()->GetAsset<Scene3D>(newSceneID);

    if(!sceneAsset.lock())
    {
        CORE_LOG_ERROR("Invalid given scene asset id");
        return {};
    }

    CORE_LOG_DEBUG("Scene asset %zu has been loaded", newSceneID);

    EntityView<ModelComponent>(
        [&](EntityHandle handle, ModelComponent& modelBase)
        {
            bool toBeUnload = true;
            sceneAsset.lock()->EntityView<ModelComponent>(
                [&](EntityHandle handle, ModelComponent& model)
                {
                    if(modelBase.asset.lock()->id == model.asset.lock()->id)
                    {
                        toBeUnload = false;
                        return;
                    }
                }
            );

            if(toBeUnload)
            {
                Project::GetActive()->GetAssetManager()->UnloadAsset(modelBase.asset.lock()->id);
            }
        }
    );

    Project::GetActive()->GetAssetManager()->UnloadAsset(id);
    CORE_LOG_DEBUG("Scene asset %zu has been cleared", id);

    return sceneAsset;
}

void Scene3D::PrepareScene()
{

}

void Scene3D::RestoreScene()
{
}

Entity Scene3D::CreateEntity()
{
    EntityHandle handle = m_registry.create();
    return {*this, handle};
}

Entity Scene3D::CreateEntity(EntityHandle handle)
{
    EntityHandle finalHandle = m_registry.create(handle);

    if(handle != finalHandle)
    {
        CORE_LOG_ERROR("scene entity handle is already used, a new one is created : given %zu, new %zu", handle, finalHandle);
    }

    return {*this, finalHandle};
}

void Scene3D::DestroyEntity(Entity& entity)
{
    m_registry.destroy(entity.GetHandle());
}

}
