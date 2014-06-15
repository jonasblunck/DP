#include "stdafx.h"

#include "AboutDlg.h"

LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());

	SetIcon(LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME)));
	
	m_hlBlunck.SubclassWindow(GetDlgItem(IDC_HL_BLUNCK));
	m_hlBlunck.SetHyperLink(_T("http://www.blunck.info"));
	m_hlBlunck.SetLabel(_T("Jonas Blunck"));

	m_hlWinwonk.SubclassWindow(GetDlgItem(IDC_HL_WINWONK));
	m_hlWinwonk.SetHyperLink(_T("http://www.winwonk.com"));
	m_hlWinwonk.SetLabel(_T("Kim Gräsman"));

	LeftAlignHyperLinkLabel(m_hlBlunck);
	LeftAlignHyperLinkLabel(m_hlWinwonk);

	return 1;
}

LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

void CAboutDlg::LeftAlignHyperLinkLabel(CHyperLink& hl)
{
	CRect rLinkCtl;
	hl.GetClientRect(&rLinkCtl);

	CRect rLinkLabel(hl.m_rcLink);	
	rLinkLabel.OffsetRect(rLinkCtl.left - rLinkLabel.left, 0);
	
	CopyRect(&hl.m_rcLink, rLinkLabel);
}

/*
// We might need this sometime...
void CAboutDlg::CenterHyperLinkLabel(CHyperLink& hl)
{
	// Tim Tabor does it more or less like this, so it can't be all wrong
	CRect rLinkCtl;
	hl.GetClientRect(&rLinkCtl);

	CRect rLinkLabel(hl.m_rcLink);	
	rLinkLabel.OffsetRect((rLinkCtl.Width() - rLinkLabel.Width()) / 2 - rLinkLabel.left, 0);
	
	CopyRect(&hl.m_rcLink, rLinkLabel);
}
*/