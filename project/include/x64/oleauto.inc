;+---------------------------------------------------------------------------
;
;Microsoft Windows
;Copyright (C) Microsoft Corporation, 1992 - 1996.
;
;File: oleauto.h
;
;Contents: Defines Ole Automation support function prototypes, constants
;
;----------------------------------------------------------------------------

SysAllocString		proto	:QWORD
SysFreeString		proto	:QWORD


 STDOLE_MAJORVERNUM	equ	1
 STDOLE_MINORVERNUM	equ	0
 STDOLE_LCID 		equ	0

; Version # of stdole2.tlb

 STDOLE2_MAJORVERNUM 	equ	2
 STDOLE2_MINORVERNUM 	equ	0
 STDOLE2_LCID		equ	0


; Flags for VariantChangeType/VariantChangeTypeEx

 VARIANT_NOVALUEPROP 	equ	1
 VARIANT_ALPHABOOL 	equ	2
 
; For VT_BOOL to VT_BSTR conversions,
; convert to "True"/"False" instead of
; "-1"/"0"

 VARIANT_NOUSEROVERRIDE 	equ	4
 
 VAR_TIMEVALUEONLY 	equ	1	; return time value 
 VAR_DATEVALUEONLY 	equ	2	; return date value 


; flags used by both dwInFlags and dwOutFlags:
 
 NUMPRS_LEADING_WHITE	equ	0001h
 NUMPRS_TRAILING_WHITE 	equ	0002h
 NUMPRS_LEADING_PLUS 	equ	0004h
 NUMPRS_TRAILING_PLUS	equ	0008h
 NUMPRS_LEADING_MINUS	equ	0010h
 NUMPRS_TRAILING_MINUS 	equ	0020h
 NUMPRS_HEX_OCT	equ	0040h
 NUMPRS_PARENS 		equ	0080h
 NUMPRS_DECIMAL		equ	0100h
 NUMPRS_THOUSANDS	equ	0200h
 NUMPRS_CURRENCY 	equ	0400h
 NUMPRS_EXPONENT 	equ	0800h
 NUMPRS_USE_ALL		equ	1000h
 NUMPRS_STD		equ	1FFFh

; flags used by dwOutFlags only:
 
 NUMPRS_NEG		equ	10000h
 NUMPRS_INEXACT		equ	20000h

; flags used by VarNumFromParseNum to indicate acceptable result types:
 
 VTBIT_I1		equ	1 SHL VT_I1
 VTBIT_UI1 		equ	1 SHL VT_UI1
 VTBIT_I2		equ	1 SHL VT_I2
 VTBIT_UI2 		equ	1 SHL VT_UI2
 VTBIT_I4		equ	1 SHL VT_I4
 VTBIT_UI4 		equ	1 SHL VT_UI4
 VTBIT_R4		equ	1 SHL VT_R4
 VTBIT_R8		equ	1 SHL VT_R8
 VTBIT_CY		equ	1 SHL VT_CY
 VTBIT_DECIMAL 		equ	1 SHL VT_DECIMAL

 VARCMP_LT		equ	0
 VARCMP_EQ		equ	1
 VARCMP_GT		equ	2
 VARCMP_NULL		equ	3


;---------------------------------------------------------------------
; New date functions
;---------------------------------------------------------------------

 VAR_VALIDDATE 		equ	4	; VarDateFromUdate() only 
 VAR_CALENDAR_HIJRI	equ	8	; use Hijri calender 
 VARIANT_CALENDAR_HIJRI 	equ	VAR_CALENDAR_HIJRI

 MEMBERID_NIL 		equ	DISPID_UNKNOWN
 ID_DEFAULTINST		equ	-2


; Flags for IDispatch::Invoke

 DISPATCH_METHOD 	equ	1
 DISPATCH_PROPERTYGET	equ	2
 DISPATCH_PROPERTYPUT	equ	4
 DISPATCH_PROPERTYPUTREF 	equ	8
 
REGKIND_DEFAULT		equ	0
REGKIND_REGISTER	equ	1
REGKIND_NONE		equ	2

;---------------------------------------------------------------------
;Active Object Registration API 
;---------------------------------------------------------------------

; flags for RegisterActiveObject 

 ACTIVEOBJECT_STRONG 	equ	0
 ACTIVEOBJECT_WEAK 	equ	1




comment #


;---------------------------------------------------------------------
;New VARIANT <-> string parsing functions 
;---------------------------------------------------------------------

NUMPARSE	struc
 nump_cDig	dd	?
 nump_dwInFlags	dd	?
 nump_dwOutFlags	dd	?
 nump_cchUsed	dd	?
 nump_nBaseShift	dd	?
 nump_nPwr10	dd	?
NUMPARSE	ends


; The UDATE structure is used with VarDateFromUdate() and VarUdateFromDate().
; It represents an "unpacked date".
 
UDATE		struc
 udate_st		SYSTEMTIME	<?>
 udate_wDayOfYear	dw	?
UDATE		ends


;---------------------------------------------------------------------
; IDispatch implementation support
;---------------------------------------------------------------------

PARAMDATA	struc
 paramd_szName	dd	?	; parameter name 
 paramd_vt	dd	?	; parameter type 
PARAMDATA	ends

METHODDATA	struc
 mthd_szName	dd	?	; method name 
 mthd_ppdata	dd	?	; pointer to an array of PARAMDATAs 
 mthd_dispid	dd	?	; method ID 
 mthd_iMeth	dd	?	; method index 
 mthd_cc	dd	?	; calling convention 
 mthd_cArgs	dd	?	; count of arguments 
 mthd_wFlags	dw	?	; same wFlags as on IDispatch::Invoke() 
 mthd_vtReturn	dd	?
METHODDATA	ends

INTERFACEDATA	struc
 intd_pmethdata	dd	?	; pointer to an array of METHODDATAs 
 intd_cMembers	dd	?	; count of members 
INTERFACEDATA	ends

-#
