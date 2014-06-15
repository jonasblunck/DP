#ifndef __FINDRESULTSVIEW_H__
#define __FINDRESULTSVIEW_H__

#pragma once 

#include "IFindOperationCallback.h"


typedef CWinTraits< WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | 
					LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SORTASCENDING, 
					WS_EX_CLIENTEDGE > CFindResultsViewTraits;

class CFindResultsView : 
	public CWindowImpl< CFindResultsView, CListViewCtrl, CFindResultsViewTraits >,
  public IFindOperationCallback
{
public:
	enum FINDRESULTSVIEW_COLUMNS
	{
		EV_COL_RVA = 0,
		EV_COL_MODULE = 1,
    EV_COL_NAME = 2,
    EV_COL_PARAMS = 3,
    EV_COL_TYPE = 4,
	};

	CFindResultsView();

	DECLARE_WND_SUPERCLASS(NULL, CListViewCtrl::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg);

BEGIN_MSG_MAP_EX(CFindResultsView)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	REFLECTED_NOTIFY_CODE_HANDLER(LVN_COLUMNCLICK, OnColumnClick)
END_MSG_MAP()

private:
  // Message handlers
  LRESULT OnCreate(UINT, WPARAM, LPARAM, BOOL&);
  LRESULT OnColumnClick(int nCode, LPNMHDR pnmh, BOOL& bHandled);

  // IFindOperationCallback
  virtual void OnItem(DWORD rwa, LPCTSTR pszModule, LPCTSTR name, LPCTSTR parameters, LPCTSTR type);


  WORD m_wSortOrder;
  WORD m_wSortColumn;
};

#endif // __EXPORTVIEW_H__
