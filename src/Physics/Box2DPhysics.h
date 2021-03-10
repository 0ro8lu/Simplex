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

    void VAddBox(StrongActorPtr pActor, bool isStatic) override;
    void VAddCircle(float radius, StrongActorPtr pActor, bool isStatic) override;
    void VRemoveActor(unsigned int actorID) override;

    void VApplyForce(const glm::vec2& dir, float newtons, unsigned int actorID) override;
    void VApplyTorque(const glm::vec2& dir, float newtons, unsigned int actorID) override;

    void VSetPosition(unsigned int actorID, const glm::vec2& vec) override;
    void VSetTransform(unsigned int actorID, const glm::mat4& mat) override;
    void VSetRotation(unsigned int actorID, float angle) override;

    std::map <unsigned int, b2Body*> m_ActorIDToRigidBody;

protected:
    b2Body* FindBox2DRigidBody(unsigned int actorID) const;

    b2World* m_pWorld;
    b2Vec2   m_Gravity;

    // Ratio between Box2D meters and pixels in the engine. 32 is a good compromise for performance.
    const float PPM = 32;

    float m_newXCoord, m_newYCoord;
    float m_newX1Rot, m_newX2Rot;
    float m_newY1Rot, m_newY2Rot;
    float m_YScale, m_XScale;
};

extern IGamePhysics* CreateAABBPhysics();
extern IGamePhysics* CreateAdvancedPhysics();
extern IGamePhysics* CreateNullPhysics();

#endif //ZOMBIEGAME_BOX2DPHYSICS_H
