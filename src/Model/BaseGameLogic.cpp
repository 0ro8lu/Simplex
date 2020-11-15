#include "BaseGameLogic.h"

BaseGameLogic::BaseGameLogic()
{
    m_pProcessManager = nullptr;
    m_pActorFactory   = nullptr;
    m_pGamePhysics    = nullptr;

    m_GameState = BGS_Running;
}

BaseGameLogic::~BaseGameLogic()
{

    for(auto &m_GameView : m_GameViews)
    {
        delete m_GameView;
    }

    m_GameViews.clear();
    m_GameViews.shrink_to_fit();


    for (auto &m_Actor : m_Actors)
    {
        m_Actor.second->Destroy();
    }
    m_Actors.clear();

    //delete m_pGamePhysics;
    //m_pGamePhysics = nullptr;

    if(!m_pGamePhysics)
        std::cout << "Physics Destroyed!\n";

    delete m_pProcessManager;
    m_pProcessManager = nullptr;

    delete m_pActorFactory;
    m_pActorFactory = nullptr;
}

WeakActorPtr BaseGameLogic::VGetActor(unsigned int id)
{
    auto findIt = m_Actors.find(id);

    if (findIt != m_Actors.end())
        return findIt->second;
    return WeakActorPtr();
}

StrongActorPtr BaseGameLogic::VCreateActor(const char *actorResource)
{
    StrongActorPtr pActor = m_pActorFactory->CreateActor(actorResource);
    m_Actors.insert(std::pair(pActor->GetID(), pActor));
    return pActor;
}

void BaseGameLogic::VDestroyActor(unsigned int id)
{
    std::unique_ptr<DestroyActorEvent> pDestroyActorEvent = std::make_unique<DestroyActorEvent>(id);
    EventManager::Get()->triggerEvent(pDestroyActorEvent.get());

    auto findIt = m_Actors.find(id);
    if (findIt != m_Actors.end())
    {
        findIt->second->Destroy();
        m_Actors.erase(findIt);
    }
}

bool BaseGameLogic::Init()
{
    m_pProcessManager = new ProcessManager;
    m_pActorFactory = VCreateActorFactory();

    m_GameState = BGS_Initializing;

    return true;
}

void BaseGameLogic::VOnUpdate()
{
    switch (m_GameState)
    {
        case BGS_Initializing:
            break;
        case BGS_Running:
            m_pProcessManager->UpdateProcesses();

            if(m_pGamePhysics)
            {
                m_pGamePhysics->VOnUpdate();
                m_pGamePhysics->VSyncVisibleScene();
            }

            break;
        default:
            break;
    }

    for (auto &gameView : m_GameViews)
    {
        gameView->VOnUpdate();
    }

    for (auto &actor : m_Actors)
    {
        actor.second->Update();
    }
}

void BaseGameLogic::VChangeState(BaseGameState newState)
{
    ///TODO: Implement particular cases.
    m_GameState = newState;
}

ActorFactory *BaseGameLogic::VCreateActorFactory()
{
    return new ActorFactory;
}

void BaseGameLogic::VAddView(IGameView *pView, unsigned int actorID)
{
    int viewID = m_GameViews.size();
    m_GameViews.push_back(pView);
    pView->VOnAttach(viewID, actorID);
    //view.VOnRestore(); ///TODO: Implement this.
}