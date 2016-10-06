;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - action class, simple linked list
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
	include	OleAuto.inc

	include	app.inc
	include	command.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new action object
; last update:	2013-06-06 - Deutsch - created
; parameters:	pxAction actionNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

actionNew	PROC	FRAME

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
	jz	actExit

	mov	r8, sizeof CLASS_ACTION
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	actExit

	lea	rcx, [rax.CLASS_ACTION.xInterface]
	mov	[rax.CLASS_ACTION.vtableThis], rcx

	lea	rdx, actInit
	mov	[rcx.CLASS_ACTION_IFACE.pfnInit], rdx
	lea	rdx, actRelease
	mov	[rcx.CLASS_ACTION_IFACE.pfnRelease], rdx
	lea	rdx, actSetProgress
	mov	[rcx.CLASS_ACTION_IFACE.pfnSetProgress], rdx
	lea	rdx, actRemProgress
	mov	[rcx.CLASS_ACTION_IFACE.pfnRemProgress], rdx

actExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

actionNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize action object
; last update:	2013-06-06 - Deutsch - created
; parameters:	unError actInit (unCmd, ptxSource, ptxDest, unGroup)
;	[in] unCmd .. command to execute
;	[in] ptxSource .. source file
;	[in] ptxDest .. destination file
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

actInit	PROC	FRAME
	LOCAL	ptxSource:QWORD
	LOCAL	ptxDest:QWORD

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32 + 2 * 8 + 8
	.allocstack	32 + 2 * 8 + 8
	.endprolog

	; -- store parameter --

	mov	ptxSource, r8
	mov	ptxDest, r9

	; -- fill in action --

	mov	r15, rcx

	mov	[r15.CLASS_ACTION.unCmd], rdx
	mov	[r15.CLASS_ACTION.idItem], 0
	mov	[r15.CLASS_ACTION.pxNext], 0
	mov	rax, [rbp + 3 * 8 + 32]
	mov	[r15.CLASS_ACTION.unGroup], rax

	mov	rcx, ptxSource
	call	SysAllocString

	mov	[r15.CLASS_ACTION.ptxSource], rax

	mov	rcx, ptxDest
	call	SysAllocString

	mov	[r15.CLASS_ACTION.ptxDest], rax

	mov	rax, 0

	; -- all done --

	add	rsp, 32 + 2 * 8 + 8
	pop	r15
	pop	rbp
	ret	0

	align	4

actInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	place content of this item as text into progress list
; last update:	2013-06-06 - Deutsch - created
; parameters:	unError actSetProgress (pxApp)
;	[in] pxApp .. main application
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

actSetProgress	PROC	FRAME
	LOCAL	hwndList:QWORD	; progress list
	LOCAL	xItem:LVITEM	; new list item
	LOCAL	txBuffer [128]:WORD	; command name
	LOCAL	xRange:PBRANGE	; progress bar range

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + 2 * 128 + sizeof LVITEM + sizeof PBRANGE
	sub	rsp, 48
	.allocstack	48 + 8 + 2 * 128 + sizeof LVITEM + sizeof PBRANGE
	.endprolog

	; -- add item to list --

	mov	r15, rcx
	mov	r12, rdx

	mov	edx, ID_CP_TABS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	GetDlgItem

	mov	edx, IDC_PROGRESS_DO
	mov	rcx, rax
	call	GetDlgItem
	mov	hwndList, rax

	mov	edx, sizeof LVITEM
	lea	rcx, xItem
	call	RtlZeroMemory

	; -- set description in progress list --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, [r15.CLASS_ACTION.unCmd]
	add	rdx, IDS_CMD_EMPTY
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, txBuffer
	mov	xItem.LVITEM.lmask, LVIF_TEXT OR LVIF_PARAM
	mov	xItem.LVITEM.pszText, rax
	mov	xItem.LVITEM.iItem, 7FFFFFFFh
	mov	xItem.LVITEM.iSubItem, 0
	mov	xItem.LVITEM.lParam, r15

	lea	r9, xItem
	mov	r8d, 0
	mov	edx, LVM_INSERTITEM
	mov	rcx, hwndList
	call	SendMessage

	mov	xItem.LVITEM.iItem, eax
	mov	[r15.CLASS_ACTION.idItem], rax

	; -- add parameter texts --

	mov	xItem.LVITEM.lmask, LVIF_TEXT

	mov	rax, [r15.CLASS_ACTION.ptxSource]
	mov	xItem.LVITEM.pszText, rax
	mov	xItem.LVITEM.iSubItem, 1

	lea	r9, xItem
	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, hwndList
	call	SendMessage

	mov	rax, [r15.CLASS_ACTION.ptxDest]
	mov	xItem.LVITEM.pszText, rax
	mov	xItem.LVITEM.iSubItem, 2

	lea	r9, xItem
	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, hwndList
	call	SendMessage

	; -- increment progress range --

	lea	rax, xRange
	mov	qword ptr [rsp + 32], rax
	mov	r9, 0
	mov	r8, PBM_GETRANGE
	mov	rdx, ID_CP_PROGRESS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendDlgItemMessage

	lea	rax, xRange
	mov	eax, [rax.PBRANGE.iHigh]
	inc	eax

	mov	qword ptr [rsp + 32], rax
	mov	r9, 0
	mov	r8d, PBM_SETRANGE32
	mov	edx, ID_CP_PROGRESS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendDlgItemMessage

	; -- all done --

