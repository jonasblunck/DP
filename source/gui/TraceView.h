#ifndef __TRACEVIEW_H__
#define __TRACEVIEW_H__

#pragma once 

#include <strstream>
#include "coms.h"

class HookedFunction;

typedef CWinTraits< WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | 
					LVS_SHOWSELALWAYS | LVS_REPORT, 
					WS_EX_CLIENTEDGE > CTraceViewTraits;

class CTraceView : 
	public CWindowImpl< CTraceView, CListViewCtrl, CTraceViewTraits >
{
public:
		
	enum TRACEVIEW_COLUMNS
	{
		TV_COL_TRACE_INDEX = 0,
		TV_COL_TIME = 1,
		TV_COL_PID = 2,
		TV_COL_MODULE = 3,
		TV_COL_RVA = 4,
		TV_COL_EXPORT = 5,
		TV_COL_MESSAGE = 6,
    TV_COL_ARGTRACE = 7
	};

	DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

BEGIN_MSG_MAP_EX(CTraceView)
	MSG_WM_CREATE(OnCreate)
END_MSG_MAP()

	CTraceView();

// Message handlers
	LRESULT OnCreate(LPCREATESTRUCT);
	
// Public interface
	BOOL OnTraceCallback(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR argTrace, DPAction action);
	BOOL OnHook(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction);
	BOOL OnUnhook(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction);
	BOOL Trace(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR pszMessage);

	BOOL CopyToClipboard();
	BOOL IsDirty();
	BOOL SaveToFile(LPCTSTR pszFilename);

	BOOL GetTraceData(int nItem, DWORD& rdwPID, CString& rstrModule, DWORD& rdwRVA, CString& rstrFunctionName);

private:
	void ResizeColumnHeaders();

	void WriteItemToStream(int nItem, std::strstream& stream);
	BOOL AddTraceItem(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR argTrace, LPCTSTR pszMessage);
	
	CString ResolveAction(DPAction action);
	CString GetCurrentTime();
	
	BOOL m_bIsDirty;
	DWORD m_cTraces;
};

#endif // __TRACEVIEW_H__
