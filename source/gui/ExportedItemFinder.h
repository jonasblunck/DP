#pragma once

#include "IFindOperationCallback.h"
#include "RunningProcesses.h"
#include "FunctionFile.h"

class ExportedItemFinder : public IEnumerateExportsCallback
{
  CString m_searchString;
  BOOL m_matchWholeWord;
  IFindOperationCallback* m_callback;
  CString2CStringMap m_functionParameters;

  virtual BOOL OnExport(LPCTSTR pszModulePath, DWORD dwOrdinal, DWORD dwRVA, 
      LPCTSTR pszFunctionName, void* pvContext, LPCTSTR pszParameters)
  {
    // check if match..
    CString strParamDefinition;
    CString2CStringMap::const_iterator t =
      m_functionParameters.find(CString(pszFunctionName));

    if (m_functionParameters.end() != t)
      strParamDefinition = t->second;

    if (m_matchWholeWord && m_searchString == pszFunctionName)
    {
      m_callback->OnItem(dwRVA, pszModulePath, pszFunctionName, strParamDefinition, "Export");
    }
    else if (CString(pszFunctionName).Find(m_searchString) != -1)
    {
      m_callback->OnItem(dwRVA, pszModulePath, pszFunctionName, strParamDefinition, "Export");
    }
    return TRUE;
  }

public:
  ExportedItemFinder(const CString& searchString, BOOL matchWholeWord,
    IFindOperationCallback* callback) : m_searchString(searchString), m_matchWholeWord(matchWholeWord),
      m_callback(callback)
  {
  }

  void Search(DWORD pid, LPCTSTR moduleToSearch)
  {
    // 
    // read parameters from definition file
    m_functionParameters.clear();
    FunctionFile::ReadFunctions(CMainFrame::GetDefinitionsFilepath(moduleToSearch), m_functionParameters);

    // 
    // enumerate exports
    CRunningProcesses processes;

    processes.EnumerateExports(moduleToSearch, static_cast<IEnumerateExportsCallback*>(this), 0, TRUE);
  }

};
