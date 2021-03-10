#ifndef ZOMBIEGAME_NULLGAMEPHYSICS_H
#define ZOMBIEGAME_NULLGAMEPHYSICS_H

#include "IGamePhysics.h"

class NullGamePhysics : public IGamePhysics
{
public:
    bool VInitialize() override{ return true; }
    void VSyncVisibleScene() override { }
    void VOnUpdate() override { }

    void VAddBox(StrongActorPtr pActor, bool isRigid) override { }
    void VAddCircle(float radius, StrongActorPtr pActor, bool isRigid) override { }
    void VRemoveActor(unsigned int actorID) override { }

    void VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID) override { }
    void VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID) override { }

    void VSetPosition(unsigned int actorID, const glm::vec2& vec) override { }
    void VSetTransform(unsigned int actorID, const glm::mat4& mat) override { }
    void VSetRotation(unsigned int actorID, float angle) override { }

};

#endif //ZOMBIEGAME_NULLGAMEPHYSICS_H
