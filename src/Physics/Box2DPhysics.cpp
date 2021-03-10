#include "Box2DPhysics.h"
#include "Utilities/PrintUtils.h"

bool Box2DPhysics::VInitialize()
{
    std::cout << "Box2D Initialized!\n";

    b2Vec2 gravity(m_Gravity);
    m_pWorld = new b2World(gravity);

    if (!m_pWorld)
    {
        std::cout << "ERROR! In Box2DPhysics::VInitialize Box2D world failed to initialize\n";
        return false;
    }

    return true;
}

void Box2DPhysics::VSyncVisibleScene()
{
    for (auto& iterator : m_ActorIDToRigidBody)
    {
        unsigned int const id = iterator.first;

        b2Body const* const pActorBody = iterator.second;
        if (!pActorBody)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: actorBody of actor " << id
                      << " is invalid!\n";
            exit(2);
        }

        StrongActorPtr pGameActor = MakeStrongPtr(g_pApp->GetGameLogic()->VGetActor(id));
        if (!pGameActor)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: actor pointer " << id << " is invalid!\n";
            exit(2);
        }

        std::shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr(
                pGameActor->GetComponent<TransformComponent>(TransformComponent::GetComponentName()));

        std::shared_ptr<SpriteRenderComponent> pRenderComponent = MakeStrongPtr(
                pGameActor->GetComponent<SpriteRenderComponent>(SpriteRenderComponent::GetComponentName()));

        if (!pTransformComponent)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: transform component pointer of actor " << id
                      << " is invalid!\n";
            exit(2);
        }

        if (!pRenderComponent)
        {
            std::cout << "FATAL ERROR in Box2DPhysics::VSyncVisibleScene: render component pointer of actor " << id
                      << " is invalid!\n";
            exit(2);
        }

        glm::mat4& transform = pTransformComponent->GetTransform();
        glm::vec2 dimensions = pRenderComponent->GetSize();

        m_newXCoord = pActorBody->GetTransform().p.x * PPM;
        m_newYCoord = pActorBody->GetTransform().p.y * PPM;

        if (transform[3][0] != m_newXCoord || transform[3][1] != m_newYCoord)
        {
            transform[3][0] = m_newXCoord;
            transform[3][1] = m_newYCoord;
        }

        m_XScale = dimensions.x;
        m_YScale = dimensions.y;

        m_newX1Rot = m_XScale * pActorBody->GetTransform().q.c;
        m_newY1Rot = -m_YScale * (-pActorBody->GetTransform().q.s);
        m_newX2Rot = -m_XScale * pActorBody->GetTransform().q.s;
        m_newY2Rot = m_YScale * pActorBody->GetTransform().q.c;

        if (transform[0][0] != m_newX1Rot || transform[0][1] != m_newY1Rot
            || transform[1][0] != m_newX2Rot || transform[1][1] != m_newY2Rot)
        {
            transform[0][0] = m_newX1Rot;
            transform[0][1] = m_newY1Rot;
            transform[1][0] = m_newX2Rot;
            transform[1][1] = m_newY2Rot;
        }
    }
}

void Box2DPhysics::VOnUpdate()
{
    m_pWorld->Step((1.0f / 60.0f), 6, 2);
}

void Box2DPhysics::VAddBox(StrongActorPtr pActor, bool isStatic)
{
    ///TODO: Remove code duplication: This function is basically 95% the same code as the VAddBox in AABBPhysics. Find a better solution!

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

    if (!isStatic)
    {
        m_ActorIDToRigidBody[pActor->GetID()] = pBody;
    }
}

void Box2DPhysics::VAddCircle(float radius, StrongActorPtr pActor, bool isStatic)
{

}

void Box2DPhysics::VRemoveActor(unsigned int actorID)
{

}

void Box2DPhysics::VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID)
{
    b2Body* actorBox2DBody = FindBox2DRigidBody(actorID);

    if(actorBox2DBody)
    {
        actorBox2DBody->ApplyForceToCenter({dir.x * newtons, dir.y * newtons}, true);
    }
    else
    {
        std::cout << "ERROR in Box2DPhysics::VApplyForce: actorBox2DBody is an invalid pointer\n";
    }
}

void Box2DPhysics::VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID)
{

}

void Box2DPhysics::VSetPosition(unsigned int actorID, const glm::vec2& vec)
{
    b2Body* actorBox2DBody = FindBox2DRigidBody(actorID);

    if(actorBox2DBody)
        actorBox2DBody->SetTransform({vec.x / PPM, vec.y / PPM}, actorBox2DBody->GetAngle());
    else
        std::cout << "ERROR in Box2DPhysics::VSetPosition: actorBox2DBody is an invalid pointer\n";
}

void Box2DPhysics::VSetTransform(unsigned int actorID, const glm::mat4& mat)
{
    b2Body* actorBox2DBody = FindBox2DRigidBody(actorID);

    if(actorBox2DBody)
    {
        float angle = glm::atan(mat[0][1], mat[0][0]);
        actorBox2DBody->SetTransform({mat[3][0] / PPM, mat[3][1] / PPM}, angle);
    }
    else
    {
        std::cout << "ERROR in Box2DPhysics::VSetTransform: actorBox2DBody is an invalid pointer\n";
    }
}

void Box2DPhysics::VSetRotation(unsigned int actorID, float angle)
{
    b2Body* actorBox2DBody = FindBox2DRigidBody(actorID);

    if(actorBox2DBody)
        actorBox2DBody->SetTransform(actorBox2DBody->GetTransform().p, angle);
    else
        std::cout << "ERROR in Box2DPhysics::VSetRotation: actorBox2DBody is an invalid pointer\n";
}

b2Body* Box2DPhysics::FindBox2DRigidBody(unsigned int actorID) const
{
    for(auto& iterator : m_ActorIDToRigidBody)
    {
        if(iterator.first == actorID)
        {
            return iterator.second;
        }
    }
    return nullptr;
}


// ------- Defining extern functions -------

IGamePhysics* CreateNullPhysics()
{
    IGamePhysics* pGamePhysics = new NullGamePhysics;

    if (pGamePhysics)
        return pGamePhysics;

    return nullptr;
}
