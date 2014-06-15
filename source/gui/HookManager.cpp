#include "stdafx.h"

#include "HookedStructures.h"

#include "HookManager.h"

CHookManager& CHookManager::Instance()
{
	static CHookManager instance;
	return instance;
}

BOOL CHookManager::AddHookedProcess(DWORD dwPID, LPCTSTR pszPath)
{
	HookedProcess* pProcess = new HookedProcess(dwPID, pszPath);
	if(pProcess == NULL)
	{
		return FALSE;
	}

	SmartScopeLock scopeLock(&m_cs);

	m_mapHookedProcesses[dwPID] = pProcess;

	return TRUE;
}

BOOL CHookManager::ExistsHookedProcess(DWORD dwPID)
{
	SmartScopeLock scopeLock(&m_cs);

	return (m_mapHookedProcesses.find(dwPID) != m_mapHookedProcesses.end());
}

BOOL CHookManager::RemoveHookedProcess(DWORD dwPID)
{
	SmartScopeLock scopeLock(&m_cs);

	return m_mapHookedProcesses.erase(dwPID);
}

BOOL CHookManager::RemoveAllHookedProcesses()
{
	SmartScopeLock scopeLock(&m_cs);
	m_mapHookedProcesses.clear();
	return TRUE;
}

SmartRefPtr<HookedProcess> CHookManager::GetHookedProcess(DWORD dwPID)
{
	SmartScopeLock scopeLock(&m_cs);
	HookedProcessMap::iterator i = m_mapHookedProcesses.find(dwPID);
	if(i == m_mapHookedProcesses.end())
	{
		return NULL;
	}

	return (*i).second;
}

DWORD CHookManager::GetHookedProcessCount()
{
	SmartScopeLock scopeLock(&m_cs);
	return m_mapHookedProcesses.size();
}

SmartRefPtr<HookedProcess> CHookManager::GetHookedProcessByIndex(DWORD dw)
{
	SmartScopeLock scopeLock(&m_cs);
	if(dw >= m_mapHookedProcesses.size())
	{
		return NULL;
	}

	HookedProcessMap::iterator i = m_mapHookedProcesses.begin();
	advance(i, dw);

	return (*i).second;
}


BOOL CHookManager::RemoveAllDeadProcesses()
{
	SmartScopeLock scopeLock(&m_cs);

	// Collect all processes to be deleted
	vector< DWORD > vecToBeDeleted;
	for(HookedProcessMap::iterator i = m_mapHookedProcesses.begin(); i != m_mapHookedProcesses.end(); ++i)
	{
		SmartRefPtr<HookedProcess> pProcess = (*i).second;
		if(pProcess == NULL)
		{
			vecToBeDeleted.push_back((*i).first);
		}
		else if(!pProcess->IsProcessAlive())
		{
			vecToBeDeleted.push_back((*i).first);
		}
	}

	// And lose them
	for(vector< DWORD >::iterator it = vecToBeDeleted.begin(); it != vecToBeDeleted.end(); ++it)
	{
		RemoveHookedProcess(*it);
	}

	return TRUE;
}