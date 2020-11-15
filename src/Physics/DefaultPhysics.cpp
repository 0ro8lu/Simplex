#include "DefaultPhysics.h"

DefaultPhysics::DefaultPhysics()
{

}

DefaultPhysics::~DefaultPhysics()
{

}

bool DefaultPhysics::VInitialize()
{
    return false;
}

void DefaultPhysics::VSyncVisibleScene()
{
    ///TODO: Check if actor has moved.
}

void DefaultPhysics::VOnUpdate()
{
    ///TODO: Step simulation.
}

void DefaultPhysics::VAddBox(const glm::vec3& dimensions, WeakActorPtr actor)
{

}

void DefaultPhysics::VRemoveActor(unsigned int actorID)
{

}

IGamePhysics* CreateDefaultGamePhysics()
{
    IGamePhysics* gamePhysics = new DefaultPhysics;

    if(gamePhysics && !gamePhysics->VInitialize())
    {
        delete gamePhysics;
        gamePhysics = nullptr;
    }

    return gamePhysics;
}

IGamePhysics* CreateGamePhyscis()
{
    ///TODO: Implement NullGamePhysics.
    return nullptr;
}