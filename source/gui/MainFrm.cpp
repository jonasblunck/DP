#include "stdafx.h"

#include "DP.h"

#include "MainFrm.h"
#include "AboutDlg.h"
#include "FindDlg.h"
#include "HookedDlg.h"
#include "OptionsDlg.h"

#include "ItemData.h"
#include "ChainHookAPI.h"
#include "HookManager.h"
#include "HookedStructures.h"
#include "ExportedItemFinder.h"
#include "TraceSink.h"

// CLSID for OleView
struct __declspec(uuid("57EFBF49-4A8B-11CE-870B-0800368D2302")) OleViewImpl;

CMainFrame::CMainFrame() 
{
  m_hInfiltratedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
  m_pTraceSink = new CTraceSink;
}

CMainFrame& CMainFrame::Instance()
{
  static CMainFrame instance;
  return instance;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
  if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
  {
    return TRUE;
  }

  return FALSE;
}

BOOL CMainFrame::OnIdle()
{
  BOOL bEnableModuleMenus = FALSE;
  BOOL bEnableModuleHookMenus = FALSE;
  DWORD dwSelectedPID = 0;

  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  if(tiSelected != NULL)
  {
    TreeItemData* pModule = (TreeItemData*)tiSelected.GetData();
    if(pModule)
    {
      dwSelectedPID = pModule->GetPID();
      bEnableModuleMenus = (pModule->GetNodeType() > NODETYPE_PROCESSES);
      bEnableModuleHookMenus = (pModule->GetNodeType() == NODETYPE_DLL);
    }
  }

  // Decide whether OleView and Depends are available
  BOOL bDependsAvailable = bEnableModuleMenus && IsDependsAvailable();
  BOOL bOleViewAvailable = bEnableModuleMenus && IsOleViewAvailable();

  // All module menus
  UIEnable(ID_EDIT_FIND, bEnableModuleMenus);
  UIEnable(ID_MODULE_VIEWDEPENDS, bDependsAvailable);
  UIEnable(ID_MODULE_VIEWTYPELIB, bOleViewAvailable);
  UIEnable(ID_MODULE_PROPERTIES, bEnableModuleMenus);
  UIEnable(ID_MODULE_PAUSE, bEnableModuleMenus);

  UIEnable(ID_MODULE_HOOK_ALL, bEnableModuleHookMenus);
  UIEnable(ID_MODULE_UNHOOK_ALL, bEnableModuleHookMenus);

  // Stuff to enable/disable if hooked
  if(dwSelectedPID != 0)
  {
    BOOL bProcessIsHooked = CHookManager::Instance().ExistsHookedProcess(dwSelectedPID);
    UIEnable(ID_MODULE_PAUSE, bProcessIsHooked);
    UIEnable(ID_MODULE_UNHOOK_ALL, (bEnableModuleHookMenus && bProcessIsHooked));
  }

  // Search-related export menus
  BOOL bEnableSearches = (m_ExportView.GetSelectedCount() == 1);
  UIEnable(ID_FUNCTION_SEARCH_MSDN, bEnableSearches);
  UIEnable(ID_FUNCTION_SEARCH_GOOGLE, bEnableSearches);
  UIEnable(ID_SEARCH_PARAMS, bEnableSearches);

  // Hook-related export menus
  BOOL bEnableExportHook = (m_ExportView.GetSelectedCount() > 0) || (m_findResultsView.GetSelectedCount() > 0);
  UIEnable(ID_FUNCTION_HOOK, bEnableExportHook);
  UIEnable(ID_FUNCTION_UNHOOK, bEnableExportHook);

  // Trace menus
  UIEnable(ID_TRACE_UNHOOK, (m_TraceView.GetSelectedCount() > 0));
  UIEnable(ID_TRACE_LOCATE, (m_TraceView.GetSelectedCount() == 1));
  UIEnable(ID_TRACE_PAUSE, (m_TraceView.GetSelectedCount() == 1));

  if(m_TraceView.GetSelectedCount() == 1)
  {
    // Enable if selected process is hooked
    DWORD dwPID, dwRVA;
    CString strModule, strFunction;
    m_TraceView.GetTraceData(m_TraceView.GetNextItem(-1, LVNI_SELECTED), dwPID, strModule, dwRVA, strFunction);

    BOOL bProcessIsHooked = CHookManager::Instance().ExistsHookedProcess(dwSelectedPID);

    UIEnable(ID_TRACE_PAUSE, bProcessIsHooked);
    UIEnable(ID_TRACE_UNHOOK, bProcessIsHooked);
  }

  // Other
  UISetCheck(ID_VIEW_TOGGLE_PATH, m_ProcessTree.IsPathShown());
  UIEnable(ID_FILE_SAVE, m_TraceView.IsDirty());
  UIEnable(ID_FILE_SAVE_AS, m_TraceView.IsDirty());

  UIUpdateToolBar();

  return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
/// Message handlers
LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  CenterWindow();

  // Create toolbar
  HWND hWndCmdBar = m_cmdBar.Create(m_hWnd, rcDefault, 0, ATL_SIMPLE_CMDBAR_PANE_STYLE);
  m_cmdBar.AttachMenu(GetMenu());
  m_cmdBar.LoadImages(IDR_MAINFRAME);
  SetMenu(0);

  HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

  CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
  AddSimpleReBarBand(hWndCmdBar);
  AddSimpleReBarBand(hWndToolBar, 0, TRUE);

  // Setup status bar
  CreateSimpleStatusBar();

  // Create splitter windows
  CRect rc;
  GetClientRect(rc);

  m_hWndClient = m_HorizontalSplitter.Create(m_hWnd, rcDefault, 0, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
  if (!m_HorizontalSplitter.IsWindow()) return -1;

  m_VerticalSplitter.Create(m_HorizontalSplitter, rcDefault, 0, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
  if (!m_VerticalSplitter.IsWindow()) return -1;

  m_VerticalSplitter.SetSplitterRect(rc);
  m_VerticalSplitter.SetSplitterPos();

  m_HorizontalSplitter.SetSplitterRect(rc);
  m_HorizontalSplitter.SetSplitterPos();

  // Create views
  m_ProcessTree.Create(m_VerticalSplitter, rcDefault);
  if (!m_ProcessTree.IsWindow()) return -1;

  m_ExportView.Create(m_VerticalSplitter, rcDefault);
  if (!m_ExportView.IsWindow()) return -1;

  m_tabView.Create(m_HorizontalSplitter, rcDefault);
  if (!m_tabView.IsWindow()) return -1;

  m_findResultsView.Create(m_tabView);
  if (!m_findResultsView.IsWindow()) return -1;

  m_TraceView.Create(m_tabView); // , rcDefault, NULL, WS_CHILD|LVS_REPORT);
  if (!m_TraceView.IsWindow()) return -1;

  m_tabView.InsertPage(0, m_TraceView.m_hWnd, "Output");
  m_tabView.InsertPage(1, m_findResultsView.m_hWnd, "Find Results");
  m_tabView.SetActivePage(0);

  // Split the panes
  m_VerticalSplitter.SetSplitterPanes(m_ProcessTree, m_ExportView);
  m_HorizontalSplitter.SetSplitterPanes(m_VerticalSplitter, m_tabView);

  UIAddToolBar(hWndToolBar);
  UIAddMenuBar(hWndCmdBar);

  UISetCheck(ID_VIEW_STATUS_BAR, 1);

  // register object for message filtering and idle updates
  CMessageLoop* pLoop = _Module.GetMessageLoop();
  ATLASSERT(pLoop != NULL);
  pLoop->AddMessageFilter(this);
  pLoop->AddIdleHandler(this);

  if(m_pTraceSink == NULL)
  {
    ReportError(_T("Failed to construct trace sink. DP cannot start."));
    PostQuitMessage(1);
  }
  else
  {
    m_pTraceSink->Start();
  }

  return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  HRESULT hr;

  if(m_pTraceSink)
  {
    m_pTraceSink->Stop();
    delete m_pTraceSink;
  }

  // Release all infiltrators
  hr = ClearInfiltrators();
  ATLASSERT(SUCCEEDED(hr));

  // unregister message filtering and idle updates
  CMessageLoop* pLoop = _Module.GetMessageLoop();
  ATLASSERT(pLoop != NULL);
  pLoop->RemoveMessageFilter(this);
  pLoop->RemoveIdleHandler(this);

  // if UI is the last thread, no need to wait
  if(_Module.GetLockCount() == 1)
  {
    _Module.m_dwTimeOut = 0L;
    _Module.m_dwPause = 0L;
  }

  _Module.Unlock();

  return 0;
}

LRESULT CMainFrame::OnProcessViewSelChanged(int, LPNMHDR, BOOL&)
{
  // Visual feedback that we're working
  CWaitCursor wc;

  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  TreeItemData* pItemData = (TreeItemData*)tiSelected.GetData();
  if(pItemData)
  {

    if(pItemData->GetNodeType() == NODETYPE_PROCESS)
    {
      if(!tiSelected.HasChildren())
      {
        m_runningProcesses.EnumerateModules(pItemData->GetPID(), &m_ProcessTree, (void*)tiSelected.m_hTreeItem, COptionsStorage::Instance().GetEnableSeDebugPriv());
      }

      tiSelected.Expand(TVE_EXPAND);
    }

    // load exports and symbols
    m_ExportView.Reload(pItemData->GetPID(), pItemData->GetPath());

    //}
    //  else if(pItemData->GetNodeType() == NODETYPE_DEBUGSYM)
    //  {
    //    if(!tiSelected.HasChildren())
    //    {
    //      m_ExportView.ReloadSymbols(pItemData->GetPID(), pItemData->GetPath());
    //    }

    //    tiSelected.Expand(TVE_EXPAND);
    //  }
    //else if(pItemData->GetNodeType() == NODETYPE_DLL)
    //{
    //	// Notify Exports view to reload itself
    //	m_ExportView.ReloadExports(pItemData->GetPID(), pItemData->GetPath());
    //}
  }

  return 0;
}

LRESULT CMainFrame::OnContextMenu(int, LPNMHDR pnmh, BOOL&)
{
  POINT ptClicked = {LOWORD(::GetMessagePos()), HIWORD(::GetMessagePos())};

  if(pnmh->hwndFrom == m_findResultsView.m_hWnd)
  {
    m_findResultsView.ScreenToClient(&ptClicked);

    // Only show the menu if we're on an item
    LVHITTESTINFO lvhtti = { { ptClicked.x, ptClicked.y } };
    int nSelectedItem = m_findResultsView.HitTest(&lvhtti);
    if(nSelectedItem != -1)
    {
      m_findResultsView.SetItemState(nSelectedItem, LVIS_SELECTED, LVIS_SELECTED);
      OnIdle();

      // Popup the menu
      POINT ptCursor;
      GetCursorPos(&ptCursor);

      CMenu popupMenu;
      popupMenu.LoadMenu(IDR_POPUP_FINDVIEW);
      CMenuHandle menu = popupMenu.GetSubMenu(0);

      menu.TrackPopupMenu(TPM_LEFTALIGN/*| TPM_NONOTIFY | TPM_RETURNCMD*/, ptCursor.x, ptCursor.y, m_hWnd);
    }

  }
  else if(pnmh->hwndFrom == m_ExportView.m_hWnd)
  {
    // Map the clicked pixel to listview's client area
    m_ExportView.ScreenToClient(&ptClicked);

    // Only show the menu if we're on an item
    LVHITTESTINFO lvhtti = { { ptClicked.x, ptClicked.y } };
    int nSelectedItem = m_ExportView.HitTest(&lvhtti);
    if(nSelectedItem != -1)
    {
      // Make sure item is selected, and menu state is set correctly
      m_ExportView.SetItemState(nSelectedItem, LVIS_SELECTED, LVIS_SELECTED);
      OnIdle();

      // Popup the menu
      POINT ptCursor;
      GetCursorPos(&ptCursor);

      CMenu popupMenu;
      popupMenu.LoadMenu(IDR_POPUP_EXPORTS);
      CMenuHandle menu = popupMenu.GetSubMenu(0);

      menu.TrackPopupMenu(TPM_LEFTALIGN, ptCursor.x, ptCursor.y, m_hWnd);
    }
  }
  else if(pnmh->hwndFrom == m_ProcessTree.m_hWnd)
  {
    // Map the clicked pixel to treeview's client area
    m_ProcessTree.ScreenToClient(&ptClicked);

    // Only show the menu if we're on an item
    TVHITTESTINFO tvhtti = { { ptClicked.x, ptClicked.y } };
    CTreeItem tiClicked = m_ProcessTree.HitTest(&tvhtti);
    if(tiClicked != NULL)
    {
      // Make sure item is selected and menu state is set correctly
      tiClicked.Select();
      OnIdle();

      // Popup the menu
      POINT ptCursor;
      GetCursorPos(&ptCursor);

      CMenu popupMenu;
      popupMenu.LoadMenu(IDR_POPUP_MODULES);
      popupMenu.GetSubMenu(0).TrackPopupMenu(TPM_LEFTALIGN, ptCursor.x, ptCursor.y, m_hWnd);
    }
  }
  else if(pnmh->hwndFrom == m_TraceView.m_hWnd)
  {
    // Map the clicked pixel to listview's client area
    m_TraceView.ScreenToClient(&ptClicked);

    // Only show the menu if we're on an item
    LVHITTESTINFO lvhtti = { { ptClicked.x, ptClicked.y } };
    int nSelectedItem = m_TraceView.HitTest(&lvhtti);
    if(nSelectedItem != -1)
    {
      // Make sure item is selected, and menu state is set correctly
      m_TraceView.SetItemState(nSelectedItem, LVIS_SELECTED, LVIS_SELECTED);
      OnIdle();

      // Popup the menu
      POINT ptCursor;
      GetCursorPos(&ptCursor);

      CMenu popupMenu;
      popupMenu.LoadMenu(IDR_POPUP_TRACE);
      CMenuHandle menu = popupMenu.GetSubMenu(0);

      menu.TrackPopupMenu(TPM_LEFTALIGN, ptCursor.x, ptCursor.y, m_hWnd);
    }
  }

  return 0;
}

LRESULT CMainFrame::OnDblClick(int, LPNMHDR pnmh, BOOL&)
{
  POINT ptClicked = {LOWORD(::GetMessagePos()), HIWORD(::GetMessagePos())};

  if(pnmh->hwndFrom == m_ExportView.m_hWnd)
  {
    // Map the clicked pixel to listview's client area
    m_ExportView.ScreenToClient(&ptClicked);

    // Only show the menu if we're on an item
    LVHITTESTINFO lvhtti = { { ptClicked.x, ptClicked.y } };
    int nSelectedItem = m_ExportView.HitTest(&lvhtti);
    if(nSelectedItem != -1)
    {
      HRESULT hr;

      // First of all, make sure the process is infiltrated
      DWORD dwPID = m_ExportView.GetCurrentPID();
      hr = Infiltrate(dwPID);
      if(FAILED(hr)) return 0;

      SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);
      ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);

      // Suspend trace
      if(COptionsStorage::Instance().GetPauseWhileHooking())
      {
        hr = pProcess->SuspendTrace();
        if(FAILED(hr))
        {
          ReportError(_T("Failed to suspend trace - continuing with trace running (0x%X)"), hr);
        }
      }

      SmartRefPtr<HookedFunction> function = pProcess->IsFunctionHooked(m_ExportView.GetCurrentModulePath(), pExport->GetRVA());

      if(function.GetPointer() != NULL)
      {
        // Function is hooked, so unhook
        hr = pProcess->UnhookFunction(function->GetHookID());
        if(SUCCEEDED(hr))
        {
          m_TraceView.OnUnhook(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName());
          m_ExportView.SetItemHooked(nSelectedItem, FALSE);
        }
        else
        {
          TraceMessage(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName(), _T("Failed to unhook function (0x%X)"), hr);
        }
      }
      else
      {
        // Function isn't hooked, so hook
        hr = pProcess->HookFunction(m_ExportView.GetCurrentModulePath(),
          pExport->GetRVA(), pExport->GetName(), pExport->GetParameters());
        if(SUCCEEDED(hr))
        {
          m_TraceView.OnHook(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName());
          m_ExportView.SetItemHooked(nSelectedItem, TRUE);
        }
        else
        {
          TraceMessage(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName(), _T("Failed to hook (0x%X)"), hr);
        }
      }

      // Resume trace
      if(COptionsStorage::Instance().GetPauseWhileHooking())
      {
        hr = pProcess->ResumeTrace();
        if(FAILED(hr))
        {
          ReportError(_T("Failed to resume trace (0x%X)"), hr);
        }
      }
    }
  }

  return 0;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  PostMessage(WM_CLOSE);

  return 0;
}

