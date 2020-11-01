#ifndef ZOMBIEGAME_GAMEAPPLICATION_H
#define ZOMBIEGAME_GAMEAPPLICATION_H

#include "Model/IApplication.h"
#include "SandBox/TestGameView.h"

class GameApplication : public IApplication
{
public:
    GameApplication();
    ~GameApplication();

private:

    TestGameView* m_pGameView;

protected:
    BaseGameLogic *VCreateGameAndView() override;
};

IApplication* CreateApplication()
{
    return new GameApplication;
}

#endif //ZOMBIEGAME_GAMEAPPLICATION_H
