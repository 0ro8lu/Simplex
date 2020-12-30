#include "DefaultPhysics.h"

#include "Utilities/PrintUtils.h"

glm::vec2 DefaultPhysics::m_MousePos;

DefaultPhysics::DefaultPhysics() = default;

DefaultPhysics::~DefaultPhysics()
{
    for (auto& it : m_actorIDToMatrix)
    {
        delete it.second;
        it.second = nullptr;
    }

    m_actorIDToMatrix.clear();
}

bool DefaultPhysics::VInitialize()
{
    return true;
}

void DefaultPhysics::VSyncVisibleScene()
{

    for (auto& it : m_actorIDToMatrix)
    {
        unsigned int actorID = it.first;
        glm::mat4* physicsMat = it.second;

        StrongActorPtr pGameActor = std::shared_ptr<Actor>(g_pApp->GetGameLogic()->VGetActor(actorID));
        if (pGameActor && physicsMat)
        {
            auto* pTransformComponent = pGameActor->GetComponentRaw<TransformComponent>(
                    TransformComponent::GetComponentName());
            if (pTransformComponent)
            {
                glm::mat4 transform = pTransformComponent->GetTransform();
                if (transform != *physicsMat)
                {
                    pTransformComponent->SetTransform(*physicsMat);
                    ///TODO: send a Move_Actor Event.
                }
            } else
            {
                std::cout << "ERROR: DefaultPhysics::VSyncVisibleScene: actor " << actorID
                          << " has no TransformComponent\n";
                return;
            }
        }
    }

    ///TODO: Check if actor has moved.
}

void DefaultPhysics::VOnUpdate()
{
    ///TODO: Clear out these comments.

    /*for(auto it : m_actorIDToMatrix)
    {
        ///TODO: Add Pair to m_actorIDToMatrix so that we don't have to allocate
        ///A tmp Rect every single time.
        Rect tmpRect{};
        m_Rect.size = { (*it.second)[0][0], (*it.second)[1][1] };
        m_Rect.pos  = { ((*it.second)[3].x - (m_Rect.size.x / 2)), ((*it.second)[3].y - (m_Rect.size.y / 2)) };

        //DynamicRectVsRect()

        // Chiamare DynamicRectVsRect() con i param. giusti.
        // Aggiungere il risultato a un buffer z.
    }*/

    // Fare un sort su Z
    // Risolvere la collisione.
    // Aggiornare pos. player.






    /*m_RayDirection = m_MousePos - m_RayPoint;
    //std::cout << "DefaultPhysics::VOnUpdate m_RayDirection (X: " << m_RayDirection.x << ", Y: " << m_RayDirection.y << " )" << "\n";

    glm::vec2 cp, cn;
    float t;

    if (RayVsRect(m_RayPoint, m_RayDirection, m_Rect, cp, cn, t) && t <= 1)
    {
        glm::vec2 normal = cp + cn;
        //std::cout << "DefaultPhysics::VOnUpdate: Collision occurred at (X: " << cp.x << ", Y: " << cp.y << " )\n";
        //std::cout << "DefaultPhysics::VOnUpdate: Collision Normal (X: " << normal.x << " ,Y " << normal.y << " )\n";
    }*/
}

void DefaultPhysics::VApplyForce(float verticalAcceleration, float horizontalAcceleration, unsigned int actorID)
{
    if (glm::mat4* physMat = FindPhysicsMatrix(actorID))
    {
        *physMat = glm::translate(*physMat, glm::vec3(horizontalAcceleration, verticalAcceleration, 0.0f));
    }
}

void DefaultPhysics::VAddBox(const glm::vec2& dimensions, StrongActorPtr actor)
{
    if (!actor)
    {
        std::cout << "ERROR! In DefaultPhysics VAddBox invalid actor pointer\n";
        return;
    }

    ///TODO: Check if actor already has a rigid body.

    glm::mat4 transform = glm::mat4(1.0f);
    auto* m_pTransformComponent = actor->GetComponentRaw<TransformComponent>(TransformComponent::GetComponentName());

    if (!m_pTransformComponent)
    {
        std::cout << "ERROR!: In DefaultPhysics VAddBox actor " << actor->GetID() << " has no TransformComponent!\n";
        return;
    }

    transform = m_pTransformComponent->GetTransform();
    m_actorIDToMatrix[actor->GetID()] = new glm::mat4(transform);
}

void VAddCircle(float radius, const WeakActorPtr& actor)
{

}

void DefaultPhysics::VRemoveActor(unsigned int actorID)
{

}

void DefaultPhysics::VAddCircle(float radius, const WeakActorPtr& actor)
{

}

IGamePhysics* CreateDefaultGamePhysics()
{
    IGamePhysics* gamePhysics = new DefaultPhysics;

    if (gamePhysics && !gamePhysics->VInitialize())
    {
        delete gamePhysics;
        gamePhysics = nullptr;
    }

    return gamePhysics;
}

IGamePhysics* CreateNullPhysics()
{
    ///TODO: Implement NullGamePhysics.
    return nullptr;
}

glm::mat4* DefaultPhysics::FindPhysicsMatrix(unsigned int actorID)
{
    auto found = m_actorIDToMatrix.find(actorID);
    if (found != m_actorIDToMatrix.end())
        return found->second;

    return nullptr;
}

bool DefaultPhysics::RayVsRect(const glm::vec2& ray_origin, const glm::vec2& ray_dir, const Rect& target,
                               glm::vec2& contact_point, glm::vec2& contact_normal, float& t_hit_near)
{
    contact_normal = {0, 0};
    contact_point = {0, 0};

    // Cache division
    glm::vec2 invdir = 1.0f / ray_dir;

    // Calculate intersections with rectangle bounding axes
    glm::vec2 t_near = (target.pos - ray_origin) * invdir;
    glm::vec2 t_far = (target.pos + target.size - ray_origin) * invdir;

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    t_hit_near = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contact_point = ray_origin + t_hit_near * ray_dir;

    if (t_near.x > t_near.y)
        if (invdir.x < 0)
            contact_normal = {1, 0};
        else
            contact_normal = {-1, 0};
    else if (t_near.x < t_near.y)
        if (invdir.y < 0)
            contact_normal = {0, 1};
        else
            contact_normal = {0, -1};

    // Note if t_near == t_far, collision is principly in a diagonal
    // so pointless to resolve. By returning a CN={0,0} even though its
    // considered a hit, the resolver wont change anything.
    return true;
}

bool DefaultPhysics::DynamicRectVsRect(const Rect* r_dynamic, const float fTimeStep, const Rect& r_static,
                                       glm::vec2& contact_point, glm::vec2& contact_normal, float& contact_time)
{
    // Check if dynamic rectangle is actually moving - we assume rectangles are NOT in collision to start
    if (r_dynamic->velocity.x == 0 && r_dynamic->velocity.y == 0)
        return false;

    // Expand target rectangle by source dimensions
    Rect expanded_target{};

    expanded_target.pos = r_static.pos - r_dynamic->size / glm::vec2(2, 2);
    expanded_target.size = r_static.size + r_dynamic->size;

    if (RayVsRect(r_dynamic->pos + r_dynamic->size / glm::vec2(2, 2), r_dynamic->velocity * fTimeStep, expanded_target,
                  contact_point, contact_normal, contact_time))
        return (contact_time >= 0.0f && contact_time < 1.0f);
    else
        return false;
}
