#include "stdafx.h"
#include "DebugSymbols.h"
#include <map>
#include "DebugSymbols.h"

#include "CppUnitTest.h"
#include "DebugSymbolsTestClass.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestDebugSymbols)
{
	DebugSymbolsTestClass debugSymbolsTest;

	TEST_CLASS_INITIALIZE(Initialise)
	{
		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_IntFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::IntFunction"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_IntFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::IntFunction"));

		Assert::AreEqual("INT, INT, INT", i->second);		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_LongFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::LongFunction"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_LongFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();

		i = debugSymbolsTest.m_symbols.find(_T("TestData::LongFunction"));

		Assert::AreEqual("LONG, LONG", i->second);				
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_StringFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::StringFunction"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_StringFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::StringFunction"));

		Assert::AreEqual("CHAR*", i->second);		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_CharFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::CharFunction"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_CharFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::CharFunction"));

		Assert::AreEqual("CHAR", i->second);		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_DwordPtrFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::DwordPtrFunction"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_DwordPtrFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::DwordPtrFunction"));

		Assert::AreEqual("DWORD*", i->second);		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_MixedFunction_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::Mixed"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());		
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_MixedFunction_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::Mixed"));

		Assert::AreEqual("DWORD*, CHAR*, INT", i->second);		
	}

	TEST_METHOD(DebugSymbols_TestPointers_PassingReference_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::PassingReference"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());
	}

	TEST_METHOD(DebugSymbols_TestPointers_PassingReference_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::PassingReference"));

		Assert::AreEqual("VOID*", i->second);
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_PointerToPointer_Find)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::PointerToPointer"));

		Assert::IsTrue(i != debugSymbolsTest.m_symbols.end());
	}

	TEST_METHOD(DebugSymbols_TestBasicTypes_PointerToPointer_Parameters)
	{
		std::map<CString, CString>::iterator i = debugSymbolsTest.m_symbols.end();
		i = debugSymbolsTest.m_symbols.find(_T("TestData::PointerToPointer"));

		Assert::AreEqual("VOID**", i->second);
	}	
};
	