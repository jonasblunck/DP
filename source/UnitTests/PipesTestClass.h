#include "stdafx.h"
#include <pipeClient.h>
#include <pipeServer.h>

class PipesTestClass : public IReadDataCallback
{
public:
	BYTE* m_data;
	DWORD m_len;
	HANDLE m_dataEvent;

	virtual void OnDataRead(BYTE* buffer, DWORD size)
	{
		m_data = buffer;
		m_len = size;
		::SetEvent(m_dataEvent);
	}
};