LRESULT CMainFrame::OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  if(m_TraceView.IsDirty())
  {
    if(m_strFilename.GetLength() == 0)
    {
      return OnFileSaveAs(wNotifyCode, wID, hWndCtl, bHandled);
    }

    if(!m_TraceView.SaveToFile((LPCTSTR)m_strFilename))
    {
      ReportError(_T("Failed to save trace output to file %s (0x%X)"), m_strFilename, GetLastError());
    }
  }

  return 0;
}

LRESULT CMainFrame::OnFileSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  if(m_TraceView.IsDirty())
  {
    TCHAR szFilePath[1024] = {0};

    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hWnd;
    ofn.lpstrFilter = _T("*.txt\0\0");
    ofn.lpstrTitle = _T("Save trace output");
    ofn.Flags = OFN_ENABLESIZING | OFN_LONGNAMES | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = _T("txt");
    ofn.lpstrFile = szFilePath;
    ofn.nMaxFile = lengthof(szFilePath);

    if(GetSaveFileName(&ofn))
    {
      m_strFilename = ofn.lpstrFile;
      return OnFileSave(wNotifyCode, wID, hWndCtl, bHandled);
    }
  }

  return 0;
}

LRESULT CMainFrame::OnEditHooks(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CHookedDlg().DoModal();
  return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
  ::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
  UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
  UpdateLayout();

  return 0;
}

