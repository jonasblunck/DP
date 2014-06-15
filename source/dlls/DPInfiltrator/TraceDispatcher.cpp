#include "stdafx.h"
#include "tracedispatcher.h"
#include <atlstr.h>
#include "IPCHelper.h"

#pragma comment (lib, "ws2_32.lib")

CTraceDispatcher::CTraceDispatcher(void)
{
  m_hIOCP = NULL;
  m_dwTID = 0;
  m_recipient = INVALID_SOCKET;
}

CTraceDispatcher::~CTraceDispatcher(void)
{
}

void CTraceDispatcher::SendSlotMessage(BYTE* data, int length)
{
  if (INVALID_SOCKET == m_recipient)
  {
    m_recipient = socket(PF_INET, SOCK_STREAM, 0);

    struct hostent *hp;
    hp = gethostbyname(_T("localhost"));
    SOCKADDR_IN SockAddrIn;

    memset(&SockAddrIn, 0, sizeof(SockAddrIn));
    memcpy(&(SockAddrIn.sin_addr),hp->h_addr,hp->h_length);
    SockAddrIn.sin_family = PF_INET;
    SockAddrIn.sin_port = htons((unsigned short)9214);

    if (SOCKET_ERROR == connect(m_recipient, (struct sockaddr *)&SockAddrIn, sizeof(SockAddrIn)))
    {
      closesocket(m_recipient);
      m_recipient = INVALID_SOCKET;
    }
  }

  //
  // send everything on the wire
  //
  int iBytesSent = 0;
  while (iBytesSent < length)
  {
    int sent = send(m_recipient, (LPCTSTR)(data + iBytesSent), length - iBytesSent, 0);

    if (SOCKET_ERROR == sent)
    {
      closesocket(m_recipient);
      m_recipient = INVALID_SOCKET;

      break;
    }

    iBytesSent += sent;
  }
}

DWORD __stdcall CTraceDispatcher::TraceThread(LPVOID pThis)
{
  CTraceDispatcher* p = reinterpret_cast<CTraceDispatcher*>(pThis);
  
  return p->WorkerProc();
}

DWORD CTraceDispatcher::WorkerProc() 
{
  ATLASSERT(m_hIOCP);
  
  DWORD dwBytes = 0;
  ULONG ulKey = 0;
  OVERLAPPED* pOverlapped = NULL;

  DWORD dwPID = GetCurrentProcessId();

  while (GetQueuedCompletionStatus(m_hIOCP, &dwBytes, &ulKey, &pOverlapped, INFINITE))
  {
    if (!dwBytes)
      break;

    DPMessage* message = reinterpret_cast<DPMessage*>(pOverlapped);

    SendSlotMessage((BYTE*)message, message->len);
      
    delete message;
  }

  return 0;
}

DWORD CTraceDispatcher::GetDispatcherThreadID()
{
  return m_dwTID;
}

void CTraceDispatcher::OnHookedFunction(long id, const CString& arguments, int returnValue)
{
  ATLASSERT(m_hIOCP);

  if (::GetCurrentThreadId() != m_dwTID) // we must not trace if call steems from our own worker thread!
  {
    DPMessage* message = IPCHelper::EncodeTraceMessage(id, ::GetCurrentProcessId(),
      returnValue, (LPCTSTR)arguments);

    PostQueuedCompletionStatus(m_hIOCP, 1, id, reinterpret_cast<LPOVERLAPPED>(message));
  }
}

void CTraceDispatcher::Terminate()
{
  if (m_hIOCP)
  {
    PostQueuedCompletionStatus(m_hIOCP, 0, 0, NULL);

    CloseHandle(m_hIOCP);
    m_hIOCP = NULL;
  }
}

void CTraceDispatcher::Init()
{
  m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

  CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CTraceDispatcher::TraceThread, (LPVOID)this, 0, &m_dwTID);
}
