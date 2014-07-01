

/* this ALWAYS GENERATED file contains the proxy stub code */


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


#include "interfaces_h.h"

#define TYPE_FORMAT_STRING_SIZE   1109                              
#define PROC_FORMAT_STRING_SIZE   571                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _interfaces_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } interfaces_MIDL_TYPE_FORMAT_STRING;

typedef struct _interfaces_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } interfaces_MIDL_PROC_FORMAT_STRING;

typedef struct _interfaces_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } interfaces_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const interfaces_MIDL_TYPE_FORMAT_STRING interfaces__MIDL_TypeFormatString;
extern const interfaces_MIDL_PROC_FORMAT_STRING interfaces__MIDL_ProcFormatString;
extern const interfaces_MIDL_EXPR_FORMAT_STRING interfaces__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITestInterface2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITestInterface2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITestInterface3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITestInterface3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITestInterface_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITestInterface_ProxyInfo;


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


static const interfaces_MIDL_PROC_FORMAT_STRING interfaces__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure MethodMix */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface20000 */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter __MIDL__ITestInterface20001 */

/* 30 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 36 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodFooBar */

/* 42 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 44 */	NdrFcLong( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x3 ),	/* 3 */
/* 50 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x8 ),	/* 8 */
/* 56 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 58 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x1 ),	/* 1 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface30000 */

/* 66 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 68 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 70 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 72 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 74 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetFooBarInterface */

/* 78 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 80 */	NdrFcLong( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x3 ),	/* 3 */
/* 86 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 88 */	NdrFcShort( 0x44 ),	/* 68 */
/* 90 */	NdrFcShort( 0x8 ),	/* 8 */
/* 92 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 94 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 96 */	NdrFcShort( 0x1 ),	/* 1 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter riid */

/* 102 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 106 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter pp */

/* 108 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 112 */	NdrFcShort( 0x3c ),	/* Type Offset=60 */

	/* Return value */

/* 114 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodInt */

/* 120 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 122 */	NdrFcLong( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x4 ),	/* 4 */
/* 128 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 130 */	NdrFcShort( 0x8 ),	/* 8 */
/* 132 */	NdrFcShort( 0x8 ),	/* 8 */
/* 134 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 136 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 142 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter a */

/* 144 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 146 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 148 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 152 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodBSTR */

/* 156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 162 */	NdrFcShort( 0x5 ),	/* 5 */
/* 164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 172 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x1 ),	/* 1 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstr */

/* 180 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 182 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 184 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 186 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 188 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodLong */

/* 192 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 194 */	NdrFcLong( 0x0 ),	/* 0 */
/* 198 */	NdrFcShort( 0x6 ),	/* 6 */
/* 200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 204 */	NdrFcShort( 0x8 ),	/* 8 */
/* 206 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 208 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0000 */

/* 216 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 218 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 222 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 224 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 226 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodFloat */

/* 228 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 230 */	NdrFcLong( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x7 ),	/* 7 */
/* 236 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 238 */	NdrFcShort( 0x8 ),	/* 8 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 244 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0001 */

/* 252 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 256 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Return value */

/* 258 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 260 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 262 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodIntOut */

