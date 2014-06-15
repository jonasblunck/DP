#include "stdafx.h"
#include "LocalListener.h"
#include "DynHooker.h"
#include "ISC.h"
#include "FakeImpl.h"

#pragma warning(disable: 4482)

class COMTest
{
  LocalListener listener;
  std::auto_ptr<FakeImpl> p;
  CDynHooker hook;

  void TestGarbageParameter()
  {
    BSTR bstr = (BSTR)0x0009c;
    listener.Reset();
    p->MethodBSTR(bstr);

    DPUNIT_ISTRUE(false == listener.WasInvoked());
  }

  void TestAddRefReleaseDoesTrace()
  {
    listener.Reset();
    p->AddRef();
    DPUNIT_STR_EQUAL("IUnknown->AddRef()", listener.GetTrace());
    DPUNIT_INT_EQUAL(1, listener.GetReturnValue()); // hard coded in fake

    p->Release();
    DPUNIT_STR_EQUAL("IUnknown->Release()", listener.GetTrace());
    DPUNIT_INT_EQUAL(1, listener.GetReturnValue()); // hard coded in fake

    p->QueryInterface(GUID_NULL, NULL);
    DPUNIT_ISTRUE(listener.WasInvoked());
    DPUNIT_ISTRUE(listener.GetTrace().Find("QueryInterface") > 0);
  }

  void TestVariant()
  {
    p->MethodVARIANT(CComVariant(100));
    DPUNIT_STR_EQUAL("ITestInterface->MethodVARIANT(100)", listener.GetTrace());

    p->MethodVARIANT(CComVariant("text"));
    DPUNIT_STR_EQUAL("ITestInterface->MethodVARIANT(text)", listener.GetTrace());
 
    CString strExpected;
    CComVariant vt;
    p->MethodVARPTROut(&vt);
    strExpected.Format("ITestInterface->MethodVARPTROut(0x%.8X)", &vt);
    DPUNIT_STR_EQUAL(strExpected, listener.GetTrace());
  }

  void TestBSTR()
  {
    p->MethodBSTR(CComBSTR("text"));
    DPUNIT_STR_EQUAL("ITestInterface->MethodBSTR(\"text\")", listener.GetTrace());
    DPUNIT_INT_EQUAL(0xbaad, listener.GetReturnValue());
  }

  void TestInt()
  {
    p->MethodInt(123);
    DPUNIT_STR_EQUAL("ITestInterface->MethodInt(123)", listener.GetTrace());
    DPUNIT_INT_EQUAL(S_OK, listener.GetReturnValue());
  }

  void TestLong()
  {
    p->MethodLong(12345678);
    DPUNIT_STR_EQUAL("ITestInterface->MethodLong(12345678)", listener.GetTrace());
  }

  void TestFloat()
  {
    p->MethodFloat((float)1.234567);
    DPUNIT_STR_EQUAL("ITestInterface->MethodFloat(1.234567)", listener.GetTrace());
  }

  void TestQI()
  {
    IUnknown* unk = 0;
    p->QueryInterface(__uuidof(ITestInterface), (void**)&unk);
    DPUNIT_INT_EQUAL(0, listener.GetTrace().Find("ITestInterface->QueryInterface(ITestInterface"));

    p->QueryInterface(__uuidof(IUnknown), (void**)&unk);
    DPUNIT_INT_EQUAL(0, listener.GetTrace().Find("ITestInterface->QueryInterface(IUnknown"));
  }

  void TestInOutInt()
  {
    int tmp = 0;
    p->MethodIntOut(&tmp);
    CString strExpect;
    strExpect.Format("ITestInterface->MethodIntOut(%ld)", &tmp);
    DPUNIT_STR_EQUAL(strExpect, listener.GetTrace());
  }

  void TestMultipleParams()
  {
    p->MethodGUID_BSTR(__uuidof(ITestInterface), CComBSTR("text"));
    DPUNIT_STR_EQUAL("ITestInterface->MethodGUID_BSTR(ITestInterface, \"text\")", listener.GetTrace());

    p->MethodDouble(1.234000, CComBSTR("text"));
    DPUNIT_STR_EQUAL("ITestInterface->MethodDouble(1.234000, \"text\")", listener.GetTrace());
  }

  void TestShort()
  {
    p->MethodShort(128);
    DPUNIT_STR_EQUAL("ITestInterface->MethodShort(128)", listener.GetTrace());
  }

  void TestBOOL()
  {
    p->MethodBOOL(FALSE, CComBSTR("foxy"));
    DPUNIT_STR_EQUAL("ITestInterface->MethodBOOL(0, \"foxy\")", listener.GetTrace());
  }

  void TestQIHooksOutgoing()
  {
    ITestInterface2* p2 = NULL;
    p->QueryInterface(__uuidof(ITestInterface2), (void**)&p2);
    DPUNIT_ISNOTNULL(p2);

    listener.Reset();
  
    p2->MethodMix(1, CComBSTR("text"));
    DPUNIT_STR_EQUAL("ITestInterface2->MethodMix(1, \"text\")", listener.GetTrace());   
  }

  void TestOut_iidis()
  {
    ITestInterface3* p3 = NULL;
    p->GetFooBarInterface(const_cast<GUID*>(&__uuidof(ITestInterface3)), reinterpret_cast<IUnknown**>(&p3));

    listener.Reset();
    DPUNIT_STR_EQUAL("", listener.GetTrace());
  }

public:
  COMTest()
  {
    p = std::auto_ptr<FakeImpl>(new FakeImpl());
    hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);
  }

  void RunTests()
  {
    TestBOOL();
    TestBSTR();
    TestInt();
    TestLong();
    TestFloat();
    TestQI();
    TestInOutInt();
    TestMultipleParams();
    TestShort();
    TestAddRefReleaseDoesTrace();
    TestGarbageParameter();
    TestVariant();
    TestQIHooksOutgoing();
    TestOut_iidis();
  }

  static void LoadTypeinformation()
  {
    CComPtr<ITypeLib> spTypeLib;
    HRESULT hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
 
    DPUNIT_ISTRUE(spTypeLib.p != NULL);
    DPUNIT_EQUAL(S_OK, hr);

    ISC::GetISC().AddTypeLibrary(spTypeLib);
  }
};

void testCOM()
{
  COMTest::LoadTypeinformation();

  std::auto_ptr<COMTest> test(new COMTest());
  test->RunTests();
}

#pragma warning(default: 4482)
