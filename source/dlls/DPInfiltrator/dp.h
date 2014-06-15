#include <windows.h>

#include <string>
#include <list>

#include "dbghelper.h"

class ParamInfo
{
public:
	ParamInfo ( const char * _type,
				const char * _name,
				const char * _value,
				ULONG _depth ) :
					type(_type),
					name(_name),
					value(_value),
					depth(_depth)
	{
	}

	std::string type;
	std::string name;
	std::string value;
	ULONG depth;
};

typedef std::list<ParamInfo *> ParamList;

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
							 void * arg );