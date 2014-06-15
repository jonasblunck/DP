#include "StdAfx.h"
#include "ISC.h"
#include "CSAuto.h"
#include "ISCPopulator.h"

static ISC s_ISC;

ISC::InterfaceMethod::InterfaceMethod()
{
  nParamCount = 0;
  pParams = NULL;
}

void ISC::InterfaceMethod::clear()
{
  nParamCount = 0;
  delete [] pParams;
  pParams = 0;
}
   
void ISC::InterfaceMethod::addParam(SHORT type, PointerSpec pointerSpec)
{
  ISC::InterfaceParam* params = new ISC::InterfaceParam[nParamCount + 1];

  for (UINT i = 0; i < nParamCount; ++i)
    params[i] = pParams[i];
  
  params[nParamCount].vtType = type;
  params[nParamCount].pointerSpec = pointerSpec;
  nParamCount++;

  delete [] pParams;
  pParams = params;
}

ISC::InterfaceParam::InterfaceParam()
{
  bInParam = false;
  bOutParam = false;
  pIidIsParam = NULL;
  pointerSpec = NoPtr;
  riid = GUID_NULL;
  vtType = VT_EMPTY;
}

ISC::InterfaceParam& ISC::InterfaceParam::operator = (ISC::InterfaceParam* pMethod)
{
  bInParam = pMethod->bInParam;
  bOutParam = pMethod->bOutParam;
  pIidIsParam = pMethod->pIidIsParam;
  pointerSpec = pMethod->pointerSpec;
  riid = pMethod->riid;
  vtType = pMethod->vtType;

  return *(this);
}

ISC::Interface::Interface()
{
  Guid = GUID_NULL;
  nMethodCount = 0;
  pMethods = NULL;
  pBase = NULL;
  GuidBase = GUID_NULL;
}

ISC::ISC(void)
{
  InitializeCriticalSection(&m_cs);

  Interface* pUnk = new Interface;
  pUnk->Guid = IID_IUnknown;
  pUnk->GuidBase = GUID_NULL;
  pUnk->nMethodCount = 3;
  pUnk->pBase = NULL;
  pUnk->strName = _T("IUnknown");

  pUnk->pMethods = new InterfaceMethod[3];
  pUnk->pMethods[0].nParamCount = 0;  // QI
  pUnk->pMethods[1].nParamCount = 0;  // AddRef
  pUnk->pMethods[2].nParamCount = 0;  // Release

  pUnk->pMethods[0].pParams = NULL;
  pUnk->pMethods[1].pParams = NULL;
  pUnk->pMethods[2].pParams = NULL;

  pUnk->pMethods[0].strName = _T("QueryInterface");
  pUnk->pMethods[1].strName = _T("AddRef");
  pUnk->pMethods[2].strName = _T("Release");

  // params for QI
  pUnk->pMethods[0].pParams = new InterfaceParam[2];
  pUnk->pMethods[0].nParamCount = 2;

  // first param for QI (REFIID riid)
  pUnk->pMethods[0].pParams[0].vtType = VT_CLSID; // using this for GUID's
  pUnk->pMethods[0].pParams[0].bInParam = true;
  pUnk->pMethods[0].pParams[0].pointerSpec = ISC::Ptr;

  // second param for QI (VOID** ppv)
  pUnk->pMethods[0].pParams[1].vtType = VT_UNKNOWN; 
  pUnk->pMethods[0].pParams[1].bOutParam = true;
  pUnk->pMethods[0].pParams[1].pointerSpec = ISC::Ptr2Ptr;
  pUnk->pMethods[0].pParams[1].pIidIsParam = &pUnk->pMethods[0].pParams[0]; // reference the first parameter 

  AddToCache(pUnk);
}

ISC::~ISC(void)
{
  DeleteCriticalSection(&m_cs);

  // clean up the cache..

  // walk the cache

}

ISC& ISC::GetISC()
{
  return s_ISC;
}

ISC::InterfaceMethod* ISC::GetMethod(ISC::Interface* pInterface, int iMethodIndex)
{
  int iNumMethods = ISC::GetMethodCount(pInterface);
  int iReversedIndex = iNumMethods - iMethodIndex;

  while (pInterface && iReversedIndex > (int)pInterface->nMethodCount && iReversedIndex >= 0)
  {
    iReversedIndex -= pInterface->nMethodCount;

    pInterface = pInterface->pBase;
  }

  if (pInterface)
  {
    int iLocalIndex = pInterface->nMethodCount - iReversedIndex;

    return &pInterface->pMethods[iLocalIndex];
  }

  return NULL;
}

int ISC::GetMethodCount(ISC::Interface* pInterface)
{
  ISC::Interface* pTemp = pInterface;

  int iCount = 0;

  while (pTemp)
  {
    iCount += pTemp->nMethodCount;

    pTemp = pTemp->pBase;
  }

  return iCount;
}

ISC::Interface* ISC::GetInterfaceImplicitUpdate(const GUID& riid)
{
  CS(const_cast<CRITICAL_SECTION&>(m_cs));

  ISCMap::const_iterator Iterator = m_mapInterfaces.find(riid);

  if (Iterator != m_mapInterfaces.end())
    return (*Iterator).second;
  else
  {
    if (UpdateCache(riid))
    {
      return GetInterfaceImplicitUpdate(riid);
    }

  }

  return NULL;
}

void ISC::AddTypeLibrary(ITypeLib* typeLib)
{
  ISCPopulator loader;
  loader.Traverse(typeLib);
}

ISC::Interface* ISC::GetInterface(const GUID& riid) 
{
  ISC::Interface* pInterface = GetInterfaceImplicitUpdate(riid);

  if (pInterface)
  {
    if (!pInterface->pBase && pInterface->GuidBase != GUID_NULL && pInterface->GuidBase != IID_IDispatch)
      pInterface->pBase = GetInterface(pInterface->GuidBase);

    return pInterface;
  }

  return NULL;
}


bool ISC::UpdateCache(const GUID& riid)
{
  ISCPopulator Loader;
  
  return Loader.Cache(riid);
}

void ISC::AddToCache(ISC::Interface* pInterface)
{
  ATLASSERT(pInterface);

  CS(const_cast<CRITICAL_SECTION&>(m_cs));

  ISCMap::const_iterator Iterator = m_mapInterfaces.find(pInterface->Guid);

  if (Iterator == m_mapInterfaces.end())
    m_mapInterfaces.insert(ISCMap::value_type(pInterface->Guid, pInterface));
}

