;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - main uninstall application
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
	include	shlobj.inc
	include	objbase.inc
	include	shellapi.inc
	include	winreg.inc

IDS_CONFIRM_TITLE	equ	10000
IDS_CONFIRM_TEXT	equ	10001
IDS_DONE_TEXT		equ	10002

;----------------------------------------------------------------------------------------------------------------------
;	data segment
;----------------------------------------------------------------------------------------------------------------------

	.data

txDelete	dw	"m", "i", "u", 0
txFormat	dw	"%", "s", " ", "%", "d", " ", "%", "s", 0
txMainApp	dw	"\", "m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "e", "x", "e", 0
txConfig	dw	"\", "m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "i", "n", "i", 0
txMenu	dw	"\", "M", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", 0
txLink	dw	"\", "M", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "l", "n", "k", 0

txUninstall	dw	"S", "o", "f", "t", "w", "a", "r", "e", "\"
	dw	"M", "i", "c", "r", "o", "s", "o", "f", "t", "\"
	dw	"W", "i", "n", "d", "o", "w", "s", "\"
	dw	"C", "u", "r", "r", "e", "n", "t", "V", "e", "r", "s", "i", "o", "n", "\", "U", "n", "i", "n", "s", "t", "a", "l", "l", "\", "m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", 0


;----------------------------------------------------------------------------------------------------------------------
;	code segment
;----------------------------------------------------------------------------------------------------------------------

	.code


;----------------------------------------------------------------------------------------------------------------------
; does:	main uninstall, prepare uninstall
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appMain ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appMain	PROC	FRAME
	LOCAL	hinstApp:QWORD
	LOCAL	idProc:QWORD
	LOCAL	txPath [1024]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 1024 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 8 + 2 * 1024 + 8
	.endprolog

	; -- prepare comctl library --

	mov	edx, COINIT_MULTITHREADED
	mov	rcx, 0
	call	CoInitializeEx

	mov	rcx, 0
	call	GetModuleHandle
	mov	hinstApp, rax

	lea	rdx, txPath
	lea	rcx, idProc
	call	appCmdLine
	test	rax, rax
	jne	unsClone

	; -- confirm uninstall --

	mov	r8, MB_OKCANCEL OR MB_ICONINFORMATION
	mov	rdx, IDS_CONFIRM_TEXT
	mov	rcx, hinstApp
	call	appShowMsg
	cmp	rax, IDCANCEL
	je	unsExit

	; -- clone process to be able to delete original executable --

	mov	rcx, hinstApp
	call	appCloneProcess
	jmp	unsExit

	; -- delete original uninstaller --

unsClone:	mov	edx, INFINITE
	mov	rcx, idProc
	call	WaitForSingleObject

	mov	rcx, idProc
	call	CloseHandle

	lea	rcx, txPath
	call	DeleteFile

	; -- snip path --

	lea	rcx, txPath
	call	lstrlen

	lea	rcx, txPath
unsLoop:	cmp	word ptr [rcx + 2 * rax], "\"
	je	unsZero

	dec	rax
	jne	unsLoop
	jmp	unsExit

unsZero:	mov	word ptr [rcx + 2 * rax], 0

	; -- delete files --

	lea	rcx, txPath
	call	appRemApp

	mov	r8, MB_OK
	mov	rdx, IDS_DONE_TEXT
	mov	rcx, hinstApp
	call	appShowMsg

	call	CoUninitialize

unsExit:	mov	rcx, 0
	call	ExitProcess

	; (we will never reach here ..)

	add	rsp, 128
	add	rsp, 2 * 8 + 2 * 1024 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appMain	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	main uninstall, prepare uninstall
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appMain ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appCmdLine	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	push	r13
	.pushreg	r13
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 32
	.allocstack	32
	.endprolog

	; -- get process number from command line --

	mov	r12, rcx
	mov	r14, rdx
	mov	qword ptr [rcx], 0

	call	GetCommandLine

	mov	rdx, 0
	mov	cx, '"'

	cmp	word ptr [rax], cx
	je	ccoScan

	mov	cx, " "

ccoScan:	inc	rdx
	cmp	word ptr [rax + 2 * rdx], 0
	je	ccoBreak
	cmp	word ptr [rax + 2 * rdx], cx
	jne	ccoScan

ccoStep:	inc	rdx
	mov	cx, [rax + 2 * rdx]
	test	cx, cx
	je	ccoBreak
	cmp	cx, " "
	je	ccoStep

	; -- convert process ID --

