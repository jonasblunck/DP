#include "stdafx.h"
#include "TraceSink.h"
#include "mainfrm.h"
#include "IPCHelper.h"

#include "TracePacket.h"
#include "ItemData.h"

CTraceSink::CTraceSink()
{
}

CTraceSink::~CTraceSink()
{
}

HRESULT CTraceSink::Start()
{
  m_ipc.Initialize(static_cast<ITransportCallback*>(this));

  return S_OK;
}

HRESULT CTraceSink::Stop()
{	
  m_ipc.Uninitialize();

	return S_OK;
}

void CTraceSink::OnConnection(DWORD context)
{
}

bool CTraceSink::BufferContainsFullMessage()
{
  DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

  if (m_buffer.get() != NULL && m_buffer.size() >= data->len)
    return true;

  return false;
}

void CTraceSink::OnDataReceived(DWORD context, BYTE* buffer, int length)
{
  m_buffer.Append(buffer, length); // I could probably get away not copying stuff around..
 
  while (BufferContainsFullMessage())
  {
    DPMessage* data = reinterpret_cast<DPMessage*>(m_buffer.get());

    CString traceText = (LPCTSTR)IPCHelper::GetTraceMessageFromMessage(data);

    TraceItemData* pItemData = new TraceItemData(data->traceMessage.pid, data->traceMessage.id, (LPCTSTR)traceText);
  	CMainFrame::Instance().PostMessage(WM_DP_TRACE_RECVD, (WPARAM)pItemData);

    int trailBufSize = m_buffer.size() - data->len;
    BYTE* tmp = m_buffer.detach();
    m_buffer.Append(tmp + data->len, trailBufSize);

    delete [] tmp;
  }

  
}

