#ifndef ZOMBIEGAME_ACTORCOMPONENT_H
#define ZOMBIEGAME_ACTORCOMPONENT_H

#include <memory>
#include "tinyxml2.h"

class Actor;

const unsigned int INVALID_COMPONENT_ID = 0;

class ActorComponent
{
    friend class ActorFactory;

public:
    ActorComponent() = default;
    virtual ~ActorComponent() = default;

    virtual bool VInit(tinyxml2::XMLElement* pData) = 0;
    virtual void VPostInit() { }
    virtual void VUpdate() { }
    virtual void VOnChanged() { }

    virtual tinyxml2::XMLElement* VGenerateXml() = 0;

    virtual const char*  VGetComponentName() const = 0;
    virtual unsigned int VGetComponentID()   const { return GetIDFromName(VGetComponentName()); }

    static constexpr unsigned int GetIDFromName(const char* componentName)
    {
        //Simple hasing function
        unsigned int h = 0;
        const char* p = nullptr;

        for(p = componentName; *p != '\0'; p++)
        {
            h = 31 * h + *p;
        }

        return h;
    }

protected:
    std::shared_ptr<Actor> m_pOwner; ///TODO: make this a normal pointer.

private:
    ///TODO: Probably change this to pass a normal pointer.
    void SetOwner(std::shared_ptr<Actor> pOwner) { m_pOwner = pOwner; }
};

#endif //ZOMBIEGAME_ACTORCOMPONENT_H
