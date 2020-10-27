#ifndef ZOMBIEGAME_EVENT_H
#define ZOMBIEGAME_EVENT_H

#include <iostream>
#include <memory>

class Event
{
public:
    explicit Event(const char* name)
        :m_Name(name)
    {}

    const char* Name() const { return m_Name; }

private:
    const char* m_Name;
};

typedef Event* EventPointer;

#endif //ZOMBIEGAME_EVENT_H
