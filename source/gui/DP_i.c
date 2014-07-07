

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jul 03 20:16:59 2014
 */
/* Compiler settings for DP.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITypeLibViewer,0xfc37e5ba,0x4a8e,0x11ce,0x87,0x0b,0x08,0x00,0x36,0x8d,0x23,0x02);


MIDL_DEFINE_GUID(IID, IID__IDummy,0x7DD08DA3,0x79A5,0x407E,0xAF,0xF8,0xA1,0xDB,0x3B,0x51,0x8F,0x19);


MIDL_DEFINE_GUID(IID, LIBID_DPLib,0x2FFC201E,0x7E58,0x4133,0xA8,0x90,0x38,0x74,0x38,0xA4,0x7C,0x10);


MIDL_DEFINE_GUID(CLSID, CLSID_TraceListener,0xA115A87C,0x5C74,0x460E,0x91,0x80,0xE3,0x94,0xD2,0x97,0x6C,0xD0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



