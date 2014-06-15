#ifndef __SINGLEINSTANCE_H__
#define __SINGLEINSTANCE_H__

class CSingleInstance
{
public:
	// Singleton accessor
	static CSingleInstance& Instance()
	{
		static CSingleInstance _instance;
		return _instance;
	}

	~CSingleInstance()
	{
		if(m_hInstanceMutex)
		{
		   CloseHandle(m_hInstanceMutex);
		   m_hInstanceMutex = NULL;
		}
	}

	BOOL IsAlreadyRunning()
	{
		return (m_hInstanceMutex != NULL && m_dwLastError == ERROR_ALREADY_EXISTS);
	}

	BOOL ActivateRunningInstance()
	{
		BOOL bRet = FALSE;

		// Attempt to bring up the old instance
		HWND hwnd = FindWindow(_T("DPMainFrame"), _T("Developer Playground"));
		if(hwnd != NULL)
		{
			WINDOWPLACEMENT wp = {0};
			wp.length = sizeof(wp);
			if(GetWindowPlacement(hwnd, &wp))
			{
				if(wp.showCmd == SW_SHOWMINIMIZED)
				{
					// If window is minimized - flash it
					FLASHWINFO fwi = { sizeof(fwi), hwnd, FLASHW_ALL | FLASHW_TIMERNOFG};
					bRet = FlashWindowEx(&fwi);
				}
				else
				{
					// Else bring it to foreground
					bRet = SetForegroundWindow(hwnd);
				}
			}
		}

		return bRet;
	}

private:
	CSingleInstance()
	{
		// Create a mutex named after the trace listener CLSID
		m_hInstanceMutex = CreateMutex(NULL, FALSE, _T("A115A87C-5C74-460E-9180-E394D2976CD0"));
		m_dwLastError = GetLastError();
	}

	HANDLE m_hInstanceMutex;
	DWORD m_dwLastError;
};

#endif //__SINGLEINSTANCE_H__
