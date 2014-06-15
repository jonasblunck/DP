#pragma once

typedef HRESULT (__stdcall* ProcCoCreateInstance)(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*);
typedef HRESULT (__stdcall* ProcCoMarshalInterface)(IStream*, REFIID, IUnknown*, DWORD, void*, DWORD);

class CHookCoCreateInstance
{
  static ProcCoCreateInstance m_ProcCoCreateInstanceChain;
  static ProcCoMarshalInterface m_ProcCoMarshalInterface;

  static HRESULT __stdcall CoCreateInstanceHook(REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*);
  static HRESULT __stdcall CoMarshalInterfaceHook(IStream*, REFIID, IUnknown*, DWORD, void*, DWORD);

public:
  CHookCoCreateInstance(void);
  ~CHookCoCreateInstance(void);

  static void Hook();

};
