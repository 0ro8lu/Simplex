#ifndef ZOMBIEGAME_CAMERANODE_H
#define ZOMBIEGAME_CAMERANODE_H

#include "SceneNode.h"

class CameraNode : public SceneNode
{
    friend class SpriteNode;

public:
    CameraNode(glm::mat4 &transform);

    SceneNode* GetTarget() const { return m_pTarget; }

    void VOnUpdate() override;

    void SetViewTransform(Scene* pScene);
    void SetTarget(SceneNode* target) { m_pTarget = target; }

private:
    SceneNode* m_pTarget;
};

#endif //ZOMBIEGAME_CAMERANODE_H
