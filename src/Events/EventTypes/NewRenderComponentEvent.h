#ifndef ZOMBIEGAME_NEWRENDERCOMPONENTEVENT_H
#define ZOMBIEGAME_NEWRENDERCOMPONENTEVENT_H

#include "Event.h"

class NewRenderComponentEvent : public Event
{
public:
    explicit NewRenderComponentEvent(unsigned int actorID, SceneNode* pSceneNode)
        : Event(StaticName()), m_actorID(actorID), m_pSceneNode(pSceneNode)
    {}

    NewRenderComponentEvent()
        : Event(StaticName()), m_actorID(0), m_pSceneNode(nullptr)
    {}

    const unsigned int GetActorID() const { return m_actorID; }
    SceneNode* GetSceneNode() const { return m_pSceneNode; }

    static const char* StaticName() { return "NewRenderComponentEvent"; }

private:
    unsigned int m_actorID;
    SceneNode* m_pSceneNode;
};

#endif //ZOMBIEGAME_NEWRENDERCOMPONENTEVENT_H
