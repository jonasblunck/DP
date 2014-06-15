#include "stdafx.h"
#include "HookedDlg.h"
#include "HookedStructures.h"
#include "MainFrm.h"
#include "HookManager.h"

CHookedDlg::CHookedDlg()
{
}

LRESULT CHookedDlg::OnInitDialog(UINT , WPARAM , LPARAM , BOOL& )
{
	DlgResize_Init();

	CenterWindow(GetParent());

	SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)));

	// Attach to controls
	m_hookedTree.Attach(GetDlgItem(IDC_TREE_HOOKS));
	m_unhookButton.Attach(GetDlgItem(IDC_UNHOOK));
	m_closeButton.Attach(GetDlgItem(IDCANCEL));

	// Setup image list
	if(!m_imageList.Create(IDB_MODULES, 16, 1, RGB(0, 128, 128)))
	{
		return -1;
	}

	m_hookedTree.SetImageList(m_imageList, TVSIL_NORMAL);

	// Render all hooked functions
	RefreshTree();
	
	return 0;
}

LRESULT CHookedDlg::OnUnhook(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CTreeItem ti = m_hookedTree.GetSelectedItem();
	_ItemData* pItemData = (_ItemData*)m_hookedTree.GetItemData(ti);
	if(pItemData->RVA != 0)
	{
		// This is a function
		UnhookSingle(pItemData);
	}
	else
	{
		// This is a process
		UnhookProcess(pItemData->PID);
	}
	
	m_hookedTree.DeleteItem(ti);

	return 0;
}

LRESULT CHookedDlg::OnUnhookAll(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	UnhookAll();
	CMainFrame::Instance().m_ExportView.OnRefresh();
	RefreshTree();

	return 0;
}

LRESULT CHookedDlg::OnCloseCmd(WORD , WORD wID, HWND , BOOL& )
{
	EndDialog(wID);
	return 0;
}

LRESULT CHookedDlg::OnHooksSelChanged(int, LPNMHDR, BOOL&)
{
	BOOL bEnabled = FALSE;

	HTREEITEM hti = m_hookedTree.GetSelectedItem();
	if(hti != NULL && m_hookedTree.GetItemData(hti) != 0)
	{
		bEnabled = TRUE;
	}

	m_unhookButton.EnableWindow(bEnabled);

	return 0;
}

LRESULT CHookedDlg::OnDblClick(int, LPNMHDR pnmh, BOOL&)
{
	POINT ptClicked = {LOWORD(::GetMessagePos()), HIWORD(::GetMessagePos())};

	if(pnmh->hwndFrom == m_hookedTree.m_hWnd)
	{
		// Map the clicked pixel to listview's client area
		m_hookedTree.ScreenToClient(&ptClicked);

		TVHITTESTINFO tvhtti = { { ptClicked.x, ptClicked.y } };
		CTreeItem tiClicked = m_hookedTree.HitTest(&tvhtti);
		if(tiClicked != NULL && tiClicked != m_hookedTree.GetRootItem())
		{
			m_hookedTree.SelectItem(tiClicked);

			BOOL b;
			return OnUnhook(0, 0, 0, b);
		}
	}

	return 0;

}

LRESULT CHookedDlg::OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled)
{
	// Destroy item data
	delete (_ItemData*)(((LPNMTREEVIEW)pnmh)->itemOld.lParam);
	return 0;	
}

//////////////////////////////////////////////////////////////////////////
/// Private methods
BOOL CHookedDlg::RefreshTree()
{
	CWaitCursor wc;
	
	SmartLockRedraw lockWindow(m_hookedTree.m_hWnd);

	m_hookedTree.DeleteAllItems();
	CHookManager::Instance().RemoveAllDeadProcesses();

	// Add root item
	CTreeItem tiRoot = m_hookedTree.InsertItem(_T("All hooked functions"), IMG_ROOT, IMG_ROOT, NULL, NULL);
	m_hookedTree.SetItemData(tiRoot, NULL);

	// Populate the tree
	for(DWORD i = 0; i < CHookManager::Instance().GetHookedProcessCount(); ++i)
	{
		SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcessByIndex(i);
		if(pProcess != NULL)
		{
			CString strProcess;
			strProcess.Format(_T("%s [%lu]"), pProcess->GetProcessName(), pProcess->GetPID());

			CTreeItem tiProcess = m_hookedTree.InsertItem(strProcess, IMG_PROCESS, IMG_PROCESS, tiRoot, NULL);
			m_hookedTree.SetItemData(tiProcess, (DWORD_PTR)new _ItemData(pProcess->GetPID(), 0, NULL, 0, NULL));

			for(HookedProcess::map_type::iterator it = pProcess->HookedFunctions.begin(); it != pProcess->HookedFunctions.end(); ++it)
			{
				SmartRefPtr<HookedFunction> pFunction = (*it).second;
				if(pFunction != NULL)
				{
					CString str = pFunction->GetModuleName();
					str += _T(" - ");
					str += pFunction->GetFunctionName();

					CTreeItem ti = m_hookedTree.InsertItem(str, IMG_FUNCTION_HOOKED, IMG_FUNCTION_HOOKED, tiProcess, NULL);
					m_hookedTree.SetItemData(ti, (DWORD_PTR)new _ItemData(pProcess->GetPID(), pFunction->GetHookID(), pFunction->GetModulePath(), pFunction->GetRVA(), pFunction->GetFunctionName()));
				}
			}
		}
	}

	m_hookedTree.Expand(tiRoot);

	return TRUE;
}

BOOL CHookedDlg::UnhookAll()
{
	BOOL bRet = CHookManager::Instance().RemoveAllHookedProcesses();
	if(bRet)
	{
		CMainFrame::Instance().m_TraceView.Trace(0, _T(""), 0, _T(""), _T("Detached from all processes"));
		CMainFrame::Instance().m_ExportView.OnRefresh();
	}

	return bRet;
}

BOOL CHookedDlg::UnhookProcess(DWORD dwPID)
{
	if(CHookManager::Instance().ExistsHookedProcess(dwPID))
	{
		// Detach from process
		CHookManager::Instance().RemoveHookedProcess(dwPID);

		// Feedback into GUI
		CMainFrame::Instance().TraceMessage(dwPID, _T(""), 0, _T(""), _T("Detached from process"));
		CMainFrame::Instance().m_ExportView.OnRefresh();
	}

	return TRUE;
}

BOOL CHookedDlg::UnhookSingle(_ItemData* pItemData)
{
	CString strResult = "Unhooked";

	SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(pItemData->PID);
	if(pProcess != NULL)
	{
		HRESULT hr = pProcess->UnhookFunction(pItemData->HookID);
		if(FAILED(hr))
		{
			strResult.Format(_T("Failed to unhook (0x%X)"), hr);
		}
	}

	CMainFrame::Instance().m_TraceView.Trace(pItemData->PID, pItemData->ModulePath, pItemData->RVA, pItemData->FunctionName, strResult);
	CMainFrame::Instance().m_ExportView.OnRefresh();

	return TRUE;
}