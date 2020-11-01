#include "GameApplication.h"
#include "TestGameLogic.h"

GameApplication::GameApplication()
{

}

GameApplication::~GameApplication()
{
    delete m_pGameView;
    m_pGameView = nullptr;
}

BaseGameLogic *GameApplication::VCreateGameAndView()
{
    m_pGameLogic = new TestGameLogic;
    m_pGameLogic->Init();

    m_pGameView = new TestGameView(*m_pRenderer);
    m_pGameLogic->VAddView(m_pGameView);

    return m_pGameLogic;
}
