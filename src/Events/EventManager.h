#ifndef ZOMBIEGAME_EVENTMANAGER_H
#define ZOMBIEGAME_EVENTMANAGER_H

#include <vector>
#include <unordered_map>
#include <iostream>

#include "MemberDelegate.h"
#include "FunctionDelegate.h"

class EventManager
{
    typedef std::vector<IDelegate*> Delegates;

public:
    EventManager();
    virtual ~EventManager();

    template<typename T>
    void registerMemberDelegate(const std::string& name, T* obj, void (T::*Function)(const EventPointer& pEvent))
    {
        m_DelegateMap[name].push_back(new MemberDelegate<T>(obj, Function));
    }

    template <typename T>
    bool unregisterMemberDelegate(const std::string& name, void (T::*Function)(const EventPointer& pEvent))
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
            if(static_cast<MemberDelegate<T>*>(*it)->p_FunctionPointer == Function)
            {
                delegates.erase(it);
                delete (*it);
                std::cout << "Succesfully removed event delegate\n";
                break;
            }
        }
        return true;
    }

    void registerDelegate(const std::string& name, void (*Function)(const EventPointer& pEvent));
    bool unregisterDelegate(const std::string& name, void (*Function)(const EventPointer& pEvent));

    void triggerEvent(const EventPointer& pEvent);

    static EventManager* Get() { return m_EventManager; }

private:
    static EventManager* m_EventManager;
    mutable std::unordered_map<std::string, Delegates> m_DelegateMap;
};

#endif //ZOMBIEGAME_EVENTMANAGER_H
