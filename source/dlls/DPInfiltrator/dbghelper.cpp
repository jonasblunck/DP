#define WIN32_LEAN_AND_MEAN

#include "stdafx.h"
//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <dbghelp.h>

#include "dbghelper.h"

#pragma comment(linker, "/defaultlib:dbghelp.lib")

DbgHelper g_dbgHelper; //  global instance of class

FrameDump::FrameDump(	HANDLE hCurrentThread, 
						DWORD programCounter, 
						/* DWORD stack, */
						DWORD frame,
						ADDRESS_MODE addrMode )
{	
	m_hProcess = GetCurrentProcess();
	m_hCurrentThread = hCurrentThread;
    
    memset( &m_sf, 0, sizeof(STACKFRAME) );

	m_callback = NULL;
	m_symbolType = stParameter;

	// no max nesting
	m_maxNestingLevel = 0;

    #ifdef _M_IX86
    // Initialize the STACKFRAME structure for the first call.  This is only
    // necessary for Intel CPUs, and isn't mentioned in the documentation.
    m_sf.AddrPC.Offset       = programCounter;
    m_sf.AddrPC.Mode         = addrMode;
    m_sf.AddrStack.Offset    = 0 /* stack */;
    m_sf.AddrStack.Mode      = addrMode;
    m_sf.AddrFrame.Offset    = frame;
    m_sf.AddrFrame.Mode      = addrMode;    
    #endif
}

FrameDump::~FrameDump( )
{	
}

BOOL FrameDump::DumpSymbols( SymbolType symbolType, 
							 EnumerateTypesCallback * callback, 
							 void * callbackArg,
							 unsigned maxNestingLevel )
{
	// Set enum type filter
	m_symbolType = symbolType;
	m_callback = callback;
	m_callbackArg = callbackArg;

    // Use SymSetContext to get just the locals/params for this frame
    IMAGEHLP_STACK_FRAME imagehlpStackFrame;
    imagehlpStackFrame.InstructionOffset = m_sf.AddrPC.Offset;
    if ( !SymSetContext( m_hProcess, &imagehlpStackFrame, 0 ) )
	{
    DWORD dwErr = GetLastError();

		return FALSE;		
	}
	
	m_maxNestingLevel = maxNestingLevel;

    // Enumerate the locals/parameters
    if ( !SymEnumSymbols( m_hProcess, 0, 0, EnumerateSymbolsCallback, this ) )
	{
		return FALSE;		
	}	

	return TRUE;	
}

//=============================================================================
// Given a linear address, locates the module, section, and offset containing  
// that address.                                                               
//                                                                             
// Note: the szModule paramater buffer is an output buffer of length specified 
// by the len parameter (in characters!)                                       
//=============================================================================
BOOL FrameDump::GetLogicalAddress(
        PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset )
{
    MEMORY_BASIC_INFORMATION mbi;

    if ( !VirtualQuery( addr, &mbi, sizeof(mbi) ) )
        return FALSE;

    DWORD hMod = (DWORD)mbi.AllocationBase;

    if ( !GetModuleFileName( (HMODULE)hMod, szModule, len ) )
        return FALSE;

    // Point to the DOS header in memory
    PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

    // From the DOS header, find the NT (PE) header
    PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );

    DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

    // Iterate through the section table, looking for the one that encompasses
    // the linear address.
    for (   unsigned i = 0;
            i < pNtHdr->FileHeader.NumberOfSections;
            i++, pSection++ )
    {
        DWORD sectionStart = pSection->VirtualAddress;
        DWORD sectionEnd = sectionStart
                    + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

        // Is the address in this section???
        if ( (rva >= sectionStart) && (rva <= sectionEnd) )
        {
            // Yes, address is in the section.  Calculate section and offset,
            // and store in the "section" & "offset" params, which were
            // passed by reference.
            section = i+1;
            offset = rva - sectionStart;
            return TRUE;
        }
    }

    return FALSE;   // Should never get here!
}

//////////////////////////////////////////////////////////////////////////////
// The function invoked by SymEnumSymbols
//////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK
FrameDump::EnumerateSymbolsCallback(
    PSYMBOL_INFO  pSymInfo,
    ULONG         SymbolSize,
    PVOID         UserContext )
{

    __try
    {
        ( (FrameDump *) UserContext )->ExtractSymbolValue( pSymInfo );            
    }
    __except( 1 )
    {
        // _tprintf( _T("punting on symbol %s\r\n"), pSymInfo->Name );
    }

    return TRUE;
}

