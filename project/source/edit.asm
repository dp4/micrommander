;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - path edit class
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

	include	app.inc
	include	config.inc
	include	edit.inc
	include	list.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new path object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	pxPath pathNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

pathNew	PROC	FRAME

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
	jz	pathExit

	mov	r8, sizeof CLASS_PATH
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	pathExit

	lea	rcx, [rax.CLASS_PATH.xInterface]
	mov	[rax.CLASS_PATH.vtableThis], rcx

	lea	rdx, pathInit
	mov	[rcx.CLASS_PATH_IFACE.pfnInit], rdx
	lea	rdx, pathLoadConfig
	mov	[rcx.CLASS_PATH_IFACE.pfnLoadConfig], rdx
	lea	rdx, pathResize
	mov	[rcx.CLASS_PATH_IFACE.pfnResize], rdx
	lea	rdx, pathUpdate
	mov	[rcx.CLASS_PATH_IFACE.pfnUpdate], rdx
	lea	rdx, pathRelease
	mov	[rcx.CLASS_PATH_IFACE.pfnRelease], rdx

pathExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

pathNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize path edit control
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError InitEdit (idPath, pxApp)
;	[in] idPath .. child window ID - left or right
;	[in] pxApp .. main application
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

pathInit	PROC	FRAME
	LOCAL	idPath:QWORD	; path control child ID
	LOCAL	hfontEdit:QWORD	; edit font
	LOCAL	hfontOrg:QWORD	; old font
	LOCAL	hdcEdit:QWORD	; edit device
	LOCAL	txText [4]:WORD	; sample text for text size
	LOCAL	txClass [16]:WORD	; edit window class name
	LOCAL	sizeText:SIZEL	; text size

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * 4 + 2 * 16 + sizeof SIZEL
	sub	rsp, 96
	.allocstack	96 + 4 * 8 + 2 * 4 + 2 * 16 + sizeof SIZEL
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	idPath, rdx
	mov	r12, r8

	; -- load edit configuration

	mov	[r15.CLASS_PATH.idPath], rdx
	mov	[r15.CLASS_PATH.pxApp], r12

	mov	rdx, idPath
	mov	rcx, r15
	mov	rax, [r15.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnLoadConfig]

	; -- create edit window --

	lea	r9, txClass
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_EDITCLASS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	qword ptr [rsp + 88], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rsp + 80], rax
	mov	rax, idPath
	mov	[rsp + 72], rax
	mov	rax, [r12.CLASS_APP.hwndApp]
	mov	[rsp + 64], eax
	mov	eax, CW_USEDEFAULT
	mov	[rsp + 56], eax
	mov	[rsp + 48], eax
	mov	[rsp + 40], eax
	mov	[rsp + 32], eax
	mov	r9d, WS_CHILD OR WS_VISIBLE OR ES_LEFT OR ES_AUTOHSCROLL
	mov	r8, 0
	lea	rdx, txClass
	mov	ecx, WS_EX_STATICEDGE
	call	CreateWindowEx
	test	rax, rax
	jz	pathFail

	mov	[r15.CLASS_PATH.hwndEdit], rax

	mov	r8, r15
	mov	edx, GWLP_USERDATA
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	SetWindowLongPtr

	lea	r8, wndprcEdit
	mov	edx, GWLP_WNDPROC
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	SetWindowLongPtr

	; -- setup font --

	lea	r8, [r15.CLASS_PATH.hfontEdit]
	lea	rdx, [r15.CLASS_PATH.xParams]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnCreateViewFont]

	mov	r9d, 0
	mov	r8, hfontEdit
	mov	edx, WM_SETFONT
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	SendMessage

	; -- get height --

	lea	rcx, txText
	mov	word ptr [rcx + 0], 69h
	mov	word ptr [rcx + 2], 68h
	mov	word ptr [rcx + 4], 67h
	mov	word ptr [rcx + 6], 66h
	mov	word ptr [rcx + 8], 0

	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	GetDC
	mov	hdcEdit, rax

	mov	rdx, hfontEdit
	mov	rcx, hdcEdit
	call	SelectObject
	mov	hfontOrg, rax

	lea	r9, sizeText
	mov	r8d, 4
	lea	rdx, txText
	mov	rcx, hdcEdit
	call	GetTextExtentPoint32

	mov	rdx, hfontOrg
	mov	rcx, hdcEdit
	call	SelectObject

	mov	rdx, hdcEdit
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	ReleaseDC

	xor	rax, rax
	mov	eax, sizeText.SIZEL.scy
	add	rax, 2 * EDIT_BORDER
	mov	[r12.CLASS_APP.unEditHeight], rax

	xor	rax, rax
	jmp	pathExit

pathFail:	call	GetLastError

pathExit:	add	rsp, 96
	add	rsp, 4 * 8 + 2 * 4 + 2 * 16 + sizeof SIZEL

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

pathInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release path object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError pathRelease ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

pathRelease	PROC	FRAME

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

	mov	r8, 0
	mov	edx, GWLP_USERDATA
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	SetWindowLongPtr

	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	DestroyWindow

	mov	rcx, [r15.CLASS_PATH.hfontEdit]
	call	DeleteObject

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

pathRelease	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	resize edit
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError pathResize (prcSize)
;	[in] prcSize .. new size rectangle
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

