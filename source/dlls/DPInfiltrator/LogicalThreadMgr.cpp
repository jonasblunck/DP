#include "stdafx.h"
#include "logicalthreadmgr.h"

LogicalThreadMgr::LogicalThreadMgr(void)
{
  m_dwTlsSlot = TlsAlloc();
}

LogicalThreadMgr::~LogicalThreadMgr(void)
{
  TlsFree(m_dwTlsSlot);
}

bool LogicalThreadMgr::IsThreadInCall()
{
  int iInCall = (int)TlsGetValue(m_dwTlsSlot);

  return iInCall == 1 ? true : false;
}

void LogicalThreadMgr::RegisterThreadCall()
{
  _ASSERTE(!IsThreadInCall());

  TlsSetValue(m_dwTlsSlot, (LPVOID)1);
}

void LogicalThreadMgr::UnregisterThreadCall()
{
  _ASSERTE(IsThreadInCall());

  TlsSetValue(m_dwTlsSlot, (LPVOID)0);
}
