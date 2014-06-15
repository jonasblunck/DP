
#include "stdafx.h"
#include "Injector.h"


bool Injector::EnablePrivilege(HANDLE hToken, LPCTSTR pszPrivName, bool bEnable) 
{
  TOKEN_PRIVILEGES tp;

  tp.PrivilegeCount = 1;

  LookupPrivilegeValue(NULL, pszPrivName, &tp.Privileges[0].Luid);

  tp.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

  AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

  return ((GetLastError() == ERROR_SUCCESS));
}
 
bool Injector::EnableDebugPrivilegeForProcess(bool bEnable) 
{
  HANDLE hToken;
  bool bOk = false;
 
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken)) 
  {
    bOk = EnablePrivilege(hToken, SE_DEBUG_NAME, bEnable);
    CloseHandle(hToken);
  }
    
  return bOk;
}

bool Injector::InjectDllInProcess(const DWORD& rdwPID, LPCTSTR pszDLL)
{
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, rdwPID);

  if (!hProcess)
  {
    EnableDebugPrivilegeForProcess(true);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, rdwPID);
  }

  if (!hProcess)
    return false;

  PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");

  if (!pfnThreadRtn)
    return false;

  DWORD dwMemSize = lstrlen(pszDLL) + 1;
  LPVOID pMem = VirtualAllocEx(hProcess, NULL, dwMemSize, MEM_COMMIT, PAGE_READWRITE);
  
  if (pMem)
  {
    if (WriteProcessMemory(hProcess, pMem, (LPVOID)pszDLL, dwMemSize, NULL))
    {
      HANDLE hThread = 
        CreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, (LPVOID)pMem, 0, NULL);

      if (hThread)
      {
        CloseHandle(hThread);

        return true;
      }
    }

    VirtualFreeEx(hProcess, (PVOID)pMem, 0, MEM_RELEASE);
  }

  return false;
}
