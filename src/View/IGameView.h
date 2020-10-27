#ifndef ZOMBIEGAME_IGAMEVIEW_H
#define ZOMBIEGAME_IGAMEVIEW_H

#include "AppMsg.h"

enum GameViewType
{
    GV_Human,
    GV_Remote,
    GV_AI,
    GV_Recorder,
    GV_Other
};

class IGameView
{
public:
    virtual ~IGameView() = default;

    /*
     virtual void VOnRestore() = 0;
     virtual void VOnLostDevice() = 0;

     */
public:
    virtual void VOnRender() = 0; ///TODO: Implement all the parameters.
    virtual GameViewType VGetType() = 0;
    virtual unsigned int VGetID() const = 0;
    virtual void VOnAttach(unsigned int viewID, unsigned int actorID) = 0;
    virtual bool VOnMsgProc(const AppMsg& msg) = 0;
    virtual void VOnUpdate() = 0;
};

#endif //ZOMBIEGAME_IGAMEVIEW_H
