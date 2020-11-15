#include "TestGameView.h"

TestGameView::TestGameView(SpriteRenderer &renderer) : HumanView(renderer)
{
    m_KeyboardHandler = nullptr;
    m_PointerHandler  = nullptr;
    m_pObject         = nullptr;
    m_pTestController = nullptr;

    RegisterAllDelegates();
}

TestGameView::~TestGameView()
{

    delete m_pTestController;
    m_pTestController = nullptr;

    RemoveAllDelegates();
}

bool TestGameView::VOnMsgProc(const AppMsg &msg)
{
    if(HumanView::VOnMsgProc(msg))
        return true;

    return true;
    ///TODO: Maybe add stuff inside here.
}

void TestGameView::VOnUpdate()
{
    HumanView::VOnUpdate();
}

void TestGameView::VOnAttach(unsigned int viewID, unsigned int actorID)
{
    HumanView::VOnAttach(viewID, actorID);
}

void TestGameView::RegisterAllDelegates()
{

}

void TestGameView::RemoveAllDelegates()
{

}

void TestGameView::VSetControlledActor(unsigned int actorID)
{
    m_pObject = (SceneNode*)m_pScene->FindActor(actorID);

    if(!m_pObject)
    {
        std::cout << "FATAL ERROR: INVALID ACTOR\n";
        return;
    }

    HumanView::VSetControlledActor(actorID);

    m_pTestController = new TestController(m_pObject);

    m_KeyboardHandler = m_pTestController;
    m_PointerHandler  = m_pTestController;
    m_pCamera->SetTarget(*m_pObject);
}

void TestGameView::SetControlledActorDelegate(EventPointer pEventData)
{
}