BOOL FrameDump::ExtractSymbolValue(
            PSYMBOL_INFO pSym )
{
	SymbolType symbolType;

    // Indicate if the variable is a local or parameter
    if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_PARAMETER )
	{
		if ( m_symbolType & stParameter )
			symbolType = stParameter;
		else		
			return TRUE;
	}
	else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_LOCAL )
	{
		if ( m_symbolType & stLocal )     
			symbolType = stLocal;
		else
			return TRUE;
	}

    // If it's a function, don't do anything.
    if ( pSym->Tag == 5 )   // SymTagFunction from CVCONST.H from the DIA SDK
        return TRUE;

    // Emit the variable name    
    DWORD_PTR pVariable = 0;    // Will point to the variable's data in memory

    if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGRELATIVE )
    {
        // if ( pSym->Register == 8 )   // EBP is the value 8 (in DBGHELP 5.1)
        {                               //  This may change!!!
            pVariable = m_sf.AddrFrame.Offset;
            pVariable += (DWORD_PTR)pSym->Address;
        }
        // else
        //  return false;
    }
    else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGISTER )
    {
        return TRUE;   // Don't try to report register variable
    }
	else
    {
		if ( m_symbolType & stGlobal )
		{
			pVariable = (DWORD_PTR)pSym->Address;   // It must be a global variable		
			symbolType  = stGlobal;
		}
		else
			return TRUE;
    }

	WCHAR pwszName[256];
	mbstowcs( pwszName, pSym->Name, 256 );

    if ( !DumpTypeIndex( symbolType, pwszName, pSym->ModBase, pSym->TypeIndex, 0, pVariable, pSym->Size ) )
    {
		// the callback signaled to stop enumeration
		return FALSE;
	}

    return TRUE;
}

struct TypeInfos
{
	IMAGEHLP_SYMBOL_TYPE_INFO typeInfoGet;
	char desc[256];
};

void DumpTypeInfo( HANDLE hProcess, DWORD64 modBase, DWORD dwTypeIndex )
{
	struct TypeInfos typesDword[] = {
		{ TI_GET_SYMTAG, "TI_GET_SYMTAG" },
		{ TI_GET_SYMINDEX, "TI_GET_SYMINDEX" },
		{ TI_GET_ADDRESSOFFSET, "TI_GET_ADDRESSOFFSET" },
		{ TI_GET_ARRAYINDEXTYPEID, "TI_GET_ARRAYINDEXTYPEID" },
		{ TI_GET_BASETYPE, "TI_GET_BASETYPE" },
		{ TI_GET_BITPOSITION, "TI_GET_BITPOSITION" },
		{ TI_GET_CALLING_CONVENTION, "TI_GET_CALLING_CONVENTION" },
		{ TI_GET_CHILDRENCOUNT, "TI_GET_CHILDRENCOUNT" },
		{ TI_GET_DATAKIND, "TI_GET_DATAKIND" },
		{ TI_GET_COUNT, "TI_GET_COUNT" },
		{ TI_GET_CLASSPARENTID, "TI_GET_CLASSPARENTID" },
		{ TI_GET_NESTED, "TI_GET_NESTED" },
		{ TI_GET_LEXICALPARENT, "TI_GET_LEXICALPARENT" },
		{ TI_GET_OFFSET, "TI_GET_OFFSET" },
		{ TI_GET_TYPEID, "TI_GET_TYPEID" },
		{ TI_GET_UDTKIND, "TI_GET_UDTKIND" },
		{ TI_GET_VIRTUALBASECLASS, "TI_GET_VIRTUALBASECLASS" },
		{ TI_GET_VIRTUALBASEPOINTEROFFSET, "TI_GET_VIRTUALBASEPOINTEROFFSET" },
	};

    /*TI_GET_SYMNAME,
    TI_GET_LENGTH,
    TI_GET_TYPE,
    TI_FINDCHILDREN,
    TI_GET_VALUE,
    TI_GET_VIRTUALTABLESHAPEID,
    TI_GET_ADDRESS,
    TI_GET_THISADJUST,*/

	DWORD dw;
	for(int i=0; i<sizeof(typesDword) / sizeof(TypeInfos); i++)
	{
		SymGetTypeInfo( hProcess, modBase, dwTypeIndex, typesDword[i].typeInfoGet,
					&dw );
		printf(" %s: %d ", typesDword[i].desc, dw);
	}
	printf("\n");
}

