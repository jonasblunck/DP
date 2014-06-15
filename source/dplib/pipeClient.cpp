#include "stdafx.h"
#include "pipeClient.h"
#include "pipeServer.h"

PipeClient::PipeClient()
{
  m_pipe = INVALID_HANDLE_VALUE;
}

PipeClient::~PipeClient()
{
  Disconnect();
}

bool PipeClient::Send(BYTE* data, DWORD len)
{
  DWORD sent = 0;

  if (!WriteFile(m_pipe, data, len, &sent, NULL))
    return false;

  return (sent == len);
}

bool PipeClient::Read(BYTE* buffer, DWORD bufferSize, DWORD* read)
{
  if (!::ReadFile(m_pipe, buffer, bufferSize, read, 0))
    return false;

  return true;
}

bool PipeClient::Connect(DWORD serverId, int numRetriesOnFailure)
{
  for (int i = 0; i < (numRetriesOnFailure + 1); ++i)
  {
    if (DoConnect(serverId))
      return true;

    Sleep(250);
  }

  return false;
}

bool PipeClient::DoConnect(DWORD serverId)
{
  while (1)
  {
    m_pipe = CreateFile( 
           (LPCTSTR)PipeServer::GetPipeName(serverId),   // pipe name 
           GENERIC_READ | GENERIC_WRITE, 
           0,              // no sharing 
           NULL,           // default security attributes
           OPEN_EXISTING,  // opens existing pipe 
           0,              // default attributes 
           NULL);          // no template file 
   
    if (INVALID_HANDLE_VALUE != m_pipe)
      break;

    if (ERROR_PIPE_BUSY != ::GetLastError())
      return false;

    if (!::WaitNamedPipe((LPCTSTR)PipeServer::GetPipeName(serverId), 1000 * 5))
      return false;
  }

  // we want to be able to both read and write from the pipe..
  DWORD dwMode = PIPE_READMODE_MESSAGE; 
  BOOL success = SetNamedPipeHandleState(m_pipe, &dwMode, NULL, NULL);

  return (TRUE == success);
}

void PipeClient::Disconnect()
{
  if (m_pipe != INVALID_HANDLE_VALUE)
  {
    CloseHandle(m_pipe);
    m_pipe = INVALID_HANDLE_VALUE;
  }

}