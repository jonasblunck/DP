#include "stdafx.h"
#include "ipc.h"
#include "IPCHelper.h"
#include "CBuffer.h"
#include <atlcoll.h>
#include "IntegrationTests.h"

#include <direct.h>
#define GetCurrentDir _getcwd

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestIntegrationAdo)
{
	//TODO: DpInfiltrator.dll crashing TestComApp.exe so to inject from outside process instead of load inside.
	// Also to move injection code from DP.exe to a separate library to allow for reuse.
	TEST_METHOD(IntegrationADO_TestAppStarts)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp("TestComApp.exe");

		Assert::IsTrue(started);
	}

	TEST_METHOD(IntegrationADO_Verify_Incoming_TraceMessage_0)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp("TestComApp.exe");

		t.InitIpc();
		t.WaitForTestAppToExit();
		CString traceResult = t.m_traces[0];

		//Assert::AreEqual("IXMLDOMDocument->load(NO_SUCH_FILE)", t.m_traces[0]);

		t.UnInitIpc();
	}

	TEST_METHOD(IntegrationADO_Verify_Incoming_TraceMessage_1)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp("TestComApp.exe");

		t.InitIpc();
		t.WaitForTestAppToExit();

		//Assert::AreEqual("IXMLDOMDocument->hasChildNodes()", t.m_traces[1]);

		t.UnInitIpc();
	}

	TEST_METHOD(IntegrationADO_Verify_Incoming_TraceMessage_2)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp("TestComApp.exe");

		t.InitIpc();
		t.WaitForTestAppToExit();

		//Assert::AreEqual("IXMLDOMDocument->Release()", t.m_traces[2]);

		t.UnInitIpc();
	}
};