/* 264 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 266 */	NdrFcLong( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 272 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 274 */	NdrFcShort( 0x1c ),	/* 28 */
/* 276 */	NdrFcShort( 0x24 ),	/* 36 */
/* 278 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 280 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 282 */	NdrFcShort( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0002 */

/* 288 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 290 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 296 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodGUID_BSTR */

/* 300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 306 */	NdrFcShort( 0x9 ),	/* 9 */
/* 308 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 310 */	NdrFcShort( 0x30 ),	/* 48 */
/* 312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 314 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 316 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x1 ),	/* 1 */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0003 */

/* 324 */	NdrFcShort( 0x8a ),	/* Flags:  must free, in, by val, */
/* 326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 328 */	NdrFcShort( 0x30 ),	/* Type Offset=48 */

	/* Parameter __MIDL__ITestInterface0004 */

/* 330 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 332 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 334 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 338 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodShort */

/* 342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0xa ),	/* 10 */
/* 350 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 352 */	NdrFcShort( 0x6 ),	/* 6 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 358 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter s */

/* 366 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 370 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 372 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodBOOL */

/* 378 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 380 */	NdrFcLong( 0x0 ),	/* 0 */
/* 384 */	NdrFcShort( 0xb ),	/* 11 */
/* 386 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 388 */	NdrFcShort( 0x8 ),	/* 8 */
/* 390 */	NdrFcShort( 0x8 ),	/* 8 */
/* 392 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 394 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x1 ),	/* 1 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0005 */

/* 402 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 404 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter __MIDL__ITestInterface0006 */

/* 408 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 410 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 412 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodDouble */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0xc ),	/* 12 */
/* 428 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 430 */	NdrFcShort( 0x10 ),	/* 16 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 436 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 438 */	NdrFcShort( 0x0 ),	/* 0 */
/* 440 */	NdrFcShort( 0x1 ),	/* 1 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0007 */

/* 444 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 446 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 448 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter __MIDL__ITestInterface0008 */

/* 450 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 452 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 454 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 456 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 458 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodVARPTROut */

/* 462 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 464 */	NdrFcLong( 0x0 ),	/* 0 */
/* 468 */	NdrFcShort( 0xd ),	/* 13 */
/* 470 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 474 */	NdrFcShort( 0x8 ),	/* 8 */
/* 476 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 478 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 480 */	NdrFcShort( 0x1 ),	/* 1 */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter p */

/* 486 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 488 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 490 */	NdrFcShort( 0x426 ),	/* Type Offset=1062 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 494 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure MethodVARIANT */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0xe ),	/* 14 */
/* 506 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x8 ),	/* 8 */
/* 512 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 514 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	NdrFcShort( 0x1 ),	/* 1 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter __MIDL__ITestInterface0009 */

/* 522 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 524 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 526 */	NdrFcShort( 0x434 ),	/* Type Offset=1076 */

	/* Return value */

/* 528 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 530 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTestInterface2 */

/* 534 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 536 */	NdrFcLong( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0xf ),	/* 15 */
/* 542 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x8 ),	/* 8 */
/* 548 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 550 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pp */

/* 558 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 560 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 562 */	NdrFcShort( 0x43e ),	/* Type Offset=1086 */

	/* Return value */

/* 564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 566 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const interfaces_MIDL_TYPE_FORMAT_STRING interfaces__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x12, 0x0,	/* FC_UP */
/*  4 */	NdrFcShort( 0xe ),	/* Offset= 14 (18) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  8 */	NdrFcShort( 0x2 ),	/* 2 */
/* 10 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 14 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 16 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 18 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 20 */	NdrFcShort( 0x8 ),	/* 8 */
/* 22 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (6) */
/* 24 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 26 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 28 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x4 ),	/* 4 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0xffde ),	/* Offset= -34 (2) */
/* 38 */	
			0x11, 0x0,	/* FC_RP */
/* 40 */	NdrFcShort( 0x8 ),	/* Offset= 8 (48) */
/* 42 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 44 */	NdrFcShort( 0x8 ),	/* 8 */
/* 46 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 48 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 50 */	NdrFcShort( 0x10 ),	/* 16 */
/* 52 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 54 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 56 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (42) */
			0x5b,		/* FC_END */
/* 60 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 66 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 68 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 70 */	NdrFcShort( 0x5 ),	/* Corr flags:  early, iid_is, */
/* 72 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 74 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 76 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 78 */	NdrFcShort( 0x3d8 ),	/* Offset= 984 (1062) */
/* 80 */	
			0x13, 0x0,	/* FC_OP */
