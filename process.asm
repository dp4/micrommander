;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - file processing operations
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
	include	list.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code

;------------------------------------------------------------------------------------------------------------------------------------------
; does:	start new list processing thread
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError prcStartThread (pxParameter)
;	[in] pxParameter .. thread parameter
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prcStartThread	PROC	FRAME
	LOCAL	idThread:QWORD	; fill thread id

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 48
	.allocstack	48 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	lea	rax, idThread
	mov	[rsp + 40], rax
	mov	dword ptr [rsp + 32], 0
	mov	r9, rdx
	lea	r8, prcWorkThread
	mov	rdx, 0
	mov	rcx, 0
	call	CreateThread
	test	rax, rax
	jz	pstFail

	mov	[r12.CLASS_APP.hthProcess], rax

	xor	rax, rax
	jmp	pstExit

pstFail:	call	GetLastError

pstExit:	add	rsp, 48
	add	rsp, 8

	pop	r12
	pop	rbp

	ret	0

	align	4

prcStartThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	stop running thread, if any
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError prcStopThread ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prcStopThread	PROC	FRAME
	LOCAL	xMessage:MSG	; handle messages during wait

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof MSG + 8
	sub	rsp, 48
	.allocstack	48 + sizeof MSG + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- check if thread is running --

	mov	rcx, [r12.CLASS_APP.hthProcess]
	test	rcx, rcx
	jz	pstDone

	; -- check if already at end --

	mov	edx, 0
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	je	pstEnded

	; -- stop now ! --

	mov	rcx, [r12.CLASS_APP.hevStop]
	call	SetEvent

	; -- wait for end --

pstLoop:	mov	dword ptr [rsp + 32], PM_REMOVE
	mov	r9d, 0
	mov	r8d, 0
	mov	rdx, 0
	lea	rcx, xMessage
	call	PeekMessage
	test	eax, eax
	jz	pstWait

	lea	rcx, xMessage
	call	DispatchMessage

	jmp	pstLoop

pstWait:	mov	dword ptr [rsp + 32], QS_ALLINPUT
	mov	r9d, 1000
	mov	r8d, FALSE
	lea	rdx, [r12.CLASS_APP.hthProcess]
	mov	ecx, 1
	call	MsgWaitForMultipleObjects
	cmp	eax, WAIT_OBJECT_0
	je	pstEnded
	cmp	eax, WAIT_OBJECT_0 + 1
	je	pstLoop

	; -- thread will not end, terminate --

	mov	rdx, 0
	mov	rcx, [r12.CLASS_APP.hthProcess]
	call	TerminateThread

	; -- thread has ended regular or has been terminated --

pstEnded:	mov	rcx, [r12.CLASS_APP.hthProcess]
	call	CloseHandle

	mov	[r12.CLASS_APP.hthProcess], 0

pstDone:	xor	rax, rax

	add	rsp, 48
	add	rsp, sizeof MSG + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

prcStopThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	wait for running thread to be done
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError prcWaitThread ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prcWaitThread	PROC	FRAME
	LOCAL	unError:QWORD
	LOCAL	xMessage:MSG	; handle messages during wait

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + sizeof MSG
	sub	rsp, 48
	.allocstack	48 + 8 + sizeof MSG
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- check if thread is running --

	mov	rcx, [r12.CLASS_APP.hthProcess]
	test	rcx, rcx
	jz	pwtDone

	; -- check if already at end --

	mov	edx, 0
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	je	pwtEnded

	; -- wait for end --

pwtLoop:	mov	dword ptr [rsp + 32], PM_REMOVE
	mov	r9d, 0
	mov	r8d, 0
	mov	rdx, 0
	lea	rcx, xMessage
	call	PeekMessage
	test	eax, eax
	jz	pwtWait

	lea	rcx, xMessage
	call	DispatchMessage

	jmp	pwtLoop

pwtWait:	mov	dword ptr [rsp + 32], QS_ALLINPUT
	mov	r9d, INFINITE
	mov	r8d, FALSE
	lea	rdx, [r12.CLASS_APP.hthProcess]
	mov	ecx, 1
	call	MsgWaitForMultipleObjects
	cmp	eax, WAIT_OBJECT_0 + 1
	je	pwtLoop

	; -- thread has ended --

