;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - button class
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

	include	app.inc
	include	button.inc
	include	command.inc
	include	config.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new button object
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	pxButton buttonNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

buttonNew	PROC	FRAME

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
	jz	btnExit

	mov	r8, sizeof CLASS_BUTTON
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	btnExit

	lea	rcx, [rax.CLASS_BUTTON.xInterface]
	mov	[rax.CLASS_BUTTON.vtableThis], rcx

	lea	rdx, btnInit
	mov	[rcx.CLASS_BUTTON_IFACE.pfnInit], rdx
	lea	rdx, btnLoadConfig
	mov	[rcx.CLASS_BUTTON_IFACE.pfnLoadConfig], rdx
	lea	rdx, btnSaveConfig
	mov	[rcx.CLASS_BUTTON_IFACE.pfnSaveConfig], rdx
	lea	rdx, btnGetRect
	mov	[rcx.CLASS_BUTTON_IFACE.pfnGetRect], rdx
	lea	rdx, btnRender
	mov	[rcx.CLASS_BUTTON_IFACE.pfnRender], rdx

btnExit:	add	rsp, 32

	pop	rbp

	ret	0

	align	4

buttonNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize button object
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError btnInit (unCol, unRow, pxApp)
;	[in] unCol .. button matrix column
;	[in] unRow .. button matrix row
;	[in] pxApp .. main app
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

btnInit	PROC	FRAME
	LOCAL	unCol:QWORD	; button position horizontal
	LOCAL	unRow:QWORD	; button position vertical
	LOCAL	txMask [64]:WORD	; button value mask

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 64
	sub	rsp, 32
	.allocstack	32 + 2 * 8 + 2 * 64
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	unCol, rdx
	mov	unRow, r8
	mov	r12, r9

	mov	[r15.CLASS_BUTTON.unCol], rdx
	mov	[r15.CLASS_BUTTON.unRow], r8
	mov	[r15.CLASS_BUTTON.pxApp], r12

	; -- get button configuration section --

	lea	r9, txMask
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_CFG_BUTTONS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	r9, unRow
	mov	r8, unCol
	lea	rdx, txMask
	lea	rcx, [r15.CLASS_BUTTON.txSection]
	call	wsprintf

	; -- load buttons configuration --

	mov	rcx, r15
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnLoadConfig]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 2 * 8 + 2 * 64

	pop	r15
	pop	r12
	pop	rbp

	ret	0
	
	align	4

btnInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	load button configuration from INI file
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError btnLoadConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

btnLoadConfig	PROC	FRAME
	LOCAL	txVoid [4]:WORD	; default void text

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 4 + 8
	sub	rsp, 48
	.allocstack	48 + 2 * 4 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_BUTTON.pxApp]

	mov	word ptr txVoid, 0

	; -- load button command --

	lea	rax, [r15.CLASS_BUTTON.unCmd]
	mov	[rsp + 32], rax
	mov	r9, CMD_EMPTY
	mov	r8, IDS_CFG_BUTTONCMD
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load button text --

	lea	rax, [r15.CLASS_BUTTON.txText]
	mov	[rsp + 32], rax
	lea	r9, txVoid
	mov	r8, IDS_CFG_BUTTONTEXT
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigText]

	; -- load button text --

	lea	rax, [r15.CLASS_BUTTON.txParam]
	mov	[rsp + 32], rax
	lea	r9, txVoid
	mov	r8, IDS_CFG_BUTTONPARAM
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigText]

	; -- load button view parameter --

	lea	rax, [r15.CLASS_BUTTON.xParams]
	mov	[rax.VIEW_PARAM.unBgColor], DEF_BUTTONBACK
	mov	[rax.VIEW_PARAM.unFgColor], DEF_BUTTONFORE
	mov	[rax.VIEW_PARAM.unFontSize], DEF_BUTTONSIZE
	mov	[rax.VIEW_PARAM.unItalic], FALSE
	mov	[rax.VIEW_PARAM.unWeight], FW_NORMAL

	lea	r9, [rax.VIEW_PARAM.txFontName]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DEF_BTNFONT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, [r15.CLASS_BUTTON.xParams]
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigView]

	; -- load button shortcut --

	lea	rax, [r15.CLASS_BUTTON.unShortcut]
	mov	[rsp + 32], rax
	mov	r9, 0
	mov	r8, IDS_CFG_BUTTONSCUT
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	xor	rax, rax

	add	rsp, 48
	add	rsp, 2 * 4 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

btnLoadConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	save button configuration
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError btnSaveConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

