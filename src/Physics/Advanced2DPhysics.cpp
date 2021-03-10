#include "Advanced2DPhysics.h"

bool Advanced2DPhysics::VInitialize()
{
    m_Gravity = {0, -9.0f};
    return Box2DPhysics::VInitialize();
}

void Advanced2DPhysics::VAddBox(StrongActorPtr pActor, bool isStatic)
{
    Box2DPhysics::VAddBox(pActor, isStatic);
}

IGamePhysics* CreateAdvancedPhysics()
{
    IGamePhysics* pGamePhysics = new Advanced2DPhysics;

    if (pGamePhysics)
    {
        if (!pGamePhysics->VInitialize())
        {
            delete pGamePhysics;
            pGamePhysics = nullptr;
        }
        return pGamePhysics;
    }
    return nullptr;
}
