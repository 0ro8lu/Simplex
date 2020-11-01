#ifndef ZOMBIEGAME_TESTGAMELOGIC_H
#define ZOMBIEGAME_TESTGAMELOGIC_H

#include "Model/BaseGameLogic.h"

class TestGameLogic : public BaseGameLogic
{
public:

    TestGameLogic();
    virtual ~TestGameLogic();

    void StartThrustDelegate(const EventPointer& pEvent);
    void EndThrustDelegate(const EventPointer& pEvent);
    void StartSteerDelegate(const EventPointer& pEvent);
    void EndSteerDelegate(const EventPointer& pEvent);

    void testFunction2();

private:
    void RegisterAllDelegates();
    void RemoveAllDelegates();

    short m_ThrustCount;
    short m_SteerCount;

    //std::shared_ptr<Actor> m_pActor;
};

#endif //ZOMBIEGAME_TESTGAMELOGIC_H