LRESULT CMainFrame::OnViewTogglePath(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  m_ProcessTree.TogglePath();

  return 0;
}

LRESULT CMainFrame::OnViewRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  m_ProcessTree.OnRefresh();
  m_ExportView.OnRefresh();

  CHookManager::Instance().RemoveAllDeadProcesses();

  return 0;
}

LRESULT CMainFrame::OnHelpHelp(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  // Get current path
  TCHAR szCurrentPath[MAX_PATH] = {0};
  if(!::GetModuleFileName(NULL, szCurrentPath, lengthof(szCurrentPath)))
  {
    return 0;
  }

  // Strip off filename part
  LPTSTR p = szCurrentPath + lstrlen(szCurrentPath) - 1;
  while(p > szCurrentPath)
  {
    if(*p == _T('\\') || *p == _T('/'))
    {
      p[1] = 0;
      break;
    }

    --p;
  }

  // Append 'help\index.htm' and spawn the resulting path
  lstrcat(szCurrentPath, _T("help\\index.htm"));
  Spawn(szCurrentPath);

  return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CAboutDlg().DoModal();
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
/// Popup menu handlers
LRESULT CMainFrame::OnEditOptions(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  COptionsDlg dlg;
  dlg.DoModal();

  return 0;
}


LRESULT CMainFrame::OnFunctionHook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  DWORD dwPID = m_ExportView.GetCurrentPID();

  if(FAILED(Infiltrate(dwPID))) return 0;

  // All functions are within the same process
  SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);

  int nSelectedItem = m_ExportView.GetNextItem(-1, LVNI_SELECTED);
  while(nSelectedItem != -1)
  {
    ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);
    HRESULT hr = pProcess->HookFunction(m_ExportView.GetCurrentModulePath(),
      pExport->GetRVA(), pExport->GetName(), pExport->GetParameters());

    if(SUCCEEDED(hr))
    {
      m_TraceView.OnHook(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName());
      m_ExportView.SetItemHooked(nSelectedItem, TRUE);
    }
    else
    {
      TraceMessage(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName(), _T("Failed to hook!)"));
    }

    nSelectedItem = m_ExportView.GetNextItem(nSelectedItem, LVNI_SELECTED);
  }		

  // hook based on find results view
  nSelectedItem = m_findResultsView.GetNextItem(-1, LVNI_SELECTED);
  while(nSelectedItem != -1)
  {
    ExportItemData* pExport = (ExportItemData*)m_findResultsView.GetItemData(nSelectedItem);
    HRESULT hr = pProcess->HookFunction(m_ExportView.GetCurrentModulePath(),
      pExport->GetRVA(), pExport->GetName(), pExport->GetParameters());

    if (SUCCEEDED(hr))
      m_TraceView.OnHook(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName());

    nSelectedItem = m_findResultsView.GetNextItem(nSelectedItem, LVNI_SELECTED);
  }		


  m_tabView.SetActivePage(0); // TODO:: 0/1 should be enums for enOutputView, enFindResultsView
  return 0;
}

