;---------------------------------------------------------------------------
;
;  Microsoft Windows
;  Copyright (C) Microsoft Corporation, 1992 - 1996.
;
;  File:       objbase.h
;
;  Contents:   Component object model defintions.
;
;----------------------------------------------------------------------------

; LISet32(li, v) ((li).HighPart = (v) < 0 ? -1 : 0, (li).LowPart = (v))
; ULISet32(li, v) ((li).HighPart = 0, (li).LowPart = (v))


CLSCTX_INPROC	equ	CLSCTX_INPROC_SERVER + CLSCTX_INPROC_HANDLER


; With DCOM, CLSCTX_REMOTE_SERVER should be included

CLSCTX_ALL	equ	CLSCTX_INPROC_SERVER + CLSCTX_INPROC_HANDLER + CLSCTX_LOCAL_SERVER + CLSCTX_REMOTE_SERVER
CLSCTX_SERVER 	equ	CLSCTX_INPROC_SERVER + CLSCTX_LOCAL_SERVER + CLSCTX_REMOTE_SERVER

; interface marshaling definitions

MARSHALINTERFACE_MIN 	equ	500 ; minimum number of bytes for interface marshl

;
; Common typedefs for paramaters used in Storage API's, gleamed from storage.h
; Also contains Storage error codes, which should be moved into the storage
; idl files.
;

CWCSTORAGENAME 	equ	32

; Storage instantiation modes 

STGM_DIRECT 		equ	00000000h
STGM_TRANSACTED 	equ	00010000h
STGM_SIMPLE 		equ	08000000h
STGM_READ 		equ	00000000h
STGM_WRITE		equ	00000001h
STGM_READWRITE		equ	00000002h
STGM_SHARE_DENY_NONE	equ	00000040h
STGM_SHARE_DENY_READ	equ	00000030h
STGM_SHARE_DENY_WRITE 	equ	00000020h
STGM_SHARE_EXCLUSIVE	equ	00000010h
STGM_PRIORITY 		equ	00040000h
STGM_DELETEONRELEASE	equ	04000000h
STGM_NOSCRATCH		equ	00100000h
STGM_CREATE 		equ	00001000h
STGM_CONVERT		equ	00020000h
STGM_FAILIFTHERE	equ	00000000h
STGM_NOSNAPSHOT 	equ	00200000h

;flags for internet asyncronous and layout docfile 

ASYNC_MODE_COMPATIBILITY	equ	00000001h
ASYNC_MODE_DEFAULT	equ	00000000h

STGTY_REPEAT		equ	00000100h
STG_TOEND 		equ	0FFFFFFFFh
STG_LAYOUT_SEQUENTIAL 	equ	00000000h
STG_LAYOUT_INTERLEAVED	equ	00000001h

; here is where we pull in the MIDL generated headers for the interfaces 

; macros to define byte pattern for a GUID.
;Example: DEFINE_GUID(GUID_XXX, a, b, c, ...);
;
; Each dll/exe must initialize the GUIDs once.This is done in one of
; two ways.If you are not using precompiled headers for the file(s) which
; initializes the GUIDs, define INITGUID before including objbase.h.This
; is how OLE builds the initialized versions of the GUIDs which are included
; in ole2.lib.The GUIDs in ole2.lib are all defined in the same text
; segment GUID_TEXT.
;
; The alternative (which some versions of the compiler don't handle properly;
; they wind up with the initialized GUIDs in a data, not a text segment),
; is to use a precompiled version of objbase.h and then include initguid.h
; after objbase.h followed by one or more of the guid defintion files.

;;DEFINE_OLEGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)


COM_RIGHTS_EXECUTE equ	1

  COINIT_APARTMENTTHREADED  equ 2
  COINIT_MULTITHREADED      equ 0
  COINIT_DISABLE_OLE1DDE    equ 4
  COINIT_SPEED_OVER_MEMORY  equ 8

CoInitialize	proto	:QWORD
CoUninitialize	proto
CoGetMalloc	proto	:DWORD, :QWORD
CoGetCurrentProcess	proto
CoRegisterMallocSpy	proto	:QWORD
CoRevokeMallocSpy	proto
CoCreateStandardMalloc	proto	:DWORD, :QWORD
CoInitializeEx	proto	:QWORD, :DWORD
CoGetCallerTID	proto	:QWORD
CoTaskMemFree	proto	:QWORD
CoCreateInstance	proto	:QWORD, :QWORD, :DWORD, :QWORD, :QWORD