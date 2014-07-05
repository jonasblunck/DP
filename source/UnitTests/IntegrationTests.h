#include "stdafx.h"
#include "ipc.h"
#include "IPCHelper.h"
#include "CBuffer.h"
#include <atlcoll.h>

class IntegrationTests : public ITransportCallback
{
private:
	HANDLE m_testApp;
	IPC m_ipc;
	CBuffer<BYTE> m_buffer;

	virtual void OnConnection(DWORD context) {}
	virtual void OnDataReceived(DWORD context, BYTE* buffer, int length)
	{
		m_buffer.Append(buffer, length);

		while (BufferContainsFullMessage())
		{
			DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

			m_traces.Add(IPCHelper::GetTraceMessageFromMessage(data));

			int trailBufSize = m_buffer.size() - data->len;
			BYTE* tmp = m_buffer.detach();
			m_buffer.Append(tmp + data->len, trailBufSize);

			delete[] tmp;
		}
	}

	bool BufferContainsFullMessage()
	{
		DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

		if (m_buffer.get() != NULL && m_buffer.size() >= data->len)
			return true;

		return false;
	}

public:
	ATL::CAtlArray<CString> m_traces;

	BOOL StartTestApp()
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		memset(&si, 0, sizeof(si));
		memset(&pi, 0, sizeof(PROCESS_INFORMATION));
		si.cb = sizeof(STARTUPINFO);

		BOOL started = ::CreateProcess(NULL, "TestApp.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

		m_testApp = pi.hProcess;

		return started;
	}

	void WaitForTestAppToExit()
	{
		WaitForSingleObject(m_testApp, INFINITE);
	}

	void InitIpc()
	{
		m_ipc.Initialize(this);		
	}

	void UnInitIpc()
	{
		m_ipc.Uninitialize();
	}
};
