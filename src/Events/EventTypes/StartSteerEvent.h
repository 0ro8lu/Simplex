#ifndef ZOMBIEGAME_STARTSTEEREVENT_H
#define ZOMBIEGAME_STARTSTEEREVENT_H

#include "Event.h"

///TODO: This is literally the same class as StartThrust, probably merge them together.

class StartSteerEvent : public Event
{
public:

    StartSteerEvent()
        : Event(StaticName())
    {
        m_ActorID = 0;
        m_Acceleration = 0.0f;
    }

    StartSteerEvent(unsigned int actorID, float acceleration)
        : Event(StaticName())
    {
        m_ActorID = actorID;
        m_Acceleration = acceleration;
    }

    unsigned int GetActorID()      const { return m_ActorID; }
    float        GetAcceleration() const { return m_Acceleration; }

    static const char* StaticName() { return "StartSteerEvent"; }

private:
    unsigned int m_ActorID;
    float        m_Acceleration;
};

#endif //ZOMBIEGAME_STARTSTEEREVENT_H
