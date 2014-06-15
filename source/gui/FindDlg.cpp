#include "stdafx.h"
#include "FindDlg.h"


LRESULT CFindDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());

	SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)));
	
	m_edit.Attach(GetDlgItem(IDC_EDIT_FIND));
	m_edit.SetLimitText(255);

	m_wholeWordCheckBox.Attach(GetDlgItem(IDC_CHK_MATCH_WHOLE));

	m_bMatchWholeWordOnly = FALSE;

	return 1;
}

LRESULT CFindDlg::OnFind(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	TCHAR szText[256];
	m_edit.GetWindowText(szText, lengthof(szText));
	m_strSearchString = szText;
	
	m_bMatchWholeWordOnly = (m_wholeWordCheckBox.GetCheck() == 1);

	EndDialog(wID);
	return 0;
}

LRESULT CFindDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

CString& CFindDlg::GetSearchString()
{
	return m_strSearchString;
}

BOOL CFindDlg::GetMatchWholeWordOnly()
{
	return m_bMatchWholeWordOnly;
}