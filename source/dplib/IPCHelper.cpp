#include "stdafx.h"
#include "IPCHelper.h"

DPMessage* IPCHelper::EncodeTraceMessage(int hookedFunctionId, DWORD processId, int returnValue, const char* traceText)
{
  int traceLen = lstrlen(traceText) + 1;
  int messageLen = sizeof(DPMessage) + traceLen;
  DPMessage* message = (DPMessage*)new BYTE[messageLen];

  message->len = messageLen;
  message->action = enTrace;
  message->id = hookedFunctionId;
  message->traceMessage.id = hookedFunctionId;
  message->traceMessage.returnValue = returnValue;
  message->traceMessage.pid = processId;
  lstrcpyn((LPTSTR)(&message->traceMessage.trace), traceText, traceLen);

  return message;
}

CString IPCHelper::GetTraceMessageFromMessage(DPMessage* message)
{
  CString traceMessage;

  if (message->action == enTrace)
    traceMessage = (LPCTSTR)(&message->traceMessage.trace);

  return traceMessage;
}
