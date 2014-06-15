#include "StdAfx.h"
#include "HookCoCreateInstance.h"
#include "ISC.h"


ProcCoCreateInstance CHookCoCreateInstance::m_ProcCoCreateInstanceChain = NULL;
ProcCoMarshalInterface CHookCoCreateInstance::m_ProcCoMarshalInterface = NULL;

bool HookInterface(IUnknown* pInterface, REFIID riid);


CHookCoCreateInstance::CHookCoCreateInstance(void)
{
  m_ProcCoCreateInstanceChain = NULL;
}

CHookCoCreateInstance::~CHookCoCreateInstance(void)
{
}

void CHookCoCreateInstance::Hook()
{
  m_ProcCoCreateInstanceChain =
    (ProcCoCreateInstance)CHHookProc(GetCurrentProcess(), &CoCreateInstance, CoCreateInstanceHook); 

  m_ProcCoMarshalInterface =
    (ProcCoMarshalInterface)CHHookProc(GetCurrentProcess(), &CoMarshalInterface, CoMarshalInterfaceHook); 
}

HRESULT __stdcall CHookCoCreateInstance::CoCreateInstanceHook(REFCLSID clsId,
                                                              LPUNKNOWN pUnkOuter,
                                                              DWORD dwClsCtx,
                                                              REFIID riid,
                                                              LPVOID* ppv)
{
  HRESULT hr = m_ProcCoCreateInstanceChain(clsId, pUnkOuter, dwClsCtx, riid, ppv);

  if (*ppv)
    HookInterface(reinterpret_cast<IUnknown*>(*ppv), riid);

  return hr;
}

HRESULT __stdcall CHookCoCreateInstance::CoMarshalInterfaceHook(IStream* pStm,
                                                                REFIID riid,
                                                                IUnknown* pUnk,
                                                                DWORD dwDestContext,
                                                                void* pvDestContext,
                                                                DWORD mshlflags)
{

  HRESULT hr = m_ProcCoMarshalInterface(pStm, riid, pUnk, dwDestContext, pvDestContext, mshlflags);

  if (pUnk)
    HookInterface(pUnk, riid);

  return hr;
}


