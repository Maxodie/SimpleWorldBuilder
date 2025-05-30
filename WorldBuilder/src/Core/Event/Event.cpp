#include "Core/Event/Event.hpp"
#include "Core/Log/Log.hpp"

namespace WB
{

EventDispatcher::~EventDispatcher()
{
    for(auto& [_, ptr] : m_registry)
    {
        auto regitry  = CastRegistry<char>(ptr);
        WB_DELETE(regitry);
    }
}

void EventDispatcher::PollEvent()
{
    for(auto& [_, registryPtr] : m_registry)
    {
        auto registry = CastRegistry<char>(registryPtr);
        while(!registry->Queue.empty())
        {
            for(auto& listener : registry->Listeners)
            {
                listener.CallbackFuns(registry->Queue.front());
            }
            registry->Queue.pop();
        }
    }

    ProcessTasks();
}

void EventDispatcher::ProcessTasks()
{
    while(!m_tasks.empty())
    {
        m_tasks.front()();
        m_tasks.pop();
    }
}

}
