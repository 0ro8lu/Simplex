#ifndef ZOMBIEGAME_IGAMELOGIC_H
#define ZOMBIEGAME_IGAMELOGIC_H

#include <ext.hpp>
#include <glm.hpp>

#include "Actors/Actor.h"

enum BaseGameState
{
    BGS_Invalid,
    BGS_Initializing,
    BGS_MainMenu,
    BGS_LoadingGameEnvironment,
    BGS_SpawningPlayerActors,
    BGS_Running
};

class IGameLogic
{
public:
    virtual WeakActorPtr   VGetActor(unsigned int id) = 0;
    virtual StrongActorPtr VCreateActor(const char *actorResource, const glm::vec2* pInitialPosition = nullptr, float angle = 0) = 0; ///TODO: Add all the parameters for actor creation.
    virtual void           VDestroyActor(unsigned int id) = 0;
    virtual void VMoveActor(unsigned int id, const glm::vec2& position, const float angle) = 0;

    ///TODO: Implement LevelManager
    //virtual bool         VLoadGame(const char* levelResource) = 0;
    virtual void           VOnUpdate() = 0;
    virtual void           VChangeState(BaseGameState newState) = 0;
};

#endif //ZOMBIEGAME_IGAMELOGIC_H
