#include "stdafx.h"
#include "resource.h"
#include "ExportView.h"

#include "ItemData.h"
#include "HookManager.h"
#include "HookedStructures.h"

#include "FunctionFile.h"
#include "IFindOperationCallback.h"


CExportView::CExportView()
{
	m_dwPID = 0;
	m_wSortOrder = 1;
	m_wSortColumn = EV_COL_RVA;
}

BOOL CExportView::PreTranslateMessage(MSG*)
{
	return FALSE;
}

LRESULT CExportView::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
	if (DefWindowProc() != 0) return -1;

	// Setup image list
	if(!m_imageList.Create(IDB_MODULES, 16, 1, CR_BACKGROUND_COLOR))
	{
		return -1;
	}

	SetImageList(m_imageList, LVSIL_SMALL);
	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

	AddColumn(_T("RVA"),			EV_COL_RVA);
	AddColumn(_T("Function Name"),	EV_COL_NAME);
	AddColumn(_T("Status"),			EV_COL_STATUS);
  AddColumn(_T("Parameters"), EV_COL_PARAMS);
  AddColumn(_T("Type"), EV_COL_TYPE);

	SetColumnWidth(EV_COL_RVA,		75);
	SetColumnWidth(EV_COL_NAME,		200);
	SetColumnWidth(EV_COL_STATUS,	100);
	SetColumnWidth(EV_COL_PARAMS,	180);
	SetColumnWidth(EV_COL_TYPE,	80);

  m_debugSymbols.Initialize();

	return 0;
}

LRESULT CExportView::OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled)
{
	// Get item data
	ExportItemData* pItem = (ExportItemData*)((LPNMLISTVIEW)pnmh)->lParam;

	// Remove cache entry
	m_rvaCache.erase(pItem->GetRVA());

	// Destroy item data
	delete pItem;
	
	return 0;
}

LRESULT CExportView::OnColumnClick(int nCode, LPNMHDR pnmh, BOOL& bHandled)
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

	SortItems(CompareFunc, MAKELPARAM(m_wSortColumn, m_wSortOrder));

	return 0;
}

void CExportView::UpdateUIAfterReload()
{
    // Commit the changes to the GUI
  SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(m_dwPID);

  SmartLockRedraw lock(m_hWnd);
  for(RVACACHEMAP::iterator i = m_rvaCache.begin(); i != m_rvaCache.end(); ++i)
  {
    ExportItemData* pItem = (*i).second;

    CString strRVA;
    strRVA.Format(_T("0x%06X"), pItem->GetRVA());

    int nAddedItem = InsertItem(0, strRVA, IMG_FUNCTION);
    AddItem(nAddedItem, EV_COL_NAME, pItem->GetName());
    AddItem(nAddedItem, EV_COL_PARAMS, pItem->GetParameters());
    AddItem(nAddedItem, EV_COL_TYPE, pItem->GetType());

    // Store item data
    SetItemData(nAddedItem, (DWORD_PTR)pItem);

    // Mark as hooked
    if(pProcess != NULL)
    {
      SmartRefPtr<HookedFunction> function = pProcess->IsFunctionHooked(m_strModulePath, pItem->GetRVA());
      if(function.GetPointer() != NULL)
      {
        SetItemHooked(nAddedItem, TRUE);
      }
    }
  }
}

BOOL CExportView::Reload(DWORD dwPID, LPCTSTR pszModulePath)
{
  // Visual feedback that we're working
  CWaitCursor wc;

  DeleteAllItems();

  m_dwPID = dwPID;
  m_strModulePath = pszModulePath;

  // enum the symbols...
  m_debugSymbols.EnumerateSymbols(pszModulePath, this);
	m_runningProcesses.EnumerateExports(m_strModulePath, this, NULL, COptionsStorage::Instance().GetUndecorateSymbols());

  UpdateUIAfterReload();

  return TRUE;
}

BOOL CExportView::OnRefresh()
{
	m_dwPID = 0;
	m_strModulePath.Empty();
	
	return DeleteAllItems();
}

void CExportView::SetItemHooked(int nItem, BOOL bHooked)
{
	ExportItemData* pItem = (ExportItemData*)GetItemData(nItem);
	pItem->SetHooked(bHooked);

	if(bHooked)
	{
		SetItem(nItem, EV_COL_RVA, LVIF_IMAGE, 0, IMG_FUNCTION_HOOKED, 0, 0, 0);
		SetItem(nItem, EV_COL_STATUS, LVIF_TEXT, _T("Hooked"), 0, 0, 0, 0);
	}
	else
	{
		SetItem(nItem, EV_COL_RVA, LVIF_IMAGE, 0, IMG_FUNCTION, 0, 0, 0);
		SetItem(nItem, EV_COL_STATUS, LVIF_TEXT, _T(""), 0, 0, 0, 0);
	}
}

