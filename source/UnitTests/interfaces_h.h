

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Jul 03 20:17:24 2014
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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __interfaces_h_h__
#define __interfaces_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITestInterface2_FWD_DEFINED__
#define __ITestInterface2_FWD_DEFINED__
typedef interface ITestInterface2 ITestInterface2;

#endif 	/* __ITestInterface2_FWD_DEFINED__ */


#ifndef __ITestInterface3_FWD_DEFINED__
#define __ITestInterface3_FWD_DEFINED__
typedef interface ITestInterface3 ITestInterface3;

#endif 	/* __ITestInterface3_FWD_DEFINED__ */


#ifndef __ITestInterface_FWD_DEFINED__
#define __ITestInterface_FWD_DEFINED__
typedef interface ITestInterface ITestInterface;

#endif 	/* __ITestInterface_FWD_DEFINED__ */


#ifndef __UnitTestCoClassNotToBeCreated_FWD_DEFINED__
#define __UnitTestCoClassNotToBeCreated_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitTestCoClassNotToBeCreated UnitTestCoClassNotToBeCreated;
#else
typedef struct UnitTestCoClassNotToBeCreated UnitTestCoClassNotToBeCreated;
#endif /* __cplusplus */

#endif 	/* __UnitTestCoClassNotToBeCreated_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITestInterface2_INTERFACE_DEFINED__
#define __ITestInterface2_INTERFACE_DEFINED__

