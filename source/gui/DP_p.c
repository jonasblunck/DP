

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "DP.h"

#define TYPE_FORMAT_STRING_SIZE   77                                
#define PROC_FORMAT_STRING_SIZE   49                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _DP_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } DP_MIDL_TYPE_FORMAT_STRING;

typedef struct _DP_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } DP_MIDL_PROC_FORMAT_STRING;

typedef struct _DP_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } DP_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const DP_MIDL_TYPE_FORMAT_STRING DP__MIDL_TypeFormatString;
extern const DP_MIDL_PROC_FORMAT_STRING DP__MIDL_ProcFormatString;
extern const DP_MIDL_EXPR_FORMAT_STRING DP__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITypeLibViewer_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITypeLibViewer_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO _IDummy_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO _IDummy_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const DP_MIDL_PROC_FORMAT_STRING DP__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure View */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 10 */	NdrFcShort( 0x44 ),	/* 68 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 16 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hwndParent */

/* 24 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */

	/* Parameter riid */

/* 30 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Parameter punk */

/* 36 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	NdrFcShort( 0x3a ),	/* Type Offset=58 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 44 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const DP_MIDL_TYPE_FORMAT_STRING DP__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/*  8 */	NdrFcShort( 0x4 ),	/* 4 */
/* 10 */	NdrFcShort( 0x2 ),	/* 2 */
/* 12 */	NdrFcLong( 0x48746457 ),	/* 1215587415 */
/* 16 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 18 */	NdrFcLong( 0x52746457 ),	/* 1383359575 */
/* 22 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 24 */	NdrFcShort( 0xffff ),	/* Offset= -1 (23) */
/* 26 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (2) */
/* 36 */	
			0x11, 0x0,	/* FC_RP */
/* 38 */	NdrFcShort( 0x8 ),	/* Offset= 8 (46) */
/* 40 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 46 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 48 */	NdrFcShort( 0x10 ),	/* 16 */
/* 50 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 52 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 54 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (40) */
			0x5b,		/* FC_END */
/* 58 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 60 */	NdrFcLong( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 70 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 72 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 74 */	0x0,		/* 0 */
			0x46,		/* 70 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            HWND_UserSize
            ,HWND_UserMarshal
            ,HWND_UserUnmarshal
            ,HWND_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ITypeLibViewer, ver. 0.0,
   GUID={0xfc37e5ba,0x4a8e,0x11ce,{0x87,0x0b,0x08,0x00,0x36,0x8d,0x23,0x02}} */

#pragma code_seg(".orpc")
static const unsigned short ITypeLibViewer_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ITypeLibViewer_ProxyInfo =
    {
    &Object_StubDesc,
    DP__MIDL_ProcFormatString.Format,
    &ITypeLibViewer_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITypeLibViewer_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DP__MIDL_ProcFormatString.Format,
    &ITypeLibViewer_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ITypeLibViewerProxyVtbl = 
{
    &ITypeLibViewer_ProxyInfo,
    &IID_ITypeLibViewer,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITypeLibViewer::View */
};

const CInterfaceStubVtbl _ITypeLibViewerStubVtbl =
{
    &IID_ITypeLibViewer,
    &ITypeLibViewer_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: _IDummy, ver. 0.0,
   GUID={0x7DD08DA3,0x79A5,0x407E,{0xAF,0xF8,0xA1,0xDB,0x3B,0x51,0x8F,0x19}} */

#pragma code_seg(".orpc")
static const unsigned short _IDummy_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO _IDummy_ProxyInfo =
    {
    &Object_StubDesc,
    DP__MIDL_ProcFormatString.Format,
    &_IDummy_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO _IDummy_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    DP__MIDL_ProcFormatString.Format,
    &_IDummy_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(3) __IDummyProxyVtbl = 
{
    0,
    &IID__IDummy,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl __IDummyStubVtbl =
{
    &IID__IDummy,
    &_IDummy_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    DP__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _DP_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &__IDummyProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITypeLibViewerProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _DP_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &__IDummyStubVtbl,
    ( CInterfaceStubVtbl *) &_ITypeLibViewerStubVtbl,
    0
};

PCInterfaceName const _DP_InterfaceNamesList[] = 
{
    "_IDummy",
    "ITypeLibViewer",
    0
};


#define _DP_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _DP, pIID, n)

int __stdcall _DP_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _DP, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _DP, 2, *pIndex )
    
}

const ExtendedProxyFileInfo DP_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _DP_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _DP_StubVtblList,
    (const PCInterfaceName * ) & _DP_InterfaceNamesList,
    0, /* no delegation */
    & _DP_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

