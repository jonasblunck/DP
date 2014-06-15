#ifndef __OPTIONSSTORAGE_H__
#define __OPTIONSSTORAGE_H__

class COptionsStorage
{
public:
	static COptionsStorage& Instance();

  CString& GetDependsPath();

	BOOL GetEnableSeDebugPriv();
	BOOL GetStripSuffixForMsdn();
	BOOL GetUndecorateSymbols();
	BOOL GetPauseWhileHooking();
	BOOL GetAutoScroll();
	BOOL GetShowStack();

	void SetDependsPath(LPCTSTR pszPath);

	void SetEnableSeDebugPriv(BOOL bValue);
	void SetStripSuffixForMsdn(BOOL bValue);
	void SetUndecorateSymbols(BOOL bValue);
	void SetPauseWhileHooking(BOOL bValue);
	void SetAutoScroll(BOOL bValue);
	void SetShowStack(BOOL bValue);
	
	BOOL LoadOptions();
	BOOL SaveOptions();

private:
	COptionsStorage();

	BOOL m_bEnableSeDebugPriv;
	BOOL m_bStripSuffixForMsdn;
	BOOL m_bUndecorateSymbols;
	BOOL m_bPauseWhileHooking;
	BOOL m_bAutoScroll;
	BOOL m_bShowStack;

  CString m_strDependsPath;
};

#endif //__OPTIONSSTORAGE_H__
