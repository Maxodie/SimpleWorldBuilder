#include "Core/Event/Event.hpp"

namespace WB::Event
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
        for(auto& listener : registry->Listeners)
        {
            listener.CallbackFuns(registry->Queue.front());
        }
        registry->Queue.pop();
    }

    ProcessTasks();
}

void EventDispatcher::ProcessTasks()
{
    while(!m_tasks.empty())
    {
        m_tasks.front().Fun();
        m_tasks.pop();
    }
}

}
