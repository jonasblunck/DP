// DPInfiltrator.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Infiltrator.h"

void __stdcall InitializeOnLoad();

BOOL APIENTRY DllMain(HINSTANCE hInstance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
      // startup WSA
      WORD wVersionRequested;
      WSADATA wsaData;
      wVersionRequested = MAKEWORD(2, 2);

      WSAStartup(wVersionRequested, &wsaData);

      // Disable multiple calls thread attachment?
      DisableThreadLibraryCalls(hInstance);

      InitializeOnLoad();
    }
    //else if (ul_reason_for_call == DLL_PROCESS_DETACH)
    //  Infiltrator::TerminateInfiltrator();

    return TRUE;
}

