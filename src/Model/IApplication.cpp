#include "IApplication.h"
#include "Physics/DefaultPhysics.h"

IApplication* g_pApp = nullptr;

IApplication::IApplication()
{
    g_pApp = this;

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

    if(appMsg.getType() == MOUSEMOVE)
    {
        //std::cout << "X: " << appMsg.xPos << " Y: " << abs(600 - appMsg.yPos) << "\n";
    }

    if (appMsg.getType() == KEYDOWN)
    {
        //std::cout << "Key " << appMsg.key << " pressed\n";

        ///TODO: make a table of keys so we are not forced to deal with numbers instead of keys.
        if (appMsg.key == GLFW_KEY_ESCAPE)
        {
            g_pApp->close();
        }
    }

    if(g_pApp->m_pGameLogic)
    {
        BaseGameLogic* pGame = g_pApp->m_pGameLogic;

        for(auto it = pGame->m_GameViews.rbegin(); it != pGame->m_GameViews.rend(); ++it)
        {
            (*it)->VOnMsgProc(appMsg);
        }
    }
}

void IApplication::onRender()
{
    BaseGameLogic* pGame = m_pGameLogic;

    m_pRenderer->DrawBackGround();

    for(auto & m_GameView : pGame->m_GameViews)
    {
        m_GameView->VOnRender();
    }
}

void IApplication::update()
{
    double previous = Timer::getCurrentTime();
    double lag = 0.0;

    while (!m_ShouldClose)
    {

        double current = Timer::getCurrentTime();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        m_pWindow->processInput();

        while(lag >= MS_PER_UPDATE)
        {
            m_pGameLogic->VOnUpdate();
            lag -= MS_PER_UPDATE;
        }
        onRender();
    }
}

void IApplication::initInstance()
{
    m_pWindow = new Window(800, 600, "Test");
    m_pEventManager = new EventManager;
    m_pRenderer  = new SpriteRenderer;
    m_pGameLogic = VCreateGameAndView();

    m_pEventManager->registerMemberDelegate(AppCloseEvent::StaticName(), this, &IApplication::closeDelegate);

    m_pGameLogic->testFunction();
}

void IApplication::closeDelegate(const EventPointer &event)
{
    close();
}
