#ifndef __TRACESINK_H__
#define __TRACESINK_H__

#include "ipc.h"
#include "CBuffer.h"

class CTraceSink : public ITransportCallback
{
public:
	CTraceSink();
	~CTraceSink();

	HRESULT Start();
	HRESULT Stop();

private:
  virtual void OnConnection(DWORD context);
  virtual void OnDataReceived(DWORD context, BYTE* buffer, int length);

  bool BufferContainsFullMessage();

  IPC m_ipc;
  CBuffer<BYTE> m_buffer;
};

#endif //__TRACESINK_H__
