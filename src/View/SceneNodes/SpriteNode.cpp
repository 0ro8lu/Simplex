#include "SpriteNode.h"
#include "Model/IApplication.h"

SpriteNode::SpriteNode(unsigned int ActorID, RenderComponent *renderComponent, std::string spriteName,
                       RenderPass renderPass,
                       const glm::vec2 &size, glm::mat4 &transform)
        : SceneNode(ActorID, renderComponent, renderPass, transform)
{

    m_pSpriteRenderer = IApplication::GetRenderer();

    m_pTexture = new Texture2D;
    m_pTexture->LoadFromFile(("../Assets/Textures/" + spriteName).c_str(), false);

    m_Props.GetTransform() = glm::scale(m_Props.GetTransform(), glm::vec3(size, 1.0f));

    m_spriteName = std::move(spriteName);
}

SpriteNode::~SpriteNode()
{
    delete m_pTexture;
    m_pTexture = nullptr;
}

bool SpriteNode::VPreRender(Scene *pScene)
{
    SceneNode::VPreRender(pScene);

    return true;
}

void SpriteNode::VRender(Scene *pScene)
{
    m_pSpriteRenderer->DrawSprite(*m_pTexture, m_Props.GetTransform());
}

void SpriteNode::initRenderData()
{

}