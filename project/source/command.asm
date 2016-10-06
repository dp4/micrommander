;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - command class and command processing
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
	include	oleauto.inc
	include	shlobj.inc
	include	shellapi.inc

	include	app.inc
	include	button.inc
	include	command.inc
	include	list.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	interface
;------------------------------------------------------------------------------------------------------------------------------------------
	
	; progress methods

prgOpenList	proto
prgCloseList	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new command object
; last update:	2013-06-06 - Deutsch - created
; parameters:	pxCommand commandNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

commandNew	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	.allocstack	32
	.endprolog

	; -- allocate object --

	call	GetProcessHeap
	test	rax, rax
	jz	cnwExit

	mov	r8, sizeof CLASS_COMMAND
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	cnwExit

	; -- prepare vtable --

	lea	rcx, [rax.CLASS_COMMAND.xInterface]
	mov	[rax.CLASS_COMMAND.vtableThis], rcx

	lea	rdx, cmdInit
	mov	[rcx.CLASS_COMMAND_IFACE.pfnInit], rdx
	lea	rdx, cmdRelease
	mov	[rcx.CLASS_COMMAND_IFACE.pfnRelease], rdx
	lea	rdx, cmdExecute
	mov	[rcx.CLASS_COMMAND_IFACE.pfnExecute], rdx
	lea	rdx, cmdRoot
	mov	[rcx.CLASS_COMMAND_IFACE.pfnChangeRoot], rdx
	lea	rdx, cmdCopyFiles
	mov	[rcx.CLASS_COMMAND_IFACE.pfnCopyFiles], rdx
	lea	rdx, cmdCopyFile
	mov	[rcx.CLASS_COMMAND_IFACE.pfnCopyFile], rdx
	lea	rdx, cmdMoveFiles
	mov	[rcx.CLASS_COMMAND_IFACE.pfnMoveFiles], rdx
	lea	rdx, cmdMoveFile
	mov	[rcx.CLASS_COMMAND_IFACE.pfnMoveFile], rdx
	lea	rdx, cmdDeleteFiles
	mov	[rcx.CLASS_COMMAND_IFACE.pfnDeleteFiles], rdx
	lea	rdx, cmdDeleteFile
	mov	[rcx.CLASS_COMMAND_IFACE.pfnDeleteFile], rdx
	lea	rdx, cmdRename
	mov	[rcx.CLASS_COMMAND_IFACE.pfnRenameFiles], rdx
	lea	rdx, cmdCreateDir
	mov	[rcx.CLASS_COMMAND_IFACE.pfnMakeDir], rdx
	lea	rdx, prgOpenList
	mov	[rcx.CLASS_COMMAND_IFACE.pfnOpenProgress], rdx
	lea	rdx, prgCloseList
	mov	[rcx.CLASS_COMMAND_IFACE.pfnCloseProgress], rdx
	lea	rdx, cmdHandleError
	mov	[rcx.CLASS_COMMAND_IFACE.pfnHandleError], rdx
	lea	rdx, cmdCleanTask
	mov	[rcx.CLASS_COMMAND_IFACE.pfnCleanTask], rdx

	; -- initialize members --

	mov	[rax.CLASS_COMMAND.unGroup], 1

cnwExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

commandNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	initialize command object
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdInit (pxApp)
;	[in] pxApp .. main application
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdInit	PROC	FRAME
	LOCAL	idThread:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + 8
	sub	rsp, 64
	.allocstack	64 + 8 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, rdx

	; -- prepare members --

	mov	[r15.CLASS_COMMAND.pxApp], r12

	; -- init thread events --

	mov	r9, 0
	mov	r8, FALSE
	mov	edx, FALSE
	mov	rcx, 0
	call	CreateEvent
	mov	[r15.CLASS_COMMAND.hevStart], rax

	mov	r9, 0
	mov	r8d, 0
	mov	edx, TRUE
	mov	rcx, 0
	call	CreateEvent
	mov	[r15.CLASS_COMMAND.hevCancel], rax

	mov	r9, 0
	mov	r8d, 0
	mov	edx, TRUE
	mov	rcx, 0
	call	CreateEvent
	mov	[r15.CLASS_COMMAND.hevUserBreak], rax
	
	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	InitializeCriticalSection

	; -- start command thread --

	lea	rax, idThread
	mov	[rsp + 40], rax
	mov	dword ptr [rsp + 32], 0
	mov	r9, r15
	lea	r8, cmdThread
	mov	rdx, 0
	mov	rcx, 0
	call	CreateThread
	test	rax, rax
	jz	cinFail

	mov	[r15.CLASS_COMMAND.htCommand], rax
	jmp	cinDone

cinFail:	call	GetLastError
	jmp	cinExit

cinDone:	xor	rax, rax

cinExit:	add	rsp, 64
	add	rsp, 8 + 8

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

cmdInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release command object
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdRelease ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdRelease	PROC	FRAME

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

	; -- stop command thread --

	mov	rcx, [r15.CLASS_COMMAND.hevCancel]
	call	SetEvent

	mov	rcx, [r15.CLASS_COMMAND.htCommand]
	test	rcx, rcx
	jz	crlFree

	mov	edx, 1000
	call	WaitForSingleObject
	cmp	eax, WAIT_TIMEOUT
	je	crlFree

	; -- thread is over, close handle --

	mov	rcx, [r15.CLASS_COMMAND.htCommand]
	call	CloseHandle

	mov	[r15.CLASS_COMMAND.htCommand], 0

	; -- free resources --

crlFree:	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	DeleteCriticalSection

	mov	rcx, [r15.CLASS_COMMAND.hevUserBreak]
	call	CloseHandle

	mov	rcx, [r15.CLASS_COMMAND.hevCancel]
	call	CloseHandle

	mov	rcx, [r15.CLASS_COMMAND.hevStart]
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

cmdRelease	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	command execution thread - waits for new command operations, queued all in a list
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdThread (pxCommand)
;	[in] pxCommand .. command object
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdThread	PROC	FRAME
	LOCAL	fDone:QWORD	; true if command list has been processed

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- wait for start or cancel --

cthLoop:	mov	r9d, INFINITE
	mov	r8d, FALSE
	lea	rdx, [r15.CLASS_COMMAND.hevStart]
	mov	ecx, 2
	call	WaitForMultipleObjects
	cmp	eax, WAIT_OBJECT_0
	je	cthStart
	cmp	eax, WAIT_OBJECT_0 + 1
	je	cthExit

	; error

	jmp	cthExit

	; -- begin processing of command task list - open progress window --

cthStart:	mov	[r15.CLASS_COMMAND.fIgnore], 0

	; -- access command list, link out current command --

cthProcessList:	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	EnterCriticalSection

	mov	r14, [r15.CLASS_COMMAND.parrCommands]
	test	r14, r14
	jz	cthLeave

	mov	rcx, [r14.CLASS_ACTION.pxNext]
	mov	[r15.CLASS_COMMAND.parrCommands], rcx

	mov	fDone, 0
	jmp	cthHandle

	; -- list empty, wait for more --

