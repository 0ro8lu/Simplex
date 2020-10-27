#include "GameApplication.h"
#include "TestGameLogic.h"

GameApplication::GameApplication()
{

}

GameApplication::~GameApplication()
{

}

BaseGameLogic *GameApplication::VCreateGameAndView()
{
    return new TestGameLogic;
}
