#ifndef ZOMBIEGAME_PRINTPROCESS_H
#define ZOMBIEGAME_PRINTPROCESS_H

#include "Processes/Process.h"

class PrintProcess : public Process
{
public:
    explicit PrintProcess(std::string pString)
            : m_pString(std::move(pString))
    {}

protected:
    void VOnUpdate() override { Succeed(); }

    void VOnSuccess() override
    {
        Process::VOnSuccess();
        std::cout << m_pString << "\n";
    }

private:
    std::string m_pString;
};

#endif //ZOMBIEGAME_PRINTPROCESS_H