pwtEnded:	lea	rdx, unError
	mov	rcx, [r12.CLASS_APP.hthProcess]
	call	GetExitCodeThread

	mov	rcx, [r12.CLASS_APP.hthProcess]
	call	CloseHandle

	mov	[r12.CLASS_APP.hthProcess], 0

	mov	rax, unError
	jmp	pwtExit

pwtDone:	xor	rax, rax

pwtExit:	add	rsp, 48
	add	rsp, 8 + sizeof MSG

	pop	r12
	pop	rbp

	ret	0

	align	4

prcWaitThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	process all selected items from active list view
; last update:	2002-12-30 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError prcWorkThread (pxParameter)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prcWorkThread	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 48
	.allocstack	48
	.endprolog

	; -- process list --

	mov	rax, rcx
	mov	rcx, [rax.PROCESS_PARAM.pxList]

	lea	rdx, cbListEntry
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnProcess]

	mov	rcx, rax
	call	ExitThread

	add	rsp, 48

	pop	rbp
	
	ret	0
	
	align	4

prcWorkThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	process single list entry
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError cbListEntry (pxItem, unCount, pxUser)
;	[in] pxItem .. list item
;	[in] unCount .. item counter
;	[in] pxUser .. user parameter
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbListEntry	PROC	FRAME
	LOCAL	pxItem:QWORD	; callback function
	LOCAL	unCount:QWORD	; callback user parameter
	LOCAL	hfFound:QWORD	; find file handle
	LOCAL	unResult:QWORD	; callback result
	LOCAL	txFile [DEF_PATH_LENGTH]:WORD	; file name buffer
	LOCAL	xFind:WIN32_FIND_DATA	; find file information

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof WIN32_FIND_DATA
	sub	rsp, 64
	.allocstack	64 + 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof WIN32_FIND_DATA
	.endprolog

	; -- get parameter --

	mov	pxItem, rcx
	mov	unCount, rdx
	mov	r14, r8

	; -- skip unselected items --

	mov	rax, pxItem
	test	[rax.LVITEM.state], LVIS_SELECTED
	je	appDone

	; -- clone path --

	mov	rdx, [r14.PROCESS_PARAM.ptxPath]
	lea	rcx, txFile
	call	lstrcpy

	mov	rax, pxItem
	mov	rdx, [rax.LVITEM.pszText]
	lea	rcx, txFile
	call	lstrcat

	; -- check if file or directory --

	mov	rax, pxItem
	cmp	[rax.LVITEM.lParam], TYPE_FILE
	jne	appDirectory

	; -- check if (still) present --

	lea	rdx, xFind
	lea	rcx, txFile
	call	FindFirstFile
	cmp	eax, INVALID_HANDLE_VALUE
	je	appDone

	mov	hfFound, rax

	; -- call callback --

	mov	[rsp + 32], r14
	mov	r9, unCount
	mov	r8, PROC_FILE
	lea	rdx, xFind
	lea	rcx, txFile
	call	cbProcessOne

	mov	unResult, rax

	mov	rcx, hfFound
	call	FindClose

	; -- check callback result --

	mov	rax, unResult
	jmp	appExit

	; -- handle into directory --

appDirectory:	lea	rcx, txFile
	call	lstrlen

	lea	rcx, txFile
	mov	word ptr [rcx + 2 * rax + 0], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r14.PROCESS_PARAM.fRecursive]
	mov	r8, r14
	mov	rdx, cbProcessOne
	lea	rcx, txFile
	call	prcWalkFolder
	test	rax, rax
	jne	appExit

appDone:	xor	rax, rax

appExit:	add	rsp, 64
	add	rsp, 4 * 8 + 2 * DEF_PATH_LENGTH + sizeof WIN32_FIND_DATA
	
	pop	r14
	pop	r12
	pop	rbp
	
	ret	0
	
	align	4

