#include "stdafx.h"
#include "CallStackParam.h"
#include <comdef.h>
#include "ISC.h"

#define MAX_LEN_STRING_ARG      48

CallStackParam::CallStackParam(ISC::InterfaceParam* param) : m_param(param)
{
}

CallStackParam::~CallStackParam()
{
}

#pragma warning(disable: 4310 4482)

inline bool CallStackParam::OnArgumentBOOL(void**& ppStackArgument, CString& rstrArgument) const
{
  BOOL vtb = (BOOL)ppStackArgument[0];
  ++ppStackArgument;

  if (vtb)
    rstrArgument += _T("TRUE");
  else
    rstrArgument += _T("FALSE");

  return true;
}

inline bool CallStackParam::OnArgumentBSTR(void**& ppStackArgument, CString& rstrArgument) const
{
  CString strArgument;

  if (NULL != (BSTR)ppStackArgument[0])
    strArgument = (BSTR)ppStackArgument[0];

  ++ppStackArgument; // next argument

  if (strArgument.GetLength() > MAX_LEN_STRING_ARG)
  {  
    strArgument = strArgument.Left(MAX_LEN_STRING_ARG);   
    strArgument += _T("...");
  }

  rstrArgument += _T("\"");
  rstrArgument += strArgument;
  rstrArgument += _T("\"");

  return true;
}

inline bool CallStackParam::OnArgumentLPWSTR(void**& ppStackArgument, CString& rstrArgument) const
{
  LPWSTR pwstr = (LPWSTR)ppStackArgument[0];
  CString strArgument;

  if (pwstr)
    strArgument = pwstr;

  ++ppStackArgument; // next argument

  if (strArgument.GetLength() > MAX_LEN_STRING_ARG)
  {  
    strArgument = strArgument.Left(MAX_LEN_STRING_ARG);   
    strArgument += _T("...");
  }

  rstrArgument += _T("\"");
  rstrArgument += strArgument;
  rstrArgument += _T("\"");

  return true;
}

inline bool CallStackParam::OnArgumentLPCTSTR(void**& ppStackArgument, CString& rstrArgument) const
{
  LPCSTR psz = (LPCTSTR)ppStackArgument[0];
  CString strArgument;

  if (psz)
    strArgument = psz;

  ++ppStackArgument; // next argument

  if (strArgument.GetLength() > MAX_LEN_STRING_ARG)
  {  
    strArgument = strArgument.Left(MAX_LEN_STRING_ARG);   
    strArgument += _T("...");
  }

  rstrArgument += _T("\"");
  rstrArgument += strArgument;
  rstrArgument += _T("\"");

  return true;
}

#pragma warning(disable: 4311)

inline bool CallStackParam::OnArgumentINT(void**& ppStackArgument, CString& rstrArgument) const
{
  int iValue = (int)ppStackArgument[0];
  ++ppStackArgument;
  rstrArgument.Format(_T("%d"), iValue);

  return true;
}

#pragma warning(default: 4311)

inline bool CallStackParam::OnArgumentPointer(void**& ppStackArgument, CString& rstrArgument) const
{
  // might be any kind of an pointer (int*, long*, IUnknown*, IMyCustom*, etc)
  LPVOID pv = (LPVOID)ppStackArgument[0];
  ++ppStackArgument;
  rstrArgument.Format(_T("0x%08X"), pv);

  return true;
}

inline bool CallStackParam::OnArgumentR4(void**& ppStackArgument, CString& rstrArgument) const
{
  float fValue;
  memcpy(&fValue, &ppStackArgument[0], sizeof(float));
  rstrArgument.Format(_T("%f"), fValue);

  ++ppStackArgument;

  return true;
}

inline bool CallStackParam::OnArgumentR8(void**& ppStackArgument, CString& rstrArgument) const
{
  double dValue;
  memcpy(&dValue, &ppStackArgument[0], sizeof(double));
  rstrArgument.Format(_T("%f"), dValue);
  ++ppStackArgument;
  ++ppStackArgument;

  return true;
}

inline bool CallStackParam::OnArgumentI2(void**& ppStackArgument, CString& rstrArgument) const
{
  short sValue = (short)ppStackArgument[0];
  ++ppStackArgument;
  rstrArgument.Format(_T("%d"), sValue);

  return true;
}

#pragma warning(disable: 4311)

inline bool CallStackParam::OnArgumentI4(void**& ppStackArgument, CString& rstrArgument) const
{
  long lValue = (long)ppStackArgument[0];
  ++ppStackArgument;
  rstrArgument.Format(_T("%i"), lValue);

  return true;
}

#pragma warning(default: 4311)

