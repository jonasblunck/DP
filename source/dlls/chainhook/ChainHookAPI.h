/*
  Copyright Jonas Blunck, 2002-2006

  All rights reserved, no warranties extended. Use at your own risk!

*/

#ifndef _CHAIN_HOOK_API_H_
#define _CHAIN_HOOK_API_H_

#ifndef _CHAIN_HOOK_BUILD_
  #ifdef _DEBUG
    #pragma comment(lib, "ChainHookD.lib")
  #else
    #pragma comment(lib, "ChainHook.lib")
  #endif
#endif

extern "C"
{
bool   CHFindStdCallParamStackSize(LPVOID pFunctionInMemory, int& riStackSize);
LPVOID CHAllocStub(HANDLE hProcess);
bool   CHHookProcEx(HANDLE hProcess, LPVOID pFunctionToIntercept, LPVOID pHook, LPVOID pStub);

LPVOID CHHookProc(HANDLE hProcess, LPVOID pFunctionToIntercept, LPVOID pHook); 
bool   CHInjectCode(HANDLE hProcess, LPVOID pFunction, BYTE* pbCode, int nCodeBytes);
bool   CHRemoveHook(HANDLE hProcess, LPVOID pInterceptedFunction, LPVOID pStub);
bool   CHInjectDLL(DWORD dwPID, LPCTSTR pszDLL);

}

#define DECLARE_COAPI_HOOK(func, params) \
  typedef HRESULT(__stdcall* proc_##func)params; \
  proc_##func func##_Chain;  

#define DECLARE_COAPI_HOOK2(type, func, params) \
  typedef type(__stdcall* proc_##func)params; \
  proc_##func func##_Chain;  

#define DECLARE_HOOK(return_type, calling_convention, func, params) \
  typedef return_type (calling_convention##* proc_##func)params; \
  proc_##func func##_Chain;

#define SETUP_HOOK(func) \
func##_Chain = (proc_##func)CHHookProc(GetCurrentProcess(), &func, func##_Hook);

#define REMOVE_HOOK(func) \
  CHRemoveHook(GetCurrentProcess(), &func, func##_Chain);


#endif

