#include "SceneNode.h"

#include "Actors/Actor.h"
#include "Utilities/templates.h"
#include "Model/IApplication.h"

SceneNode::SceneNode(unsigned int ActorID, RenderComponent *renderComponent, RenderPass renderPass,
                     glm::mat4 &transform)
{
    m_pParent = nullptr;

    m_Props.m_ActorID = ActorID;
    m_Props.m_Name = (renderComponent) ? renderComponent->VGetComponentName() : "SceneNode";
    m_Props.m_pTransform = &transform;
    //m_Props.m_Position = position;
    m_Props.m_RenderPass = renderPass;
}

SceneNode::SceneNode(unsigned int ActorID, RenderComponent *renderComponent, RenderPass renderPass)
{
    m_pParent = nullptr;

    m_Props.m_ActorID = ActorID;
    m_Props.m_Name = (renderComponent) ? renderComponent->VGetComponentName() : "SceneNode";
    /// This is already set to nullptr in the SceneNodeProperties tho.
    m_Props.m_pTransform = nullptr;
    m_Props.m_RenderPass = renderPass;
}

SceneNode::~SceneNode()
{
    for(auto & it : m_Children)
    {
        delete it;
    }

    m_Children.clear();
    m_Children.shrink_to_fit();
}

void SceneNode::VOnUpdate()
{
    for (auto &child : m_Children)
    {
        child->VOnUpdate();
    }
}

bool SceneNode::VAddChild(ISceneNode *pKid)
{
    m_Children.push_back(pKid);

    ///TODO: find a better solution here, i don't like dymamic casts.
    SceneNode *kid = dynamic_cast<SceneNode *>(pKid);
    kid->m_pParent = this;

    return true;
}

bool SceneNode::VRemoveChild(unsigned int actorID)
{
    for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
    {
        const SceneNodeProperties *pProps = (*it)->VGet();
        if (pProps->ActorID() != 0 && actorID == pProps->ActorID())
        {
            it = m_Children.erase(it); ///TODO: Change this.
            return true;
        }
    }
    return false;
}

bool SceneNode::VPreRender(Scene *pScene)
{
    /*
    StrongActorPtr pActor = MakeStrongPtr(IApplication::pApplication->GetGameLogic()->VGetActor(m_Props.ActorID()));
    if(pActor)
    {
        auto pTransformComponent = MakeStrongPtr(pActor->GetComponent<TransformComponent>(TransformComponent::GetComponentName()));

        if(pTransformComponent)
        {
            m_Props.m_Position.x = pTransformComponent->GetXPosition();
            m_Props.m_Position.y = pTransformComponent->GetYPosition();
        }
    }
    return true;
     */
    return true;
}

bool SceneNode::VPostRender(Scene *pScene)
{
    return true;
}

void SceneNode::VRenderChildren(Scene *pScene)
{
    for(auto it = m_Children.begin(); it != m_Children.end(); ++it)
    {
        if((*it)->VPreRender(pScene))
        {
            (*it)->VRender(pScene);
            (*it)->VRenderChildren(pScene);
            (*it)->VPostRender(pScene);
        }
    }
}
