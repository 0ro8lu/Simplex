#ifndef ZOMBIEGAME_TIMER_H
#define ZOMBIEGAME_TIMER_H

#include <chrono>

class Timer
{
public:
    static double getCurrentTime()
    {
        using namespace std::chrono;
        milliseconds ms = duration_cast< milliseconds >(steady_clock::now().time_since_epoch());
        return ms.count();
    }
};

#endif //ZOMBIEGAME_TIMER_H
