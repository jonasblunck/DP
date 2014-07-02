#include "stdafx.h"
#include "LocalListener.h"
#include "DynHooker.h"
#include "ISC.h"
#include "FakeImpl.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(COMTest)
{
public:
	
	TEST_METHOD(COM_LoadTypeLib_LibIsNotNull)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		Assert::IsTrue(spTypeLib.p != NULL);
	}

	TEST_METHOD(COM_LoadTypeLib_HresultIsOK)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		Assert::AreEqual(S_OK, hr);
	}

	TEST_METHOD(COM_GarbageParameter)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);
		
		BSTR bstr = (BSTR)0x0009c;
		listener.Reset();
		p->MethodBSTR(bstr);

		Assert::IsFalse(listener.WasInvoked());
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_AddRef_CorrectTrace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();
		p->AddRef();

		Assert::AreEqual("ITestInterface->AddRef()", listener.GetTrace());		
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_AddRef_Correct_ReturnValue)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();
		p->AddRef();
		
		Assert::AreEqual(1, listener.GetReturnValue()); // hard coded in fake
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_Release_Correct_Trace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();

		p->AddRef();
		p->Release();
		
		Assert::AreEqual("ITestInterface->Release()", listener.GetTrace());		
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_Release_Correct_ReturnValue)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();

		p->AddRef();
		p->Release();
		
		Assert::AreEqual(1, listener.GetReturnValue()); // hard coded in fake
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_QueryInterface_WasInvoked)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();
		p->AddRef();
		p->Release();

		p->QueryInterface(GUID_NULL, NULL);
		
		Assert::IsTrue(listener.WasInvoked());
	}

	TEST_METHOD(COM_AddRefReleaseDoesTrace_QueryInterface_CorrectTrace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		listener.Reset();
		p->AddRef();

		p->Release();

		p->QueryInterface(GUID_NULL, NULL);

		Assert::IsTrue(listener.GetTrace().Find("QueryInterface") > 0);
	}

	
	TEST_METHOD(TestVariant_CorrectTrace_Int)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodVARIANT(CComVariant(100));
		
		Assert::AreEqual("ITestInterface->MethodVARIANT(100)", listener.GetTrace());
	}
	
	TEST_METHOD(TestVariant_CorrectTrace_String)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodVARIANT(CComVariant("text"));
		
		Assert::AreEqual("ITestInterface->MethodVARIANT(text)", listener.GetTrace());
	}
	
	TEST_METHOD(TestVariant_CorrectTrace_Pointer)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		CString strExpected;
		CComVariant vt;
		p->MethodVARPTROut(&vt);
		strExpected.Format("ITestInterface->MethodVARPTROut(0x%.8X)", &vt);
		
		Assert::AreEqual((LPCTSTR)strExpected, listener.GetTrace());
	}

	TEST_METHOD(COM_TestBSTR_CorrectTrace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodBSTR(CComBSTR("text"));
		
		Assert::AreEqual("ITestInterface->MethodBSTR(\"text\")", listener.GetTrace());
	}

	TEST_METHOD(COM_TestBSTR_Correct_ReturnValue)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodBSTR(CComBSTR("text"));

		Assert::AreEqual(0xbaad, listener.GetReturnValue());
	}

	TEST_METHOD(COM_Int_Correct_Trace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodInt(123);

		Assert::AreEqual("ITestInterface->MethodInt(123)", listener.GetTrace());
	}

	TEST_METHOD(COM_Int_Correct_ReturnValue)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodInt(123);

		Assert::AreEqual((int)S_OK, listener.GetReturnValue());
	}

	TEST_METHOD(TestLong_Correct_Trace)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodLong(12345678);

		Assert::AreEqual("ITestInterface->MethodLong(12345678)", listener.GetTrace());
	}

	TEST_METHOD(TestFloat)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodFloat((float)1.234567);

		Assert::AreEqual("ITestInterface->MethodFloat(1.234567)", listener.GetTrace());
	}
	
	TEST_METHOD(COM_QueryInterface_ITestInterface)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		IUnknown* unk = 0;
		p->QueryInterface(__uuidof(ITestInterface), (void**)&unk);
		
		Assert::AreEqual(0, listener.GetTrace().Find("ITestInterface->QueryInterface(ITestInterface"));
	}

	TEST_METHOD(COM_QueryInterface_IUnknown)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		IUnknown* unk = 0;

		p->QueryInterface(__uuidof(IUnknown), (void**)&unk);
		
		Assert::AreEqual(0, listener.GetTrace().Find("ITestInterface->QueryInterface(IUnknown"));
	}

	TEST_METHOD(COM_InOutInt)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		int tmp = 0;
		p->MethodIntOut(&tmp);
		CString strExpect;
		strExpect.Format("ITestInterface->MethodIntOut(%ld)", &tmp);

		Assert::AreEqual((LPCTSTR)strExpect, listener.GetTrace());
	}
	
	TEST_METHOD(COM_MultipleParams_ITestInterface_BTSTR)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodGUID_BSTR(__uuidof(ITestInterface), CComBSTR("text"));

		Assert::AreEqual("ITestInterface->MethodGUID_BSTR(ITestInterface, \"text\")", listener.GetTrace());
	}
	
	TEST_METHOD(COM_MultipleParams_Double_BTSTR)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodDouble(1.234000, CComBSTR("text"));
		
		Assert::AreEqual("ITestInterface->MethodDouble(1.234000, \"text\")", listener.GetTrace());
	}

	TEST_METHOD(COM_TestShort)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodShort(128);
		
		Assert::AreEqual("ITestInterface->MethodShort(128)", listener.GetTrace());
	}

	TEST_METHOD(COM_BOOL)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		p->MethodBOOL(FALSE, CComBSTR("foxy"));
		
		Assert::AreEqual("ITestInterface->MethodBOOL(0, \"foxy\")", listener.GetTrace());
	}

	TEST_METHOD(COM_QueryInterface_HooksOutgoing_ITestInterface)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);
		
		ITestInterface2* p2 = NULL;
		p->QueryInterface(__uuidof(ITestInterface2), (void**)&p2);
		
		Assert::IsNotNull(p2);
	}

	
	TEST_METHOD(COM_QueryInterface_HooksOutgoing_MethodMix)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		ITestInterface2* p2 = NULL;
		p->QueryInterface(__uuidof(ITestInterface2), (void**)&p2);

		listener.Reset();

		p2->MethodMix(1, CComBSTR("text"));

		Assert::AreEqual("ITestInterface2->MethodMix(1, \"text\")", listener.GetTrace());
	}

	TEST_METHOD(COM_Out_iidis)
	{
		LocalListener listener;
		std::auto_ptr<FakeImpl> p;
		CDynHooker hook;
		CComPtr<ITypeLib> spTypeLib;
		HRESULT hr;

		hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
		ISC::GetISC().AddTypeLibrary(spTypeLib);

		p = std::auto_ptr<FakeImpl>(new FakeImpl());
		hook.HookInterface(reinterpret_cast<IUnknown*>(p.get()), __uuidof(ITestInterface), &listener);

		ITestInterface3* p3 = NULL;
		p->GetFooBarInterface(const_cast<GUID*>(&__uuidof(ITestInterface3)), reinterpret_cast<IUnknown**>(&p3));

		listener.Reset();

		Assert::AreEqual("", listener.GetTrace());
	}
};