BOOL FrameDump::DumpTypeIndex(   
		SymbolType symbolType,
		LPCWSTR variableName,
        DWORD64 modBase,
        DWORD dwTypeIndex,
        unsigned nestingLevel,		
        DWORD_PTR offset,
		DWORD64 size )
{
	// Assume failure
	BOOL bRet = FALSE;

	DWORD dwChildrenCount = 0;
	DWORD dwArrayCount = 0;
	enum SymTagEnum dwSymTag = SymTagNull;
    WCHAR * pwszTypeName = NULL;

    struct FINDCHILDREN : TI_FINDCHILDREN_PARAMS
    {
        ULONG   MoreChildIds[1024];
        FINDCHILDREN(){Count = sizeof(MoreChildIds) / sizeof(MoreChildIds[0]);}
    } children;

	if ( m_maxNestingLevel != 0 && nestingLevel >= m_maxNestingLevel )
	{
		// Reached the max
		bRet = TRUE;
		goto cleanup;
	}

//	 DumpTypeInfo ( m_hProcess, modBase, dwTypeIndex );

	BasicType basicType = GetBasicType( dwTypeIndex, modBase );

	if ( 0 && basicType == btNoType )
	{
		SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_TYPEID,
						&dwTypeIndex );   		
	}

    // Get the name of the symbol.  This will either be a Type name (if a UDT),
    // or the structure member name.
	SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_SYMNAME,
					&pwszTypeName );    

    // Determine how many children this type has.    
    SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_CHILDRENCOUNT,
                    &dwChildrenCount );
	
    SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_COUNT,
                    &dwArrayCount );

    SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_SYMTAG,
                    &dwSymTag );   

	if ( dwSymTag == SymTagFunction )
	{
		// ignore this type
		bRet = TRUE;
		goto cleanup;
	}

    if ( !dwChildrenCount )     // If no children, we're done
	{
		DWORD dwLevelsOfIndirection = 0;        

		if ( basicType == btNoType )
		{
			// This type is not a UDT and not a basic type
			if ( dwSymTag == SymTagPointerType )
			{
				// Some kind of pointer, let's see how deep it goes
				dwLevelsOfIndirection = 1;

				// Let's find the levels of indirection
				DWORD dwTypeId2 = dwTypeIndex;
				while ( SymGetTypeInfo( m_hProcess, modBase, dwTypeId2, TI_GET_TYPEID,
									&dwTypeId2 ) && dwTypeId2 != 0 )
				{				
					enum SymTagEnum dwSymTag2;
					SymGetTypeInfo( m_hProcess, modBase, dwTypeId2, TI_GET_SYMTAG,
									&dwSymTag2 );

					if ( dwSymTag2 == SymTagPointerType )
					{
						dwLevelsOfIndirection++;
					}
					else
					{
						// This is the end of the line, this is final pointed to type

						if ( pwszTypeName )
						{
							LocalFree( pwszTypeName );
							pwszTypeName = NULL;
						}

						SymGetTypeInfo( m_hProcess, modBase, dwTypeId2, TI_GET_SYMNAME,
										&pwszTypeName );
						
						basicType = GetBasicType( dwTypeId2, modBase );
						break;
					}
				}
			} 
			else if ( dwSymTag == SymTagData )
			{
				// This is a member of some UDT, so we'll "dereference" this and redo
				SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_TYPEID,
						&dwTypeIndex );   	

				// We'll redo this
				bRet = DumpTypeIndex( symbolType, pwszTypeName, modBase,
												dwTypeIndex, nestingLevel,
												offset, size );

				goto cleanup;
			}
		}

		// If the child wasn't a UDT, format it appropriately
		DWORD_PTR dwFinalOffset;
		ULONG64 length;

		FormatNonUDT( modBase, dwTypeIndex, offset, &basicType, &dwFinalOffset, &length );

		if ( m_callback )
		{			
			if ( ( *m_callback )( symbolType, 
								  basicType,
								  variableName ? pwszTypeName : NULL,
								  (enum SymTagEnum)dwSymTag,
								  dwArrayCount,
								  dwLevelsOfIndirection,
								  variableName ? variableName : pwszTypeName, 
								  (PVOID)dwFinalOffset, 
								  length, 
								  nestingLevel, 								  
								  m_callbackArg ) == FALSE )
			{
				// the callback signaled to stop enumeration				
				bRet = FALSE;
				goto cleanup;
			}
		}

		bRet = TRUE;		
        goto cleanup;
	}

    // Prepare to get an array of "TypeIds", representing each of the children.
    // SymGetTypeInfo(TI_FINDCHILDREN) expects more memory than just a
    // TI_FINDCHILDREN_PARAMS struct has.  Use derivation to accomplish this.

    children.Count = dwChildrenCount;
    children.Start = 0;

    // Get the array of TypeIds, one for each child type
    if ( !SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_FINDCHILDREN,
                            &children ) )
    {
		bRet = TRUE;
        goto cleanup;
    }

    // If the child wasn't a UDT, format it appropriately
    DWORD_PTR dwFinalOffset;
	ULONG64 length;

	FormatNonUDT( modBase, dwTypeIndex, offset, &basicType, &dwFinalOffset, &length );

	if ( m_callback )
	{
		// This is a UDT (struct/class/unino)
		if ( ( *m_callback )( symbolType, basicType, pwszTypeName, (enum SymTagEnum)dwSymTag, dwArrayCount, 0, variableName, (PVOID)dwFinalOffset, length, nestingLevel, m_callbackArg ) == FALSE )
		{
			// the callback signaled to stop enumeration				
			bRet = FALSE;
			goto cleanup;
		}
	}

    // Iterate through each of the children
    for ( unsigned i = 0; i < dwChildrenCount; i++ )
    {
		// Get the offset of the child member, relative to its parent
		DWORD dwMemberOffset;
		SymGetTypeInfo( m_hProcess, modBase, children.ChildId[i],
						TI_GET_OFFSET, &dwMemberOffset );

		// Calculate the address of the member
		DWORD_PTR dwFinalOffset = offset + dwMemberOffset;

        // Recurse for each of the child types        
        BOOL bRet2 = DumpTypeIndex( symbolType, NULL, modBase,
                                        children.ChildId[i], nestingLevel+1,										
                                        dwFinalOffset, size );

		if ( FALSE == bRet2 )
		{
			bRet = FALSE;
			goto cleanup;
		}
    }

	bRet = TRUE;

