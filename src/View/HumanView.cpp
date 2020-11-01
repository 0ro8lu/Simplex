#include "HumanView.h"
#include "Window.h"

HumanView::HumanView(SpriteRenderer &renderer)
{
    m_ProcessManager = new ProcessManager;

    m_ViewID = 0;
    m_ActorID = 0;

    m_pScene  = new ScreenElementScene(renderer);

    m_pCamera = new CameraNode((float)Window::getWidth(), (float)Window::getHeight(), 0.1f, 100.0f);
    m_pCamera->SetProjectionMatrix(m_pScene);

    m_pScene->VAddChild(0, m_pCamera);
    m_pScene->SetCamera(m_pCamera);

    RegisterAllDelegates();

    m_BaseGameState = BGS_Initializing;

    ///TODO: Remove this from here.
    LoadGame(nullptr);
}

HumanView::~HumanView()
{
    RemoveAllDelegates();

    while(!m_ScreenElementList.empty())
    {
        m_ScreenElementList.pop_front();
    }

    delete m_ProcessManager;
    m_ProcessManager = nullptr;

    delete m_pScene;
    m_pScene = nullptr;
}

void HumanView::VOnRender()
{
    ///TODO: Sort the list by... what?
    //m_ScreenElementList.sort()

    ///TODO: if(g_pApp->m_Renderer->VPreRender())

    for(auto it = m_ScreenElementList.begin(); it != m_ScreenElementList.end(); ++it)
    {
        if((*it)->VIsVisible())
        {
            (*it)->VOnRender();
        }
    }

    ///TODO: VRenderText();

    ///TODO: g_pApp->m_Renderer->VPostRender();
}

void HumanView::VOnAttach(unsigned int viewID, unsigned int actorID)
{
    m_ViewID = viewID;
    m_ActorID = actorID;
}

bool HumanView::VOnMsgProc(const AppMsg& msg)
{

    for(auto i = m_ScreenElementList.rbegin(); i != m_ScreenElementList.rend(); ++i)
    {
        if((*i)->VIsVisible())
        {
            if((*i)->VOnMsgProc(msg))
            {
                return true;
            }
        }
    }

    switch (msg.getType())
    {
        case KEYUP:

            if(m_KeyboardHandler)
                return m_KeyboardHandler->VOnKeyUp(msg.key);
            break;

        case KEYDOWN:

            if(m_KeyboardHandler)
                return m_KeyboardHandler->VOnKeyDown(msg.key);
            break;

        case KEYREPEAT:
            break;

        case MOUSEUP:

            if(m_PointerHandler)
                return m_PointerHandler->VOnPointerButtonUp(msg.xPos, msg.yPos, msg.key);
            break;

        case MOUSEDOWN:

            if(m_PointerHandler)
                return m_PointerHandler->VOnPointerButtonDown(msg.xPos, msg.yPos, msg.key);
            break;

        case MOUSESCROLL:
            break;

        case MOUSEMOVE:

            if(m_PointerHandler)
                return m_PointerHandler->VOnPointerMove(msg.xPos, msg.yPos);
            break;
        default:
            return false;
    }
    return false;
}

void HumanView::VOnUpdate()
{
    m_ProcessManager->UpdateProcesses();

    for(auto& it : m_ScreenElementList)
    {
        it->VOnUpdate();
    }
}

void HumanView::VPushElement(IScreenElement *pElement)
{
    m_ScreenElementList.push_front(pElement);
}

void HumanView::VRemoveElement(IScreenElement *pElement)
{
    m_ScreenElementList.remove(pElement);
}

void HumanView::RegisterAllDelegates()
{
    ///TODO: Implement this.
}

void HumanView::RemoveAllDelegates()
{
    ///TODO: Implement this.
}

bool HumanView::LoadGame(tinyxml2::XMLElement* pLevelData)
{
    return VLoadGameDelegate(pLevelData);
}
