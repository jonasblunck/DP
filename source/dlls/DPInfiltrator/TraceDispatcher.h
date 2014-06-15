#pragma once

#include "HookedFunctionListener.h"

class CTraceDispatcher : public HookedFunctionListener
{
  HANDLE m_hIOCP;
  DWORD m_dwTID;
  SOCKET m_recipient;

  static DWORD __stdcall TraceThread(LPVOID p);
  DWORD WorkerProc();
  void SendSlotMessage(BYTE* data, int length);

public:
  CTraceDispatcher(void);
  ~CTraceDispatcher(void);

  void Init();
  void Terminate();
  DWORD GetDispatcherThreadID();

  virtual void OnHookedFunction(long id, const CString& strArguments, int returnValue);

//  static void AddTrace(DWORD dwID, LPSTR argTrace);
};
