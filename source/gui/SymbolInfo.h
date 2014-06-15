#pragma once

class CSymbolInfo
{
  PSYMBOL_INFO m_syminfo;

public:
  CSymbolInfo(PSYMBOL_INFO syminfo) : m_syminfo(syminfo)
  {
  }

  BOOL FindChildren(ULONG* childIndices, DWORD& bufferSize)
  {
    DWORD childCount = 0;

    if (SymGetTypeInfo(0, m_syminfo->ModBase, m_syminfo->TypeIndex, TI_GET_CHILDRENCOUNT, &childCount) &&
        childCount > 0)
    {
      int size = sizeof(TI_FINDCHILDREN_PARAMS) + childCount * sizeof(ULONG);
      TI_FINDCHILDREN_PARAMS* params = (TI_FINDCHILDREN_PARAMS*)_alloca(size);
      memset(params, 0, size);
      params->Count = childCount;

      if (SymGetTypeInfo(0, m_syminfo->ModBase, m_syminfo->TypeIndex, TI_FINDCHILDREN, params))
      {
        for (DWORD d = 0; (d < childCount) && (d < bufferSize); ++d)
          childIndices[d] = params->ChildId[d];

        bufferSize = childCount;

        return TRUE;
      }

    }

    return FALSE;
  }

  BOOL GetType(ULONG itemId, DWORD& type)
  {
    if (SymGetTypeInfo(0, m_syminfo->ModBase, itemId, TI_GET_TYPE, &type))
      return TRUE;

    return FALSE;
  }

  BOOL GetTypeId(ULONG itemId, DWORD& typeId)
  {
    if (SymGetTypeInfo(0, m_syminfo->ModBase, itemId, TI_GET_TYPEID, &typeId))
      return TRUE;

    return FALSE;
  }

  BOOL GetCallConvention(ULONG itemId, DWORD& callConventionId)
  {
    if (SymGetTypeInfo(0, m_syminfo->ModBase, itemId, TI_GET_CALLING_CONVENTION, &callConventionId))
      return TRUE;

    return FALSE;
  }

  BOOL GetTag(ULONG itemId, DWORD& tag)
  {
    if (SymGetTypeInfo(0, m_syminfo->ModBase, itemId, TI_GET_SYMTAG, &tag))
      return TRUE;

    return FALSE;
  }

  BOOL GetBaseType(ULONG itemId, DWORD& typeId)
  {
    if (SymGetTypeInfo(0, m_syminfo->ModBase, itemId, TI_GET_BASETYPE, &typeId))
      return TRUE;

    return FALSE;
  }
};

