#ifndef ZOMBIEGAME_ADVANCED2DPHYSICS_H
#define ZOMBIEGAME_ADVANCED2DPHYSICS_H

#include "Box2DPhysics.h"

class Advanced2DPhysics : public Box2DPhysics
{
public:
    bool VInitialize() override;
    void VAddBox(StrongActorPtr pActor, bool isStatic) override;
};

#endif //ZOMBIEGAME_ADVANCED2DPHYSICS_H
