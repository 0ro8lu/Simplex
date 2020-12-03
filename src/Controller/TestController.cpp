#include "TestController.h"

#include "glfw3.h"

TestController::TestController(SceneNode* object)
{
    m_Object = object;
}

void TestController::OnUpdate()
{

}

bool TestController::VOnKeyDown(short key)
{
    if (key == GLFW_KEY_W || key == GLFW_KEY_S)
    {
        unsigned int actorID = m_Object->VGet()->ActorID();
        std::unique_ptr<StartThrustEvent> pEvent = std::make_unique<StartThrustEvent>(actorID, (key == GLFW_KEY_W ? 0.03f : (-0.03)));
        EventManager::Get()->triggerEvent(pEvent.get());
    }

    if (key == GLFW_KEY_A || key == GLFW_KEY_D)
    {
        unsigned int actorID = m_Object->VGet()->ActorID();
        std::unique_ptr<StartSteerEvent> pEvent = std::make_unique<StartSteerEvent>(actorID, (key == GLFW_KEY_D ? 0.03f : (-0.03f)));
        EventManager::Get()->triggerEvent(pEvent.get());
    }

    return true;
}

bool TestController::VOnKeyUp(short key)
{

    if(key == GLFW_KEY_W || key == GLFW_KEY_S)
    {
        unsigned int actorID = m_Object->VGet()->ActorID();
        std::unique_ptr<EndThrustEvent> pEvent = std::make_unique<EndThrustEvent>(actorID);
        EventManager::Get()->triggerEvent(pEvent.get());
    }

    if (key == GLFW_KEY_A || key == GLFW_KEY_D)
    {
        unsigned int actorID = m_Object->VGet()->ActorID();
        std::unique_ptr<EndSteerEvent> pEvent = std::make_unique<EndSteerEvent>(actorID);
        EventManager::Get()->triggerEvent(pEvent.get());
    }

    return true;
}