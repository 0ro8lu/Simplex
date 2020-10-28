#include "ProcessManager.h"

ProcessManager::ProcessManager()
{

}


ProcessManager::~ProcessManager()
{
    ClearAllProcesses();
}

unsigned int ProcessManager::UpdateProcesses()
{

    unsigned int successCount = 0;
    unsigned int failCount = 0;

    auto it = m_ProcessList.begin();
    while (it != m_ProcessList.end())
    {
        StrongProcessPtr pCurrentProcess = (*it);
        auto thisIt = it;
        ++it;

        if (pCurrentProcess->GetState() == UNINITIALIZED)
            pCurrentProcess->VOnInit();

        if (pCurrentProcess->GetState() == RUNNING)
            pCurrentProcess->VOnUpdate();

        if (pCurrentProcess->IsDead())
        {
            switch (pCurrentProcess->GetState())
            {
                case SUCCEEDED:
                {
                    pCurrentProcess->VOnSuccess();
                    StrongProcessPtr pChild = pCurrentProcess->RemoveChild();
                    if (pChild)
                    {
                        AttachProcess(pChild);
                    } else
                    {
                        ++successCount;
                    }
                    break;
                }
                case FAILED:
                {
                    pCurrentProcess->VOnFail();
                    ++failCount;
                    break;
                }
                case ABORTED:
                {
                    pCurrentProcess->VOnAbort();
                    ++failCount;
                    break;
                }
            }
            m_ProcessList.erase(thisIt);
        }
    }
    return ((successCount << 16 ) | failCount);
}

WeakProcessPtr ProcessManager::AttachProcess(const StrongProcessPtr &pProcess)
{
    m_ProcessList.push_front(pProcess);
    return WeakProcessPtr(pProcess);
}

void ProcessManager::AbortAllProcesses(bool immediate)
{
    auto it = m_ProcessList.begin();
    while(it != m_ProcessList.end())
    {
        auto tempIt = it;
        ++it;

        StrongProcessPtr pProcess = *tempIt;
        if(pProcess->IsAlive())
        {
            pProcess->SetState(ABORTED);
            if(immediate)
            {
                pProcess->VOnAbort();
                m_ProcessList.erase(tempIt);
            }
        }
    }
}

void ProcessManager::ClearAllProcesses()
{
    m_ProcessList.clear();
}