pathResize	PROC	FRAME

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

	; -- move window --

	mov	dword ptr [rsp + 40], TRUE
	mov	eax, [rdx.RECT.bottom]
	mov	[rsp + 32], eax
	mov	r9d, [rdx.RECT.right]
	mov	r8d, [rdx.RECT.top]
	mov	edx, [rdx.RECT.left]
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	MoveWindow

	xor	rax, rax

	add	rsp, 48
	add	rsp, 8

	pop	r15
	pop	rbp

	ret	0

	align	4

pathResize	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	loads path configuration from config file - if none, create new
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError pathLoadConfig (idPath)
;	[in] idPath .. which path - left or right
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

pathLoadConfig	PROC	FRAME
	LOCAL	idPath:QWORD	; edit id (left/right)
	LOCAL	txSection [64]:WORD	; section name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * 64 + 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8 + 2 * 64 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	idPath, rdx
	mov	r12, [r15.CLASS_PATH.pxApp]

	; -- get section name --

	mov	rcx, idPath
	cmp	rcx, IDC_LEFTPATH
	je	pathLeft

	mov	rdx, IDS_CFG_RIGHTEDIT
	jmp	pathLoad

pathLeft:	mov	rdx, IDS_CFG_LEFTEDIT

pathLoad:	lea	r9, txSection
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	; -- load edit view parameter --

	lea	rax, [r15.CLASS_PATH.xParams]
	mov	[rax.VIEW_PARAM.unBgColor], DEF_BGCOLOR
	mov	[rax.VIEW_PARAM.unFgColor], DEF_FGCOLOR
	mov	[rax.VIEW_PARAM.unFontSize], DEF_EDITSIZE
	mov	[rax.VIEW_PARAM.unItalic], FALSE
	mov	[rax.VIEW_PARAM.unWeight], FW_NORMAL

	lea	r9, [rax.VIEW_PARAM.txFontName]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DEF_EDITFONT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, [r15.CLASS_PATH.xParams]
	lea	rdx, txSection
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigView]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8 + 2 * 64 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

pathLoadConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	update path control (for color change)
; last update:	2002-12-27 - Scholz - created
;	2013-02-21 - Deutsch - x64 translation
; parameters:	unError pathUpdate ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

pathUpdate	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 32
	.allocstack	32 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx

	; -- update window --

	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	InvalidateRect

	mov	rcx, [r15.CLASS_PATH.hwndEdit]
	call	UpdateWindow

	xor	rax, rax

	add	rsp, 32
	add	rsp, 8

	pop	r15
	pop	rbp

	ret	0

	align	4

pathUpdate	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle relevant edit events
; last update:	2000-04-14 - Scholz - created
;	2013-02-21 - Deutsch - x64 translation
; parameters:	result wndprcEdit (hwndEdit, unMsg, wParam, lParam)
;	[in] hwndEdit .. path edit window
;	[in] unMessage .. message to handle
;	[in] wParam .. message parameter
;	[in] lParam .. message parameter
; returns:	depending on message
;------------------------------------------------------------------------------------------------------------------------------------------

wndprcEdit	PROC	FRAME
	LOCAL	hwndEdit:QWORD	; edit control window
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	txPath [DEF_PATH_LENGTH]:WORD	; new path

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + 8
	sub	rsp, 48
	.allocstack	48 + 4 * 8 + 2 * DEF_PATH_LENGTH + 8
	.endprolog

	; -- get parameter --

	mov	hwndEdit, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- get object --

	mov	edx, GWLP_USERDATA
	mov	rcx, hwndEdit
	call	GetWindowLongPtr
	test	rax, rax
	jz	pathBack

	mov	r15, rax

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_SETFOCUS
	je	pathFocus
	cmp	eax, WM_KEYDOWN
	je	pathKeyDown

	jmp	pathBack

	; -- set focus event --

pathFocus:	mov	rdx, [r15.CLASS_PATH.idPath]
	sub	rdx, 2
	mov	rcx, [r15.CLASS_PATH.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetActive]

	jmp	pathBack

	; -- key down event --

pathKeyDown:	mov	rax, wParam
	cmp	ax, VK_RETURN
	je	pathKeyReturn

	jmp	pathBack

	; -- use input on return key --

pathKeyReturn:	lea	r9, txPath
	mov	r8, DEF_PATH_LENGTH - 1
	mov	edx, WM_GETTEXT
	mov	rcx, hwndEdit
	call	SendMessage

	lea	rdx, txPath
	mov	rcx, [r15.CLASS_PATH.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetPath]

	mov	rdx, LIST_ACTUAL
	mov	rcx, [r15.CLASS_PATH.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	mov	rcx, hwndEdit
	call	GetParent

	mov	rcx, rax
	call	SetFocus

	jmp	pathZero

	; -- pipe to original proc --

pathBack:	mov	edx, GCLP_WNDPROC
	mov	rcx, hwndEdit
	call	GetClassLongPtr

	mov	rcx, lParam
	mov	[rsp + 32], rcx
	mov	r9, wParam
	mov	r8d, unMessage
	mov	rdx, hwndEdit
	mov	rcx, rax
	call	CallWindowProc

	jmp	pathExit

pathZero:	xor	rax, rax

pathExit:	add	rsp, 48
	add	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + 8

	pop	r15
	pop	rbp

	ret	0

	align	4

wndprcEdit	ENDP

	END
