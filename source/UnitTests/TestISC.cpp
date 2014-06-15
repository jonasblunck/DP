#include "stdafx.h"

#include "ISC.h"

#import "..\..\Bin\UnitTests.tlb"  raw_interfaces_only, no_namespace

void LoadTypeinformation()
{
  CComPtr<ITypeLib> spTypeLib;
  HRESULT hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
 
  DPUNIT_ISTRUE(spTypeLib.p != NULL);
  DPUNIT_EQUAL(S_OK, hr);

  ISC::GetISC().AddTypeLibrary(spTypeLib);
}

void TestOutInterfaceHasCorrectIID()
{
  ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

  ISC::InterfaceMethod& m2 = itf->pMethods[12];
  DPUNIT_STR_EQUAL("GetTestInterface2", m2.strName);
  DPUNIT_ISTRUE(m2.pParams[0].riid == __uuidof(ITestInterface2));
}

void TestLoadedTypelibContainsInterface()
{
  ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));
  DPUNIT_INT_EQUAL(13, itf->nMethodCount); // count does not include base functions (QI, AddRef, Release)

  ISC::InterfaceMethod& method = itf->pMethods[5];

  DPUNIT_STR_EQUAL("MethodIntOut", method.strName);
  DPUNIT_ISTRUE(ISC::PointerSpec::Ptr == method.pParams[0].pointerSpec);
  DPUNIT_ISTRUE(VT_INT == method.pParams[0].vtType);

  ISC::InterfaceMethod& m = itf->pMethods[0];
  DPUNIT_STR_EQUAL("GetFooBarInterface", m.strName);
  DPUNIT_ISTRUE(m.pParams[1].riid == __uuidof(IUnknown));
}

void testISC()
{
  LoadTypeinformation();

  TestLoadedTypelibContainsInterface();
  TestOutInterfaceHasCorrectIID();
}