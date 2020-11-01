#ifndef ZOMBIEGAME_CAMERANODE_H
#define ZOMBIEGAME_CAMERANODE_H

#include "SceneNode.h"

class CameraNode : public SceneNode
{
    //friend class SpriteNode;

public:

    CameraNode(float width, float height, float zNear, float zFar);
    CameraNode(glm::mat4 &mat, float width, float height, float zNear, float zFar);

    SceneNode* GetTarget() const { return m_pTarget; }
    void SetTarget(SceneNode& target) { m_pTarget = &target; }
    void ClearTarget() { m_pTarget = nullptr; }

    void SetViewMatrix(Scene* pScene);
    void SetProjectionMatrix(Scene* pScene);

    const glm::mat4& GetView() const { return m_View; }
    const glm::mat4& GetProjection() const { return m_Projection; }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    int GetZFar() const { return m_ZFar; }
    int GetZNear() const { return m_ZNear; }

private:

    glm::mat4 m_View;
    glm::mat4 m_Projection;
    SceneNode* m_pTarget;

    glm::vec3 m_CameraPos, m_CameraFront, m_CameraUp;

    float m_Width, m_Height;
    float m_HalfWidth, m_HalfHeight;
    float m_ZFar, m_ZNear;
};

#endif //ZOMBIEGAME_CAMERANODE_H
