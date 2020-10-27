#ifndef ZOMBIEGAME_TESTCONTROLLER_H
#define ZOMBIEGAME_TESTCONTROLLER_H

#include "IPointerHandler.h"
#include "IKeyboardHandler.h"
#include "SceneNodes/SceneNode.h"

///TODO: Add all these event in a single file.

#include "StartThrustEvent.h"
#include "EndThrustEvent.h"
#include "StartSteerEvent.h"
#include "EndSteerEvent.h"

class TestController : public IPointerHandler, public IKeyboardHandler
{
public:
    explicit TestController(SceneNode* object);

    void OnUpdate();

    bool VOnPointerMove(int x, int y) override { return true; }
    bool VOnPointerButtonDown(int x, int y, int key) override { return true; }
    bool VOnPointerButtonUp(int x, int y, int key) override { return true; }

    bool VOnKeyDown(short key) override;
    bool VOnKeyUp(short key)   override;

private:
    SceneNode* m_Object;
};

#endif //ZOMBIEGAME_TESTCONTROLLER_H
