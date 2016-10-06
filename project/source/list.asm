;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - file list class
; note:	copyright © by digital performance 1997 - 2014
; license:
;
; This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
; assembler:	Visual Studio 2013
; last update:	2013-02-20 - Deutsch - make x64
;------------------------------------------------------------------------------------------------------------------------------------------

	include	windows.inc
	include	commctrl.inc
	include	shellapi.inc

	include	app.inc
	include	config.inc
	include	list.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new list object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	pxList listNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

listNew	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	.allocstack	32
	.endprolog

	; -- allocate and set vtable --

	call	GetProcessHeap
	test	rax, rax
	jz	listExit

	mov	r8, sizeof CLASS_LIST
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	listExit

	lea	rcx, [rax.CLASS_LIST.xInterface]
	mov	[rax.CLASS_LIST.vtableThis], rcx

	lea	rdx, listInit
	mov	[rcx.CLASS_LIST_IFACE.pfnInit], rdx
	lea	rdx, listRelease
	mov	[rcx.CLASS_LIST_IFACE.pfnRelease], rdx
	lea	rdx, listLoadConfig
	mov	[rcx.CLASS_LIST_IFACE.pfnLoadConfig], rdx
	lea	rdx, listInitControl
	mov	[rcx.CLASS_LIST_IFACE.pfnInitControl], rdx
	lea	rdx, listInitColumn
	mov	[rcx.CLASS_LIST_IFACE.pfnInitColumn], rdx
	lea	rdx, listChangeColumn
	mov	[rcx.CLASS_LIST_IFACE.pfnChangeColumn], rdx
	lea	rdx, listChangeColor
	mov	[rcx.CLASS_LIST_IFACE.pfnChangeColor], rdx
	lea	rdx, listChangeFont
	mov	[rcx.CLASS_LIST_IFACE.pfnChangeFont], rdx
	lea	rdx, listResize
	mov	[rcx.CLASS_LIST_IFACE.pfnResize], rdx
	lea	rdx, listHandleNotify
	mov	[rcx.CLASS_LIST_IFACE.pfnHandleNotify], rdx
	lea	rdx, listProcess
	mov	[rcx.CLASS_LIST_IFACE.pfnProcess], rdx
	lea	rdx, listStartThread
	mov	[rcx.CLASS_LIST_IFACE.pfnStartThread], rdx
	lea	rdx, listStopThread
	mov	[rcx.CLASS_LIST_IFACE.pfnStopThread], rdx
	lea	rdx, listReleaseControl
	mov	[rcx.CLASS_LIST_IFACE.pfnReleaseControl], rdx

listExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

listNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize list control window
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listInitControl (pxApp)
;	[in] pxApp .. main application
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listInitControl	PROC	FRAME
	LOCAL	hwndList:QWORD	; new control
	LOCAL	txClass [16]:WORD	; list window class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * 16 + 8
	sub	rsp, 96
	.allocstack	96 + 1 * 8 + 2 * 16 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, rdx

	; -- open window --

	lea	r9, txClass
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_LISTCLASS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	qword ptr [rsp + 88], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rsp + 80], rax
	mov	rax, [r15.CLASS_LIST.idList]
	mov	[rsp + 72], rax
	mov	rax, [r12.CLASS_APP.hwndApp]
	mov	[rsp + 64], eax
	mov	eax, CW_USEDEFAULT
	mov	[rsp + 56], eax
	mov	[rsp + 48], eax
	mov	[rsp + 40], eax
	mov	[rsp + 32], eax
	mov	r9d, LVS_SHAREIMAGELISTS OR LVS_SHOWSELALWAYS OR LVS_REPORT OR WS_CHILD OR WS_VISIBLE OR WS_VSCROLL
	mov	r8, 0
	lea	rdx, txClass
	mov	ecx, WS_EX_STATICEDGE
	call	CreateWindowEx
	test	rax, rax
	jz	listFail

	mov	hwndList, rax

	mov	rax, hwndList
	mov	[r15.CLASS_LIST.hwndList], rax

	mov	r8, r15
	mov	edx, GWLP_USERDATA
	mov	rcx, hwndList
	call	SetWindowLongPtr

	lea	r8, wndprcList
	mov	edx, GWLP_WNDPROC
	mov	rcx, hwndList
	call	SetWindowLongPtr

	mov	r9d, LVS_EX_FULLROWSELECT
	mov	r8d, LVS_EX_FULLROWSELECT
	mov	edx, LVM_SETEXTENDEDLISTVIEWSTYLE
	mov	rcx, hwndList
	call	SendMessage

	; -- clone id for header --

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, LVM_GETHEADER
	mov	rcx, hwndList
	call	SendMessage

	mov	r8, [r15.CLASS_LIST.idList]
	mov	edx, GWLP_ID
	mov	rcx, rax
	call	SetWindowLongPtr

	; -- init list view --

	mov	r9d, dword ptr [r15.CLASS_LIST.xParams.VIEW_PARAM.unBgColor]
	mov	r8d, 0
	mov	edx, LVM_SETBKCOLOR
	mov	rcx, hwndList
	call	SendMessage

	mov	r9d, dword ptr [r15.CLASS_LIST.xParams.VIEW_PARAM.unBgColor]
	mov	r8d, 0
	mov	edx, LVM_SETTEXTBKCOLOR
	mov	rcx, hwndList
	call	SendMessage

	mov	r9d, dword ptr [r15.CLASS_LIST.xParams.VIEW_PARAM.unFgColor]
	mov	r8d, 0
	mov	edx, LVM_SETTEXTCOLOR
	mov	rcx, hwndList
	call	SendMessage

	mov	rdx, [r15.CLASS_LIST.idList]
	mov	rcx, r15
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnInitColumn]

	; -- init list font --

	lea	r8, [r15.CLASS_LIST.hfontList]
	lea	rdx, [r15.CLASS_LIST.xParams]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnCreateViewFont]

	mov	r9, 0
	mov	r8, [r15.CLASS_LIST.hfontList]
	mov	edx, WM_SETFONT
	mov	rcx, hwndList
	call	SendMessage

	xor	rax, rax
	jmp	listExit

listFail:	call	GetLastError

listExit:	add	rsp, 96
	add	rsp, 1 * 8 + 2 * 16 + 8

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

