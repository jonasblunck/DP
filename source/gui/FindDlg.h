#ifndef __FINDDLG_H__
#define __FINDDLG_H__

#pragma once 

#include "resource.h"

class CFindDlg : public CDialogImpl<CFindDlg>
{
public:
	enum { IDD = IDD_FIND };

BEGIN_MSG_MAP(CAboutDlg)
	MESSAGE_HANDLER(WM_INITDIALOG,	OnInitDialog)
	COMMAND_ID_HANDLER(IDOK,		OnFind)
	COMMAND_ID_HANDLER(IDCANCEL,	OnCancel)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFind(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	CString& GetSearchString();
	BOOL GetMatchWholeWordOnly();

private:
	CEdit	m_edit;
	CString m_strSearchString;
	CButton m_wholeWordCheckBox;

	BOOL	m_bMatchWholeWordOnly;
};

#endif // __FINDDLG_H__
