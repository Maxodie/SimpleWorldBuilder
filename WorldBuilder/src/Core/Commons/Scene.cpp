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
    EntityView<Asset>(
        [&](EntityHandle handle, Asset& asset)
        {
            CORE_LOG_DEBUG("asset unloaded : %zu", handle);
            Project::GetActive()->GetAssetManager()->UnloadAsset(asset.id);
        }
    );

    m_registry.clear();
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
