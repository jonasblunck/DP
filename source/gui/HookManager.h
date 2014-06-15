#ifndef __HOOKMANAGER_H__
#define __HOOKMANAGER_H__

#pragma once 

#include <map>
#include "HookedStructures.h"

using namespace std;

class HookedProcess;

class CHookManager
{
public:
	static CHookManager& Instance();

	BOOL AddHookedProcess(DWORD dwPID, LPCTSTR pszPath);
	BOOL ExistsHookedProcess(DWORD dwPID);
	SmartRefPtr<HookedProcess> GetHookedProcess(DWORD dwPID);
	BOOL RemoveHookedProcess(DWORD dwPID);
	BOOL RemoveAllHookedProcesses();

	DWORD GetHookedProcessCount();
	SmartRefPtr<HookedProcess> GetHookedProcessByIndex(DWORD dw);
	
	BOOL RemoveAllDeadProcesses();

private:
	CHookManager() {}	// Disallow normal construction

	typedef map< DWORD, SmartRefPtr< HookedProcess > > HookedProcessMap;
	HookedProcessMap m_mapHookedProcesses;
	
	SmartCriticalSection m_cs;
};

#endif // __HOOKMANAGER_H__
