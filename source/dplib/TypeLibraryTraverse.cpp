#include "StdAfx.h"
#include "typelibrarytraverse.h"
#include "ISC.h"

CTypeLibraryTraverse::CTypeLibraryTraverse(void)
{
}

CTypeLibraryTraverse::~CTypeLibraryTraverse(void)
{
}

HRESULT CTypeLibraryTraverse::Traverse(const GUID& riid)
{
  LPOLESTR poleStr = NULL;

  if (S_OK != StringFromIID(riid, &poleStr))
    return E_FAIL;

  ATLASSERT(poleStr);

  CString strIID(poleStr);
  CoTaskMemFree(poleStr);

  CString strKey;
  strKey.Format(_T("Interface\\%s\\TypeLib"), (LPCTSTR)strIID);

  CRegKey RegTlb;

  if (ERROR_SUCCESS != RegTlb.Open(HKEY_CLASSES_ROOT, strKey, KEY_READ))
    return E_FAIL;

  CString strGUID;

  ULONG lLen = 255;

  RegTlb.QueryStringValue(_T(""), strGUID.GetBuffer(lLen + 1), &lLen);
  strGUID.ReleaseBuffer();

  CString strVersion;
  RegTlb.QueryStringValue(_T("Version"), strVersion.GetBuffer(lLen + 1), &lLen);
  strVersion.ReleaseBuffer();

  int iDelim = strVersion.Find(_T("."));

  USHORT uMajorVersion = (USHORT)atoi((LPCTSTR)strVersion.Left(iDelim));
  USHORT uMinorVersion = (USHORT)atoi((LPCTSTR)strVersion.Mid(iDelim + 1));

  GUID guidTlb;

  if (S_OK != CLSIDFromString(CComBSTR(strGUID), &guidTlb))
    return E_FAIL;

  if (S_OK == LoadRegTypeLib(guidTlb, uMajorVersion, uMinorVersion, NULL, &m_spTypeLib))
    HandleTypeLibrary();
  
  return S_OK;
}

HRESULT CTypeLibraryTraverse::Traverse(ITypeLib* typeLib)
{
  m_spTypeLib = typeLib;
  HandleTypeLibrary();

  return S_OK;
}

HRESULT CTypeLibraryTraverse::Traverse(const CString& rstrFilename)
{
  HRESULT hr = LoadTypeLib(CComBSTR(rstrFilename), &m_spTypeLib);

  if (SUCCEEDED(hr))
    HandleTypeLibrary();

  m_spTypeLib.Release();

  return hr;
}


bool CTypeLibraryTraverse::GetType(ITypeInfo* pTypeInfo, TYPEDESC* pTypeDesc, ISC::InterfaceParam* pParamInfo)
{
  // pParamInfo->bInParam/bOutParam is not touched in this routine, only the type
  if (pTypeDesc)
  {
    switch (pTypeDesc->vt)
    {
    case VT_PTR:
      {
        if (pParamInfo->pointerSpec == ISC::NoPtr)
          pParamInfo->pointerSpec = ISC::Ptr;
        else if (pParamInfo->pointerSpec == ISC::Ptr)
          pParamInfo->pointerSpec = ISC::Ptr2Ptr;

        return GetType(pTypeInfo, (TYPEDESC*)pTypeDesc->lptdesc, pParamInfo);
      }
    case VT_USERDEFINED:
      {
        CComPtr<ITypeInfo> spRefTypeInfo;
        if (S_OK == pTypeInfo->GetRefTypeInfo(pTypeDesc->hreftype, &spRefTypeInfo))
        {
          TYPEATTR* p = NULL;
          spRefTypeInfo->GetTypeAttr(&p);

          if (p->typekind == TKIND_INTERFACE ||
              p->typekind == TKIND_DISPATCH)
          {
            pParamInfo->riid = p->guid;
            pParamInfo->vtType = VT_USERDEFINED;
          }
          else if (p->typekind == TKIND_RECORD &&
                   p->cbSizeInstance == 16 &&
                   p->cVars == 4 &&
                   p->wTypeFlags == 16)
          {
            // it's an GUID
            pParamInfo->vtType = VT_CLSID;
          }
             
          spRefTypeInfo->ReleaseTypeAttr(p);

          return true;
        }
      }

    default:
      {
        if (VT_UNKNOWN == pTypeDesc->vt)
          pParamInfo->riid = IID_IUnknown;
        else if (VT_DISPATCH == pTypeDesc->vt)
          pParamInfo->riid = IID_IDispatch;

        pParamInfo->vtType = pTypeDesc->vt;
        return true;
      }
    }

  }

  return false;
}

