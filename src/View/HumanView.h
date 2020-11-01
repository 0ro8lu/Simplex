#ifndef ZOMBIEGAME_HUMANVIEW_H
#define ZOMBIEGAME_HUMANVIEW_H

#include <list>

#include "IGameView.h"
#include "Actors/Actor.h"
#include "Processes/ProcessManager.h"
#include "Model/BaseGameLogic.h"
#include "IScreenElement.h"
#include "ScreenElementScene.h"

#include "Controller/IKeyboardHandler.h"
#include "Controller/IPointerHandler.h"
#include "SceneNodes/CameraNode.h"

class HumanView : public IGameView
{
    friend class IApplication;

private:
    void RegisterAllDelegates();
    void RemoveAllDelegates();

public:

    HumanView(SpriteRenderer &renderer);
    virtual ~HumanView();

    bool LoadGame(tinyxml2::XMLElement* pLevelData);

    void VOnRender() override;
    GameViewType VGetType() override     { return GV_Human; }
    unsigned int VGetID() const override { return m_ViewID; }
    void VOnAttach(unsigned int viewID, unsigned int actorID) override;
    bool VOnMsgProc(const AppMsg& msg) override;
    void VOnUpdate() override;

    virtual void VPushElement(IScreenElement* pElement);
    virtual void VRemoveElement(IScreenElement* pElement);
    ///TODO: void TogglePause(bool active);
    std::list<IScreenElement*> m_ScreenElementList; ///TODO: Maybe change this into a vector ;)

    ///TODO: Implement these inside sandbox, in a class that inherits from this HumanView.
    IKeyboardHandler* m_KeyboardHandler;
    IPointerHandler*  m_PointerHandler;

    ProcessManager* GetProcessManager() const { return m_ProcessManager; }

    ScreenElementScene* m_pScene;
    CameraNode*         m_pCamera;

    void HandleGameState(BaseGameState newState);
    virtual void VSetControlledActor(unsigned int actorID) { m_ActorID = actorID; }

protected:

    unsigned int m_ViewID;
    unsigned int m_ActorID;

    ProcessManager* m_ProcessManager;
    BaseGameState m_BaseGameState;

    virtual bool VLoadGameDelegate(tinyxml2::XMLElement* pLevelData) { VPushElement(m_pScene); return true; }

    //TODO: virtual void VRenderText() { };
};


#endif //ZOMBIEGAME_HUMANVIEW_H
