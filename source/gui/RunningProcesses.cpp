#include "stdafx.h"
#include "RunningProcesses.h"
#include "FunctionFile.h"
#include "MainFrm.h"

BOOL CRunningProcesses::EnumerateRunningProcesses(IEnumerateRunningProcessesCallback* pCallback, void* pvContext, BOOL bEnableDebugPriv)
{
  // Enumerate all processes, and save process ID in the array
  DWORD rgdwProcessIDs[1024];
  DWORD cbNeeded = 0;
  if(!::EnumProcesses(rgdwProcessIDs, sizeof(rgdwProcessIDs), &cbNeeded))
  {
    return FALSE;
  }

  int nProcesses = cbNeeded / sizeof(DWORD);
  for (int i = 1; i < nProcesses; ++i)	// We'll never be able to open System Idle Process (index 0)
  {
    TCHAR szExePath[MAX_PATH];
    if(GetPathFromPID(rgdwProcessIDs[i], szExePath, lengthof(szExePath), bEnableDebugPriv))
    {
      pCallback->OnProcess(rgdwProcessIDs[i], szExePath, pvContext);
    }
  }

  return TRUE;
}

BOOL CRunningProcesses::EnumerateModules(DWORD dwPID, IEnumerateModulesCallback* pCallback, void* pvContext, BOOL bEnableDebugPriv)
{
  SmartProcessPrivilege priv;
  if(bEnableDebugPriv)
  {
    priv.Enable(SE_DEBUG_NAME);
  }

  SmartHandle process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
  if(process != NULL)
  {
    HMODULE rghModules[1024];
    DWORD cbNeeded;
    if(EnumProcessModules(process, rghModules, sizeof(rghModules), &cbNeeded))
    {
      int nModules = cbNeeded / sizeof(DWORD);
      for(int n = 1; n < nModules; n++)	// Skip the first
      {
        TCHAR szModulePath[MAX_PATH];
        MODULEINFO modInfo = {0};
        ::GetModuleInformation(process, rghModules[n], &modInfo, sizeof(MODULEINFO));

        if(GetModuleFileNameEx(process, rghModules[n], szModulePath, lengthof(szModulePath)))
        {
          if(!pCallback->OnModule(dwPID, szModulePath, pvContext))
          {
            break;
          }
        }
      }
    }
  }

  return TRUE;
}

BOOL CRunningProcesses::EnumerateExports(LPCTSTR pszModulePath, IEnumerateExportsCallback* pCallback, void* pvContext, BOOL bUndecorateSymbols)
{
  //
  // get the signatures for the exported functions..
  CString2CStringMap functions;
  FunctionFile::ReadFunctions(CMainFrame::GetDefinitionsFilepath(pszModulePath), functions);

  // Map view of file, and gather PE information
  SmartFileMapping fileMapping(pszModulePath);
  PBYTE pImageBase = fileMapping;
  if(pImageBase == NULL)
  {
    return FALSE;
  }

  PIMAGE_NT_HEADERS pNTHeader = ImageNtHeader(pImageBase);

  DWORD exportsStartRVA = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
  DWORD exportsEndRVA	= exportsStartRVA + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

  // Get the IMAGE_SECTION_HEADER that contains the exports
  PIMAGE_SECTION_HEADER header = ImageRvaToSection(pNTHeader, pImageBase, exportsStartRVA);
  if(header == 0)
  {
    return FALSE;
  }

  PIMAGE_EXPORT_DIRECTORY pExportDir = (PIMAGE_EXPORT_DIRECTORY)ImageRvaToVa(pNTHeader, pImageBase, exportsStartRVA, NULL);

  PDWORD	pdwFunctions =	(PDWORD)ImageRvaToVa(pNTHeader, pImageBase, pExportDir->AddressOfFunctions, NULL);
  PWORD	pwOrdinals	=	(PWORD)	ImageRvaToVa(pNTHeader, pImageBase, pExportDir->AddressOfNameOrdinals, NULL);
  PDWORD	pszFuncNames =	(PDWORD)ImageRvaToVa(pNTHeader, pImageBase, pExportDir->AddressOfNames, NULL);

  for(DWORD i = 0; i < pExportDir->NumberOfFunctions; i++)
  {
    DWORD dwProcRVA = pdwFunctions[i];
    if(dwProcRVA == 0)
    {
      continue;
    }

    TCHAR szProcName[256] = _T("<no name>");

    // See if this function has an associated name exported for it.
    for(unsigned j = 0; j < pExportDir->NumberOfNames; j++)
    {
      if(pwOrdinals[j] == i)
      {
#ifdef _UNICODE
        CHAR szProc[256] = {0};
        lstrcpynA(szProc, (LPCSTR)ImageRvaToVa(pNTHeader, pImageBase, pszFuncNames[j], NULL), lengthof(szProc) - 1);
        if(bUndecorateSymbols)
        {
          // Undecorate in temporary ANSI buffer
          UnDecorateSymbolName(szProc, szProc, lengthof(szProc), UNDNAME_COMPLETE);

          // And convert back to UNICODE
          MultiByteToWideChar(CP_ACP, 0, szProc, -1, szProcName, lengthof(szProcName));
        }
#else
        _tcsncpy(szProcName, (LPCTSTR)ImageRvaToVa(pNTHeader, pImageBase, pszFuncNames[j], NULL), lengthof(szProcName) - 1);
        if(bUndecorateSymbols)
        {
          // Undecorate in place
          UnDecorateSymbolName(szProcName, szProcName, lengthof(szProcName), UNDNAME_COMPLETE);
        }
#endif
        break;
      }
    }

    CString strParamDefinition;
    CString2CStringMap::const_iterator t =
      functions.find(CString(szProcName));

    if (functions.end() != t)
      strParamDefinition = t->second;

    // Call back name or no name
    pCallback->OnExport(pszModulePath, i, dwProcRVA, szProcName, pvContext, (LPCTSTR)strParamDefinition);
  }

  return TRUE;
}

BOOL CRunningProcesses::GetPathFromPID(DWORD dwPID, LPTSTR pszBuffer, DWORD cchBuffer, BOOL bEnableDebugPriv)
{
  SmartProcessPrivilege priv;
  if(bEnableDebugPriv)
  {
    priv.Enable(SE_DEBUG_NAME);
  }

  SmartHandle process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
  if(process == NULL)
  {
    return FALSE;
  }

  // Somewhat undocumented: Passing NULL for the HMODULE gives us the EXE name
  if(!GetModuleFileNameEx(process, NULL, pszBuffer, cchBuffer))
  {
    return FALSE;
  }

  return TRUE;
}

BOOL CRunningProcesses::GetNameFromPID(DWORD dwPID, LPTSTR pszBuffer, DWORD cchBuffer, BOOL bEnableDebugPriv)
{
  SmartProcessPrivilege priv;
  if(bEnableDebugPriv)
  {
    priv.Enable(SE_DEBUG_NAME);
  }

  SmartHandle process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPID);
  if(process == NULL)
  {
    return FALSE;
  }

  // Somewhat undocumented: Passing NULL for the HMODULE gives us the EXE name
  if(!GetModuleBaseName(process, NULL, pszBuffer, cchBuffer))
  {
    return FALSE;
  }

  return TRUE;
}
