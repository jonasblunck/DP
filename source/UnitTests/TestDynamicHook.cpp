
#include "stdafx.h"
#include "..\dlls\chainhook\ChainHookAPI.h"
#include "DynHooker.h"
#include "ParameterTypes.h"
#include "HookContext.h"
#include "LocalListener.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#pragma warning(disable: 4482)


namespace DpTests
{

	TEST_CLASS(TestDynamicHook)
	{
		static void __stdcall IntFunction(int i1, int i2)
		{
			ENSURE_RELEASE_NOT_OPT("IntFunction");
		}

		static void UnknownFunction()
		{
			ENSURE_RELEASE_NOT_OPT("UnknownFunction");
		}

		static void PointerFunction(LPVOID p1, LPVOID p2)
		{
			ENSURE_RELEASE_NOT_OPT("PointerFunction");
		}

		// static __stdcall does not push this pointer...
		static void __stdcall StringFunction(LPSTR psz)
		{
			ENSURE_RELEASE_NOT_OPT("StringFunction");
		}

		static void ContextTest(int, float)
		{
			ENSURE_RELEASE_NOT_OPT("ContextTest");
		}

		// __stdcall on instance-member function pushes this as stack parameter
		void __stdcall NonStatic(int, int)
		{
			ENSURE_RELEASE_NOT_OPT("NonStatic");
		}

		static void CallOtherHookedFunctions()
		{
			IntFunction(100, 200);
			StringFunction("text");
		}

		void TestNonStatic()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			LPVOID address = NULL;

			__asm
			{
				mov eax, TestDynamicHook::NonStatic
					mov address, eax
			}

			m_hookManager.InstallDynamicHook(address, NULL, &m_parameters, &m_listener, true);

			NonStatic(4422, 5533); // call the hooked function

			DPUNIT_ISTRUE(m_listener.WasInvoked());
			DPUNIT_STR_EQUAL("4422, 5533", m_listener.GetTrace());
		}

		void TestUnknown()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::UnknownFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();

			DPUNIT_ISTRUE(m_listener.WasInvoked());
			DPUNIT_EQUAL(m_hookId, m_listener.GetId());
			DPUNIT_STR_EQUAL("???", m_listener.GetTrace());
		}

	public:

		TEST_METHOD(TestIntsWithFunctionName)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::IntFunction;

			TestDynamicHook::IntFunction(100, 200);

			DPUNIT_ISTRUE(m_listener.WasInvoked());
			Assert::IsTrue(m_listener.WasInvoked());
			
			DPUNIT_EQUAL(m_hookId, m_listener.GetId());
			
			DPUNIT_STR_EQUAL("IntFunction(100, 200)", m_listener.GetTrace());			
		}

		void TestPointers()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::PointerFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);

			DPUNIT_ISTRUE(m_listener.WasInvoked());
			DPUNIT_EQUAL(m_hookId, m_listener.GetId());
			DPUNIT_STR_EQUAL("0x88776655, 0x00000000", m_listener.GetTrace());
		}

		void TestString()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::StringFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");

			DPUNIT_ISTRUE(m_listener.WasInvoked());
			DPUNIT_EQUAL(m_hookId, m_listener.GetId());
			DPUNIT_STR_EQUAL("\"stringie..\"", m_listener.GetTrace());
		}

		void TestCallsThatInvokesOtherHookedFunctions()
		{
			// CallOtherHookedFunctions, IntFunction, StringFunction
			TestIntsWithFunctionName(); // will make sure "IntFunction" is hooked
			TestString(); // will make sure "StringFunction" is hooked

			m_parameters.clear();
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::CallOtherHookedFunctions, "CallOtherHookedFunctions", &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::CallOtherHookedFunctions;

			TestDynamicHook::CallOtherHookedFunctions();

			DPUNIT_STR_EQUAL("CallOtherHookedFunctions()", m_listener.GetTrace());
		}

		void TestContext()
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			//
			// not hooked, no context should be available
			DPUNIT_EQUAL(false, CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context));

			// 
			// hook and check context
			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			DPUNIT_ISTRUE(CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context));

			DPUNIT_EQUAL(2, context->GetMethodInfo()->nParamCount);
			DPUNIT_EQUAL(VT_INT, context->GetMethodInfo()->pParams[0].vtType);
			DPUNIT_EQUAL(VT_R4, context->GetMethodInfo()->pParams[1].vtType);
			DPUNIT_ISTRUE(context->IsActive());
		}

		CDynHooker m_hookManager;
		LocalListener m_listener;
		ISC::InterfaceMethod m_parameters;
		long m_hookId;
	
		void Test()
		{
			//TestIntsWithFunctionName();
			//TestPointers();
			//TestString();
			//TestUnknown();
			//  TestContext();
			//TestNonStatic();
			//TestCallsThatInvokesOtherHookedFunctions();
		}
	};


	//void testDynamicHook()
	//{
	//	TestDynamicHook test;
	//
	//	test.Test();
	//}

}

#pragma warning(default: 4482)