#ifndef __OPTIONSDLG_H__
#define __OPTIONSDLG_H__

#include "resource.h"

class COptionsDlg : public CDialogImpl< COptionsDlg >
{
public:
	enum { IDD = IDD_OPTIONS };

	BEGIN_MSG_MAP(COptionsDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_ID_HANDLER(IDC_BUTTON_BROWSE_DEPENDS, OnBrowseForDepends)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBrowseForDepends(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

private:
	BOOL BrowseForFile(LPCTSTR pszFilename, CString& rstrFilePath);

	CEdit m_editDependsPath;

	CButton m_chkEnablePriv;
	CButton m_chkStripSuffix;
	CButton m_chkUndecorateSymbols;
	CButton m_chkPauseWhileHooking;
	CButton m_chkAutoScroll;
	CButton m_chkShowStack;
};

#endif //__OPTIONSDLG_H__
