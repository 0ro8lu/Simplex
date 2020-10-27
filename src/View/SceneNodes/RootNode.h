#ifndef ZOMBIEGAME_ROOTNODE_H
#define ZOMBIEGAME_ROOTNODE_H

#include "SceneNode.h"

class RootNode : public SceneNode
{
public:
    RootNode();

private:
    bool VAddChild(ISceneNode* kid) override;
    bool VRemoveChild(unsigned int ActorID) override;

    void VRenderChildren(Scene* pScene) override;

    SceneNode* m_pStaticGroup;
    SceneNode* m_pActorGroup;
    SceneNode* m_pBackGroundGroup;
    SceneNode* m_pInvisibleGroup;
};

#endif //ZOMBIEGAME_ROOTNODE_H
