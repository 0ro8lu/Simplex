#ifndef ZOMBIEGAME_TRANSFORMCOMPONENT_H
#define ZOMBIEGAME_TRANSFORMCOMPONENT_H

#include "Actors/ActorComponent.h"

#include <iostream>
#include "gtc/matrix_transform.hpp"
#include "Utilities/PrintUtils.h"

class TransformComponent : public ActorComponent
{

public:
    bool VInit(tinyxml2::XMLElement *pData) override;
    const char *VGetComponentName() const override { return GetComponentName();}
    static const char* GetComponentName() { return "TransformComponent"; }

    tinyxml2::XMLElement *VGenerateXml() override { return nullptr; }

    glm::mat4& GetTransform() { return m_Transform; }
    void       SetTransform(glm::mat4 transform) { m_Transform = transform; }

    glm::vec3 GetPositionNew() const { return m_Transform[3]; }
    void      SetPositionNew(glm::vec3 position) { m_Transform = glm::translate(m_Transform, position); } ///TODO: Implement this.

    float GetXPosition()    const { return m_Position.x; }
    float GetYPosition()    const { return m_Position.y; }
    glm::vec2 GetPosition() const { return m_Position; }

    void SetXPosition(float xPos)        { m_Position.x = xPos; }
    void SetYPosition(float yPos)        { m_Position.y = yPos; }
    void SetPosition(glm::vec2 position) { m_Transform[3][0] = position[0]; m_Transform[3][1] = position[1]; }

private:
    glm::vec2 m_Position;
    glm::mat4 m_Transform;
};

#endif //ZOMBIEGAME_TRANSFORMCOMPONENT_H