int CExportView::FindItems(LPCTSTR pszFind, BOOL bMatchWholeWord, IFindOperationCallback* itemCallback)
{
  int itemsFound = 0;

  CString strFunctionName(pszFind);
  strFunctionName.MakeLower();

  for(int n = 0; n < GetItemCount(); ++n)
  {
    bool found = false;

    CString strItemText;
    if(GetItemText(n, EV_COL_NAME, strItemText))
    {
      strItemText.MakeLower();

      if(bMatchWholeWord)
      {
        if(strFunctionName == strItemText)
        {
          found = true;
        }
      }
      else if (strItemText.Find(strFunctionName) != -1)
      {
        found = true;
      }
    }

    if (found)
    {
      ExportItemData* data = (ExportItemData*)GetItemData(n);
      itemCallback->OnItem(data->GetRVA(), (LPCTSTR)m_strModulePath, data->GetName(), data->GetParameters(), data->GetType());
      ++itemsFound;
    }
  }

  return itemsFound;
}

BOOL CExportView::FocusSingleItem(int nItem)
{
	// Set the item focused and ensure it's visible
	if(!SetItemState(nItem, LVIS_FOCUSED, LVIS_FOCUSED))
	{
		return FALSE;
	}

	return EnsureVisible(nItem, FALSE);
}

CString& CExportView::GetCurrentModulePath()
{
	return m_strModulePath;
}

DWORD CExportView::GetCurrentPID()
{
	return m_dwPID;
}

void CExportView::AddTreeItemToCache(LPCTSTR pszSymbolName, DWORD dwOrdinal, DWORD dwRVA, LPCTSTR pszParameters, LPCTSTR pszType)
{
	RVACACHEMAP::iterator i = m_rvaCache.find(dwRVA);
	if(i != m_rvaCache.end())
	{
		// If the RVA is already there, update the function name...
		ExportItemData* pItem = (*i).second;
		pItem->AppendName(pszSymbolName);
	}
	else
	{
		// ... otherwise, add it
		ExportItemData* pItem = new ExportItemData(dwOrdinal, dwRVA, pszSymbolName, pszParameters, pszType);
		m_rvaCache[dwRVA] = pItem;
	}
}

////////////////////////////////////////////////////////////////////////////////////
/// IEnumerateExportsCallback implementation
BOOL CExportView::OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
                           LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParams)
{
  AddTreeItemToCache(pszFunctionName, dwOrdinal, dwRVA, pszParams, "Export");

	return TRUE;
}

BOOL CExportView::OnSymbol(LPCTSTR pszSymbolName, DWORD dwOrdinal, DWORD dwRVA, LPCTSTR pszParameters)
{
  LPCTSTR pszModule = _T("Symbols");

  AddTreeItemToCache(pszSymbolName, dwOrdinal, dwRVA, pszParameters, "Debug Symbol");

  return TRUE;
}


//////////////////////////////////////////////////////////////////////////
/// Private methods
int CALLBACK CExportView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iRet = 0;

	ExportItemData* pItem1 = NULL;
	ExportItemData* pItem2 = NULL;

	WORD wSortColumn = LOWORD(lParamSort);
	WORD wSortOrder = HIWORD(lParamSort);

	if(wSortOrder)
	{
		pItem1 = (ExportItemData*)lParam1;
		pItem2 = (ExportItemData*)lParam2;
	}
	else
	{
		pItem1 = (ExportItemData*)lParam2;
		pItem2 = (ExportItemData*)lParam1;
	}

	switch(wSortColumn)
	{
	case EV_COL_RVA:
		iRet = (pItem1->GetRVA() - pItem2->GetRVA());
		break;
	case EV_COL_NAME:
		iRet = _tcscmp(pItem1->GetName(), pItem2->GetName());
		break;
	case EV_COL_STATUS:
		if(pItem2->IsHooked() == pItem1->IsHooked())
		{
			iRet = 0;
		}
		else if(pItem1->IsHooked() && !pItem2->IsHooked())
		{
			iRet = -1;
		}
		else if(pItem2->IsHooked() && !pItem1->IsHooked())
		{
			iRet = 1;
		}
	}

	return iRet;
}