aspDone:	mov	rax, 0

	add	rsp, 48
	add	rsp, 8 + 2 * 128 + sizeof LVITEM + sizeof PBRANGE

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

actSetProgress	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	remove item from progress list
; last update:	2013-06-06 - Deutsch - created
; parameters:	unError actRemProgress (hwndList)
;	[in] hwndList .. progress list
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

actRemProgress	PROC	FRAME
	LOCAL	hwndList:QWORD	; progress list
	LOCAL	xFindItem:LVFINDINFOW

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + sizeof LVFINDINFO
	sub	rsp, 48
	.allocstack	48 + 1 * 8 + sizeof LVFINDINFO
	.endprolog

	; -- remove item from list --

	mov	r15, rcx
	mov	r12, rdx

	mov	edx, ID_CP_TABS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	GetDlgItem

	mov	edx, IDC_PROGRESS_DO
	mov	rcx, rax
	call	GetDlgItem
	mov	hwndList, rax

	; -- remove item from progress list --

	lea	r9, xFindItem
	mov	[r9.LVFINDINFO.flags], LVFI_PARAM
	mov	[r9.LVFINDINFO.psz], 0
	mov	[r9.LVFINDINFO.lParam], r15
	mov	[r9.LVFINDINFO.pt.POINT.x], 0
	mov	[r9.LVFINDINFO.pt.POINT.y], 0
	mov	[r9.LVFINDINFO.vkDirection], 0

	mov	r8, -1
	mov	edx, LVM_FINDITEM
	mov	rcx, hwndList
	call	SendMessage

	mov	r9, 0
	mov	r8d, eax
	mov	edx, LVM_DELETEITEM
	mov	rcx, hwndList
	call	SendMessage

	; -- step progress bar --

	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8, PBM_STEPIT 
	mov	rdx, ID_CP_PROGRESS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendDlgItemMessage

	; -- all done --

	mov	rax, 0

	add	rsp, 48
	add	rsp, 1 * 8 + sizeof LVFINDINFO

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

actRemProgress	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release action object
; last update:	2013-06-06 - Deutsch - created
; parameters:	unError actRelease ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

actRelease	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 32
	.allocstack	32 + 8
	.endprolog

	; -- free strings and myself --

	mov	r14, rcx

	mov	rcx, [r14.CLASS_ACTION.ptxDest]
	call	SysFreeString

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	SysFreeString

	call	GetProcessHeap

	mov	r8, r14
	mov	edx, 0
	mov	rcx, rax
	call	HeapFree

	; - -all done --

	mov	rax, 0

	add	rsp, 32
	add	rsp, 8

	pop	r14
	pop	rbp
	ret	0

	align	4

actRelease	ENDP

	END
