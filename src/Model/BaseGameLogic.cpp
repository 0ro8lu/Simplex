#include "BaseGameLogic.h"
#include "SandBox/TestGameView.h"

BaseGameLogic::BaseGameLogic()
{
    m_ProcessManager = nullptr;
    m_pActorFactory  = nullptr;

    //pDelayProcess->AttachChild(pPrintProcess);

    Init();

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


    delete m_ProcessManager;
    m_ProcessManager = nullptr;

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
    const StrongActorPtr pActor = m_pActorFactory->CreateActor(actorResource);
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
    m_ProcessManager = new ProcessManager;
    m_pActorFactory = VCreateActorFactory();

    ///TODO: Don't really like the fact that we are using shared_ptrs, reformat code!
    StrongProcessPtr pDelayProcess = std::make_shared<DelayProcess>(3000);
    StrongProcessPtr pPrintProcess = std::make_shared<PrintProcess>("Done!");
    pDelayProcess->AttachChild(pPrintProcess);

    m_ProcessManager->AttachProcess(pDelayProcess);

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
            m_ProcessManager->UpdateProcesses();
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

void BaseGameLogic::testFunction()
{
    auto tgv = new TestGameView;

    std::shared_ptr<Actor> m_pActor1 = VCreateActor("../Assets/Actors/TestActor.xml");
    std::shared_ptr<Actor> m_pActor2 = VCreateActor("../Assets/Actors/TestActor.xml");

    m_Actors[m_pActor1->GetID()] = m_pActor1;
    m_Actors[m_pActor2->GetID()] = m_pActor2;

    VAddView(tgv, m_pActor1->GetID());
}