/* 82 */	NdrFcShort( 0x3c0 ),	/* Offset= 960 (1042) */
/* 84 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 86 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 88 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 90 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 92 */	NdrFcShort( 0x2 ),	/* Offset= 2 (94) */
/* 94 */	NdrFcShort( 0x10 ),	/* 16 */
/* 96 */	NdrFcShort( 0x2f ),	/* 47 */
/* 98 */	NdrFcLong( 0x14 ),	/* 20 */
/* 102 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 104 */	NdrFcLong( 0x3 ),	/* 3 */
/* 108 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 110 */	NdrFcLong( 0x11 ),	/* 17 */
/* 114 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 116 */	NdrFcLong( 0x2 ),	/* 2 */
/* 120 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 122 */	NdrFcLong( 0x4 ),	/* 4 */
/* 126 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 128 */	NdrFcLong( 0x5 ),	/* 5 */
/* 132 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 134 */	NdrFcLong( 0xb ),	/* 11 */
/* 138 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 140 */	NdrFcLong( 0xa ),	/* 10 */
/* 144 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 146 */	NdrFcLong( 0x6 ),	/* 6 */
/* 150 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (382) */
/* 152 */	NdrFcLong( 0x7 ),	/* 7 */
/* 156 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 158 */	NdrFcLong( 0x8 ),	/* 8 */
/* 162 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (388) */
/* 164 */	NdrFcLong( 0xd ),	/* 13 */
/* 168 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (392) */
/* 170 */	NdrFcLong( 0x9 ),	/* 9 */
/* 174 */	NdrFcShort( 0xec ),	/* Offset= 236 (410) */
/* 176 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 180 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (428) */
/* 182 */	NdrFcLong( 0x24 ),	/* 36 */
/* 186 */	NdrFcShort( 0x30e ),	/* Offset= 782 (968) */
/* 188 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 192 */	NdrFcShort( 0x308 ),	/* Offset= 776 (968) */
/* 194 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 198 */	NdrFcShort( 0x306 ),	/* Offset= 774 (972) */
/* 200 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 204 */	NdrFcShort( 0x304 ),	/* Offset= 772 (976) */
/* 206 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 210 */	NdrFcShort( 0x302 ),	/* Offset= 770 (980) */
/* 212 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 216 */	NdrFcShort( 0x300 ),	/* Offset= 768 (984) */
/* 218 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 222 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (988) */
/* 224 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 228 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (992) */
/* 230 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 234 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (976) */
/* 236 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 240 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (980) */
/* 242 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 246 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (996) */
/* 248 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 252 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (992) */
/* 254 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 258 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (1000) */
/* 260 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 264 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (1004) */
/* 266 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 270 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (1008) */
/* 272 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 276 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (1012) */
/* 278 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 282 */	NdrFcShort( 0x2de ),	/* Offset= 734 (1016) */
/* 284 */	NdrFcLong( 0x10 ),	/* 16 */
/* 288 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 290 */	NdrFcLong( 0x12 ),	/* 18 */
/* 294 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 296 */	NdrFcLong( 0x13 ),	/* 19 */
/* 300 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 302 */	NdrFcLong( 0x15 ),	/* 21 */
/* 306 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 308 */	NdrFcLong( 0x16 ),	/* 22 */
/* 312 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 314 */	NdrFcLong( 0x17 ),	/* 23 */
/* 318 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 320 */	NdrFcLong( 0xe ),	/* 14 */
/* 324 */	NdrFcShort( 0x2bc ),	/* Offset= 700 (1024) */
/* 326 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 330 */	NdrFcShort( 0x2c0 ),	/* Offset= 704 (1034) */
/* 332 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 336 */	NdrFcShort( 0x2be ),	/* Offset= 702 (1038) */
/* 338 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 342 */	NdrFcShort( 0x27a ),	/* Offset= 634 (976) */
/* 344 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 348 */	NdrFcShort( 0x278 ),	/* Offset= 632 (980) */
/* 350 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 354 */	NdrFcShort( 0x276 ),	/* Offset= 630 (984) */
/* 356 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 360 */	NdrFcShort( 0x26c ),	/* Offset= 620 (980) */
/* 362 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 366 */	NdrFcShort( 0x266 ),	/* Offset= 614 (980) */
/* 368 */	NdrFcLong( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x0 ),	/* Offset= 0 (372) */
/* 374 */	NdrFcLong( 0x1 ),	/* 1 */
/* 378 */	NdrFcShort( 0x0 ),	/* Offset= 0 (378) */
/* 380 */	NdrFcShort( 0xffff ),	/* Offset= -1 (379) */
/* 382 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 386 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 388 */	
			0x13, 0x0,	/* FC_OP */
/* 390 */	NdrFcShort( 0xfe8c ),	/* Offset= -372 (18) */
/* 392 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */
/* 402 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 404 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 406 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 408 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 410 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 412 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 420 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 422 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 424 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 426 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 428 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 430 */	NdrFcShort( 0x2 ),	/* Offset= 2 (432) */
/* 432 */	
			0x13, 0x0,	/* FC_OP */
