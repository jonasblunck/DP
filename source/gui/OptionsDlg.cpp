#include "stdafx.h"
#include "OptionsDlg.h"
#include "OptionsStorage.h"

LRESULT COptionsDlg::OnInitDialog(UINT , WPARAM , LPARAM , BOOL& )
{
	CenterWindow(GetParent());

	SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)));

	m_editDependsPath.Attach(GetDlgItem(IDC_EDIT_PATH_DEPENDS));

	m_chkEnablePriv.Attach(GetDlgItem(IDC_CHECK_ENABLE_PRIV));
	m_chkStripSuffix.Attach(GetDlgItem(IDC_CHECK_STRIP_AW));
	m_chkUndecorateSymbols.Attach(GetDlgItem(IDC_CHECK_UNDECORATE));
	m_chkPauseWhileHooking.Attach(GetDlgItem(IDC_CHECK_PAUSE));
	m_chkAutoScroll.Attach(GetDlgItem(IDC_CHECK_AUTOSCROLL));
	m_chkShowStack.Attach(GetDlgItem(IDC_CHECK_SHOWSTACK));
	
	// Read dialog data from options storage
	COptionsStorage& optionsStorage = COptionsStorage::Instance();

	m_editDependsPath.SetWindowText(optionsStorage.GetDependsPath());

	m_chkEnablePriv.SetCheck(optionsStorage.GetEnableSeDebugPriv() ? BST_CHECKED : BST_UNCHECKED);
	m_chkStripSuffix.SetCheck(optionsStorage.GetStripSuffixForMsdn() ? BST_CHECKED : BST_UNCHECKED);
	m_chkUndecorateSymbols.SetCheck(optionsStorage.GetUndecorateSymbols() ? BST_CHECKED : BST_UNCHECKED);
	m_chkPauseWhileHooking.SetCheck(optionsStorage.GetPauseWhileHooking() ? BST_CHECKED : BST_UNCHECKED);
	m_chkAutoScroll.SetCheck(optionsStorage.GetAutoScroll() ? BST_CHECKED : BST_UNCHECKED);
	m_chkShowStack.SetCheck(optionsStorage.GetShowStack() ? BST_CHECKED : BST_UNCHECKED);

	return 1;
}

LRESULT COptionsDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID == IDOK)
	{
		// Write info back to options storage
		COptionsStorage& optionsStorage = COptionsStorage::Instance();

		TCHAR szBuf[512] = {0};
		m_editDependsPath.GetWindowText(szBuf, lengthof(szBuf));
		optionsStorage.SetDependsPath(szBuf);

		optionsStorage.SetEnableSeDebugPriv(m_chkEnablePriv.GetCheck() == BST_CHECKED ? TRUE : FALSE);
		optionsStorage.SetStripSuffixForMsdn(m_chkStripSuffix.GetCheck() == BST_CHECKED ? TRUE : FALSE);
		optionsStorage.SetUndecorateSymbols(m_chkUndecorateSymbols.GetCheck() == BST_CHECKED ? TRUE : FALSE);
		optionsStorage.SetPauseWhileHooking(m_chkPauseWhileHooking.GetCheck() == BST_CHECKED ? TRUE : FALSE);
		optionsStorage.SetAutoScroll(m_chkAutoScroll.GetCheck() == BST_CHECKED ? TRUE : FALSE);
		optionsStorage.SetShowStack(m_chkShowStack.GetCheck() == BST_CHECKED ? TRUE : FALSE);

		optionsStorage.SaveOptions();
	}

	EndDialog(wID);
	return 0;
}

LRESULT COptionsDlg::OnBrowseForDepends(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString strPath;
	if(BrowseForFile(_T("depends.exe"), strPath))
	{
		m_editDependsPath.SetWindowText(strPath);
	}

	return 0;
}

BOOL COptionsDlg::BrowseForFile(LPCTSTR pszFilename, CString& rstrFilePath)
{
	CString strTitle = _T("Browse for ");
	strTitle += pszFilename;

	TCHAR szFilter[258] = {0};
	_tcscpy(szFilter, pszFilename);

	TCHAR szFilePath[1024] = {0};

	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFilter = szFilter;
	ofn.lpstrTitle = strTitle;
	ofn.Flags = OFN_ENABLESIZING | OFN_LONGNAMES | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = _T("exe");
	ofn.lpstrFile = szFilePath;
	ofn.nMaxFile = lengthof(szFilePath);
	
	if(GetOpenFileName(&ofn))
	{
		rstrFilePath = szFilePath;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}