#ifndef ZOMBIEGAME_SCENENODEPROPERTIES_H
#define ZOMBIEGAME_SCENENODEPROPERTIES_H

#include <glm.hpp>

enum RenderPass
{
    RenderPass_0,
    RenderPass_Static = RenderPass_0,
    RenderPass_Actor,
    RenderPass_BackGround,
    //RenderPass_Sky,
    RenderPass_NotRendered,
    RenderPass_Last
};

class SceneNodeProperties
{
    friend class SceneNode;

public:
    SceneNodeProperties()
    {
        m_pTransform = nullptr;
        m_ActorID = 0;
        m_Position = {0, 0};
    }

    const unsigned int& ActorID() const { return m_ActorID; }
    std::string Name() const { return m_Name; }
    RenderPass GetRenderPass() const { return m_RenderPass; }

    float GetXPosition() const { return m_Position.x; }
    float GetYPosition() const { return m_Position.y; }

    glm::vec2 GetPosition() const { return glm::vec2((*m_pTransform)[3]); }
    glm::mat4& GetTransform() { return *m_pTransform; }

protected:
    unsigned int m_ActorID;
    std::string  m_Name;
    RenderPass   m_RenderPass;

    glm::vec2    m_Position;
    glm::mat4*   m_pTransform;
    ///TODO: Implement all the other things.
};

#endif //ZOMBIEGAME_SCENENODEPROPERTIES_H