listInitControl	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize list object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listInit (idList, ptxPath, pxApp)
;	[in] idList .. child window ID
;	[in] ptxPath .. initial path
;	[in] pxApp .. main application
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listInit	PROC	FRAME
	LOCAL	idList:QWORD	; list child ID
	LOCAL	ptxPath:QWORD	; list path
	LOCAL	idConfig:QWORD	; configuration text

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	idList, rdx
	mov	ptxPath, r8
	mov	r12, r9

	; -- prepare members --

	mov	rcx, idList
	mov	rdx, ptxPath
	mov	[r15.CLASS_LIST.idList], rcx
	mov	[r15.CLASS_LIST.ptxPath], rdx
	mov	[r15.CLASS_LIST.pxApp], r12

	; -- get object for list --

	mov	rax, idList
	cmp	rax, IDC_LEFT
	je	listLeft

	mov	idConfig, IDS_CFG_RIGHTLIST
	jmp	listLoad

listLeft:	mov	idConfig, IDS_CFG_LEFTLIST

	; -- load config --

listLoad:	lea	r9, [r15.CLASS_LIST.txSection]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, idConfig
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	rcx, r15
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnLoadConfig]
	test	rax, rax
	jnz	listExit

	; -- create control window --

	mov	rdx, r12
	mov	rcx, r15
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnInitControl]
	test	rax, rax
	jnz	listExit

	; -- init thread events --

	mov	r9, 0
	mov	r8d, 0
	mov	edx, TRUE
	mov	rcx, 0
	call	CreateEvent
	mov	[r15.CLASS_LIST.hevStop], rax

	xor	rax, rax

listExit:	add	rsp, 32
	add	rsp, 3 * 8 + 8

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

listInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release list object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listRelease ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listRelease	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32 + 8
	.allocstack	32 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	; -- free resources --

	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnReleaseControl]

	mov	rcx, [r15.CLASS_LIST.hevStop]
	call	CloseHandle

	; -- free object --

	call	GetProcessHeap

	mov	r8, r15
	mov	edx, 0
	mov	rcx, rax
	call	HeapFree

	xor	rax, rax

	add	rsp, 32 + 8

	pop	r15
	pop	rbp
	ret	0

	align	4

listRelease	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release list control window
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listReleaseControl ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listReleaseControl	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32 + 8
	.allocstack	32 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	; -- free resources --

	mov	rcx, [r15.CLASS_LIST.hfontList]
	call	DeleteObject

	; -- close list window --

	mov	r8, 0
	mov	edx, GWLP_USERDATA
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SetWindowLongPtr

	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	DestroyWindow

	xor	rax, rax

	add	rsp, 32 + 8

	pop	r15
	pop	rbp
	ret	0

	align	4

listReleaseControl	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	loads list data from config file - if none, create new
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listLoadConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listLoadConfig	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 48
	.allocstack	48
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_LIST.pxApp]

	; -- load multiple list configuration data --

	lea	rax, [r15.CLASS_LIST.xParams]

	mov	[rax.VIEW_PARAM.unBgColor], DEF_BGCOLOR
	mov	[rax.VIEW_PARAM.unFgColor], DEF_FGCOLOR
	mov	[rax.VIEW_PARAM.unFontSize], DEF_LISTSIZE
	mov	[rax.VIEW_PARAM.unItalic], FALSE
	mov	[rax.VIEW_PARAM.unWeight], FW_NORMAL

	lea	r9, [rax.VIEW_PARAM.txFontName]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DEF_LISTFONT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, [r15.CLASS_LIST.xParams]
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigView]

	; -- load list column widths --

	lea	rax, [r15.CLASS_LIST.unMode]
	mov	[rsp + 32], rax
	mov	r9, LIST_SYMBOL OR LIST_SIZE OR LIST_TYPE OR LIST_DATE
	mov	r8, IDS_CFG_LISTMODE
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	lea	rax, [r15.CLASS_LIST.unCwName]
	mov	[rsp + 32], rax
	mov	r9, 300
	mov	r8, IDS_CFG_LISTNAMECOL
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	lea	rax, [r15.CLASS_LIST.unCwSize]
	mov	[rsp + 32], rax
	mov	r9, 100
	mov	r8, IDS_CFG_LISTSIZECOL
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	lea	rax, [r15.CLASS_LIST.unCwType]
	mov	[rsp + 32], rax
	mov	r9, 100
	mov	r8, IDS_CFG_LISTTYPECOL
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	lea	rax, [r15.CLASS_LIST.unCwDate]
	mov	[rsp + 32], rax
	mov	r9, 100
	mov	r8, IDS_CFG_LISTDATECOL
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	xor	rax, rax

	add	rsp, 48

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

listLoadConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	read column widths and texts, put columns into listview
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listInitColumn (idList)
;	[in] idList .. left or right list
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listInitColumn	PROC	FRAME
	LOCAL	idList:QWORD	; list id (left/right)
	LOCAL	unState:QWORD	; menu item state
	LOCAL	xColumn:LVCOLUMN	; column information
	LOCAL	xInfo:SHFILEINFO	; shell file information
	LOCAL	txBuffer [64]:WORD
	LOCAL	txDefShell [64]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 64 + 2 * 64 + sizeof LVCOLUMN + sizeof SHFILEINFO + 8
	sub	rsp, 48
	.allocstack	48 + 2 * 8 + 2 * 64 + 2 * 64 + sizeof LVCOLUMN + sizeof SHFILEINFO + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	idList, rdx
	mov	r12, [r15.CLASS_LIST.pxApp]

	; -- init column info --

	mov	unState, MFS_UNCHECKED

	mov	xColumn.LVCOLUMN.lmask, LVCF_FMT OR LVCF_WIDTH OR LVCF_SUBITEM OR LVCF_TEXT
	mov	xColumn.LVCOLUMN.iSubItem, 0

	; -- init smybols --

	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SYMBOL
	je	listName

	lea	r9, txDefShell
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DEFPATH
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	eax, SHGFI_SYSICONINDEX OR SHGFI_SMALLICON
	mov	[rsp + 32], eax
	mov	r9d, sizeof SHFILEINFO
	lea	r8, xInfo
	mov	edx, 0
	lea	rcx, txDefShell
	call	SHGetFileInfo

	mov	r9, rax
	mov	r8d, LVSIL_SMALL
	mov	edx, LVM_SETIMAGELIST
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	rax, idList
	cmp	rax, IDC_LEFT
	je	listLeft

	mov	rdx, IDM_RIGHT_SYMBOL
	jmp	listSet

