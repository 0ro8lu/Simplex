#include "CameraNode.h"

#include <gtc/matrix_transform.hpp>
#include "Scene.h"

CameraNode::CameraNode(glm::mat4 &mat, float width, float height, float zNear, float zFar)
    : SceneNode(0, nullptr, RenderPass_0, mat),
      m_Projection(mat), m_Width(width), m_Height(height), m_ZFar(zNear), m_ZNear(zFar)
{
    m_pTarget = nullptr;

    m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_CameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    m_Projection = glm::ortho(0.0f, m_Width, 0.0f, m_Height, m_ZNear, m_ZFar);
}

CameraNode::CameraNode(float width, float height, float zNear, float zFar)
    : SceneNode(0, nullptr, RenderPass_0),
      m_Width(width), m_Height(height), m_ZFar(zFar), m_ZNear(zNear),
      m_HalfWidth(width/2), m_HalfHeight(height/2)
{
    m_pTarget = nullptr;

    m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_CameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    m_View       = glm::mat4(1.0f);

    m_Projection = glm::ortho(0.0f, m_Width, 0.0f, m_Height, m_ZNear, m_ZFar);
}

void CameraNode::SetViewMatrix(Scene* pScene)
{
    if(m_pTarget)
    {
        glm::vec2 objectPos = glm::vec2(m_pTarget->VGet()->GetTransform()[3]);
        ///TODO: Make this better, don't divide and do a bunch of things every time you need to render.
        m_CameraPos = glm::vec3((objectPos.x) - (m_HalfWidth) + (m_pTarget->VGet()->GetTransform()[0][0]) / 2,
                                (objectPos.y) - (m_HalfHeight) + (m_pTarget->VGet()->GetTransform()[1][1]) / 2,
                                3.0f);
    }
    else
    {
        m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    }

    m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);

    pScene->GetRenderer()->SetViewMatrix(m_View);
}

void CameraNode::SetProjectionMatrix(Scene* pScene)
{
    pScene->GetRenderer()->SetProjectionMatrix(m_Projection);
}


