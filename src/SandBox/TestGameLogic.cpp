#include "TestGameLogic.h"

#include "TestGameView.h"
#include "Utilities/PrintUtils.h"

TestGameLogic::TestGameLogic()
{
    m_ThrustCount = m_SteerCount = 0;

    m_pGamePhysics = CreateAdvancedPhysics();

    RegisterAllDelegates();
}

TestGameLogic::~TestGameLogic()
{
    RemoveAllDelegates();
}

void TestGameLogic::StartThrustDelegate(const EventPointer& pEvent)
{
    ///TODO: Revisit this whole MakeStrongPtr thing, i don't like it.
    auto* pCastEvent = (StartThrustEvent*)pEvent;
    StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEvent->GetActorID()));

    if(pActor)
    {
        std::shared_ptr<PhysicsComponent> pPhysicsComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::GetComponentName()));
        if(pPhysicsComponent)
        {
            pPhysicsComponent->ApplyVerticalAcceleration(pCastEvent->GetAcceleration());
        }
    }
    m_ThrustCount++;
}

void TestGameLogic::EndThrustDelegate(EventPointer const &pEvent)
{

    if(m_ThrustCount != 2)
    {
        auto *pCastEvent = (EndThrustEvent *) pEvent;
        StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEvent->GetActorID()));

        if (pActor)
        {
            auto pPhysicsComponent = MakeStrongPtr(
                    pActor->GetComponent<PhysicsComponent>(PhysicsComponent::GetComponentName()));
            if (pPhysicsComponent)
            {
                pPhysicsComponent->ApplyVerticalAcceleration(0);
            }
        }
    }
    m_ThrustCount--;
}

void TestGameLogic::StartSteerDelegate(EventPointer const &pEvent)
{
    auto* pCastEvent = (StartSteerEvent*)pEvent;
    StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEvent->GetActorID()));

    if(pActor)
    {
        auto pPhysicsComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::GetComponentName()));
        if(pPhysicsComponent)
        {
            pPhysicsComponent->ApplyHorizontalAcceleration(pCastEvent->GetAcceleration());
        }
    }

    m_SteerCount++;
}

void TestGameLogic::EndSteerDelegate(EventPointer const &pEvent)
{
    if(m_SteerCount != 2)
    {
        auto *pCastEvent = (EndSteerEvent *) pEvent;
        StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEvent->GetActorID()));

        if (pActor)
        {
            auto pPhysicsComponent = MakeStrongPtr(
                    pActor->GetComponent<PhysicsComponent>(PhysicsComponent::GetComponentName()));
            if (pPhysicsComponent)
            {
                pPhysicsComponent->ApplyHorizontalAcceleration(0);
            }
        }
    }
    m_SteerCount--;
}


void TestGameLogic::RegisterAllDelegates()
{
    EventManager* pEventManager = EventManager::Get();

    pEventManager->registerMemberDelegate(StartThrustEvent::StaticName(), this, &TestGameLogic::StartThrustDelegate);
    pEventManager->registerMemberDelegate(EndThrustEvent::StaticName(), this, &TestGameLogic::EndThrustDelegate);

    pEventManager->registerMemberDelegate(StartSteerEvent::StaticName(), this, &TestGameLogic::StartSteerDelegate);
    pEventManager->registerMemberDelegate(EndSteerEvent::StaticName(), this, &TestGameLogic::EndSteerDelegate);
}

void TestGameLogic::RemoveAllDelegates()
{
    EventManager* pEventManager = EventManager::Get();

    pEventManager->unregisterMemberDelegate(StartThrustEvent::StaticName(), &TestGameLogic::StartThrustDelegate);
    pEventManager->unregisterMemberDelegate(EndThrustEvent::StaticName(), &TestGameLogic::EndThrustDelegate);

    pEventManager->unregisterMemberDelegate(StartSteerEvent::StaticName(), &TestGameLogic::StartSteerDelegate);
    pEventManager->unregisterMemberDelegate(EndSteerEvent::StaticName(), &TestGameLogic::EndSteerDelegate);
}

void BaseGameLogic::testFunction()
{
    auto aiv = new AIView;

    std::shared_ptr<Actor> m_pActor1 = VCreateActor("../Assets/Actors/TestActor.xml");

    glm::vec2 pos = {100, 10};
    std::shared_ptr<Actor> m_pActor2 = VCreateActor("../Assets/Actors/RigidPlatform.xml", &pos);

    //pos.x = 200; pos.y = 60;
    //std::shared_ptr<Actor> m_pActor3 = VCreateActor("../Assets/Actors/RigidPlatform.xml", &pos, 1.0f);

    for(auto& gameView : m_GameViews)
    {
        if (gameView->VGetType() == GV_Human)
        {
            auto pHumanView = static_cast<TestGameView*>(gameView);
            pHumanView->VSetControlledActor(m_pActor1->GetID());
        }
    }

    VAddView(aiv, m_pActor2->GetID());
    //VAddView(aiv, m_pActor3->GetID());
}