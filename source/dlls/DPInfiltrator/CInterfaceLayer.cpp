
#include "stdafx.h"
#include "Infiltrator.h"
#include "CBuffer.h"
#include "PipeServer.h"
#include <memory>
#include "HookCoCreateInstance.h"
#include "DynHooker.h"

class ComServer : private IReadDataCallback
{
  std::auto_ptr<PipeServer> m_pipeServer;
  CBuffer<BYTE> m_buffer;

  virtual void OnDataRead(BYTE* buffer, DWORD size)
  {
    m_buffer.Append(buffer, size);  // I could avoid unnecessary copying here by looking at buffer directly (but deal with in-complete streams)
    DPMessage* message = reinterpret_cast<DPMessage*>(m_buffer.get());

    if (m_buffer.size() == message->len)
    {
      HandleReceivedMessage(message);
      m_buffer.clear();
    }
    else
    {
      OutputDebugString("****** LOST MESSAGE *****");
    }
  }

  void HandleReceivedMessage(DPMessage* message)
  {
    Infiltrator infiltrator;

    if (message->action == hookRequest)
    {
      long id = 0;
      HRESULT hr = infiltrator.SetupTrace(CComBSTR(message->hookRequest.module), message->hookRequest.rva, CComBSTR(message->hookRequest.paramDefinition), &id);

      DPMessage response = {0};
      response.action = hookResponse;
      response.id = message->id;
      response.len = sizeof(DPMessage);
      response.hookResponse.id = id;
      response.hookResponse.success = SUCCEEDED(hr) ? true : false;

      m_pipeServer->Send((BYTE*)&response, sizeof(DPMessage));
    }
    else if (message->action == unHookRequest)
    {
      long idToPause = message->id;
      
      if (idToPause)
        CDynHooker().SetActive((LPVOID)idToPause, false);
    }
  }


public:

  void Init()
  {
    DWORD serverId = ::GetCurrentProcessId();
    m_pipeServer = std::auto_ptr<PipeServer>(new PipeServer(this));
    m_pipeServer->InitializeServerSide(serverId);
  }

  void SendMessage(DPMessage* message)
  {
    m_pipeServer->Send(reinterpret_cast<BYTE*>(message), message->len);
  }

};

static ComServer comServer;

void InitInfiltrator();

void __stdcall InitializeOnLoad()
{
  comServer.Init(); 
  InitInfiltrator(); 

  CHookCoCreateInstance::Hook();
}

