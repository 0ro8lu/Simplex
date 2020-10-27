#ifndef ZOMBIEGAME_SCREENELEMENTSCENE_H
#define ZOMBIEGAME_SCREENELEMENTSCENE_H

#include "SceneNodes/Scene.h"
#include "IScreenElement.h"

class ScreenElementScene : public IScreenElement, public Scene
{
public:

    ///TODO: Add renderer to parameter.
    ScreenElementScene() = default;
    virtual ~ScreenElementScene() { }

    // IScreenElement Implementation.
    void VOnUpdate() override  { OnUpdate(); }
    virtual void VOnRestore() { OnRestore(); }
    void VOnRender() override  { OnRender(); }

    //Don't handle any messages.
    bool VIsVisible() const override { return true; }
    bool VOnMsgProc(const AppMsg& msg) override { return false; }
    virtual bool VAddChild(unsigned int ActorID, ISceneNode* kid) { return Scene::AddChild(ActorID, kid); }
};

#endif //ZOMBIEGAME_SCREENELEMENTSCENE_H
