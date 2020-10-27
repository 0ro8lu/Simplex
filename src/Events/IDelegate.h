#ifndef ZOMBIEGAME_IDELEGATE_H
#define ZOMBIEGAME_IDELEGATE_H

#include "Event.h"

class IDelegate
{
public:

    IDelegate() = default;
    virtual ~IDelegate() = default;

    virtual bool invoke(const EventPointer& pEvent) = 0;
private:
};

#endif //ZOMBIEGAME_IDELEGATE_H