listLeft:	mov	rdx, IDM_LEFT_SYMBOL

listSet:	mov	unState, 0

	lea	r8, unState
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetMenuState]

	; -- init name column --

listName:	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLNAME
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, [r15.CLASS_LIST.unCwName]

	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	inc	xColumn.LVCOLUMN.iSubItem

	; -- init size column --

	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SIZE
	je	listType

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLSIZE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, [r15.CLASS_LIST.unCwSize]

	mov	xColumn.LVCOLUMN.fmt, LVCFMT_RIGHT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	rax, idList
	cmp	rax, IDC_LEFT
	je	listLeft2

	mov	rdx, IDM_RIGHT_SIZE
	jmp	listSet2

listLeft2:	mov	rdx, IDM_LEFT_SIZE

listSet2:	mov	unState, 0

	lea	r8, unState
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetMenuState]

	inc	xColumn.LVCOLUMN.iSubItem

	; -- init type column --

listType:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_TYPE
	je	listDate

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLTYPE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, [r15.CLASS_LIST.unCwType]

	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	rax, idList
	cmp	rax, IDC_LEFT
	je	listLeft3

	mov	rdx, IDM_RIGHT_TYPE
	jmp	listSet3

listLeft3:	mov	rdx, IDM_LEFT_TYPE

listSet3:	mov	unState, 0

	lea	r8, unState
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetMenuState]

	inc	xColumn.LVCOLUMN.iSubItem

	; -- init date column --

listDate:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_DATE
	je	listExit

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLDATE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, [r15.CLASS_LIST.unCwDate]

	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	rax, idList
	cmp	rax, IDC_LEFT
	je	listLeft4

	mov	rdx, IDM_RIGHT_DATE
	jmp	listSet4

listLeft4:	mov	rdx, IDM_LEFT_DATE

listSet4:	mov	unState, 0

	lea	r8, unState
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetMenuState]

	inc	xColumn.LVCOLUMN.iSubItem

	; insert more column types here

listExit:	xor	rax, rax

	add	rsp, 48
	add	rsp, 2 * 8 + 2 * 64 + 2 * 64 + sizeof LVCOLUMN + sizeof SHFILEINFO + 8

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

listInitColumn	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	apply column mode and change configuration
; last update:	2002-12-27 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError listChangeColumn (unColumn, fVisible)
;	[in] unColumn .. which column
;	[in] fVisible .. make column visible or hide it
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listChangeColumn	PROC	FRAME
	LOCAL	unColumn:QWORD	; which column to change
	LOCAL	fVisible:QWORD	; make visible or hide
	LOCAL	rcApp:RECT	; application size

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + sizeof RECT
	sub	rsp, 32
	.allocstack	32 + 2 * 8 + sizeof RECT
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	unColumn, rdx
	mov	fVisible, r8
	mov	r12, [r15.CLASS_LIST.pxApp]

	mov	rdx, [r15.CLASS_LIST.idList]
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetActive]

	; -- make visible or hide --

	cmp	fVisible, FALSE
	je	listDelete

	; -- set visible --

	mov	rax, unColumn
	or	[r15.CLASS_LIST.unMode], rax
	jmp	listSet

	; -- set hidden --

listDelete:	mov	rax, unColumn
	not	rax
	and	[r15.CLASS_LIST.unMode], rax

	; -- write back to configuration --

listSet:	mov	r9, [r15.CLASS_LIST.unMode]
	mov	r8, IDS_CFG_LISTMODE
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- re-create list --

	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnReleaseControl]

	mov	rdx, r12
	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnInitControl]

	; -- resize list --

	lea	rdx, rcApp
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	GetClientRect

	lea	rdx, rcApp
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnResize]

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 2 * 8 + sizeof RECT

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

listChangeColumn	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	ask for new color, apply changes
; last update:	2002-12-27 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError listChangeColor (unMode)
;	[in] unMode .. change foreground or background color
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listChangeColor	PROC	FRAME
	LOCAL	unMode:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	unMode, rdx
	mov	r12, [r15.CLASS_LIST.pxApp]

	; -- get color --

	mov	rax, unMode
	cmp	rax, CHANGE_BGCOLOR
	je	listBack

	lea	rdx, [r15.CLASS_LIST.xParams.VIEW_PARAM.unFgColor]
	jmp	listQuery

listBack:	lea	rdx, [r15.CLASS_LIST.xParams.VIEW_PARAM.unBgColor]

	; -- query new color --

listQuery:	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnColorDialog]
	test	rax, rax
	jnz	listExit

	; -- apply color

	mov	rax, unMode
	cmp	rax, CHANGE_BGCOLOR
	je	listBgCol

	; -- apply foreground --

	mov	r9, [r15.CLASS_LIST.xParams.VIEW_PARAM.unFgColor]
	mov	r8d, 0
	mov	edx, LVM_SETTEXTCOLOR
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	jmp	listStore

	; -- apply background --

listBgCol:	mov	r9, [r15.CLASS_LIST.xParams.VIEW_PARAM.unBgColor]
	mov	r8d, 0
	mov	edx, LVM_SETBKCOLOR
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	r9, [r15.CLASS_LIST.xParams.VIEW_PARAM.unBgColor]
	mov	r8d, 0
	mov	edx, LVM_SETTEXTBKCOLOR
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- update list --

listStore:	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	InvalidateRect

	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	UpdateWindow

	; -- save config --

	lea	r8, [r15.CLASS_LIST.xParams]
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigView]

	xor	rax, rax
	jmp	listExit

listFail:	mov	rax, E_FAIL

listExit:	add	rsp, 32
	add	rsp, 1 * 8 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

listChangeColor	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	ask for new font, apply changes
; last update:	2002-12-27 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError listChangeFont ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listChangeFont	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	.allocstack	32 + 2 * 64
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_LIST.pxApp]

	; -- get font --

	lea	rdx, [r15.CLASS_LIST.xParams]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnFontDialog]
	test	rax, rax
	jnz	listExit

	mov	rcx, [r15.CLASS_LIST.hfontList]
	call	DeleteObject

	lea	r8, [r15.CLASS_LIST.hfontList]
	lea	rdx, [r15.CLASS_LIST.xParams]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnCreateViewFont]

	mov	r9, 0
	mov	r8, [r15.CLASS_LIST.hfontList]
	mov	edx, WM_SETFONT
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- update list --

	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	InvalidateRect

	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	UpdateWindow

	; -- save config --

	lea	r8, [r15.CLASS_LIST.xParams]
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigView]

	xor	rax, rax

