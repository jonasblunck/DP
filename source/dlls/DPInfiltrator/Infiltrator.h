
#ifndef _INFILTRATOR_H_
#define _INFILTRATOR_H_

#include <list>
#include <atlstr.h>
typedef std::list<DWORD> DWList;

enum ParameterType;

class Infiltrator  
{
  long m_lRef;
  DWList m_ListUnsafe;

  void InitUnsafeAddresses();
  bool IsUnsafe(DWORD dwAddress);
  static void ExtractParameterDefinitions(const CString& combound, std::list<SHORT>& definitions);

public:
  Infiltrator();
  ~Infiltrator();

  // IDPInfiltrator
  STDMETHOD(SetupTrace)(BSTR bstrModule, DWORD dwRVA, BSTR bstrParamDefinition, long* plIDBlock);
  STDMETHOD(Unhook)(BSTR bstrModule, DWORD dwRWA);

  STDMETHOD(Pause)(VARIANT_BOOL vtbPause);

};

#endif
