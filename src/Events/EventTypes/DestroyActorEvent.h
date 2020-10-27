#ifndef ZOMBIEGAME_DESTROYACTOREVENT_H
#define ZOMBIEGAME_DESTROYACTOREVENT_H

#include "Event.h"

class DestroyActorEvent : public Event
{
public:
    explicit DestroyActorEvent(unsigned int actorID = 0)
        : Event(StaticName()), m_ActorID(actorID)
    {}

    unsigned int GetActorID() const { return m_ActorID; }
    static const char* StaticName() { return "DestroyActorEvent"; }

private:
    unsigned int m_ActorID;
};

#endif //ZOMBIEGAME_DESTROYACTOREVENT_H
