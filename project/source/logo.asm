;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - startup logo class
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
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	register logo class and open window
; last update:	2002-12-30 - Scholz - created
;	2013-02-19 - Deutsch - x64 translation
; parameters:	unError appInitLogo (unTimeout)
;	[in] unTimeout .. close logo banner after this milliseconds
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appInitLogo	PROC	FRAME
	LOCAL	unTimeout:QWORD	; logo show time
	LOCAL	hwndLogo:QWORD	; logo popup
	LOCAL	hbmLogo:QWORD	; logo image
	LOCAL	xClass:WNDCLASSEX	; logo window class information
	LOCAL	xBitmap:BITMAP	; logo bitmap information
	LOCAL	rcLogo:RECT	; window rectangle
	LOCAL	txClass [64]:WORD	; class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * 64 + sizeof WNDCLASSEX  + sizeof BITMAP + sizeof RECT + 8
	sub	rsp, 128
	.allocstack	128 + 3 * 8 + 2 * 64 + sizeof WNDCLASSEX + sizeof BITMAP + sizeof RECT + 8
	.endprolog

	; -- init logo --

	mov	r12, rcx
	mov	unTimeout, rdx

	mov	edx, IDB_STARTLOGO
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadBitmap
	mov	hbmLogo, rax

	; -- get some bitmap info --

	lea	r8, xBitmap
	mov	edx, sizeof BITMAP
	mov	rcx, hbmLogo
	call	GetObject

	lea	rax, xBitmap
	mov	ecx, [rax.BITMAP.bmHeight]
	mov	edx, [rax.BITMAP.bmWidth]

	lea	r14, rcLogo
	mov	[r14.RECT.bottom], ecx
	mov	[r14.RECT.right], edx

	mov	ecx, SM_CXFULLSCREEN
	call	GetSystemMetrics
	sub	eax, [r14.RECT.right]
	sar	eax, 1
	mov	[r14.RECT.left], eax

	mov	ecx, SM_CYFULLSCREEN
	call	GetSystemMetrics
	sub	eax, [r14.RECT.bottom]
	sar	eax, 1
	mov	[r14.RECT.top], eax

	; -- register own window class --

	lea	r9, txClass
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_LOGOCLASS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r14, xClass

	mov	edx, sizeof WNDCLASSEX
	mov	rcx, r14
	call	RtlZeroMemory

	mov	[r14.WNDCLASSEX.cbSize], sizeof WNDCLASSEX
	mov	[r14.WNDCLASSEX.Style], CS_HREDRAW OR CS_VREDRAW

	mov	rax, [r12.CLASS_APP.hinstApp]
	lea	rdx, txClass
	lea	rcx, wndprcLogo
	mov	[r14.WNDCLASSEX.hInstance], rax
	mov	[r14.WNDCLASSEX.lpszClassName], rdx
	mov	[r14.WNDCLASSEX.lpfnWndProc], rcx

	mov	rcx, r14
	call	RegisterClassEx

	; -- create window --

	lea	rdx, rcLogo

	mov	qword ptr [rsp + 88], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rsp + 80], rax
	mov	qword ptr [rsp + 72], 0
	mov	qword ptr [rsp + 64], 0
	mov	eax, [rdx.RECT.bottom]
	mov	[rsp + 56], eax
	mov	eax, [rdx.RECT.right]
	mov	[rsp + 48], eax
	mov	eax, [rdx.RECT.top]
	mov	[rsp + 40], eax
	mov	eax, [rdx.RECT.left]
	mov	[rsp + 32], eax
	mov	r9d, WS_VISIBLE OR WS_POPUP OR WS_BORDER
	mov	r8, 0
	lea	rdx, txClass
	mov	ecx, WS_EX_TOPMOST OR WS_EX_TOOLWINDOW
	call	CreateWindowEx
	test	rax, rax
	je	ilwExit

	mov	hwndLogo, rax

	; -- set bitmap --

	mov	r8, hbmLogo
	mov	edx, GWLP_USERDATA
	mov	rcx, hwndLogo
	call	SetWindowLongPtr

	; -- force window to be repainted --

	mov	r8d, FALSE
	mov	rdx, 0
	mov	rcx, hwndLogo
	call	InvalidateRect

	mov	rcx, hwndLogo
	call	UpdateWindow

	mov	r9, 0
	mov	r8, unTimeout
	mov	edx, "LOGO"
	mov	rcx, hwndLogo
	call	SetTimer

	xor	rax, rax

ilwExit:	add	rsp, 128
	add	rsp, 3 * 8 + 2 * 64 + sizeof WNDCLASSEX + sizeof BITMAP + sizeof RECT + 8

	pop	r14
	pop	r12
	pop	rbp
	ret	0

	align	4

appInitLogo	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	load image during create, start timer
; last update:	1999-04-28 - Scholz - created
;	2013-02-19 - Deutsch - x64 translation
; parameters:	result wndprcLogo (hwndLogo, unMessage, wParam, lParam)
;	[in] hwndLogo .. logo banner window
;	[in] unMessage .. message to handle
;	[in] wParam .. message parameter
;	[in] lParam .. message parameter
; returns:	depending on message
;------------------------------------------------------------------------------------------------------------------------------------------

