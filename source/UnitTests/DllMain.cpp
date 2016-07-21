#include "stdafx.h"

CString g_DllLocation;

BOOL APIENTRY DllMain(HINSTANCE hInstance,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		GetModuleFileName(hInstance, g_DllLocation.GetBufferSetLength(MAX_PATH), MAX_PATH);

		g_DllLocation.ReleaseBuffer();

	}

	return TRUE;
}
