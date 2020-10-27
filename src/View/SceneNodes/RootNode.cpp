#include "RootNode.h"
#include "Actors/Components/RenderComponent.h"

typedef RenderComponent *baseRenderComponent;

RootNode::RootNode()
        : SceneNode(0, nullptr, RenderPass_0)
{
    m_pStaticGroup = new SceneNode(0, nullptr, RenderPass_Static);
    m_pActorGroup = new SceneNode(0, nullptr, RenderPass_Actor);
    m_pBackGroundGroup = new SceneNode(0, nullptr, RenderPass_BackGround);
    //SceneNode *skyGroup = new SceneNode(0, nullptr, RenderPass_Sky);
    m_pInvisibleGroup = new SceneNode(0, nullptr, RenderPass_NotRendered);

    m_Children.push_back(m_pStaticGroup);
    m_Children.push_back(m_pActorGroup);
    m_Children.push_back(m_pBackGroundGroup);
    //m_Children.push_back(skyGroup);
    m_Children.push_back(m_pInvisibleGroup);
}

bool RootNode::VAddChild(ISceneNode *kid)
{
    RenderPass pass = kid->VGet()->GetRenderPass();
    if ((unsigned) pass >= m_Children.size() || !m_Children[pass])
    {
        std::cout << "There is no such render pass\n";
        return false;
    }

    return m_Children[pass]->VAddChild(kid);
}

bool RootNode::VRemoveChild(unsigned int ActorID)
{
    bool anythingRemoved = false;

    for (int i = RenderPass_0; i < RenderPass_Last; ++i)
    {
        if (m_Children[i]->VRemoveChild(ActorID))
        {
            anythingRemoved = true;
        }
    }

    return anythingRemoved;
}

void RootNode::VRenderChildren(Scene *pScene)
{
    for (int pass = RenderPass_0; pass < RenderPass_Last; ++pass)
    {
        switch (pass)
        {
            case RenderPass_Static:
            case RenderPass_Actor:
                m_Children[pass]->VRenderChildren(pScene);
                break;
        }
    }
}
