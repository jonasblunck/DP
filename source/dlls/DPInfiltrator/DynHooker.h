// Hook.h: interface for the CDynHooker class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <list>

#include "LogicalThreadMgr.h"
#include "HookedFunctionListener.h"
#include "ISC.h"

class HookContext;
enum ParameterType;

class CDynHooker  
{
  LogicalThreadMgr  m_Causality;
  bool              m_bPaused;
  static DWORD CalcAddressOffset(DWORD dwDestinationAddress, DWORD dwHookCodeStartAddress, DWORD dwInstructionOffsetInHook, DWORD dwTotalInstSize);

public:
	CDynHooker();      
	virtual ~CDynHooker();  

  static bool GetHookContext(LPVOID pInterceptedFunction, HookContext*& context);

  HookContext* InstallDynamicHook(LPVOID pFunctionToIntercept, LPCTSTR pszName, ISC::InterfaceMethod*, HookedFunctionListener* listener, bool isStdCall = false);
  bool HookInterface(IUnknown* pInterface, REFIID riid, HookedFunctionListener* listener);

  void SetPause(bool bPause);
  bool SetActive(LPVOID pInterceptedFunction, bool active);
};

