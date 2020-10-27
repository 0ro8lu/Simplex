#ifndef ZOMBIEGAME_TESTCOMPONENT_H
#define ZOMBIEGAME_TESTCOMPONENT_H

#include "Actors/ActorComponent.h"

class TestComponent : public ActorComponent
{
public:
    bool VInit(tinyxml2::XMLElement *pData) override
    {
        tinyxml2::XMLElement* pAttributes = pData->FirstChildElement("TestVariable");
        if(!pAttributes)
        {
            std::cout << "ERROR!: Could not find attribute TestVariable in TestComponent\n";
            return false;
        }

        int data = 0;
        pAttributes->QueryIntAttribute("x", &data);
        std::cout << "TestVariable: " << data << "\n";

        return true;
    }

    static const char*  GetComponentName() { return "TestComponent"; }

    const char* VGetComponentName() const override
    {
        return GetComponentName();
    }

    tinyxml2::XMLElement *VGenerateXml() override
    {
        return nullptr;
    }

};

#endif //ZOMBIEGAME_TESTCOMPONENT_H
