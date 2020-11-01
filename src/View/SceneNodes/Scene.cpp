#include "Scene.h"

Scene::Scene(SpriteRenderer &renderer)
{
    m_pRoot = std::make_unique<RootNode>();
    m_pRenderer = &renderer;

    ///TODO: Add all event delegates.
    EventManager* pEventMgr = EventManager::Get();
    pEventMgr->registerMemberDelegate(NewRenderComponentEvent::StaticName(), this, &Scene::NewRenderComponentDelegate);
    pEventMgr->registerMemberDelegate(ModifiedRenderComponentEvent::StaticName(), this, &Scene::ModifiedRenderComponentDelgate);
    pEventMgr->registerMemberDelegate(DestroyActorEvent::StaticName(), this, &Scene::DestroyActorDelegate);
}

Scene::~Scene()
{
    EventManager* pEventMgr = EventManager::Get();
    pEventMgr->unregisterMemberDelegate(NewRenderComponentEvent::StaticName(), &Scene::NewRenderComponentDelegate);
    pEventMgr->unregisterMemberDelegate(ModifiedRenderComponentEvent::StaticName(), &Scene::ModifiedRenderComponentDelgate);
    pEventMgr->unregisterMemberDelegate(DestroyActorEvent::StaticName(), &Scene::DestroyActorDelegate);

    m_ActorMap.clear();
}

void Scene::OnRender()
{
    if(m_pRoot)
    //if(m_pRoot && m_pCamera)
    {
        m_pCamera->SetViewMatrix(this);

        if(m_pRoot->VPreRender(this))
        {
            m_pRoot->VRender(this);
            m_pRoot->VRenderChildren(this);
            m_pRoot->VPostRender(this);
        }
    }
}

void Scene::OnRestore()
{

}

void Scene::OnLostDevice()
{

}

void Scene::OnUpdate()
{
    if(!m_pRoot)
        return;

    m_pRoot->VOnUpdate();
}

ISceneNode *Scene::FindActor(unsigned int actorID)
{
    auto it = m_ActorMap.find(actorID);

    if(it == m_ActorMap.end())
        return nullptr;

    return it->second;
}

bool Scene::AddChild(unsigned int actorID, ISceneNode *child)
{
    if(actorID != 0)
    {
        m_ActorMap[actorID] = child;
    }

    return m_pRoot->VAddChild(child);
}

bool Scene::RemoveChild(unsigned int actorID)
{
    if(actorID == 0)
        return false;

    //ISceneNode* kid = FindActor(actorID);
    m_ActorMap.erase(actorID);
    return m_pRoot->VRemoveChild(actorID);
}

void Scene::NewRenderComponentDelegate(const EventPointer& pEventData)
{
    auto* pCastEventData = static_cast<NewRenderComponentEvent*>(pEventData);

    ///TODO: Add VOnRestore.
    AddChild(pCastEventData->GetActorID(), pCastEventData->GetSceneNode());
}

void Scene::ModifiedRenderComponentDelgate(const EventPointer& pEventData)
{
    auto* pCastEventData = static_cast<ModifiedRenderComponentEvent*>(pEventData);

    unsigned int ActorID = pCastEventData->GetActorID();
    if(ActorID == 0)
    {
        std::cout << "Scene::ModifiedRenderComponentDelegate - unknown actor ID\n";
        return;
    }

    ///TODO: Add that if the game is loading it will just return.

    ISceneNode* pSceneNode = FindActor(ActorID);
    if(!pSceneNode) ///TODO: Add || not pSceneNode->VonRestore(this).
    {
        std::cout << "Failed to restore scene node to the scene for ActorID " << ActorID << "\n";
    }
}

void Scene::DestroyActorDelegate(EventPointer const &pEventData)
{
    auto* pCastEventData = static_cast<DestroyActorEvent*>(pEventData);
    RemoveChild(pCastEventData->GetActorID());
}

