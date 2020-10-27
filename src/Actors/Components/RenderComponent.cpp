#include "RenderComponent.h"
#include "Actors/Actor.h"
#include "TransformComponent.h"

#include "View/SceneNodes/SpriteNode.h"

SceneNode *RenderComponent::VGetSceneNode()
{
    return m_pSceneNode;
}

bool RenderComponent::VInit(tinyxml2::XMLElement *pData)
{
    m_pSceneNode = nullptr;
    return VDelegateInit(pData);
}

void RenderComponent::VPostInit()
{
    SceneNode* pSceneNode = VGetSceneNode();
    std::unique_ptr<NewRenderComponentEvent> pEvent = std::make_unique<NewRenderComponentEvent>(m_pOwner->GetID(), pSceneNode);
    EventManager::Get()->triggerEvent((EventPointer&)pEvent);
}

void RenderComponent::VOnChanged()
{
    //ModifiedRenderComponentEvent
    std::unique_ptr<ModifiedRenderComponentEvent> pEvent = std::make_unique<ModifiedRenderComponentEvent>(m_pOwner->GetID());
    EventManager::Get()->triggerEvent((EventPointer&)pEvent);
}

tinyxml2::XMLElement *RenderComponent::VGenerateXml()
{
    ///TODO: basically save the component back into the xml file
    return nullptr;
}



//------------------------------------SpriteRenderComponent--------------------------------

bool SpriteRenderComponent::VDelegateInit(tinyxml2::XMLElement *pData)
{
    m_Size = {0, 0};

    tinyxml2::XMLElement* pAttributes = pData->FirstChildElement("Texture");
    if(!pAttributes)
    {
        std::cout << "ERROR!: Could not find attribute Texture in SpriteRenderComponent\n";
        return false;
    }

    pAttributes->QueryStringAttribute("name", &m_TextureName);

    pAttributes = pData->FirstChildElement("Dimentions");

    if(!pAttributes)
    {
        std::cout << "ERROR!: Could not find attribute Dimentions in SpriteRenderComponent\n";
        return false;
    }

    pAttributes->QueryFloatAttribute("width", (&m_Size.x));
    pAttributes->QueryFloatAttribute("height", (&m_Size.y));

    return true;
}

SceneNode* SpriteRenderComponent::VCreateSceneNode()
{
    auto pTransformComponent = m_pOwner->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());
    return new SpriteNode(m_pOwner->GetID(), this, m_TextureName, RenderPass_Actor, m_Size, pTransformComponent->GetTransform());
}

void SpriteRenderComponent::VPostInit()
{
    m_pSceneNode = VCreateSceneNode();
    RenderComponent::VPostInit();
}