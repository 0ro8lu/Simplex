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

    virtual void VApplyForce(float verticalAcceleration, float horizontalAcceleration, unsigned int actorID) = 0;

    virtual void VAddBox(const glm::vec2& dimensions, StrongActorPtr actor) = 0;
    virtual void VAddCircle(float radius, const WeakActorPtr& actor) = 0; ///TODO: Implement Better.
    virtual void VRemoveActor(unsigned int actorID) = 0;

};

#endif //ZOMBIEGAME_IGAMEPHYSICS_H
