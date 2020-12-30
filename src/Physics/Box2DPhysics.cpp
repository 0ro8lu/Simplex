#include "Box2DPhysics.h"

bool Box2DPhysics::VInitialize()
{
    std::cout << "Box2D Initialized!\n";

    b2Vec2 gravity(0.0f, -10.0f);
    m_pWorld = new b2World(gravity);

    if(!m_pWorld)
    {
        std::cout << "ERROR! In Box2DPhysics::VInitialize Box2D world failed to initialize\n";
        return false;
    }

    return true;
}

void Box2DPhysics::VSyncVisibleScene()
{
    for(auto& iterator : m_ActorIDToRigidBody)
    {
        unsigned int const id = iterator.first;

        b2Body const* const pActorBody = iterator.second.first;
        if(!pActorBody)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: actorBody of actor " << id << " is invalid!\n";
            exit(2);
        }

        StrongActorPtr pGameActor = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(id));
        if(!pGameActor)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: actor pointer " << id << " is invalid!\n";
            exit(2);
        }

        std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pGameActor->GetComponent<TransformComponent>(TransformComponent::GetComponentName()));
        if(!pTransformComponent)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: transform component pointer of actor " << id << " is invalid!\n";
            exit(2);
        }

        glm::mat4 transform = pTransformComponent->GetTransform();
        if(transform[3][0] != pActorBody->GetPosition().x || transform[3][1] != pActorBody->GetPosition().y)
        {
            //transform[3][0] = pActorBody->GetPosition().x
        }
    }
}

void Box2DPhysics::VOnUpdate()
{
    m_pWorld->Step((1.0f / 60.0f), 6, 2);
}

void Box2DPhysics::VAddBox(const glm::vec2& dimensions, StrongActorPtr pActor)
{
    if(!pActor)
    {
        std::cout << "ERROR!: In Box2DPhysics::VAddBox could not convert weakActor to strongActor\n";
        return;
    }

    std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::GetComponentName()));
    glm::mat4 transform = pTransformComponent->GetTransform();

    b2BodyDef bodyDef;
    b2Body* pBody;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(transform[3][0] / PPM, transform[3][1] / PPM);
    pBody = m_pWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(transform[0][0] / 2 / PPM, transform[1][1] / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    pBody->CreateFixture(&fixtureDef);

    m_ActorIDToRigidBody[pActor->GetID()] = std::pair(pBody, glm::vec2(transform[0][0], transform[1][1]));
}

void Box2DPhysics::VAddCircle(float radius, StrongActorPtr pActor)
{

}

void Box2DPhysics::VRemoveActor(unsigned int actorID)
{

}

void Box2DPhysics::VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID)
{

}

void Box2DPhysics::VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID)
{

}


// ------- Defining extern functions -------


IGamePhysics* CreateGamePhysics()
{
    IGamePhysics* pGamePhysics = new Box2DPhysics;

    if(pGamePhysics)
    {
        if(!pGamePhysics->VInitialize())
        {
            delete pGamePhysics;
            pGamePhysics = nullptr;
        }
        return pGamePhysics;
    }
    return nullptr;
}

IGamePhysics* CreateNullPhysics()
{
    IGamePhysics* pGamePhysics = new NullGamePhysics;

    if(pGamePhysics)
        return pGamePhysics;

    return nullptr;
}