LRESULT CMainFrame::OnFunctionUnhook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  DWORD dwPID = m_ExportView.GetCurrentPID();

  // Get the process
  SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);

  // Unhook selected functions
  int nSelectedItem = m_ExportView.GetNextItem(-1, LVNI_SELECTED);
  while(nSelectedItem != -1)
  {
    ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);
    SmartRefPtr<HookedFunction> function = pProcess->IsFunctionHooked(m_ExportView.GetCurrentModulePath(), pExport->GetRVA());

    if(function.GetPointer() != NULL)
    {
      pProcess->UnhookFunction(function->GetHookID());
      m_TraceView.OnUnhook(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName());
      m_ExportView.SetItemHooked(nSelectedItem, FALSE);
    }
    else
    {
      TraceMessage(dwPID, m_ExportView.GetCurrentModulePath(), pExport->GetRVA(), pExport->GetName(), _T("Failed to unhook function!"));
    }

    nSelectedItem = m_ExportView.GetNextItem(nSelectedItem, LVNI_SELECTED);
  }

  return 0;
}

LRESULT CMainFrame::OnFunctionSearchMSDNParams(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  int nSelectedItem = m_ExportView.GetNextItem(-1, LVNI_SELECTED);
  while(nSelectedItem != -1)
  {
    ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);
    CString url;

    //if (MsdnScraper::FindMsdnURL(pExport->GetName(), url))
    //{
    //  CString parameters;

    //  if (MsdnScraper::FindParameters(pExport->GetName(), url, parameters))
    //  {
    //    MessageBox(NULL, (LPCTSTR)parameters, "Worked!", MB_OK);

    //  }
    //}

    nSelectedItem = m_ExportView.GetNextItem(nSelectedItem, LVNI_SELECTED);
  }

  return 0;
}

