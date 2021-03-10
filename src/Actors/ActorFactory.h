#ifndef ZOMBIEGAME_ACTORFACTORY_H
#define ZOMBIEGAME_ACTORFACTORY_H

#include "Actor.h"
#include "Utilities/templates.h"

#include "Components/TestComponent.h"
#include "Components/RenderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/PhysicsComponent.h"

class ActorFactory
{
public:
    ActorFactory();
    virtual ~ActorFactory();

    std::shared_ptr<Actor> CreateActor(const char* actorResource, const glm::vec2* pInitialPosition, float angle = 0);
    virtual std::shared_ptr<ActorComponent> CreateComponent(tinyxml2::XMLElement* pData);

protected:
    GenericObjectFactory<ActorComponent, unsigned int> m_ComponentFactory;

private:
    unsigned int GetNextActorID() { ++m_LastActorID; return m_LastActorID; }
    unsigned int m_LastActorID;
};

#endif //ZOMBIEGAME_ACTORFACTORY_H
