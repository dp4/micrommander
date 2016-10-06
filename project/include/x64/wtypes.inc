
RECT	struc
 left	dd	?
 top	dd	?
 right	dd	?
 bottom	dd	?
RECT	ends


; this ALWAYS GENERATED file contains the definitions for the interfaces 

; File created by MIDL compiler version 3.00.44 
; at Fri Jul 12 18:09:25 1996
 
; Compiler settings for wtypes.idl:

; Forward Declarations  


;***************************************
; * Generated header for interface: __MIDL__intf_0000
; * at Fri Jul 12 18:09:25 1996
; * using MIDL 3.00.44
; ***************************************
; [local]  

CLSCTX_INPROC_SERVER	= 1
CLSCTX_INPROC_HANDLER	= 2
CLSCTX_LOCAL_SERVER	= 4
CLSCTX_INPROC_SERVER16	= 8
CLSCTX_REMOTE_SERVER	= 10h
CLSCTX_INPROC_HANDLER16	= 20h
CLSCTX_INPROC_SERVERX86	= 40h
CLSCTX_INPROC_HANDLERX86	= 80h

;+-------------------------------------------------------------------------
;
;  Microsoft Windows
;  Copyright (C) Microsoft Corporation, 1992 - 1996.
;
;--------------------------------------------------------------------------

;***************************************
; * Generated header for interface: IWinTypes
; * at Fri Jul 12 18:09:25 1996
; * using MIDL 3.00.44
; ***************************************
; [auto_handle][unique][version][uuid]  
comment #

COLORREF	textequ dd

RECTL	struc
 rectl_left	dd	?
 rectl_top	dd	?
 rectl_right	dd	?
 rectl_bottom	dd	?
RECTL	ends

POINT	struc
 pnt_x	dd	?
 pnt_y	dd	?
POINT	ends

POINTL	struc
 pntl_x	dd	?
 pntl_y	dd	?
POINTL	ends

SIZEL	struc
 sizel_cx	dd	?
 sizel_cy	dd	?
SIZEL	ends

;;typedef float FLOAT;


RECT2	struc
 rect_left	dd	?
 rect_top	dd	?
 rect_width	dd	?
 rect_height	dd	?
RECT2	ends

UCHAR	textequ	db
USHORT	textequ	dw
ULONG	textequ	dd

;;typedef double DOUBLE;

LARGE_INTEGER	struc
 lint_QuadPart	dd	?, ?
LARGE_INTEGER	ends

ULARGE_INTEGER	struc
 ulint_QuadPart	dd	?, ?
ULARGE_INTEGER	ends

PSID	textequ	dd

COAUTHIDENTITY		struc
 cau_UserLength		dd	?
 cau_DomainLength	dd	?
 cau_PasswordLength	dd	?
 cau_Flags		dd	?
COAUTHIDENTITY		ends

COAUTHINFO		struc
 cai_dwAuthnSvc		dd	?
 cai_dwAuthzSvc		dd	?
 cai_pwszServerPrincName	dd	?
 cai_dwAuthnLevel		dd	?
 cai_dwImpersonationLevel	dd	?
 cai_pAuthIdentityData	dd	?
 cai_dwCapabilities		dd	?
COAUTHINFO		ends

COSERVERINFO	struc
 csi_dwReserved1	dd	?
 csi_pwszName	dd	?
 csi_pAuthInfo	dd	?
 csi_dwReserved2	dd	?
COSERVERINFO	ends

LCID	textequ	dd

WDT_INPROC_CALL	equ	48746457h
WDT_REMOTE_CALL	equ	52746457h

;typedef double DATE;

CY	struc
 cy_int64	dd	?, ?
CY	ends

; The following isn't the real definition of Decimal type, 
; but it is what RPC knows how to remote 
DECIMAL	struc
 dec_wReserved	dw	?
 dec_scale	db	?
 dec_sign	db	?
 dec_Hi32	dd	?
 dec_Lo64	dd	?, ?
DECIMAL	ends

DECIMAL_NEG	equ	128

VARIANT_TRUE	equ	0FFFFh
VARIANT_FALSE	equ	0

;;BLOB	struc
;; blob_cbSize	dd	?
;;BLOB	ends

CLIPDATA	struc
 clip_cbSize	dd	?
 clip_ulClipFmt	dd	?
CLIPDATA	ends

DVASPECT_CONTENT	= 1
DVASPECT_THUMBNAIL	= 2
DVASPECT_ICON		= 4
DVASPECT_DOCPRINT	= 8

