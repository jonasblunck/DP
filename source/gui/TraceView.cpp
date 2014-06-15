#include "stdafx.h"

#include "TraceView.h"
#include "HookedStructures.h"

CTraceView::CTraceView()
{
	m_bIsDirty = FALSE;
	m_cTraces = 0;
}

LRESULT CTraceView::OnCreate(LPCREATESTRUCT)
{
	if (DefWindowProc() != 0) return -1;

	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT);

	AddColumn(_T("#"), TV_COL_TRACE_INDEX);
	AddColumn(_T("Time"), TV_COL_TIME);
	AddColumn(_T("Process"), TV_COL_PID);
	AddColumn(_T("Module"), TV_COL_MODULE);
	AddColumn(_T("RVA"), TV_COL_RVA);
	AddColumn(_T("Function"), TV_COL_EXPORT);
	AddColumn(_T("Event"), TV_COL_MESSAGE);
  AddColumn(_T("Arguments trace"), TV_COL_ARGTRACE);

	ResizeColumnHeaders();

	return 0;
}

BOOL CTraceView::OnTraceCallback(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR argTrace, DPAction action)
{
	return AddTraceItem(dwPID, pszModule, dwRVA, pszFunction, argTrace, ResolveAction(action));
}

BOOL CTraceView::OnHook(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction)
{
	return AddTraceItem(dwPID, pszModule, dwRVA, pszFunction, NULL, _T("Hooked"));
}

BOOL CTraceView::OnUnhook(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction)
{
	return AddTraceItem(dwPID, pszModule, dwRVA, pszFunction, NULL, _T("Unhooked"));
}

BOOL CTraceView::Trace(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR pszMessage)
{
	return AddTraceItem(dwPID, pszModule, dwRVA, pszFunction, NULL, pszMessage);
}

BOOL CTraceView::CopyToClipboard()
{
	CWaitCursor wc;

	// Write all items as a tab-delimited string-list to a stream
	std::strstream clipboardStream;
	int nItem = GetNextItem(-1, LVNI_SELECTED);
	if(nItem == -1)
	{
		// Copy all of the items
		for(nItem = 0; nItem < GetItemCount(); ++nItem)
		{
			WriteItemToStream(nItem, clipboardStream);
		}
	}
	else
	{
		// Copy only selected items
		for(; nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
		{
			WriteItemToStream(nItem, clipboardStream);
		}
	}

	// Terminate string
	clipboardStream << ends;

	// Copy the whole thing to the clipboard
	BOOL bRet = FALSE;
	if(OpenClipboard())
	{
		EmptyClipboard();

		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, (SIZE_T)(clipboardStream.pcount() + sizeof(char)));
		if(hData != NULL)
		{
			char* pszBuffer = (char*)GlobalLock(hData);
			if(pszBuffer)
			{
				memcpy(pszBuffer, clipboardStream.str(), (SIZE_T)clipboardStream.pcount());
				pszBuffer[clipboardStream.pcount() - 1] = 0;
				GlobalUnlock(hData);

				if(SetClipboardData(CF_TEXT, hData))
				{
					bRet = TRUE;
				}
			}
		}

		CloseClipboard();
		GlobalFree(hData);
	}

	return bRet;
}

BOOL CTraceView::IsDirty()
{
	return m_bIsDirty;
}

