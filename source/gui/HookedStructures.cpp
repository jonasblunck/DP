#include "stdafx.h"
#include "HookedStructures.h"
#include "MainFrm.h"
#include "FunctionFile.h"

#include "pipeClient.h"

////////////////////////////////////////////////////////////////////////
/// HookedFunction implementation
HookedFunction::HookedFunction(long lHookID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction)
{
	m_lHookID = lHookID;
	m_dwRVA = dwRVA;

	ZeroMemory(m_szModulePath, sizeof(m_szModulePath));
	ZeroMemory(m_szFunctionName, sizeof(m_szFunctionName));

	_tcsncpy(m_szModulePath, pszModule, lengthof(m_szModulePath) - 1);
	_tcsncpy(m_szFunctionName, pszFunction, lengthof(m_szFunctionName) - 1);
}

LPCTSTR HookedFunction::GetModuleName()
{
	LPCTSTR pszName = _tcsrchr(m_szModulePath, _T('\\'));
	if(pszName)
	{
		return pszName + 1;
	}
	else
	{
		return m_szModulePath;
	}
}

LPCTSTR HookedFunction::GetModulePath()
{
	return m_szModulePath;
}

LPCTSTR HookedFunction::GetFunctionName()
{
	return m_szFunctionName;
}

long HookedFunction::GetHookID()
{
	return m_lHookID;
}

DWORD HookedFunction::GetRVA()
{
	return m_dwRVA;
}

////////////////////////////////////////////////////////////////////////
/// HookedProcess implementation
HookedProcess::HookedProcess(DWORD dwPID, LPCTSTR pszExePath)
	:	m_dwPID(dwPID),
		m_dwInfiltratorCookie(0),
		m_dwHostCookie(0),
		m_bPaused(false)
{
	ZeroMemory(m_szPath, sizeof(m_szPath));

	_tcsncpy(m_szPath, pszExePath, lengthof(m_szPath) - 1);
	_tcsupr(m_szPath);
}

HookedProcess::~HookedProcess()
{

	ATLTRACE(_T("[%lu] HookedProcess::destructor() this=0x%X\n"), GetCurrentThreadId(), this);
}

LPCTSTR HookedProcess::GetProcessName()
{
	LPCTSTR pszName = _tcsrchr(m_szPath, _T('\\'));
	if(pszName)
	{
		return pszName + 1;
	}
	else
	{
		return m_szPath;
	}
}

LPCTSTR HookedProcess::GetProcessPath()
{
	return m_szPath;
}

DWORD HookedProcess::GetPID()
{
	return m_dwPID;
}


BOOL HookedProcess::IsProcessAlive()
{
	SmartHandle process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_dwPID);
	if(process != NULL)
	{
		// Somewhat undocumented: Passing NULL for the HMODULE gives us the EXE name
		TCHAR szProcessPath[MAX_PATH];
		if(GetModuleFileNameEx(process, NULL, szProcessPath, lengthof(szProcessPath)))
		{
			if(_tcsicmp(szProcessPath, m_szPath) == 0)
			{
				return TRUE;
			}
		}		
	}

	return FALSE;
}

SmartRefPtr<HookedFunction> HookedProcess::IsFunctionHooked(LPCTSTR pszModule, DWORD dwRVA)
{
	for(map_type::iterator i = HookedFunctions.begin(); i != HookedFunctions.end(); ++i)
	{
		SmartRefPtr<HookedFunction> pFunc = (*i).second;
		if(pFunc != NULL)
		{
			if(pFunc->GetRVA() == dwRVA)
			{
				return pFunc;
			}
		}
	}

	return 0;
}



