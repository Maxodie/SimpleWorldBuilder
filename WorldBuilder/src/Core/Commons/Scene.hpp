#pragma once
#include "Core/Core.hpp"
#include "Core/Commons/Camera.hpp"
#include "Core/ECS/EcsComponent.hpp"

namespace WB
{

struct SceneData
{
    Camera* cam;
    std::vector<TransformComponent*> transforms; //replace with ecs id or smt eventually
};

class Scene3D
{
public:
    WB_INLINE const SceneData* GetData() const { return m_sceneData; }
    WB_INLINE void SetData(SceneData& sceneData) { m_sceneData = &sceneData; }

    void BeginScene();
    void UpdateScene();
    void EndScene();

    void PrepareScene();
    void RestoreScene();

private:
    SceneData* m_sceneData;
    SceneData m_saveSceneData;
};

}