cbListEntry	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	process callback, will be called with each list entry and file/folder (if recursive), check for cancel, else call users callback
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cbProcessOne (ptxFile, pxFind, unMode, unCount, pxUser)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbProcessOne	PROC	FRAME
	LOCAL	ptxFile:QWORD	; current file name
	LOCAL	pxFind:QWORD	; found file information
	LOCAL	unMode:QWORD	; current process mode
	LOCAL	unCount:QWORD	; new list entry, place at end

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8
	sub	rsp, 48
	.allocstack	48 + 4 * 8
	.endprolog

	; -- get parameter --

	mov	ptxFile, rcx
	mov	pxFind, rdx
	mov	unMode, r8
	mov	unCount, r9
	mov	r14, [rbp + 4 * 8 + 32]
	mov	r12, [r14.PROCESS_PARAM.pxApp]

	; -- check for main closing --

	mov	edx, 0
	mov	rcx, [r12.CLASS_APP.hevStop]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	je	cpoCancel

	; -- call original user callback --

	mov	rax, [r14.PROCESS_PARAM.pxUser]
	mov	[rsp + 32], rax
	mov	r9, unCount
	mov	r8, unMode
	mov	rdx, pxFind
	mov	rcx, ptxFile
	call	[r14.PROCESS_PARAM.pfnCallback]

	jmp	cpoExit

cpoCancel:	mov	rax, ERROR_CANCELLED

cpoExit:	add	rsp, 48
	add	rsp, 4 * 8

	pop	r14
	pop	r12
	pop	rbp

	ret	0
	
	align	4

cbProcessOne	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	call user callback with every file, walk recursively if wanted
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError prcWalkFolder (ptxPath, pfnProc, pxUser, fRecursive, nDepth)
;	[in] ptxPath .. path to process
;	[in] pfnProc .. callback, called with each folder down / up and each file
;	[in] pxUser .. user parameter for callback
;	[in] fRecursive .. process sub folders or not
;	[in] nDepth .. processing depth
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

prcWalkFolder	PROC	FRAME
	LOCAL	ptxPath:QWORD	; path to process
	LOCAL	pfnProc:QWORD	; callback procedure
	LOCAL	pxUser:QWORD	; callback parameter
	LOCAL	fRecursive:QWORD	; true if recursive processing
	LOCAL	unDepth:QWORD	; recursion depth
	LOCAL	unError:QWORD	; error result
	LOCAL	hFindFile:QWORD	; find file handle
	LOCAL	ptxInside:QWORD	; file name position
	LOCAL	xFind:WIN32_FIND_DATA	; find information
	LOCAL	txProcess [DEF_PATH_LENGTH]:WORD	; text work buffer
	LOCAL	txAsterix [8]:WORD	; find pattern

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 * 8 + 2 * DEF_PATH_LENGTH + 2 * 8 + sizeof WIN32_FIND_DATA
	sub	rsp, 48
	.allocstack	48 + 8 * 8 + 2 * DEF_PATH_LENGTH + 2 * 8 + sizeof WIN32_FIND_DATA
	.endprolog

	; -- get parameter --
	
	mov	ptxPath, rcx
	mov	pfnProc, rdx
	mov	pxUser, r8
	mov	fRecursive, r9
	mov	rax, [rbp + 2 * 8 + 32]
	mov	unDepth, rax

	; -- check if path or file --

	mov	rcx, ptxPath
	call	GetFileAttributes
	cmp	eax, INVALID_HANDLE_VALUE
	je	proError
	test	eax, FILE_ATTRIBUTE_DIRECTORY
	jnz	proUseDir

	; -- handle single file --

	lea	rdx, xFind
	mov	rcx, ptxPath
	call	FindFirstFile
	cmp	eax, INVALID_HANDLE_VALUE
	je	proError

	mov	hFindFile, rax

	; -- call with one file --

	mov	rax, pxUser
	mov	[rsp + 32], rax
	mov	r9, unDepth
	mov	r8, PROC_FILE
	lea	rdx, xFind
	mov	rcx, ptxPath
	call	pfnProc
	test	rax, rax
	jnz	proErrClose

	mov	rcx, hFindFile
	call	FindClose
	jmp	proDone

	; -- loop each directory entry --

proUseDir:	lea	rcx, xFind
	mov	[rcx.WIN32_FIND_DATA.dwFileAttributes], eax

	mov	rdx, ptxPath
	lea	rcx, txProcess
	call	lstrcpy

	; -- check if trailing backslash --

	lea	rcx, txProcess
	call	lstrlen

	lea	rcx, txProcess
	cmp	word ptr [rcx + 2 * rax - 2], "\"
	jne	proDive

	mov	word ptr [rcx + 2 * rax - 2], 0

	; -- dive in, append mask, find first --

