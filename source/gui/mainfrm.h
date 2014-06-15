// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E4E667B8_A8FD_4032_A595_A5187AB84592__INCLUDED_)
#define AFX_MAINFRM_H__E4E667B8_A8FD_4032_A595_A5187AB84592__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ProcessView.h"
#include "ExportView.h"
#include "TraceView.h"
#include "FindResultsView.h"

#include "HookedStructures.h"

class CTraceSink;

class CMainFrame : 
	public CFrameWindowImpl<CMainFrame>, 
	public CUpdateUI<CMainFrame>,
	public CMessageFilter, 
	public CIdleHandler
{
public:
	static CMainFrame& Instance();

	DECLARE_FRAME_WND_CLASS(_T("DPMainFrame"), IDR_MAINFRAME)

	CSplitterWindow		m_VerticalSplitter;
	CHorSplitterWindow	m_HorizontalSplitter;

	CProcessView m_ProcessTree;
	CExportView m_ExportView;
	CTraceView m_TraceView;
  CTabView m_tabView;
  CFindResultsView m_findResultsView;

	CCommandBarCtrl m_cmdBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_DP_TRACE_RECVD, OnTrace)

		NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnProcessViewSelChanged)
		NOTIFY_CODE_HANDLER(NM_RCLICK,		OnContextMenu)

		NOTIFY_CODE_HANDLER(NM_DBLCLK,		OnDblClick)
		
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_SAVE, OnFileSave)
		COMMAND_ID_HANDLER(ID_FILE_SAVE_AS, OnFileSaveAs)

		COMMAND_ID_HANDLER(ID_EDIT_FIND, OnEditFind)
		COMMAND_ID_HANDLER(ID_EDIT_HOOKS, OnEditHooks)
		COMMAND_ID_HANDLER(ID_EDIT_OPTIONS, OnEditOptions)

    COMMAND_ID_HANDLER(ID_SEARCH_PARAMS, OnFunctionSearchMSDNParams)
		COMMAND_ID_HANDLER(ID_FUNCTION_SEARCH_MSDN, OnFunctionSearchMSDN)
		COMMAND_ID_HANDLER(ID_FUNCTION_SEARCH_GOOGLE, OnFunctionSearchGoogle)
		COMMAND_ID_HANDLER(ID_FUNCTION_HOOK, OnFunctionHook)
		COMMAND_ID_HANDLER(ID_FUNCTION_UNHOOK, OnFunctionUnhook)

		COMMAND_ID_HANDLER(ID_HELP_HELP, OnHelpHelp)

		COMMAND_ID_HANDLER(ID_MODULE_VIEWTYPELIB, OnModuleViewTypeLib)
		COMMAND_ID_HANDLER(ID_MODULE_VIEWDEPENDS, OnModuleViewDepends)
		COMMAND_ID_HANDLER(ID_MODULE_PROPERTIES, OnModuleProperties)
		COMMAND_ID_HANDLER(ID_MODULE_PAUSE, OnModulePause)
		
		COMMAND_ID_HANDLER(ID_TRACE_COPY, OnTraceCopy)
		COMMAND_ID_HANDLER(ID_TRACE_SELECT_ALL, OnTraceSelectAll)
		COMMAND_ID_HANDLER(ID_TRACE_CLEAR, OnTraceClear)
		COMMAND_ID_HANDLER(ID_TRACE_LOCATE, OnTraceLocate)
		COMMAND_ID_HANDLER(ID_TRACE_UNHOOK, OnTraceUnhook)
		COMMAND_ID_HANDLER(ID_TRACE_PAUSE, OnTracePause)

		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_VIEW_TOGGLE_PATH, OnViewTogglePath)
		COMMAND_ID_HANDLER(ID_VIEW_REFRESH, OnViewRefresh)
	
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
		
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR,		UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_TOGGLE_PATH,		UPDUI_MENUPOPUP | UPDUI_TOOLBAR)

		UPDATE_ELEMENT(ID_EDIT_FIND,			UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_EDIT_FIND_NEXT,		UPDUI_MENUPOPUP | UPDUI_TOOLBAR)

		UPDATE_ELEMENT(ID_FILE_SAVE,			UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_FILE_SAVE_AS,			UPDUI_MENUPOPUP)

		UPDATE_ELEMENT(ID_MODULE_VIEWDEPENDS,	UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_MODULE_VIEWTYPELIB,	UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_MODULE_PROPERTIES,	UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_MODULE_HOOK_ALL,		UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_MODULE_UNHOOK_ALL,	UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_MODULE_PAUSE,			UPDUI_MENUPOPUP)

		UPDATE_ELEMENT(ID_FUNCTION_SEARCH_MSDN,		UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_FUNCTION_SEARCH_GOOGLE,	UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
		UPDATE_ELEMENT(ID_FUNCTION_HOOK,			UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_FUNCTION_UNHOOK,			UPDUI_MENUPOPUP)

		UPDATE_ELEMENT(ID_TRACE_LOCATE,			UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TRACE_UNHOOK,			UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_TRACE_PAUSE,			UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

	LRESULT OnTrace(UINT, WPARAM wParam, LPARAM lParam, BOOL&);

	LRESULT OnProcessViewSelChanged(int, LPNMHDR, BOOL&);
	LRESULT OnContextMenu(int, LPNMHDR pnmh, BOOL&);
	LRESULT OnDblClick(int, LPNMHDR pnmh, BOOL&);

	LRESULT OnFunctionHook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFunctionUnhook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFunctionSearchMSDN(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFunctionSearchGoogle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFunctionSearchMSDNParams(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnFileSave(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnTraceCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTraceSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTraceClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTraceLocate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTraceUnhook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTracePause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewTogglePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnModuleViewTypeLib(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnModuleViewDepends(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnModuleProperties(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnModulePause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnEditFind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditHooks(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnEditOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	
	LRESULT OnHelpHelp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

// Provides feedback opportunities
	void TraceMessage(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR pszMsg, ...);

  static CString GetDefinitionsFilepath(LPCTSTR pszModule);

private:
	CMainFrame(); // Disallow normal construction

	BOOL Spawn(LPCTSTR pszFile, LPCTSTR pszParameters = NULL);
	BOOL LocateModuleExport(CTreeItem& tiModule, int nExportListItem);
	BOOL IsOleViewAvailable();
	BOOL IsDependsAvailable();

	HRESULT ClearInfiltrators();
	HRESULT Infiltrate(DWORD dwPID);
	
	void ReportError(LPCTSTR pszMsg, ...);

	CRunningProcesses m_runningProcesses;
	SmartHandle m_hInfiltratedEvent;

	CString m_strFilename;
	CTraceSink* m_pTraceSink;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E4E667B8_A8FD_4032_A595_A5187AB84592__INCLUDED_)
