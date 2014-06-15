#include "stdafx.h"

#pragma optimize ("", off)

class TestData
{
  void IntFunction(int, int, int) {}
  void LongFunction(long, long) {}
  void StringFunction(LPCTSTR) {}
  void CharFunction(char) {}
  void DwordPtrFunction(DWORD*) {}
  void Mixed(DWORD*, char*, int) {}
  void PassingReference(const TestData& data) {}
  void PointerToPointer(void**) {}

public:

  TestData()
  {
    IntFunction(1, 2, 3);
    LongFunction(1, 2);
    StringFunction("argument");
    CharFunction('a');
    DwordPtrFunction((DWORD*)0x2929292);
    Mixed((DWORD*)0x9999, "kjhljl", 2);
    PassingReference(*this);
    PointerToPointer(0);
  }
};

static TestData s_td;

#pragma optimize ("", on)