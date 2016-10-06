;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - progress handling
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
	include	command.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code

;------------------------------------------------------------------------------------------------------------------------------------------
; does:	open progress dialog
; last update:	2015-07-22 - Deutsch - created
; parameters:	unError prgOpenList ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prgOpenList	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 128
	.allocstack	128
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- open progress dialog --

	mov	[rsp + 32], r12
	lea	r9, dlgprcProgress
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_PROGRESS
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	CreateDialogParam
	test	rax, rax
	jz	polExit

	mov	[r12.CLASS_APP.hwndProgress], rax

	; -- prepare user cancel event --

	mov	rcx, [r15.CLASS_COMMAND.hevUserBreak]
	call	ResetEvent

	xor	rax, rax

polExit:	add	rsp, 128

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

prgOpenList	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	close progress dialog
; last update:	2015-07-22 - Deutsch - created
; parameters:	unError prgCloseList ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prgCloseList	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 128
	.allocstack	128 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- task list is empty, close progress --

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_CLOSE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendMessage

	mov	[r12.CLASS_APP.hwndProgress], 0

	xor	rax, rax

polExit:	add	rsp, 128
	add	rsp, 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

prgCloseList	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for progress dialog
; last update:	2001-01-07 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError dlgprcProgress (hwndDlg, unMessage, wParam, lParam)
;	[in] hwndDlg .. dialog window
;	[in] unMessage .. message to handle
;	[in] wParam .. message parameter
;	[in] lParam .. message parameter
; returns:	true for handled, else zero
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcProgress	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	hwndList:QWORD	; tab list
	LOCAL	xTab:TCITEM	; tabulator description
	LOCAL	xColumn:LVCOLUMN	; column information
	LOCAL	rcTab:RECT	; tab control size
	LOCAL	txBuffer [64]:WORD	; list window class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 96
	sub	rsp, 5 * 8 + sizeof TCITEM + sizeof LVCOLUMN + sizeof RECT + 64 * 2
	.allocstack	96 + 5 * 8 + sizeof TCITEM + sizeof LVCOLUMN + sizeof RECT + 64 * 2
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dppInit
	cmp	eax, WM_COMMAND
	je	dppCommand
	cmp	eax, WM_CLOSE
	je	dppClose
	cmp	eax, WM_DESTROY
	je	dppDestroy

	jmp	dppZero

	; -- prepare progress bar --

dppInit:	mov	r12, lParam

	mov	r8, lParam
	mov	edx, GWLP_USERDATA
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8d, PBM_SETRANGE32
	mov	edx, ID_CP_PROGRESS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	qword ptr [rsp + 32], 0
	mov	r9, 1
	mov	r8d, PBM_SETSTEP
	mov	edx, ID_CP_PROGRESS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	r9, [r12.CLASS_APP.hiconApp]
	mov	r8d, ICON_SMALL
	mov	edx, WM_SETICON
	mov	rcx, hwndDlg
	call	SendMessage

	; -- prepare do tab --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_PROGRESS_DO
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, xTab
	lea	rcx, txBuffer
	mov	[rax.TCITEM.imask], TCIF_TEXT
	mov	[rax.TCITEM.dwState], 0
	mov	[rax.TCITEM.dwStateMask], 0
	mov	[rax.TCITEM.pszText], rcx
	mov	[rax.TCITEM.cchTextMax], 0
	mov	[rax.TCITEM.iImage], 0
	mov	[rax.TCITEM.lParam], 0

	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, TCM_INSERTITEM
	mov	edx, ID_CP_TABS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- get tabulator client area --

	mov	edx, ID_CP_TABS
	mov	rcx, hwndDlg
	call	GetDlgItem

	lea	rdx, rcTab
	mov	rcx, rax
	call	GetClientRect

	lea	rax, rcTab
	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, TCM_ADJUSTRECT
	mov	edx, ID_CP_TABS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	lea	r9, txBuffer
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_LISTCLASS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	qword ptr [rsp + 88], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rsp + 80], rax
	mov	rax, IDC_PROGRESS_DO
	mov	[rsp + 72], rax

	mov	edx, ID_CP_TABS
	mov	rcx, hwndDlg
	call	GetDlgItem

	mov	[rsp + 64], rax
	lea	rcx, rcTab
	mov	eax, [rcx.RECT.bottom]
	sub	eax, [rcx.RECT.top]
	mov	[rsp + 56], eax
	lea	rcx, rcTab
	mov	eax, [rcx.RECT.right]
	sub	eax, [rcx.RECT.left]
	mov	[rsp + 48], eax
	lea	rax, rcTab
	mov	eax, [rax.RECT.top]
	mov	[rsp + 40], eax
	lea	rax, rcTab
	mov	eax, [rax.RECT.left]
	mov	[rsp + 32], eax
	mov	r9d, LVS_REPORT OR WS_CHILD OR WS_VISIBLE OR WS_VSCROLL
	mov	r8, 0
	lea	rdx, txBuffer
	mov	ecx, 0
	call	CreateWindowEx
	mov	hwndList, rax

	; -- prepare progress list column - action --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLACTION
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, 128

	mov	xColumn.LVCOLUMN.lmask, LVCF_FMT OR LVCF_WIDTH OR LVCF_SUBITEM OR LVCF_TEXT
	mov	xColumn.LVCOLUMN.iSubItem, 0
	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, hwndList
	call	SendMessage

	; -- prepare progress list column - source --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLSOURCE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, 320

	mov	xColumn.LVCOLUMN.iSubItem, 1
	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, hwndList
	call	SendMessage

	; -- prepare progress list column - target --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COLTARGET
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	rcx, 320

	mov	xColumn.LVCOLUMN.iSubItem, 2
	mov	xColumn.LVCOLUMN.fmt, LVCFMT_LEFT
	mov	xColumn.LVCOLUMN.pszText, rax
	mov	xColumn.LVCOLUMN.scx, ecx

	lea	r9, xColumn
	mov	r8d, xColumn.LVCOLUMN.iSubItem
	mov	edx, LVM_INSERTCOLUMN
	mov	rcx, hwndList
	call	SendMessage

	; -- prepare fail tab --

	mov	rax, TRUE
	jmp	dppExit

	; -- handle cancel button --

dppCommand:	mov	rax, wParam
	shr	rax, 16
	cmp	ax, BN_CLICKED
	jne	dppZero

	; -- get main --

	mov	edx, GWLP_USERDATA
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	test	rax, rax
	jz	dppZero

	mov	r12, rax

	; -- get command --

	mov	rax, wParam
	cmp	ax, IDCANCEL
	je	dppCancel

	; add more here

	jmp	dppZero

	; -- cancel - set event --

dppCancel:	mov	r15, [r12.CLASS_APP.pxCommand]
	mov	rcx, [r15.CLASS_COMMAND.hevUserBreak]
	call	SetEvent

	mov	rax, TRUE
	jmp	dppExit

	; -- close dialog --

dppClose:	mov	rcx, hwndDlg
	call	DestroyWindow

	mov	rax, TRUE
	jmp	dppExit

	; -- give back focus --

dppDestroy:	mov	edx, GW_OWNER
	mov	rcx, hwndDlg
	call	GetWindow

	mov	rcx, rax
	call	SetFocus

	mov	rax, TRUE
	jmp	dppExit

dppZero:	xor	rax, rax

dppExit:	add	rsp, 96
	add	rsp, 5 * 8 + sizeof TCITEM + sizeof LVCOLUMN + sizeof RECT + 64 * 2
		
	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

dlgprcProgress	ENDP

	END
