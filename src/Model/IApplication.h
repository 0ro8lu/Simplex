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

    SpriteRenderer* m_pRenderer;

protected:
    virtual BaseGameLogic* VCreateGameAndView() = 0;

    ///TODO: Maybe declare this inside the GameApplication, if someone wanted to have a different value it would not have to dig into Engine Code.
    const double MS_PER_UPDATE = 16.67f;

    Window*         m_pWindow;
    EventManager*   m_pEventManager;
    BaseGameLogic*  m_pGameLogic;

    bool m_ShouldClose;

private:

    void update();
    virtual void initInstance();
    void closeDelegate(const EventPointer& event);
};

extern IApplication* g_pApp;
extern IApplication* CreateApplication();

#endif //ZOMBIEGAME_IAPPLICATION_H
