
#pragma once

#include "ParameterTypes.h"
#include "LogicalThreadMgr.h"
#include "CallStackParam.h"
#include "HookedFunctionListener.h"
#include "ISC.h"

class HookContext
{
protected:
  LogicalThreadMgr& m_threadManager;
  HookedFunctionListener* m_listener;
  bool m_active;
  bool m_isStdCall;
  CString m_name;
  CString m_buffer;
  bool m_error;
  void* m_pInterceptedFunction; // which function am I intercepting?
  ISC::InterfaceMethod* m_methodInfo;

  void PreExecuteCheckParam(ISC::InterfaceParam& param, LPVOID* ppStack)
  {
    if (param.vtType == VT_CLSID && param.IsPointer())
    {
      GUID* guid = (GUID*)ppStack[0]; // only a pointer to the GUID is placed on the stack
      memcpy(&param.riid, guid, sizeof(GUID));
    }

    if (param.bOutParam && param.pIidIsParam)
    {
      // this is an outgoing interface, so store the VOID*
      param.ppv = (void**)ppStack[0];
    }
  }

  void WalkCallstack(LPVOID* ppStackArgs, CString& formatted)
  {
    LPVOID* pp = m_isStdCall ? ++ppStackArgs : ppStackArgs;

    for (unsigned int i = 0; i < m_methodInfo->nParamCount; ++i)
    {
      PreExecuteCheckParam(m_methodInfo->pParams[i], pp);

      CString argument;
      CallStackParam par(&m_methodInfo->pParams[i]);

      bool paramOk = par.ParseCallStackParam(pp, argument);

      if (!formatted.IsEmpty())
        formatted += ", ";

      formatted += argument;

      if (!paramOk)
        break;
    }
  }

  bool SafeGetArguments(CString& buffer, CString& tmp, LPVOID* ppStackArgs)
  {
    __try
    {
      if (!m_name.IsEmpty())
      {
        WalkCallstack(ppStackArgs, tmp);

        buffer.Format("%s(%s)", m_name, tmp);
      }
      else
      {
        WalkCallstack(ppStackArgs, buffer);
      }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
      return false;
    }

    return true;
  }

  void PostExecuteHandleOutParams()
  {
    for (UINT i = 0; i < m_methodInfo->nParamCount; ++i)
    {
      if (m_methodInfo->pParams[i].bOutParam && m_methodInfo->pParams[i].pIidIsParam)
      {
        if (m_methodInfo->pParams[i].pIidIsParam->riid != GUID_NULL)
        {
          IUnknown* pUnk = reinterpret_cast<IUnknown*>(*m_methodInfo->pParams[i].ppv);

          if (NULL != pUnk)
          {
            CDynHooker h;
            h.HookInterface(pUnk, m_methodInfo->pParams[i].pIidIsParam->riid, m_listener);
          }

        }
      }
    }
  }

public:

  HookContext(void* pInterceptedFunction, ISC::InterfaceMethod* methodInfo,
    LogicalThreadMgr& threadManager, HookedFunctionListener* listener, LPCTSTR pszName, bool isStdCall = false) : m_threadManager(threadManager), m_listener(listener), m_active(true)
  {
    m_methodInfo = methodInfo;
    m_pInterceptedFunction = pInterceptedFunction;
    m_name = pszName;
    m_isStdCall = isStdCall;
    m_error = false;
  }

  ~HookContext()
  {
  }

  void OnAfterExecute(int returnValue)
  {
    if (!m_error)
      m_listener->OnHookedFunction((long)m_pInterceptedFunction, m_buffer, returnValue);

    PostExecuteHandleOutParams();
  }

  void OnBeforeExecute(LPVOID* ppStackArgs)
  {
    m_error = false;

  //  if (!m_threadManager.IsThreadInCall())
    {
    //  CAUSALITY(m_threadManager); // register "in-call" state // TODO: prove this check necessary...

      m_buffer.Empty();
      CString tmp;

      if (!SafeGetArguments(m_buffer, tmp, ppStackArgs))
        m_error = true;
    }
  }

  void SetActive(bool active)
  {
    m_active = active;
  }

  bool IsActive() const
  {
    return m_active;
  }

  ISC::InterfaceMethod* GetMethodInfo() const
  {
    return m_methodInfo;
  }
};
