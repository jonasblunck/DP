
#pragma once

#pragma optimize ("", off)

#import "..\..\Bin\UnitTests.tlb"  raw_interfaces_only, no_namespace

class FakeImpl : public ITestInterface, public ITestInterface2, public ITestInterface3
{
public:
  STDMETHOD(QueryInterface)(REFIID riid, void** ppvObj)
  {
    if (!ppvObj)
      return E_INVALIDARG;

    *ppvObj = 0;

    if (__uuidof(ITestInterface) == riid)
      *ppvObj = static_cast<ITestInterface*>(this);
    else if (__uuidof(ITestInterface2) == riid)
      *ppvObj = static_cast<ITestInterface2*>(this);
    else if (__uuidof(IUnknown) == riid)
      *ppvObj = this;
    else
      *ppvObj = 0;

    if (*ppvObj)
      return S_OK;

    return E_NOINTERFACE;
  }

  STDMETHOD_(ULONG, AddRef)(void) { return 1; }
  STDMETHOD_(ULONG, Release)(void) { return 1; }
  STDMETHOD(MethodInt)(int a) { return S_OK;  }
  STDMETHOD(MethodBSTR)(BSTR b) { return 0xbaad; }
  STDMETHOD(MethodLong)(long l) { return S_OK; }
  STDMETHOD(MethodFloat)(float) { return S_OK; }
  STDMETHOD(MethodIntOut)(int*) { return S_OK;  }
  STDMETHOD(MethodGUID_BSTR)(GUID, BSTR) { return S_OK;  }
  STDMETHOD(MethodShort)(SHORT s) { return S_OK; }
  STDMETHOD(MethodBOOL)(long, BSTR) { return S_OK; }
  STDMETHOD(MethodDouble)(double, BSTR) { return S_OK; }
  STDMETHOD(MethodVARPTROut)(VARIANT*) { return S_OK; }
  STDMETHOD(MethodVARIANT)(VARIANT) { return 0xdeaddead; }
  STDMETHOD(GetFooBarInterface)(GUID* riid, IUnknown** pp)
   {
     if (NULL != pp && NULL != riid && (*riid == __uuidof(ITestInterface3)))
     {
       *pp = reinterpret_cast<ITestInterface3*>(this);
       return S_OK;
     }

     return E_FAIL;
   }

  STDMETHOD(GetTestInterface2)(ITestInterface2** pp) { return S_OK; }

  // ITestInterface2
  STDMETHOD(MethodMix)(long, BSTR) { return E_FAIL; }

  // ITestInterface3
  STDMETHOD(MethodFooBar)(BSTR) { return E_UNEXPECTED; }
};

#pragma optimize ("", on)

