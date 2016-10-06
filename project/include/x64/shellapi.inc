;****************************************************************************
;
; shellapi.h -SHELL.DLL functions, types, and definitions
;
; Copyright (c) 1992-1996, Microsoft Corp.All rights reserved
;
;***************************************************************************

;
; Define API decoration for direct importing of DLL references.
;

;;#include <pshpack1.h>

	IFDEF	UNICODE

DragQueryFile	equ	DragQueryFileW
ExtractIcon	equ	ExtractIconW
ExtractIconEx	equ	ExtractIconExW
FindExecutable	equ	FindExecutableW
ShellAbout	equ	ShellAboutW
ShellExecute	equ	ShellExecuteW
ShellExecuteEx	equ	ShellExecuteExW
SHFileOperation	equ	SHFileOperationW
SHGetFileInfo	equ	SHGetFileInfoW

SHFILEINFO	equ	SHFILEINFOW
SHFILEOPSTRUCT	equ	SHFILEOPSTRUCTW
	
	ELSE

DragQueryFile	equ	DragQueryFileA
ExtractIcon	equ	ExtractIconA
ExtractIconEx	equ	ExtractIconExA
FindExecutable	equ	FindExecutableA
ShellAbout	equ	ShellAboutA
ShellExecute	equ	ShellExecuteA
ShellExecuteEx	equ	ShellExecuteExA
SHFileOperation	equ	SHFileOperationA
SHGetFileInfo	equ	SHGetFileInfoA

SHFILEINFO	equ	SHFILEINFOA
SHFILEOPSTRUCT	equ	SHFILEOPSTRUCTA

	ENDIF

ShellExecuteA		proto	:QWORD, :QWORD, :QWORD, :QWORD, :QWORD, :DWORD
ShellExecuteW		proto	:QWORD, :QWORD, :QWORD, :QWORD, :QWORD, :DWORD
ShellExecuteExA		proto	:QWORD
ShellExecuteExW		proto	:QWORD
SHFileOperationA		proto	:QWORD
SHFileOperationW		proto	:QWORD
SHGetFileInfoA		proto	:QWORD, :DWORD, :QWORD, :DWORD, :DWORD
SHGetFileInfoW		proto	:QWORD, :DWORD, :QWORD, :DWORD, :DWORD

; AppBar stuff

ABM_NEW 		= 00000000h
ABM_REMOVE		= 00000001h
ABM_QUERYPOS		= 00000002h
ABM_SETPOS		= 00000003h
ABM_GETSTATE		= 00000004h
ABM_GETTASKBARPOS 	= 00000005h
ABM_ACTIVATE		= 00000006h	; lParam == TRUE/FALSE means activate/deactivate
ABM_GETAUTOHIDEBAR 	= 00000007h
ABM_SETAUTOHIDEBAR 	= 00000008h	; this can fail at any time.MUST check the result lParam = TRUE/FALSESet/Unset uEdge = what edge
ABM_WINDOWPOSCHANGED 	= 0000009h

; these are put in the wparam of callback messages

ABN_STATECHANGE	= 0000000h
ABN_POSCHANGED 	= 0000001h
ABN_FULLSCREENAPP	= 0000002h
ABN_WINDOWARRANGE	= 0000003h	; lParam == TRUE means hide

; flags for get state

ABS_AUTOHIDE		= 0000001h
ABS_ALWAYSONTOP 	= 0000002h

ABE_LEFT	= 0
ABE_TOP	= 1
ABE_RIGHT	= 2
ABE_BOTTOM	= 3

APPBARDATA		struc
 abd_cbSize		dd	?
 abd_hWnd		dq	?
 abd_uCallbackMessage	dd	?
 abd_uEdge		dd	?
 abd_rc		RECT	<?>
 abd_lParam		dq	?	; message specific
APPBARDATA		ends

; EndAppBar

;; EIRESID(x) -1 * x

; Shell File Operations

FO_MOVE 	= 0001
FO_COPY 	= 0002
FO_DELETE 	= 0003
FO_RENAME 	= 0004