listExit:	add	rsp, 32

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

listChangeFont	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	resize list and its columns to new width
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listResize (prcSize)
;	[in] prcSize .. new rectangle
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listResize	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 48
	.allocstack	48 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	mov	dword ptr [rsp + 40], TRUE
	mov	eax, [rdx.RECT.bottom]
	mov	[rsp + 32], eax
	mov	r9d, [rdx.RECT.right]
	mov	r8d, [rdx.RECT.top]
	mov	edx, [rdx.RECT.left]
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	MoveWindow

	; -- size columns --

	xor	rax, rax

	add	rsp, 48
	add	rsp, 8

	pop	r15
	pop	rbp

	ret	0

	align	4

listResize	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	process all items from given list view
; last update:	2002-12-30 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError listProcess (pfnCallback, pxUser)
;	[in] pfnCallback .. callback function, called with each list item
;	[in] pxUser .. user parameter for callback
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listProcess	PROC	FRAME
	LOCAL	pfnCallback:QWORD	; callback function
	LOCAL	pxUser:QWORD	; callback user parameter
	LOCAL	unCount:QWORD	; loop counter
	LOCAL	unItem:QWORD	; current item
	LOCAL	txItem [DEF_PATH_LENGTH]:WORD	; item text
	LOCAL	xItem:LVITEM	; list item information

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof LVITEM
	sub	rsp, 32
	.allocstack	32 + 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof LVITEM
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	pfnCallback, rdx
	mov	pxUser, r8

	; -- loop list items --

	mov	unCount, 0
	mov	unItem, 0FFFFFFFFh

listLoop:	mov	r9d, LVNI_ALL
	mov	r8d, dword ptr unItem
	mov	edx, LVM_GETNEXTITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage
	cmp	eax, -1
	je	listDone

	mov	unItem, rax

	; -- get items text --

	lea	r9, xItem
	mov	[r9.LVITEM.lmask], LVIF_TEXT OR LVIF_STATE OR LVIF_PARAM
	mov	[r9.LVITEM.stateMask], LVIS_CUT OR LVIS_DROPHILITED OR LVIS_FOCUSED OR LVIS_SELECTED
	mov	[r9.LVITEM.iItem], eax
	mov	[r9.LVITEM.iSubItem], 0
	mov	[r9.LVITEM.state], 0
	lea	rax, txItem
	mov	[r9.LVITEM.pszText], rax
	mov	[r9.LVITEM.cchTextMax], DEF_PATH_LENGTH - 1

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage
	test	rax, rax
	je	listNext

	mov	r8, pxUser
	mov	rdx, unCount
	lea	rcx, xItem
	call	pfnCallback
	test	rax, rax
	jnz	listExit

listNext:	inc	unCount
	jmp	listLoop

listDone:	xor	rax, rax

listExit:	add	rsp, 32
	add	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof LVITEM
	
	pop	r15
	pop	rbp
	
	ret	0
	
	align	4
	
listProcess	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	start new folder reading thread
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listStartThread ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listStartThread	PROC	FRAME
	LOCAL	idThread:QWORD	; fill thread id

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 48
	.allocstack	48 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	lea	rax, idThread
	mov	[rsp + 40], rax
	mov	dword ptr [rsp + 32], 0
	mov	r9, r15
	lea	r8, listListThread
	mov	rdx, 0
	mov	rcx, 0
	call	CreateThread
	test	rax, rax
	jz	listFail

	mov	[r15.CLASS_LIST.hthFill], rax

	xor	rax, rax
	jmp	listExit

listFail:	call	GetLastError

listExit:	add	rsp, 48
	add	rsp, 8

	pop	r15
	pop	rbp

	ret	0

	align	4

listStartThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	stop running thread, if any
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listStopThread ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listStopThread	PROC	FRAME
	LOCAL	xMessage:MSG	; handle messages during wait

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof MSG + 8
	sub	rsp, 48
	.allocstack	48 + sizeof MSG + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	; -- check if thread is running --

	mov	rcx, [r15.CLASS_LIST.hthFill]
	test	rcx, rcx
	jz	listDone

	; -- check if already at end --

	mov	edx, 0
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	je	listEnded

	; -- stop now ! --

	mov	rcx, [r15.CLASS_LIST.hevStop]
	call	SetEvent

	; -- wait for end --

listLoop:	mov	dword ptr [rsp + 32], PM_REMOVE
	mov	r9d, 0
	mov	r8d, 0
	mov	rdx, 0
	lea	rcx, xMessage
	call	PeekMessage
	test	eax, eax
	jz	listWait

	lea	rcx, xMessage
	call	DispatchMessage

	jmp	listLoop

listWait:	mov	dword ptr [rsp + 32], QS_ALLINPUT
	mov	r9d, 1000
	mov	r8d, FALSE
	lea	rdx, [r15.CLASS_LIST.hthFill]
	mov	ecx, 1
	call	MsgWaitForMultipleObjects
	cmp	eax, WAIT_OBJECT_0
	je	listStopped
	cmp	eax, WAIT_OBJECT_0 + 1
	je	listLoop

	; -- thread will not end, terminate --

	mov	rdx, 0
	mov	rcx, [r15.CLASS_LIST.hthFill]
	call	TerminateThread

	; -- reset stop signal --

listStopped:
	mov	rcx, [r15.CLASS_LIST.hevStop]
	call	ResetEvent

	; -- thread has ended regular or has been terminated --

listEnded:	mov	rcx, [r15.CLASS_LIST.hthFill]
	call	CloseHandle

	mov	[r15.CLASS_LIST.hthFill], 0

listDone:	xor	rax, rax

	add	rsp, 48
	add	rsp, sizeof MSG + 8

	pop	r15
	pop	rbp

	ret	0

	align	4

listStopThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	thread that fills the list
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError listListThread (pxList)
;	[in] pxList .. list to work on
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listListThread	PROC	FRAME
	LOCAL	xParam:LISTFILL_DATA	; fill enum parameter

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof LISTFILL_DATA
	sub	rsp, 48
	.allocstack	48 + sizeof LISTFILL_DATA
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_LIST.pxApp]

	; -- reset list --

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, LVM_DELETEALLITEMS
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_SETREDRAW
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- begin path processing --

	mov	xParam.LISTFILL_DATA.pxList, r15
	mov	xParam.LISTFILL_DATA.unCount, 0

	; -- get multiple format strings --

	lea	r9, xParam.LISTFILL_DATA.txDirTag
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_DIRTAG
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, xParam.LISTFILL_DATA.txFmtDate
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_DATEFORMAT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, xParam.LISTFILL_DATA.txFmtTime
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_TIMEFORMAT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	; -- process all files --

	mov	qword ptr [rsp + 32], 0
	mov	r9, FALSE
	lea	r8, xParam
	lea	rdx, cbInsert
	mov	rcx, [r15.CLASS_LIST.ptxPath]
	call	prcWalkFolder

	; -- all items ok, sort --

	lea	r9, cbSort
	mov	r8, r15
	mov	edx, LVM_SORTITEMSEX
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	r9d, 0
	mov	r8d, 1
	mov	edx, WM_SETREDRAW
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	rcx, 0
	call	ExitThread

	add	rsp, 48
	add	rsp, sizeof LISTFILL_DATA

	pop	r15
	pop	r12
	pop	rbp
	
	ret	0
	
	align	4

listListThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle notify messages
; last update:	2002-12-30 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError listHandleNotify (pxNotify)
;	[in] pxNotify .. windows notification message to handle
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

listHandleNotify	PROC	FRAME
	LOCAL	pxNotify:QWORD	; notification information
	LOCAL	unWidth:QWORD	; column width
	LOCAL	idConfig:QWORD	; configure ID

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	pxNotify, rdx

	; -- check for headers --

	mov	rax, pxNotify
	mov	eax, [rax.NMHDR.lcode]
	cmp	eax, HDN_ITEMCHANGED
	je	listChange
	cmp	eax, LVN_KEYDOWN 
	je	listKey
	cmp	eax, LVN_COLUMNCLICK
	je	listColumn

	jmp	listDone

	; -- key in list pressed --

listKey:	mov	rax, pxNotify
	mov	cx, [rax.NMLVKEYDOWN.wVKey]

	cmp	cx, VK_RETURN
	je	listReturn

	; add more

	jmp	listDone

	; -- return pressed - handel as double click --

listReturn:	call	GetMessagePos

	mov	rcx, pxNotify
	mov	r9d, eax
	mov	r8d, 0
	mov	edx, WM_LBUTTONDBLCLK
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	jmp	listDone

	; -- column clicked --

listColumn:	mov	rax, pxNotify
	mov	eax, [rax.NMLISTVIEW.iSubItem]

	mov	rcx, [r15.CLASS_LIST.unSort]
	cmp	rcx, rax
	je	listChgDir

	mov	[r15.CLASS_LIST.unSort], rax
	jmp	listResort

	; -- change direction --

listChgDir:	xor	[r15.CLASS_LIST.fSortDir], 1

	; -- resort list --

listResort:	mov	rcx, pxNotify
	lea	r9, cbSort
	mov	r8, r15
	mov	edx, LVM_SORTITEMSEX
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	jmp	listDone

	; -- column width changed --

listChange:	mov	rax, pxNotify
	mov	rax, [rax.NMHEADER.pitem]
	test	rax, rax
	jz	listDone

	test	[rax.HDITEM.lmask], HDI_WIDTH
	jz	listDone

	; -- store width --

	mov	eax, [rax.HDITEM.cxy]
	mov	unWidth, rax

	; -- get correct column --

	mov	rcx, [r15.CLASS_LIST.unMode]
	mov	rax, pxNotify
	mov	eax, [rax.NMHEADER.iItem]

	cmp	rax, 0
	je	listColName
	cmp	rax, 1
	je	listOne
	cmp	rax, 2
	je	listTwo
	cmp	rax, 3
	je	listColDate

	jmp	listDone

	; -- clicked on list two --

listTwo:	test	rcx, LIST_SIZE
	jz	listTwoOth
	test	rcx, LIST_TYPE
	jnz	listColType
	test	rcx, LIST_DATE
	jnz	listColDate

	jmp	listDone

listTwoOth:	test	rcx, LIST_DATE
	jnz	listColDate
	jmp	listDone

	; -- clicked on list one --

listOne:	test	rcx, LIST_SIZE
	jnz	listColSize
	test	rcx, LIST_TYPE
	jnz	listColType
	test	rcx, LIST_DATE
	jnz	listColDate

	jmp	listDone

	; -- clicked on date column --

listColDate:	mov	rcx, unWidth
	mov	[r15.CLASS_LIST.unCwDate], rcx
	mov	idConfig, IDS_CFG_LISTDATECOL
	jmp	listSave

	; -- clicked on type column --

listColType:	mov	rcx, unWidth
	mov	[r15.CLASS_LIST.unCwType], rcx
	mov	idConfig, IDS_CFG_LISTTYPECOL
	jmp	listSave

	; -- clicked on size column --

listColSize:	mov	rcx, unWidth
	mov	[r15.CLASS_LIST.unCwSize], rcx
	mov	idConfig, IDS_CFG_LISTSIZECOL
	jmp	listSave

	; -- clicked on name column --

listColName:	mov	rcx, unWidth
	mov	[r15.CLASS_LIST.unCwName], rcx
	mov	idConfig, IDS_CFG_LISTNAMECOL
	jmp	listSave

	; -- save to registry --