btnSaveConfig	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	.allocstack	32
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_BUTTON.pxApp]

	; -- save button command --

	mov	r9, [r15.CLASS_BUTTON.unCmd]
	mov	r8, IDS_CFG_BUTTONCMD
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- save button text --

	lea	r9, [r15.CLASS_BUTTON.txText]
	mov	r8, IDS_CFG_BUTTONTEXT
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigText]

	; -- save button parameter --

	lea	r9, [r15.CLASS_BUTTON.txParam]
	mov	r8, IDS_CFG_BUTTONPARAM
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigText]

	; -- save button view parameter --

	lea	r8, [r15.CLASS_BUTTON.xParams]
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigView]

	; -- save button shortcut --

	mov	r9, [r15.CLASS_BUTTON.unShortcut]
	mov	r8, IDS_CFG_BUTTONSCUT
	lea	rdx, [r15.CLASS_BUTTON.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	xor	rax, rax

	add	rsp, 32

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

btnSaveConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	retreive buttons rectangle by line and row
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError btnGetRect (prcButton)
;	[out] prcButton .. buttons rectangle
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

btnGetRect	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r10, rdx
	mov	r12, [r15.CLASS_BUTTON.pxApp]

	; -- get width --

	mov	rax, [r12.CLASS_APP.unBtnWidth]
	add	rax, DEF_BUTTON_GAP
	imul	[r15.CLASS_BUTTON.unCol]
	add	rax, DEF_BUTTON_GAP
	add	rax, DEF_CHILD_GAP
	mov	[r10.RECT.left], eax

	add	rax, [r12.CLASS_APP.unBtnWidth]
	mov	[r10.RECT.right], eax

	; -- get height --

	mov	rax, [r12.CLASS_APP.unBtnHeight]
	add	rax, DEF_BUTTON_GAP
	imul	[r15.CLASS_BUTTON.unRow]

	add	rax, [r12.CLASS_APP.unBtnTop]
	sub	rax, [r12.CLASS_APP.unBtnArea]
	sub	rax, [r12.CLASS_APP.unStHeight]
	sub	rax, DEF_BUTTON_GAP
	mov	[r10.RECT.top], eax

	add	rax, [r12.CLASS_APP.unBtnHeight]
	mov	[r10.RECT.bottom], eax

	xor	rax, rax

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

btnGetRect	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	draw single button
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError btnRender (hdcApp, unType, prcButton)
;	[in] hdcApp .. device context to render
;	[in] unType .. button draw type (pressed / unpressed)
;	[in] prcButton .. buttons rectangle to draw inside
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

btnRender	PROC	FRAME
	LOCAL	hdcApp:QWORD	; device to draw in
	LOCAL	unType:QWORD	; button type
	LOCAL	prcButton:QWORD	; button rectangle
	LOCAL	hfontBtn:QWORD	; buttons font
	LOCAL	hfontOld:QWORD	; original font
	LOCAL	hrgnClip:QWORD	; clipping region
	LOCAL	unLen:QWORD	; text length

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 7 * 8 + 8
	sub	rsp, 48
	.allocstack	48 + 7 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	hdcApp, rdx
	mov	unType, r8
	mov	r12, [r15.CLASS_BUTTON.pxApp]
	mov	rax, r9
	mov	prcButton, rax

	; -- draw button shape --

	mov	r9, unType
	mov	r8d, DFC_BUTTON
	mov	rdx, prcButton
	mov	rcx, hdcApp
	call	DrawFrameControl

	; -- prepare text --

	mov	edx, TRANSPARENT
	mov	rcx, hdcApp
	call	SetBkMode

	mov	edx, TA_CENTER OR TA_TOP
	mov	rcx, hdcApp
	call	SetTextAlign

	lea	r8, hfontBtn
	lea	rdx, [r15.CLASS_BUTTON.xParams]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnCreateViewFont]

	mov	rdx, hfontBtn
	mov	rcx, hdcApp
	call	SelectObject
	mov	hfontOld, rax

	mov	edx, dword ptr [r15.CLASS_BUTTON.xParams.VIEW_PARAM.unFgColor]
	mov	rcx, hdcApp
	call	SetTextColor

	; -- prepare clip region --

	mov	rax, prcButton
	mov	r9d, [rax.RECT.bottom]
	mov	r8d, [rax.RECT.right]
	mov	edx, [rax.RECT.top]
	mov	ecx, [rax.RECT.left]
	call	CreateRectRgn
	mov	hrgnClip, rax

	mov	rdx, hrgnClip
	mov	rcx, hdcApp
	call	SelectClipRgn

	mov	rcx, hrgnClip
	call	DeleteObject

	; -- draw text --

	lea	rcx, [r15.CLASS_BUTTON.txText]
	call	lstrlen
	mov	unLen, rax

	mov	rcx, prcButton

	mov	rax, unLen
	mov	[rsp + 32], rax
	lea	r9, [r15.CLASS_BUTTON.txText]
	mov	r8d, [rcx.RECT.top]
	add	r8d, 5
	mov	rdx, [r12.CLASS_APP.unBtnWidth]
	sar	rdx, 1
	add	edx, [rcx.RECT.left]
	mov	rcx, hdcApp
	call	TextOut

	mov	rdx, hfontOld
	mov	rcx, hdcApp
	call	SelectObject

	mov	rcx, hfontBtn
	call	DeleteObject

	mov	rdx, 0
	mov	rcx, hdcApp
	call	SelectClipRgn

	xor	rax, rax

