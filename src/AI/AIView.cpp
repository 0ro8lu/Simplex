#include "AIView.h"


AIView::AIView()
{
    m_ViewID = m_PlayerActorID = 0;

    m_pProcessManager = nullptr;
}

AIView::~AIView()
{
    delete m_pProcessManager;
    m_pProcessManager = nullptr;
}

void AIView::Init()
{
    m_pProcessManager = new ProcessManager;
}
