
#pragma once

class _CSAuto
{
  CRITICAL_SECTION* m_pcs;
public:
  _CSAuto(CRITICAL_SECTION* p) : m_pcs(p)
  {
    _ASSERTE(m_pcs);

    if (m_pcs)
      EnterCriticalSection(m_pcs);
  }

  ~_CSAuto()
  {
    _ASSERTE(m_pcs);

    if (m_pcs)
    {
      LeaveCriticalSection(m_pcs);
      m_pcs = NULL;
    }

  }
};

#define CS(x) _CSAuto __cs(&x);
