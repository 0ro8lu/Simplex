#ifndef ZOMBIEGAME_NULLGAMEPHYSICS_H
#define ZOMBIEGAME_NULLGAMEPHYSICS_H

#include "IGamePhysics.h"

class NullGamePhysics : public IGamePhysics
{
public:
    bool VInitialize() override{ return true; }
    void VSyncVisibleScene() override { }
    void VOnUpdate() override { }

    void VAddBox(const glm::vec2& dimensions, StrongActorPtr pActor) override { }
    void VAddCircle(float radius, StrongActorPtr pActor) override { }
    void VRemoveActor(unsigned int actorID) override { }

    void VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID) override { }
    void VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID) override { }

};

#endif //ZOMBIEGAME_NULLGAMEPHYSICS_H
