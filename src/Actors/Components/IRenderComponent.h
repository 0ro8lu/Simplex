#ifndef ZOMBIEGAME_IRENDERCOMPONENT_H
#define ZOMBIEGAME_IRENDERCOMPONENT_H

#include "Actors/ActorComponent.h"

class SceneNode;

class IRenderComponent : public ActorComponent
{
    ///TODO: Maybe make this a unique_ptr;
    virtual SceneNode* VGetSceneNode() = 0;
};

#endif //ZOMBIEGAME_IRENDERCOMPONENT_H
