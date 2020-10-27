#ifndef ZOMBIEGAME_IAPPLICATION_H
#define ZOMBIEGAME_IAPPLICATION_H

#include "Window.h"
#include "EventManager.h"
#include "AppCloseEvent.h"
#include "BaseGameLogic.h"
#include "Rendering/SpriteRenderer.h"
#include "Utilities/Timer.h"

class IApplication
{
public:

    IApplication();
    virtual ~IApplication();

    void start();
    void close();
    static void messageProcess(const AppMsg& appMsg);

    void onRender();

    BaseGameLogic* GetGameLogic() const { return m_pGameLogic; }
    static SpriteRenderer*& GetRenderer() { return m_pRenderer; }

    static IApplication* pApplication;

protected:
    virtual BaseGameLogic* VCreateGameAndView() = 0;

    const double MS_PER_UPDATE = 16.67f;

private:

    void update();
    virtual void initInstance();
    void closeDelegate(const EventPointer& event);

    bool m_ShouldClose;

    Window*         m_pWindow;
    EventManager*   m_pEventManager;
    BaseGameLogic*  m_pGameLogic;

    static SpriteRenderer* m_pRenderer;
};

extern IApplication* CreateApplication();

#endif //ZOMBIEGAME_IAPPLICATION_H
