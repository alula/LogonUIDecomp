

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for logonui10\logon.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
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
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __logon_h__
#define __logon_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __ILogonController_FWD_DEFINED__
#define __ILogonController_FWD_DEFINED__
typedef interface ILogonController ILogonController;

#endif 	/* __ILogonController_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ILogonController_INTERFACE_DEFINED__
#define __ILogonController_INTERFACE_DEFINED__

/* interface ILogonController */
/* [object][uuid] */ 


EXTERN_C const IID IID_ILogonController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e76c5d5b-7ad9-4496-9efd-dfa08ec700bb")
    ILogonController : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DoModal( 
            /* [in] */ ULONG flags,
            /* [in] */ ULONG testclientprocessid,
            /* [in] */ ULONG state0,
            /* [in] */ ULONG state1) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ILogonControllerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogonController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogonController * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogonController * This);
        
        DECLSPEC_XFGVIRT(ILogonController, DoModal)
        HRESULT ( STDMETHODCALLTYPE *DoModal )( 
            ILogonController * This,
            /* [in] */ ULONG flags,
            /* [in] */ ULONG testclientprocessid,
            /* [in] */ ULONG state0,
            /* [in] */ ULONG state1);
        
        END_INTERFACE
    } ILogonControllerVtbl;

    interface ILogonController
    {
        CONST_VTBL struct ILogonControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogonController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogonController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogonController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogonController_DoModal(This,flags,testclientprocessid,state0,state1)	\
    ( (This)->lpVtbl -> DoModal(This,flags,testclientprocessid,state0,state1) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogonController_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


