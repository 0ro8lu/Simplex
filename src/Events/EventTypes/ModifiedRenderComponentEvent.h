#ifndef ZOMBIEGAME_MODIFIEDRENDERCOMPONENTEVENT_H
#define ZOMBIEGAME_MODIFIEDRENDERCOMPONENTEVENT_H

#include "Event.h"

class ModifiedRenderComponentEvent : public Event
{
public:
    explicit ModifiedRenderComponentEvent(unsigned int actorID)
        : Event(StaticName()), m_actorID(actorID)
    {}

    ModifiedRenderComponentEvent()
        : Event(StaticName()), m_actorID(0)
    {}

    const unsigned int GetActorID() const { return m_actorID; }

    static const char* StaticName() { return "ModifiedRenderComponentEvent"; }

private:
    unsigned int m_actorID;
};

#endif //ZOMBIEGAME_MODIFIEDRENDERCOMPONENTEVENT_H
