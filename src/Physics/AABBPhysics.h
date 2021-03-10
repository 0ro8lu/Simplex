#ifndef ZOMBIEGAME_AABBPHYSICS_H
#define ZOMBIEGAME_AABBPHYSICS_H

#include "Box2DPhysics.h"

class AABBPhysics : public Box2DPhysics
{
public:
    bool VInitialize() override;
    void VAddBox(StrongActorPtr pActor, bool isStatic) override;
};

#endif //ZOMBIEGAME_AABBPHYSICS_H
