#include "PhysicsComponent.h"

#include "Actors/Actor.h"
#include "TransformComponent.h"
#include "Model/IApplication.h"

PhysicsComponent::PhysicsComponent()
{
    m_horizontalAcceleration = 0.0f;
    m_verticalAcceleration = 0.0f;

    m_pGamePhysics = nullptr;
    m_pTransformComponent = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{

}

bool PhysicsComponent::VInit(tinyxml2::XMLElement *pData)
{
    m_pGamePhysics = g_pApp->GetGameLogic()->VGetGamePhysics();

    if (!m_pGamePhysics)
    {
        std::cout << "PhysicsComponent ERROR: No valid IGamePhysics Pointer!\n";
        return false;
    }

    tinyxml2::XMLElement *pAttributes = pData->FirstChildElement("Shape");

    if (!pAttributes)
    {
        std::cout << "ERROR!: Could not find attribute Shape in PhysicsComponent\n";
        return false;
    }

    m_pShape = pAttributes->GetText();

    pAttributes = pData->FirstChildElement("Type");

    if (!pAttributes)
    {
        std::cout << "ERROR!: Could not find attribute Type in PhysicsComponent\n";
        return false;
    }

    m_pType = pAttributes->GetText();

    return true;
}

void PhysicsComponent::VPostInit()
{

    if (!m_pOwner)
    {
        std::cout << "PhysicsComponent ERROR: Invalid Owner \n";
        return;
    }

    bool isStatic;
    if (strcmp(m_pType, "Static") == 0)
    {
        isStatic = true;
    } else if (strcmp(m_pType, "Dynamic") == 0)
    {
        isStatic = false;
    } else
    {
        std::cout << "ERROR!: Unsupported physics tyoe " << m_pType << " for PhysicsComponent in actor "
                  << m_pOwner->GetID() << "\n";
        return;
    }


    if (strcmp(m_pShape, "Box") == 0)
    {
        m_pGamePhysics->VAddBox(m_pOwner, isStatic);

    } else if (strcmp(m_pShape, "Circle") == 0)
    {
        ///TODO: Let physics system add a circle.
    } else
    {
        std::cout << "ERROR!: Unsupported shape type " << m_pShape << " for PhysicsComponent in actor "
                  << m_pOwner->GetID() << "\n";
    }

    m_pTransformComponent = m_pOwner->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());

    if (!m_pTransformComponent)
    {
        std::cout << "PhysicsComponent ERROR: No TranformComponent in actor number " << m_pOwner->GetID() << "\n";
        return;
    }
}

tinyxml2::XMLElement *PhysicsComponent::VGenerateXml()
{
    return nullptr;
}

/*void PhysicsComponent::VUpdate()
{

    ///TODO: Set the transform only before rendering and just update variables here.
    ///TODO: Probably check if TransformComponent is a valid pointer, but kinda don't want to have an if condition every frame.

    m_pTransformComponent->GetTransform() = glm::translate(m_pTransformComponent->GetTransform(),
                                                           glm::vec3(m_horizontalAcceleration, m_verticalAcceleration,
                                                                    0.0f));

    //m_pTransformComponent->SetXPosition(m_pTransformComponent->GetXPosition() + m_horizontalAcceleration);
    //m_pTransformComponent->SetYPosition(m_pTransformComponent->GetYPosition() + m_verticalAcceleration);
}*/

void PhysicsComponent::VUpdate()
{
    if (m_verticalAcceleration != 0.0f || m_horizontalAcceleration != 0.0f)
    {
        ///TODO: Why the hell should i pass an ID, and then look for the actor inside the physics system when i can just pass an ActorPtr.
        ///I could have a map of <Actor*, Rectangle*> instead of <unsigned int, Rectangle*> difference between unsigned int and Actor* in terms
        ///of bytes should be minimal, so why waste CPU time?
        m_pGamePhysics->VApplyForce({m_horizontalAcceleration, m_verticalAcceleration}, 2000, m_pOwner->GetID());
    }

}

void PhysicsComponent::ApplyVerticalAcceleration(float acceleration)
{
    m_verticalAcceleration = acceleration;
}

void PhysicsComponent::ApplyHorizontalAcceleration(float acceleration)
{
    m_horizontalAcceleration = acceleration;
}
