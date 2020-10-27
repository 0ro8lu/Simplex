#ifndef ZOMBIEGAME_SPRITENODE_H
#define ZOMBIEGAME_SPRITENODE_H

#include "SceneNode.h"

#include "Rendering/SpriteRenderer.h"

class SpriteNode : public SceneNode
{
    friend class Window;

public:
    SpriteNode(unsigned int ActorID, RenderComponent *renderComponent, std::string spriteName, RenderPass renderPass,
               const glm::vec2 &size, glm::mat4 &transform);

    virtual ~SpriteNode();

    bool VPreRender(Scene *pScene) override;

    void VRender(Scene *pScene) override;

private:
    void initRenderData();

    unsigned int quadVAO;

    std::string m_spriteName;
    SpriteRenderer* m_pSpriteRenderer;
    Texture2D* m_pTexture;
};

#endif //ZOMBIEGAME_SPRITENODE_H
