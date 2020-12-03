#ifndef ZOMBIEGAME_DEFAULTPHYSICS_H
#define ZOMBIEGAME_DEFAULTPHYSICS_H

///TODO: Add Physics Events.

#include <map>

#include "Actors/Components/TransformComponent.h"
#include "Rectangle.h"
#include "IGamePhysics.h"
#include "Model/IApplication.h"

///TODO: Let physics system handle boxes and many other shapes.

class DefaultPhysics : public IGamePhysics
{
public:

    DefaultPhysics();
    virtual ~DefaultPhysics();

    bool VInitialize() override;

    void VSyncVisibleScene() override;
    void VOnUpdate() override;

    void VApplyForce(float verticalAcceleration, float horizontalAcceleration, unsigned int actorID) override;

    void VAddBox(const glm::vec2& dimensions, StrongActorPtr actor) override;
    void VAddCircle(float radius, const WeakActorPtr& actor) override;

    void VRemoveActor(unsigned int actorID) override;

    ///TODO: Refactor this, let it accept an interface for shape(?) maybe.
    std::map<unsigned int, glm::mat4*> m_actorIDToRectangle;

private:
    glm::mat4* FindPhysicsMatrix(unsigned int actorID);
};

extern IGamePhysics* CreateDefaultGamePhysics();
extern IGamePhysics* CreateNullPhysics();

#endif //ZOMBIEGAME_DEFAULTPHYSICS_H