listSave:	mov	r9, rcx
	mov	r8, idConfig
	lea	rdx, [r15.CLASS_LIST.txSection]
	mov	rcx, [r15.CLASS_LIST.pxApp]
	mov	rcx, [rcx.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- all done --

listDone:	xor	rax, rax

	add	rsp, 32
	add	rsp, 3 * 8
	
	pop	r15
	pop	rbp

	ret	0
	
	align	4

listHandleNotify	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle relevant list events
; last update:	2000-04-14 - Scholz - created
;	2013-02-21 - Deutsch - x64 translation
; parameters:	result wndprcList (hwndList, unMessage, wParam, lParam)
;	[in] hwndList .. list window
;	[in] unMessage .. message to handle
;	[in] wParam .. message parameter
;	[in] lParam .. message parameter
; returns:	depending on message
;------------------------------------------------------------------------------------------------------------------------------------------

wndprcList	PROC	FRAME
	LOCAL	hwndList:QWORD	; list control window
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 8
	sub	rsp, 48
	.allocstack	48 + 4 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	hwndList, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- check for my messages --

	mov	eax, unMessage
	cmp	eax, WM_LBUTTONDOWN
	je	listLeftDown
	cmp	eax, WM_RBUTTONDOWN
	je	listLeftDown
	cmp	eax, WM_LBUTTONDBLCLK
	je	listLeftDouble
	cmp	eax, WM_KEYDOWN
	je	listChar
	cmp	eax, WM_CHAR
	je	listChar
	cmp	eax, WM_DEADCHAR
	je	listChar

	jmp	listBack

	; -- handle left down --

listLeftDown:	mov	edx, GWLP_USERDATA
	mov	rcx, hwndList
	call	GetWindowLongPtr
	test	rax, rax
	jz	listBack

	mov	r15, rax

	mov	rdx, [r15.CLASS_LIST.idList]
	mov	rcx, [r15.CLASS_LIST.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetActive]

	jmp	listBack

	; -- handle double click --

listLeftDouble:	mov	edx, GWLP_USERDATA
	mov	rcx, hwndList
	call	GetWindowLongPtr
	test	rax, rax
	jz	listBack

	mov	r15, rax

	mov	rdx, [r15.CLASS_LIST.idList]
	mov	rcx, [r15.CLASS_LIST.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetActive]

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r15.CLASS_LIST.pxApp]
	lea	r8, cbDoubleClick
	mov	rdx, LIST_ACTUAL
	mov	rcx, [r15.CLASS_LIST.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]

	jmp	listBack


	; -- pipe keyboard messages to main window --

listChar:	mov	rcx, hwndList
	call	GetParent

	mov	r9, lParam
	mov	r8, wParam
	mov	edx, unMessage
	mov	rcx, rax
	call	SendMessage

	; maybe we should care here about used keys

	jmp	listBack

	; -- back to original proc --

listBack:	mov	edx, GCLP_WNDPROC
	mov	rcx, hwndList
	call	GetClassLongPtr

	mov	rcx, lParam
	mov	[rsp + 32], rcx
	mov	r9, wParam
	mov	r8d, unMessage
	mov	rdx, hwndList
	mov	rcx, rax
	call	CallWindowProc

	jmp	listExit

listZero:	xor	rax, rax

listExit:	add	rsp, 48
	add	rsp, 4 * 8 + 8

	pop	r15
	pop	rbp

	ret	0

	align	4

wndprcList	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle double click - execute file or dive into directory
; last update:	2002-12-30 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError cbDoubleClick (ptxEntry, pxFind, unMode, unDepth, pxApp)
;	[in] ptxEntry .. name of clicked item
;	[in] pxFind .. windows information about item
;	[in] unMode .. enumeration mode
;	[in] unDepth .. recursion depth
;	[in] pxApp .. main application
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbDoubleClick	PROC	FRAME
	LOCAL	ptxEntry:QWORD	; list entry
	LOCAL	pxFind:QWORD	; file information
	LOCAL	unMode:QWORD	; callback operation mode
	LOCAL	txOperation [64]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * 64
	sub	rsp, 48
	.allocstack	48 + 3 * 8 + 2 * 64
	.endprolog

	; -- get parameter --

	mov	ptxEntry, rcx
	mov	pxFind, rdx
	mov	unMode, r8
	mov	r12, [rbp + 3 * 8 + 32]

	; -- decide on mode --

	mov	rax, unMode
	cmp	rax, PROC_DIRUP
	je	cdcDone
	cmp	rax, PROC_DIRDOWN
	je	cdcDir
	cmp	rax, PROC_FILE
	je	cdcFile

	jmp	cdcDone

	; -- file clicked --

cdcFile:	lea	r9, txOperation
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_SHELLOPEN
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	dword ptr [rsp + 40], SW_SHOWNORMAL
	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8, ptxEntry
	lea	rdx, txOperation
	mov	ecx, HWND_DESKTOP
	call	ShellExecute
	jmp	cdcDone

	; -- directory clicked --

cdcDir:	mov	rdx, ptxEntry
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetPath]

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

cdcDone:	mov	rax, ERROR_CANCELLED 

	add	rsp, 48
	add	rsp, 3 * 8 + 2 * 64

	pop	r12
	pop	rbp

	ret	0

	align	4

cbDoubleClick	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	directory enumeration callback
;	add a single line / item to listview
; last update:	2002-12-29 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cbInsert (ptxFile, pxFind, unMode, unDepth, pxList)
;	[in] ptxFile .. name of clicked item
;	[in] pxFind .. windows information about item
;	[in] unMode .. enumeration mode
;	[in] unDepth .. recursion depth
;	[in] pxList .. current list
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbInsert	PROC	FRAME
	LOCAL	ptxFile:QWORD	; current file
	LOCAL	pxFind:QWORD	; file information
	LOCAL	unMode:QWORD	; current operation mode
	LOCAL	unDepth:QWORD	; recursion depth
	LOCAL	dqSize:QWORD	; file size
	LOCAL	xItem:LVITEM	; new list item
	LOCAL	xInfo:SHFILEINFO	; file information (icon)
	LOCAL	xTime:SYSTEMTIME	; file time information
	LOCAL	txBuffer [64]:WORD	; file size in ascii

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 5 * 8 + sizeof LVITEM + sizeof SHFILEINFO + sizeof SYSTEMTIME + 2 * 64 + 8
	sub	rsp, 64
	.allocstack	64 + 5 * 8 + sizeof LVITEM + sizeof SHFILEINFO + sizeof SYSTEMTIME + 2 * 64 + 8
	.endprolog

	; -- get parameter --

	mov	ptxFile, rcx
	mov	pxFind, rdx
	mov	unMode, r8
	mov	unDepth, r9
	mov	r14, [rbp + 4 * 8 + 32]
	mov	r15, [r14.LISTFILL_DATA.pxList]

	; -- check if self --

	mov	rax, unMode
	cmp	rax, PROC_DIRUP
	je	listDone
	cmp	rax, PROC_DIRDOWN
	je	listDir
	cmp	rax, PROC_FILE
	je	listFile
	jmp	listDone

	; -- skip initial directory --

listDir:	mov	rax, unDepth
	cmp	rax, 0
	je	listDone

	; -- handle names --

