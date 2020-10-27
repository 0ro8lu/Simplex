#ifndef ZOMBIEGAME_RENDERCOMPONENT_H
#define ZOMBIEGAME_RENDERCOMPONENT_H

#include <glm.hpp>

#include "IRenderComponent.h"

#include "NewRenderComponentEvent.h"
#include "ModifiedRenderComponentEvent.h"

#include "EventManager.h"

class RenderComponent : public IRenderComponent
{
public:
    bool VInit(tinyxml2::XMLElement* pData) override;
    void VPostInit() override;
    void VOnChanged() override;
    tinyxml2::XMLElement* VGenerateXml() override;

    static const char* GetComponentName() { return "RenderComponent"; }
    const char* VGetComponentName() const override { return GetComponentName(); }

protected:

    virtual bool VDelegateInit(tinyxml2::XMLElement* pData) { return true; }
    virtual SceneNode * VCreateSceneNode() = 0;

    SceneNode* m_pSceneNode;
private:
    SceneNode* VGetSceneNode() override;
};

class SpriteRenderComponent : public RenderComponent
{
public:
    static const char* GetComponentName() { return "SpriteRenderComponent"; }

protected:
    void VPostInit() override;
    bool VDelegateInit(tinyxml2::XMLElement* pData) override;
    SceneNode* VCreateSceneNode() override;

private:
    glm::vec2 m_Size;

    const char* m_TextureName;
};

#endif //ZOMBIEGAME_RENDERCOMPONENT_H