dbtExit:	add	rsp, 48
	add	rsp, 7 * 8 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

btnRender	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for button setup dialog
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	fHandled dlgprcButton (hwndDlg, unMessage, wParam, lParam)
;	[in] hwndDlg .. dialog to handle
;	[in] unMessage .. message to handle
;	[in] wParam .. message parameter 1
;	[in] lParam .. message parameter 2
; returns:	true for handled, else zero
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcButton	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unLoop:QWORD	; loop counter
	LOCAL	unCount:QWORD	; list entries
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	txBuffer [2048]:WORD	; hint text
	LOCAL	xItem:COMBOBOXEXITEM	; list item

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 64
	sub	rsp, 4 * 8 + 2 * 2048 + sizeof COMBOBOXEXITEM + 8
	.allocstack	64 + 4 * 8 + 2 * 2048 + sizeof COMBOBOXEXITEM + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dpbInit
	cmp	eax, WM_COMMAND
	je	dpbCommand
	cmp	eax, WM_CLOSE
	je	dpbClose

	jmp	dpbZero

	; -- init dialog - set all strings --

dpbInit:	mov	r15, lParam
	mov	r12, [r15.CLASS_BUTTON.pxApp]

	mov	r8, r15
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	dword ptr [rsp + 32], 0
	mov	r9d, 32
	mov	r8d, EM_LIMITTEXT
	mov	edx, ID_BC_TEXT
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	dword ptr [rsp + 32], 0
	mov	r9d, 256
	mov	r8d, EM_LIMITTEXT
	mov	edx, ID_BC_PARAM
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	lea	r8, [r15.CLASS_BUTTON.txText]
	mov	edx, ID_BC_TEXT
	mov	rcx, hwndDlg
	call	SetDlgItemText

	lea	r8, [r15.CLASS_BUTTON.txParam]
	mov	edx, ID_BC_PARAM
	mov	rcx, hwndDlg
	call	SetDlgItemText

	; -- set parameter for buttons command --

	mov	rdx, [r15.CLASS_BUTTON.unCmd]
	add	rdx, IDS_CMD_BASE

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_BC_HINT
	mov	rcx, hwndDlg
	call	SetDlgItemText

	mov	dword ptr [rsp + 48], LR_DEFAULTCOLOR
	mov	dword ptr [rsp + 40], IMAGE_BITMAP
	mov	dword ptr [rsp + 32], CLR_DEFAULT
	mov	r9d, 64
	mov	r8d, 16
	mov	edx, IDB_CMDICONS
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	ImageList_LoadImage

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_SETIMAGELIST
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- init default section --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDCAT_DEFAULT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	lea	rcx, txBuffer

	mov	[rax.COMBOBOXEXITEM.lmask], CBEIF_IMAGE OR CBEIF_INDENT OR CBEIF_LPARAM OR CBEIF_TEXT OR CBEIF_SELECTEDIMAGE
	mov	[rax.COMBOBOXEXITEM.iItem], 0
	mov	[rax.COMBOBOXEXITEM.pszText], rcx
	mov	[rax.COMBOBOXEXITEM.iImage], 11
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 11
	mov	[rax.COMBOBOXEXITEM.iIndent], 0
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert null command --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_EMPTY
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 10
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 10
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert select all command --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_ALL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 4
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 4
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_ALL

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert select none command --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_NONE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 9
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 9
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_NONE

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert exit command --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_EXIT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 11
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 11
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EXIT

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert file category --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDCAT_FILES
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 1
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 1
	mov	[rax.COMBOBOXEXITEM.iIndent], 0
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert copy files --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_COPY
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 12
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 12
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_COPY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert move files --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_MOVE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 13
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 13
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_MOVE

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert rename files --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_RENAME
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 14
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 14
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_RENAME

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert delete files --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_DELETE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 15
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 15
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_DELETE

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert filesize --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_BYTE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 16
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 16
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_BYTE

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert folder category --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDCAT_FOLDERS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 0
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 0
	mov	[rax.COMBOBOXEXITEM.iIndent], 0
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert goto root --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_ROOT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 5
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 5
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_ROOT

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert parent folder --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_PARENT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 6
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 6
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_PARENT

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert change folder --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_CD
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 7
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 7
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_CD

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert make dir --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_MKDIR
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 8
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 8
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_MKDIR

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert drive category --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDCAT_DRIVES
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 17
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 17
	mov	[rax.COMBOBOXEXITEM.iIndent], 0
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert format drive --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_FORMAT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 18
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 18
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_FORMAT

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert external category --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDCAT_EXTERN
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 3
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 3
	mov	[rax.COMBOBOXEXITEM.iIndent], 0
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EMPTY

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- insert execute --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_EXECUTE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xItem
	inc	[rax.COMBOBOXEXITEM.iItem]
	mov	[rax.COMBOBOXEXITEM.iImage], 3
	mov	[rax.COMBOBOXEXITEM.iSelectedImage], 3
	mov	[rax.COMBOBOXEXITEM.iIndent], 1
	mov	[rax.COMBOBOXEXITEM.lParam], CMD_EXECUTE

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, CBEM_INSERTITEM
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- find command --

	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, CB_GETCOUNT
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	
	or	rax, 0FFFFFFFFh
	mov	unCount, rax

	mov	unLoop, 0

