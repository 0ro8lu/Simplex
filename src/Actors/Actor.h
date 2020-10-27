#ifndef ZOMBIEGAME_ACTOR_H
#define ZOMBIEGAME_ACTOR_H

#include <iostream>
#include <string>
#include <map>

#include "ActorComponent.h"

class Actor;

typedef std::weak_ptr<Actor> WeakActorPtr;
typedef std::shared_ptr<Actor> StrongActorPtr;
const unsigned int INVALID_ACTOR_ID = 0;

typedef std::string ActorType;

class Actor
{
    friend class ActorFactory;

public:
    explicit Actor(unsigned int id);
    ~Actor();

    bool Init(tinyxml2::XMLElement* pData);
    void PostInit();
    void Destroy();
    void Update();

    unsigned int GetID() const { return m_ID; }
    std::string GetType() const { return m_Type; }

    ///TODO: change this to be a normal pointer.
    template<class ComponentType>
    std::weak_ptr<ComponentType> GetComponent(const char* componentName)
    {
        unsigned int componentID = ActorComponent::GetIDFromName(componentName);

        auto it = m_Components.find(componentID);
        if(it != m_Components.end())
        {
            ///TODO: Refactor this code, it really fucking sucks.
            std::shared_ptr<ActorComponent> pBase(it->second);
            std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
            std::weak_ptr<ComponentType> pWeakSub(pSub);
            return pWeakSub;
        }
        else
        {
            return std::weak_ptr<ComponentType>();
        }
    }

    template<class ComponentType>
    ComponentType* GetComponentRaw(const char* componentName)
    {
        unsigned int componentID = ActorComponent::GetIDFromName(componentName);

        auto it = m_Components.find(componentID);
        if (it != m_Components.end())
        {
            ///TODO: Refactor this code, it really fucking sucks.
            std::shared_ptr<ActorComponent> pBase(it->second);
            std::shared_ptr<ComponentType> pSub(std::static_pointer_cast<ComponentType>(pBase));
            ComponentType *pWeakSub = pSub.get();
            return pWeakSub;
        } else
        {
            return nullptr;
        }
    }

    const std::map<unsigned int, std::shared_ptr<ActorComponent>>* GetComponents() const { return &m_Components; }
    void AddComponent(const std::shared_ptr<ActorComponent>& pComponent);

private:
    unsigned int m_ID;
    const char* m_Type;
    const char* m_Resource;
    std::map<unsigned int, std::shared_ptr<ActorComponent>> m_Components;
};

#endif //ZOMBIEGAME_ACTOR_H
