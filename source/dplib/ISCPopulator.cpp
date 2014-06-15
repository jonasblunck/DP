#include "StdAfx.h"
#include "iscpopulator.h"

ISCPopulator::ISCPopulator(void)
{
  m_pCurrentInterface = NULL;
}

ISCPopulator::~ISCPopulator(void)
{
}

void ISCPopulator::OnInterface(const CString& rstrName, const GUID& riid, long lNumMethods, const GUID& riidBase)
{
  ATLASSERT(NULL == m_pCurrentInterface);

  m_pCurrentInterface = new ISC::Interface();
  m_pCurrentInterface->Guid = riid;
  m_pCurrentInterface->pBase = NULL;
  m_pCurrentInterface->GuidBase = riidBase;
  m_pCurrentInterface->nMethodCount = lNumMethods;
  m_pCurrentInterface->strName = rstrName;
  m_pCurrentInterface->pMethods = new ISC::InterfaceMethod[lNumMethods];
}

void ISCPopulator::OnFunction(UINT uiFunctionIndex, const CString& rstrFunctionName,
                              ISC::InterfaceParam* pParams, int nNumParams)
{
  ATLASSERT(uiFunctionIndex <= m_pCurrentInterface->nMethodCount);
  ATLASSERT(m_pCurrentInterface);
  ATLASSERT(m_pCurrentInterface->pMethods);

  if (m_pCurrentInterface->pMethods)
  {
    ISC::InterfaceMethod* pMethod = &m_pCurrentInterface->pMethods[uiFunctionIndex];

    pMethod->nParamCount = nNumParams;
    pMethod->strName = rstrFunctionName;
    pMethod->pParams = NULL;

    if (nNumParams)
      pMethod->pParams = pParams;
  }

}

bool ISCPopulator::OnAfterInterface(const GUID& riid)
{
  ATLASSERT(m_pCurrentInterface);

  ISC::GetISC().AddToCache(m_pCurrentInterface);

  m_pCurrentInterface = NULL;

  if (riid == m_riidToCache)
    return false;

  return true;
}

bool ISCPopulator::Cache(const GUID& riid)
{
  m_riidToCache = riid;

  if (S_OK != Traverse(riid))
    return false;

  return true;
}