FOF_MULTIDESTFILES 	= 0001h
FOF_CONFIRMMOUSE 	= 0002h
FOF_SILENT 		= 0004h	; don't create progress/report
FOF_RENAMEONCOLLISION	= 0008h
FOF_NOCONFIRMATION 	= 0010h	; Don't prompt the user.
FOF_WANTMAPPINGHANDLE	= 0020h	; Fill in SHFILEOPSTRUCT.hNameMappings Must be freed using SHFreeNameMappings
FOF_ALLOWUNDO		= 0040h
FOF_FILESONLY		= 0080h	; on *.*, do only files
FOF_SIMPLEPROGRESS 	= 0100h	; means don't show names of files
FOF_NOCONFIRMMKDIR 	= 0200h	; don't confirm making any needed dirs
FOF_NOERRORUI		= 0400h	; don't put up error UI

PO_DELETE 		= 0013h	; printer is being deleted
PO_RENAME 		= 0014h	; printer is being renamed
PO_PORTCHANGE 		= 0020h	; port this printer connected to is being changed if this id is set, the strings received by the copyhook are a doubly-null terminated list of strings.The first is the printer name and the second is the printer port.
PO_REN_PORT 		= 0034	; PO_RENAME and PO_PORTCHANGE at same time.

; no POF_ flags currently defined

; implicit parameters are: if pFrom or pTo are unqualified names the current directories are
; taken from the global current drive/directory settings managed by Get/SetCurrentDrive/Directory
; the global confirmation settings

SHFILEOPSTRUCTA		struc
 hwnd		dq	?
 wFunc		dq	?
 pFrom		dq	?
 pTo		dq	?
 fFlags		dw	?	; odd structure len !!!
		dw	?
 fAnyOperationsAborted	dd	?
 hNameMappings		dq	?
 lpszProgressTitle		dq	? 	; only used if FOF_SIMPLEPROGRESS
SHFILEOPSTRUCTA		ends

SHFILEOPSTRUCTW	struc
 hwnd		dq	?
 wFunc		dq	?
 pFrom		dq	?
 pTo		dq	?
 fFlags		dw	?	; odd structure len !!!
		dw	?
 fAnyOperationsAborted	dd	?
 hNameMappings		dq	?
 lpszProgressTitle		dq	? 	; only used if FOF_SIMPLEPROGRESS
SHFILEOPSTRUCTW	ends

SHNAMEMAPPINGA	struc
 pszOldPath	dq	?
 pszNewPath	dq	?
 cchOldPath	dd	?
 cchNewPath	dd	?
SHNAMEMAPPINGA	ends

SHNAMEMAPPING	equ	SHNAMEMAPPINGA

; End Shell File Operations

; Begin ShellExecuteEx and family

; ShellExecute() and ShellExecuteEx() error codes

; regular WinExec() codes

SE_ERR_FNF		= 2	; file not found
SE_ERR_PNF		= 3	; path not found
SE_ERR_ACCESSDENIED	= 5	; access denied
SE_ERR_OOM		= 8	; out of memory
SE_ERR_DLLNOTFOUND	= 32

; error values for ShellExecute() beyond the regular WinExec() codes

SE_ERR_SHARE		= 26
SE_ERR_ASSOCINCOMPLETE	= 27
SE_ERR_DDETIMEOUT	= 28
SE_ERR_DDEFAIL		= 29
SE_ERR_DDEBUSY		= 30
SE_ERR_NOASSOC		= 31

; Note CLASSKEY overrides CLASSNAME

SEE_MASK_CLASSNAME	= 00000001h
SEE_MASK_CLASSKEY 	= 00000003h	; Note INVOKEIDLIST overrides IDLIST
SEE_MASK_IDLIST 		= 00000004h
SEE_MASK_INVOKEIDLIST 	= 0000000ch
SEE_MASK_ICON 		= 00000010h
SEE_MASK_HOTKEY 	= 00000020h
SEE_MASK_NOCLOSEPROCESS 	= 00000040h
SEE_MASK_CONNECTNETDRV	= 00000080h
SEE_MASK_FLAG_DDEWAIT 	= 00000100h
SEE_MASK_DOENVSUBST 	= 00000200h
SEE_MASK_FLAG_NO_UI 	= 00000400h
SEE_MASK_UNICODE	= 00004000h
SEE_MASK_NO_CONSOLE 	= 00008000h
SEE_MASK_ASYNCOK	= 00100000h

