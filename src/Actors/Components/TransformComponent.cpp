#include "TransformComponent.h"

bool TransformComponent::VInit(tinyxml2::XMLElement *pData)
{
    m_Transform = glm::mat4(1.0f);

    tinyxml2::XMLElement* pAttributes = pData->FirstChildElement("Position");
    if(!pAttributes)
    {
        std::cout << "ERROR!: Could not find attribute Position in TransformComponent\n";
        return false;
    }

    pAttributes->QueryFloatAttribute("x", &m_Position.x);
    pAttributes->QueryFloatAttribute("y", &m_Position.y);

    m_Transform = glm::translate(m_Transform, glm::vec3(m_Position, 0.0f));

    return true;
}