ccoSkip:	inc	rdx
	cmp	word ptr [rax + 2 * rdx], " "
	jne	ccoSkip

	lea	r13, [rax + 2 * rdx + 2]
	lea	r15, [rax + 2 * rdx - 2]

	mov	rax, 0
	mov	rdx, 1

ccoLoop:	cmp	word ptr [r15], " "
	je	ccoPath

	mov	ax, [r15]
	sub	ax, "0"
	sub	r15, 2

	imul	rax, rdx
	add	qword ptr [r12], rax
	imul	rdx, 10
	jmp	ccoLoop

	; --- pick up file path ---

ccoPath:	mov	rdx, r13
	mov	rcx, r14
	call	lstrcpyW

	mov	rax, 1
	jmp	ccoExit

ccoBreak:	xor	rax, rax

ccoExit:	add	rsp, 32

	pop	r13
	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

appCmdLine	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	display a message box with strings from resource
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appMain ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appShowMsg	PROC	FRAME
	LOCAL	txTitle [128]:WORD
	LOCAL	txText [128]:WORD

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
	sub	rsp, 2 * 128 + 2 * 128 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 128 + 2 * 128 + 8
	.endprolog

	; -- separate success message --

	mov	r12, rcx
	mov	r14, rdx
	mov	r15, r8

	mov	r9d, 128
	lea	r8, txTitle
	mov	edx, IDS_CONFIRM_TITLE
	mov	rcx, r12
	call	LoadString

	mov	r9d, 128
	lea	r8, txText
	mov	rdx, r14
	mov	rcx, r12
	call	LoadString

	mov	r9, r15
	lea	r8, txTitle
	lea	rdx, txText
	mov	rcx, 0
	call	MessageBox

	add	rsp, 128
	add	rsp, 2 * 128 + 2 * 128 + 8

	pop	r15
	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

appShowMsg	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	displays the system dependend message if an error occurs
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appShowLastErr ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appShowLastErr	PROC	FRAME
	LOCAL	ptxMessage:QWORD
	LOCAL	txTitle [128]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 128 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 128 + 8
	.endprolog

	mov	r12, rcx

	; -- get windows error text from error number --

	call	GetLastError

	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 40], 0
	lea	rcx, ptxMessage
	mov	qword ptr [rsp + 32], rcx
	mov	r9d, 0
	mov	r8d, eax
	mov	rdx, 0
	mov	ecx, FORMAT_MESSAGE_ALLOCATE_BUFFER OR FORMAT_MESSAGE_FROM_SYSTEM
	call	FormatMessage

	mov	r9d, 128
	lea	r8, txTitle
	mov	edx, IDS_CONFIRM_TITLE
	mov	rcx, r12
	call	LoadString

	mov	r9d, MB_OK OR MB_ICONSTOP
	lea	r8, txTitle
	mov	rdx, ptxMessage
	mov	rcx, 0
	call	MessageBox

	add	rsp, 128
	add	rsp, 2 * 128 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appShowLastErr	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	initiates the second process for uninstalling - makes a clone in temp directory and starts a second process
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appCloneProcess ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appCloneProcess	PROC	FRAME
	LOCAL	idProc:QWORD
	LOCAL	pxProcess:QWORD
	LOCAL	txTemp [1024]:WORD
	LOCAL	txPath [128]:WORD
	LOCAL	txCmd [1024]:WORD
	LOCAL	xStartup:STARTUPINFO

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 1024 + 2 * 128 + 2 * 1024 + sizeof STARTUPINFO + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 8 + 2 * 1024 + 2 * 128 + 2 * 1024 + sizeof STARTUPINFO + 8
	.endprolog

	mov	r12, rcx

	mov	edx, sizeof STARTUPINFO
	lea	rcx, xStartup
	call	RtlZeroMemory

	; -- get module name --

	mov	r8d, 1024
	lea	rdx, txPath
	mov	rcx, 0
	call	GetModuleFileName

	; -- get temp path and file --

	lea	rdx, txTemp
	mov	ecx, 1024
	call	GetTempPath

	lea	r9, txTemp
	mov	r8, 0
	lea	rdx, txDelete
	lea	rcx, txTemp
	call	GetTempFileName

	; -- copy myself --

	mov	r8d, 0
	lea	rdx, txTemp
	lea	rcx, txPath
	call	CopyFile

	call	GetCurrentProcessId

 	mov	r8d, eax
 	mov	edx, 1
 	mov	ecx, SYNCHRONIZE
	call	OpenProcess
	mov	idProc, rax

	lea	rax, txPath
	mov	qword ptr [rsp + 32], rax
	mov	r9, idProc
	lea	r8, txTemp
	lea	rdx, txFormat
	lea	rcx, txCmd
	call	wsprintf

	lea	rax, xStartup
	mov	dword ptr [rax.STARTUPINFO.cb], sizeof STARTUPINFO

	lea	rax, pxProcess
	mov	qword ptr [rsp + 72], rax
	lea	rax, xStartup
	mov	qword ptr [rsp + 64], rax
	mov	qword ptr [rsp + 56], 0
	mov	qword ptr [rsp + 48], 0
	mov	qword ptr [rsp + 40], 0
	mov	qword ptr [rsp + 32], 1
	mov	r9, 0
	mov	r8, 0
	lea	rdx, txCmd
	mov	rcx, 0
	call	CreateProcess
	test	rax, rax
	jnz	cprFree

	mov	rcx, r12
	call	appShowLastErr

