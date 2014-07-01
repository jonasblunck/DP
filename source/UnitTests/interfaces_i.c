

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Jun 27 09:59:09 2014
 */
/* Compiler settings for interfaces.idl:
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

MIDL_DEFINE_GUID(IID, IID_ITestInterface2,0xA3425BD7,0xD547,0x4636,0xA6,0x66,0x14,0x7C,0x35,0xDE,0x13,0x27);


MIDL_DEFINE_GUID(IID, IID_ITestInterface3,0xA3425BD7,0xD547,0x4636,0xA6,0x66,0x14,0x7C,0x35,0xDE,0x13,0x29);


MIDL_DEFINE_GUID(IID, IID_ITestInterface,0x48937FFC,0x8DD2,0x4739,0x9F,0x54,0xE5,0xB9,0x69,0xDD,0x9B,0xDF);


MIDL_DEFINE_GUID(IID, LIBID_UnitTestLibrary,0x97BE6885,0xAC69,0x472E,0xB1,0x53,0xE1,0xA1,0xA6,0x5C,0x0C,0x35);


MIDL_DEFINE_GUID(CLSID, CLSID_UnitTestCoClassNotToBeCreated,0xDAE2DE76,0xCB4A,0x4EE7,0x9D,0x49,0xDC,0xD7,0x63,0xEC,0x9E,0xCF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