cthLeave:	mov	fDone, 1

cthHandle:	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	LeaveCriticalSection

	cmp	fDone, 1
	jne	cthProcess

	; -- close progress --

	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCloseProgress]

	; -- final refresh of source and destination list --

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	mov	rdx, LIST_OTHER
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	jmp	cthLoop

	; -- execute current command from list --

cthProcess:	mov	rcx, [r14.CLASS_ACTION.unCmd]
	cmp	rcx, CMD_MKDIR
	je	cthDoCreate
	cmp	rcx, CMD_COPY
	je	cthDoCopy
	cmp	rcx, CMD_MOVE
	je	cthDoMove
	cmp	rcx, CMD_DELETE
	je	cthDoDelete
	cmp	rcx, CMD_RENAME
	je	cthDoRename

	jmp	cthRemove

	; -- do create folder --

cthDoCreate:	mov	rdx, [r14.CLASS_ACTION.ptxDest]
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnMakeDir]

	jmp	cthHandleErr

	; -- do file copy --

cthDoCopy:	mov	rdx, r14
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCopyFile]

	jmp	cthHandleErr

	; -- do file move --

cthDoMove:	mov	rdx, r14
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnMoveFile]

	jmp	cthHandleErr

	; -- do file delete --

cthDoDelete:	mov	rdx, r14
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnDeleteFile]

	jmp	cthHandleErr

	; -- do file rename --

cthDoRename:
	jmp	cthHandleErr

	; -- handle any result code - we shall have our own button results only --

cthHandleErr:	test	rax, rax
	jz	cthRemove

	cmp	rax, ID_BTN_RETRY
	je	cthProcess
	cmp	rax, ID_BTN_IGNORE
	je	cthRemove
	cmp	rax, ID_BTN_IGNORE_ALL
	je	cthIgnAll
	cmp	rax, IDCANCEL
	je	cthUserCancel

	; add more error options here ..

	jmp	cthRemove

	; -- ignore all errors from now on --

cthIgnAll:	mov	[r15.CLASS_COMMAND.fIgnore], 1

	; -- remove command --

cthRemove:	mov	rdx, r12
	mov	rcx, r14
	mov	rax, [r14.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnRemProgress]

	mov	rcx, r14
	mov	rax, [r14.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnRelease]

	mov	r14, 0

	; -- check for user cancel --

	mov	rdx, 0
	mov	rcx, [r15.CLASS_COMMAND.hevUserBreak]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	jne	cthProcessList

	; -- error or cancel during task processing - clean task list --

cthUserCancel:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCleanTask]

	jmp	cthProcessList

	; -- exit thread --

cthExit:	mov	ecx, 0
	call	ExitThread

	add	rsp, 32
	add	rsp, 1 * 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdThread	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	clean task list from all entries with given action 
; last update:	2015-07-24 - Deutsch - created
; parameters:	unError cmdCleanTask (pxApp)
;	[in] pxApp .. main application object
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdCleanTask	PROC	FRAME
	LOCAL	xRange:PBRANGE

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof PBRANGE + 8
	sub	rsp, 32
	.allocstack	32 + sizeof PBRANGE + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- loop task list, remove wanted entries

	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	EnterCriticalSection

cctLoop:	mov	r14, [r15.CLASS_COMMAND.parrCommands]
	test	r14, r14
	jz	cctLeave

	; -- remove entry --

	mov	rcx, [r14.CLASS_ACTION.pxNext]
	mov	[r15.CLASS_COMMAND.parrCommands], rcx

	mov	rcx, r14
	mov	rax, [r14.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnRelease]

	jmp	cctLoop

cctLeave:	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	LeaveCriticalSection

	; -- clean list --

	mov	edx, ID_CP_TABS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	GetDlgItem

	mov	edx, IDC_PROGRESS_DO
	mov	rcx, rax
	call	GetDlgItem

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, LVM_DELETEALLITEMS
	mov	rcx, rax
	call	SendMessage

	; -- end step progress --

	lea	rax, xRange
	mov	[rsp + 32], rax
	mov	r9, 0
	mov	r8, PBM_GETRANGE
	mov	rdx, ID_CP_PROGRESS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendDlgItemMessage

	lea	rax, xRange
	mov	eax, [rax.PBRANGE.iHigh]

	mov	qword ptr [rsp + 32], 0
	mov	r9d, eax
	mov	r8, PBM_SETPOS
	mov	rdx, ID_CP_PROGRESS
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SendDlgItemMessage


	xor	rax, rax

	add	rsp, 32
	add	rsp, sizeof PBRANGE + 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdCleanTask	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	execute given command
; last update:	2006-04-09 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cmdExecute (pxButton)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdExecute	PROC	FRAME
	LOCAL	xSelect:CMD_SELECT_PARAM	; select list callback parameter
	LOCAL	txPath [DEF_PATH_LENGTH]:WORD	; misc. path name
	LOCAL	txNew [DEF_PATH_LENGTH]:WORD	; create new folder name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + sizeof CMD_SELECT_PARAM + 8
	sub	rsp, 64
	.allocstack	64 + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + sizeof CMD_SELECT_PARAM + 8
	.endprolog

	; -- get parameter --

	mov	r14, rdx
	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- check command --
	
	mov	rax, [r14.CLASS_BUTTON.unCmd]
	cmp	rax, CMD_EXIT
	je	cexQuit
	cmp	rax, CMD_CD
	je	cexChDir
	cmp	rax, CMD_PARENT
	je	cexParent
	cmp	rax, CMD_ROOT
	je	cexDoRoot
	cmp	rax, CMD_ALL
	je	cexSelAll
	cmp	rax, CMD_NONE
	je	cexSelNone
	cmp	rax, CMD_MKDIR
	je	cexMakeDir
	cmp	rax, CMD_COPY
	je	cexCopyFile
	cmp	rax, CMD_MOVE
	je	cexMoveFile
	cmp	rax, CMD_DELETE
	je	cexDeleteFile
	cmp	rax, CMD_RENAME
	je	cexRenameFile
	cmp	rax, CMD_FORMAT
	je	cexFormat
	cmp	rax, CMD_EXECUTE
	je	cexExec
	cmp	rax, CMD_BYTE
	je	cexByte

	; fill in more

	jmp	cexExit

	; -- exit program --

cexQuit:	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_CLOSE
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SendMessage

	jmp	cexExit

	; -- copy files --

cexCopyFile:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnOpenProgress]

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCopyFiles]

	jmp	cexExit

	; -- move files --

cexMoveFile:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnOpenProgress]

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnMoveFiles]

	jmp	cexExit

	; -- delete files --

cexDeleteFile:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnOpenProgress]

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnDeleteFiles]

	jmp	cexExit

	; -- rename files --

cexRenameFile:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnRenameFiles]

	; -- update list --

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	jmp	cexExit

	; -- change directory to string --

