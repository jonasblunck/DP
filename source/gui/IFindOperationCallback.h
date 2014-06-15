#pragma  once

class IFindOperationCallback
{
public:
  virtual void OnItem(DWORD rwa, LPCTSTR pszModule, LPCTSTR name, LPCTSTR parameters, LPCTSTR type) = 0;
};
