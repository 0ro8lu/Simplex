#ifndef ZOMBIEGAME_MEMBERDELEGATE_H
#define ZOMBIEGAME_MEMBERDELEGATE_H

#include "IDelegate.h"

#include <string>

template<typename T>
class MemberDelegate : public IDelegate
{
    friend class EventManager;

public:
    MemberDelegate(T* obj, void (T::*Function)(const EventPointer& pEvent))
            : p_Obj(obj), p_FunctionPointer(Function)
    {}

    bool invoke(const EventPointer& pEvent) override
    {
        (p_Obj->*p_FunctionPointer)(pEvent);
        return true;
    }

private:
    T* p_Obj;

    void (T::*p_FunctionPointer)(const EventPointer& pEvent);
};

#endif //ZOMBIEGAME_MEMBERDELEGATE_H
