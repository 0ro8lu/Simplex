#ifndef ZOMBIEGAME_DEFAULTPHYSICS_H
#define ZOMBIEGAME_DEFAULTPHYSICS_H

///TODO: Add Physics Events.

#include "IGamePhysics.h"

class DefaultPhysics : public IGamePhysics
{
public:

    DefaultPhysics();
    virtual ~DefaultPhysics();

    bool VInitialize() override;

    void VSyncVisibleScene() override;
    void VOnUpdate() override;

    void VAddBox(const glm::vec3& dimensions, WeakActorPtr actor) override;
    void VRemoveActor(unsigned int actorID) override;
};

extern IGamePhysics* CreateDefaultGamePhysics();
extern IGamePhysics* CreateNullPhysics();

#endif //ZOMBIEGAME_DEFAULTPHYSICS_H
