;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - setup options handling
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
	include	setup.inc


;----------------------------------------------------------------------------------------------------------------------
;	code segment
;----------------------------------------------------------------------------------------------------------------------

	.code

;----------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for install options
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	unError dlgprcOptions (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;----------------------------------------------------------------------------------------------------------------------

dlgprcOptions	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 8
	sub	rsp, 128
	.allocstack	128 + 4 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	optInitDialog
	cmp	eax, WM_COMMAND
	je	optWMCommand

	xor	eax, eax
	jmp	optExit


	; -- handle dialog init --

optInitDialog:	mov	r12, lParam

	test	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_DESKTOP
	je	owidStartMenu

	mov	qword ptr [rsp + 32], 0
	mov	r9d, BST_CHECKED
	mov	r8d, BM_SETCHECK
	mov	edx, ID_OP_DESKTOP
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

owidStartMenu:	test	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_STARTMENU
	je	optHandled

	mov	qword ptr [rsp + 32], 0
	mov	r9d, BST_CHECKED
	mov	r8d, BM_SETCHECK
	mov	edx, ID_OP_START
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	r8, r12
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	jmp	optHandled

	; -- handle commands --

optWMCommand:	cmp	word ptr wParam + 2, BN_CLICKED
	jne	optHandled

	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rax, wParam
	cmp	ax, IDC_PREVPAGE
	je	optPrevPage
	cmp	ax, IDC_NEXTPAGE
	je	optNextPage
	cmp	ax, IDCANCEL
	je	optUserExit

	jmp	optHandled

	; -- goto previous page, store options --

optPrevPage:	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [rcx.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnGetOptions]

	mov	edx, SETUP_PREV
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	optHandled

	; -- goto next page, store options --

optNextPage:	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [rcx.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnGetOptions]

	mov	edx, SETUP_NEXT
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	optHandled

	; -- cancel installation --

optUserExit:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit]
	cmp	eax, IDYES
	jne	optHandled

	mov	edx, SETUP_BREAK
	mov	rcx, hwndDlg
	call	EndDialog

optHandled:	mov	eax, TRUE

optExit:	add	rsp, 128
	add	rsp, 4 * 8 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

dlgprcOptions	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	sets the global options bit field according to current selection
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appGetOptions (pxApp, hwndDlg)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appGetOptions	PROC	FRAME
	LOCAL	hwndDlg:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 128
	.allocstack	128 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx

	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8d, BM_GETCHECK
	mov	edx, ID_OP_DESKTOP
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	test	eax, BST_CHECKED
	je	gioStart

	or	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_DESKTOP

gioStart:	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8d, BM_GETCHECK
	mov	edx, ID_OP_START
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	test	eax, BST_CHECKED
	je	gioFinish

	or	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_STARTMENU

gioFinish:	add	rsp, 128
	add	rsp, 1 * 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appGetOptions	ENDP

	End