/* 434 */	NdrFcShort( 0x204 ),	/* Offset= 516 (950) */
/* 436 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 438 */	NdrFcShort( 0x18 ),	/* 24 */
/* 440 */	NdrFcShort( 0xa ),	/* 10 */
/* 442 */	NdrFcLong( 0x8 ),	/* 8 */
/* 446 */	NdrFcShort( 0x5a ),	/* Offset= 90 (536) */
/* 448 */	NdrFcLong( 0xd ),	/* 13 */
/* 452 */	NdrFcShort( 0x7e ),	/* Offset= 126 (578) */
/* 454 */	NdrFcLong( 0x9 ),	/* 9 */
/* 458 */	NdrFcShort( 0x9e ),	/* Offset= 158 (616) */
/* 460 */	NdrFcLong( 0xc ),	/* 12 */
/* 464 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (664) */
/* 466 */	NdrFcLong( 0x24 ),	/* 36 */
/* 470 */	NdrFcShort( 0x124 ),	/* Offset= 292 (762) */
/* 472 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 476 */	NdrFcShort( 0x12e ),	/* Offset= 302 (778) */
/* 478 */	NdrFcLong( 0x10 ),	/* 16 */
/* 482 */	NdrFcShort( 0x148 ),	/* Offset= 328 (810) */
/* 484 */	NdrFcLong( 0x2 ),	/* 2 */
/* 488 */	NdrFcShort( 0x162 ),	/* Offset= 354 (842) */
/* 490 */	NdrFcLong( 0x3 ),	/* 3 */
/* 494 */	NdrFcShort( 0x17c ),	/* Offset= 380 (874) */
/* 496 */	NdrFcLong( 0x14 ),	/* 20 */
/* 500 */	NdrFcShort( 0x196 ),	/* Offset= 406 (906) */
/* 502 */	NdrFcShort( 0xffff ),	/* Offset= -1 (501) */
/* 504 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 506 */	NdrFcShort( 0x4 ),	/* 4 */
/* 508 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 510 */	NdrFcShort( 0x0 ),	/* 0 */
/* 512 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 514 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 516 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 518 */	NdrFcShort( 0x4 ),	/* 4 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x1 ),	/* 1 */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	0x13, 0x0,	/* FC_OP */
/* 530 */	NdrFcShort( 0xfe00 ),	/* Offset= -512 (18) */
/* 532 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 534 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 536 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 538 */	NdrFcShort( 0x8 ),	/* 8 */
/* 540 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 542 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 544 */	NdrFcShort( 0x4 ),	/* 4 */
/* 546 */	NdrFcShort( 0x4 ),	/* 4 */
/* 548 */	0x11, 0x0,	/* FC_RP */
/* 550 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (504) */
/* 552 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 554 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 556 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 566 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 570 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 572 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 574 */	NdrFcShort( 0xff4a ),	/* Offset= -182 (392) */
/* 576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 578 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 582 */	NdrFcShort( 0x0 ),	/* 0 */
/* 584 */	NdrFcShort( 0x6 ),	/* Offset= 6 (590) */
/* 586 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 588 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 590 */	
			0x11, 0x0,	/* FC_RP */
/* 592 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (556) */
/* 594 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 596 */	NdrFcShort( 0x0 ),	/* 0 */
/* 598 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 604 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 608 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 610 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 612 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (410) */
/* 614 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 616 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 618 */	NdrFcShort( 0x8 ),	/* 8 */
/* 620 */	NdrFcShort( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0x6 ),	/* Offset= 6 (628) */
/* 624 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 626 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 628 */	
			0x11, 0x0,	/* FC_RP */
/* 630 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (594) */
/* 632 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 634 */	NdrFcShort( 0x4 ),	/* 4 */
/* 636 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 642 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 644 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x1 ),	/* 1 */
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	0x13, 0x0,	/* FC_OP */
/* 658 */	NdrFcShort( 0x180 ),	/* Offset= 384 (1042) */
/* 660 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 662 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 664 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 670 */	NdrFcShort( 0x6 ),	/* Offset= 6 (676) */
/* 672 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 674 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 676 */	
			0x11, 0x0,	/* FC_RP */
/* 678 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (632) */
/* 680 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 682 */	NdrFcLong( 0x2f ),	/* 47 */
/* 686 */	NdrFcShort( 0x0 ),	/* 0 */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 690 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 692 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 694 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 696 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 698 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 700 */	NdrFcShort( 0x1 ),	/* 1 */
/* 702 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 704 */	NdrFcShort( 0x4 ),	/* 4 */
/* 706 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 708 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 710 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x10 ),	/* 16 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0xa ),	/* Offset= 10 (726) */
/* 718 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 720 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 722 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (680) */
/* 724 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 726 */	
			0x13, 0x0,	/* FC_OP */
/* 728 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (698) */
/* 730 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 732 */	NdrFcShort( 0x4 ),	/* 4 */
/* 734 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 740 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 742 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 744 */	NdrFcShort( 0x4 ),	/* 4 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x1 ),	/* 1 */
/* 750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	0x13, 0x0,	/* FC_OP */
/* 756 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (710) */
/* 758 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 760 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 762 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 764 */	NdrFcShort( 0x8 ),	/* 8 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x6 ),	/* Offset= 6 (774) */
/* 770 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 772 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 774 */	
			0x11, 0x0,	/* FC_RP */
