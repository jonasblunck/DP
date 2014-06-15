#pragma once

template< typename T >
class CBuffer
{
  T* m_buffer;
  int m_size;

public:
  CBuffer() : m_buffer(0), m_size(0)
  {
  }

  CBuffer(const CBuffer& b) : m_buffer(0), m_size(0)
  {
    operator = (b);
  }

  CBuffer& operator = (const CBuffer& r)
  {
    Append(r.get(), r.size());

    return *this;
  }

  ~CBuffer()
  {
    if (m_buffer)
    {
      delete [] m_buffer;
      m_buffer = 0;
      m_size = 0;
    }
  }

  template<typename T>
  void TakeOwnership(CBuffer<T>& l)
  {
    if (m_buffer)
      delete [] m_buffer;

    m_buffer = l.get();
    m_size = l.size();

    l.m_buffer = 0;
    l.m_size = 0;
  }

  const T* Append(T* buffer, int size)
  {
    int newSize = m_size + size;
    T* result = 0;
    
    if (size > 0)
      result = new T[newSize];

    memcpy(result, m_buffer, m_size);
    memcpy(result + m_size, buffer, size);

    if (m_buffer)
      delete [] m_buffer;

    m_buffer = result;
    m_size = newSize;

    return m_buffer;
  }

  T* detach() { T* b = m_buffer; m_buffer = 0; m_size = 0; return b; }
  T* get() const { return m_buffer; }
  int size() const { return m_size; }
  void clear() { if (m_buffer) delete [] m_buffer; m_buffer = 0; m_size = 0; }

};
