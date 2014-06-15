// Hook.cpp: implementation of the CDynHooker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynHooker.h"
#include "HookContext.h"
#include "CallStackParam.h"
#include "ISC.h"
#include "Callstack.h"

#pragma warning(disable: 4482)
static CallStack s_callStack;


int __stdcall __OnBeforeExecute(DWORD returnAddress, HookContext* hookContext, DWORD _esp)
{
  if (hookContext->IsActive())
  {
    // stack arguments starts at esp + 8!
    hookContext->OnBeforeExecute((void**)(_esp + 8));
  }

  s_callStack.Push(CallContext(hookContext, returnAddress));

  return 0;
}

static DWORD __stdcall OnAfterExecuted(int returnValue)
{
  CallContext context = s_callStack.Pop();

  context.hookContext->OnAfterExecute(returnValue);

  return context.returnAddress;
}

static void __declspec(naked) CallCompleted()
{
  _asm
  {
    push eax
    push ecx
    push edi

    push eax // the HRESULT for COM calls
    call OnAfterExecuted

    mov edx, eax

    pop edi
    pop ecx
    pop eax

    jmp edx
  }

}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynHooker::CDynHooker()
{
  m_bPaused = false;
}

CDynHooker::~CDynHooker()
{
}


DWORD CDynHooker::CalcAddressOffset(DWORD dwDestinationAddress,
                                    DWORD dwHookCodeStartAddress,       // just to simplify
                                    DWORD dwInstructionOffsetInHook,     // how many bytes in btHook[] does the instruction start
                                    DWORD dwTotalInstSize                // total size of instruction, including address displacement
                        )
{
  DWORD dwDisplacement =
    dwDestinationAddress - dwHookCodeStartAddress - dwInstructionOffsetInHook - dwTotalInstSize;

  return dwDisplacement;
}

bool CDynHooker::GetHookContext(LPVOID pInterceptedFunction, HookContext*& context)
{
  bool success = false;

  // first there should be a JMP statement pointer to the chain!
  if (0xE9 == ((BYTE*)(pInterceptedFunction))[0])
  {
    BYTE* chainAddress = 0;
    memcpy(&chainAddress, (LPVOID)((DWORD)pInterceptedFunction + 1), sizeof(LPVOID));

    chainAddress += (DWORD)pInterceptedFunction + sizeof(LPVOID) + 1; // the extra '1' is from the 0xE9 instruction!

    BYTE hookedSignature[] = { 0x51, 0x54, 0x68 };

    //
    // make sure this really is a chain function
    if (0 == memcmp(chainAddress, hookedSignature, sizeof(hookedSignature)))
    {
      LPVOID source = (LPVOID)((DWORD)chainAddress + 3);
      memcpy(&context, source, sizeof(LPVOID));

      success = true;
    }
  }

  return success;
}

HookContext* CDynHooker::InstallDynamicHook(LPVOID pFunctionToIntercept, LPCTSTR pszName, 
                                    ISC::InterfaceMethod* method,
                                    HookedFunctionListener* listener, bool isStdCall)
{
  BYTE btHook[] =
  {
    0x8b, 0x14, 0x24,     // mov edx, dword ptr [esp]
    0x51,                 // push ecx (this pointer)
    0x54,                 // push esp (stack pointer so we can deduce stack arguments)
    0x68, 0, 0, 0, 0,     // push HookContext*   (insert the hook context instance pointer here)  (6)
    0x52,                 // push edx (return address)
    0xe8, 0, 0, 0, 0,     // call __HookForTrace (insert displacement for __HookForTrace)   (12)
    0x59,                 // pop ecx (this pointer)
    0x8d, 0x1d, 0, 0, 0, 0, // lea ebx, CallCompleted (insert address for CallCompleted) (19)
    0x89, 0x1c, 0x24,     // mov dword ptr [esp], ebx
    0xe9, 0, 0, 0, 0,     // jmp ChainFunction (insert displacement for Chain Func)  (27)     
  };

  HANDLE hProcess = GetCurrentProcess();

  DWORD dwMaxSize = sizeof(btHook); 
  DWORD* pdwHook = (DWORD*)VirtualAllocEx(hProcess, NULL, dwMaxSize, MEM_COMMIT|MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);

  if (!pdwHook)
    return false;

  HookContext* context = new HookContext(pFunctionToIntercept, method, m_Causality, listener, pszName, isStdCall);

  if (!context)
    return 0;

  DWORD dwChainAddress = (DWORD)CHAllocStub(hProcess);
  DWORD dwDisplacement_HookForTrace = CalcAddressOffset((DWORD)__OnBeforeExecute, (DWORD)pdwHook, 11, 5); 
  DWORD dwCallCompletedAddress = (DWORD)CallCompleted;
  DWORD dwDisplacement_ChainAddress = CalcAddressOffset((DWORD)dwChainAddress, (DWORD)pdwHook, 26, 5);

  // set the addresses need in the assembly code 
  memcpy(&btHook[6], &context, sizeof(LPVOID)); // set address to Hook context
  memcpy(&btHook[12], &dwDisplacement_HookForTrace, 4); // set address for call __HookForTrace
  memcpy(&btHook[19], &dwCallCompletedAddress, 4); // set address for call CallComplete
  memcpy(&btHook[27], &dwDisplacement_ChainAddress, 4); // set address for jmp ChainFunction 

  // copy the code to the hook
  memcpy(pdwHook, &btHook[0], sizeof(btHook));  

  // create the hook
  if (!CHHookProcEx(hProcess, pFunctionToIntercept, pdwHook, (LPVOID)dwChainAddress))
  {
    VirtualFree((LPVOID)pdwHook, dwMaxSize, MEM_RELEASE);

    return 0;
  }

  return context;
}

void CDynHooker::SetPause(bool bPause)
{
  m_bPaused = bPause;
}

bool CDynHooker::SetActive(LPVOID pInterceptedFunction, bool active)
{
  HookContext* context = 0;

  if (CDynHooker::GetHookContext(pInterceptedFunction, context))
  {
    context->SetActive(active);

    return true;
  }

  return false;
}

bool CDynHooker::HookInterface(IUnknown* pInterface, REFIID riid, HookedFunctionListener* listener)
{
  ISC::Interface* pInterfaceInfo = ISC::GetISC().GetInterface(riid);

  if (!pInterfaceInfo)
    return false;
//   return HookVTable(pInterface, riid, 3); // QI, AddRef, Release

  ATLASSERT(pInterfaceInfo);

  if (pInterfaceInfo && pInterface)
  {
    int nMethodCount = ISC::GetISC().GetMethodCount(pInterfaceInfo);

    for (int i = 0; i < nMethodCount; ++i)
    {
      DWORD dwAddressOfFunction = ((DWORD**)pInterface)[0][i];

      HookContext* context = NULL;
      if (GetHookContext((LPVOID)dwAddressOfFunction, context))
        continue;

      ISC::InterfaceMethod* method = ISC::GetMethod(pInterfaceInfo, i);

      CString name;
      name.Format("%s->%s", pInterfaceInfo->strName, method->strName);

      context = InstallDynamicHook((LPVOID)dwAddressOfFunction, name, method, listener, true);

    //  return 0 != context;
    }

    return true;

  }

  return false;
}

#pragma warning(default: 4482)