/* 776 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (730) */
/* 778 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 780 */	NdrFcShort( 0x18 ),	/* 24 */
/* 782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 784 */	NdrFcShort( 0xa ),	/* Offset= 10 (794) */
/* 786 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 788 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 790 */	NdrFcShort( 0xfd1a ),	/* Offset= -742 (48) */
/* 792 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 794 */	
			0x11, 0x0,	/* FC_RP */
/* 796 */	NdrFcShort( 0xff10 ),	/* Offset= -240 (556) */
/* 798 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 800 */	NdrFcShort( 0x1 ),	/* 1 */
/* 802 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 804 */	NdrFcShort( 0x0 ),	/* 0 */
/* 806 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 808 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 810 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 816 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	0x13, 0x0,	/* FC_OP */
/* 824 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (798) */
/* 826 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 828 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 830 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 832 */	NdrFcShort( 0x2 ),	/* 2 */
/* 834 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 840 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 842 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 848 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	NdrFcShort( 0x4 ),	/* 4 */
/* 854 */	0x13, 0x0,	/* FC_OP */
/* 856 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (830) */
/* 858 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 860 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 862 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 864 */	NdrFcShort( 0x4 ),	/* 4 */
/* 866 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 870 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 872 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 874 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 876 */	NdrFcShort( 0x8 ),	/* 8 */
/* 878 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 880 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 882 */	NdrFcShort( 0x4 ),	/* 4 */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	0x13, 0x0,	/* FC_OP */
/* 888 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (862) */
/* 890 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 892 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 894 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 898 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 904 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 906 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 912 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	NdrFcShort( 0x4 ),	/* 4 */
/* 918 */	0x13, 0x0,	/* FC_OP */
/* 920 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (894) */
/* 922 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 924 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 926 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 928 */	NdrFcShort( 0x8 ),	/* 8 */
/* 930 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 932 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 934 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 936 */	NdrFcShort( 0x8 ),	/* 8 */
/* 938 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 940 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 942 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 944 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 946 */	NdrFcShort( 0xffec ),	/* Offset= -20 (926) */
/* 948 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 950 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 952 */	NdrFcShort( 0x28 ),	/* 40 */
/* 954 */	NdrFcShort( 0xffec ),	/* Offset= -20 (934) */
/* 956 */	NdrFcShort( 0x0 ),	/* Offset= 0 (956) */
/* 958 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 960 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 962 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 964 */	NdrFcShort( 0xfdf0 ),	/* Offset= -528 (436) */
/* 966 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 968 */	
			0x13, 0x0,	/* FC_OP */
/* 970 */	NdrFcShort( 0xfefc ),	/* Offset= -260 (710) */
/* 972 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 974 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 976 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 978 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 980 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 982 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 984 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 986 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 988 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 990 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 992 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 994 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 996 */	
			0x13, 0x0,	/* FC_OP */
/* 998 */	NdrFcShort( 0xfd98 ),	/* Offset= -616 (382) */
/* 1000 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1002 */	NdrFcShort( 0xfd9a ),	/* Offset= -614 (388) */
/* 1004 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1006 */	NdrFcShort( 0xfd9a ),	/* Offset= -614 (392) */
/* 1008 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1010 */	NdrFcShort( 0xfda8 ),	/* Offset= -600 (410) */
/* 1012 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1014 */	NdrFcShort( 0xfdb6 ),	/* Offset= -586 (428) */
/* 1016 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1018 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1020) */
/* 1020 */	
			0x13, 0x0,	/* FC_OP */
/* 1022 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1042) */
/* 1024 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1026 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1028 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1030 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1032 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1034 */	
			0x13, 0x0,	/* FC_OP */
/* 1036 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1024) */
/* 1038 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1040 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1042 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1044 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1046 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1048 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1048) */
/* 1050 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1052 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1054 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1056 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1058 */	NdrFcShort( 0xfc32 ),	/* Offset= -974 (84) */
/* 1060 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1062 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1064 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1066 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1070 */	NdrFcShort( 0xfc22 ),	/* Offset= -990 (80) */
/* 1072 */	
			0x12, 0x0,	/* FC_UP */
