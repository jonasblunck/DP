#include "stdafx.h"
#include "ProcessView.h"
#include "ItemData.h"

CProcessView::CProcessView()
{	
	m_bShowPath = FALSE;
}

BOOL CProcessView::PreTranslateMessage(MSG*)
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// Message handlers
LRESULT CProcessView::OnCreate(UINT, WPARAM, LPARAM, BOOL&)
{
	// Forward to base window proc
	if(DefWindowProc() != 0) return -1;

	SHFILEINFO sfi = {0};
	CImageList systemImageList = (HIMAGELIST)::SHGetFileInfo(_T(""), 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	SetImageList(systemImageList, TVSIL_NORMAL);

	OnRefresh();

	return 0;
}

LRESULT CProcessView::OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled)
{
	// Destroy item data
	delete (TreeItemData*)(((LPNMTREEVIEW)pnmh)->itemOld.lParam);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// Public methods
BOOL CProcessView::OnRefresh()
{
	CWaitCursor wc;
	
	DeleteAllItems();

	// Create root item
	int nImage = GetImageIndex(CSIDL_DRIVES);
	CTreeItem tiRoot = InsertItem(_T("Processes"), nImage, nImage, NULL, NULL);
	tiRoot.SetData(NULL);

	// Populate tree
	CRunningProcesses runningProcesses;
	runningProcesses.EnumerateRunningProcesses(this, (void*)tiRoot, COptionsStorage::Instance().GetEnableSeDebugPriv());

	// Expand root item
	return Expand(tiRoot);
}

BOOL CProcessView::TogglePath()
{
	m_bShowPath = !m_bShowPath;
	if(!RecursiveTogglePath(GetRootItem().GetChild(), m_bShowPath))
	{
		return FALSE;
	}

	return SortChildren(GetRootItem());
}

BOOL CProcessView::IsPathShown()
{
	return m_bShowPath;
}

CTreeItem CProcessView::FindItem(DWORD dwPID, LPCTSTR pszModulePath)
{
	for(CTreeItem tiProcess = GetRootItem().GetChild(); tiProcess != NULL; tiProcess = tiProcess.GetNextSibling())
	{
		TreeItemData* ptid = (TreeItemData*)tiProcess.GetData();
		if(ptid->GetPID() == dwPID)
		{
			for(CTreeItem tiModule = tiProcess.GetChild(); tiModule != NULL; tiModule = tiModule.GetNextSibling())
			{
				TreeItemData* pModuleData = (TreeItemData*)tiModule.GetData();
				if(_tcsicmp(pModuleData->GetPath(), pszModulePath) == 0)
				{
					return tiModule;
				}
			}
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// IEnumerateRunningProcessesCallback implementation
BOOL CProcessView::OnProcess(DWORD dwPID, LPCTSTR pszPath, void* pvContext)
{
	if(dwPID == GetCurrentProcessId())
	{
		// Skip self
		return TRUE;
	}

	HTREEITEM htiRoot = (HTREEITEM)pvContext;

	TreeItemData* pProcess = new TreeItemData(dwPID, pszPath, NODETYPE_PROCESS);
	if(pProcess == NULL)
	{
		return FALSE;
	}

	// Set exe name or path as tree item
	CString strTreeItemText;
	if(m_bShowPath)
	{
		strTreeItemText.Format(_T("%s [%lu]"), pszPath, dwPID);
	}
	else
	{
		strTreeItemText.Format(_T("%s [%lu]"), pProcess->GetName(), dwPID);
	}

	int nImage = GetImageIndex(pProcess->GetPath(), _T(".exe"));
	CTreeItem tiProcess = InsertItem(strTreeItemText, nImage, nImage, htiRoot, TVI_SORT);
	if(tiProcess == NULL)
	{
		delete pProcess;
		return FALSE;
	}
	
  // Set item data
  tiProcess.SetData((DWORD)pProcess);

  //TreeItemData* pExports = new TreeItemData(dwPID, pszPath, NODETYPE_EXPORTS);
  //CTreeItem tiExports = InsertItem(_T("Exports"), (HTREEITEM)tiProcess, 0);
  //tiExports.SetData((DWORD)pExports);

  //TreeItemData* pDebug = new TreeItemData(dwPID, pszPath, NODETYPE_DEBUGSYM);
  //CTreeItem tiDebug = InsertItem(_T("Debug symbols"), (HTREEITEM)tiProcess, 0);
  //tiDebug.SetData((DWORD)pDebug);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// IEnumerateModulesCallback implementation
BOOL CProcessView::OnModule(DWORD dwPID, LPCTSTR pszModulePath, void* pvContext)
{
	HTREEITEM htiParent = (HTREEITEM)pvContext;

	TreeItemData* pModule = new TreeItemData(dwPID, pszModulePath, NODETYPE_DLL);
	if(pModule == NULL)
	{
		return FALSE;
	}

	// Text is path or name
	CString strTreeItemText;
	if(m_bShowPath)
	{
		strTreeItemText = pModule->GetPath();
	}
	else
	{
		strTreeItemText = pModule->GetName();
	}

	int nImage = GetImageIndex(pModule->GetPath(), _T(".dll"));
	CTreeItem tiModule = InsertItem(strTreeItemText, nImage, nImage, htiParent, TVI_SORT);
	if(tiModule == NULL)
	{
		delete pModule;
		return FALSE;
	}

	// Set item data
	tiModule.SetData((DWORD)pModule);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// Private helpers
/*
int CProcessView::GetNodeLevel(HTREEITEM hti)
{
	int iNodeLevel = NODETYPE_PROCESSES;

	if(hti)
	{
		TreeItemData* ptid = (TreeItemData*)GetItemData(hti);
		if(ptid != NULL)
		{
			iNodeLevel = ptid->GetNodeType();
		}
	}

	return iNodeLevel;
}
*/
BOOL CProcessView::RecursiveTogglePath(const CTreeItem& tiCurrent, BOOL bShowPath)
{
	for(CTreeItem ti = tiCurrent; ti != NULL; ti = ti.GetNextSibling())
	{
		TreeItemData* ptid = (TreeItemData*)ti.GetData();

		CString strItemText;
		if(bShowPath)
		{
			strItemText = ptid->GetPath();
		}
		else
		{
			strItemText = ptid->GetName();
		}

		if(ti.GetParent() == GetRootItem())
		{
			// This is a process - tuck on the PID
			CString strPID;
			strPID.Format(_T(" [%lu]"), ptid->GetPID());
			strItemText += strPID;
		}

		if(!ti.SetText(strItemText))
		{
			return FALSE;
		}

		if(ti.HasChildren())
		{
			if(!RecursiveTogglePath(ti.GetChild(), bShowPath))
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

int CProcessView::GetImageIndex(LPCTSTR pszFilename, LPCTSTR pszDefault)
{
	int iRet = 0;

	SHFILEINFO sfi = {0};
	if(::SHGetFileInfo(pszFilename, 0, &sfi, sizeof(sfi), SHGFI_SYSICONINDEX | SHGFI_SMALLICON))
	{
		iRet = sfi.iIcon;
	}
	else if(::SHGetFileInfo(pszDefault, FILE_ATTRIBUTE_NORMAL, &sfi, sizeof(sfi), SHGFI_USEFILEATTRIBUTES | SHGFI_SYSICONINDEX | SHGFI_SMALLICON))
	{
		iRet = sfi.iIcon;
	}
	
	return iRet;
}

int CProcessView::GetImageIndex(int csidl)
{
	int iRet = 0;

	HRESULT hr;		

	LPITEMIDLIST pidl;
	hr = SHGetSpecialFolderLocation(m_hWnd, csidl, &pidl);
	if(SUCCEEDED(hr))
	{
		SHFILEINFO sfi = {0};
		::SHGetFileInfo((LPCTSTR)pidl, 0, &sfi, sizeof(sfi), SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

		iRet = sfi.iIcon;

		CComPtr<IMalloc> spMalloc;
		if(SUCCEEDED(SHGetMalloc(&spMalloc)))
		{
			spMalloc->Free(pidl);
		}
	}

	return iRet;
}

