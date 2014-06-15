#include "stdafx.h"
#include <pipeClient.h>
#include <pipeServer.h>


class TestPipes : public IReadDataCallback
{
  BYTE* m_data;
  DWORD m_len;
  HANDLE m_dataEvent;

  virtual void OnDataRead(BYTE* buffer, DWORD size)
  {
    m_data = buffer;
    m_len = size;
    ::SetEvent(m_dataEvent);
  }

  void TestServerInConnectModeCanDisconnect()
  {
    PipeServer server(this);

    DPUNIT_ISTRUE(server.InitializeServerSide(0x989));
    server.Disconnect();
  }

  void TestClientCanConnectToServerAndDisconnect()
  {
    PipeServer server(this);
    PipeClient client;

    DPUNIT_ISTRUE(server.InitializeServerSide(0x11));
    DPUNIT_ISTRUE(client.Connect(0x11));
    
    client.Disconnect();
    server.Disconnect();
  }

  void TestClientCanSendDataToServer()
  {
    PipeServer server(this);
    PipeClient client;

    char message[] = "the message..";
    m_len = 0;

    DPUNIT_ISTRUE(server.InitializeServerSide(GetCurrentProcessId()));
    DPUNIT_ISTRUE(client.Connect(GetCurrentProcessId()));
    DPUNIT_ISTRUE(client.Send((BYTE*)message, sizeof(message)));

    DPUNIT_EQUAL(WAIT_OBJECT_0, WaitForSingleObject(m_dataEvent, 500));
    DPUNIT_ISTRUE(m_len > 0);
    DPUNIT_EQUAL(0, memcmp(m_data, message, m_len));    // we received what was sent?
    
    client.Disconnect();
    server.Disconnect();
  }

  void TestClientCanReconnectAfterDisconnect()
  {
    PipeServer server(this);
    PipeClient client;

    DPUNIT_ISTRUE(server.InitializeServerSide(GetCurrentProcessId()));
    DPUNIT_ISTRUE(client.Connect(GetCurrentProcessId()));
    client.Disconnect();

    PipeClient client2;
    DPUNIT_ISTRUE(client2.Connect(GetCurrentProcessId()));

    char message[] = "the text..";
    client2.Send((BYTE*)message, sizeof(message));

    DPUNIT_EQUAL(WAIT_OBJECT_0, WaitForSingleObject(m_dataEvent, INFINITE));
    DPUNIT_EQUAL(0, memcmp(m_data, message, m_len));
  }

  void TestClientConnectsLaterThenServerStarts()
  {
    PipeServer server(this);
    PipeClient client;

    char message[] = "the message..";
    m_len = 0;

    DPUNIT_ISTRUE(server.InitializeServerSide(0x8877));
    DPUNIT_ISTRUE(client.Connect(0x8877));
    DPUNIT_ISTRUE(client.Send((BYTE*)message, sizeof(message)));
    DPUNIT_EQUAL(WAIT_OBJECT_0, WaitForSingleObject(m_dataEvent, 100));

    DPUNIT_ISTRUE(m_len > 0);
    DPUNIT_EQUAL(0, memcmp(m_data, message, m_len));

    client.Disconnect();
    server.Disconnect();
  }

  void TestServerCanSendResponse()
  {
    PipeServer server(this);
    PipeClient client;

    char message[] = "the lazy brown dog..";
    BYTE buffer[256];
    DWORD len = 0;

    DPUNIT_ISTRUE(server.InitializeServerSide(0xdead));
    DPUNIT_ISTRUE(client.Connect(0xdead));
    DPUNIT_ISTRUE(server.Send((BYTE*)message, sizeof(message)));
    DPUNIT_ISTRUE(client.Read(buffer, sizeof(buffer), &len));
    DPUNIT_ISTRUE(len > 0);
    DPUNIT_EQUAL(0, memcmp(buffer, message, len));
  }

public:
  TestPipes()
  {
    m_dataEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
  }

  ~TestPipes()
  {
    CloseHandle(m_dataEvent);
  }

  void Test()
  {
    TestServerInConnectModeCanDisconnect();
    TestClientCanConnectToServerAndDisconnect();
    TestClientCanSendDataToServer();
    TestClientConnectsLaterThenServerStarts();
    TestClientCanReconnectAfterDisconnect();
    TestServerCanSendResponse();
  }

};

void testPipes()
{
  TestPipes pipes;

  pipes.Test();
}
