#ifndef ZOMBIEGAME_PROCESSMANAGER_H
#define ZOMBIEGAME_PROCESSMANAGER_H

#include <list>
#include "Process.h"

class ProcessManager
{
    typedef std::list<StrongProcessPtr> ProcessList;
    ProcessList m_ProcessList;

public:
    ProcessManager();
    virtual ~ProcessManager();

    unsigned int UpdateProcesses();
    WeakProcessPtr AttachProcess(const StrongProcessPtr& pProcess);
    void AbortAllProcesses(bool immediate);

    unsigned int GetProcessCount() const { return m_ProcessList.size(); }

private:
    void ClearAllProcesses();
};

#endif//ZOMBIEGAME_PROCESSMANAGER_H
