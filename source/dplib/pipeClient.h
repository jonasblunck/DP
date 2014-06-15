
#pragma once

class PipeClient
{
  HANDLE m_pipe;

  bool DoConnect(DWORD serverId);
public:
  PipeClient();
  ~PipeClient();

  bool Connect(DWORD serverId, int numRetriesOnFailure = 0);
  void Disconnect();
  bool Send(BYTE* data, DWORD len);
  bool Read(BYTE* buffer, DWORD bufferSize, DWORD* read);
};