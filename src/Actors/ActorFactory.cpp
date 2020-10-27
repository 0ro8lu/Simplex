#include "ActorFactory.h"

ActorFactory::ActorFactory()
{
    m_LastActorID = 0;

    m_ComponentFactory.Register<TestComponent>(TestComponent::GetIDFromName(TestComponent::GetComponentName()));
    m_ComponentFactory.Register<SpriteRenderComponent>(SpriteRenderComponent::GetIDFromName(SpriteRenderComponent::GetComponentName()));
    m_ComponentFactory.Register<TransformComponent>(TransformComponent::GetIDFromName(TransformComponent::GetComponentName()));
    m_ComponentFactory.Register<PhysicsComponent>(PhysicsComponent::GetIDFromName(PhysicsComponent::GetComponentName()));
}

ActorFactory::~ActorFactory()
= default;

std::shared_ptr<Actor> ActorFactory::CreateActor(const char *actorResource)
{

    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError eResult = xmlDoc.LoadFile(actorResource);

    if(eResult != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ACTOR ERROR: Could not load file " << actorResource << std::endl;
        return std::shared_ptr<Actor>();
    }

    tinyxml2::XMLElement* pRoot = dynamic_cast<tinyxml2::XMLElement *>(xmlDoc.FirstChild());

    if(pRoot == nullptr)
    {
        std::cout << "Error! invalid xml actor in file " << actorResource << std::endl;
        return std::shared_ptr<Actor>();
    }

    std::shared_ptr<Actor> pActor = std::make_shared<Actor>(GetNextActorID());

    if(!pActor->Init(pRoot))
    {
        std::cout << "Failed to initialize actor " << actorResource << std::endl;
        return std::shared_ptr<Actor>();
    }

    for(tinyxml2::XMLElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
    {
        std::shared_ptr<ActorComponent> pComponent = CreateComponent(pNode);
        if(pComponent)
        {
            pActor->AddComponent(pComponent);
            pComponent->SetOwner(pActor);
        }
        else
        {
            return std::shared_ptr<Actor>();
        }
    }

    pActor->PostInit();
    return pActor;
}

std::shared_ptr<ActorComponent> ActorFactory::CreateComponent(tinyxml2::XMLElement *pData)
{

    const char* pName = pData->Value();
    std::shared_ptr<ActorComponent> pComponent(m_ComponentFactory.Create(ActorComponent::GetIDFromName(pName)));

    if(pComponent)
    {
        if(!pComponent->VInit(pData))
        {
            std::cout << "ERROR!: Component failed to initialize: " << pName << std::endl;
            return std::shared_ptr<ActorComponent>();
        }
    }
    else
    {
        std::cout << "ERROR!: Could not find ActorComponent named " << pName << std::endl;
        return std::shared_ptr<ActorComponent>();
    }

    return pComponent;
}
