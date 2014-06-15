#ifndef __TRACEPACKET_H__
#define __TRACEPACKET_H__

struct TRACEPACKET
{
	DWORD dwPID;
	DWORD dwHookID;
	DWORD dwRetVal;
	BYTE pbStack[40];
};

#endif //__TRACEPACKET_H__
