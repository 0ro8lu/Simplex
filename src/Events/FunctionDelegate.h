#ifndef ZOMBIEGAME_FUNCTIONDELEGATE_H
#define ZOMBIEGAME_FUNCTIONDELEGATE_H

#include "IDelegate.h"

class FunctionDelegate : public IDelegate
{
    friend class EventManager;

public:
    explicit FunctionDelegate(void (*Function)(const EventPointer& pEvent))
            : p_FunctionPointer(Function)
    {}

    bool invoke(const EventPointer& pEvent) override
    {
        p_FunctionPointer(pEvent);
        return true;
    }

private:
    void (*p_FunctionPointer)(const EventPointer& pEvent);
};

#endif //ZOMBIEGAME_FUNCTIONDELEGATE_H