LRESULT CMainFrame::OnFunctionSearchMSDN(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  if(m_ExportView.GetSelectedCount() == 1)
  {
    // Get selected function name
    int nSelectedItem = m_ExportView.GetNextItem(-1, LVNI_SELECTED);
    ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);

    TCHAR szFunction[256] = {0};
    _tcscpy(szFunction, pExport->GetName());

    if(COptionsStorage::Instance().GetStripSuffixForMsdn())
    {
      // Strip A/W suffix before searching MSDN
      int nLastChar = _tcslen(szFunction) - 1;
      if(szFunction[nLastChar] == _T('W') || szFunction[nLastChar] == _T('A'))
      {
        szFunction[nLastChar] = 0;
      }
    }

    // Build an URL
    CString strUrl;
    strUrl.Format(_T("http://www.google.com/search?q=%s+site:msdn.microsoft.com"), szFunction);

    // Spawn the URL to bring up default browser
    Spawn(strUrl);
  }

  return 0;
}

LRESULT CMainFrame::OnFunctionSearchGoogle(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  if(m_ExportView.GetSelectedCount() == 1)
  {
    // Get selected function name
    int nSelectedItem = m_ExportView.GetNextItem(-1, LVNI_SELECTED);
    ExportItemData* pExport = (ExportItemData*)m_ExportView.GetItemData(nSelectedItem);

    TCHAR szFunction[256] = {0};
    _tcscpy(szFunction, pExport->GetName());

    if(COptionsStorage::Instance().GetStripSuffixForMsdn())
    {
      // Strip A/W suffix before searching MSDN
      int nLastChar = _tcslen(szFunction) - 1;
      if(szFunction[nLastChar] == _T('W') || szFunction[nLastChar] == _T('A'))
      {
        szFunction[nLastChar] = 0;
      }
    }

    // Build an URL
    CString strUrl;
    strUrl.Format(_T("http://www.google.com/search?q=%s"), szFunction);

    // Spawn the URL to bring up default browser
    Spawn(strUrl);
  }

  return 0;
}
LRESULT CMainFrame::OnEditFind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CFindDlg dlg;
  if(dlg.DoModal() != IDCANCEL)
  {
    CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
    TreeItemData* ptid = (TreeItemData*)tiSelected.GetData();

    m_findResultsView.DeleteAllItems();

    // search current selected item
    m_ExportView.FindItems(dlg.GetSearchString(), dlg.GetMatchWholeWordOnly(), &m_findResultsView);

    // if we have selected the process, select all sub modules
    if (ptid->GetNodeType() == NODETYPE_PROCESS)
    {
      ExportedItemFinder finder(dlg.GetSearchString(), dlg.GetMatchWholeWordOnly(), &m_findResultsView);

      // search each module
      for(CTreeItem tiChild = m_ProcessTree.GetChildItem(tiSelected); tiChild != NULL; tiChild = m_ProcessTree.GetNextSiblingItem(tiChild))
      {
        TreeItemData* pChildData = (TreeItemData*)tiChild.GetData();
        finder.Search(pChildData->GetPID(), pChildData->GetPath());
      }
    }

  }

  m_tabView.SetActivePage(1);

  return 0;
}

