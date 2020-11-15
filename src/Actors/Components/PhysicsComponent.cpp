#include "PhysicsComponent.h"

#include "Actors/Actor.h"
#include "TransformComponent.h"

PhysicsComponent::PhysicsComponent()
{
    m_horizontalAcceleration = 0;
    m_verticalAcceleration   = 0;
}

PhysicsComponent::~PhysicsComponent()
{

}

bool PhysicsComponent::VInit(tinyxml2::XMLElement *pData)
{
    ///TODO: Get GamePhysics from application.

    return true;
}

void PhysicsComponent::VPostInit()
{
    m_pTranformComponent = m_pOwner->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());

    if(!m_pTranformComponent)
    {
        std::cout << "ERROR: No TranformComponent in actor number " << m_pOwner->GetID() << "\n";
        return;
    }


}

tinyxml2::XMLElement *PhysicsComponent::VGenerateXml()
{
    return nullptr;
}

void PhysicsComponent::VUpdate()
{

    ///TODO: Set the transform only before rendering and just update variables here.
    ///TODO: Probably check if TransformComponent is a valid pointer, but kinda don't want to have an if condition every frame.

    m_pTranformComponent->GetTransform() = glm::translate(m_pTranformComponent->GetTransform(),
                                                          glm::vec3(m_horizontalAcceleration, m_verticalAcceleration, 0.0f));

    //m_pTranformComponent->SetXPosition(m_pTranformComponent->GetXPosition() + m_horizontalAcceleration);
    //m_pTranformComponent->SetYPosition(m_pTranformComponent->GetYPosition() + m_verticalAcceleration);
}

void PhysicsComponent::ApplyVerticalAcceleration(float acceleration)
{
    m_verticalAcceleration = acceleration;
}

void PhysicsComponent::ApplyHorizontalAcceleration(float acceleration)
{
    m_horizontalAcceleration = acceleration;
}
