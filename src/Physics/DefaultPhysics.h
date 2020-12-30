#ifndef ZOMBIEGAME_DEFAULTPHYSICS_H
#define ZOMBIEGAME_DEFAULTPHYSICS_H

///TODO: Add Physics Events.

#include <map>

#include "Actors/Components/TransformComponent.h"
#include "IGamePhysics.h"
#include "Model/IApplication.h"

///TODO: Let physics system handle boxes and many other shapes.

struct Rect
{
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 velocity;
};

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
    std::map<unsigned int, glm::mat4*> m_actorIDToMatrix;

    // ------- Functions Specific to this Physics Scheme ----------

    bool RayVsRect(const glm::vec2& ray_origin, const glm::vec2& ray_dir, const Rect& target, glm::vec2& contact_point,
                   glm::vec2& contact_normal, float& t_hit_near);

    bool DynamicRectVsRect(const Rect* r_dynamic, const float fTimeStep, const Rect& r_static,
                           glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time);

    ///TODO: Remove this.
    static void setMouse(glm::vec2 mousePos)
    { m_MousePos = mousePos; }

private:
    glm::mat4* FindPhysicsMatrix(unsigned int actorID);

    ///TODO: Remove these.
    glm::vec2 m_RayPoint = {20.0f, 20.0f};
    glm::vec2 m_RayDirection{};
    static glm::vec2 m_MousePos;
    Rect m_Rect{};
};

extern IGamePhysics* CreateDefaultGamePhysics();

extern IGamePhysics* CreateNullPhysics();

#endif //ZOMBIEGAME_DEFAULTPHYSICS_H
