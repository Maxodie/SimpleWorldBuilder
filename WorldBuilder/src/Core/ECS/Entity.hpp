#pragma once

#include "Core/Commons/Scene.hpp"
#include "Core/Core.hpp"
#include "entt/entt.hpp"
namespace WB
{

class Entity
{
public:
    Entity(Scene3D& scene, EntityHandle handle) : m_scene(&scene), m_handle(handle) {}
    Entity() {}

    template<typename T, typename ... TArgs>
    T& AddComponent(TArgs&&... args)
    {
        return m_scene->GetRegistry().get_or_emplace<T>(m_handle, std::forward<TArgs>(args)...);
    }

    template<typename T>
    void RemoveComponent()
    {
        m_scene->GetRegistry().remove<T>(m_handle);
    }

    WB_INLINE EntityHandle GetHandle() { return m_handle; }

    WB_INLINE bool Exists() { return m_scene; }

    template<typename T>
    WB_INLINE T& Get() { return m_scene->GetRegistry().get<T>(m_handle); }

    template<typename T>
    WB_INLINE bool Has() { return m_scene && m_scene->GetRegistry().all_of<T>(m_handle); }

    WB_INLINE void Destroy() { m_scene->GetRegistry().destroy(m_handle); }

    WB_INLINE Entity& operator=(Entity& b)
    {
        m_scene = b.m_scene;
        m_handle = b.m_handle;
        return *this;
    }

private:
    Scene3D* m_scene;
    EntityHandle m_handle;
};

}
