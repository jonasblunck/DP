
#pragma once

#include <atlstr.h>

inline SHORT TranslateNamedType(const CString& namedType)
{
  #define LOOKUP_ELEMENT(x) { x, #x }
  #define NELM(x) sizeof(x) / sizeof(x[0])

  static struct _lookup
  {
    SHORT typeID;
    char typeName[16];
  } lookup [] = 
  {
    { VT_INT, "INT" },
    { VT_UINT, "UINT" },
    { VT_I4, "LONG" },
    { VT_UI4, "ULONG" },
    { VT_I8, "DWORD" },
    { VT_R4, "FLOAT" },
    { VT_R8, "DOUBLE" },
    { VT_UI2, "USHORT" },
    { VT_I2, "SHORT" },
    { VT_BOOL, "BOOL" },
    // strings
    { VT_BSTR, "BSTR" },
    { VT_LPWSTR, "LPWSTR" },
    { VT_LPSTR, "LPSTR" },
    { VT_LPSTR, "CHAR*" },

    // typical type defs
    { VT_VOID, "HANDLE" },
    { VT_VOID, "LPVOID" },
    { VT_VOID, "VOID*" },
  };

  for (int i = 0; i < NELM(lookup); ++i)
  {
    if (namedType == CString(lookup[i].typeName))
    {
      return lookup[i].typeID;
    }
  }

  return VT_EMPTY;
}

