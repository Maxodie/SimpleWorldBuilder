#pragma once

#include "Core/Commons/Scene.hpp"
#include "Core/Core.hpp"
#include "entt/entt.hpp"
namespace WB
{

using EntityHandle = entt::entity;

class Entity
{
public:
    Entity() = delete;
    Entity(Scene3D& scene, EntityHandle handle) : m_scene(scene), m_handle(handle) {}

    template<typename T, typename ... TArgs>
    void AddComponent(TArgs&&... args)
    {
        m_scene.GetRegistry().emplace<T>(m_handle, std::forward(args...));
    }

    template<typename T>
    void RemoveComponent()
    {
        m_scene.GetRegistry().remove<T>(m_handle);
    }

    WB_INLINE EntityHandle GetHandle() { return m_handle; }

private:
    entt::entity m_handle;
    Scene3D& m_scene;
};

}
