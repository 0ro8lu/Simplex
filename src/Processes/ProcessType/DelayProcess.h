#ifndef ZOMBIEGAME_DELAYPROCESS_H
#define ZOMBIEGAME_DELAYPROCESS_H

#include "Processes/Process.h"

class DelayProcess : public Process
{
public:
    explicit DelayProcess(unsigned long timeToDelay)
            : m_timeToDelay(timeToDelay), m_timeDelayedSoFar(0)
    {}

protected:

    void VOnUpdate() override
    {
        m_timeDelayedSoFar += 16;
        if(m_timeDelayedSoFar >= m_timeToDelay)
            Succeed();
    }

    void VOnSuccess() override
    {
        Process::VOnSuccess();
    }

private:
    unsigned long m_timeToDelay;
    unsigned long m_timeDelayedSoFar;
};

#endif //ZOMBIEGAME_DELAYPROCESS_H
