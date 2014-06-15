
#pragma once

#define BUFFER_SIZE 1024

class IReadDataCallback
{
public:
  virtual void OnDataRead(BYTE* buffer, DWORD size) = 0;
};

class PipeServer
{
  enum { stopEvent = 0, pipeEvent = 1, numEvents = 2 };
  HANDLE m_events[numEvents];

  HANDLE m_pipe;
  HANDLE m_readThread;
  IReadDataCallback* m_OnReadCallback;

  static DWORD ReadThreadProc(LPVOID pvThis);
  void ReadProc();
  bool WaitForConnectionOrShutdownRequest(LPOVERLAPPED ol);

public:
  PipeServer(IReadDataCallback* onReadCallback);
  ~PipeServer();
  
  bool InitializeServerSide(DWORD id);
  bool Send(BYTE* data, DWORD size);
  void Disconnect();

  static CString GetPipeName(DWORD id);
};