
#pragma once

struct CallContext
{
public:

  HookContext* hookContext;
  DWORD returnAddress;

  CallContext(HookContext* context, DWORD address)
  {
    hookContext = context;
    returnAddress = address;
  }

};

class CallStack
{
  DWORD m_tlsSlot;
  
  std::list<CallContext>& GetCurrentContext()
  {
    std::list<CallContext>* context = reinterpret_cast<std::list<CallContext>*>(::TlsGetValue(m_tlsSlot));

    if (!context)
    {
      context = new std::list<CallContext>();

      TlsSetValue(m_tlsSlot, context);
    }

    return *context;
  }

public:
  CallStack()
  {
    m_tlsSlot = ::TlsAlloc();
  }

  void Push(CallContext& context)
  {
    GetCurrentContext().push_front(context);
  }

  CallContext Pop()
  {
    CallContext context = GetCurrentContext().front();
    GetCurrentContext().pop_front();

    return context;
  }

};
