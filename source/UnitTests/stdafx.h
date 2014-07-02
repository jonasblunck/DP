// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
extern bool s_unittest_success;


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <atlbase.h>
#include <atlstr.h>

#include "..\dlls\chainhook\ChainHookAPI.h"

#include "TestAsserts.h"

#define _NO_CVCONST_H
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

#define ENSURE_RELEASE_NOT_OPT(x) OutputDebugString(x)

#include "GuidHelpers.h"
#include "CS.h"

#define DLL_LOCATION "c:\\dev\\c++\\dp\\source\\bin\\unittests.dll"

