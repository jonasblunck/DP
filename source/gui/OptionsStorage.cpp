#include "stdafx.h"
#include "OptionsStorage.h"

// Private constructor
COptionsStorage::COptionsStorage()
	:	m_bStripSuffixForMsdn(TRUE),
		m_bUndecorateSymbols(FALSE),
		m_bEnableSeDebugPriv(TRUE),
		m_bPauseWhileHooking(TRUE),
		m_bAutoScroll(TRUE),
		m_bShowStack(FALSE)
{
	LoadOptions();
}

// Public singleton accessor
COptionsStorage& COptionsStorage::Instance()
{
	static COptionsStorage instance;
	return instance;
}

// Accessors
CString& COptionsStorage::GetDependsPath()
{
	return m_strDependsPath;
}

BOOL COptionsStorage::GetEnableSeDebugPriv()
{
	return m_bEnableSeDebugPriv;
}

BOOL COptionsStorage::GetStripSuffixForMsdn()
{
	return m_bStripSuffixForMsdn;
}

BOOL COptionsStorage::GetUndecorateSymbols()
{
	return m_bUndecorateSymbols;
}

BOOL COptionsStorage::GetPauseWhileHooking()
{
	return m_bPauseWhileHooking;
}

BOOL COptionsStorage::GetAutoScroll()
{
	return m_bAutoScroll;
}

BOOL COptionsStorage::GetShowStack()
{
	return m_bShowStack;
}

void COptionsStorage::SetDependsPath(LPCTSTR pszPath)
{
	m_strDependsPath = pszPath;
}

void COptionsStorage::SetEnableSeDebugPriv(BOOL bValue)
{
	m_bEnableSeDebugPriv = bValue;
}

void COptionsStorage::SetStripSuffixForMsdn(BOOL bValue)
{
	m_bStripSuffixForMsdn = bValue;
}

void COptionsStorage::SetUndecorateSymbols(BOOL bValue)
{
	m_bUndecorateSymbols = bValue;
}

void COptionsStorage::SetPauseWhileHooking(BOOL bValue)
{
	m_bPauseWhileHooking = bValue;
}

void COptionsStorage::SetAutoScroll(BOOL bValue)
{
	m_bAutoScroll = bValue;
}

void COptionsStorage::SetShowStack(BOOL bValue)
{
	m_bShowStack = bValue;
}

// Persistence
// ATL7 deprecated CRegKey::QueryValue and SetValue, so we keep two different
// versions here to allow compilation with ATL3
#if _ATL_VER < 0x0700 // ATL3
BOOL COptionsStorage::LoadOptions()
{
	CRegKey regKey;
	LONG lRet = regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\Developer Playground"), KEY_READ);
	if(lRet != ERROR_SUCCESS) return FALSE;

	// Get the configurable parameters
	TCHAR szValue[512] = {0};

	DWORD cbValue = sizeof(szValue);
	if(regKey.QueryValue(szValue, _T("DependsPath"), &cbValue) == ERROR_SUCCESS)
	{
		m_strDependsPath = szValue;
	}

	DWORD dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("EnableSeDebugPriv")) == ERROR_SUCCESS)
	{
		m_bEnableSeDebugPriv = dwValue;
	}

	dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("StripSuffixForMsdn")) == ERROR_SUCCESS)
	{
		m_bStripSuffixForMsdn = dwValue;
	}

	dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("UndecorateSymbols")) == ERROR_SUCCESS)
	{
		m_bUndecorateSymbols = dwValue;
	}

	dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("PauseWhileHooking")) == ERROR_SUCCESS)
	{
		m_bPauseWhileHooking = dwValue;
	}

	dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("AutoScroll")) == ERROR_SUCCESS)
	{
		m_bAutoScroll = dwValue;
	}

	dwValue = 0;
	if(regKey.QueryValue(dwValue, _T("ShowStack")) == ERROR_SUCCESS)
	{
		m_bShowStack = dwValue;
	}

	return TRUE;
}

