#ifndef ZOMBIEGAME_PROCESS_H
#define ZOMBIEGAME_PROCESS_H

#include <memory>
#include <iostream>

class Process;
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process>   WeakProcessPtr;

enum State
{
    UNINITIALIZED,
    REMOVED,
    RUNNING,
    PAUSED,
    SUCCEEDED,
    FAILED,
    ABORTED
};

class Process
{
    friend class ProcessManager;

public:
    Process();
    virtual ~Process();

    inline void Succeed() { m_State = SUCCEEDED; }
    inline void Fail()   { m_State = FAILED; }
    void        Pause();
    void        UnPause();

    void AttachChild(const StrongProcessPtr& childProcess);
    StrongProcessPtr RemoveChild();
    inline StrongProcessPtr PeekChild() const { return m_pChild; }

    inline State GetState()  const        { return m_State; }
    inline void  SetState(State newState) { m_State = newState; }

    inline bool  IsAlive()   const { return (m_State == RUNNING || m_State == PAUSED); }
    inline bool  IsDead()    const { return (m_State == SUCCEEDED || m_State == ABORTED || m_State == FAILED); }
    inline bool  IsRemoved() const { return (m_State == REMOVED); }
    inline bool  IsPaused()  const { return (m_State == PAUSED); }

protected:

    virtual void VOnInit() { m_State = RUNNING; }
    virtual void VOnUpdate() = 0;
    virtual void VOnSuccess() {};
    virtual void VOnFail()    {};
    virtual void VOnAbort()   {};

private:
    State   m_State;
    StrongProcessPtr m_pChild;
};

#endif //ZOMBIEGAME_PROCESS_H
