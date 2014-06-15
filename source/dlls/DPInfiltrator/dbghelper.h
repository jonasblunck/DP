#pragma once

#include <dbghelp.h>

enum BasicType  // Stolen from CVCONST.H in the DIA 2.0 SDK
{
    btNoType = 0,
    btVoid = 1,
    btChar = 2,
    btWChar = 3,
    btInt = 6,
    btUInt = 7,
    btFloat = 8,
    btBCD = 9,
    btBool = 10,
    btLong = 13,
    btULong = 14,
    btCurrency = 25,
    btDate = 26,
    btVariant = 27,
    btComplex = 28,
    btBit = 29,
    btBSTR = 30,
    btHresult = 31,	
};

enum SymbolType
{
	stParameter = 0x1,
	stLocal = 0x2,
	stGlobal = 0x4
};

enum SymTagEnum // Stolen from DIA SDK
{
   SymTagNull,
   SymTagExe,
   SymTagCompiland,
   SymTagCompilandDetails,
   SymTagCompilandEnv,
   SymTagFunction,
   SymTagBlock,
   SymTagData,
   SymTagAnnotation,
   SymTagLabel,
   SymTagPublicSymbol,
   SymTagUDT,
   SymTagEnum,
   SymTagFunctionType,
   SymTagPointerType,
   SymTagArrayType, 
   SymTagBaseType, 
   SymTagTypedef, 
   SymTagBaseClass,
   SymTagFriend,
   SymTagFunctionArgType, 
   SymTagFuncDebugStart, 
   SymTagFuncDebugEnd,
   SymTagUsingNamespace, 
   SymTagVTableShape,
   SymTagVTable,
   SymTagCustom,
   SymTagThunk,
   SymTagCustomType,
   SymTagManagedType,
   SymTagDimension
};

typedef BOOL CALLBACK EnumerateTypesCallback ( SymbolType symbolType, 
											   BasicType basicType, 
											   LPCWSTR typeName, 
											   enum SymTagEnum typeTag,
											   ULONG typeArrayCount,
											   ULONG levelsOfIndirection,
											   LPCWSTR symbolName, 											   
											   PVOID symbolValueAddr, 
											   ULONG64 symbolValueLen, 
											   ULONG udtDepth, 
											   void * arg );

class FrameDump
{
public:
    
	// TODO: Does this work with FPO optimization?
	// Dumps the frame in the current process, given thread handle and programCounter = eip, stack = esp, frame = ebp
    FrameDump( HANDLE hCurrentThread, DWORD programCounter, /* DWORD stack, */ DWORD frame, ADDRESS_MODE addrMode = AddrModeFlat );
    ~FrameDump();

	BOOL DumpSymbols( SymbolType symbolType, 
					  EnumerateTypesCallback * callback, 
					  void * callbackArg,
					  unsigned maxNestingLevel = 0);

    static BOOL GetLogicalAddress(  PVOID addr, PTSTR szModule, DWORD len,
                                    DWORD& section, DWORD& offset );

	static LPCWSTR GetBasicTypeDescription( BasicType basicType )
	{
		switch (basicType)
		{		
		case btNoType:
			return 0;
		case btVoid:
			return L"void";
		case btChar:
			return L"char";
		case btWChar:
			return L"wchar";
		case btInt:
			return L"long";
		case btUInt:
			return L"unsigned long";
		case btFloat:
			return L"float";
		case btBCD:
			return L"bcd";
		case btBool:
			return L"bool";
		case btLong:
			return L"long";
		case btULong:
			return L"unsigned long";
		case btCurrency:
			return L"currency";
		case btDate:
			return L"date";
		case btVariant:
			return L"variant";
		case btComplex:
			return L"complex";
		case btBit:
			return L"bit";
		case btBSTR:
			return L"BSTR";
		case btHresult:
			return L"HRESULT";
		default:
			return L"null";
		}
	}

private:

    static BOOL CALLBACK EnumerateSymbolsCallback( PSYMBOL_INFO,ULONG, PVOID );

	BOOL ExtractSymbolValue( PSYMBOL_INFO pSym );

	BasicType GetBasicType( DWORD typeIndex, DWORD64 modBase );

	// Returns FALSE to stop enumeration
	BOOL DumpTypeIndex( SymbolType symbolType, 
						LPCWSTR variableName, 
						DWORD64 modBase, 
						DWORD dwTypeIndex, 
						unsigned nestingLevel, 						
						DWORD_PTR offset, 
						DWORD64 size );

	void FormatNonUDT( DWORD64 modBase, 
					   ULONG childTypeId, 
					   DWORD_PTR offset, 
					   BasicType * pBasicType, 
					   DWORD_PTR * pDwFinalOffset, 
					   ULONG64 * pLength );

    HANDLE m_hProcess;
	HANDLE m_hCurrentThread;	

	// Save values for DumpParameters
	DWORD m_symbolType;
	EnumerateTypesCallback * m_callback;
	void * m_callbackArg;
	STACKFRAME m_sf;
	unsigned m_maxNestingLevel;

};

// All dbghelp functions are NOT thread-safe, and only 1 instance can exist per process
class DbgHelper
{
public:

	DbgHelper();
	~DbgHelper();
};