/* interface ITestInterface2 */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITestInterface2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3425BD7-D547-4636-A666-147C35DE1327")
    ITestInterface2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MethodMix( 
            /* [in] */ long __MIDL__ITestInterface20000,
            /* [in] */ BSTR __MIDL__ITestInterface20001) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITestInterface2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestInterface2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestInterface2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestInterface2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *MethodMix )( 
            ITestInterface2 * This,
            /* [in] */ long __MIDL__ITestInterface20000,
            /* [in] */ BSTR __MIDL__ITestInterface20001);
        
        END_INTERFACE
    } ITestInterface2Vtbl;

    interface ITestInterface2
    {
        CONST_VTBL struct ITestInterface2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestInterface2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestInterface2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestInterface2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestInterface2_MethodMix(This,__MIDL__ITestInterface20000,__MIDL__ITestInterface20001)	\
    ( (This)->lpVtbl -> MethodMix(This,__MIDL__ITestInterface20000,__MIDL__ITestInterface20001) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestInterface2_INTERFACE_DEFINED__ */


#ifndef __ITestInterface3_INTERFACE_DEFINED__
#define __ITestInterface3_INTERFACE_DEFINED__

/* interface ITestInterface3 */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITestInterface3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3425BD7-D547-4636-A666-147C35DE1329")
    ITestInterface3 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MethodFooBar( 
            /* [in] */ BSTR __MIDL__ITestInterface30000) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITestInterface3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestInterface3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestInterface3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestInterface3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *MethodFooBar )( 
            ITestInterface3 * This,
            /* [in] */ BSTR __MIDL__ITestInterface30000);
        
        END_INTERFACE
    } ITestInterface3Vtbl;

    interface ITestInterface3
    {
        CONST_VTBL struct ITestInterface3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestInterface3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestInterface3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestInterface3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestInterface3_MethodFooBar(This,__MIDL__ITestInterface30000)	\
    ( (This)->lpVtbl -> MethodFooBar(This,__MIDL__ITestInterface30000) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestInterface3_INTERFACE_DEFINED__ */


#ifndef __ITestInterface_INTERFACE_DEFINED__
#define __ITestInterface_INTERFACE_DEFINED__

/* interface ITestInterface */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITestInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48937FFC-8DD2-4739-9F54-E5B969DD9BDF")
    ITestInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFooBarInterface( 
            /* [in] */ REFIID riid,
            /* [iid_is][retval][out] */ IUnknown **pp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodInt( 
            /* [in] */ int a) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodBSTR( 
            /* [in] */ BSTR bstr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodLong( 
            /* [in] */ long __MIDL__ITestInterface0000) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodFloat( 
            /* [in] */ float __MIDL__ITestInterface0001) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodIntOut( 
            /* [out][in] */ int *__MIDL__ITestInterface0002) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodGUID_BSTR( 
            /* [in] */ GUID __MIDL__ITestInterface0003,
            BSTR __MIDL__ITestInterface0004) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodShort( 
            /* [in] */ SHORT s) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodBOOL( 
            /* [in] */ BOOL __MIDL__ITestInterface0005,
            /* [in] */ BSTR __MIDL__ITestInterface0006) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodDouble( 
            /* [in] */ double __MIDL__ITestInterface0007,
            /* [in] */ BSTR __MIDL__ITestInterface0008) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodVARPTROut( 
            /* [out] */ VARIANT *p) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MethodVARIANT( 
            /* [in] */ VARIANT __MIDL__ITestInterface0009) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTestInterface2( 
            /* [retval][out] */ ITestInterface2 **pp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITestInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITestInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITestInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITestInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetFooBarInterface )( 
            ITestInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][retval][out] */ IUnknown **pp);
        
        HRESULT ( STDMETHODCALLTYPE *MethodInt )( 
            ITestInterface * This,
            /* [in] */ int a);
        
        HRESULT ( STDMETHODCALLTYPE *MethodBSTR )( 
            ITestInterface * This,
            /* [in] */ BSTR bstr);
        
        HRESULT ( STDMETHODCALLTYPE *MethodLong )( 
            ITestInterface * This,
            /* [in] */ long __MIDL__ITestInterface0000);
        
        HRESULT ( STDMETHODCALLTYPE *MethodFloat )( 
            ITestInterface * This,
            /* [in] */ float __MIDL__ITestInterface0001);
        
        HRESULT ( STDMETHODCALLTYPE *MethodIntOut )( 
            ITestInterface * This,
            /* [out][in] */ int *__MIDL__ITestInterface0002);
        
        HRESULT ( STDMETHODCALLTYPE *MethodGUID_BSTR )( 
            ITestInterface * This,
            /* [in] */ GUID __MIDL__ITestInterface0003,
            BSTR __MIDL__ITestInterface0004);
        
        HRESULT ( STDMETHODCALLTYPE *MethodShort )( 
            ITestInterface * This,
            /* [in] */ SHORT s);
        
        HRESULT ( STDMETHODCALLTYPE *MethodBOOL )( 
            ITestInterface * This,
            /* [in] */ BOOL __MIDL__ITestInterface0005,
            /* [in] */ BSTR __MIDL__ITestInterface0006);
        
        HRESULT ( STDMETHODCALLTYPE *MethodDouble )( 
            ITestInterface * This,
            /* [in] */ double __MIDL__ITestInterface0007,
            /* [in] */ BSTR __MIDL__ITestInterface0008);
        
        HRESULT ( STDMETHODCALLTYPE *MethodVARPTROut )( 
            ITestInterface * This,
            /* [out] */ VARIANT *p);
        
        HRESULT ( STDMETHODCALLTYPE *MethodVARIANT )( 
            ITestInterface * This,
            /* [in] */ VARIANT __MIDL__ITestInterface0009);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestInterface2 )( 
            ITestInterface * This,
            /* [retval][out] */ ITestInterface2 **pp);
        
        END_INTERFACE
    } ITestInterfaceVtbl;

    interface ITestInterface
    {
        CONST_VTBL struct ITestInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITestInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITestInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITestInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITestInterface_GetFooBarInterface(This,riid,pp)	\
    ( (This)->lpVtbl -> GetFooBarInterface(This,riid,pp) ) 

#define ITestInterface_MethodInt(This,a)	\
    ( (This)->lpVtbl -> MethodInt(This,a) ) 

#define ITestInterface_MethodBSTR(This,bstr)	\
    ( (This)->lpVtbl -> MethodBSTR(This,bstr) ) 

#define ITestInterface_MethodLong(This,__MIDL__ITestInterface0000)	\
    ( (This)->lpVtbl -> MethodLong(This,__MIDL__ITestInterface0000) ) 

#define ITestInterface_MethodFloat(This,__MIDL__ITestInterface0001)	\
    ( (This)->lpVtbl -> MethodFloat(This,__MIDL__ITestInterface0001) ) 

#define ITestInterface_MethodIntOut(This,__MIDL__ITestInterface0002)	\
    ( (This)->lpVtbl -> MethodIntOut(This,__MIDL__ITestInterface0002) ) 

#define ITestInterface_MethodGUID_BSTR(This,__MIDL__ITestInterface0003,__MIDL__ITestInterface0004)	\
    ( (This)->lpVtbl -> MethodGUID_BSTR(This,__MIDL__ITestInterface0003,__MIDL__ITestInterface0004) ) 

#define ITestInterface_MethodShort(This,s)	\
    ( (This)->lpVtbl -> MethodShort(This,s) ) 

#define ITestInterface_MethodBOOL(This,__MIDL__ITestInterface0005,__MIDL__ITestInterface0006)	\
    ( (This)->lpVtbl -> MethodBOOL(This,__MIDL__ITestInterface0005,__MIDL__ITestInterface0006) ) 

#define ITestInterface_MethodDouble(This,__MIDL__ITestInterface0007,__MIDL__ITestInterface0008)	\
    ( (This)->lpVtbl -> MethodDouble(This,__MIDL__ITestInterface0007,__MIDL__ITestInterface0008) ) 

#define ITestInterface_MethodVARPTROut(This,p)	\
    ( (This)->lpVtbl -> MethodVARPTROut(This,p) ) 

#define ITestInterface_MethodVARIANT(This,__MIDL__ITestInterface0009)	\
    ( (This)->lpVtbl -> MethodVARIANT(This,__MIDL__ITestInterface0009) ) 

#define ITestInterface_GetTestInterface2(This,pp)	\
    ( (This)->lpVtbl -> GetTestInterface2(This,pp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITestInterface_INTERFACE_DEFINED__ */



#ifndef __UnitTestLibrary_LIBRARY_DEFINED__
#define __UnitTestLibrary_LIBRARY_DEFINED__

/* library UnitTestLibrary */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_UnitTestLibrary;

EXTERN_C const CLSID CLSID_UnitTestCoClassNotToBeCreated;

#ifdef __cplusplus

class DECLSPEC_UUID("DAE2DE76-CB4A-4EE7-9D49-DCD763EC9ECF")
UnitTestCoClassNotToBeCreated;
#endif
#endif /* __UnitTestLibrary_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


