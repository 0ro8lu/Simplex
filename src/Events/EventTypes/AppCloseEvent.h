#ifndef ZOMBIEGAME_APPCLOSEEVENT_H
#define ZOMBIEGAME_APPCLOSEEVENT_H

#include <iostream>

#include "Event.h"

class AppCloseEvent : public Event
{
public:
    AppCloseEvent()
        :Event(StaticName())
    {}

    ~AppCloseEvent()
    {
        std::cout << "AppCloseEvent Destroyed\n";
    }

    static const char* StaticName() { return "AppCloseEvent"; }
};

#endif //ZOMBIEGAME_APPCLOSEEVENT_H
