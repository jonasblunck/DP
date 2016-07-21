
#include "stdafx.h"
#include "..\dlls\chainhook\ChainHookAPI.h"
#include "DynHooker.h"
#include "ParameterTypes.h"
#include "HookContext.h"
#include "LocalListener.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static CDynHooker s_hookManager;
static ISC::InterfaceMethod s_parameters;
static LocalListener s_listener;

namespace DpTests
{
	TEST_CLASS(TestDynamicHook)
	{
	private:

		long m_hookId;
		
		void IntsWithFunctionNameCall()
		{
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::IntFunction;

			TestDynamicHook::IntFunction(100, 200);
		}

		void StringFunctionCall()
		{
			s_parameters.clear();
			s_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
		}
		

		TEST_CLASS_INITIALIZE(InitializeHooks)
		{
			s_hookManager.InstallDynamicHook(
				TestDynamicHook::IntFunction, "IntFunction", &s_parameters, &s_listener);

			s_hookManager.InstallDynamicHook(
				TestDynamicHook::StringFunction, "StringFunction", &s_parameters, &s_listener);

			s_hookManager.InstallDynamicHook(
				TestDynamicHook::UnknownFunction, NULL, &s_parameters, &s_listener);

			s_hookManager.InstallDynamicHook(
				TestDynamicHook::PointerFunction, NULL, &s_parameters, &s_listener);

			LPVOID address = NULL;

			__asm
			{
				mov eax, TestDynamicHook::NonStatic
				mov address, eax
			}

			s_hookManager.InstallDynamicHook(address, NULL, &s_parameters, &s_listener, true);

		}
		
	public:

		TestDynamicHook()
		{
			InitializeHooks();
		}
		
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
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			NonStatic(4422, 5533); // call the hooked function

			Assert::IsTrue(s_listener.WasInvoked());			
		}

		TEST_METHOD(DynamicHook_NonStatic_CorrectTrace)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			NonStatic(4422, 5533); // call the hooked function
			
			Assert::AreEqual("4422, 5533", s_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_Unknown_WasInvoked)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();

			Assert::IsTrue(s_listener.WasInvoked());
		}	

		TEST_METHOD(DynamicHook_Unknown_CorrectId)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();
			
			Assert::AreEqual(m_hookId, s_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_Unknown_CorrectTrace)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_EMPTY, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::UnknownFunction;

			TestDynamicHook::UnknownFunction();

			Assert::AreEqual("???", s_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_WasInvoked)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();			

			TestDynamicHook::IntFunction(100, 200);
			
			Assert::IsTrue(s_listener.WasInvoked());														
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_CorrectId)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::IntFunction;

			TestDynamicHook::IntFunction(100, 200);
			
			Assert::AreEqual(m_hookId, s_listener.GetId());
		}

		TEST_METHOD(DynamicHook_IntsWithFunctionName_CorrectTrace)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_parameters.addParam(VT_INT, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			TestDynamicHook::IntFunction(100, 200);				
			
			Assert::AreEqual("IntFunction(100, 200)", s_listener.GetTrace());
		}				

		TEST_METHOD(DynamicHook_Pointers_WasInvoked)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
			
			Assert::IsTrue(s_listener.WasInvoked());			
		}

		TEST_METHOD(DynamicHook_Pointers_CorrectId)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
						
			Assert::AreEqual(m_hookId, s_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_Pointers_CorrectTrace)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);
			s_parameters.addParam(VT_VOID, ISC::PointerSpec::Ptr);

			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::PointerFunction;

			TestDynamicHook::PointerFunction((LPVOID)0x88776655, (LPVOID)0x00000000);
						
			Assert::AreEqual("0x88776655, 0x00000000", s_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_String_WasInvoked)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
			
			Assert::IsTrue(s_listener.WasInvoked());
		}

		TEST_METHOD(DynamicHook_String_CorrectId)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
						
			Assert::AreEqual(m_hookId, s_listener.GetId());			
		}

		TEST_METHOD(DynamicHook_String_CorrectTrace)
		{
			s_parameters.clear();
			s_parameters.addParam(VT_LPSTR, ISC::PointerSpec::NoPtr);
			s_listener.Reset();

			m_hookId = (long)TestDynamicHook::StringFunction;

			TestDynamicHook::StringFunction("stringie..");
			
			Assert::AreEqual("StringFunction(\"stringie..\")", s_listener.GetTrace());
		}

		TEST_METHOD(DynamicHook_CallThatInvokesOtherHookedFunctions)
		{			
			IntsWithFunctionNameCall(); // will make sure "IntFunction" is hooked
			StringFunctionCall(); // will make sure "StringFunction" is hooked

			s_parameters.clear();
			s_listener.Reset();

			s_hookManager.InstallDynamicHook
				(TestDynamicHook::CallOtherHookedFunctions, "CallOtherHookedFunctions", &s_parameters, &s_listener);

			m_hookId = (long)TestDynamicHook::CallOtherHookedFunctions;

			TestDynamicHook::CallOtherHookedFunctions();

			Assert::AreEqual("CallOtherHookedFunctions()", s_listener.GetTrace());
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