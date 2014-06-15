/*
  Copyright Jonas Blunck, 2002-2006

  All rights reserved, no warranties extended. Use at your own risk!

*/

#ifndef _INJECTOR_H_
#define _INJECTOR_H_

class Injector
{
  static bool EnableDebugPrivilegeForProcess(bool bEnable);
  static bool EnablePrivilege(HANDLE hToken, LPCTSTR pszPrivName, bool bEnable); 

public:
  static bool InjectDllInProcess(const DWORD& rdwPID, LPCTSTR pszDLL);

};

#endif