SHELLEXECUTEINFOA	struc
 cbSize		dd	?
 fMask		dd	?
 hwnd		dq	?
 lpVerb		dq	?
 lpFile		dq	?
 lpParameters		dq	?
 lpDirectory		dq	?
 nShow		dd	?
 hInstApp		dq	?	; Optional fields
 lpIDList		dq	?
 lpClass		dq	?
 hkeyClass		dq	?
 dwHotKey		dd	?
 hIcon		dq	?
 hProcess		dq	?
SHELLEXECUTEINFOA	ends

SHELLEXECUTEINFOW	struc
 cbSize		dd	?
 fMask		dd	?
 hwnd		dq	?
 lpVerb		dq	?
 lpFile		dq	?
 lpParameters		dq	?
 lpDirectory		dq	?
 nShow		dd	?
 hInstApp		dq	?	; Optional fields
 lpIDList		dq	?
 lpClass		dq	?
 hkeyClass		dq	?
 dwHotKey		dd	?
 hIcon		dq	?
 hProcess		dq	?
SHELLEXECUTEINFOW	ends

SHELLEXECUTEINFO	equ	SHELLEXECUTEINFOA

; End ShellExecuteEx and family

; Tray notification definitions

NOTIFYICONDATAA	struc
 cbSize		dd	?
 hWnd		dq	?
 uID		dd	?
 uFlags		dd	?
 uCallbackMessage		dq	?
 hIcon		dq	?
 szTip		db	64 dup(?)
NOTIFYICONDATAA	ends

NOTIFYICONDATA		equ	NOTIFYICONDATAA

NIM_ADD 		= 0
NIM_MODIFY		= 1
NIM_DELETE		= 2

NIF_MESSAGE 		= 1
NIF_ICON		= 2
NIF_TIP 		= 4

; End Tray Notification Icons

; Begin SHGetFileInfo

;
; The SHGetFileInfo API provides an easy way to get attributes
; for a file given a pathname.
;
; PARAMETERS
;
; pszPathfile name to get info about
; dwFileAttributes file attribs, only used with SHGFI_USEFILEATTRIBUTES
; psfi place to return file info
; cbFileInfo size of structure
; uFlags flags
;
; RETURN
; TRUE if things worked


SHFILEINFOA	struc
 hIcon	dq	?
 iIcon	dd	?	; out: icon index
 dwAttributes	dd	?	; out: SFGAO_ flags
 szDisplayName	db	MAX_PATH dup(?)	; out: display name (or path)
 szTypeName	db	80 dup(?)	; out: type name
SHFILEINFOA	ends

SHFILEINFOW	struc
 hIcon	dq	?
 iIcon	dd	?	; out: icon index
 dwAttributes	dd	?	; out: SFGAO_ flags
 szDisplayName	dw	MAX_PATH dup(?)	; out: display name (or path)
 szTypeName	dw	80 dup(?)	; out: type name
SHFILEINFOW	ends

SHGFI_ICON		= 000000100h	; get icon
SHGFI_DISPLAYNAME 	= 000000200h	; get display name
SHGFI_TYPENAME		= 000000400h	; get type name
SHGFI_ATTRIBUTES	= 000000800h	; get attributes
SHGFI_ICONLOCATION	= 000001000h	; get icon location
SHGFI_EXETYPE 		= 000002000h	; return exe type
SHGFI_SYSICONINDEX	= 000004000h	; get system icon index
SHGFI_LINKOVERLAY 	= 000008000h	; put a link overlay on icon
SHGFI_SELECTED		= 000010000h	; show icon in selected state
SHGFI_LARGEICON 		= 000000000h	; get large icon
SHGFI_SMALLICON 	= 000000001h	; get small icon
SHGFI_OPENICON		= 000000002h	; get open icon
SHGFI_SHELLICONSIZE 	= 000000004h	; get shell size icon
SHGFI_PIDL		= 000000008h	; pszPath is a pidl
SHGFI_USEFILEATTRIBUTES 	= 000000010h	; use passed dwFileAttribute

SHGNLI_PIDL 		= 1	; pszLinkTo is a pidl
SHGNLI_PREFIXNAME 	= 2	; Make name "Shortcut to xxx"
SHGNLI_NOUNIQUE 	= 4	; don't do the unique name generation

; End SHGetFileInfo
