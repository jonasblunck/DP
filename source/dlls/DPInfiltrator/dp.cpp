#include "stdafx.h"
#include "dp.h"
#include <stdlib.h>

#define countof(x) ((sizeof(x)/sizeof(char)) - sizeof(char))

void AddToList(const char *type, const char *symbol, const char *value, ULONG udtDepth, void * arg)
{
	ParamList * list = ( ParamList * ) arg;
	ParamInfo * info = new ParamInfo( type, symbol, value, udtDepth );

	list->push_back(info);
}

BOOL CALLBACK populateEnumCallback ( SymbolType symbolType, 
							 BasicType basicType, 
							 LPCWSTR typeName, 
							 enum SymTagEnum typeTag,
							 ULONG typeArrayCount,
							 ULONG levelsOfIndirection,
							 LPCWSTR symbolName, 
							 PVOID symbolValueAddr, 
							 ULONG64 symbolValueLen, 
							 ULONG udtDepth, 
							 void * arg )
{
	char typebuf[256], *type = typebuf;	
	char symbolbuf[256], valuebuf[256];

	typebuf[0] = valuebuf[0] = symbolbuf[0] = '\0';

	// Typename
	//type += sprintf(type, "%ls", typeName ? typeName : FrameDump::GetBasicTypeDescription( basicType ) );
	
	if ( typeTag == SymTagPointerType )
	{
		for ( ULONG i=0; i<=levelsOfIndirection; i++)
		{
			type += sprintf(type, " *");
		}		
	}

	if ( typeArrayCount )
	{
		type += sprintf(type, "[%d]", typeArrayCount);
	}	

	_snprintf(symbolbuf, countof(symbolbuf),  "%ls",
						symbolName );
	symbolbuf[countof(symbolbuf)] = '\0';

	__try
	{
		if ( typeTag == SymTagArrayType && basicType == btChar )
		{
			// This is a character array
			if ( !IsBadStringPtr( (PTSTR)symbolValueAddr, typeArrayCount ) )
			{
				_snprintf( valuebuf, countof(valuebuf),  "\"%.31s\"",
						(PTSTR)symbolValueAddr );
			}
			else
				_snprintf( valuebuf, countof(valuebuf),  "%X",
						*(PDWORD)symbolValueAddr );
		}
    else if (basicType == btChar && typeTag == SymTagPointerType)
    {
      char* pszValue = (char*)(((int*)symbolValueAddr)[0]);
			_snprintf( valuebuf, countof(valuebuf), "%s", pszValue );
    }
		// Format appropriately (assuming it's a 1, 2, or 4 bytes (!!!)	
		else if ( symbolValueLen == 1 )
			_snprintf( valuebuf, countof(valuebuf), "0x%X", *(PBYTE)symbolValueAddr );
		else if ( symbolValueLen == 2 )
			_snprintf( valuebuf, countof(valuebuf),  "0x%X", *(PWORD)symbolValueAddr );
		else if ( symbolValueLen == 4 )
		{
			if ( basicType == btFloat )
			{
				_snprintf( valuebuf, countof(valuebuf), "%f", *(PFLOAT)symbolValueAddr );
			}
			else if ( basicType == btChar )
			{
				if ( !IsBadStringPtr( *(PTSTR*)symbolValueAddr, 32) )
				{
					_snprintf( valuebuf, countof(valuebuf), "\"%.31s\"",
							*(PDWORD)symbolValueAddr );
				}
				else
					_snprintf( valuebuf, countof(valuebuf), "%X",
							*(PDWORD)symbolValueAddr );
			}
			else
				_snprintf( valuebuf, countof(valuebuf), "0x%X", *(PDWORD)symbolValueAddr );
		}
		else if ( symbolValueLen == 8 )
		{
			if ( basicType == btFloat )
			{
				_snprintf( valuebuf, countof(valuebuf), "%lf", *(double *)symbolValueAddr );
			}
			else
				_snprintf( valuebuf, countof(valuebuf), "0x%I64X", *(DWORD64*)symbolValueAddr );
		}
	}
	__except (1)
	{
		_snprintf( valuebuf, countof(valuebuf), "0x%I64X\n", *(DWORD64*)symbolValueAddr );
	}

	valuebuf[countof(valuebuf)] = '\0';

	AddToList( typebuf, symbolbuf, valuebuf, udtDepth, arg );

	return TRUE;
}