cexChDir:	lea	rdx, [r14.CLASS_BUTTON.txParam]
	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrcpy

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	jmp	cexExit

	; -- go to root --

cexDoRoot:	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnChangeRoot]

	jmp	cexExit

	; -- get parent --

cexParent:	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]

	cmp	rax, 2
	jle	cexExit
	dec	rax

cexLoop:	dec	rax
	cmp	word ptr [rcx + 2 * rax], "\"
	je	cexFound

	test	rax, rax
	jnz	cexLoop

	; no more parent possible

	jmp	cexExit

cexFound:	mov	word ptr [rcx + 2 * rax + 2], 0

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	jmp	cexExit

	; -- select all items --

cexSelAll:	mov	rax, [r12.CLASS_APP.pxActive]
	mov	xSelect.CMD_SELECT_PARAM.pxThis, rax
	mov	xSelect.CMD_SELECT_PARAM.fSelect, TRUE

	; -- select list --

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.hwndList]
	call	SetFocus

	; -- process list --

	lea	r8, xSelect
	lea	rdx, cbSelect
	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnProcess]

	jmp	cexExit

	; -- deselect all items --

cexSelNone:	mov	rax, [r12.CLASS_APP.pxActive]
	mov	xSelect.CMD_SELECT_PARAM.pxThis, rax
	mov	xSelect.CMD_SELECT_PARAM.fSelect, FALSE

	; -- select list --

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.hwndList]
	call	SetFocus

	; -- process list --

	lea	r8, xSelect
	lea	rdx, cbSelect
	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnProcess]

	jmp	cexExit

	; -- create new directory --

cexMakeDir:	lea	rax, txPath
	mov	[rsp + 32], rax
	lea	r9, dlgprcMakeDir
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_MAKE_DIR
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	DialogBoxParam
	test	eax, eax
	jz	cexExit

	; -- build target --

	mov	rdx, [r12.CLASS_APP.pxActive]
	mov	rdx, [rdx.CLASS_LIST.ptxPath]
	lea	rcx, txNew
	call	lstrcpy

	lea	rdx, txPath
	lea	rcx, txNew
	call	lstrcat

	lea	rdx, txNew
	mov	rcx, r12
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnMakeDir]

	; -- update list --

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	jmp	cexExit

	; -- execute file in button parameter --

cexExec:	mov	dword ptr [rsp + 40], SW_SHOWNORMAL
	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	lea	r8, [r14.CLASS_BUTTON.txParam]
	mov	edx, 0
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	ShellExecute

	jmp	cexExit

	; -- format drive --

cexFormat:	mov	rax, [r12.CLASS_APP.pxActive]
	mov	rax, [rax.CLASS_LIST.ptxPath]

	mov	dx, [rax]
	and	dx, NOT 20h
	cmp	dx, "A"
	jl	cexExit
	cmp	dx, "Z"
	jg	cexExit

	sub	rdx, "A"
	and	rdx, 0FFh

	mov	r9d, 0
	mov	r8d, SHFMT_ID_DEFAULT
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SHFormatDrive

	jmp	cexExit

	; -- get size of files --

cexByte:	mov	rcx, r12
	call	cmdFileSize

	jmp	cexExit

	; -- all done --

cexDone:	xor	eax, eax

cexExit:	add	rsp, 64
	add	rsp, 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH + sizeof CMD_SELECT_PARAM + 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdExecute	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	copy selected files and folders - add selected files recursively to command list
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdCopyFiles ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdCopyFiles	PROC	FRAME
	LOCAL	xAction:CMD_ADD_ACTION	; action to add
	LOCAL	txBuffer [64]:WORD	; list window class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8
	sub	rsp, 128
	.allocstack	128 + sizeof CMD_ADD_ACTION + 64 * 2 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- show collect hint --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_COPY_COLLECT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- add selected files recursively to command list --

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.pxApp], r12
	mov	[r9.CMD_ADD_ACTION.unFileAction], CMD_COPY
	mov	[r9.CMD_ADD_ACTION.unDownAction], CMD_MKDIR
	mov	[r9.CMD_ADD_ACTION.unUpAction], CMD_NONE

	mov	rax, [r15.CLASS_COMMAND.unGroup]
	mov	[r9.CMD_ADD_ACTION.unGroup], rax
	add	[r15.CLASS_COMMAND.unGroup], 1

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unSourcePos], rax

	mov	rcx, [r12.CLASS_APP.pxInactive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unTargetPos], rax

	mov	rdx, [r12.CLASS_APP.pxInactive]
	mov	rdx, [rdx.CLASS_LIST.ptxPath]
	lea	rcx, [r9.CMD_ADD_ACTION.txTarget]
	call	lstrcpy

	mov	qword ptr [rsp + 32], 1
	lea	r8, cbAddCmd
	lea	r9, xAction
	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]
	test	rax, rax
	jz	ccfRunCopy
	cmp	rax, ERROR_OPERATION_ABORTED
	je	cffDone

	; -- error or cancel during collection - clean task list --

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCleanTask]
	
	jmp	ccfCleanup

	; -- show process task list hint --

ccfRunCopy:	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_COPY
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- start worker thread --

ccfCleanup:	mov	rcx, [r15.CLASS_COMMAND.hevStart]
	call	SetEvent

cffDone:	xor	rax, rax

	add	rsp, 128
	add	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdCopyFiles	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	copy single file, handle progress, errors, options
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdCopyFile (pxApp, pxAction)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbCopyProgress	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 0
	sub	rsp, 128
	.allocstack	128 + 0
	.endprolog

;DWORD CALLBACK CopyProgressRoutine(
;  _In_      LARGE_INTEGER TotalFileSize,
;  _In_      LARGE_INTEGER TotalBytesTransferred,
;  _In_      LARGE_INTEGER StreamSize,
;  _In_      LARGE_INTEGER StreamBytesTransferred,
;  _In_      DWORD dwStreamNumber,
;  _In_      DWORD dwCallbackReason,
;  _In_      HANDLE hSourceFile,
;  _In_      HANDLE hDestinationFile,
;  _In_opt_  LPVOID lpData

	mov	rax, PROGRESS_CONTINUE

	add	rsp, 128
	add	rsp, 0

	pop	rbp

	ret	0

	align	4

cbCopyProgress	ENDP


cmdCopyFile	PROC	FRAME
	LOCAL	fCancel:QWORD	; true if copy was cancelled
	LOCAL	txPath [DEF_PATH_LENGTH]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * DEF_PATH_LENGTH
	sub	rsp, 128
	.allocstack	128 + 1 * 8 + 2 * DEF_PATH_LENGTH
	.endprolog

	; -- get parameter --

	mov	r14, rdx
	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- build target file --

	mov	rdx, [r14.CLASS_ACTION.ptxDest]
	lea	rcx, txPath
	call	lstrcpy

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	lstrlen

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
cpyGetFile:	test	rax, rax
	jz	cpyAppend

	dec	rax

	cmp	word ptr [rcx + 2 * rax], "\"
	je	cpyAppend

	jmp	cpyGetFile

cpyAppend:	lea	rdx, [rcx + 2 * rax]
	lea	rcx, txPath
	call	lstrcat

	mov	fCancel, 0

	lea	rax, fCancel
	mov	dword ptr [rsp + 40], 0
	mov	[rsp + 32], rax
	mov	r9, r12
	lea	r8, cbCopyProgress
	lea	rdx, txPath
	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	CopyFileExW
	test	eax, eax
	jnz	cpyDone

	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r14.CLASS_ACTION.ptxSource]
	mov	r8, rax
	mov	rdx, CMD_COPY
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	cpyExit