listFile:	mov	edx, 0
	mov	rcx, [r15.CLASS_LIST.hevStop]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	je	listCancel

	; -- set file icon --

	mov	edx, sizeof LVITEM
	lea	rcx, xItem
	call	RtlZeroMemory

	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SYMBOL
	jz	listName

	mov	dword ptr [rsp + 32], SHGFI_SYSICONINDEX OR SHGFI_SMALLICON
	mov	r9d, sizeof SHFILEINFO
	lea	r8, xInfo
	mov	edx, 0
	mov	rcx, ptxFile
	call	SHGetFileInfo

	mov	eax, xInfo.SHFILEINFO.iIcon

	or	xItem.LVITEM.lmask, LVIF_IMAGE
	mov	xItem.LVITEM.iImage, eax

	; -- set file name, strip name from path --

listName:	mov	rcx, ptxFile
	call	lstrlen

	mov	rcx, ptxFile

listStrip:	cmp	word ptr [rcx + 2 * rax], "\"
	je	listStripped

	dec	rax
	jne	listStrip

listStripped:	lea	rcx, [rcx + 2 * rax + 2]
	mov	xItem.LVITEM.pszText, rcx

	or	xItem.LVITEM.lmask, LVIF_TEXT OR LVIF_PARAM

	mov	rax, unMode
	cmp	rax, PROC_DIRDOWN
	je	listTypeDir

	mov	xItem.LVITEM.lParam, TYPE_FILE
	jmp	listSetParam

listTypeDir:	mov	xItem.LVITEM.lParam, TYPE_DIR

listSetParam:	mov	xItem.LVITEM.iItem, 0

	lea	r9, xItem
	mov	r8d, 0
	mov	edx, LVM_INSERTITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	xItem.LVITEM.iItem, eax

	; -- set file size --

	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SIZE
	je	listType

	; -- skip directories --

	mov	rdx, pxFind
	test	[rdx.WIN32_FIND_DATA.dwFileAttributes], FILE_ATTRIBUTE_DIRECTORY
	jnz	listDirSize

	; -- convert file size to ascii --

	mov	eax, [rdx.WIN32_FIND_DATA.nFileSizeLow]
	mov	ecx, [rdx.WIN32_FIND_DATA.nFileSizeHigh]
	mov	dword ptr dqSize + 0, eax
	mov	dword ptr dqSize + 4, ecx

	lea	rdx, txBuffer
	lea	rcx, dqSize
	call	i64toa

	; -- insert file size --

	lea	rax, txBuffer
	jmp	listSize

listDirSize:	lea	rax, [r14.LISTFILL_DATA.txDirTag]

listSize:	lea	r9, xItem
	mov	[r9.LVITEM.lmask], LVIF_TEXT
	mov	[r9.LVITEM.pszText], rax
	inc	[r9.LVITEM.iSubItem]

	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- set file type --

listType:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_TYPE
	je	listDate

	mov	dword ptr [rsp + 32], SHGFI_TYPENAME
	mov	r9d, sizeof SHFILEINFO
	lea	r8, xInfo
	mov	edx, 0
	mov	rcx, ptxFile
	call	SHGetFileInfo

	lea	r9, xItem
	lea	rax, xInfo
	lea	rax, [rax.SHFILEINFO.szTypeName]

	mov	[r9.LVITEM.lmask], LVIF_TEXT
	mov	[r9.LVITEM.pszText], rax
	inc	[r9.LVITEM.iSubItem]

	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- set file date --

listDate:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_DATE
	je	listUpdate

	mov	rax, pxFind

	lea	rdx, xTime
	lea	rcx, [rax.WIN32_FIND_DATA.ftCreationTime]
	call	FileTimeToSystemTime

	mov	dword ptr [rsp + 40], 64 - 1
	lea	rax, txBuffer
	mov	[rsp + 32], rax
	lea	r9, [r14.LISTFILL_DATA.txFmtDate]
	lea	r8, xTime
	mov	edx, 0
	mov	ecx, LOCALE_USER_DEFAULT
	call	GetDateFormat

	lea	rcx, txBuffer
	lea	rcx, [rcx + 2 * rax - 2]
	mov	word ptr [rcx], " "
	add	rcx, 2

	mov	dword ptr [rsp + 40], 64 - 1
	mov	[rsp + 32], rcx
	lea	r9, [r14.LISTFILL_DATA.txFmtTime]
	lea	r8, xTime
	mov	edx, 0
	mov	ecx, LOCALE_USER_DEFAULT
	call	GetTimeFormat

	lea	r9, xItem
	lea	rax, txBuffer
	mov	[r9.LVITEM.lmask], LVIF_TEXT
	mov	[r9.LVITEM.pszText], rax
	inc	[r9.LVITEM.iSubItem]

	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; fill in more column types ...

	; -- update window recently --

listUpdate:	inc	[r14.LISTFILL_DATA.unCount]

	mov	rax, [r14.LISTFILL_DATA.unCount]
	cqo
	mov	rcx, LIST_FILL_REFRESH
	idiv	rcx
	test	rdx, rdx
	jnz	listDone

	; -- sort before update --

	lea	r9, cbSort
	mov	r8, r15
	mov	edx, LVM_SORTITEMSEX
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- update now --

	mov	r9d, 0
	mov	r8d, TRUE
	mov	edx, WM_SETREDRAW
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	InvalidateRect

	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	UpdateWindow

	mov	r9d, 0
	mov	r8d, FALSE
	mov	edx, WM_SETREDRAW
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	; -- exit cases --

listDone:	xor	rax, rax
	jmp	listExit

listCancel:	mov	rax, ERROR_CANCELLED

listExit:	add	rsp, 64
	add	rsp, 5 * 8 + sizeof LVITEM + sizeof SHFILEINFO + sizeof SYSTEMTIME + 2 * 64 + 8

	pop	r15
	pop	r14
	pop	rbp

	ret	0

	align	4

