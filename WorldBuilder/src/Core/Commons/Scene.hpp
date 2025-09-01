#pragma once
#include "Core/Core.hpp"
#include "Core/Commons/Camera.hpp"
#include "Core/ECS/EcsComponent.hpp"

#include "entt/entt.hpp"

namespace WB
{

struct SceneData
{
    Camera* cam;
    std::vector<TransformComponent*> transforms;
};

class Scene3D
{
public:
    Scene3D(SceneData&  sceneData) : m_sceneData(sceneData){}
    WB_INLINE const SceneData& GetData() const { return m_sceneData; }

    void BeginScene();
    void UpdateScene();
    void EndScene();

    void PrepareScene();
    void RestoreScene();

    void CreateEntity();
    void DestroyEntity(class Entity& entity);

    WB_INLINE entt::registry& GetRegistry() { return m_registry; }

private:
    entt::registry m_registry;

    SceneData& m_sceneData;
    SceneData m_saveSceneData;
};

}