proDive:	mov	rax, pxUser
	mov	[rsp + 32], rax
	mov	r9, unDepth
	mov	r8, PROC_DIRDOWN
	lea	rdx, xFind
	lea	rcx, txProcess
	call	pfnProc
	test	eax, eax
	jnz	proExit

	; -- dont enum if not recursive --

	cmp	fRecursive, TRUE
	je	proFind

	; -- skip if no recursion --

	mov	rax, unDepth
	cmp	rax, 0
	jg	proDirUpCb

	; -- begin find loop --

proFind:	lea	rdx, txAsterix
	mov	word ptr [rdx + 0], "\"
	mov	word ptr [rdx + 2], "*"
	mov	word ptr [rdx + 4], "."
	mov	word ptr [rdx + 6], "*"
	mov	word ptr [rdx + 8], 0

	lea	rcx, txProcess
	call	lstrcat

	lea	rdx, xFind
	lea	rcx, txProcess
	call	FindFirstFile
	cmp	eax, INVALID_HANDLE_VALUE
	jne	proListDir

	; -- cannot list this folder, check some common errors --

	call	GetLastError
	cmp	eax, ERROR_ACCESS_DENIED
	je	proDirUpCb

	; -- unknown error, cancel here --

	jmp	proExit

proListDir:	mov	hFindFile, rax

	; -- remove asterix --

	lea	rcx, txProcess
	call	lstrlen

	lea	rcx, txProcess
	lea	rax, [rcx + 2 * rax - 8]
	mov	ptxInside, rax

	mov	word ptr [rax], 0

	; -- build path + filename, filter dots --

proUser:	lea	rdx, xFind
	lea	rdx, [rdx.WIN32_FIND_DATA.cFileName]

	cmp	dword ptr [rdx], 0000002Eh
	je	proNext

	cmp	dword ptr [rdx], 002E002Eh
	jne	proValid
	cmp	word ptr [rdx + 4], 0000h
	je	proNext

proValid:	mov	rcx, ptxInside
	mov	word ptr [rcx], "\"
	add	rcx, 2

	call	lstrcpy

	; -- check if file or dir --

	lea	rax, xFind
	mov	eax, [rax.WIN32_FIND_DATA.dwFileAttributes]
	test	eax, FILE_ATTRIBUTE_DIRECTORY
	jne	proDir

	; -- handle file --

	mov	rax, pxUser
	mov	[rsp + 32], rax
	mov	r9, unDepth
	mov	r8, PROC_FILE
	lea	rdx, xFind
	lea	rcx, txProcess
	call	pfnProc
	test	eax, eax
	jnz	proErrClose
	jmp	proNext

	; -- handle directory --

proDir:	cmp	fRecursive, TRUE
	je	proProcess

	; -- skip if no recursion --

	mov	rax, unDepth
	cmp	rax, 0
	jg	proNext

	; -- recursive handle dir --

proProcess:	mov	rax, unDepth
	inc	rax
	mov	[rsp + 32], rax
	mov	r9, fRecursive
	mov	r8, pxUser
	mov	rdx, pfnProc
	lea	rcx, txProcess
	call	prcWalkFolder
	test	rax, rax
	jne	proErrClose

	; -- find next --

proNext:	lea	rdx, xFind
	mov	rcx, hFindFile
	call	FindNextFile
	test	eax, eax
	jnz	proUser

	call	GetLastError
	cmp	eax, ERROR_NO_MORE_FILES
	jne	proExit

	; -- all done, go up one dir --

	mov	rcx, ptxInside
	mov	word ptr [rcx], 0

proDirUp:	mov	rcx, hFindFile
	call	FindClose

proDirUpCb:	mov	rax, pxUser
	mov	[rsp + 32], rax
	mov	r9, unDepth
	mov	r8, PROC_DIRUP
	lea	rdx, xFind
	lea	rcx, txProcess
	call	pfnProc

	jmp	proExit

	; -- close and errror --

proErrClose:	mov	unError, rax

	mov	rcx, hFindFile
	call	FindClose

	mov	rax, unError
	jmp	proExit

	; -- all done --

proDone:	xor	rax, rax
	jmp	proExit

proError:	call	GetLastError

proExit:	add	rsp, 48
	add	rsp, 8 * 8 + 2 * DEF_PATH_LENGTH + 2 * 8 + sizeof WIN32_FIND_DATA

	pop	rbp
	
	ret	0
	
	align	4

prcWalkFolder	ENDP

	END