STATFLAG_DEFAULT	= 0
STATFLAG_NONAME	= 1
STATFLAG_NOOPEN	= 2

;
; VARENUM usage key,
;
;; [V] - may appear in a VARIANT
;; [T] - may appear in a TYPEDESC
;; [P] - may appear in an OLE property set
;; [S] - may appear in a Safe Array
;
;
;  VT_EMPTY            [V]   [P]     nothing
;  VT_NULL             [V]   [P]     SQL style Null
;  VT_I2               [V][T][P][S]  2 byte signed int
;  VT_I4               [V][T][P][S]  4 byte signed int
;  VT_R4               [V][T][P][S]  4 byte real
;  VT_R8               [V][T][P][S]  8 byte real
;  VT_CY               [V][T][P][S]  currency
;  VT_DATE             [V][T][P][S]  date
;  VT_BSTR             [V][T][P][S]  OLE Automation string
;  VT_DISPATCH         [V][T][P][S]  IDispatch;
;  VT_ERROR            [V][T]   [S]  SCODE
;  VT_BOOL             [V][T][P][S]  True=-1, False=0
;  VT_VARIANT          [V][T][P][S]  VARIANT;
;  VT_UNKNOWN          [V][T]   [S]  IUnknown;
;  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
;  VT_I1                  [T]        signed char
;  VT_UI1              [V][T][P][S]  unsigned char
;  VT_UI2                 [T][P]     unsigned short
;  VT_UI4                 [T][P]     unsigned short
;  VT_I8                  [T][P]     signed 64-bit int
;  VT_UI8                 [T][P]     unsigned 64-bit int
;  VT_INT                 [T]        signed machine int
;  VT_UINT                [T]        unsigned machine int
;  VT_VOID                [T]        C style void
;  VT_HRESULT             [T]        Standard return type
;  VT_PTR                 [T]        pointer type
;  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
;  VT_CARRAY              [T]        C style array
;  VT_USERDEFINED         [T]        user defined type
;  VT_LPSTR               [T][P]     null terminated string
;  VT_LPWSTR              [T][P]     wide null terminated string
;  VT_FILETIME               [P]     FILETIME
;  VT_BLOB                   [P]     Length prefixed bytes
;  VT_STREAM                 [P]     Name of the stream follows
;  VT_STORAGE                [P]     Name of the storage follows
;  VT_STREAMED_OBJECT        [P]     Stream contains an object
;  VT_STORED_OBJECT          [P]     Storage contains an object
;  VT_BLOB_OBJECT            [P]     Blob contains an object
;  VT_CF                     [P]     Clipboard format
;  VT_CLSID                  [P]     A Class ID
;  VT_VECTOR                 [P]     simple counted array
;  VT_ARRAY            [V]           SAFEARRAY*
;  VT_BYREF            [V]           void* for local use


VT_EMPTY		equ	0
VT_NULL		equ	1
VT_I2		equ	2
VT_I4		equ	3
VT_R4		equ	4
VT_R8		equ	5
VT_CY		equ	6
VT_DATE		equ	7
VT_BSTR		equ	8
VT_DISPATCH		equ	9
VT_ERROR		equ	10
VT_BOOL		equ	11
VT_VARIANT		equ	12
VT_UNKNOWN		equ	13
VT_DECIMAL		equ	14
VT_I1		equ	16
VT_UI1		equ	17
VT_UI2		equ	18
VT_UI4		equ	19
VT_I8		equ	20
VT_UI8		equ	21
VT_INT		equ	22
VT_UINT		equ	23
VT_VOID		equ	24
VT_HRESULT		equ	25
VT_PTR		equ	26
VT_SAFEARRAY		equ	27
VT_CARRAY		equ	28
VT_USERDEFINED		equ	29
VT_LPSTR		equ	30
VT_LPWSTR		equ	31
VT_FILETIME		equ	64
VT_BLOB		equ	65
VT_STREAM		equ	66
VT_STORAGE		equ	67
VT_STREAMED_OBJECT	equ	68
VT_STORED_OBJECT	equ	69
VT_BLOB_OBJECT		equ	70
VT_CF		equ	71
VT_CLSID		equ	72
VT_VECTOR		equ	1000h
VT_ARRAY		equ	2000h
VT_BYREF		equ	4000h
VT_RESERVED		equ	8000h
VT_ILLEGAL		equ	0ffffh
VT_ILLEGALMASKED	equ	0fffh
VT_TYPEMASK		equ	0fffh
-#
