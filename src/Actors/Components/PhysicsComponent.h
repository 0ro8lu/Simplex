#ifndef ZOMBIEGAME_PHYSICSCOMPONENT_H
#define ZOMBIEGAME_PHYSICSCOMPONENT_H

#include "TransformComponent.h"

class PhysicsComponent : public ActorComponent
{
public:

    bool VInit(tinyxml2::XMLElement *pData) override;
    tinyxml2::XMLElement *VGenerateXml() override;
    const char *VGetComponentName() const override { return GetComponentName(); }
    void VUpdate() override;
    void VPostInit() override;

    static const char* GetComponentName() { return "PhysicsComponent"; }

    void ApplyVerticalAcceleration(float acceleration);
    void ApplyHorizontalAcceleration(float acceleration);

private:
    TransformComponent* m_pTranformComponent;
    float m_horizontalAcceleration;
    float m_verticalAcceleration;
};

#endif //ZOMBIEGAME_PHYSICSCOMPONENT_H
