#pragma once
#include "Core/Core.hpp"
#include "Core/AssetManager/Asset.hpp"
#include "entt/entt.hpp"

namespace WB
{

using EntityHandle = entt::entity;
class Scene3D : public Asset
{
public:
    Scene3D() = default;

    void BeginScene();
    void UpdateScene();
    void EndScene();

    WeakPtr<Scene3D> TransitionToNewPackage(const ScenePackage& packageToTranstion);
    void Clear();

    template<typename TComp>
    WB_INLINE bool Has(EntityHandle entityHandle) const
    {
        return m_registry.all_of<TComp>(entityHandle);
    }

    WB_INLINE bool Has(EntityHandle entityHandle) const
    {
        return m_registry.valid(entityHandle);
    }

    template<typename TComp>
    WB_INLINE const TComp& Get(EntityHandle entityHandle) const
    {
        return m_registry.get<TComp>(entityHandle);
    }

    template<typename TComp>
    WB_INLINE TComp& Get(EntityHandle entityHandle)
    {
        return m_registry.get<TComp>(entityHandle);
    }

    template<typename Task>
    void Each(Task&& task) const
    {
        for(EntityHandle entityHandle : m_registry.view<entt::entity>())
        {
            task(entityHandle);
        }
    }

    template<typename TComp, typename Task>
    void EntityView(Task&& task)
    {
        m_registry.view<TComp>().each(
            [this, &task](EntityHandle entity, auto& comp)
            {
                task(entity, comp);
            }
        );
    }

    template<typename TComp1, typename TComp2, typename Task>
    void EntityView(Task&& task)
    {
        m_registry.view<TComp1, TComp2>().each(
            [this, &task](EntityHandle entity, auto& comp1, auto& comp2)
            {
                task(entity, comp1, comp2);
            }
        );
    }

    class Entity CreateEntity();
    Entity CreateEntity(EntityHandle handle);
    void DestroyEntity(class Entity& entity);

    [[nodiscard]] WB_INLINE const entt::registry& GetRegistry() const { return m_registry; }
    WB_INLINE entt::registry& GetRegistry() { return m_registry; }

private:
    entt::registry m_registry;
};

}
