// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__C23D82D5_F372_4E0F_A56B_B6463ADE4E7B__INCLUDED_)
#define AFX_STDAFX_H__C23D82D5_F372_4E0F_A56B_B6463ADE4E7B__INCLUDED_

// Change these values to use different versions
#define WINVER		0x0500
#define _WIN32_IE	0x0400
#define _RICHEDIT_VER	0x0100

#define _WIN32_WINNT 0x0500
#define _ATL_FREE_THREADED

// #define _ATL_DEBUG_INTERFACES
// #define _ATL_DEBUG_REFCOUNT
//#define _WTL_USE_CSTRING

#define _WTL_NO_CSTRING

#include <atlbase.h>
#include <atlstr.h>
#include <atlapp.h>

extern CServerAppModule _Module;

#include <atlcom.h>
#include <atlwin.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlctrlw.h>
#include <atlsplit.h>
#include <atlframe.h>
#include <atlcrack.h>
#include <atlmisc.h>

// STL
#include <map>
#include <vector>

// My headers
#include "constant.h"
#include "smarts.h"

#include "OptionsStorage.h"
#include "coms.h"

// Windows headers
#define _NO_CVCONST_H
#include <dbghelp.h>
#include <psapi.h>
#include <ShlObj.h>

#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "psapi.lib")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#include "CS.h"

#endif // !defined(AFX_STDAFX_H__C23D82D5_F372_4E0F_A56B_B6463ADE4E7B__INCLUDED_)
