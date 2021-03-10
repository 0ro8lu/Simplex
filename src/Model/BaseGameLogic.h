#ifndef ZOMBIEGAME_BASEGAMELOGIC_H
#define ZOMBIEGAME_BASEGAMELOGIC_H

#include <vector>

#include "IGameLogic.h"
#include "Processes/ProcessManager.h"
#include "Actors/ActorFactory.h"
#include "View/HumanView.h"
#include "Physics/IGamePhysics.h"

#include "AI/AIView.h"

typedef std::map<unsigned int, std::shared_ptr<Actor>> ActorMap;

class BaseGameLogic : public IGameLogic
{
    friend class IApplication;

public:

    BaseGameLogic();

    virtual ~BaseGameLogic();

    WeakActorPtr VGetActor(unsigned int id) override;
    StrongActorPtr VCreateActor(const char* actorResource, const glm::vec2* pInitialPosition = nullptr, float angle = 0) override;
    void VDestroyActor(unsigned int id) override;
    void VOnUpdate() override;
    void VChangeState(BaseGameState newState) override;
    void VMoveActor(unsigned int id, const glm::vec2& position, const float angle) override;

    bool Init();

    unsigned int GetNewActorID()
    { return ++m_LastActorID; }

    const BaseGameState GetState() const
    { return m_GameState; }

    virtual IGamePhysics*& VGetGamePhysics()
    { return m_pGamePhysics; }

    virtual void VAddView(IGameView* pView, unsigned int actorID = 0);

    void testFunction();

protected:

    virtual ActorFactory* VCreateActorFactory();

    ProcessManager* m_pProcessManager;
    IGamePhysics* m_pGamePhysics;

    ActorFactory* m_pActorFactory;
    ActorMap m_Actors;
    unsigned int m_LastActorID;

    std::vector<IGameView*> m_GameViews;

    BaseGameState m_GameState;
};

#endif //ZOMBIEGAME_BASEGAMELOGIC_H