BOOL CTraceView::SaveToFile(LPCTSTR pszFilename)
{
	BOOL bRet = FALSE;

	// Copy all of the items
	std::strstream fileStream;
	for(int nItem = 0; nItem < GetItemCount(); ++nItem)
	{
		WriteItemToStream(nItem, fileStream);
	}

	// Terminate string
	fileStream << ends;

	// Write stream contents to file
	SmartFileHandle hFile = CreateFile(pszFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
	if(hFile.IsValid())
	{
		DWORD dwWritten = 0;
		if(WriteFile(hFile, fileStream.str(), (DWORD)fileStream.pcount(), &dwWritten, NULL))
		{
			ATLASSERT(fileStream.pcount() == dwWritten);
			bRet = TRUE;
		}
	}

	return bRet;
}

BOOL CTraceView::GetTraceData(int nItem, DWORD& rdwPID, CString& rstrModule, DWORD& rdwRVA, CString& rstrFunctionName)
{
	CString strPID, strModule, strRVA, strFunctionName;

	if(!GetItemText(nItem, TV_COL_PID, strPID))
	{
		return FALSE;
	}

	if(!GetItemText(nItem, TV_COL_MODULE, strModule))
	{
		return FALSE;
	}

	if(!GetItemText(nItem, TV_COL_RVA, strRVA))
	{
		return FALSE;
	}

	strRVA = strRVA.Right(strRVA.GetLength() - 2);

	if(!GetItemText(nItem, TV_COL_EXPORT, strFunctionName))
	{
		return FALSE;
	}

	rdwPID = _tcstoul(strPID, NULL, 10);
	rstrModule = strModule;
	rdwRVA = _tcstoul(strRVA, NULL, 16);
	rstrFunctionName = strFunctionName;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////
/// Private members
void CTraceView::ResizeColumnHeaders()
{
	SetColumnWidth(TV_COL_TRACE_INDEX, 30);
	SetColumnWidth(TV_COL_TIME, 80);
	SetColumnWidth(TV_COL_PID, 60);
	SetColumnWidth(TV_COL_MODULE, 200);
	SetColumnWidth(TV_COL_RVA, 80);
	SetColumnWidth(TV_COL_EXPORT, 210);
  SetColumnWidth(TV_COL_ARGTRACE, 300);

	
	SetColumnWidth(TV_COL_MESSAGE, 80);
}

CString CTraceView::ResolveAction(DPAction action)
{
	switch(action)
	{
	case enNone:
		return _T("");
	case enTrace:
		return _T("Trace");
	}

	return _T("Undefined");
}

CString CTraceView::GetCurrentTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strTime;
	strTime.Format(_T("%02u:%02u:%02u.%03u"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	return strTime;
}

void CTraceView::WriteItemToStream(int nItem, std::strstream& stream)
{
	CString strIndex, strTimestamp, strPID, strModule, strFunction, strMessage, strRVA, strArgTrace;

	GetItemText(nItem, TV_COL_TRACE_INDEX, strIndex);
	GetItemText(nItem, TV_COL_TIME, strTimestamp);
	GetItemText(nItem, TV_COL_PID, strPID);
	GetItemText(nItem, TV_COL_MODULE, strModule);
	GetItemText(nItem, TV_COL_RVA, strRVA);
	GetItemText(nItem, TV_COL_EXPORT, strFunction);
	GetItemText(nItem, TV_COL_ARGTRACE, strArgTrace);
	GetItemText(nItem, TV_COL_MESSAGE, strMessage);

	stream << (LPCTSTR)strIndex << "\t";
	stream << (LPCTSTR)strTimestamp << "\t";
	stream << (LPCTSTR)strPID << "\t";
	stream << (LPCTSTR)strModule << "\t";
	stream << (LPCTSTR)strRVA << "\t";
	stream << (LPCTSTR)strFunction << "\t";
	stream << (LPCTSTR)strArgTrace<< "\t";
	stream << (LPCTSTR)strMessage << "\r\n";
}

BOOL CTraceView::AddTraceItem(DWORD dwPID, LPCTSTR pszModule, DWORD dwRVA, LPCTSTR pszFunction, LPCTSTR argTrace, LPCTSTR pszMessage)
{
	CString strPID;
	strPID.Format(_T("%lu"), dwPID);

	CString strRVA;
	if(dwRVA)
	{
		strRVA.Format(_T("0x%06X"), dwRVA);
	}

	CString strCurrentIndex;
	strCurrentIndex.Format(_T("%lu"), m_cTraces);

	int nItem = AddItem(GetItemCount(), TV_COL_TRACE_INDEX, strCurrentIndex);
	AddItem(nItem, TV_COL_TIME, GetCurrentTime());
	AddItem(nItem, TV_COL_PID, strPID);
	AddItem(nItem, TV_COL_MODULE, pszModule);
	AddItem(nItem, TV_COL_RVA, strRVA);
	AddItem(nItem, TV_COL_EXPORT, pszFunction);
	AddItem(nItem, TV_COL_MESSAGE, pszMessage);
  AddItem(nItem, TV_COL_ARGTRACE, argTrace);

	m_bIsDirty = TRUE;
	
	if(COptionsStorage::Instance().GetAutoScroll())
	{
		EnsureVisible(nItem, TRUE);
	}

	InterlockedIncrement(reinterpret_cast<LPLONG>(&m_cTraces));
	return TRUE;
}

