#include "stdafx.h"
#include "DebugSymbols.h"
#include <map>

class TestDebugSymbols : public IEnumerateDebugSymbolsCallback
{
  std::map<CString, CString> m_symbols;

  void Setup()
  {
    // read symbols for my own test code!
    CString filename; 
    ::GetModuleFileName(0, filename.GetBuffer(1024), 1024); filename.ReleaseBuffer();

    CDebugSymbols symbolEngine;

    symbolEngine.Initialize();
    symbolEngine.EnumerateSymbols((LPCTSTR)filename, this);
  }

  // IEnumerateDebugSymbolsCallback callback
  BOOL OnSymbol(LPCTSTR pszSymbolName, DWORD dwOrdinal, DWORD dwRVA, LPCTSTR pszParameters)
  {
    CString name(pszSymbolName);
    CString params(pszParameters);

    m_symbols.insert(std::map<CString, CString>::value_type(name, params));

    return TRUE;
  }

  //
  // test functions start here
  //
  void TestBasicTypes()
  {
    std::map<CString, CString>::const_iterator i = m_symbols.end();

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::IntFunction"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("INT, INT, INT", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::LongFunction"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("LONG, LONG", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::StringFunction"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("CHAR*", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::CharFunction"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("CHAR", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::DwordPtrFunction"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("DWORD*", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::Mixed"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("DWORD*, CHAR*, INT", i->second);
  }

  void TestPointers()
  {
    std::map<CString, CString>::const_iterator i = m_symbols.end();

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::PassingReference"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("VOID*", i->second);

    DPUNIT_ISTRUE((i = m_symbols.find(_T("TestData::PointerToPointer"))) != m_symbols.end());
    DPUNIT_STR_EQUAL("VOID**", i->second);
  }

public:
  void Test()
  {
    Setup();
    TestBasicTypes();
    TestPointers();
  }
};

void testDebugSymbols()
{
  TestDebugSymbols test;
  test.Test();
}

