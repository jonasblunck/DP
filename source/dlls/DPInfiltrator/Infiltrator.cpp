
#include "stdafx.h"
#include "Infiltrator.h"
#include "DynHooker.h"
#include "TraceDispatcher.h"
#include "ParameterTypes.h"
#include "HookCoCreateInstance.h"

static CDynHooker s_HookManager;
static CTraceDispatcher s_dispatcher;

static HANDLE s_hStopThreadEvent = NULL;
#define NELM(x) sizeof(x) / sizeof(x[0])

Infiltrator::Infiltrator()
{
  InitUnsafeAddresses();
}

Infiltrator::~Infiltrator()
{
}

void Infiltrator::InitUnsafeAddresses()
{
  m_ListUnsafe.clear();

  m_ListUnsafe.push_back((DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"), "TlsGetValue"));
  m_ListUnsafe.push_back((DWORD)GetProcAddress(GetModuleHandle("kernel32.dll"), "TlsSetValue"));
}

bool Infiltrator::IsUnsafe(DWORD dwAddress)
{
  DWList::iterator Iterator = m_ListUnsafe.begin();

  while (Iterator != m_ListUnsafe.end())
  {
    if (dwAddress == (*Iterator))
      return true;

    ++Iterator;
  }

  return false;
}

STDMETHODIMP Infiltrator::Pause(VARIANT_BOOL vtbPause)
{
  bool bPause = (VARIANT_TRUE == vtbPause);

  s_HookManager.SetPause(bPause);

  return S_OK;
}

void Infiltrator::ExtractParameterDefinitions(const CString& combound, std::list<SHORT>& definitions)
{
  CString tmp(combound);
  int position = 0;
  
  do
  {
    CString vtParam = tmp.Tokenize(",", position);
    vtParam.Trim();

    if (!vtParam.IsEmpty())
    {
      SHORT paramType = TranslateNamedType(vtParam);

      definitions.push_back(paramType);
    }
  }
  while (-1 != position);
}

STDMETHODIMP Infiltrator::Unhook(BSTR bstrModule, DWORD dwRVA)
{
  USES_CONVERSION;

  DWORD dwAbsoluteAddress = (DWORD)GetModuleHandle(W2A(bstrModule)) + dwRVA;

  if (IsUnsafe(dwAbsoluteAddress))
    return E_INVALIDARG;

  if (s_HookManager.SetActive((LPVOID)dwAbsoluteAddress, false))
    return S_OK;

  return E_INVALIDARG; // not an active hook?
}

STDMETHODIMP Infiltrator::SetupTrace(BSTR bstrModule, DWORD dwRVA, BSTR bstrParamDefinition, long* plIDBlock)
{
  USES_CONVERSION;

  DWORD dwAbsoluteAddress = (DWORD)GetModuleHandle(W2A(bstrModule)) + dwRVA;

  if (IsUnsafe(dwAbsoluteAddress))
    return E_INVALIDARG;
  
  //
  // enumerate parameters
  //
  std::list<SHORT> params;
  Infiltrator::ExtractParameterDefinitions(CString(bstrParamDefinition), params);
 
  // check if already hooked!
  if (s_HookManager.SetActive((LPVOID)dwAbsoluteAddress, true))
  {
    *plIDBlock = (long)dwAbsoluteAddress;
    
    return S_OK;
  }

  ISC::InterfaceMethod* method = NULL; // TODO to extract this info

  //
  // not previously hooked, setup it up
  // 
  if (!s_HookManager.InstallDynamicHook((LPVOID)dwAbsoluteAddress, NULL, method, &s_dispatcher))
    return E_FAIL;

  *plIDBlock = dwAbsoluteAddress;

  return S_OK;
}


bool HookInterface(IUnknown* pInterface, REFIID riid)
{
  return s_HookManager.HookInterface(pInterface, riid, &s_dispatcher);
}


void InitInfiltrator()
{
  s_dispatcher.Init();
}