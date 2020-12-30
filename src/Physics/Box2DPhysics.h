#ifndef ZOMBIEGAME_BOX2DPHYSICS_H
#define ZOMBIEGAME_BOX2DPHYSICS_H

#include "NullGamePhysics.h"
#include "Actors/Components/TransformComponent.h"
#include "Utilities/templates.h"
#include "Model/IApplication.h"

#include <box2d.h>

class Box2DPhysics : public IGamePhysics
{
public:

    bool VInitialize() override;
    void VSyncVisibleScene() override;
    void VOnUpdate() override;

    void VAddBox(const glm::vec2& dimensions, StrongActorPtr pActor) override;
    void VAddCircle(float radius, StrongActorPtr pActor) override;
    void VRemoveActor(unsigned int actorID) override;

    void VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID) override;
    void VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID) override;

    std::map <unsigned int, std::pair<b2Body*,glm::vec2>> m_ActorIDToRigidBody;

private:
    b2World* m_pWorld;

    // Ratio between Box2D meters and pixels in the engine. 32 is a good compromise for performance.
    const float PPM = 32;
};

extern IGamePhysics* CreateGamePhysics();
extern IGamePhysics* CreateNullPhysics();

#endif //ZOMBIEGAME_BOX2DPHYSICS_H
