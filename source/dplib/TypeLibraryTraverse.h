#pragma once

#include "ISC.h"

class CTypeLibraryTraverse
{
public:
  CTypeLibraryTraverse(void);
  ~CTypeLibraryTraverse(void);

  HRESULT Traverse(ITypeLib* pTypeInfo);
  HRESULT Traverse(const CString& rstrFilename);
  HRESULT Traverse(const GUID& riid); // find this interface in and load the typelib

protected:

  virtual void OnInterface(const CString& rstrName, const GUID& riid, long lNumMethods, const GUID& riidBase) = 0;
  virtual void OnFunction(UINT uiFunctionIndex, const CString& rstrFunctionName, ISC::InterfaceParam* pParams, int iParamCount) = 0;
  virtual bool OnAfterInterface(const GUID& riid) = 0;

private:
  CComPtr<ITypeLib> m_spTypeLib;
  CComPtr<ITypeInfo> m_spTypeInfo;

  bool FindBaseIID(ITypeInfo* pTypeInfo, GUID& riid);
//  int GetNumMethods(ITypeInfo* pTypeInfo);
  void HandleTypeLibrary();
  bool HandleTypeInfo(ITypeInfo* pTypeInfo);
  void HandleInterface(ITypeInfo* pTypeInfo, TYPEATTR* pTypeAttributes);
  void HandleFunction(ITypeInfo* pTypeInfo, FUNCDESC* pFuncionDescription, UINT uiFunctionIndex);

  bool GetType(ITypeInfo* pTypeInfo, TYPEDESC* pTypeDesc, ISC::InterfaceParam* pParamInfo);

};
