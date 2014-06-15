#ifndef __RUNNINGPROCESSES_H__
#define __RUNNINGPROCESSES_H__

#pragma once 

/// Callback interfaces for clients to implement
class IEnumerateRunningProcessesCallback
{
public:
	virtual BOOL OnProcess(DWORD dwPID, LPCTSTR pszPath, void* pvContext) = 0;
};

class IEnumerateModulesCallback
{
public:
	virtual BOOL OnModule(DWORD dwPID, LPCTSTR pszModulePath, void* pvContext) = 0;
};

class IEnumerateExportsCallback
{
public:
	virtual BOOL OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
    LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParameters) = 0;
};

/// Enumerates running processes, modules and functions
/// and provides helpers for querying running processes
class CRunningProcesses
{
public:
	BOOL EnumerateRunningProcesses(IEnumerateRunningProcessesCallback* pCallback, void* pvContext, BOOL bEnableDebugPriv);
	BOOL EnumerateModules(DWORD dwPID, IEnumerateModulesCallback* pCallback, void* pvContext, BOOL bEnableDebugPriv);
	BOOL EnumerateExports(LPCTSTR pszModulePath, IEnumerateExportsCallback* pCallback, void* pvContext, BOOL bUndecorateSymbols);

	BOOL GetPathFromPID(DWORD dwPID, LPTSTR pszBuffer, DWORD cchBuffer, BOOL bEnableDebugPriv);
	BOOL GetNameFromPID(DWORD dwPID, LPTSTR pszBuffer, DWORD cchBuffer, BOOL bEnableDebugPriv);
};

#endif // __RUNNINGPROCESSES_H__
