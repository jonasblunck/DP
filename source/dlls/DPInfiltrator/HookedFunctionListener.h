
#pragma once

#include <atlstr.h>

class HookedFunctionListener
{
public:
  virtual void OnHookedFunction(long id, const CString& strArguments, int returnValue) = 0;
};

  