LRESULT CMainFrame::OnModuleViewTypeLib(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  if(tiSelected != NULL)
  {
    TreeItemData* pModule = (TreeItemData*)tiSelected.GetData();

    CComPtr<ITypeLib> spTypeLib;
    HRESULT hr = LoadTypeLib(CComBSTR(pModule->GetPath()), &spTypeLib);
    if (SUCCEEDED(hr))
    {
      CComPtr<ITypeLibViewer> spTypeLibViewer;
      hr = spTypeLibViewer.CoCreateInstance(__uuidof(OleViewImpl));
      if(SUCCEEDED(hr))
      {
        spTypeLibViewer->View(m_hWnd, __uuidof(spTypeLib), spTypeLib); 
      }
    }
    else
    {
      ReportError(_T("Failed to load type library for %s. (0x%X)"), pModule->GetName(), hr);
    }
  }

  return 0;
}

LRESULT CMainFrame::OnModuleViewDepends(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  if(tiSelected != NULL)
  {
    TreeItemData* pModule = (TreeItemData*)tiSelected.GetData();
    if(pModule != NULL)
    {
      // Spawn Depends.exe
      CString strPath = COptionsStorage::Instance().GetDependsPath();
      if(strPath.GetLength() == 0)
      {
        strPath = _T("depends.exe");
      }

      Spawn(strPath, pModule->GetPath());
    }
  }

  return 0;
}

LRESULT CMainFrame::OnModuleProperties(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  if(tiSelected != NULL)
  {
    TreeItemData* pModule = (TreeItemData*)tiSelected.GetData();
    if(pModule != NULL)
    {
      CString strQuotedPath;
      strQuotedPath.Format(_T("\"%s\""), pModule->GetPath());

      SHELLEXECUTEINFO sei = {sizeof(SHELLEXECUTEINFO)};
      sei.lpVerb = _T("properties");
      sei.lpFile = strQuotedPath;
      sei.fMask = SEE_MASK_INVOKEIDLIST;

      ShellExecuteEx(&sei);
    }
  }

  return 0;
}

LRESULT CMainFrame::OnModulePause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  HRESULT hr;

  CTreeItem tiSelected = m_ProcessTree.GetSelectedItem();
  if(tiSelected != NULL)
  {
    TreeItemData* pModule = (TreeItemData*)tiSelected.GetData();
    if(pModule != NULL)
    {
      // Get the process
      SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(pModule->GetPID());
      if(pProcess != NULL)
      {
        // Toggle trace pause
        CString strMessage;

        BOOL bIsPaused = FALSE;
        hr = pProcess->ToggleTrace(&bIsPaused);
        if(SUCCEEDED(hr))
        {
          strMessage.Format(_T("Trace %s"), bIsPaused ? _T("paused") : _T("resumed"));
        }
        else
        {
          strMessage.Format(_T("Failed to toggle pause for trace (0x%X)"), hr);
        }

        TraceMessage(pModule->GetPID(), _T(""), 0, _T(""), strMessage);
      }
    }
  }

  return 0;
}

LRESULT CMainFrame::OnTraceCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  m_TraceView.CopyToClipboard();
  return 0;
}

LRESULT CMainFrame::OnTraceSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  for(int n = 0; n < m_TraceView.GetItemCount(); ++n)
  {
    m_TraceView.SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
  }

  return 0;
}

LRESULT CMainFrame::OnTraceClear(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  m_TraceView.DeleteAllItems();
  return 0;
}

