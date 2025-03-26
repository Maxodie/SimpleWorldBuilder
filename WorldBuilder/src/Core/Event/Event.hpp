#pragma once
#include "Core/Core.hpp"

namespace WB::Event
{

using EventID = TypeID;

enum class EventType
{
    KEYBOARD,
    MOUSE,
    WINDOW,
};

struct Task
{
    std::function<void()> Fun;
};

template<typename Event>
struct EventListener
{
    using CallbackFun = std::function<void(const Event&)>;

    EventListener(EventID id, CallbackFun callbackFun)
        : ID(id), CallbackFuns(callbackFun)
    {

    }

    EventID ID;
    CallbackFun CallbackFuns;
};

template<typename Event>
struct EventRegistry
{
    std::queue<Event> Queue;
    std::vector<EventListener<Event>> Listeners;
};

class EventDispatcher
{
public:
    ~EventDispatcher();

    void PollEvent();

    template<typename Event, typename ... TArgs>
    void PostEvent(TArgs&&... args)
    {
        auto& registry = GetRegistry<Event>();
        registry.Queue.queue((std::forward<TArgs>(args), ...));
    }

    template<typename Event, typename Callback>
    void PostCallback(Callback&& callback, EventID id)
    {
        auto& registry = GetRegistry<Event>();
        registry.Listeners.emplace_back(id, callback);
    }

    template<typename Event>
    void EraseCallback(EventID id)
    {
        auto& registry = GetRegistry<Event>();
        registry.Listeners.erase(std::remove_if(
            [id](auto item)
            {
                return item->ID == id;
            }
        ));
    }

    template<typename Event>
    void EraseListner(EventID id)
    {
        for(auto& [_, registry] : m_registry)
        {
            CastRegistry<Event>(registry)->Listeners.erase(std::remove_if(
                [id](auto item)
                {
                    return item->ID == id;
                }
            ));
        }
    }

    template<typename ... TArgs>
    void PostTask(TArgs&&... args)
    {
        m_tasks.emplace((std::forward<TArgs>(args), ...));
    }

private:
    void ProcessTasks();

    template<typename Event>
    EventRegistry<Event>* CastRegistry(void* ptr)
    {
        return static_cast<EventRegistry<Event>*>(ptr);
    }

    template<typename Event>
    EventRegistry<Event>& GetRegistry()
    {
        const auto registry = m_registry.find(GetTypeID<Event>());
        if(registry != m_registry.end())
        {
            return *registry;
        }

        auto newRegistry = new EventRegistry<Event>();
        m_registry[GetTypeID<Event>()] = newRegistry;
        return newRegistry;
    }

private:
    std::queue<Task> m_tasks;
    std::unordered_map<EventID, void*> m_registry;
};


}
