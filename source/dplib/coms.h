#pragma once

typedef enum Action { hookRequest, hookResponse, traceMessage, unHookRequest } Action;

struct HookRequest
{
  char module[512];
  DWORD rva;
  char paramDefinition[128]; 
};

struct HookResponse
{
  long id;
  bool success;
};

struct TraceMessage
{
  long id;
  DWORD pid;
  int returnValue;
  char* trace; // make it big enough upon allocation!
};

struct DPMessage
{
  int len;
  int action;
  int id; // either transaction ID or hook-id (for traceToggle actions)
  union
  {
    HookRequest hookRequest;
    HookResponse hookResponse;
    TraceMessage traceMessage;
  };
};

struct TRACEMESSAGE
{
  int messageLength; // length of TRACEMESSAGE + following string containing the trace of the arguments
  DWORD dwPID;
  DWORD dwHookID;
  char arguments[256];
};

typedef enum DPAction { enNone = 0, enTrace = 1, enPause = 2 } DPAction;