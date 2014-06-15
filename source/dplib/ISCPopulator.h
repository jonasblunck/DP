#pragma once

#include "TypeLibraryTraverse.h"
#include "ISC.h"

class ISCPopulator : public CTypeLibraryTraverse
{
private:
  ISC::Interface* m_pCurrentInterface;
  GUID m_riidToCache;

protected:
  void OnInterface(const CString& rstrName, const GUID& riid, long lNumMethods, const GUID& riidBase);
  void OnFunction(UINT uiFunctionIndex, const CString& rstrFunctionName, ISC::InterfaceParam* ppParams, int iParamCount);
  bool OnAfterInterface(const GUID& riid);

public:
  ISCPopulator(void);
  ~ISCPopulator(void);

  bool Cache(const GUID& riid);
};
