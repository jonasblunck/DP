#ifndef __SMARTS_H__
#define __SMARTS_H__

#pragma once 

// Very handy for functions taking a char buffer and the number of chars it contains
#define lengthof(rg) (sizeof(rg) / sizeof(*rg))

// Proto-type for a smart handle - the template param should say either 0 (NULL) or -1 (INVALID_HANDLE_VALUE)
template< long _InvalidHandleValue >
struct SmartHandleT
{
	SmartHandleT() : m_h((HANDLE)_InvalidHandleValue) {}
	SmartHandleT(HANDLE h) : m_h(h) {}

	~SmartHandleT()
	{
		Close();
	}

	void Close()
	{
		if(m_h != (HANDLE)_InvalidHandleValue)
		{
			CloseHandle(m_h);
			m_h = (HANDLE)_InvalidHandleValue;
		}
	}

	BOOL IsValid()
	{
		return (m_h != (HANDLE)_InvalidHandleValue);
	}
	
	SmartHandleT< _InvalidHandleValue >& operator=(HANDLE h)
	{
		Close();
		m_h = h;

		return *this;
	}

	operator HANDLE()
	{
		return m_h;
	}

	HANDLE m_h;
};

// And some typedefs to make it clearer
typedef struct SmartHandleT< 0 > SmartHandle;
typedef struct SmartHandleT< -1 > SmartFileHandle;	// INVALID_HANDLE_VALUE == -1

// Module wrapper - uses LoadLibraryEx and FreeLibrary to manage resources
struct SmartModule
{
	SmartModule() : m_hm(NULL) {}
	SmartModule(HMODULE hm) : m_hm(hm) {}
	SmartModule(LPCTSTR pszFilename, DWORD dwFlags = 0) : m_hm(NULL)
	{
		Load(pszFilename, dwFlags);
	}

	~SmartModule()
	{
		Close();
	}

	BOOL Load(LPCTSTR pszFilename, DWORD dwFlags = 0)
	{
		Close();
		m_hm = LoadLibraryEx(pszFilename, NULL, dwFlags);

		return (m_hm != NULL);
	}

	void Close()
	{
		if(m_hm)
		{
			FreeLibrary(m_hm);
			m_hm = NULL;
		}
	}

	operator LPVOID()
	{
		return (LPVOID)m_hm;
	}

	operator LPBYTE()
	{
		return (LPBYTE)m_hm;
	}

	operator HMODULE()
	{
		return m_hm;
	}

	HMODULE m_hm;
};

// File mapping wrapper
// TODO: Make constructors for all the possible r/w params, etc.
struct SmartFileMapping
{
	SmartFileMapping() :
		m_pvMappedView(NULL)
	{
	}

	SmartFileMapping(LPCTSTR pszFilename) :
		m_pvMappedView(NULL)
	{
		Open(pszFilename);
	}

	~SmartFileMapping()
	{
		Close();
	}

	BOOL Open(LPCTSTR pszFilename)
	{
		// Ensure we've properly closed any previous resources
		Close();

		// Open file
		SmartFileHandle hFile = CreateFile(pszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			return FALSE;
		}

		// Map a view of the file
		SmartHandle hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
		if(hMapping == NULL)
		{
			return FALSE;
		}

		m_pvMappedView = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
		if(m_pvMappedView == NULL)
		{
			return FALSE;
		}

		return TRUE;
	}

	void Close()
	{
		if(m_pvMappedView != NULL)
		{
			UnmapViewOfFile(m_pvMappedView);
			m_pvMappedView = NULL;
		}
	}

	operator LPVOID()
	{
		return m_pvMappedView;
	}

	operator LPBYTE()
	{
		return (LPBYTE)m_pvMappedView;
	}

	operator LPDWORD()
	{
		return (LPDWORD)m_pvMappedView;
	}

private:
	LPVOID m_pvMappedView;
};

// Attempts to enable a privilege for the current thread
// Restores previous state in destructor
struct SmartThreadPrivilege
{
	SmartThreadPrivilege()
	{
		ZeroMemory(this, sizeof(*this));
	}

	SmartThreadPrivilege(LPCTSTR pszPrivilegeName)
	{
		m_bSucceeded = Enable(pszPrivilegeName);
	}

	~SmartThreadPrivilege()
	{
		Revert();
	}
	
	BOOL Enable(LPCTSTR pszPrivilegeName)
	{
		BOOL bRet = FALSE;
		
		if(m_hToken == NULL)
		{
			if(OpenThreadToken(GetCurrentThread(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, TRUE, &m_hToken.m_h))
			{
				TOKEN_PRIVILEGES tp;
				tp.PrivilegeCount = 1;
				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				bRet = LookupPrivilegeValue(0, pszPrivilegeName, &tp.Privileges[0].Luid);
				if(bRet)
				{
					DWORD cbOld = sizeof(m_tp);
					bRet = AdjustTokenPrivileges(m_hToken, FALSE, &tp, cbOld, &m_tp, &cbOld);
				}
			}
		}

		return bRet;
	}

	BOOL Revert()
	{
		BOOL bRet = TRUE;
		
		if(m_hToken != NULL)
		{
			bRet = AdjustTokenPrivileges(m_hToken, FALSE, &m_tp, 0, 0, 0);
		}

		return bRet;
	}

	BOOL Succeeded()
	{
		return m_bSucceeded;
	}

	SmartHandle			m_hToken;
	TOKEN_PRIVILEGES	m_tp;
	BOOL				m_bSucceeded;
};

// Attempts to enable a privilege for the current process
// Restores previous state in destructor
struct SmartProcessPrivilege
{
	SmartProcessPrivilege()
	{
		ZeroMemory(this, sizeof(*this));
	}

