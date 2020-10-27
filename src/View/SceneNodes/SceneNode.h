#ifndef ZOMBIEGAME_SCENENODE_H
#define ZOMBIEGAME_SCENENODE_H

#include <vector>
#include <string>

#include "ISceneNode.h"
#include "Actors/Components/RenderComponent.h"
#include "SceneNodeProperties.h"

class SceneNode : public ISceneNode
{
    friend class Scene;

public:

    //SceneNode();
    ///TODO: Implement constructor.
    SceneNode(unsigned int ActorID, RenderComponent *renderComponent, RenderPass renderPass,
              glm::mat4 &transform);

    SceneNode(unsigned int ActorID, RenderComponent *renderComponent, RenderPass renderPass);

    virtual ~SceneNode();

    void VOnUpdate() override;
    bool VAddChild(ISceneNode *kid) override;
    bool VRemoveChild(unsigned int actorID) override;
    bool VPreRender(Scene* pScene) override;
    void VRender(Scene* pScene) override { }
    bool VPostRender(Scene* pScene) override;
    void VRenderChildren(Scene* pScene) override;

    const SceneNodeProperties* const VGet() const override { return &m_Props; }

protected:
    std::vector<ISceneNode*> m_Children;
    SceneNode*               m_pParent;
    SceneNodeProperties      m_Props;
};

#endif //ZOMBIEGAME_SCENENODE_H