LRESULT CMainFrame::OnTraceLocate(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  //if(m_TraceView.GetSelectedCount() == 1)
  //{
  //	// Get trace data
  //	DWORD dwPID, dwRVA;
  //	CString strModule, strFunction;
  //	if(m_TraceView.GetTraceData(m_TraceView.GetNextItem(-1, LVNI_SELECTED), dwPID, strModule, dwRVA, strFunction))
  //	{
  //		// See if we can find this item (PID-Module pair) in the tree
  //		CTreeItem ti = m_ProcessTree.FindItem(dwPID, strModule);
  //		if(ti != NULL)
  //		{
  //			// If so, select it, so the export view reloads
  //			m_ProcessTree.EnsureVisible(ti);
  //			m_ProcessTree.SelectItem(ti);

  //			// Find the function in export view, and select it
  //			int nItem = m_ExportView.FindItem(dwRVA);
  //			if(nItem != -1)
  //			{
  //				m_ExportView.FocusSingleItem(nItem);
  //				m_ExportView.SetFocus();
  //			}
  //		}
  //	}
  //}

  return 0;
}

LRESULT CMainFrame::OnTraceUnhook(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  BOOL bUnhookedSomething = FALSE;

  // Loop through all selected items
  for(int nItem = m_TraceView.GetNextItem(-1, LVNI_SELECTED); nItem != -1; nItem = m_TraceView.GetNextItem(nItem, LVNI_SELECTED))
  {
    DWORD dwPID, dwRVA;
    CString strModule, strFunction;
    if(m_TraceView.GetTraceData(nItem, dwPID, strModule, dwRVA, strFunction))
    {
      // Get the process
      SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);
      if(pProcess != NULL)
      {
        // Unhook function
        SmartRefPtr<HookedFunction> function = pProcess->IsFunctionHooked(strModule, dwRVA);

        if (function.GetPointer() != NULL)
        {
          pProcess->UnhookFunction(function->GetHookID());
          bUnhookedSomething = m_TraceView.OnUnhook(dwPID, strModule, dwRVA, strFunction);
        }
        else
        {
          TraceMessage(dwPID, strModule, dwRVA, strFunction, _T("Failed to unhook function!"));
        }
      }
    }
  }

  if(bUnhookedSomething)
  {
    m_ExportView.OnRefresh();
  }

  return 0;
}

LRESULT CMainFrame::OnTracePause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  HRESULT hr;

  // Loop through all selected items
  if(m_TraceView.GetSelectedCount() == 1)
  {
    DWORD dwPID, dwRVA;
    CString strModule, strFunction;
    if(m_TraceView.GetTraceData(m_TraceView.GetNextItem(-1, LVNI_SELECTED), dwPID, strModule, dwRVA, strFunction))
    {
      // Get the process
      SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);
      if(pProcess != NULL)
      {
        // Pause trace
        BOOL bIsPaused = FALSE;
        hr = pProcess->ToggleTrace(&bIsPaused);
        if(SUCCEEDED(hr))
        {
          if(bIsPaused)
          {
            TraceMessage(dwPID, _T(""), 0, _T(""), _T("Trace paused"));
          }
          else
          {
            TraceMessage(dwPID, _T(""), 0, _T(""), _T("Trace resumed"));
          }
        }
        else
        {
          if(bIsPaused)
          {
            TraceMessage(dwPID, _T(""), 0, _T(""), _T("Failed to pause trace (0x%X)"), hr);
          }
          else
          {
            TraceMessage(dwPID, _T(""), 0, _T(""), _T("Failed to resume trace (0x%X)"), hr);
          }
        }
      }
    }
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
/// Public interface

HRESULT CMainFrame::Infiltrate(DWORD dwPID)
{
  // Check if this PID is already infiltrated
  if(!CHookManager::Instance().ExistsHookedProcess(dwPID))
  {
    // get name of module to inject
    CString path;
    ::GetModuleFileName(_Module.GetModuleInstance(), path.GetBuffer(2056), 2055); path.ReleaseBuffer();
    path = path.Left(path.ReverseFind('\\'));

    if (path.Right(1) != '\\')
      path += '\\';

    path += "DPInfiltrator.dll";

    if (CHInjectDLL(dwPID, (LPCTSTR)path))
    {
      // Get the process name
      TCHAR szProcessName[MAX_PATH] = {0};
      m_runningProcesses.GetNameFromPID(dwPID, szProcessName, lengthof(szProcessName), COptionsStorage::Instance().GetEnableSeDebugPriv());
      _tcsupr(szProcessName);

      if(!CHookManager::Instance().ExistsHookedProcess(dwPID))
      {
        // Get path from PID
        TCHAR szProcessPath[MAX_PATH];
        m_runningProcesses.GetPathFromPID(dwPID, szProcessPath, lengthof(szProcessPath), COptionsStorage::Instance().GetEnableSeDebugPriv());

        if(!CHookManager::Instance().AddHookedProcess(dwPID, szProcessPath))
        {
          return E_OUTOFMEMORY;
        }
      }
    }
  }

  return S_OK;
}


HRESULT CMainFrame::ClearInfiltrators()
{
  CHookManager::Instance().RemoveAllHookedProcesses();
  return S_OK;
}

