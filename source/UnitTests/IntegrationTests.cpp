#include "stdafx.h"
#include "ipc.h"
#include "IPCHelper.h"
#include "CBuffer.h"
#include <atlcoll.h>

class IntegrationTests : public ITransportCallback
{
  HANDLE m_testApp;
  IPC m_ipc;
  ATL::CAtlArray<CString> m_traces;
  CBuffer<BYTE> m_buffer;

  virtual void OnConnection(DWORD context) {}
  virtual void OnDataReceived(DWORD context, BYTE* buffer, int length)
  {
    m_buffer.Append(buffer, length);

    while (BufferContainsFullMessage())
    {
      DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

      // data->traceMessage.returnValue holds return values (HRESULT or AddRef/Release return values)

      m_traces.Add(IPCHelper::GetTraceMessageFromMessage(data));

      int trailBufSize = m_buffer.size() - data->len;
      BYTE* tmp = m_buffer.detach();
      m_buffer.Append(tmp + data->len, trailBufSize);

      delete [] tmp;
    }
  }

  bool BufferContainsFullMessage()
  {
    DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

    if (m_buffer.get() != NULL && m_buffer.size() >= data->len)
      return true;

    return false;
  }

  BOOL StartTestApp()
  {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    BOOL started = ::CreateProcess(NULL, "TestApp.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
    DPUNIT_ISTRUE(started);
    
    m_testApp = pi.hProcess;

    return started;
  }

  void WaitForTestAppToExit()
  {
    WaitForSingleObject(m_testApp, INFINITE);
  }

  void VerifyIncomingTraceMessages()
  {
    DPUNIT_STR_EQUAL("IXMLDOMDocument->load(NO_SUCH_FILE)", m_traces[0]);
    DPUNIT_STR_EQUAL("IXMLDOMDocument->hasChildNodes()", m_traces[1]);
    DPUNIT_STR_EQUAL("IXMLDOMDocument->Release()", m_traces[2]);
  }

public:
  void Run()
  {
    m_ipc.Initialize(this); // this will allow me to retrieve incoming trace messages

    if (StartTestApp())
    {
      WaitForTestAppToExit();
      VerifyIncomingTraceMessages();
    }

    m_ipc.Uninitialize();
  }
};

void integrationTests()
{
  IntegrationTests t;
  t.Run();
}