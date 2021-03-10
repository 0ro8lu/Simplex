#include "AABBPhysics.h"

bool AABBPhysics::VInitialize()
{
    m_Gravity = {0.0f, 0.0f};
    return Box2DPhysics::VInitialize();
}

void AABBPhysics::VAddBox(StrongActorPtr pActor, bool isStatic)
{
    ///TODO: Remove code duplication: This function is basically 95% the same code as the VAddBox in Box2DPhysics. Find a better solution!

    if (!pActor)
    {
        std::cout << "ERROR!: In Box2DPhysics::VAddBox could not convert weakActor to strongActor\n";
        return;
    }

    std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(
            pActor->GetComponent<TransformComponent>(TransformComponent::GetComponentName()));
    std::shared_ptr<SpriteRenderComponent> pRenderComponent = MakeStrongPtr(
            pActor->GetComponent<SpriteRenderComponent>(SpriteRenderComponent::GetComponentName()));

    glm::mat4 transform = glm::mat4(1.0f);
    if (pTransformComponent && pRenderComponent)
    {
        transform = pTransformComponent->GetTransform();
    } else
    {
        std::cout << "ERROR! In Box2DPhysics::VAddBox Invalid Transform or Render component\n";
        return;
    }

    b2BodyDef bodyDef;
    b2Body* pBody;

    if (isStatic)
        bodyDef.type = b2_staticBody;
    else
        bodyDef.type = b2_dynamicBody;

    float angle = glm::atan(transform[0][1], transform[0][0]);

    bodyDef.angle = angle;
    bodyDef.position.Set(transform[3][0] / PPM, transform[3][1] / PPM);
    pBody = m_pWorld->CreateBody(&bodyDef);

    b2PolygonShape physicsBox;
    glm::vec2 dimensions = pRenderComponent->GetSize();
    physicsBox.SetAsBox(dimensions.x / 2 / PPM, dimensions.y / 2 / PPM);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &physicsBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    pBody->CreateFixture(&fixtureDef);
    pBody->SetFixedRotation(true);

    pBody->SetAngularDamping(3);
    pBody->SetLinearDamping(3);

    if (!isStatic)
    {
        m_ActorIDToRigidBody[pActor->GetID()] = pBody;
    }
}

IGamePhysics* CreateAABBPhysics()
{
    IGamePhysics* pGamePhysics = new AABBPhysics;

    if (pGamePhysics)
    {
        if (!pGamePhysics->VInitialize())
        {
            delete pGamePhysics;
            pGamePhysics = nullptr;
        }
        return pGamePhysics;
    }
    return nullptr;
}