BOOL COptionsStorage::SaveOptions()
{
	CRegKey regKey;
	LONG lRet = regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\Developer Playground"), KEY_WRITE);
	if(lRet != ERROR_SUCCESS) return FALSE;

	// Set the configurable parameters
	regKey.SetValue(m_strDependsPath, _T("DependsPath"));

	regKey.SetValue(m_bEnableSeDebugPriv, _T("EnableSeDebugPriv"));
	regKey.SetValue(m_bStripSuffixForMsdn, _T("StripSuffixForMsdn"));
	regKey.SetValue(m_bUndecorateSymbols, _T("UndecorateSymbols"));
	regKey.SetValue(m_bPauseWhileHooking, _T("PauseWhileHooking"));
	regKey.SetValue(m_bAutoScroll, _T("AutoScroll"));
	regKey.SetValue(m_bShowStack, _T("ShowStack"));

	return TRUE;
}

#else // ATL 7.x

BOOL COptionsStorage::LoadOptions()
{
	CRegKey regKey;
	LONG lRet = regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\Developer Playground"), KEY_READ);
	if(lRet != ERROR_SUCCESS) return FALSE;

	// Get the configurable parameters
	TCHAR szValue[512] = {0};

	DWORD cchValue = lengthof(szValue);
	if(regKey.QueryStringValue(_T("DependsPath"), szValue, &cchValue) == ERROR_SUCCESS)
	{
		m_strDependsPath = szValue;
	}

	DWORD dwValue = 0;
	if(regKey.QueryDWORDValue(_T("EnableSeDebugPriv"), dwValue) == ERROR_SUCCESS)
	{
		m_bEnableSeDebugPriv = (dwValue != 0);
	}

	dwValue = 0;
	if(regKey.QueryDWORDValue(_T("StripSuffixForMsdn"), dwValue) == ERROR_SUCCESS)
	{
		m_bStripSuffixForMsdn = (dwValue != 0);
	}

	dwValue = 0;
	if(regKey.QueryDWORDValue(_T("UndecorateSymbols"), dwValue) == ERROR_SUCCESS)
	{
		m_bUndecorateSymbols = (dwValue != 0);
	}

	dwValue = 0;
	if(regKey.QueryDWORDValue(_T("PauseWhileHooking"), dwValue) == ERROR_SUCCESS)
	{
		m_bPauseWhileHooking = (dwValue != 0);
	}

	dwValue = 0;
	if(regKey.QueryDWORDValue(_T("AutoScroll"), dwValue) == ERROR_SUCCESS)
	{
		m_bAutoScroll = (dwValue != 0);
	}

	dwValue = 0;
	if(regKey.QueryDWORDValue(_T("ShowStack"), dwValue) == ERROR_SUCCESS)
	{
		m_bShowStack = (dwValue != 0);
	}

	return TRUE;
}

BOOL COptionsStorage::SaveOptions()
{
	CRegKey regKey;
	LONG lRet = regKey.Open(HKEY_CURRENT_USER, _T("SOFTWARE\\Developer Playground"), KEY_WRITE);
	if(lRet != ERROR_SUCCESS) return FALSE;

	// Set the configurable parameters
	regKey.SetStringValue(_T("DependsPath"), m_strDependsPath);

	regKey.SetDWORDValue(_T("EnableSeDebugPriv"), m_bEnableSeDebugPriv);
	regKey.SetDWORDValue(_T("StripSuffixForMsdn"), m_bStripSuffixForMsdn);
	regKey.SetDWORDValue(_T("UndecorateSymbols"), m_bUndecorateSymbols);
	regKey.SetDWORDValue(_T("PauseWhileHooking"), m_bPauseWhileHooking);
	regKey.SetDWORDValue(_T("AutoScroll"), m_bAutoScroll);
	regKey.SetDWORDValue(_T("ShowStack"), m_bShowStack);

	return TRUE;
}

#endif // _ATL_VER
