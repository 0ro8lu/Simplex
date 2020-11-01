#ifndef ZOMBIEGAME_AIVIEW_H
#define ZOMBIEGAME_AIVIEW_H

#include "View/IGameView.h"
#include "Processes/ProcessManager.h"

#include "EventManager.h"
#include "StartThrustEvent.h"

#include "Processes/ProcessType/DelayProcess.h"
#include "Processes/ProcessType/PrintProcess.h"

class AIView : public IGameView
{
public:

    AIView();
    ~AIView();

    void Init();

    void VOnRender() override { }
    GameViewType VGetType() override { return GV_AI; }
    unsigned int VGetID() const override { return m_ViewID; }
    void VOnAttach(unsigned int viewID, unsigned int actorID) override { m_ViewID = viewID; m_PlayerActorID = actorID; }
    bool VOnMsgProc(const AppMsg &msg) override { return true; } ///TODO: Maybe return false? check source code of "TeapotWarsView.h" at line 169.
    void VOnUpdate() override;

protected:
    unsigned int m_ViewID;
    unsigned int m_PlayerActorID;

private:
    ProcessManager* m_pProcessManager;
};

#endif //ZOMBIEGAME_AIVIEW_H
