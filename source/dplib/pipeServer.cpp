#include "stdafx.h"
#include "pipeServer.h"

CString PipeServer::GetPipeName(DWORD id)
{
  CString name;
  name.Format("\\\\.\\pipe\\dpcontrol_%d", id);

  return name;
}

PipeServer::PipeServer(IReadDataCallback* onReadCallback)
{
  m_OnReadCallback = onReadCallback;
  m_events[stopEvent] = ::CreateEvent(0, TRUE, FALSE, NULL);
  m_events[pipeEvent] = ::CreateEvent(0, TRUE, FALSE, NULL);
  m_pipe = INVALID_HANDLE_VALUE;
  m_readThread = NULL;
}

PipeServer::~PipeServer()
{
  Disconnect();

  CloseHandle(m_events[stopEvent]);
  CloseHandle(m_events[pipeEvent]);
}


DWORD PipeServer::ReadThreadProc(LPVOID pvThis)
{
  ((PipeServer*)pvThis)->ReadProc();
  
  return 0;
}

bool PipeServer::WaitForConnectionOrShutdownRequest(LPOVERLAPPED ol)
{
  if (ConnectNamedPipe(m_pipe, ol))
    return true;
  
  if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_events[stopEvent], 1))
    return false;

  return true; // no connection yet, but did not fail
}

bool PipeServer::Send(BYTE* data, DWORD size)
{
  DWORD written = 0;

  while (written < size)
  {
    DWORD bytes = 0;

    if (!::WriteFile(m_pipe, data + written, (size - written), &bytes, 0))
      return false;

    written += bytes;
  }

  return true;
}

void PipeServer::ReadProc()
{
  BYTE buffer[BUFFER_SIZE];
  OVERLAPPED ol = {0};
  ol.hEvent = m_events[pipeEvent];
  ol.Pointer = buffer;

  while (WaitForConnectionOrShutdownRequest(&ol))
  {
    while (1)
    {
      BYTE data[BUFFER_SIZE];
      DWORD read = 0;

      BOOL success = ReadFile(m_pipe, data, BUFFER_SIZE * sizeof(BYTE), &read, &ol);
      DWORD lastError = ::GetLastError();

      if (success)
      {
        if (read)
          m_OnReadCallback->OnDataRead(data, read);

        continue;
      }
      
      if (ERROR_IO_PENDING == lastError || ERROR_PIPE_LISTENING == lastError)
      {
        DWORD wait = ::WaitForMultipleObjects(numEvents, m_events, FALSE, INFINITE);

        if (WAIT_OBJECT_0 + stopEvent == wait)
        {
          break;
        }
        else if (WAIT_OBJECT_0 + pipeEvent == wait)
        {
          if (ERROR_IO_PENDING == lastError)
          {
            if (::GetOverlappedResult(m_pipe, &ol, &read, TRUE) && (read > 0))
              m_OnReadCallback->OnDataRead(data, read);
          }
        }
  
      }
      else // if (ERROR_BROKEN_PIPE == lastError)
      {
        ::DisconnectNamedPipe(m_pipe);

        break;
      }
  
    }
  }
}

void PipeServer::Disconnect()
{ 
  SetEvent(m_events[stopEvent]);
 
  if (INVALID_HANDLE_VALUE != m_pipe)
  {
    FlushFileBuffers(m_pipe); 
    DisconnectNamedPipe(m_pipe); 
    CloseHandle(m_pipe); 
    m_pipe = INVALID_HANDLE_VALUE;
  }

  if (m_readThread)
  {
    WaitForSingleObject(m_readThread, INFINITE);
    CloseHandle(m_readThread);
    m_readThread = NULL;
  }
}

bool PipeServer::InitializeServerSide(DWORD id)
{
  m_pipe = CreateNamedPipe( 
    (LPCTSTR)PipeServer::GetPipeName(id),            
          PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,       
          PIPE_TYPE_MESSAGE |      
          PIPE_READMODE_MESSAGE | 
          PIPE_WAIT,               
          PIPE_UNLIMITED_INSTANCES, 
          BUFFER_SIZE,                  
          BUFFER_SIZE,                
          0,                        
          NULL);                    

  if (INVALID_HANDLE_VALUE == m_pipe)
    return false;

  m_readThread = 
    ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PipeServer::ReadThreadProc, (LPVOID)this, 0, 0);

  return NULL != m_readThread;
}