#include "AIView.h"

AIView::AIView()
{
    m_ViewID = m_PlayerActorID = 0;

    m_pProcessManager = nullptr;

    Init();
}

AIView::~AIView()
{
    delete m_pProcessManager;
    m_pProcessManager = nullptr;
}

void AIView::Init()
{
    m_pProcessManager = new ProcessManager;

    /*///TODO: Don't really like the fact that we are using shared_ptrs, reformat code!
    StrongProcessPtr pDelayProcess = std::make_shared<DelayProcess>(3000);
    StrongProcessPtr pPrintProcess = std::make_shared<PrintProcess>("Done!");
    pDelayProcess->AttachChild(pPrintProcess);
    pPrintProcess->AttachChild(pDelayProcess);

    m_pProcessManager->AttachProcess(pDelayProcess);*/
}

void AIView::VOnUpdate()
{

    //std::unique_ptr<StartThrustEvent> pEvent = std::make_unique<StartThrustEvent>(m_PlayerActorID, 0.01f);
    //EventManager::Get()->triggerEvent(pEvent.get());

    m_pProcessManager->UpdateProcesses();
}
