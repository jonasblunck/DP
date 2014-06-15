#pragma once


class LogicalThreadMgr
{
  DWORD m_dwTlsSlot;
public:
  LogicalThreadMgr(void);
  ~LogicalThreadMgr(void);

  bool IsThreadInCall();
  void RegisterThreadCall();
  void UnregisterThreadCall();
};


class LogicalThreadAutoRegister
{
  LogicalThreadMgr& m_rThreadMgr;
public:
  LogicalThreadAutoRegister(LogicalThreadMgr& rMgr) : m_rThreadMgr(rMgr)
  {
    m_rThreadMgr.RegisterThreadCall();
  }

  ~LogicalThreadAutoRegister()
  {
    m_rThreadMgr.UnregisterThreadCall();
  }
};

#define CAUSALITY(x) LogicalThreadAutoRegister __Causal(x)