cbInsert	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	list sort callback
; last update:	2002-12-29 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cbSort (hitemOne, hitemTwo, pxThis)
;	[in] hitemOne .. compare item 1
;	[in] hitemTwo .. compare item 2
;	[in] pxList .. current list
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbSort	PROC	FRAME
	LOCAL	hitemOne:QWORD	; first item to compare
	LOCAL	hitemTwo:QWORD	; second item to compare
	LOCAL	unTypeOne:QWORD	; type of item - file or directory
	LOCAL	unTypeTwo:QWORD	; type of item - file or directory
	LOCAL	unSize1:QWORD	; file size of item
	LOCAL	unSize2:QWORD	; file size of item
	LOCAL	xItem:LVITEM	; list item
	LOCAL	txOne [DEF_PATH_LENGTH]:WORD
	LOCAL	txTwo [DEF_PATH_LENGTH]:WORD
	LOCAL	txSize [64]:WORD

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 6 * 8 + sizeof LVITEM + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + 2 * 64
	sub	rsp, 32
	.allocstack	32 + 6 * 8 + sizeof LVITEM + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + 2 * 64
	.endprolog

	; -- get parameter --

	mov	hitemOne, rcx
	mov	hitemTwo, rdx
	mov	r15, r8

	; -- retreive first item data --

	lea	r9, xItem
	lea	rax, txOne
	mov	rcx, hitemOne
	mov	[r9.LVITEM.iSubItem], 0
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax
	mov	[r9.LVITEM.cchTextMax], DEF_PATH_LENGTH - 1
	mov	[r9.LVITEM.lmask], LVIF_TEXT OR LVIF_PARAM

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	r9, xItem
	mov	rax, [r9.LVITEM.lParam]
	mov	unTypeOne, rax

	; -- retreive second item --

	lea	rax, txTwo
	mov	rcx, hitemTwo
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	r9, xItem
	mov	rax, [r9.LVITEM.lParam]
	mov	unTypeTwo, rax

	; -- sort by column mode --

	mov	rax, [r15.CLASS_LIST.unSort]
	cmp	rax, 0
	je	listName
	cmp	rax, 1
	je	listSecond
	cmp	rax, 2
	je	listThird
	cmp	rax, 3
	je	listFourth
	jmp	listSame

	; -- sort by name, sort folders on top --

listName:	mov	rax, unTypeOne
	mov	rcx, unTypeTwo

	cmp	rax, rcx
	je	listNameSort
	cmp	rax, TYPE_DIR
	je	listSmaller
	cmp	rcx, TYPE_DIR
	je	listGreater

listNameSort:	mov	rax, [r15.CLASS_LIST.fSortDir]
	cmp	rax, TRUE
	je	listNameDes

	; -- sort by name ascending --

	lea	rdx, txTwo
	lea	rcx, txOne
	call	lstrcmpi
	jmp	listExit

	; -- sort by name ascending --

listNameDes:	lea	rdx, txOne
	lea	rcx, txTwo
	call	lstrcmpi
	jmp	listExit

	; -- check second column --

listSecond:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SIZE
	jnz	listSize
	test	rax, LIST_TYPE
	jnz	listType
	test	rax, LIST_DATE
	jnz	listDate

	; -- fill in more --

	jmp	listSame

	; -- third column clicked --

listThird:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SIZE
	jz	listTrdOther
	test	rax, LIST_TYPE
	jnz	listType
	test	rax, LIST_DATE
	jnz	listDate

	; -- fill in more --

	jmp	listSame

listTrdOther:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_DATE
	jnz	listDate

	; -- fill in more --

	jmp	listSame

	; -- fourth column --

listFourth:	mov	rax, [r15.CLASS_LIST.unMode]
	test	rax, LIST_SIZE
	jz	listSame
	test	rax, LIST_TYPE
	jz	listSame
	test	rax, LIST_DATE
	jnz	listDate

	; -- fill in more --

	jmp	listSame

	; -- sort by size, sort folders on top --

listSize:	mov	rax, unTypeOne
	mov	rcx, unTypeTwo

	cmp	rax, TYPE_DIR
	je	listSmaller
	cmp	rcx, TYPE_DIR
	je	listGreater

	; -- get sub items with size, get number from text --

	lea	r9, xItem
	lea	rax, txSize
	mov	rcx, hitemOne
	mov	[r9.LVITEM.iSubItem], 1
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax
	mov	[r9.LVITEM.cchTextMax], 64 - 1
	mov	[r9.LVITEM.lmask], LVIF_TEXT

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	rdx, unSize1
	lea	rcx, txSize
	call	a64toi

	lea	r9, xItem
	mov	rcx, hitemTwo
	mov	[r9.LVITEM.iItem], ecx

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	rdx, unSize2
	lea	rcx, txSize
	call	a64toi

	; -- compare sizes --

	mov	rax, [r15.CLASS_LIST.fSortDir]
	cmp	rax, TRUE
	je	listSizeDes

	; -- compare ascending --

	mov	rax, unSize1
	cmp	rax, unSize2
	jl	listSmaller
	jg	listGreater
	jmp	listSame

	; -- compare descending --

listSizeDes:	mov	rax, unSize1
	cmp	rax, unSize2
	jl	listGreater
	jg	listSmaller
	jmp	listSame

	; -- sort by type --

listType:	lea	r9, xItem
	lea	rax, txOne
	mov	rcx, hitemOne
	mov	rdx, [r15.CLASS_LIST.unSort]

	mov	[r9.LVITEM.iSubItem], edx
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax
	mov	[r9.LVITEM.cchTextMax], DEF_PATH_LENGTH - 1
	mov	[r9.LVITEM.lmask], LVIF_TEXT

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	r9, xItem
	lea	rax, txTwo
	mov	rcx, hitemTwo
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	jmp	listNameSort

	; -- sort by date --

listDate:	lea	r9, xItem
	lea	rax, txOne
	mov	rcx, hitemOne
	mov	rdx, [r15.CLASS_LIST.unSort]

	mov	[r9.LVITEM.iSubItem], edx
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax
	mov	[r9.LVITEM.cchTextMax], DEF_PATH_LENGTH - 1
	mov	[r9.LVITEM.lmask], LVIF_TEXT

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	lea	r9, xItem
	lea	rax, txTwo
	mov	rcx, hitemTwo
	mov	[r9.LVITEM.iItem], ecx
	mov	[r9.LVITEM.pszText], rax

	mov	r8d, 0
	mov	edx, LVM_GETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage
	jmp	listNameSort

	; -- entries --

listGreater:	mov	rax, 1
	jmp	listExit

listSmaller:	mov	rax, -1
	jmp	listExit

listSame:	xor	rax, rax

listExit:	add	rsp, 32
	add	rsp, 6 * 8 + sizeof LVITEM + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + 2 * 64

	pop	r15
	pop	rbp

	ret	0

	align	4

cbSort	ENDP

	END
