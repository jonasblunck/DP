#include "stdafx.h"
#include "coms.h"
#include "IPCHelper.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(testEncodedTraceMessageCanBeDecoded)
{
  TEST_METHOD(IPC_TraceMessage_Action)
  {
	  int hookedFunctionId = 10;
	  int processId = 0xdead;
	  int returnValue = E_UNEXPECTED;
	  DPMessage* message;
	  char* traceText = "this is the trace message";

	  message = IPCHelper::EncodeTraceMessage(hookedFunctionId, processId, returnValue, traceText);

	  Assert::AreEqual((int)enTrace, (int)message->action);
  }

  TEST_METHOD(IPC_TraceMessage_ProcessId)
  {
	  int hookedFunctionId = 10;
	  int processId = 0xdead;
	  int returnValue = E_UNEXPECTED;
	  DPMessage* message;
	  char* traceText = "this is the trace message";

	  message = IPCHelper::EncodeTraceMessage(hookedFunctionId, processId, returnValue, traceText);

	  Assert::AreEqual(static_cast<DWORD>(processId), message->traceMessage.pid);
  }

  TEST_METHOD(IPC_TraceMessage_ReturnMessage)
  {
	  int hookedFunctionId = 10;
	  int processId = 0xdead;
	  int returnValue = E_UNEXPECTED;
	  DPMessage* message;
	  char* traceText = "this is the trace message";

	  message = IPCHelper::EncodeTraceMessage(hookedFunctionId, processId, returnValue, traceText);

	  Assert::AreEqual(returnValue, message->traceMessage.returnValue);
  }

  TEST_METHOD(IPC_TraceMessage_TraceText)
  {
	  int hookedFunctionId = 10;
	  int processId = 0xdead;
	  int returnValue = E_UNEXPECTED;
	  DPMessage* message;
	  char* traceText = "this is the trace message";

	  message = IPCHelper::EncodeTraceMessage(hookedFunctionId, processId, returnValue, traceText);

	  Assert::AreEqual(traceText, IPCHelper::GetTraceMessageFromMessage(message));
  }
};
