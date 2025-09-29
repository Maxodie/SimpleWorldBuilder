#pragma once
#include "Core/Core.hpp"

namespace WB
{

using EventID = TypeIDptr;

enum class EventType
{
    KEYBOARD,
    MOUSE,
    WINDOW,
};

struct Event
{
};

template<typename TEvent>
struct EventListener
{
    using CallbackFun = std::function<void(const TEvent&)>;

    EventListener(EventID id, CallbackFun callbackFun)
        : ID(id), CallbackFuns(callbackFun)
    {

    }

    EventID ID;
    CallbackFun CallbackFuns;
};

template<typename TEvent>
struct EventRegistry
{
    std::queue<TEvent> Queue;
    std::vector<EventListener<TEvent>> Listeners;
};

class EventDispatcher
{
public:
    ~EventDispatcher();

    void PollEvent();

    template<typename TEvent, typename ... TArgs>
    void PostEvent(TArgs&&... args)
    {
        auto& registry = GetRegistry<TEvent>();

        if(!registry.Listeners.empty())
        {
            registry.Queue.emplace(std::forward<TArgs>(args)...);
            m_eventCallback(registry.Queue.front());
        }
        else
        {
            m_eventCallback(std::forward<TArgs>(args)...);
        }

    }

    template<typename TEvent, typename Callback>
    void PostCallback(Callback&& callback, EventID id)
    {
        auto listener = EventListener<TEvent>(id, std::move(callback));

        auto& registry = GetRegistry<TEvent>();
        registry.Listeners.push_back(std::move(listener));
    }

    template<typename TEvent>
    void EraseCallback(EventID id)
    {
        auto& registry = GetRegistry<TEvent>();
        registry.Listeners.erase(std::remove_if(
            [id](auto item)
            {
                return item->ID == id;
            }
        ));
    }

    template<typename TEvent>
    void EraseListner(EventID id)
    {
        for(auto& [_, registry] : m_registry)
        {
            CastRegistry<TEvent>(registry)->Listeners.erase(std::remove_if(
                [id](auto item)
                {
                    return item->ID == id;
                }
            ));
        }
    }

    template<typename TTask>
    void PostTask(TTask&& task)
    {
        m_tasks.push(std::move(task));
    }

    template<typename Callback>
    void SetOnEventCallback(Callback&& callback)
    {
        m_eventCallback = std::move(callback);
    }

private:
    void ProcessTasks();

    template<typename TEvent>
    EventRegistry<TEvent>* CastRegistry(void* ptr)
    {
        return static_cast<EventRegistry<TEvent>*>(ptr);
    }

    template<typename TEvent>
    EventRegistry<TEvent>& GetRegistry()
    {
        const auto registry = m_registry.find(GetTypeIDptr<TEvent>());
        if(registry != m_registry.end())
        {
            return *CastRegistry<TEvent>(registry->second);
        }

        const auto newRegistry = new EventRegistry<TEvent>();
        m_registry[GetTypeIDptr<TEvent>()] = newRegistry;
        return *newRegistry;
    }

private:
    std::queue<std::function<void()>> m_tasks;
    std::unordered_map<EventID, void*> m_registry;
    std::function<void(Event&)> m_eventCallback;
};


}