wndprcLogo	PROC	FRAME
	LOCAL	hwndLogo:QWORD, unMessage:DWORD, wParam:QWORD, lParam:QWORD

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8
	sub	rsp, 48
	.allocstack	48 + 4 * 8
	.endprolog

	; -- get parameter --

	mov	hwndLogo, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message

	mov	eax, unMessage
	cmp	eax, WM_LBUTTONDOWN
	je	wplClose
	cmp	eax, WM_RBUTTONDOWN
	je	wplClose
	cmp	eax, WM_KEYDOWN
	je	wplClose
	cmp	eax, WM_TIMER
	je	wplClose
	cmp	eax, WM_CLOSE
	je	wplClose
	cmp	eax, WM_DESTROY
	je	wplDestroy
	cmp	eax, WM_PAINT
	je	wplPaint

	; -- pipe message to default proc --

	mov	rax, lParam
	mov	[rsp + 32], rax
	mov	r9, wParam
	mov	r8d, unMessage
	mov	rdx, hwndLogo
	lea	rcx, DefWindowProc
	call	CallWindowProc

	jmp	wplReturn

	; -- handle close --

wplClose:	mov	edx, "LOGO"
	mov	rcx, hwndLogo
	call	KillTimer

	mov	rcx, hwndLogo
	call	DestroyWindow
	jmp	wplExit

	; -- handle destroy --

wplDestroy:
	mov	edx, GWLP_USERDATA
	mov	rcx, hwndLogo
	call	GetWindowLongPtr

	mov	rcx, rax
	call	DeleteObject

	jmp	wplExit

	; -- handle paint --

wplPaint:	mov	r8d, 0
	mov	rdx, 0
	mov	rcx, hwndLogo
	call	GetUpdateRect
	test	rax, rax
	je	wplPaintEx

	mov	edx, GWLP_USERDATA
	mov	rcx, hwndLogo
	call	GetWindowLongPtr

	mov	rdx, rax
	mov	rcx, hwndLogo
	call	DrawBitmap

wplPaintEx:	mov	rdx, 0
	mov	rcx, hwndLogo
	call	ValidateRect

	jmp	wplExit

	; -- exit cases --

wplExit:	xor	rax, rax

wplReturn:	add	rsp, 48
	add	rsp, 4 * 8

	pop	rbp
	ret	0

	align	4

wndprcLogo	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	draws a bitmap specified by handle into a region of a window
; last update:	1999-01-27 - Hamann - created
;	2013-02-19 - Deutsch - x64 translation
; parameters:	void DrawBitmap (hwndDraw, hbmPic)
;	[in] hwndDraw .. window to fill with bitmap
;	[in] hbmPic .. image to draw
;------------------------------------------------------------------------------------------------------------------------------------------

DrawBitmap	PROC	FRAME
	LOCAL	hwndDraw:QWORD	; window to draw inside
	LOCAL	hbmPic:QWORD	; image to draw
	LOCAL	hdcMemory:QWORD	; draw DC
	LOCAL	hdcWindow:QWORD	; window DC
	LOCAL	rcDraw:RECT	; target rectangle
	LOCAL	xBitmap:BITMAP	; bitmap information

	push	rbp
	.pushreg	rbp
	push	rsi
	.pushreg	rsi
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + sizeof RECT + sizeof BITMAP + 8
	sub	rsp, 96
	.allocstack	96 + 4 * 8 + sizeof RECT + sizeof BITMAP + 8
	.endprolog

	; -- get windows client size --

	mov	hwndDraw, rcx
	mov	hbmPic, rdx

	lea	rdx, rcDraw
	mov	rcx, hwndDraw
	call	GetClientRect

	; -- create both contexts --

	mov	rcx, hwndDraw
	call	GetDC
	mov	hdcWindow, rax

	mov	rcx, hdcWindow
	call	CreateCompatibleDC
	mov	hdcMemory, rax

	mov	rdx, hbmPic
	mov	rcx, hdcMemory
	call	SelectObject
	mov	rsi, rax

	lea	r8, xBitmap
	mov	edx, sizeof BITMAP
	mov	rcx, hbmPic
	call	GetObject

	mov	edx, COLORONCOLOR
	mov	rcx, hdcWindow
	call	SetStretchBltMode

	lea	rdx, rcDraw
	lea	rcx, xBitmap

	mov	eax, SRCCOPY
	mov	[rsp + 80], eax
	mov	eax, [rcx.BITMAP.bmHeight]
	mov	[rsp + 72], eax
	mov	eax, [rcx.BITMAP.bmWidth]
	mov	[rsp + 64], eax
	mov	dword ptr [rsp + 56], 0
	mov	dword ptr [rsp + 48], 0
	mov	rax, hdcMemory
	mov	[rsp + 40], rax
	mov	eax, [rdx.RECT.bottom]
	mov	[rsp + 32], eax
	mov	r9d, [rdx.RECT.right]
	mov	r8d, 8
	mov	edx, 0
	mov	rcx, hdcWindow
	call	StretchBlt

	mov	rdx, rsi
	mov	rcx, hdcMemory
	call	SelectObject

	mov	rcx, hdcMemory
	call	DeleteDC

	mov	rdx, hdcWindow
	mov	rcx, hwndDraw
	call	ReleaseDC

	add	rsp, 96
	add	rsp, 4 * 8 + sizeof RECT + sizeof BITMAP + 8

	pop	rsi
	pop	rbp
	ret	0

	align	4

DrawBitmap	ENDP

	END
