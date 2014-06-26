#include "stdafx.h"

#include "ISC.h"

#import "..\..\Bin\UnitTests.tlb"  raw_interfaces_only, no_namespace

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DpTests
{
	TEST_CLASS(TestISC)
	{
		TEST_CLASS_INITIALIZE(Initialise)
		{
			CComPtr<ITypeLib> spTypeLib;
			HRESULT hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);			

			ISC::GetISC().AddTypeLibrary(spTypeLib);
		}
		
		TEST_METHOD(ISC_LoadTypeinformation_ComPointerIsNotNull)
		{
			CComPtr<ITypeLib> spTypeLib;
			HRESULT hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);

			Assert::IsTrue(spTypeLib.p != NULL);
		}

		TEST_METHOD(ISC_LoadTypeinformation_HresultIsOk)
		{
			CComPtr<ITypeLib> spTypeLib;
			HRESULT hr = LoadTypeLibEx(CComBSTR("UnitTests.tlb"), REGKIND_REGISTER, &spTypeLib);
			
			Assert::AreEqual(S_OK, hr);
		}

		TEST_METHOD(ISC_OutInterface_HasCorrectName)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& m2 = itf->pMethods[12];

			Assert::AreEqual("GetTestInterface2", m2.strName);
		}

		TEST_METHOD(ISC_OutInterface_HasCorrectIID)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& m2 = itf->pMethods[12];

			Assert::IsTrue(m2.pParams[0].riid == __uuidof(ITestInterface2));
		}

		TEST_METHOD(ISC_LoadedTypelib_Has13Methods)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));
			Assert::AreEqual(13, (int)itf->nMethodCount); // count does not include base functions (QI, AddRef, Release)

			ISC::InterfaceMethod& method = itf->pMethods[5];			
		}

		TEST_METHOD(ISC_LoadedTypelib_SixthMethodNameCorrect)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));			

			ISC::InterfaceMethod& method = itf->pMethods[5];

			Assert::AreEqual("MethodIntOut", method.strName);
		}

		TEST_METHOD(ISC_LoadedTypelib_SixthMethodFirstParamIsPointer)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& method = itf->pMethods[5];

			Assert::IsTrue(ISC::PointerSpec::Ptr == method.pParams[0].pointerSpec);			
		}

		TEST_METHOD(ISC_LoadedTypelib_SixthMethodFirstParamIsInt)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& method = itf->pMethods[5];

			Assert::IsTrue(VT_INT == method.pParams[0].vtType);
			
		}

		TEST_METHOD(ISC_LoadedTypelib_FirstMethodInterfaceNameCorrect)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& m = itf->pMethods[0];

			Assert::AreEqual("GetFooBarInterface", m.strName);
		}

		TEST_METHOD(ISC_LoadedTypelib_ContainsInterface)
		{
			ISC::Interface* itf = ISC::GetISC().GetInterface(__uuidof(ITestInterface));

			ISC::InterfaceMethod& m = itf->pMethods[0];

			Assert::IsTrue(m.pParams[1].riid == __uuidof(IUnknown));
		}		
	};
}