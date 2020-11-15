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

    virtual void VAddBox(const glm::vec3& dimensions, WeakActorPtr actor) = 0;
    virtual void VRemoveActor(unsigned int actorID) = 0;

};

#endif //ZOMBIEGAME_IGAMEPHYSICS_H