cprFree:	mov	rcx, idProc
	call	CloseHandle

	add	rsp, 128
	add	rsp, 2 * 8 + 2 * 1024 + 2 * 128 + 2 * 1024 + sizeof STARTUPINFO + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appCloneProcess	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	removes all files, links and registry entries from the current installation
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appCloneProcess ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appRemApp	PROC	FRAME
	LOCAL	pidlPath:QWORD
	LOCAL	txPath [1024]:WORD
	LOCAL	xFolder:SHFILEOPSTRUCT

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + 2 * 1024 + sizeof SHFILEOPSTRUCT + 8
	sub	rsp, 128
	.allocstack	128 + 8 + 2 * 1024 + sizeof SHFILEOPSTRUCT + 8
	.endprolog

	mov	r12, rcx

	; -- remove uninstall information --

	lea	rdx, txUninstall
	mov	rcx, HKEY_LOCAL_MACHINE
	call	RegDeleteKey

	; -- remove main executable --

	mov	rdx, r12
	lea	rcx, txPath
	call	lstrcpy

	lea	rdx, txMainApp
	lea	rcx, txPath
	call	lstrcat

	lea	rcx, txPath
	call	DeleteFile

	; -- remove configuration INI --

	mov	rdx, r12
	lea	rcx, txPath
	call	lstrcpy

	lea	rdx, txConfig
	lea	rcx, txPath
	call	lstrcat

	lea	rcx, txPath
	call	DeleteFile

	; -- remove program directory --

	mov	rdx, r12
	lea	rcx, txPath
	call	lstrcpy

	lea	rcx, txPath
	call	RemoveDirectory

	; -- delete start menu entry --

	lea	r8, pidlPath
	mov	edx, CSIDL_PROGRAMS
	mov	rcx, 0
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	rmsDone

	lea	rdx, txPath
	mov	rcx, pidlPath
	call	SHGetPathFromIDList

	lea	rdx, txMenu
	lea	rcx, txPath
	call	lstrcat

	lea	rcx, txPath
	call	lstrlen

	lea	rcx, txPath
	mov	word ptr [rcx + 2 * rax + 2], 0

	lea	rax, txPath
	lea	rcx, xFolder
	mov	qword ptr [rcx.SHFILEOPSTRUCT.hwnd], 0
	mov	qword ptr [rcx.SHFILEOPSTRUCT.wFunc], FO_DELETE
	mov	qword ptr [rcx.SHFILEOPSTRUCT.pFrom], rax
	mov	qword ptr [rcx.SHFILEOPSTRUCT.pTo], 0
	mov	word ptr [rcx.SHFILEOPSTRUCT.fFlags], 0
	mov	dword ptr [rcx.SHFILEOPSTRUCT.fAnyOperationsAborted], 0
	mov	qword ptr [rcx.SHFILEOPSTRUCT.hNameMappings], 0
	mov	qword ptr [rcx.SHFILEOPSTRUCT.lpszProgressTitle], 0
	call	SHFileOperation

	; -- delete desktop link --

	lea	r8, pidlPath
	mov	edx, CSIDL_DESKTOP
	mov	rcx, 0
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	rmsDone

	lea	rdx, txPath
	mov	rcx, pidlPath
	call	SHGetPathFromIDList

	lea	rdx, txLink
	lea	rcx, txPath
	call	lstrcat

	lea	rcx, txPath
	call	DeleteFile

rmsDone:	add	rsp, 128
	add	rsp, 8 + 2 * 1024 + sizeof SHFILEOPSTRUCT + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appRemApp	ENDP

	END
