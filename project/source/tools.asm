;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - misc. helper functions
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


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	convert large integer to string
; last update:	2003-01-02 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError i64toa (puqValue, ptxBuffer)
;	[in] puqValue .. pointer to value
;	[out] ptxBuffer .. resulting ascii text of number
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

i64toa	PROC	FRAME
	LOCAL	unDigits:QWORD	; number of digits in string
	LOCAL	ptxBuffer:QWORD	; output buffer, shall be 64 chars long !
	LOCAL	txBuffer [64]:WORD	; intermediate buffer

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 64
	.allocstack	2 * 8 + 2 * 64
	.endprolog

	; store parameter

	mov	ptxBuffer, rdx

	; prepare loop, start at end of buffer

	lea	r10, txBuffer
	lea	r10, [r10 + 2 * 63]

	mov	rax, [rcx]
	mov	unDigits, 0
	mov	r11, 10

toolLoop:	cqo
	div	r11

	add	dx, 30h
	mov	[r10], dx
	sub	r10, 2
	inc	unDigits

	cmp	rax, 0
	jne	toolLoop

	; -- move digits to start of buffer --

	add	r10, 2
	mov	rcx, unDigits

	mov	r11, r10
	mov	r10, ptxBuffer

toolMove: 	mov	ax, [r11]
	mov	[r10], ax

	add	r11, 2
	add	r10, 2
	loop	toolMove

	; -- terminate --

	mov	word ptr [r10], 0

	xor	rax, rax

	add	rsp, 2 * 8 + 2 * 64
	pop	rbp
	
	ret	0
	
	align	4

i64toa	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	convert numeric string to large integer
; last update:	2003-01-02 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError a64toi (ptxBuffer, puqValue)
;	[in] ptxBuffer .. resulting ascii text of number
;	[out] puqValue .. pointer to value
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

a64toi	PROC	FRAME
	LOCAL	unMultiply:QWORD	; decimal position
	LOCAL	ptxBuffer:QWORD	; input text
	LOCAL	punValue:QWORD	; output value

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 8
	.endprolog

	; -- store parameter --

	mov	ptxBuffer, rcx
	mov	punValue, rdx
	
	; -- prepare loop --
	
	mov	unMultiply, 1

	mov	rcx, ptxBuffer
	call	lstrlen
	mov	r11, rax

	mov	r10, punValue
	mov	qword ptr [r10], 0

	mov	r9, ptxBuffer

	; -- loop chars --

toolLoop:	test	r11, r11
	jz	toolDone

	mov	cx, [r9 + 2 * r11 - 2]
	sub	cx, "0"
	jl	toolFail
	cmp	rcx, 9
	jg	toolFail

	; -- multiply char with factor --

	movsx	rax, cx
	imul	unMultiply
	add	[r10], rax

	; -- advance multiply and string --

	mov	rax, unMultiply
	mov	rcx, 10
	imul	rcx
	mov	unMultiply, rax

	dec	r11
	jmp	toolLoop

toolDone:	xor	rax, rax
	jmp	toolExit

toolFail:	mov	rax, E_FAIL

toolExit:	add	rsp, 32
	add	rsp, 3 * 8 + 8
	pop	rbp
	
	ret	0
	
	align	4

a64toi	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	set decimal (e.g. 1.000.000) divider points in digit string
; last update:	2003-01-02 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError toolDecPoints (ptxText, ptxBuffer)
;	[in] ptxText .. raw number
;	[out] ptxBuffer .. formatted number
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

toolDecPoints	PROC	FRAME
	LOCAL	unPoints:QWORD	; number of points
	LOCAL	unCount:QWORD	; position counter
	LOCAL	unFirst:QWORD	; digits in first block

	push	rbp
	.pushreg	rbp
	push	r13
	.pushreg	r13
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 8
	.endprolog

	; -- store parameter --

	mov	r13, rcx
	mov	r14, rdx

	; -- get number of decimal points --

	mov	rcx, r13
	call	lstrlen

	dec	rax
	mov	rcx, 3
	cqo
	idiv	rcx
	mov	unPoints, rax

	; -- get digits in first block --

	inc	rdx
	mov	unFirst, rdx

	; -- copy first block, add null termination

	mov	r8, unFirst
	inc	r8
	mov	rdx, r13
	mov	rcx, r14
	call	lstrcpyn

	mov	rax, unFirst
	lea	r13, [r13 + 2 * rax]
	lea	r14, [r14 + 2 * rax]

	mov	unCount, 0

	; -- loop remaining blocks, copy 3 chars + null terminator --

toolLoop:	mov	rcx, unPoints
	cmp	unCount, rcx
	jge	toolDone

	mov	word ptr [r14], "."
	add	r14, 2

	mov	r8d, 4		;
	mov	rdx, r13
	mov	rcx, r14
	call	lstrcpyn

	lea	r13, [r13 + 2 * 3]
	lea	r14, [r14 + 2 * 3]

	inc	unCount
	jmp	toolLoop

toolDone:	xor	rax, rax

	add	rsp, 32
	add	rsp, 3 * 8 + 8

	pop	r14
	pop	r13
	pop	rbp
	
	ret	0
	
	align	4

toolDecPoints	ENDP

	END
