#include "stdafx.h"
#include "ipc.h"
#include "IPCHelper.h"
#include "CBuffer.h"
#include <atlcoll.h>
#include "IntegrationTests.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestIntegration)
{
	TEST_METHOD(Integration_TestAppStarts)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp();

		Assert::IsTrue(started);
	}

	TEST_METHOD(Integration_Verify_Incoming_TraceMessage_0)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp();

		t.InitIpc();
		t.WaitForTestAppToExit();

		Assert::AreEqual("IXMLDOMDocument->load(NO_SUCH_FILE)", t.m_traces[0]);

		t.UnInitIpc();
	}

	TEST_METHOD(Integration_Verify_Incoming_TraceMessage_1)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp();

		t.InitIpc();
		t.WaitForTestAppToExit();

		Assert::AreEqual("IXMLDOMDocument->hasChildNodes()", t.m_traces[1]);

		t.UnInitIpc();
	}

	TEST_METHOD(Integration_Verify_Incoming_TraceMessage_2)
	{
		IntegrationTests t;
		BOOL started = t.StartTestApp();

		t.InitIpc();
		t.WaitForTestAppToExit();

		Assert::AreEqual("IXMLDOMDocument->Release()", t.m_traces[2]);

		t.UnInitIpc();
	}
};