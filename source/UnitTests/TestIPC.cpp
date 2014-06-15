#include "stdafx.h"
#include "coms.h"
#include "IPCHelper.h"

void testEncodedTraceMessageCanBeDecoded()
{
  int hookedFunctionId = 10;
  int processId = 0xdead;
  int returnValue = E_UNEXPECTED;
  char* traceText = "this is the trace message";

  DPMessage* message = IPCHelper::EncodeTraceMessage(hookedFunctionId, processId, returnValue, traceText);

  DPUNIT_EQUAL(enTrace, message->action);
  DPUNIT_EQUAL(processId, message->traceMessage.pid);
  DPUNIT_EQUAL(returnValue, message->traceMessage.returnValue);
  DPUNIT_STR_EQUAL(traceText, IPCHelper::GetTraceMessageFromMessage(message));

}

void testIPC()
{
  testEncodedTraceMessageCanBeDecoded();
}
