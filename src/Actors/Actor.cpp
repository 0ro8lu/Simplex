#include "Actor.h"
#include "ActorComponent.h"

Actor::Actor(unsigned int id)
{
    m_ID = id;
    m_Type = "Unknown";
    m_Resource = "Unknown";
}

Actor::~Actor()
{
    std::cout << "ACTOR: Destroying Actor " << m_ID << std::endl;
}

bool Actor::Init(tinyxml2::XMLElement* pData)
{
    std::cout << "ACTOR: Initializing Actor with ID: " << m_ID << std::endl;

    tinyxml2::XMLError eResult = pData->QueryStringAttribute("type", &m_Type);

    if(eResult != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ERROR: Invalid xml format, actor type not found\n";
        return false;
    }

    eResult = pData->QueryStringAttribute("resource", &m_Resource);

    if(eResult != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ERROR: Invalid xml format, actor resource not found\n";
        return false;
    }

    std::cout << m_Type << " " << m_Resource << std::endl;

    return true;
}

void Actor::PostInit()
{
    for(auto & m_Component : m_Components)
    {
        m_Component.second->VPostInit();
    }
}

void Actor::Destroy()
{
    m_Components.clear();
}

void Actor::Update()
{
    for(auto & m_Component : m_Components)
    {
        m_Component.second->VUpdate();
    }
}

void Actor::AddComponent(const std::shared_ptr<ActorComponent>& pComponent)
{
    m_Components.insert(std::make_pair(pComponent->VGetComponentID(), pComponent));
}