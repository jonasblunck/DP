
#include "stdafx.h"
#include "ipc.h"

#define READBUFFER_SIZE 1024 * 10

ConnectionBuffer::ConnectionBuffer() : OVERLAPPED()
{
  memset(static_cast<OVERLAPPED*>(this), 0, sizeof(OVERLAPPED));
  memset(&m_buffer, 0, sizeof(WSABUF));

  const int bufferSize = READBUFFER_SIZE;
  m_buffer = new BYTE[bufferSize];;
}

BYTE* ConnectionBuffer::GetBuffer() 
{
  return m_buffer;
}

int ConnectionBuffer::GetBufferSize() const
{
  const int bufferSize = READBUFFER_SIZE;

  return bufferSize;
}

IPC::IPC() 
{
  m_completionPort = NULL;
  m_connectThread = NULL;
  m_socket = INVALID_SOCKET;
  m_callback = NULL;
  m_readThread = NULL;
}

IPC::~IPC()
{
}

bool IPC::InitWSA()
{
  WORD wVersionRequested;
  WSADATA wsaData;

  wVersionRequested = MAKEWORD(2, 2);

  if (WSAStartup(wVersionRequested, &wsaData))
    return false; // not any usable WinSock DLL

  if (LOBYTE( wsaData.wVersion ) != 2 ||
    HIBYTE( wsaData.wVersion ) != 2 )
  {
    WSACleanup();
    return false;
  }

  return true;
}

void IPC::Uninitialize()
{
  PostQueuedCompletionStatus(m_completionPort, 0, 0, 0); // tell read thread to quit..

  shutdown(m_socket, 0);
  closesocket(m_socket);
  m_socket = INVALID_SOCKET;

  WaitForSingleObject(m_connectThread, INFINITE);
  CloseHandle(m_connectThread);

  WaitForSingleObject(m_readThread, INFINITE);
  CloseHandle(m_readThread);
}

bool IPC::InitializeSocket()
{
  const int ipcPort = 9214;
  m_socket = socket(PF_INET, SOCK_STREAM, 0);

  if (INVALID_SOCKET != m_socket)
  {
    sockaddr_in sin = {0};
    memset(&sin, 0, sizeof(sockaddr_in));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(ipcPort);

    if (SOCKET_ERROR != bind(m_socket, (sockaddr *)&sin, sizeof(sockaddr_in)))
    {
      if (listen(m_socket, 200) != SOCKET_ERROR)
        return true;
    }
  }

  return false;
}

bool IPC::Initialize(ITransportCallback* callback)
{
  m_callback = callback;

  if (!IPC::InitWSA())
    return false;

  if (!InitializeSocket())
    return false;

  if (NULL == (m_completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0)))
    return false;

  m_connectThread = 
    ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IPC::ConnectThread, (void*)this, 0, 0);

  m_readThread = 
    ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)IPC::ReadThread, (void*)this, 0, 0);

  return true;
}

DWORD IPC::ConnectThread(DWORD pvThis)
{
  ((IPC*)pvThis)->ConnectProc();

  return 0;
}

DWORD IPC::ReadThread(DWORD pvThis)
{
  ((IPC*)pvThis)->ReadIncomingProc();

  return 0;
}

void IPC::ReadIncomingProc()
{
  DWORD bytesRead = 0;
  ULONG key = 0;
  LPOVERLAPPED olInfo = NULL;

  while (true)
  {
    DWORD status = GetQueuedCompletionStatus(m_completionPort, &bytesRead, &key, (LPOVERLAPPED*)&olInfo, INFINITE);

    if (status && !key && !olInfo && !bytesRead)
      break; // we are done!

    if (olInfo)
    {
      ConnectionBuffer* buffer = (ConnectionBuffer*)olInfo;
      m_callback->OnDataReceived((DWORD)key, (BYTE*)buffer->GetBuffer(), bytesRead);

      IssueReceive(buffer, (SOCKET)key);
    }
  }
}

#pragma warning(disable:4700)
void IPC::ConnectProc()
{
  ATLASSERT(NULL != m_completionPort);

  SOCKET connection = INVALID_SOCKET;

  while (INVALID_SOCKET != (connection = Connect()))
  {
    if (NULL != CreateIoCompletionPort((HANDLE)connection, m_completionPort, (ULONG_PTR)connection, 0))
    {
      // connection established, setup receive buffer and start reading.
      ConnectionBuffer* buffer = new ConnectionBuffer();
      IssueReceive(buffer, connection);
    }
  }
}
#pragma warning(default:4700)


SOCKET IPC::Connect()
{
  ATLASSERT(INVALID_SOCKET != m_socket);

  sockaddr addr;
  memset(&addr, 0, sizeof(addr));
  int len = sizeof(addr);

  return accept(m_socket, &addr, &len);
}

void IPC::IssueReceive(ConnectionBuffer* buffer, SOCKET socket)
{
  DWORD dummy = 0;
  DWORD flags = 0;
  WSABUF wsabuf = {0};
  wsabuf.buf = (CHAR*)buffer->GetBuffer();
  wsabuf.len = buffer->GetBufferSize();

  WSARecv(socket, &wsabuf, 1, &dummy, &flags, static_cast<OVERLAPPED*>(buffer), 0);
}