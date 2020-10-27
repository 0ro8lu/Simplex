#ifndef ZOMBIEGAME_ENDSTEEREVENT_H
#define ZOMBIEGAME_ENDSTEEREVENT_H

#include "Event.h"

class EndSteerEvent : public Event
{
public:

    EndSteerEvent()
        : Event(StaticName())
    {
        m_ActorID = 0;
    }

    EndSteerEvent(unsigned int actorID)
        : Event(StaticName()), m_ActorID(actorID)
    {}

    unsigned int GetActorID() const { return m_ActorID; }

    static const char* StaticName() { return "EndSteerEvent"; }

private:
    unsigned int m_ActorID;
};

#endif //ZOMBIEGAME_ENDSTEEREVENT_H
