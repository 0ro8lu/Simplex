#include "IApplication.h"

IApplication*   IApplication::pApplication = nullptr;
SpriteRenderer* IApplication::m_pRenderer = nullptr;

IApplication::IApplication()
{
    pApplication = this;

    m_ShouldClose = false;

    m_pWindow       = nullptr;
    m_pEventManager = nullptr;
    m_pGameLogic    = nullptr;
    m_pRenderer     = nullptr;
}

IApplication::~IApplication()
{
    m_pEventManager->unregisterMemberDelegate(AppCloseEvent::StaticName(), &IApplication::closeDelegate);

    delete m_pRenderer;
    m_pRenderer = nullptr;

    delete m_pGameLogic;
    m_pGameLogic = nullptr;

    delete m_pEventManager;
    m_pEventManager = nullptr;

    delete m_pWindow;
    m_pWindow = nullptr;
}

void IApplication::start()
{
    m_ShouldClose = false;

    initInstance();
    update();
}

void IApplication::close()
{
    m_ShouldClose = true;
    std::cout << "Closing...\n";
}

void IApplication::messageProcess(const AppMsg &appMsg)
{
    if (appMsg.getType() == KEYDOWN)
    {
        //std::cout << "Key " << appMsg.key << " pressed\n";

        ///TODO: make a table of keys so we are not forced to deal with numbers instead of keys.
        if (appMsg.key == GLFW_KEY_ESCAPE)
        {
            pApplication->close();
        }
    }

    if(pApplication->m_pGameLogic)
    {
        BaseGameLogic* pGame = pApplication->m_pGameLogic;

        for(auto it = pGame->m_GameViews.rbegin(); it != pGame->m_GameViews.rend(); ++it)
        {
            (*it)->VOnMsgProc(appMsg);
        }
    }
}

void IApplication::onRender()
{
    BaseGameLogic* pGame = pApplication->m_pGameLogic;

    m_pRenderer->DrawBackGround();

    for(auto & m_GameView : pGame->m_GameViews)
    {
        m_GameView->VOnRender();
    }
}

void IApplication::update()
{
    while (!m_ShouldClose)
    {
        m_pWindow->update();
        m_pGameLogic->VOnUpdate();
        onRender();
        ///TODO: Add game loop.
    }
}

void IApplication::initInstance()
{
    m_pWindow = new Window(800, 600, "Test");
    m_pEventManager = new EventManager;
    m_pGameLogic = VCreateGameAndView();
    m_pRenderer  = new SpriteRenderer;

    m_pEventManager->registerMemberDelegate(AppCloseEvent::StaticName(), this, &IApplication::closeDelegate);

    m_pGameLogic->testFunction();
}

void IApplication::closeDelegate(const EventPointer &event)
{
    close();
}
