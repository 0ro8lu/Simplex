#ifndef ZOMBIEGAME_STARTTHRUSTEVENT_H
#define ZOMBIEGAME_STARTTHRUSTEVENT_H

#include "Event.h"

class StartThrustEvent : public Event
{
public:
    StartThrustEvent()
        :Event(StaticName())
    {
        m_ActorID = 0;
        m_Acceleration = 0.0f;
    }

    StartThrustEvent(unsigned int actorID, float acceleration)
        : Event(StaticName())
    {
        m_ActorID = actorID;
        m_Acceleration = acceleration;
    }

    unsigned int GetActorID()      const { return m_ActorID; }
    float        GetAcceleration() const { return m_Acceleration; }

    ///TODO: Maybe have a SetActorID function.

    static const char* StaticName() { return "StartThrustEvent"; }

private:
    unsigned int m_ActorID;
    float        m_Acceleration;
};

#endif //ZOMBIEGAME_STARTTHRUSTEVENT_H
