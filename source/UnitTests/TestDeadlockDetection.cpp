
#include "stdafx.h"
#include "CSAuto.h"

class IDeadlockListener
{
public:
  virtual void OnPotentialDeadlock() = 0;
};

class QuiteDeadlockListener : public IDeadlockListener
{
  bool m_deadlocked;
public:
  QuiteDeadlockListener() : m_deadlocked(false) 
  {
  }

  virtual void OnPotentialDeadlock() 
  {
    m_deadlocked = true;
  }

  bool IsDeadlocked() const
  {
    return m_deadlocked;
  }

  void Clear()
  {
    m_deadlocked = false;
  }
};

class TestDeadlockDetection
{
  QuiteDeadlockListener m_listener;
  CRITICAL_SECTION m_cs1;
  CRITICAL_SECTION m_cs2;
  CRITICAL_SECTION m_cs3;

public:
  TestDeadlockDetection()
  {
    InitializeCriticalSection(&m_cs1);
    InitializeCriticalSection(&m_cs2);
    InitializeCriticalSection(&m_cs3);

    SetDeadlockDetectionListener(&m_listener);
  }

  ~TestDeadlockDetection()
  {
    SetDeadlockDetectionListener(NULL);

    DeleteCriticalSection(&m_cs1);
    DeleteCriticalSection(&m_cs2);
    DeleteCriticalSection(&m_cs3);
  }
  
  void testDeadlock()
  {
    { // first set of taking locks.. could not deadlock!
      m_listener.Clear();

      _CSAuto lockA(&m_cs1);
      _CSAuto lockB(&m_cs2);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }

    { //same pattern again should not deadlock!
      m_listener.Clear();

      _CSAuto lockA(&m_cs1);
      _CSAuto lockB(&m_cs2);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }

    {// now take locks in wrong order - should deadlock
      m_listener.Clear();

      _CSAuto lockA(&m_cs2);
      _CSAuto lockB(&m_cs1); // taking locks in 'wrong' order should deadlock

      DPUNIT_ISTRUE(m_listener.IsDeadlocked());
    }

    {// just take one look should not deadlock
      m_listener.Clear();

      _CSAuto lockA(&m_cs2);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }

    {// just take one look should not deadlock
      m_listener.Clear();

      _CSAuto lockA(&m_cs1);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }


    {// re-entrency should not be an issue on Windows
      m_listener.Clear();

      _CSAuto lockA(&m_cs1);
      _CSAuto lockB(&m_cs1);
      _CSAuto lockC(&m_cs2);
      _CSAuto lockD(&m_cs2);
      _CSAuto lockE(&m_cs2);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }

    {
      m_listener.Clear();

      _CSAuto lockC(&m_cs3);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());

      _CSAuto lockA(&m_cs1);

      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());
    }


    {
      m_listener.Clear();

      _CSAuto lockC(&m_cs3);
      _CSAuto lockA(&m_cs1);
      _CSAuto lockB(&m_cs2);
  
      DPUNIT_ISTRUE(!m_listener.IsDeadlocked());

      _CSAuto lockB2(&m_cs2);
      _CSAuto lockC2(&m_cs3);

      DPUNIT_ISTRUE(m_listener.IsDeadlocked());
    }

  }

  void Test()
  {
    testDeadlock();
  }
};

void testDeadlockDetection()
{
  TestDeadlockDetection suite;
  suite.Test();
}