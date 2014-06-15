#ifndef __HOOKEDSTRUCTURES_H__
#define __HOOKEDSTRUCTURES_H__

#pragma once 

#include "RunningProcesses.h"

using namespace std;

class HookedFunction : public SmartRCBase
{
public:
	HookedFunction(long lHookID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction);
	~HookedFunction()
	{
		ATLTRACE(_T("[%lu] HookedFunction::destructor() this=0x%X\n"), GetCurrentThreadId(), this);
	}
	
	LPCTSTR GetModuleName();
	LPCTSTR GetModulePath();
	LPCTSTR GetFunctionName();
	long	GetHookID();
	DWORD	GetRVA();

private:
	TCHAR	m_szModulePath[MAX_PATH];
	TCHAR	m_szFunctionName[MAX_PATH];
	long	m_lHookID;
	DWORD	m_dwRVA;

	HookedFunction(const HookedFunction& rhs);
	HookedFunction& operator=(const HookedFunction& rhs);
};

class HookedProcess : 
	public SmartRCBase,
	public IEnumerateExportsCallback,
	public IEnumerateModulesCallback
{
public:
	HookedProcess(DWORD dwPID, LPCTSTR pszExePath);
	~HookedProcess();

	SmartRefPtr<HookedFunction> IsFunctionHooked(LPCTSTR pszModule, DWORD dwRVA);

	HRESULT HookFunction(LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunctionName, LPCTSTR pszParameters);
	HRESULT UnhookFunction(long lID);
	HRESULT UnhookAll();

	HRESULT SuspendTrace();
	HRESULT ResumeTrace();
	HRESULT ToggleTrace(BOOL* pbNewValue);
	
	BOOL IsProcessAlive();
	
	LPCTSTR GetProcessName();
	LPCTSTR GetProcessPath();
	DWORD GetPID();

	typedef map< long, SmartRefPtr< HookedFunction > > map_type;
	map_type HookedFunctions;

// IEnumerateModulesCallback
	BOOL OnModule(DWORD dwPID, LPCTSTR pszModulePath, void* pvContext);

// IEnumerateExportsCallback
	BOOL OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
    LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParameters);

private:
	TCHAR m_szPath[MAX_PATH];
	DWORD m_dwPID;

	DWORD m_dwInfiltratorCookie;
	DWORD m_dwHostCookie;
	
	bool m_bPaused;

	HookedProcess(const HookedProcess& rhs);
	HookedProcess& operator=(const HookedProcess& rhs);
};


#endif // __HOOKEDSTRUCTURES_H__
