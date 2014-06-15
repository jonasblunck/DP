
#pragma once

template <typename T>
class TLS
{
  DWORD m_slot;
public:
  TLS<T>::TLS() 
  {
    m_slot = ::TlsAlloc();
  }

  T get()
  {
    return reinterpret_cast<T>(::TlsGetValue(m_slot));
  }

  void set(T t)
  {
    BOOL b = ::TlsSetValue(m_slot, (LPVOID)t);
    _ASSERTE(b);
  }
};