cpyDone:	mov	rax, 0

cpyExit:	add	rsp, 128
	add	rsp, 1 * 8 + 2 * DEF_PATH_LENGTH

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdCopyFile	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create single folder
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdCreateDir (pxApp, ptxCreate)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdCreateDir	PROC	FRAME
	LOCAL	ptxCreate:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + 8
	sub	rsp, 128
	.allocstack	128 + 8 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]
	mov	ptxCreate, rdx

	mov	rdx, 0
	mov	rcx, ptxCreate
	call	CreateDirectory
	test	eax, eax
	jnz	cdiDone

	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, ptxCreate
	mov	r8, rax
	mov	rdx, CMD_MKDIR
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	cdiExit

cdiDone:	xor	rax, rax

cdiExit:	add	rsp, 128
	add	rsp, 8 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdCreateDir	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	move selected files and folders - add selected files recursively to command list
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdMoveFiles ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdMoveFiles	PROC	FRAME
	LOCAL	xAction:CMD_ADD_ACTION	; action to add
	LOCAL	txBuffer [64]:WORD	; list window class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8
	sub	rsp, 128
	.allocstack	128 + sizeof CMD_ADD_ACTION + 64 * 2 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- show collect hint --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_MOVE_COLLECT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- add selected files recursively to command list --

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.pxApp], r12
	mov	[r9.CMD_ADD_ACTION.unFileAction], CMD_MOVE
	mov	[r9.CMD_ADD_ACTION.unDownAction], CMD_MKDIR
	mov	[r9.CMD_ADD_ACTION.unUpAction], CMD_DELETE

	mov	rax, [r15.CLASS_COMMAND.unGroup]
	mov	[r9.CMD_ADD_ACTION.unGroup], rax
	add	[r15.CLASS_COMMAND.unGroup], 1

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unSourcePos], rax

	mov	rcx, [r12.CLASS_APP.pxInactive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unTargetPos], rax

	mov	rdx, [r12.CLASS_APP.pxInactive]
	mov	rdx, [rdx.CLASS_LIST.ptxPath]
	lea	rcx, [r9.CMD_ADD_ACTION.txTarget]
	call	lstrcpy

	mov	qword ptr [rsp + 32], 1
	lea	r8, cbAddCmd
	lea	r9, xAction
	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]
	test	rax, rax
	jz	cmfRunMove

	; -- error or cancel during collection - clean task list --

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCleanTask]
	
	jmp	cmfCleanup

	; -- show process task list hint --

cmfRunMove:	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_MOVE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- start worker thread --

cmfCleanup:	mov	rcx, [r15.CLASS_COMMAND.hevStart]
	call	SetEvent

	xor	rax, rax

	add	rsp, 128
	add	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdMoveFiles	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	move single file - do copy, delete
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdMoveFile (pxApp, pxAction)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbMoveProgress	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 0
	sub	rsp, 128
	.allocstack	128 + 0
	.endprolog

;DWORD CALLBACK CopyProgressRoutine(
;  _In_      LARGE_INTEGER TotalFileSize,
;  _In_      LARGE_INTEGER TotalBytesTransferred,
;  _In_      LARGE_INTEGER StreamSize,
;  _In_      LARGE_INTEGER StreamBytesTransferred,
;  _In_      DWORD dwStreamNumber,
;  _In_      DWORD dwCallbackReason,
;  _In_      HANDLE hSourceFile,
;  _In_      HANDLE hDestinationFile,
;  _In_opt_  LPVOID lpData

	mov	rax, PROGRESS_CONTINUE

	add	rsp, 128
	add	rsp, 0

	pop	rbp

	ret	0

	align	4

cbMoveProgress	ENDP


cmdMoveFile	PROC	FRAME
	LOCAL	fCancel:QWORD	; true if copy was cancelled
	LOCAL	txPath [DEF_PATH_LENGTH]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * DEF_PATH_LENGTH
	sub	rsp, 128
	.allocstack	128 + 1 * 8 + 2 * DEF_PATH_LENGTH
	.endprolog

	; -- get parameter --

	mov	r14, rdx
	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- build target file --

	mov	rdx, [r14.CLASS_ACTION.ptxDest]
	lea	rcx, txPath
	call	lstrcpy

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	lstrlen

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
cmoGetFile:	test	rax, rax
	jz	cmoAppend

	dec	rax

	cmp	word ptr [rcx + 2 * rax], "\"
	je	cmoAppend

	jmp	cmoGetFile

cmoAppend:	lea	rdx, [rcx + 2 * rax]
	lea	rcx, txPath
	call	lstrcat

	mov	fCancel, 0

	lea	rax, fCancel
	mov	dword ptr [rsp + 40], 0
	mov	[rsp + 32], rax
	mov	r9, r12
	lea	r8, cbMoveProgress
	lea	rdx, txPath
	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	CopyFileExW
	test	eax, eax
	jnz	cmoDelete

	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r14.CLASS_ACTION.ptxSource]
	mov	r8, rax
	mov	rdx, CMD_MOVE
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	cmoExit

	; -- delete source file --

cmoDelete:	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	DeleteFileW
	test	eax, eax
	jnz	cmoDone

	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r14.CLASS_ACTION.ptxSource]
	mov	r8, rax
	mov	rdx, CMD_MOVE
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	cmoExit

cmoDone:	mov	rax, 0

cmoExit:	add	rsp, 128
	add	rsp, 1 * 8 + 2 * DEF_PATH_LENGTH

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdMoveFile	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	delete selected files and folders - add selected files recursively to command list
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdDeleteFiles ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdDeleteFiles	PROC	FRAME
	LOCAL	xAction:CMD_ADD_ACTION	; action to add
	LOCAL	txBuffer [64]:WORD	; list window class name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8
	sub	rsp, 128
	.allocstack	128 + sizeof CMD_ADD_ACTION + 64 * 2 + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- show collect hint --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_DELETE_COLLECT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- add selected files recursively to command list --

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.pxApp], r12
	mov	[r9.CMD_ADD_ACTION.unDownAction], CMD_EMPTY
	mov	[r9.CMD_ADD_ACTION.unFileAction], CMD_DELETE
	mov	[r9.CMD_ADD_ACTION.unUpAction], CMD_DELETE

	mov	rax, [r15.CLASS_COMMAND.unGroup]
	mov	[r9.CMD_ADD_ACTION.unGroup], rax
	add	[r15.CLASS_COMMAND.unGroup], 1

	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unSourcePos], rax

	mov	rcx, [r12.CLASS_APP.pxInactive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrlen

	lea	r9, xAction
	mov	[r9.CMD_ADD_ACTION.unTargetPos], rax

	mov	rdx, [r12.CLASS_APP.pxInactive]
	mov	rdx, [rdx.CLASS_LIST.ptxPath]
	lea	rcx, [r9.CMD_ADD_ACTION.txTarget]
	call	lstrcpy

	mov	qword ptr [rsp + 32], 1
	lea	r8, cbAddCmd
	lea	r9, xAction
	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]
	test	rax, rax
	jz	cdfRunMove

	; -- error or cancel during collection - clean task list --

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCleanTask]
	
	jmp	cdfCleanup

	; -- show process task list hint --