HRESULT HookedProcess::HookFunction(LPCTSTR pszModule, DWORD dwRVA, 
                                    LPCTSTR pszFunctionName, LPCTSTR pszParameters)
{
  PipeClient client;
  long lID = 0;
  const int numRetriesOnConnectFail = 4;

  if (!client.Connect(m_dwPID, numRetriesOnConnectFail))
    return E_FAIL;

  DPMessage message;
  message.action = hookRequest;
  message.len = sizeof(DPMessage);
  message.id = 0;
  message.hookRequest.rva = dwRVA;
  lstrcpyn(message.hookRequest.paramDefinition, pszParameters, sizeof(message.hookRequest.paramDefinition));
  lstrcpyn(message.hookRequest.module, pszModule, sizeof(message.hookRequest.module));

  if (!client.Send((BYTE*)&message, message.len))
    return E_FAIL;

  DPMessage response = {0};
  DWORD read = 0;
  if (client.Read((BYTE*)&response, sizeof(DPMessage), &read))
  {
    if (read == sizeof(DPMessage) && response.action == hookResponse && response.id == message.id)
    {
      lID = response.hookResponse.id;
    }
  }

#ifdef _DEBUG
  if (HookedFunctions.end() != HookedFunctions.find(lID))
    ATLTRACE(_T("[%lu] Id %ld is already occupied!\n"), GetCurrentThreadId(), lID);
#endif

	HookedFunctions[lID] = new HookedFunction(lID, pszModule, dwRVA, pszFunctionName);

	return S_OK;
}

HRESULT HookedProcess::UnhookFunction(long lID)
{
  PipeClient client;

  if (client.Connect(m_dwPID))
  {
    DPMessage message = {0};
    message.len = sizeof(DPMessage);
    message.action = unHookRequest;
    message.id = lID;

    if (client.Send((BYTE*)&message, message.len))
    {
      HookedFunctions.erase(lID);
      return S_OK;
    }
  }

  return E_FAIL;
}

HRESULT HookedProcess::UnhookAll()
{
  PipeClient client;

  if (client.Connect(m_dwPID))
  {
    for(map_type::iterator i = HookedFunctions.begin(); i != HookedFunctions.end(); ++i)
	  {
      long id = (*i).first;

      DPMessage message = {0};
      message.len = sizeof(DPMessage);
      message.action = unHookRequest;
      message.id = id;

      client.Send((BYTE*)&message, message.len);
	  }

	  // Clear hooked map
	  HookedFunctions.clear();
  }

	return S_OK;
}

HRESULT HookedProcess::SuspendTrace()
{
  // TODO: Not IMPLEMENTED
	return S_OK;
}

HRESULT HookedProcess::ResumeTrace()
{
  // TODO: not Implemented
	return S_OK;
}

HRESULT HookedProcess::ToggleTrace(BOOL* pbNewValue)
{
  // TODO: not implemented

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////
/// IEnumerateExportsCallback implementation
BOOL HookedProcess::OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
                             LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParameters)
{
	HRESULT hr = S_OK;

	BOOL bHookState = (BOOL)pvContext;
  SmartRefPtr<HookedFunction> function = IsFunctionHooked(pszModulePath, dwRVA);

	if(bHookState)
	{
		if(NULL == function.GetPointer())
		{
			CString strMessage;
			hr = HookFunction(pszModulePath, dwRVA, pszFunctionName, pszParameters);
			if(FAILED(hr))
			{
				strMessage.Format(_T("Failed to hook (0x%X)"), hr);
			}
			else
			{
				strMessage = _T("Hooked");
			}

			CMainFrame::Instance().TraceMessage(m_dwPID, pszModulePath, dwRVA, pszFunctionName, strMessage);
		}
	}
	else
	{
		if(NULL != function.GetPointer())
		{
			CString strMessage;
			hr = UnhookFunction(function->GetHookID());
			if(FAILED(hr))
			{
				strMessage.Format(_T("Failed to unhook (0x%X)"), hr);
			}
			else
			{
				strMessage = _T("Unhooked");
			}

			CMainFrame::Instance().TraceMessage(m_dwPID, pszModulePath, dwRVA, pszFunctionName, strMessage);
		}
	}

	return (SUCCEEDED(hr));
}

/////////////////////////////////////////////////////////////////////////////////////
/// IEnumerateModulesCallback implementation
BOOL HookedProcess::OnModule(DWORD dwPID, LPCTSTR pszModulePath, void* pvContext)
{
	CRunningProcesses runningProcesses;
	return runningProcesses.EnumerateExports(pszModulePath, this, pvContext, COptionsStorage::Instance().GetUndecorateSymbols());
}
