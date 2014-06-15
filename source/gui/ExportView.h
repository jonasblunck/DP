#ifndef __EXPORTVIEW_H__
#define __EXPORTVIEW_H__

#pragma once 

#include "RunningProcesses.h"
#include "DebugSymbols.h"

// Somebody MS should have done this...
#define LPNMLVDISPINFO NMLVDISPINFO*

struct ExportItemData;
class IFindOperationCallback;

typedef CWinTraits< WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | 
					LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SORTASCENDING, 
					WS_EX_CLIENTEDGE > CExportViewTraits;

class CExportView : 
	public CWindowImpl< CExportView, CListViewCtrl, CExportViewTraits >,
	public IEnumerateExportsCallback,
  public IEnumerateDebugSymbolsCallback
{
public:
	enum EXPORTVIEW_COLUMNS
	{
		EV_COL_RVA = 0,
		EV_COL_NAME = 1,
		EV_COL_STATUS = 2,
    EV_COL_PARAMS = 3,
    EV_COL_TYPE = 4,
	};

	CExportView();

	DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

BEGIN_MSG_MAP_EX(CExportView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	REFLECTED_NOTIFY_CODE_HANDLER(LVN_DELETEITEM, OnItemDeleted)
	REFLECTED_NOTIFY_CODE_HANDLER(LVN_COLUMNCLICK, OnColumnClick)
END_MSG_MAP()

// Message handlers
	LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled);
	LRESULT OnColumnClick(int nCode, LPNMHDR pnmh, BOOL& bHandled);

// Public interface
	BOOL OnRefresh();
	BOOL FocusSingleItem(int nItem);
  BOOL Reload(DWORD dwPID, LPCTSTR pszModulePath);

	CString& GetCurrentModulePath();
	DWORD GetCurrentPID();

	void SetItemHooked(int nItem, BOOL bHooked);

  int FindItems(LPCTSTR pszFind, BOOL bMatchWholeWord, IFindOperationCallback* itemCallback);
	//int FindItem(LPCTSTR pszFunctionName, BOOL bMatchWholeWord = FALSE, int nStartFrom = 0);
	//int FindItem(DWORD dwRVA);
	
// IEnumerateExportsCallback
	BOOL OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
    LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParams);

  BOOL OnSymbol(LPCTSTR pszSymbolName, DWORD dwOrdinal, DWORD dwRVA, 
    LPCTSTR pszParameters);

private:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
  void UpdateUIAfterReload();
  void AddTreeItemToCache(LPCTSTR pszSymbolName, DWORD dwOrdinal, DWORD dwRVA, LPCTSTR pszParameters, LPCTSTR pszType);

	typedef std::map< DWORD, ExportItemData* > RVACACHEMAP;
	RVACACHEMAP m_rvaCache;

	CString m_strModulePath;
	DWORD m_dwPID;

	WORD m_wSortOrder;
	WORD m_wSortColumn;

	CRunningProcesses m_runningProcesses;
  CDebugSymbols m_debugSymbols;
	CImageList m_imageList;
};

#endif // __EXPORTVIEW_H__
