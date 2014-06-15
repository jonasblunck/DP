// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABOUTDLG_H__71B57706_ABC9_476E_BB3F_A3C4D0311D9B__INCLUDED_)
#define AFX_ABOUTDLG_H__71B57706_ABC9_476E_BB3F_A3C4D0311D9B__INCLUDED_

#include "resource.h"

class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	CHyperLink m_hlBlunck;
	CHyperLink m_hlWinwonk;

	void LeftAlignHyperLinkLabel(CHyperLink& hl);
//	void CenterHyperLinkLabel(CHyperLink& hl);
};

#endif // !defined(AFX_ABOUTDLG_H__71B57706_ABC9_476E_BB3F_A3C4D0311D9B__INCLUDED_)
