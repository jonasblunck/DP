
#include "stdafx.h"
#include "ChainHookAPI.h"
#include "CChainHook.h"
#include "Injector.h"
#include <crtdbg.h>

LPVOID CHAllocStub(HANDLE hProcess)
{
  _ASSERTE(hProcess);

  CChainHook Hook;

  return Hook.AllocStub(hProcess);
}

bool CHInjectCode(HANDLE hProcess, LPVOID pFunction, BYTE* pbCode, int nCodeBytes)
{
  _ASSERTE(hProcess);
  _ASSERTE(pFunction);

  CChainHook Hook;
  
  return Hook.InjectCode(hProcess, pFunction, pbCode, nCodeBytes);
}

bool CHHookProcEx(HANDLE hProcess, LPVOID pFunctionToIntercept, LPVOID pHook, LPVOID pStub)
{
  _ASSERTE(hProcess);
  _ASSERTE(pFunctionToIntercept);
  _ASSERTE(pHook);
  _ASSERTE(pStub);

  CChainHook Hook;

  return Hook.HookProcEx(hProcess, pFunctionToIntercept, pHook, pStub);
}

LPVOID CHHookProc(HANDLE hProcess, LPVOID pFunctionToIntercept, LPVOID pHook)
{
  _ASSERTE(hProcess);
  _ASSERTE(pFunctionToIntercept);
  _ASSERTE(pHook);

  CChainHook Hook;

  return Hook.HookProc(hProcess, pFunctionToIntercept, pHook);
}

bool CHRemoveHook(HANDLE hProcess, LPVOID pInterceptedFunction, LPVOID pStub)
{
  _ASSERTE(hProcess);
  _ASSERTE(pInterceptedFunction);
  _ASSERTE(pStub);

  CChainHook Hook;

  return Hook.RemoveHook(hProcess, pInterceptedFunction, pStub);
}

bool CHInjectDLL(DWORD dwPID, LPCTSTR pszDLL)
{
  _ASSERTE(pszDLL);

  return Injector::InjectDllInProcess(dwPID, pszDLL);
}

bool CHFindStdCallParamStackSize(LPVOID pFunctionInMemory, int& riStackSize)
{ 
  _ASSERTE(pFunctionInMemory);

  return false;
}








