// DP.cpp : main source file for DP.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>


#include "resource.h"

// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f DPps.mk in the project directory.
#include "initguid.h"
#include "DP.h"
#include "DP_i.c"

#include "ProcessView.h"
#include "ExportView.h"
#include "TraceView.h"

#include "aboutdlg.h"
#include "MainFrm.h"
#include "SingleInstance.h"

CServerAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_TraceListener, CTraceListener)
END_OBJECT_MAP()

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame& wndMain = CMainFrame::Instance();
	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	_Module.Lock();

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

DWORD __stdcall FactoryThreadProc(LPVOID pv)
{
	HRESULT hr;

	HANDLE hShutdownEvent = (HANDLE)pv;

	hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hr));

	hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
	ATLASSERT(SUCCEEDED(hr));

	DWORD dwRet = WaitForSingleObject(hShutdownEvent, INFINITE);
	ATLASSERT(dwRet == WAIT_OBJECT_0);
	
	hr = _Module.RevokeClassObjects();
	ATLASSERT(SUCCEEDED(hr));

	CoUninitialize();

	return 0;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_BAR_CLASSES;	// change to support other controls
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	hRes = _Module.Init(ObjectMap, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = 0;

	TCHAR szTokens[] = _T("-/");
	bool bRun = true;
	bool bAutomation = false;

	LPCTSTR lpszToken = _Module.FindOneOf(::GetCommandLine(), szTokens);
	while(lpszToken != NULL)
	{
		if(lstrcmpi(lpszToken, _T("UnregServer")) == 0)
		{
			_Module.UpdateRegistryFromResource(IDR_DP, FALSE);
			nRet = _Module.UnregisterServer(TRUE);
			bRun = false;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("RegServer")) == 0)
		{
			// Already registered...
			bRun = false;
			break;
		}
		else if((lstrcmpi(lpszToken, _T("Automation")) == 0) ||
			(lstrcmpi(lpszToken, _T("Embedding")) == 0))
		{
			bAutomation = true;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if(bRun)
	{
		if(!bAutomation && CSingleInstance::Instance().IsAlreadyRunning())
		{
			// Only attempt this if manually started, i.e. allow automation
			// clients to start multiple instances, for what it's worth
			if(!CSingleInstance::Instance().ActivateRunningInstance())
			{
				MessageBox(NULL, _T("Failed to activate running instance of Developer Playground.\nPlease use Task Manager or similar to terminate rogue DP processes."), _T("DP Error"), MB_OK);
			}
		}
		else
		{
			if(!bAutomation)
			{
				// Auto-register self at startup, if manually started
				_Module.UpdateRegistryFromResource(IDR_DP, TRUE);
				nRet = _Module.RegisterServer(TRUE);
			}

			DWORD dwThreadId = 0;
			SmartHandle hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			SmartHandle hThread = CreateThread(NULL, 0, FactoryThreadProc, hEvent, 0, &dwThreadId);

			_Module.StartMonitor();

			if(bAutomation)
			{
				CMessageLoop theLoop;
				nRet = theLoop.Run();
			}
			else
			{
				nRet = Run(lpstrCmdLine, nCmdShow);
			}

			SetEvent(hEvent);
			::Sleep(_Module.m_dwPause);
		}
	}

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
