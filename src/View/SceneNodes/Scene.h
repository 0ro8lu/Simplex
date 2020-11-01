#ifndef ZOMBIEGAME_SCENE_H
#define ZOMBIEGAME_SCENE_H

#include <map>

#include "ISceneNode.h"
#include "Events/EventManager.h"
#include "DestroyActorEvent.h"

#include "RootNode.h"
#include "CameraNode.h"

#include "Rendering/SpriteRenderer.h"

class Scene
{
public:

    ///TODO: Add Interface class to renderer. Don't just pass SpriteRenderer.
    Scene(SpriteRenderer &renderer);

    virtual ~Scene();

    void OnRender();
    void OnRestore();
    void OnLostDevice();
    void OnUpdate();
    ISceneNode* FindActor(unsigned int actorID);
    bool AddChild(unsigned int actorID, ISceneNode* child);
    bool RemoveChild(unsigned int actorID);

    void NewRenderComponentDelegate(const EventPointer& pEventData);
    void ModifiedRenderComponentDelgate(const EventPointer& pEventData);
    void DestroyActorDelegate(const EventPointer& pEventData);

    void SetCamera(CameraNode* pCamera) { m_pCamera = pCamera; }
    CameraNode* GetCamera() const { return m_pCamera; }
    SpriteRenderer* GetRenderer() const { return m_pRenderer; }

    ///TODO: Implement all the rest.

protected:
    ///TODO: SceneNode Pointer;
    ///TODO: Implement all the rest.

    std::map<unsigned int, ISceneNode*> m_ActorMap;

    std::unique_ptr<SceneNode> m_pRoot;
    CameraNode* m_pCamera;
    SpriteRenderer* m_pRenderer;
};

#endif //ZOMBIEGAME_SCENE_H
