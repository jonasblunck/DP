
#pragma once
#pragma comment(lib, "Ws2_32.lib")

class ITransportCallback
{
public:
  virtual void OnConnection(DWORD context) = 0;
  virtual void OnDataReceived(DWORD context, BYTE* buffer, int length) = 0;
};

class ITransport
{
public:
  virtual bool Initialize(ITransportCallback* callback) = 0;
  virtual void Uninitialize() = 0;
};

class ConnectionBuffer : public OVERLAPPED
{
  BYTE* m_buffer;
public:

  ConnectionBuffer();
  BYTE* GetBuffer();
  int GetBufferSize() const;
};

//
// my IPC implementation
//
class IPC : ITransport
{
  SOCKET m_socket;
  HANDLE m_completionPort;
  HANDLE m_connectThread;
  HANDLE m_readThread;
  ITransportCallback* m_callback;

  static bool InitWSA();
  bool InitializeSocket();
  SOCKET Connect();

  static DWORD ConnectThread(DWORD pvThis);
  static DWORD ReadThread(DWORD pvThis);

  void ConnectProc();
  void ReadIncomingProc();
  void IssueReceive(ConnectionBuffer* buffer, SOCKET socket);

public:

  IPC();
  ~IPC();

  virtual bool Initialize(ITransportCallback* callback);
  virtual void Uninitialize();
};
