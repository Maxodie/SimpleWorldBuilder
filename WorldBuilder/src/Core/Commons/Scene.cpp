#include "Core/Commons/Scene.hpp"
#include "Core/Renderer/Renderer3D.hpp"
#include "Core/Renderer/RenderCommand.hpp"

namespace WB
{

void Scene3D::BeginScene()
{
    RenderCommand::Clear();

    Renderer3D::BeginScene(*GetData());
}

void Scene3D::UpdateScene()
{

}

void Scene3D::EndScene()
{
    Renderer3D::EndScene();
}

void Scene3D::PrepareScene()
{
    if(m_saveSceneData.cam)
    {
        *m_saveSceneData.cam = *m_sceneData->cam;
    }
    else
    {
        m_saveSceneData.cam = new Camera(*m_sceneData->cam);
    }

    //TODO : make smt better for the transforms
    for(auto* tr : m_saveSceneData.transforms)
    {
        delete tr;
    }
    if(m_saveSceneData.transforms.size() != m_sceneData->transforms.size())
    {
        m_saveSceneData.transforms.resize(m_sceneData->transforms.size());
    }

    for(int i = 0; i < m_sceneData->transforms.size(); i++)
    {
        m_saveSceneData.transforms[i] = new TransformComponent();
        *m_saveSceneData.transforms[i] = *m_sceneData->transforms[i];
    }
}

void Scene3D::RestoreScene()
{
    *m_sceneData->cam = *m_saveSceneData.cam;
    for(int i = 0; i < m_sceneData->transforms.size(); i++)
    {
        *m_sceneData->transforms[i] = *m_saveSceneData.transforms[i];
    }
}

}