inline bool CallStackParam::OnArgumentUI2(void**& ppStackArgument, CString& rstrArgument) const
{
  USHORT sValue = (USHORT)ppStackArgument[0];

  ++ppStackArgument;

  rstrArgument.Format(_T("%d"), sValue);

  return true;
}

#pragma warning(disable: 4311)

inline bool CallStackParam::OnArgumentUI4(void**& ppStackArgument, CString& rstrArgument) const
{
  ULONG ulValue = (ULONG)ppStackArgument[0];

  ++ppStackArgument;

  rstrArgument.Format(_T("%ld"), ulValue);

  return true;
}

inline bool CallStackParam::OnArgumentUINT(void**& ppStackArgument, CString& rstrArgument) const
{
  UINT uiValue = (UINT)ppStackArgument[0];

  ++ppStackArgument;

  rstrArgument.Format(_T("%u"), uiValue);

  return true;
}

inline bool CallStackParam::OnArgumentGUID(void**& ppStackArgument, CString& rstrArgument) const
{
  GUID guid = GUID_NULL;

  memcpy(&guid, &ppStackArgument[0], sizeof(GUID));

  ppStackArgument++;
  ppStackArgument++;
  ppStackArgument++;
  ppStackArgument++;

  ISC::Interface* pInterface = ISC::GetISC().GetInterface(guid);

  if (pInterface)
  {
    rstrArgument = pInterface->strName;
  }
  else
  {
    LPOLESTR poleStr = NULL;
    StringFromIID(guid, &poleStr);
    rstrArgument = poleStr;
    CoTaskMemFree(poleStr);
  }

  return true;
}

inline bool CallStackParam::OnArgumentVARIANT(void**& ppStackArgument, CString& rstrArgument) const
{
  CComVariant v((VARIANT&)ppStackArgument[0]);

  v.ChangeType(VT_BSTR);

  rstrArgument = v.bstrVal;

  return true;
}

inline bool CallStackParam::OnArgumentREFIID(void**& ppStackArgument, CString& rstrArgument) const
{
  GUID* guid = (GUID*)ppStackArgument[0]; // only a pointer to the GUID is placed on the stack
  ++ppStackArgument; 

  ISC::Interface* pInterface = ISC::GetISC().GetInterface(*guid);

  if (pInterface)
  {
    rstrArgument = pInterface->strName;

    return true;
  }
  else
  {
    LPOLESTR poleStr = NULL;
    StringFromIID(*guid, &poleStr);
    rstrArgument = poleStr;
    CoTaskMemFree(poleStr);

    return true;
  }

  return false;
}


bool CallStackParam::ParseCallStackParam(void**& ppStackArgument, CString& rstrArgument) 
{
  SHORT type = m_param->vtType;

  if (m_param->bOutParam && (m_param->pointerSpec == ISC::PointerSpec::Ptr || m_param->pointerSpec == ISC::PointerSpec::Ptr2Ptr))
  {
    type = VT_VOID;
  }

  switch (type)
  {
  case VT_INT:
    return OnArgumentINT(ppStackArgument, rstrArgument);
  case VT_I4:
    return OnArgumentI4(ppStackArgument, rstrArgument);
  case VT_UINT:
    return OnArgumentUINT(ppStackArgument, rstrArgument);
  case VT_VOID:
  case VT_PTR:
    return OnArgumentPointer(ppStackArgument, rstrArgument);
  case VT_BSTR:
    return OnArgumentBSTR(ppStackArgument, rstrArgument);
  case VT_I2:
    return OnArgumentI2(ppStackArgument, rstrArgument);
  case VT_BOOL:
    return OnArgumentBOOL(ppStackArgument, rstrArgument);
  case VT_R4:
    return OnArgumentR4(ppStackArgument, rstrArgument);
  case VT_R8:
    return OnArgumentR8(ppStackArgument, rstrArgument);
  case VT_UI2:
    return OnArgumentUI2(ppStackArgument, rstrArgument);
  case VT_UI4:
    return OnArgumentUI4(ppStackArgument, rstrArgument);
  case VT_LPWSTR:
    return OnArgumentLPWSTR(ppStackArgument, rstrArgument);
  case VT_LPSTR:
    return OnArgumentLPCTSTR(ppStackArgument, rstrArgument);
  case VT_CLSID:
    if (m_param->pointerSpec == ISC::PointerSpec::NoPtr)
      return OnArgumentGUID(ppStackArgument, rstrArgument);
    else
      return OnArgumentREFIID(ppStackArgument, rstrArgument);
  case VT_VARIANT:
    return OnArgumentVARIANT(ppStackArgument, rstrArgument);
  default:
    rstrArgument += _T("???");
    return false;
  }

  return false;
}


#pragma warning(default: 4310 4482)
