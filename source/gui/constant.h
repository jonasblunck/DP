#ifndef __CONSTANT_H__
#define __CONSTANT_H__

// Define custom message
#define WM_DP_TRACE_RECVD (WM_APP + 0x001)

// Define node levels
enum NODETYPE
{
	NODETYPE_PROCESSES = 0,
	NODETYPE_PROCESS = 1,
  NODETYPE_EXPORTS = 2,
  NODETYPE_DEBUGSYM = 3,
	NODETYPE_DLL
};

// Caption for error message boxes
const LPCTSTR ERROR_CAPTION = _T("DP Error");

// Image list indices
#define IMG_ROOT			0
#define IMG_PROCESS			1
#define IMG_DLL				2
#define IMG_FUNCTION		3
#define IMG_FUNCTION_HOOKED	4

// Default mask color
const COLORREF CR_BACKGROUND_COLOR = RGB(0, 128, 128);

#endif //__CONSTANT_H__
