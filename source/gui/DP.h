

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __DP_h__
#define __DP_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITypeLibViewer_FWD_DEFINED__
#define __ITypeLibViewer_FWD_DEFINED__
typedef interface ITypeLibViewer ITypeLibViewer;

#endif 	/* __ITypeLibViewer_FWD_DEFINED__ */


#ifndef ___IDummy_FWD_DEFINED__
#define ___IDummy_FWD_DEFINED__
typedef interface _IDummy _IDummy;

#endif 	/* ___IDummy_FWD_DEFINED__ */


#ifndef __TraceListener_FWD_DEFINED__
#define __TraceListener_FWD_DEFINED__

#ifdef __cplusplus
typedef class TraceListener TraceListener;
#else
typedef struct TraceListener TraceListener;
#endif /* __cplusplus */

#endif 	/* __TraceListener_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ITypeLibViewer_INTERFACE_DEFINED__
#define __ITypeLibViewer_INTERFACE_DEFINED__

/* interface ITypeLibViewer */
/* [object][uuid] */ 


EXTERN_C const IID IID_ITypeLibViewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fc37e5ba-4a8e-11ce-870b-0800368d2302")
    ITypeLibViewer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE View( 
            /* [in] */ HWND hwndParent,
            /* [in] */ REFIID riid,
            /* [in] */ IUnknown *punk) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ITypeLibViewerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITypeLibViewer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITypeLibViewer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITypeLibViewer * This);
        
        HRESULT ( STDMETHODCALLTYPE *View )( 
            ITypeLibViewer * This,
            /* [in] */ HWND hwndParent,
            /* [in] */ REFIID riid,
            /* [in] */ IUnknown *punk);
        
        END_INTERFACE
    } ITypeLibViewerVtbl;

    interface ITypeLibViewer
    {
        CONST_VTBL struct ITypeLibViewerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITypeLibViewer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ITypeLibViewer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ITypeLibViewer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ITypeLibViewer_View(This,hwndParent,riid,punk)	\
    ( (This)->lpVtbl -> View(This,hwndParent,riid,punk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ITypeLibViewer_INTERFACE_DEFINED__ */


#ifndef ___IDummy_INTERFACE_DEFINED__
#define ___IDummy_INTERFACE_DEFINED__

/* interface _IDummy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID__IDummy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7DD08DA3-79A5-407E-AFF8-A1DB3B518F19")
    _IDummy : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct _IDummyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IDummy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IDummy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IDummy * This);
        
        END_INTERFACE
    } _IDummyVtbl;

    interface _IDummy
    {
        CONST_VTBL struct _IDummyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDummy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IDummy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IDummy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IDummy_INTERFACE_DEFINED__ */



#ifndef __DPLib_LIBRARY_DEFINED__
#define __DPLib_LIBRARY_DEFINED__

/* library DPLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DPLib;

EXTERN_C const CLSID CLSID_TraceListener;

#ifdef __cplusplus

class DECLSPEC_UUID("A115A87C-5C74-460E-9180-E394D2976CD0")
TraceListener;
#endif
#endif /* __DPLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


