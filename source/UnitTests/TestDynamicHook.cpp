
#include "stdafx.h"
#include "..\dlls\chainhook\ChainHookAPI.h"
#include "DynHooker.h"
#include "ParameterTypes.h"
#include "HookContext.h"
#include "LocalListener.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DpTests
{
	TEST_CLASS(TestDynamicHook)
	{
	private:

		CDynHooker m_hookManager;
		LocalListener m_listener;
		ISC::InterfaceMethod m_parameters;
		long m_hookId;

		void IntsWithFunctionNameCall()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::IntFunction;

			TestDynamicHook::IntFunction(100, 200);
		}

		void StringFunctionCall()
		{
			m_parameters.clear();
			m_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::StringFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
		}

	public:
		
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

		TEST_METHOD(DynamicHook_NonStatic_WasInvoked)
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

			Assert::IsTrue(m_listener.WasInvoked());			
		}

		TEST_METHOD(DynamicHook_NonStatic_CorrectTrace)
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
			
			Assert::AreEqual("4422, 5533", m_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_Unknown_WasInvoked)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::UnknownFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();

			Assert::IsTrue(m_listener.WasInvoked());
		}	

		TEST_METHOD(DynamicHook_Unknown_CorrectId)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::UnknownFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();
			
			Assert::AreEqual(m_hookId, m_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_Unknown_CorrectTrace)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::UnknownFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();

			Assert::AreEqual("???", m_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_WasInvoked)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &m_parameters, &m_listener);			

			TestDynamicHook::IntFunction(100, 200);
			
			Assert::IsTrue(m_listener.WasInvoked());														
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_CorrectId)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::IntFunction;

			TestDynamicHook::IntFunction(100, 200);
			
			Assert::AreEqual(m_hookId, m_listener.GetId());
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_CorrectTrace)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &m_parameters, &m_listener);

			TestDynamicHook::IntFunction(100, 200);				
			
			Assert::AreEqual("IntFunction(100, 200)", m_listener.GetTrace());
		}				

		TEST_METHOD(DynamicHook_Pointers_WasInvoked)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::PointerFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
			
			Assert::IsTrue(m_listener.WasInvoked());			
		}

		TEST_METHOD(DynamicHook_Pointers_CorrectId)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::PointerFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
						
			Assert::AreEqual(m_hookId, m_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_Pointers_CorrectTrace)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			m_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::PointerFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
						
			Assert::AreEqual("0x88776655, 0x00000000", m_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_String_WasInvoked)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::StringFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
			
			Assert::IsTrue(m_listener.WasInvoked());
		}

		TEST_METHOD(DynamicHook_String_CorrectId)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::StringFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
						
			Assert::AreEqual(m_hookId, m_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_String_CorrectTrace)
		{
			m_parameters.clear();
			m_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::StringFunction, NULL, &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
			
			Assert::AreEqual("\"stringie..\"", m_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_CallThatInvokesOtherHookedFunctions)
		{			
			IntsWithFunctionNameCall(); // will make sure "IntFunction" is hooked
			StringFunctionCall(); // will make sure "StringFunction" is hooked

			m_parameters.clear();
			m_listener.Reset();

			m_hookManager.InstallDynamicHook
				(TestDynamicHook::CallOtherHookedFunctions, "CallOtherHookedFunctions", &m_parameters, &m_listener);

			m_hookId = (long)TestDynamicHook::CallOtherHookedFunctions;

			TestDynamicHook::CallOtherHookedFunctions();

			Assert::AreEqual("CallOtherHookedFunctions()", m_listener.GetTrace());
		}

		// Context Tests - currently not passing
		/*
		TEST_METHOD(DynamicHook_Context_NotHooked)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			// not hooked, no context should be available
			Assert::AreEqual(false, CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context));			
		}

		TEST_METHOD(DynamicHook_Context_IsHooked)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			Assert::IsTrue(CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context));
		}

		TEST_METHOD(DynamicHook_Context_TwoParams)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context);

			Assert::AreEqual(2, (int)context->GetMethodInfo()->nParamCount);
		}

		
		TEST_METHOD(DynamicHook_Context_FirstParamIsInt)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context);

			Assert::AreEqual((SHORT)VT_INT, context->GetMethodInfo()->pParams[0].vtType);
		}

		TEST_METHOD(DynamicHook_Context_SecondParamIs4ByteReal)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context);

			Assert::AreEqual((SHORT)VT_INT, context->GetMethodInfo()->pParams[1].vtType);			
		}

		TEST_METHOD(DynamicHook_Context_IsContextActive)
		{
			HookContext* context = 0;
			m_parameters.clear();
			m_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			m_parameters.addParam(VT_R4, ISC::PointerSpec::NoPtr);

			m_hookManager.InstallDynamicHook(
				TestDynamicHook::ContextTest, "ContextTest", &m_parameters, &m_listener);

			CDynHooker::GetHookContext(TestDynamicHook::ContextTest, context);
			
			Assert::IsTrue(context->IsActive());
		}	
		*/
			
	};
	  
}

//#pragma warning(default: 4482)