cleanup:
	if ( pwszTypeName )
	{
		LocalFree( pwszTypeName );
	}
    
    return bRet;
}

void FrameDump::FormatNonUDT( DWORD64 modBase, ULONG childTypeId, DWORD_PTR offset, BasicType * pBasicType, DWORD_PTR * pDwFinalOffset, ULONG64 * pLength )
{
    // Get the offset of the child member, relative to its parent
    DWORD dwMemberOffset;
    SymGetTypeInfo( m_hProcess, modBase, childTypeId,
                    TI_GET_OFFSET, &dwMemberOffset );

    // Get the real "TypeId" of the child.  We need this for the
    // SymGetTypeInfo( TI_GET_TYPEID ) call below.
    DWORD typeId;
    SymGetTypeInfo( m_hProcess, modBase, childTypeId,
                    TI_GET_TYPEID, &typeId );

    // Get the size of the child member
    ULONG64 length = 0;
    SymGetTypeInfo(m_hProcess, modBase, typeId, TI_GET_LENGTH, &length);

    // Calculate the address of the member
    DWORD_PTR dwFinalOffset = offset + dwMemberOffset;

    *pBasicType = GetBasicType( childTypeId, modBase );
	*pDwFinalOffset = dwFinalOffset;

	if ( 0 == length && btNoType != *pBasicType )
	{
		// Let's fix up the length for basic types, things like unsigned long dont
		// get back the proper length
		switch (*pBasicType)
		{
		case btChar:
			length = 1;
			break;
		case btWChar:
			length = 2;
			break;
		case btInt:
		case btUInt:
		case btFloat:
		case btBool:
		case btLong:
		case btULong:
			length = 4;
			break;
		default:			
			break;
		}
	}

	*pLength = length;
}

BasicType FrameDump::GetBasicType( DWORD typeIndex, DWORD64 modBase )
{
    BasicType basicType;
    if ( SymGetTypeInfo( m_hProcess, modBase, typeIndex,
                        TI_GET_BASETYPE, &basicType ) )
    {
        return basicType;
    }

    // Get the real "TypeId" of the child.  We need this for the
    // SymGetTypeInfo( TI_GET_TYPEID ) call below.
    DWORD typeId;
    if (SymGetTypeInfo(m_hProcess,modBase, typeIndex, TI_GET_TYPEID, &typeId))
    {
        if ( SymGetTypeInfo( m_hProcess, modBase, typeId, TI_GET_BASETYPE,
                            &basicType ) )
        {
            return basicType;
        }
    }

    return btNoType;
}

// TODO: I want this to be on demand only
DbgHelper::DbgHelper( )
{
	// Setup the dbghelp library
	SymSetOptions( SYMOPT_DEFERRED_LOADS );

	// Initialize DbgHelp
	HANDLE hProcess = GetCurrentProcess();
	if ( !SymInitialize( hProcess, 0, TRUE ) )
		return;
}

DbgHelper::~DbgHelper( )
{
	SymCleanup( GetCurrentProcess() );
}