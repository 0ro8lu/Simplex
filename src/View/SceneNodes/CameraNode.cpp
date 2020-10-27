#include "CameraNode.h"

///TODO: Redo this and let camera take frustum as parameter.
CameraNode::CameraNode(glm::mat4 &transform)
    : SceneNode(0, nullptr, RenderPass_0, transform)
{
}

void CameraNode::SetViewTransform(Scene *pScene)
{

}

void CameraNode::VOnUpdate()
{
    SceneNode::VOnUpdate();
}
