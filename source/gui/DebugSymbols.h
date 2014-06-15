#pragma once

#include "SymbolInfo.h"

class IEnumerateDebugSymbolsCallback
{
public:
  virtual BOOL OnSymbol(LPCTSTR pszSymbolName, DWORD dwOrdinal, 
    DWORD dwRVA, LPCTSTR pszParameters) = 0;
};


class CDebugSymbols
{
  HANDLE m_processHandle;

  static bool DoGetTypeId(CSymbolInfo& symbolInfo, DWORD index, CString& parameter);
  static BOOL __stdcall EnumSymbolsCallback(PSYMBOL_INFO syminfo, ULONG size, PVOID context);
  static bool FormatType(DWORD typeId, CString& type);

public:
  CDebugSymbols();
  ~CDebugSymbols();

  bool Initialize();
  void EnumerateSymbols(LPCTSTR pszModule, IEnumerateDebugSymbolsCallback* callback);
};