cdfRunMove:	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMD_DELETE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txBuffer
	mov	edx, ID_CP_STATE
	mov	rcx, [r12.CLASS_APP.hwndProgress]
	call	SetDlgItemText

	; -- start worker thread --

cdfCleanup:	mov	rcx, [r15.CLASS_COMMAND.hevStart]
	call	SetEvent

	xor	rax, rax

	add	rsp, 128
	add	rsp, sizeof CMD_ADD_ACTION + 64 * 2 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdDeleteFiles	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	delete single file
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdDeleteFile (pxApp, pxAction)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdDeleteFile	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 64
	.allocstack	64 + 8
	.endprolog

	; -- get parameter --

	mov	r14, rdx
	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- check read only, try to remove if present --

	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	GetFileAttributesW
	cmp	eax, INVALID_FILE_ATTRIBUTES
	je	cdeLastErr
	
	test	eax, FILE_ATTRIBUTE_DIRECTORY
	jnz	cdeRemDir
	test	eax, FILE_ATTRIBUTE_READONLY
	jz	cdeDelete

	and	eax, NOT FILE_ATTRIBUTE_READONLY
	mov	edx, eax
	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	SetFileAttributesW

	; -- delete source file --

cdeDelete:	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	DeleteFileW
	test	eax, eax
	jz	cdeLastErr

	jmp	cdeDone

	; -- delete if folder --

cdeRemDir:	mov	rcx, [r14.CLASS_ACTION.ptxSource]
	call	RemoveDirectoryW
	test	eax, eax
	jz	cdeLastErr

	jmp	cdeDone

	; -- handle file I/O errors --

cdeLastErr:	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r14.CLASS_ACTION.ptxSource]
	mov	r8, rax
	mov	rdx, CMD_MOVE
	mov	rcx, r15
	mov	rax, [r15.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	cdeExit

	; -- all done --

cdeDone:	mov	rax, 0

cdeExit:	add	rsp, 64
	add	rsp, 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdDeleteFile	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	rename selected files and folders - process list, open rename dialog for each
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cmdRename ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbRenCmd	PROC	FRAME
	LOCAL	ptxFile:QWORD	; current file name
	LOCAL	unMode:QWORD	; current process mode
	LOCAL	unPos:QWORD	; start of file name in path
	LOCAL	txPath [DEF_PATH_LENGTH]:WORD	; displayed file name
	LOCAL	txNew [DEF_PATH_LENGTH]:WORD	; new full path name

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH
	sub	rsp, 64
	.allocstack	64 + 3 * 8 + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH
	.endprolog

	; -- get parameter --

	mov	r12, [rbp + 3 * 8 + 32]
	mov	ptxFile, rcx
	mov	unMode, r8

	; -- get last part --

	mov	rcx, ptxFile
	call	lstrlen

	mov	rcx, ptxFile

crcLoop:	cmp	rax, 0
	jz	crcDone

	dec	rax
	cmp	word ptr [rcx + 2 * rax], "\"
	jne	crcLoop

	; -- put filename in editbox --

	mov	unPos, rax

	lea	rdx, [rcx + 2 * rax + 2]
	lea	rcx, txPath
	call	lstrcpy

	lea	rax, txPath
	mov	qword ptr [rsp + 32], rax
	lea	r9, dlgprcRename
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_RENAME
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	DialogBoxParam

	test	eax, eax
	jz	crcDone

	; -- rename ok, do rename --

	mov	rdx, ptxFile
	lea	rcx, txNew
	call	lstrcpy

	mov	rax, unPos

	lea	rdx, txPath
	lea	rcx, txNew
	lea	rcx, [rcx + 2 * rax + 2]
	call	lstrcpy

	lea	rdx, txNew
	mov	rcx, ptxFile
	call	MoveFile
	test	rax, rax
	jnz	crcDone

	call	GetLastError

	mov	qword ptr [rsp + 32], 0
	mov	r9, ptxFile
	mov	r8, rax
	mov	rdx, CMD_RENAME
	mov	rcx, r12
	mov	rcx, [r12.CLASS_APP.pxCommand]
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnHandleError]

	jmp	crcExit

crcDone:	xor	rax, rax

crcExit:	add	rsp, 64
	add	rsp, 3 * 8 + 2 * DEF_PATH_LENGTH + 2 * DEF_PATH_LENGTH

	pop	r12
	pop	rbp

	ret	0
	
	align	4

cbRenCmd	ENDP

cmdRename	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 64
	.allocstack	64
	.endprolog

	; -- get parameter --
	
	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- process selected files, no recursion --

	mov	qword ptr [rsp + 32], 0
	lea	r8, cbRenCmd
	mov	r9, r12
	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]
	
	add	rsp, 64

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdRename	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	add new operation to command list
; last update:	2013-06-06 - Deutsch - make x64
; parameters:	unError cbAddCmd (ptxFile, pxFind, unMode, unCount, pxUser)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbAddCmd	PROC	FRAME
	LOCAL	ptxFile:QWORD	; current file name
	LOCAL	pxFind:QWORD	; found file information
	LOCAL	unMode:QWORD	; current process mode
	LOCAL	pxEntry:QWORD	; new list entry, place at end

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 8
	sub	rsp, 128
	.allocstack	128 + 4 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	ptxFile, rcx
	mov	pxFind, rdx
	mov	unMode, r8
	mov	r14, [rbp + 5 * 8 + 32]
	mov	r12, [r14.CMD_ADD_ACTION.pxApp]
	mov	r15, [r12.CLASS_APP.pxCommand]
	test	r15, r15
	jz	cmdFreed

	; -- decide on operation --

	mov	rax, unMode
	cmp	rax, PROC_DIRDOWN
	je	cmdDirDown
	cmp	rax, PROC_FILE
	je	cmdAddAction
	cmp	rax, PROC_DIRUP
	je	cmdDirUp

	jmp	cmdDone

	; -- dive into sub directory / come back from sub directory - use as current target path --

