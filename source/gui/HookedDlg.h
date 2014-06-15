#ifndef __HOOKEDDLG_H__
#define __HOOKEDDLG_H__

#pragma once 

#include "resource.h"

class CHookedDlg : 
	public CDialogImpl<CHookedDlg>,
	public CDialogResize<CHookedDlg>
{
public:
	CHookedDlg();

	enum { IDD = IDD_HOOKEDFUNCTIONS };

	BEGIN_MSG_MAP(CHookedDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_UNHOOK, OnUnhook)
		COMMAND_ID_HANDLER(IDC_UNHOOK_ALL, OnUnhookAll)
		NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnHooksSelChanged)
		NOTIFY_CODE_HANDLER(NM_DBLCLK,		OnDblClick)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_DELETEITEM, OnItemDeleted)
		CHAIN_MSG_MAP(CDialogResize<CHookedDlg>)
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CHookedDlg)
		// Move buttons
		DLGRESIZE_CONTROL(IDC_UNHOOK, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDC_UNHOOK_ALL, DLSZ_MOVE_X)
		DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X | DLSZ_MOVE_Y)

		// Resize tree
		DLGRESIZE_CONTROL(IDC_TREE_HOOKS, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUnhook(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnUnhookAll(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnHooksSelChanged(int, LPNMHDR, BOOL&);
	LRESULT OnDblClick(int, LPNMHDR, BOOL&);
	LRESULT OnItemDeleted(int nCode, LPNMHDR pnmh, BOOL& bHandled);

private:
	struct _ItemData
	{
		_ItemData(DWORD dwPID, long lHookID, LPCTSTR pszModulePath, DWORD dwRVA, LPCTSTR pszFunctionName)
			:	PID(dwPID),
				HookID(lHookID),
				RVA(dwRVA)
		{
			if(pszModulePath)
			{
				ModulePath = pszModulePath;
			}
			
			if(pszFunctionName)
			{
				FunctionName = pszFunctionName;
			}
		}

		DWORD PID;
		DWORD RVA;
		long HookID;
		CString ModulePath;
		CString FunctionName;
	};

	BOOL RefreshTree();

	BOOL UnhookAll();
	BOOL UnhookProcess(DWORD dwPID);
	BOOL UnhookSingle(_ItemData* pItemData);

	CTreeViewCtrlEx	m_hookedTree;
	CImageList		m_imageList;
	CButton			m_unhookButton;
	CButton			m_closeButton;
};

#endif // __HOOKEDDLG_H__