/* 1074 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (1042) */
/* 1076 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1078 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1080 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1084 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1072) */
/* 1086 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1088 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1090) */
/* 1090 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1092 */	NdrFcLong( 0xa3425bd7 ),	/* -1555932201 */
/* 1096 */	NdrFcShort( 0xd547 ),	/* -10937 */
/* 1098 */	NdrFcShort( 0x4636 ),	/* 17974 */
/* 1100 */	0xa6,		/* 166 */
			0x66,		/* 102 */
/* 1102 */	0x14,		/* 20 */
			0x7c,		/* 124 */
/* 1104 */	0x35,		/* 53 */
			0xde,		/* 222 */
/* 1106 */	0x13,		/* 19 */
			0x27,		/* 39 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ITestInterface2, ver. 0.0,
   GUID={0xA3425BD7,0xD547,0x4636,{0xA6,0x66,0x14,0x7C,0x35,0xDE,0x13,0x27}} */

#pragma code_seg(".orpc")
static const unsigned short ITestInterface2_FormatStringOffsetTable[] =
    {
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ITestInterface2_ProxyInfo =
    {
    &Object_StubDesc,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITestInterface2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ITestInterface2ProxyVtbl = 
{
    &ITestInterface2_ProxyInfo,
    &IID_ITestInterface2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITestInterface2::MethodMix */
};

const CInterfaceStubVtbl _ITestInterface2StubVtbl =
{
    &IID_ITestInterface2,
    &ITestInterface2_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITestInterface3, ver. 0.0,
   GUID={0xA3425BD7,0xD547,0x4636,{0xA6,0x66,0x14,0x7C,0x35,0xDE,0x13,0x29}} */

#pragma code_seg(".orpc")
static const unsigned short ITestInterface3_FormatStringOffsetTable[] =
    {
    42
    };

static const MIDL_STUBLESS_PROXY_INFO ITestInterface3_ProxyInfo =
    {
    &Object_StubDesc,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITestInterface3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _ITestInterface3ProxyVtbl = 
{
    &ITestInterface3_ProxyInfo,
    &IID_ITestInterface3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITestInterface3::MethodFooBar */
};

const CInterfaceStubVtbl _ITestInterface3StubVtbl =
{
    &IID_ITestInterface3,
    &ITestInterface3_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: ITestInterface, ver. 0.0,
   GUID={0x48937FFC,0x8DD2,0x4739,{0x9F,0x54,0xE5,0xB9,0x69,0xDD,0x9B,0xDF}} */

#pragma code_seg(".orpc")
static const unsigned short ITestInterface_FormatStringOffsetTable[] =
    {
    78,
    120,
    156,
    192,
    228,
    264,
    300,
    342,
    378,
    420,
    462,
    498,
    534
    };

static const MIDL_STUBLESS_PROXY_INFO ITestInterface_ProxyInfo =
    {
    &Object_StubDesc,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITestInterface_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    interfaces__MIDL_ProcFormatString.Format,
    &ITestInterface_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(16) _ITestInterfaceProxyVtbl = 
{
    &ITestInterface_ProxyInfo,
    &IID_ITestInterface,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* ITestInterface::GetFooBarInterface */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodInt */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodBSTR */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodLong */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodFloat */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodIntOut */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodGUID_BSTR */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodShort */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodBOOL */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodDouble */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodVARPTROut */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::MethodVARIANT */ ,
    (void *) (INT_PTR) -1 /* ITestInterface::GetTestInterface2 */
};

const CInterfaceStubVtbl _ITestInterfaceStubVtbl =
{
    &IID_ITestInterface,
    &ITestInterface_ServerInfo,
    16,
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
    interfaces__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const _interfaces_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITestInterface2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITestInterface3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ITestInterfaceProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _interfaces_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITestInterface2StubVtbl,
    ( CInterfaceStubVtbl *) &_ITestInterface3StubVtbl,
    ( CInterfaceStubVtbl *) &_ITestInterfaceStubVtbl,
    0
};

PCInterfaceName const _interfaces_InterfaceNamesList[] = 
{
    "ITestInterface2",
    "ITestInterface3",
    "ITestInterface",
    0
};


#define _interfaces_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _interfaces, pIID, n)

int __stdcall _interfaces_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _interfaces, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _interfaces, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _interfaces, 3, *pIndex )
    
}

const ExtendedProxyFileInfo interfaces_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _interfaces_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _interfaces_StubVtblList,
    (const PCInterfaceName * ) & _interfaces_InterfaceNamesList,
    0, /* no delegation */
    & _interfaces_IID_Lookup, 
    3,
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