cmdDirDown:	mov	rax, [r14.CMD_ADD_ACTION.unSourcePos]
	mov	rdx, ptxFile
	lea	rdx, [rdx + 2 * rax]
	lea	rcx, [r14.CMD_ADD_ACTION.txTarget]
	mov	rax, [r14.CMD_ADD_ACTION.unTargetPos]
	lea	rcx, [rcx + 2 * rax]
	call	lstrcpy

	; -- insert into task list --

	cmp	[r14.CMD_ADD_ACTION.unDownAction], CMD_EMPTY
	je	cmdSkip

	call	actionNew
	test	rax, rax
	jz	cmdExit

	mov	pxEntry, rax

	; -- initialize action --

	mov	rax, [r14.CMD_ADD_ACTION.unGroup]
	mov	qword ptr [rsp + 32], rax
	lea	r9, [r14.CMD_ADD_ACTION.txTarget]
	mov	r8, ptxFile
	mov	rdx, [r14.CMD_ADD_ACTION.unDownAction]
	mov	rcx, pxEntry
	mov	rax, [rcx.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnInit]
	test	rax, rax
	jnz	cmdExit

	jmp	cmdInsert

	; -- come back from sub directory - use as current target path --

cmdDirUp:	mov	rax, [r14.CMD_ADD_ACTION.unSourcePos]
	mov	rdx, ptxFile
	lea	rdx, [rdx + 2 * rax]
	lea	rcx, [r14.CMD_ADD_ACTION.txTarget]
	mov	rax, [r14.CMD_ADD_ACTION.unTargetPos]
	lea	rcx, [rcx + 2 * rax]
	call	lstrcpy

	; -- insert into task list --

	cmp	[r14.CMD_ADD_ACTION.unUpAction], CMD_EMPTY
	je	cmdSkip

	call	actionNew
	test	rax, rax
	jz	cmdExit

	mov	pxEntry, rax

	; -- initialize action --

	mov	rax, [r14.CMD_ADD_ACTION.unGroup]
	mov	qword ptr [rsp + 32], rax
	lea	r9, [r14.CMD_ADD_ACTION.txTarget]
	mov	r8, ptxFile
	mov	rdx, [r14.CMD_ADD_ACTION.unUpAction]
	mov	rcx, pxEntry
	mov	rax, [rcx.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnInit]
	test	rax, rax
	jnz	cmdExit

	jmp	cmdInsert

	; -- add action with current file --

cmdAddAction:	cmp	[r14.CMD_ADD_ACTION.unFileAction], CMD_EMPTY
	je	cmdSkip

	call	actionNew
	test	rax, rax
	jz	cmdExit

	mov	pxEntry, rax

	; -- initialize command --

	mov	rax, [r14.CMD_ADD_ACTION.unGroup]
	mov	qword ptr [rsp + 32], rax
	lea	r9, [r14.CMD_ADD_ACTION.txTarget]
	mov	r8, ptxFile
	mov	rdx, [r14.CMD_ADD_ACTION.unFileAction]
	mov	rcx, pxEntry
	mov	rax, [rcx.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnInit]
	test	rax, rax
	jnz	cmdExit

	; -- access command list, append at end --

cmdInsert:	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	EnterCriticalSection

	; -- add structure at end of linked list --

	lea	rax, [r15.CLASS_COMMAND.parrCommands]

cmdLoop:	mov	rcx, [rax]
	test	rcx, rcx
	jz	cmdAdd

	lea	rax, [rcx.CLASS_ACTION.pxNext]
	jmp	cmdLoop

	; -- add here --

cmdAdd:	mov	rcx, pxEntry
	mov	[rax], rcx

	; -- add progress into do be done list --

	mov	rdx, r12
	mov	rcx, pxEntry
	mov	rax, [rcx.CLASS_ACTION.vtableThis]
	call	[rax.CLASS_ACTION_IFACE.pfnSetProgress]

	lea	rcx, [r15.CLASS_COMMAND.xCritical]
	call	LeaveCriticalSection

	; -- check if user cancels current operation --

cmdSkip:	mov	rdx, 0
	mov	rcx, [r15.CLASS_COMMAND.hevUserBreak]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	jne	cmdDone

	mov	rax, ERROR_CANCELLED
	jmp	cmdExit

cmdFreed:	mov	rax, ERROR_INVALID_HANDLE
	jmp	cmdExit

cmdDone:	xor	rax, rax

cmdExit:	add	rsp, 128
	add	rsp, 4 * 8 + 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0
	
	align	4

cbAddCmd	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	goto root of given path
; last update:	2006-04-09 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cmdRoot ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdRoot	PROC	FRAME

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
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	; -- check drive letter or UNC --

	mov	rax, [r12.CLASS_APP.pxActive]
	mov	rax, [rax.CLASS_LIST.ptxPath]

	mov	cx, [rax + 0]
	cmp	cx, "\"
	jne	rotDrive
	mov	cx, [rax + 2]
	cmp	cx, "\"
	je	rotUnc

	; unknown type !

	; -- drive letter --

rotDrive:	mov	word ptr [rax + 2 * 3], 0
	jmp	rotUpdate

	; -- cut UNC path --

rotUnc:	lea	rax, [rax + 2 * 2]

rotLoop:	mov	cx, [rax]
	cmp	cx, 0
	je	rotDone
	cmp	cx, "\"
	je	rotCut

	add	rax, 2
	jmp	rotLoop

rotCut:	mov	word ptr [rax], 0

	; -- update all --

rotUpdate:	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

rotDone:	xor	rax, rax

	add	rsp, 32

	pop	r15
	pop	r12
	pop	rbp

	ret	0
	
	align	4

cmdRoot	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	list entry select/unselect callback
; last update:	2006-04-09 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cbSelect (unCount, pxUser)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbSelect	PROC	FRAME

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

	; -- change item --

	mov	r9, rcx
	mov	r15, [r8.CMD_SELECT_PARAM.pxThis]

	mov	[r9.LVITEM.lmask], LVIF_STATE
	mov	[r9.LVITEM.stateMask], LVIS_SELECTED

	cmp	[r8.CMD_SELECT_PARAM.fSelect], TRUE
	je	selSel

	and	[r9.LVITEM.state], NOT LVIS_SELECTED
	jmp	selSet

selSel:	or	[r9.LVITEM.state], LVIS_SELECTED

selSet:	mov	r8d, 0
	mov	edx, LVM_SETITEM
	mov	rcx, [r15.CLASS_LIST.hwndList]
	call	SendMessage

	xor	rax, rax

	add	rsp, 8
	add	rsp, 32

	pop	r15
	pop	rbp

	ret	0
	
	align	4

