#pragma once

#include <atlstr.h>
#include "ISC.h"

class CallStackParam 
{
private:

  ISC::InterfaceParam* m_param;

  inline bool OnArgumentBSTR(void**& ppStackArgument, CString& rstrArgument) const; // BSTR 
  inline bool OnArgumentI2(void**& ppStackArgument, CString& rstrArgument) const;   // SHORT  
  inline bool OnArgumentI4(void**& ppStackArgument, CString& rstrArgument) const;  // long 
  inline bool OnArgumentUINT(void**& ppStackArgument, CString& rstrArgument) const;  // UINT
  inline bool OnArgumentINT(void**& ppStackArgument, CString& rstrArgument) const;  // int 
  inline bool OnArgumentBOOL(void**& ppStackArgument, CString& rstrArgument) const; // BOOL
  inline bool OnArgumentR4(void**& ppStackArgument, CString& rstrArgument) const; // float 
  inline bool OnArgumentR8(void**& ppStackArgument, CString& rstrArgument) const; // double
  inline bool OnArgumentUI2(void**& ppStackArgument, CString& rstrArgument) const; // USHORT
  inline bool OnArgumentUI4(void**& ppStackArgument, CString& rstrArgument) const; // ULONG
  inline bool OnArgumentPointer(void**& ppStackArgument, CString& rstrArgument) const; // Some kind of pointer (VT_POINTER of VT_PTR) 
  inline bool OnArgumentLPWSTR(void**& ppStackArgument, CString& rstrArgument) const;
  inline bool OnArgumentLPCTSTR(void**& ppStackArgument, CString& rstrArgument) const; // LPTSTR, LPSTR, LPCTSTR
  inline bool OnArgumentREFIID(void**& ppStackArgument, CString& rstrArgument) const; // GUID* 
  inline bool OnArgumentGUID(void**& ppStackArgument, CString& rstrArgument) const; // GUID 
  inline bool OnArgumentVARIANT(void**& ppStackArgument, CString& rstrArgument) const; // VARIANT 

public:

  CallStackParam(ISC::InterfaceParam* param);
  ~CallStackParam();

  bool ParseCallStackParam(void**& ppStackArgument, CString& rstrArgument); 
};


