#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__

#pragma once 

class TreeItemData
{
public:
	TreeItemData(DWORD dwPID, LPCTSTR pszPath, NODETYPE nodeType)
	{
		m_dwPID = dwPID;
		m_nodeType = nodeType;
		
		memset(m_szPath, 0, sizeof(m_szPath));
		if(!GetLongPathName(pszPath, m_szPath, lengthof(m_szPath)))
		{
			if(_tcsncmp(pszPath, _T("\\??\\"), 4) == 0)
			{
				// This is one of the weird ones...
				_tcsncpy(m_szPath, pszPath + 4, lengthof(m_szPath) - 1);
			}
			else
			{
				// Default to the passed-in name
				_tcsncpy(m_szPath, pszPath, lengthof(m_szPath) - 1);
			}
		}
		
		_tcsupr(m_szPath);
	}

	LPCTSTR GetName()
	{
		LPCTSTR pszName = _tcsrchr(m_szPath, _T('\\'));
		if(pszName)
		{
			return pszName + 1;
		}
		else
		{
			return m_szPath;
		}
	}

	DWORD GetPID()
	{
		return m_dwPID;
	}

	LPCTSTR GetPath()
	{
		return m_szPath;
	}

	NODETYPE GetNodeType()
	{
		return m_nodeType;
	}

private:
	TCHAR m_szPath[MAX_PATH];
	DWORD m_dwPID;
	NODETYPE m_nodeType;
};

struct ExportItemData
{
	ExportItemData(DWORD dwOrdinal, DWORD dwRVA, LPCTSTR pszFunctionName, LPCTSTR pszParameters, LPCTSTR pszType)
	{
		m_dwOrdinal = dwOrdinal;
		m_dwRVA = dwRVA;
		m_bIsHooked = false;

		m_strName = pszFunctionName;
    m_strParameters = pszParameters;
    m_strType = pszType;
	}

	LPCTSTR GetName()
	{
		return m_strName;
	}

  LPCTSTR GetParameters()
  {
    return m_strParameters;
  }

  LPCTSTR GetType()
  {
    return m_strType;
  }

	DWORD GetOrdinal()
	{
		return m_dwOrdinal;
	}

	DWORD GetRVA()
	{
		return m_dwRVA;
	}

	void AppendName(LPCTSTR pszName)
	{
		m_strName += _T(", ");
		m_strName += pszName;
	}

	BOOL IsHooked()
	{
		return m_bIsHooked;
	}

	void SetHooked(BOOL b)
	{
		m_bIsHooked = b;
	}
	
private:
	CString m_strName;
  CString m_strParameters;
  CString m_strType;
	DWORD m_dwOrdinal;
	DWORD m_dwRVA;
	BOOL m_bIsHooked;
};

struct TraceItemData
{
	TraceItemData(DWORD dwPID, long lHookID, LPCTSTR argTrace)
		:	m_dwPID(dwPID),
			m_lHookID(lHookID)
	{
	  m_argTrace = argTrace;
	}

// Getters
	DWORD GetPID()
	{
		return m_dwPID;
	}

	long GetHookID()
	{
		return m_lHookID;
	}

	LPCTSTR GetArgumentsTrace() const
	{
		return (LPCTSTR)m_argTrace;
	}

private:
	DWORD	m_dwPID;
	long	m_lHookID;
  CString m_argTrace;
};

#endif // __ITEMDATA_H__