cbSelect	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for creating a new folder
; last update:	2004-02-17 - Brühl - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError dlgprcMakeDir (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcMakeDir	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	sub	rsp, 4 * 8
	.allocstack	32 + 4 * 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dmdInitDlg
	cmp	eax, WM_COMMAND
	je	dmdCmd
	cmp	eax, WM_CLOSE
	je	dmdClose

	jmp	dmdZero

	; -- init dialog --

dmdInitDlg:	mov	r8, lParam
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	rax, TRUE
	jmp	dmdExit

	; -- get directory text if ok --

dmdCmd:	mov	rax, wParam
	cmp	ax, IDOK
	je	dmdOk
	cmp	ax, IDCANCEL
	je	dmdClose

	jmp	dmdZero

	; -- ok - copy result string --

dmdOk:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr

	mov	r9d, DEF_PATH_LENGTH - 1
	mov	r8, rax
	mov	edx, ID_MK_NEWDIR
	mov	rcx, hwndDlg
	call	GetDlgItemText

	mov	rdx, TRUE
	mov	rcx, hwndDlg
	call	EndDialog

	mov	rax, TRUE
	jmp	dmdExit

	; -- close dialog --

dmdClose:	mov	rdx, FALSE
	mov	rcx, hwndDlg
	call	EndDialog

	mov	rax, TRUE
	jmp	dmdExit

dmdZero:	xor	rax, rax

dmdExit:	add	rsp, 32
	add	rsp, 4 * 8

	pop	rbp

	ret	0

	align	4

dlgprcMakeDir	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for file rename
; last update:	2004-02-17 - Brühl - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError dlgprcRename (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcRename	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	sub	rsp, 4 * 8
	.allocstack	32 + 4 * 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dmdInitDlg
	cmp	eax, WM_COMMAND
	je	dmdCmd
	cmp	eax, WM_CLOSE
	je	dmdClose

	jmp	dmdZero

	; -- init dialog --

dmdInitDlg:	mov	r8, lParam
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	r8, lParam
	mov	edx, ID_RM_FILENAME
	mov	rcx, hwndDlg
	call	SetDlgItemText

	mov	rax, TRUE
	jmp	dmdExit

	; -- get directory text if ok --

dmdCmd:	mov	rax, wParam
	cmp	ax, IDOK
	je	dmdOk
	cmp	ax, IDCANCEL
	je	dmdClose

	jmp	dmdZero

	; -- ok - copy result string --

dmdOk:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr

	mov	r9d, DEF_PATH_LENGTH - 1
	mov	r8, rax
	mov	edx, ID_RM_FILENAME
	mov	rcx, hwndDlg
	call	GetDlgItemText

	mov	rdx, TRUE
	mov	rcx, hwndDlg
	call	EndDialog

	mov	rax, TRUE
	jmp	dmdExit

	; -- close dialog --

dmdClose:	mov	rdx, FALSE
	mov	rcx, hwndDlg
	call	EndDialog

	mov	rax, TRUE
	jmp	dmdExit

dmdZero:	xor	rax, rax

dmdExit:	add	rsp, 32
	add	rsp, 4 * 8

	pop	rbp

	ret	0

	align	4

dlgprcRename	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	show error dialog and continue options
; last update:	2004-02-17 - Brühl - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError cmdHandleError (unCmd, unError, ptxFile)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdHandleError	PROC	FRAME
	LOCAL	unCmd:QWORD	; button dialog
	LOCAL	unError:QWORD	; occurred windows error code
	LOCAL	unResult:QWORD	; dialog result
	LOCAL	ptxFile:QWORD	; source file while failed operation
	LOCAL	ptxMessage:QWORD	; windows message text
	LOCAL	txBuffer [256]:WORD	; "error in command xyz"
	LOCAL	txButton1 [64]:WORD	; extra button 1
	LOCAL	txButton2 [64]:WORD	; extra button 2
	LOCAL	txButton3 [64]:WORD	; extra button 3
	LOCAL	xErrorDlg:TASKDIALOGCONFIG	; error dialog configuration
	LOCAL	xButtons [3]:TASKDIALOG_BUTTON	; extra buttons

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 128
	sub	rsp, 5 * 8 + 2 * 256 + 3 * 2 * 64 + sizeof TASKDIALOGCONFIG + (3 * (sizeof TASKDIALOG_BUTTON + 4)) + 8
	.allocstack	128 + 5 * 8 + 2 * 256 + 3 * 2 * 64 + sizeof TASKDIALOGCONFIG + (3 * (sizeof TASKDIALOG_BUTTON + 4)) + 8
	.endprolog

	; -- get parameter --

	mov	r15, rcx
	mov	r12, [r15.CLASS_COMMAND.pxApp]

	mov	unCmd, rdx
	mov	unError, r8
	mov	ptxFile, r9

	; -- check ignore mode --

	cmp	[r15.CLASS_COMMAND.fIgnore], 1
	jne	cheHandle

	mov	rax, ID_BTN_IGNORE
	jmp	cheExit

	; -- get system message --

cheHandle:	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 40], 0
	lea	rax, ptxMessage
	mov	[rsp + 32], rax
	mov	r9, [r12.CLASS_APP.unLang]
	mov	r8d, dword ptr unError
	mov	rdx, 0
	mov	ecx, FORMAT_MESSAGE_ALLOCATE_BUFFER OR FORMAT_MESSAGE_FROM_SYSTEM
	call	FormatMessage
	test	eax, eax
	jz	cheExit

	; -- prepare extra buttons --

	lea	r9, txButton1
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDERR_RETRY
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txButton2
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDERR_IGNORE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txButton3
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CMDERR_IGNORE_ALL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rcx, xButtons
	mov	[rcx.TASKDIALOG_BUTTON.nButtonID], ID_BTN_RETRY
	lea	rax, txButton1
	mov	[rcx.TASKDIALOG_BUTTON.pszButtonText], rax

	add	rcx, sizeof TASKDIALOG_BUTTON
	mov	[rcx.TASKDIALOG_BUTTON.nButtonID], ID_BTN_IGNORE
	lea	rax, txButton2
	mov	[rcx.TASKDIALOG_BUTTON.pszButtonText], rax

	add	rcx, sizeof TASKDIALOG_BUTTON
	mov	[rcx.TASKDIALOG_BUTTON.nButtonID], ID_BTN_IGNORE_ALL
	lea	rax, txButton3
	mov	[rcx.TASKDIALOG_BUTTON.pszButtonText], rax

	; -- prepare error dialog --

	lea	r9, txBuffer
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, unCmd
	add	rdx, IDS_ERROR_BASE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	rdx, sizeof TASKDIALOGCONFIG
	lea	rcx, xErrorDlg
	call	RtlZeroMemory

	lea	rcx, xErrorDlg
	mov	[rcx.TASKDIALOGCONFIG.cbSize], sizeof TASKDIALOGCONFIG
	mov	rax, [r12.CLASS_APP.hwndApp]
	mov	[rcx.TASKDIALOGCONFIG.hwndParent], rax
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rcx.TASKDIALOGCONFIG.hInstance], rax	
	mov	[rcx.TASKDIALOGCONFIG.dwFlags], TDF_USE_COMMAND_LINKS
	mov	[rcx.TASKDIALOGCONFIG.dwCommonButtons], TDCBF_CANCEL_BUTTON
	lea	rax, txBuffer
	mov	[rcx.TASKDIALOGCONFIG.pszWindowTitle], rax
	mov	word ptr [rcx.TASKDIALOGCONFIG.pszMainIcon], TD_ERROR_ICON
	mov	rax, ptxMessage
	mov	[rcx.TASKDIALOGCONFIG.pszMainInstruction], rax
	mov	rax, ptxFile
	mov	[rcx.TASKDIALOGCONFIG.pszContent], rax
	mov	[rcx.TASKDIALOGCONFIG.cButtons], 3
	lea	rax, xButtons
	mov	[rcx.TASKDIALOGCONFIG.pButtons], rax
	mov	[rcx.TASKDIALOGCONFIG.nDefaultButton], IDCANCEL

	; -- show error dialog --

	mov	r9, 0
	mov	r8, 0
	lea	rdx, unResult
	call	TaskDialogIndirect

	mov	rcx, ptxMessage
	call	LocalFree

	mov	rax, unResult

