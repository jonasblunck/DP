#pragma once
#include "coms.h"

class IPCHelper
{
public:
  static DPMessage* EncodeTraceMessage
    (int hookedFunctionId, DWORD processId, int returnValue, const char* traceText);

  static CString GetTraceMessageFromMessage(DPMessage* message);

};