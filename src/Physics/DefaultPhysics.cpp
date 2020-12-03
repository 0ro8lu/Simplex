#include "DefaultPhysics.h"

#include "Utilities/PrintUtils.h"

DefaultPhysics::DefaultPhysics() = default;

DefaultPhysics::~DefaultPhysics()
{
    for(auto & it : m_actorIDToRectangle)
    {
        delete it.second;
        it.second = nullptr;
    }

    m_actorIDToRectangle.clear();
}

bool DefaultPhysics::VInitialize()
{
    return true;
}

void DefaultPhysics::VSyncVisibleScene()
{

    for(auto & it : m_actorIDToRectangle)
    {
        unsigned int actorID = it.first;
        glm::mat4* physicsMat = it.second;

        StrongActorPtr pGameActor = std::shared_ptr<Actor>(g_pApp->GetGameLogic()->VGetActor(actorID));
        if(pGameActor && physicsMat)
        {
            auto* pTransformComponent = pGameActor->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());
            if(pTransformComponent)
            {
                glm::mat4 transform = pTransformComponent->GetTransform();
                if(transform != *physicsMat)
                {
                    pTransformComponent->SetTransform(*physicsMat);
                    ///TODO: send a Move_Actor Event.
                }
            }
            else
            {
                std::cout << "ERROR: DefaultPhysics::VSyncVisibleScene: actor " << actorID << " has no TransformComponent\n";
                return;
            }
        }
    }

    ///TODO: Check if actor has moved.
}

void DefaultPhysics::VOnUpdate()
{
    ///TODO: Step simulation.
}

void DefaultPhysics::VApplyForce(float verticalAcceleration, float horizontalAcceleration, unsigned int actorID)
{
    if(glm::mat4* physMat = FindPhysicsMatrix(actorID))
    {
        *physMat = glm::translate(*physMat, glm::vec3(horizontalAcceleration, verticalAcceleration, 0.0f));
        PrintUtils::printMat(*physMat);
    }
}

void DefaultPhysics::VAddBox(const glm::vec2& dimensions, StrongActorPtr actor)
{
    if(!actor)
    {
        std::cout << "ERROR! In DefaultPhysics VAddBox invalid actor pointer\n";
        return;
    }

    ///TODO: Check if actor already has a rigid body.

    glm::mat4 transform = glm::mat4(1.0f);
    auto* m_pTransformComponent = actor->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());

    if(!m_pTransformComponent)
    {
        std::cout << "ERROR!: In DefaultPhysics VAddBox actor " << actor->GetID() << " has no TransformComponent!\n";
        return;
    }

    transform = m_pTransformComponent->GetTransform();
    m_actorIDToRectangle[actor->GetID()] = new glm::mat4(transform);
}

void VAddCircle(float radius, const WeakActorPtr& actor)
{

}

void DefaultPhysics::VRemoveActor(unsigned int actorID)
{

}

void DefaultPhysics::VAddCircle(float radius, const WeakActorPtr& actor)
{

}

IGamePhysics* CreateDefaultGamePhysics()
{
    IGamePhysics* gamePhysics = new DefaultPhysics;

    if(gamePhysics && !gamePhysics->VInitialize())
    {
        delete gamePhysics;
        gamePhysics = nullptr;
    }

    return gamePhysics;
}

IGamePhysics* CreateNullPhysics()
{
    ///TODO: Implement NullGamePhysics.
    return nullptr;
}

glm::mat4* DefaultPhysics::FindPhysicsMatrix(unsigned int actorID)
{
    auto found = m_actorIDToRectangle.find(actorID);
    if(found != m_actorIDToRectangle.end())
        return found->second;

    return nullptr;
}
