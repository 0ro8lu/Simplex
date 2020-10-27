#include "TestGameLogic.h"

#include "TestGameView.h"

TestGameLogic::TestGameLogic()
{
    m_ThrustCount = m_SteerCount = 0;

    RegisterAllDelegates();
}

TestGameLogic::~TestGameLogic()
{
    //VDestroyActor(m_pActor->GetID());
    RemoveAllDelegates();
}

void TestGameLogic::StartThrustDelegate(const EventPointer& pEvent)
{
    ///TODO: Revisit this whole MakeStrongPtr thing, i don't like it.
    StartThrustEvent* pCastEvent = (StartThrustEvent*)pEvent;
    StrongActorPtr pActor = MakeStrongPtr(VGetActor(pCastEvent->GetActorID()));

    if(pActor)
    {
        auto pPhysicsComponent = MakeStrongPtr(pActor->GetComponent<PhysicsComponent>(PhysicsComponent::GetComponentName()));
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
        EndThrustEvent *pCastEvent = (EndThrustEvent *) pEvent;
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
    StartSteerEvent* pCastEvent = (StartSteerEvent*)pEvent;
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
        EndSteerEvent *pCastEvent = (EndSteerEvent *) pEvent;
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