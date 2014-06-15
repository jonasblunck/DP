#pragma once
#include <map>
#include "GuidHelpers.h"
#define IDLFLAG_RIID    0x400

class ISC
{
public:

  typedef enum PointerSpec
  {
    NoPtr, Ptr, Ptr2Ptr
  };

  struct InterfaceParam
  {
    bool bInParam;
    bool bOutParam;
    SHORT vtType; // VT_BSTR, etc
    PointerSpec pointerSpec;
    GUID riid;  // the IID for the type, or GUID_NULL
    LPVOID* ppv; // for outgoing interfaces
    InterfaceParam* pIidIsParam; // The parameter that specs the IID or NULL (NULL when loaded from typelib)

    InterfaceParam();
    InterfaceParam& operator = (InterfaceParam* pMethod);

    bool IsPointer()
    {
      return pointerSpec == Ptr;
    }
  };

  struct InterfaceMethod
  {
    CString strName;
    UINT nParamCount;
    InterfaceParam* pParams;

    InterfaceMethod();

    void clear();
    void addParam(SHORT type, PointerSpec pointerSpec);
  };

  struct Interface
  {
    GUID Guid;
    CString strName;
    UINT nMethodCount;
    InterfaceMethod* pMethods; // number of elements indicated by nMethodCount
    Interface* pBase;
    GUID GuidBase;

    Interface();
  };

public:
  static ISC& GetISC();

  void AddToCache(ISC::Interface* pInterface);
  ISC::Interface* GetInterface(const GUID& riid);
  void AddTypeLibrary(ITypeLib* typeLib);

  static ISC::InterfaceMethod* GetMethod(ISC::Interface* pInterface, int iMethodIndex);
  static int GetMethodCount(ISC::Interface* pInterface);

  ISC(void);
  ~ISC(void);

private:

  ISC::Interface* GetInterfaceImplicitUpdate(const GUID& riid);
  bool UpdateCache(const GUID& riid);

  typedef std::map<GUID, ISC::Interface*> ISCMap;
  CRITICAL_SECTION m_cs;
  ISCMap m_mapInterfaces;

};