void CTypeLibraryTraverse::HandleFunction(ITypeInfo* pTypeInfo, FUNCDESC* pFunctionDescription, UINT uiFunctionIndex)
{
  int iNelm = /*pFunctionDescription->cParams + */ 1;

// allocate place for one extra name since index 0 will be the name of the function!
  BSTR* pbstrNames = (BSTR*)CoTaskMemAlloc(sizeof(BSTR) * iNelm);

  if (pbstrNames)
  {
    UINT uiNames = 0;

    ISC::InterfaceParam* pReturnType = NULL;

    if (VT_PTR == pFunctionDescription->elemdescFunc.tdesc.vt)
    {
      pReturnType = new ISC::InterfaceParam();
      pReturnType->bOutParam = true; // hey, it's a retval ;)

      if (!GetType(pTypeInfo, &pFunctionDescription->elemdescFunc.tdesc, pReturnType))
      {
        delete pReturnType;
        pReturnType = NULL; // I don't know the return-type (sorry)
      }
    }

    if (SUCCEEDED(pTypeInfo->GetNames(pFunctionDescription->memid, pbstrNames, iNelm, &uiNames)))
    {
      ISC::InterfaceParam* pParams = NULL;
      int nParams = pFunctionDescription->cParams + (pReturnType ? 1 : 0);

      if (nParams)
      {
        pParams = new ISC::InterfaceParam[nParams];
        
        for (int i = 0; i < pFunctionDescription->cParams; ++i)
        { 
          ELEMDESC* pElemDesc = &pFunctionDescription->lprgelemdescParam[i];
          TYPEDESC* pTypeDesc = &pElemDesc->tdesc;

          ISC::InterfaceParam* pParam = &pParams[i];

          if (pElemDesc->idldesc.wIDLFlags & IDLFLAG_FIN)
            pParam->bInParam = true;
          else if (pElemDesc->idldesc.wIDLFlags & IDLFLAG_FOUT)
            pParam->bOutParam = true;

          GetType(pTypeInfo, pTypeDesc, pParam);
        }

        // copy return-type
        if (NULL != pReturnType)
          pParams[nParams - 1] = pReturnType;

      }

      // send method-info to the client
      OnFunction(uiFunctionIndex, CString(pbstrNames[0]), pParams, nParams);

      delete pReturnType;
    }
  }

  // cleanup
  for (int i = 0; i < iNelm; ++i)
    SysFreeString(pbstrNames[i]);

  CoTaskMemFree(pbstrNames);
}
  
void CTypeLibraryTraverse::HandleInterface(ITypeInfo* pTypeInfo, TYPEATTR* pTypeAttributes)
{
  ATLASSERT(pTypeInfo && pTypeAttributes);

  if (pTypeInfo && pTypeAttributes)
  {
    for (int i = 0; i < pTypeAttributes->cFuncs; ++i)
    {
      FUNCDESC* pFunctionDescription = NULL;

      if (SUCCEEDED(pTypeInfo->GetFuncDesc(i, &pFunctionDescription)))
      {
        HandleFunction(pTypeInfo, pFunctionDescription, i);

        pTypeInfo->ReleaseFuncDesc(pFunctionDescription);
      }
    }
  }
}

bool CTypeLibraryTraverse::FindBaseIID(ITypeInfo* pTypeInfo, GUID& riid)
{
  HREFTYPE hRef;

  if (SUCCEEDED(pTypeInfo->GetRefTypeOfImplType(0, &hRef)))
  {
    CComPtr<ITypeInfo> spBaseTypeInfo;

    if (SUCCEEDED(pTypeInfo->GetRefTypeInfo(hRef, &spBaseTypeInfo)))
    {
      TYPEATTR* pType = NULL;

      spBaseTypeInfo->GetTypeAttr(&pType);

      riid = pType->guid;

      spBaseTypeInfo->ReleaseTypeAttr(pType);
    }
  }

  return false;
}

bool CTypeLibraryTraverse::HandleTypeInfo(ITypeInfo* pTypeInfo)
{
  ATLASSERT(pTypeInfo);

  CComBSTR bstrName;
  TYPEATTR* pTypeAttributes = NULL;

  if (SUCCEEDED(pTypeInfo->GetTypeAttr(&pTypeAttributes)) && pTypeAttributes)
  {
    if (SUCCEEDED(pTypeInfo->GetDocumentation(pTypeAttributes->memidConstructor, &bstrName, 0, 0, 0)))
    {
      GUID riidBase = GUID_NULL;

      FindBaseIID(pTypeInfo, riidBase);

      OnInterface(CString(bstrName), pTypeAttributes->guid, pTypeAttributes->cFuncs, riidBase);

      HandleInterface(pTypeInfo, pTypeAttributes);

      if (!OnAfterInterface(pTypeAttributes->guid))
        return false;
    }

    pTypeInfo->ReleaseTypeAttr(pTypeAttributes);
  }

  return true;
}

void CTypeLibraryTraverse::HandleTypeLibrary()
{
  ATLASSERT(m_spTypeLib);

  UINT uiIndex = 0;
  bool bContinue = true;

  while (bContinue)
  {
    CComPtr<ITypeInfo> spTypeInfo;

    if (SUCCEEDED(m_spTypeLib->GetTypeInfo(uiIndex, &spTypeInfo)))
    {
      TYPEKIND InfoType;

      if (SUCCEEDED(m_spTypeLib->GetTypeInfoType(uiIndex, &InfoType)))
      {
        if (TKIND_INTERFACE == InfoType || TKIND_DISPATCH == InfoType)
        {
          bContinue = HandleTypeInfo(spTypeInfo);
        }
      }

    }
    else
    {
      bContinue = false;
    }

    ++uiIndex;
  }

}
