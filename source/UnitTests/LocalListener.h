
#pragma once
#include "HookedFunctionListener.h"

class LocalListener : public HookedFunctionListener
{
  long m_id;
  CString m_trace;
  int m_returnValue;
public:
  LocalListener()
  {
    m_id = -1;
  }

  virtual void OnHookedFunction(long id, const CString& strArguments, int returnValue)
  {
    m_id = id;
    m_trace = strArguments;
    m_returnValue = returnValue;
  }

  int GetReturnValue() const { return m_returnValue; }
  long GetId() const { return m_id; }
  const CString& GetTrace() const { return m_trace; }
  bool WasInvoked() const { return (m_id != -1); }
  void Reset() 
  {
    m_id = -1;
    m_trace.Empty();
    m_returnValue = 0xffffffff;
  }

};