LRESULT CMainFrame::OnTrace(UINT, WPARAM wParam, LPARAM lParam, BOOL&)
{
  TraceItemData* pItemData = (TraceItemData*)wParam;

  DWORD dwPID = pItemData->GetPID();
  long lHookID = pItemData->GetHookID();

  SmartRefPtr<HookedProcess> pProcess = CHookManager::Instance().GetHookedProcess(dwPID);
  if(pProcess != NULL)
  {
    SmartRefPtr<HookedFunction> pFunction = pProcess->HookedFunctions[lHookID];
    if(pFunction != NULL)
    {
      m_TraceView.OnTraceCallback(dwPID, pFunction->GetModulePath(), pFunction->GetRVA(), pFunction->GetFunctionName(), pItemData->GetArgumentsTrace(), enTrace);
    }
    else if (pItemData->GetArgumentsTrace() != NULL)
    {
      m_TraceView.OnTraceCallback(dwPID, "", 0, "Unsolicited", pItemData->GetArgumentsTrace(), enTrace);
    }
    else
    {

#ifdef _DEBUG
      TraceMessage(dwPID, _T(""), 0, _T(""), _T("Trace callback for unknown function (PID: %ld HookID: %ld)"), dwPID, lHookID);
#endif
    }
  }
  else
  {
    if (pItemData->GetArgumentsTrace() != NULL)
    {
       m_TraceView.OnTraceCallback(dwPID, "", 0, "Unsolicited trace", pItemData->GetArgumentsTrace(), enTrace);
    }
#ifdef _DEBUG
    else
    {
      TraceMessage(dwPID, _T(""), 0, _T(""), _T("Trace callback for unknown process (PID: %ld)"), dwPID);
    }
#endif
  }

  delete pItemData;

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Private helpers
BOOL CMainFrame::Spawn(LPCTSTR pszFile, LPCTSTR pszParameters)
{
  // Quote parameters
  CString strQuotedParams;
  if(pszParameters)
  {
    strQuotedParams.Format(_T("\"%s\""), pszParameters);
  }

  // Shellexecute the file
  SHELLEXECUTEINFO sei = { sizeof(sei) };
  sei.lpVerb = _T("open");
  sei.lpFile = pszFile;
  sei.lpParameters = strQuotedParams;
  sei.nShow = SW_NORMAL;

  if(!ShellExecuteEx(&sei))
  {
    ReportError(_T("Failed to start %s (0x%X)"), pszFile, GetLastError());
    return FALSE;
  }

  return TRUE;
}

BOOL CMainFrame::LocateModuleExport(CTreeItem& tiModule, int nExportListItem)
{
  m_ProcessTree.EnsureVisible(tiModule);
  m_ProcessTree.SelectItem(tiModule);

  m_ExportView.FocusSingleItem(nExportListItem);
  m_ExportView.SetFocus();

  return TRUE;
}

void CMainFrame::ReportError(LPCTSTR pszMsg, ...)
{
  va_list arglist;
  va_start(arglist, pszMsg);

  TCHAR szBuf[512] = {0};
  _vsntprintf(szBuf, lengthof(szBuf), pszMsg, arglist);

  va_end(arglist);

  MessageBox(szBuf, ERROR_CAPTION, MB_ICONERROR);
}

void CMainFrame::TraceMessage(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR pszMsg, ...)
{
  va_list arglist;
  va_start(arglist, pszMsg);

  TCHAR szBuf[512] = {0};
  _vsntprintf(szBuf, lengthof(szBuf), pszMsg, arglist);

  va_end(arglist);

  m_TraceView.Trace(dwPID, pszModule, dwRVA, pszFunction, szBuf);
}

BOOL CMainFrame::IsOleViewAvailable()
{
  CComPtr<ITypeLibViewer> spTypeLibViewer;
  return (SUCCEEDED(spTypeLibViewer.CoCreateInstance(__uuidof(OleViewImpl))));
}

BOOL CMainFrame::IsDependsAvailable()
{
  CString strDependsPath = COptionsStorage::Instance().GetDependsPath();
  if(strDependsPath.IsEmpty())
  {
    strDependsPath = _T("depends.exe");
  }

  TCHAR szFilePath[MAX_PATH];
  _tcsncpy(szFilePath, strDependsPath, MAX_PATH);

  return PathFindOnPath(szFilePath, NULL);
}

CString CMainFrame::GetDefinitionsFilepath(LPCTSTR pszModule)
{
  // sanitize module
  CString strModule(pszModule);

  {
    int pos = strModule.ReverseFind('\\');

    if (-1 != pos)
      strModule = strModule.Mid(pos + 1);

    pos = strModule.Find('.');

    if (-1 != pos)
      strModule = strModule.Left(pos);
  }

  CString path;

  ::GetModuleFileName(_Module.GetModuleInstance(), path.GetBuffer(2056), 2055); path.ReleaseBuffer();

  path = path.Left(path.ReverseFind('\\'));

  if (path.Right(1) != '\\')
    path += '\\';

  path += "definitions\\";
  path += strModule;
  path += ".functions";

  return path;
}
