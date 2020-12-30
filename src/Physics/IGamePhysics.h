#ifndef ZOMBIEGAME_IGAMEPHYSICS_H
#define ZOMBIEGAME_IGAMEPHYSICS_H

#include "glm.hpp"
#include "Actors/Actor.h"

class IGamePhysics
{
public:

    virtual ~IGamePhysics() = default;

    virtual bool VInitialize() = 0;
    virtual void VSyncVisibleScene() = 0;
    virtual void VOnUpdate() = 0;

    virtual void VAddBox(const glm::vec2& dimensions, StrongActorPtr pActor) = 0;
    virtual void VAddCircle(float radius, StrongActorPtr pActor) = 0;
    virtual void VRemoveActor(unsigned int actorID) = 0;

    virtual void VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID) = 0;
    virtual void VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID) = 0;
};

#endif //ZOMBIEGAME_IGAMEPHYSICS_H
