#include "stdafx.h"
#include "DebugSymbols.h"
#include "SymbolInfo.h"
#include "smarts.h"

#define MAX_STRING 2056

CDebugSymbols::CDebugSymbols()
{
  m_processHandle = 0; // could be anything really..
}

CDebugSymbols::~CDebugSymbols()
{
  SymCleanup(m_processHandle);
}

bool CDebugSymbols::Initialize()
{
  SymSetOptions(SYMOPT_CASE_INSENSITIVE | SYMOPT_LOAD_LINES | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS |
    SYMOPT_EXACT_SYMBOLS | SYMOPT_UNDNAME | SYMOPT_AUTO_PUBLICS);

  CString searchPath;

  DWORD len = 
    ::GetEnvironmentVariable(_T("_NT_SYMBOL_PATH"), searchPath.GetBuffer(MAX_STRING), MAX_STRING); searchPath.ReleaseBuffer();

  //if (!len)
  //  return false;

  if (!SymInitialize(m_processHandle, (LPCSTR)(LPCTSTR)searchPath, FALSE))
    return false;

  return true;
}

bool CDebugSymbols::FormatType(DWORD typeId, CString& type)
{
  enum BasicType
  {
    btNoType = 0,
    btVoid = 1,
    btChar = 2,
    btWChar = 3,
    btInt = 6,
    btUInt = 7,
    btFloat = 8,
    btBCD = 9,
    btBool = 10,
    btLong = 13,
    btULong = 14, // DWORD
    btCurrency = 25,
    btDate = 26,
    btVariant = 27,
    btComplex = 28,
    btBit = 29,
    btBSTR = 30,
    btHresult = 31
  };

  switch(typeId)
  {
  case btVoid:
    type = "VOID"; // ??
    return true;
  case btChar:
    type = "CHAR";
    return true;
  case btWChar:
    type = "WCHAR";
    return true;
  case btInt:
    type = "INT";
    return true;
  case btUInt:
    type = "UINT";
    return true;
  case btFloat:
    type = "FLOAT";
    return true;
  case btLong:
    type = "LONG";
    return true;
  case btBool:
    type = "BOOL";
    return true;
  case btBSTR:
    type = "BSTR";
    return true;
  case btVariant:
    type = "VARIANT";
    return true;
  case btULong:
    type = "DWORD";
    return true;
  default:
    type.Format("%d", typeId);
    return true;
  }

  return false;
}

bool CDebugSymbols::DoGetTypeId(CSymbolInfo& symbolInfo, DWORD index, CString& parameter)
{
  DWORD typeId = 0;
  DWORD tagId = 0;

  if (symbolInfo.GetType(index, typeId) && symbolInfo.GetTag(typeId, tagId))
  {
    DWORD baseTypeId = 0;

    if (SymTagBaseType == tagId && symbolInfo.GetBaseType(typeId, baseTypeId))
    {
      return CDebugSymbols::FormatType(baseTypeId, parameter);
    }
    else if (SymTagPointerType == tagId)
    {
      DWORD childIndex = 0;

      if (symbolInfo.GetTypeId(index, childIndex))
      {
        if (CDebugSymbols::DoGetTypeId(symbolInfo, childIndex, parameter))
        {
          parameter += "*";

          return true;
        }
        else
        {
          // we could know find the type, but we know this is a pointer!
          parameter = "VOID*";

          return true;
        }
      }
    }
  }

  return false;
}

BOOL __stdcall CDebugSymbols::EnumSymbolsCallback(PSYMBOL_INFO syminfo, ULONG size, PVOID context)
{
  CString parameters;

  if (SymTagFunction == syminfo->Tag)
  {
    ULONG childIds[32]; // only support 32 arguments
    DWORD numChilds = sizeof(childIds) / sizeof(ULONG);
    CSymbolInfo symbolInfo(syminfo);

    if (symbolInfo.FindChildren(childIds, numChilds))
    {
      for (ULONG i = 0; i < numChilds; ++i)
      {
        DWORD typeId = 0;
        DWORD tagId = 0;
        DWORD childId = childIds[i];

        CString parameter;
        if (!CDebugSymbols::DoGetTypeId(symbolInfo, childId, parameter))
          break;

        if (parameters.GetLength() > 0)
          parameters += ", ";

        parameters += parameter;
      }
    }

    DWORD dwRWA = (DWORD)(syminfo->Address - syminfo->ModBase);
    ((IEnumerateDebugSymbolsCallback*)context)->OnSymbol(syminfo->Name, syminfo->Index, dwRWA, (LPCTSTR)parameters);
  }

  return TRUE;
}

void CDebugSymbols::EnumerateSymbols(LPCTSTR pszModule, IEnumerateDebugSymbolsCallback* callback)
{
  SmartHandle file = 
    CreateFile(pszModule, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);

  if (file.IsValid())
  {
    DWORD size = GetFileSize((HANDLE)file, 0);

    DWORD64 addr = SymLoadModuleEx(m_processHandle, (HANDLE)file, pszModule, 0, 0, size, NULL, 0);

    if (addr)
    {
      BOOL b = SymEnumSymbols(m_processHandle, addr, "", EnumSymbolsCallback, (LPVOID)callback);

      SymUnloadModule64(m_processHandle, addr);
    }
  }

}

