#ifndef ZOMBIEGAME_TESTGAMEVIEW_H
#define ZOMBIEGAME_TESTGAMEVIEW_H

#include "HumanView.h"
#include "Controller/TestController.h"

class TestGameView : public HumanView
{
public:
    TestGameView(SpriteRenderer &renderer);
    ~TestGameView();

    bool VOnMsgProc(const AppMsg& msg) override;
    void VOnUpdate() override;
    void VOnAttach(unsigned int viewID, unsigned int actorID) override;

    void VSetControlledActor(unsigned int actorID) override;

    void SetControlledActorDelegate(EventPointer pEventData);
protected:
    ///TODO: Add SceneNode referring to this game view.
    SceneNode*      m_pObject;
    TestController* m_pTestController;

private:
    void RegisterAllDelegates();
    void RemoveAllDelegates();
};

#endif //ZOMBIEGAME_TESTGAMEVIEW_H
