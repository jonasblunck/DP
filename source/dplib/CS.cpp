#pragma warning(disable: 4244)

#include <windows.h>
#include <list>
#include <map>
#include <algorithm>
#include "hash.h"
#include "TLS.h"

class IDeadlockListener
{
public:
  virtual void OnPotentialDeadlock() = 0;
};

class DebugBreakOnDeadlock : public IDeadlockListener
{
public:
  virtual void OnPotentialDeadlock()
  {
    DebugBreak();
  }
};

class DeadlockPattern
{
  typedef std::list<int> MutexList;
  typedef std::map<unsigned __int64, unsigned __int64> PatternHashMap;
  TLS<MutexList*> m_threadMutexes;
  PatternHashMap m_patterns;
  IDeadlockListener* m_deadlockNotifier;
  DebugBreakOnDeadlock m_breakOnDeadlock;

  MutexList& getCurrentMutexList()
  {
    MutexList* p = m_threadMutexes.get();

    if (!p)
    {
      p = new MutexList();
      m_threadMutexes.set(p);
    }

    return *p;
  }

public:

  DeadlockPattern()
  {
    m_deadlockNotifier = &m_breakOnDeadlock;
  }

  static DeadlockPattern& Instance()
  {
    static DeadlockPattern* instance = NULL;

    if (!instance)
    {
      instance = new DeadlockPattern();
    }

    return *instance;
  }

  void SetOrRevokeListener(IDeadlockListener* listener)
  {
    if (!listener)
    {
      m_deadlockNotifier = &m_breakOnDeadlock;
    }
    else
    {
      m_deadlockNotifier = listener;
    }
  }

  static unsigned __int64 CalculatePatternId(int criticalEnter, int criticalReference)
  {
    int highest = criticalEnter >= criticalReference ? criticalEnter : criticalReference;
    int lowest = criticalEnter <= criticalReference ? criticalEnter : criticalReference;

    return Hash(highest, lowest);
  }

  void EnterCritical(int critical)
  {
    MutexList& mutexes = getCurrentMutexList();

    // check combination of orders
    for (MutexList::const_iterator j = mutexes.begin(); j != mutexes.end(); ++j)
    {
      unsigned __int64 patternId = CalculatePatternId((*j), critical);
      unsigned __int64 hash = Hash((*j), critical);

      PatternHashMap::const_iterator i = 
        m_patterns.find(patternId);

      if (m_patterns.end() != i)
      {
        if ((*i).second != hash)
        {
          m_deadlockNotifier->OnPotentialDeadlock();
        }
      }
      else
      {
        m_patterns.insert(std::make_pair(patternId, hash));
      }
    }

    mutexes.push_back(critical);
  }

  void LeaveCritical(int critical)
  {
    getCurrentMutexList().remove(critical);  // memory leak as this will create a new list?
  }

};

void SetDeadlockDetectionListener(IDeadlockListener* listener)
{
  DeadlockPattern::Instance().SetOrRevokeListener(listener);
}

void CheckedEnterCriticalSection(CRITICAL_SECTION* cs)
{
#ifdef _DEBUG
  DeadlockPattern::Instance().EnterCritical(reinterpret_cast<int>(cs));
#endif
  ::EnterCriticalSection(cs);
}

void CheckedLeaveCriticalSection(CRITICAL_SECTION* cs)
{
#ifdef _DEBUG
  DeadlockPattern::Instance().LeaveCritical(reinterpret_cast<int>(cs));
#endif
  ::LeaveCriticalSection(cs);
}

#pragma warning(default: 4244)