	SmartProcessPrivilege(LPCTSTR pszPrivilegeName)
	{
		m_bSucceeded = Enable(pszPrivilegeName);
	}

	~SmartProcessPrivilege()
	{
		Revert();
	}

	BOOL Enable(LPCTSTR pszPrivilegeName)
	{
		BOOL bRet = FALSE;

		if(m_hToken == NULL)
		{
			if(OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &m_hToken.m_h))
			{
				TOKEN_PRIVILEGES tp;
				tp.PrivilegeCount = 1;
				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				bRet = LookupPrivilegeValue(0, pszPrivilegeName, &tp.Privileges[0].Luid);
				if(bRet)
				{
					DWORD cbOld = sizeof(m_tp);
					bRet = AdjustTokenPrivileges(m_hToken, FALSE, &tp, cbOld, &m_tp, &cbOld);
				}
			}
		}

		return bRet;
	}

	BOOL Revert()
	{
		BOOL bRet = TRUE;

		if(m_hToken != NULL)
		{
			bRet = AdjustTokenPrivileges(m_hToken, FALSE, &m_tp, 0, 0, 0);
		}

		return bRet;
	}

	BOOL Succeeded()
	{
		return m_bSucceeded;
	}

	SmartHandle			m_hToken;
	TOKEN_PRIVILEGES	m_tp;
	BOOL				m_bSucceeded;
};

// Locks window update of the passed in window
struct SmartLockRedraw
{
	SmartLockRedraw(HWND hwnd)
		: m_hwnd(hwnd)
	{
		if(m_hwnd)
		{
			// Disable repaint
			SendMessage(m_hwnd, WM_SETREDRAW, FALSE, 0);
		}
	}

	~SmartLockRedraw()
	{
		if(m_hwnd)
		{
			// Restore repaint
			SendMessage(m_hwnd, WM_SETREDRAW, TRUE, 0);
		}
	}

private:
	HWND m_hwnd;
};

struct SmartCriticalSection
{
	SmartCriticalSection()
	{
		InitializeCriticalSection(&m_cs);
	}

	~SmartCriticalSection()
	{
		DeleteCriticalSection(&m_cs);
	}

	LPCRITICAL_SECTION operator&()
	{
		return &m_cs;
	}

	CRITICAL_SECTION m_cs;
};

struct SmartScopeLock
{
	SmartScopeLock(LPCRITICAL_SECTION lpcs)
	{
		m_lpcs = lpcs;
		EnterCriticalSection(m_lpcs);
	}

	~SmartScopeLock()
	{
		LeaveCriticalSection(m_lpcs);
	}

	LPCRITICAL_SECTION m_lpcs;
};

// Reference counting helpers
class SmartRCBase
{
public:
	SmartRCBase() : m_cRef(0) {}
	virtual ~SmartRCBase() {}

	DWORD IncRef()
	{
		return ++m_cRef;
	}

	DWORD DecRef()
	{
		DWORD dw = --m_cRef;
		if(dw == 0)
		{
			delete this;
		}

		return dw;
	}

private:
	BYTE PreGuard[256];
	DWORD m_cRef;
	BYTE PostGuard[256];
};

template< class T >
class SmartRefPtr
{
public:
	SmartRefPtr()
	{
		m_p = NULL;
	}

	SmartRefPtr(T* p)
	{
		m_p = p;
		if(m_p)
		{
			m_p->IncRef();
		}
	}

	SmartRefPtr(const SmartRefPtr& p)
	{
		m_p = p.m_p;
		if(m_p)
		{
			m_p->IncRef();
		}
	}

	~SmartRefPtr()
	{
		Release();
	}

	SmartRefPtr& operator=(T* p)
	{
		Release();

		m_p = p;
		if(m_p)
		{
			m_p->IncRef();
		}

		return *this;
	}

	SmartRefPtr& operator=(const SmartRefPtr& p)
	{
		Release();

		m_p = p.m_p;
		if(m_p)
		{
			m_p->IncRef();
		}

		return *this;
	}

	void Release()
	{
		if(m_p)
		{
			m_p->DecRef();
			m_p = NULL;
		}
	}

	T* operator->()
	{
		ATLASSERT(m_p);
		return m_p;
	}

	BOOL operator!=(T* p)
	{
		return !operator==(p);
	}

	BOOL operator==(T* p)
	{
		return (m_p == p);
	}

	T* GetPointer()
	{
		return m_p;
	}

private:
	T* m_p;
};

#endif // __SMARTS_H__

