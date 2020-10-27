#ifndef ZOMBIEGAME_ISCENENODE_H
#define ZOMBIEGAME_ISCENENODE_H

#include "SceneNodeProperties.h"

class Scene;

class ISceneNode
{
public:
    virtual const SceneNodeProperties* const VGet() const = 0;

    virtual ~ISceneNode() = default;

    ///TODO: Implement this.
    /*
     * virtual void VSetTransform() = 0;
     * virtual HRESULT VOnRestore() = 0;
     * virtual HRESULT VPreRender() = 0;
     * virtual HRESULT VOnLostDevice() = 0;
     * virtual HRESULT VPick() = 0;
     */

    virtual void VOnUpdate() = 0;

    virtual bool VAddChild(ISceneNode* kid) = 0;
    virtual bool VRemoveChild(unsigned int actorID) = 0;
    virtual bool VPreRender(Scene* pScene) = 0;
    virtual void VRender(Scene* pScene) = 0;
    virtual bool VPostRender(Scene* pScene) = 0;
    virtual void VRenderChildren(Scene* pScene) = 0;
};

#endif //ZOMBIEGAME_ISCENENODE_H
