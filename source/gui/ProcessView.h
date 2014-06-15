#ifndef __PROCESSVIEW_H__
#define __PROCESSVIEW_H__

#pragma once 

#include "resource.h"
#include "RunningProcesses.h"

typedef CWinTraits< WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | 
					TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS | TVS_HASBUTTONS, 
					WS_EX_CLIENTEDGE > CProcessViewTraits;

class CProcessView :
	public CWindowImpl<CProcessView, CTreeViewCtrlEx, CProcessViewTraits>,
	public IEnumerateRunningProcessesCallback,
	public IEnumerateModulesCallback
{
public:
	CProcessView();

	DECLARE_WND_SUPERCLASS(NULL, CTreeViewCtrlEx::GetWndClassName())

	BOOL PreTranslateMessage(MSG*);

BEGIN_MSG_MAP_EX(CProcessView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	REFLECTED_NOTIFY_CODE_HANDLER(TVN_DELETEITEM, OnItemDeleted)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

// Message handlers
	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled);
	
// Public methods
	BOOL OnRefresh();
	BOOL TogglePath();
	BOOL IsPathShown();
//	int GetNodeLevel(HTREEITEM hti);
	CTreeItem FindItem(DWORD dwPID, LPCTSTR pszModulePath);
	BOOL RefreshImageList(BOOL bUseShellIcons);

// IEnumerateXXXCallback interfaces
	BOOL OnProcess(DWORD dwPID, LPCTSTR pszPath, void* pvContext);
	BOOL OnModule(DWORD dwPID, LPCTSTR pszModulePath, void* pvContext);

private:
	BOOL RecursiveTogglePath(const CTreeItem& tiCurrent, BOOL bShowPath);
	int GetImageIndex(LPCTSTR pszFilename, LPCTSTR pszDefault);
	int GetImageIndex(int csidl);

	BOOL m_bShowPath;
};

#endif // __PROCESSVIEW_H__