cheExit:	add	rsp, 128
	add	rsp, 5 * 8 + 2 * 256 + 3 * 2 * 64 + sizeof TASKDIALOGCONFIG + (3 * (sizeof TASKDIALOG_BUTTON + 4)) + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

cmdHandleError	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	show count of files / dirs and size
; last update:	2006-04-09 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cmdFileSize ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cmdFileSize	PROC	FRAME
	LOCAL	xParam:CMD_SIZE_PARAM

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof CMD_SIZE_PARAM + 8
	sub	rsp, 64
	.allocstack	64 + sizeof CMD_SIZE_PARAM + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- show info dialog --

	mov	qword ptr [rsp + 32], 0
	lea	r9, dlgprcBytes
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_BYTEINFO
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	CreateDialogParam

	; -- process all files --

	lea	r9, xParam
	mov	[r9.CMD_SIZE_PARAM.hwndDlg], rax
	mov	[r9.CMD_SIZE_PARAM.unFiles], 0
	mov	[r9.CMD_SIZE_PARAM.unDirs], 0
	mov	[r9.CMD_SIZE_PARAM.unSize], 0

	mov	qword ptr [rsp + 32], 1
	lea	r8, cbSize
	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnProcessActive]

	; -- update again after last file --

	lea	rax, xParam
	mov	[rsp + 32], rax
	mov	r9, 0
	mov	r8, PROC_VOID
	mov	rdx, 0
	mov	rcx, 0
	call	cbSize

	xor	rax, rax

	add	rsp, sizeof CMD_SIZE_PARAM + 8
	add	rsp, 64

	pop	r12
	pop	rbp

	ret	0
	
	align	4

cmdFileSize	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	count bytes, files and directories, update dialog
; last update:	2006-04-09 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	unError cbSize (ptxFile, pxFind, unMode, unCount, pxUser)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

cbSize	PROC	FRAME
	LOCAL	ptxFile:QWORD	; current file name
	LOCAL	pxFind:QWORD	; found file information
	LOCAL	unMode:QWORD	; current process mode
	LOCAL	txInfo [64]:WORD
	LOCAL	txSize [64]:WORD
	LOCAL	txMask [8]:WORD

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * 64 + 2 * 64 + 2 * 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 2 * 64 + 2 * 64 + 2 * 8
	.endprolog

	; -- get parameter --

	mov	ptxFile, rcx
	mov	pxFind, rdx
	mov	unMode, r8
	mov	r14, [rbp + 3 * 8 + 32]

	; -- branch on file type --

	mov	rax, unMode
	cmp	rax, PROC_VOID
	je	sizUpdate
	cmp	rax, PROC_DIRDOWN
	je	sizDir
	cmp	rax, PROC_FILE
	je	sizFile

	jmp	sizDone

	; -- count files and size --

sizFile:	inc	[r14.CMD_SIZE_PARAM.unFiles]

	mov	eax, [rdx.WIN32_FIND_DATA.nFileSizeHigh]
	mov	edx, [rdx.WIN32_FIND_DATA.nFileSizeLow]
	shl	rax, 32
	or	rax, rdx

	add	[r14.CMD_SIZE_PARAM.unSize], rax
	jmp	sizRefresh

	; -- count directories --

sizDir:	inc	[r14.CMD_SIZE_PARAM.unDirs]

	; -- refresh dialog each x. callback --

sizRefresh:
	mov	rax, [r14.CMD_SIZE_PARAM.unFiles]
	mov	rcx, CMD_SIZE_REFRESH
	cqo
	idiv	rcx
	test	rdx, rdx
	jnz	sizDone

	; -- update dialog texts --

sizUpdate:
	lea	rdx, txInfo
	lea	rcx, [r14.CMD_SIZE_PARAM.unSize]
	call	i64toa

	lea	rdx, txSize
	lea	rcx, txInfo
	call	toolDecPoints

	lea	r8, txSize
	mov	edx, ID_BI_BYTES
	mov	rcx, [r14.CMD_SIZE_PARAM.hwndDlg]
	call	SetDlgItemText

	; -- show file count --

	mov	txMask + 0, "%"
	mov	txMask + 2, "d"
	mov	txMask + 4, 0

	mov	r8, [r14.CMD_SIZE_PARAM.unFiles]
	lea	rdx, txMask
	lea	rcx, txSize
	call	wsprintf

	lea	r8, txSize
	mov	edx, ID_BI_FILES
	mov	rcx, [r14.CMD_SIZE_PARAM.hwndDlg]
	call	SetDlgItemText

	; -- show dir count --

	mov	r8, [r14.CMD_SIZE_PARAM.unDirs]
	lea	rdx, txMask
	lea	rcx, txSize
	call	wsprintf

	lea	r8, txSize
	mov	rdx, ID_BI_DIRECTORY
	mov	rcx, [r14.CMD_SIZE_PARAM.hwndDlg]
	call	SetDlgItemText

sizDone:	xor	rax, rax

	add	rsp, 3 * 8 + 2 * 64 + 2 * 64 + 2 * 8
	add	rsp, 32

	pop	r14
	pop	rbp

	ret	0
	
	align	4

cbSize	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for byte command
; last update:	2004-02-17 - Brühl - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError dlgprcBytes (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcBytes	PROC	FRAME
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
	sub	rsp, 32
	sub	rsp, 4 * 8 + 8
	.allocstack	32 + 4 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_COMMAND
	je	bytCmd
	cmp	eax, WM_CLOSE
	je	bytClose

	jmp	bytZero

	; -- close window on ok --

bytCmd:	mov	rax, wParam
	cmp	ax, IDOK
	jne	bytZero

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_CLOSE
	mov	rcx, hwndDlg
	call	SendMessage

	mov	rax, TRUE
	jmp	bytExit

	; -- close dialog --

bytClose:	mov	rcx, hwndDlg
	call	DestroyWindow

	mov	rax, TRUE
	jmp	bytExit

bytZero:	xor	rax, rax

bytExit:	add	rsp, 32
	add	rsp, 4 * 8 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

dlgprcBytes	ENDP

	END
