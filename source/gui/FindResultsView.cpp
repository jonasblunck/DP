#include "stdafx.h"
#include "resource.h"
#include "FindResultsView.h"
#include "ItemData.h"

CFindResultsView::CFindResultsView()
{
  m_wSortOrder = 1;
  m_wSortColumn = EV_COL_NAME;
}

BOOL CFindResultsView::PreTranslateMessage(MSG*)
{
	return FALSE;
}

LRESULT CFindResultsView::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
	if (DefWindowProc() != 0) return -1;

	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

	AddColumn(_T("RVA"),			EV_COL_RVA);
  AddColumn(_T("Module"), EV_COL_MODULE);
	AddColumn(_T("Function Name"),	EV_COL_NAME);
  AddColumn(_T("Parameters"), EV_COL_PARAMS);
  AddColumn(_T("Type"), EV_COL_TYPE);

	SetColumnWidth(EV_COL_RVA,		75);
  SetColumnWidth(EV_COL_MODULE,		250);
  SetColumnWidth(EV_COL_NAME,		200);
	SetColumnWidth(EV_COL_PARAMS,	220);
	SetColumnWidth(EV_COL_TYPE,	80);

	return 0;
}

LRESULT CFindResultsView::OnColumnClick(int nCode, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLISTVIEW pnmlv = (LPNMLISTVIEW)pnmh;

	if(pnmlv->iSubItem == m_wSortColumn)
	{
		// Toggle sort order
		m_wSortOrder = !m_wSortOrder;
	}
	else
	{
		m_wSortColumn = pnmlv->iSubItem;
	}

//	SortItems(CompareFunc, MAKELPARAM(m_wSortColumn, m_wSortOrder));

	return 0;
}

void CFindResultsView::OnItem(DWORD rwa, LPCTSTR pszModule, LPCTSTR name, LPCTSTR parameters, LPCTSTR type)
{
  CString strRVA;
  strRVA.Format("0x%06X", rwa);

  int nAddedItem = InsertItem(0, strRVA, IMG_FUNCTION);
  AddItem(nAddedItem, EV_COL_MODULE, pszModule);
  AddItem(nAddedItem, EV_COL_NAME, name);
  AddItem(nAddedItem, EV_COL_PARAMS, parameters);
  AddItem(nAddedItem, EV_COL_TYPE, type);

  ExportItemData* pItemData = new ExportItemData(0, rwa, name, parameters, type);
  SetItemData(nAddedItem, (DWORD)pItemData); 

  // TODO - Fix memory leak!

}

