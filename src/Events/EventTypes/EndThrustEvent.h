#ifndef ZOMBIEGAME_ENDTHRUSTEVENT_H
#define ZOMBIEGAME_ENDTHRUSTEVENT_H

#include "Event.h"

class EndThrustEvent : public Event
{
public:

    EndThrustEvent()
        : Event(StaticName())
    {
        m_ActorID = 0;
    }

    EndThrustEvent(unsigned int actorID)
        : Event(StaticName()), m_ActorID(actorID)
    {}

    unsigned int GetActorID() const { return m_ActorID; }

    static const char* StaticName() { return "EndThrustEvent"; }

private:

    unsigned int m_ActorID;
};

#endif //ZOMBIEGAME_ENDTHRUSTEVENT_H
