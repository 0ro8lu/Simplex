#include "EventManager.h"

EventManager* EventManager::m_EventManager;

EventManager::EventManager()
{
    m_EventManager = this;
}

EventManager::~EventManager()
= default;

void EventManager::registerDelegate(const std::string& name, void (*Function)(const EventPointer& pEvent))
{
    m_DelegateMap[name].push_back(new FunctionDelegate(Function));
}

bool EventManager::unregisterDelegate(const std::string &name, void (*Function)(const EventPointer &))
{
    auto findIt = m_DelegateMap.find(name);

    if(findIt == m_DelegateMap.end())
    {
        std::cout << "ERROR: Trying to remove a non-existing delegate!\n";
        return false;
    }

    Delegates& delegates = findIt->second;

    for(auto it = delegates.begin(); it != delegates.end(); it++)
    {
        if(dynamic_cast<FunctionDelegate*>(*it)->p_FunctionPointer == Function)
        {
            delegates.erase(it);
            std::cout << "Succesfully removed event delegate\n";
            break;
        }
    }
    return true;
}

void EventManager::triggerEvent(const EventPointer& pEvent)
{
    auto const it = m_DelegateMap.find(pEvent->Name());
    if(it == m_DelegateMap.end()) { return; }

    Delegates& delegates = it->second;

    for(auto & delegate : delegates)
    {
        delegate->invoke(pEvent);
    }
}
