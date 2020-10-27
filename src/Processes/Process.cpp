#include "Process.h"

Process::Process()
{
    m_State = UNINITIALIZED;
}

Process::~Process()
{
    if (m_pChild)
    {
        m_pChild->VOnAbort();
    }
}

void Process::Pause()
{
    if (m_State == RUNNING)
        m_State = PAUSED;
    else
        std::cout << "ERROR: Trying to pause process that is not running!\n";
}

void Process::UnPause()
{
    if (m_State == PAUSED)
        m_State = RUNNING;
    else
        std::cout << "ERROR: Trying to unpause a process that is not paused!\n";
}

void Process::AttachChild(const StrongProcessPtr& childProcess)
{
    if (m_pChild)
        m_pChild->AttachChild(childProcess);
    else
        m_pChild = childProcess;
}

StrongProcessPtr Process::RemoveChild()
{
    if(m_pChild)
    {
        StrongProcessPtr pChild = m_pChild;
        m_pChild.reset();
        return pChild;
    }

    return StrongProcessPtr();
}