dpbInitLoop:	mov	dword ptr [rsp + 32], 0
	mov	r9, unLoop
	mov	r8d, CB_GETITEMDATA 
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	cmp	rax, [r15.CLASS_BUTTON.unCmd]
	je	dpbFound

	inc	unLoop
	mov	rax, unLoop
	cmp	rax, unCount
	jne	dpbInitLoop

	jmp	dpbInitDone

	; -- select current --

dpbFound:	mov	rax, unLoop
	cmp	rax, 0
	jne	dpbSelect

	inc	rax

dpbSelect:	mov	dword ptr [rsp + 32], 0
	mov	r9d, eax
	mov	r8d, CB_SETCURSEL
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

dpbInitDone:	mov	rax, TRUE
	jmp	dpbExit

	; -- handle commands --

dpbCommand:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	test	rax, rax
	je	dpbZero

	mov	r15, rax
	mov	r12, [r15.CLASS_BUTTON.pxApp]

	; -- branch on command --

	mov	rax, wParam
	shr	rax, 16

	cmp	ax, BN_CLICKED
	je	dpbButton
	cmp	ax, CBN_SELCHANGE
	je	dpbCombo

	jmp	dpbZero

	; -- cmd selection changed --

dpbCombo:	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, CB_GETCURSEL
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	dword ptr [rsp + 32], 0
	mov	r9, rax
	mov	r8d, CB_GETITEMDATA
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	add	rax, IDS_CMD_BASE

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, rax
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_BC_HINT
	mov	rcx, hwndDlg
	call	SetDlgItemText

	mov	rax, TRUE
	jmp	dpbExit

	; -- button pressed --

dpbButton:	mov	rax, wParam
	cmp	ax, IDOK
	je	dpbDone
	cmp	ax, IDCANCEL
	je	dpbClose

	jmp	dpbClose

	; -- read out command --

dpbDone:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	test	rax, rax
	je	dpbClose

	mov	r15, rax

	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, CB_GETCURSEL
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	dword ptr [rsp + 32], 0
	mov	r9, rax
	mov	r8d, CB_GETITEMDATA
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	[r15.CLASS_BUTTON.unCmd], rax

	; -- read out parameter text --

	lea	rax, [r15.CLASS_BUTTON.txParam]
	mov	[rsp + 32], rax
	mov	r9d, 256 - 1
	mov	r8d, WM_GETTEXT
	mov	edx, ID_BC_PARAM
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- read out button text --

	lea	rax, [r15.CLASS_BUTTON.txText]
	mov	[rsp + 32], rax
	mov	r9d, 32 - 1
	mov	r8d, WM_GETTEXT
	mov	edx, ID_BC_TEXT
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	jmp	dpbClose

	; -- handle close button --

dpbClose:	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, CBEM_SETIMAGELIST
	mov	edx, ID_BC_CMDLIST
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	rcx, rax
	call	ImageList_Destroy

	mov	edx, 0
	mov	rcx, hwndDlg
	call	EndDialog

	mov	rax, TRUE
	jmp	dpbExit

dpbZero:	xor	rax, rax

dpbExit:	add	rsp, 64
	add	rsp, 4 * 8 + 2 * 2048 + sizeof COMBOBOXEXITEM + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

dlgprcButton	ENDP

	END
