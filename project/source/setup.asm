;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - main setup application
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

	include	setup.inc
	include	windows.inc
	include	commctrl.inc
	include	objbase.inc
	include	ShObjIdl.inc
	include	shlobj.inc
	include	objidl.inc
	include	winreg.inc
	include	winnt.inc


;----------------------------------------------------------------------------------------------------------------------
;	 defines
;----------------------------------------------------------------------------------------------------------------------

dlgprcDirectory	proto	:QWORD, :DWORD, :QWORD, :QWORD
dlgprcOptions	proto	:QWORD, :DWORD, :QWORD, :QWORD
appPathMessage	proto	:QWORD, :QWORD, :DWORD, :DWORD, :QWORD, :DWORD
appGetOptions	proto	:QWORD, :QWORD


;----------------------------------------------------------------------------------------------------------------------
;	 data segment
;----------------------------------------------------------------------------------------------------------------------

	.data

xMainFiles	dq	IDR_BIN_FILE1, offset txMainExe
	dq	IDR_BIN_FILE2, offset txConfig
	dq	IDR_BIN_FILE3, offset txUninst
	dq	0

iidShellLinkW	dd	000214F9h
	dw	0, 0
	db	0C0h, 0, 0, 0, 0, 0, 0, 46h

xLinkCLSID	dd	00021401h
	dw	0, 0
	db	0C0h, 0, 0, 0, 0, 0, 0, 46h

xPersistIID	dd	0000010Bh
	dw	0, 0
	db	0C0h, 0, 0, 0, 0, 0, 0, 46h

txSlash	dw	"\", 0
szCaptFont	dw	"A", "r", "i", "a", "l", 0
txUninst	dw	"m", "i", "u", "n", "i", "n", "s", "t", ".", "e", "x", "e", 0
txConfig	dw	"m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "i", "n", "i", 0
szRegister	dw	"D", "l", "l", "R", "e", "g", "i", "s", "t", "e", "r", "S", "e", "r", "v", "e", "r", 0

txMicro	dw	"M", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", 0
txMainExe	dw	"m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "e", "x", "e", 0
txLink	dw	"M", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", ".", "l", "n", "k", 0


;--------------------------------------------------------
; registry data path info
;--------------------------------------------------------

txUninstall	dw	"S", "o", "f", "t", "w", "a", "r", "e", "\"
	dw	"M", "i", "c", "r", "o", "s", "o", "f", "t", "\"
	dw	"W", "i", "n", "d", "o", "w", "s", "\"
	dw	"C", "u", "r", "r", "e", "n", "t", "V", "e", "r", "s", "i", "o", "n", "\", "U", "n", "i", "n", "s", "t", "a", "l", "l", "\", "m", "i", "c", "r", "o", "m", "m", "a", "n", "d", "e", "r", 0
txDisplay	dw	"D", "i", "s", "p", "l", "a", "y", "N", "a", "m", "e", 0
txUnString	dw	"U", "n", "i", "n", "s", "t", "a", "l", "l", "S", "t", "r", "i", "n", "g", 0
txUninstCmd	dw	"%", "l", "s", "m", "i", "u", "n", "i", "n", "s", "t", ".", "e", "x", "e", 0


;----------------------------------------------------------------------------------------------------------------------
;	 code segment
;----------------------------------------------------------------------------------------------------------------------

	.code

;----------------------------------------------------------------------------------------------------------------------
; does:	main setup, init all required staff
; last update:	2003-10-13 - Scholz - created
;	2014-08-26 - Deutsch - make x64
; parameters:	exitcode appMain ()
; returns:	process return value
;----------------------------------------------------------------------------------------------------------------------

appMain	PROC	FRAME
	LOCAL	xCtrls:INITCOMMCTRLEX	; common controls initialize information

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof INITCOMMCTRLEX
	sub	rsp, 128
	.allocstack	128 + sizeof INITCOMMCTRLEX
	.endprolog

	; -- prepare comctl library --

	lea	rcx, xCtrls
	mov	[rcx.INITCOMMCTRLEX.dwSize], sizeof INITCOMMCTRLEX
	mov	[rcx.INITCOMMCTRLEX.dwICC], ICC_LISTVIEW_CLASSES OR ICC_BAR_CLASSES OR ICC_PROGRESS_CLASS OR ICC_STANDARD_CLASSES OR ICC_USEREX_CLASSES

	call	InitCommonControlsEx

	mov	edx, COINIT_MULTITHREADED
	mov	rcx, 0
	call	CoInitializeEx

	; -- allocate new main app object --

	call	appNew
	mov	r12, rax


	; -- run application --

	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnRun]

	; -- free object --

	call	GetProcessHeap

	mov	r8, r12
	mov	edx, 0
	mov	rcx, rax
	call	HeapFree

	call	CoUninitialize

	; -- end process --

	mov	rcx, 0
	call	ExitProcess

	; (we will never reach here ..)

	add	rsp, 128
	add	rsp, sizeof INITCOMMCTRLEX

	pop	r12
	pop	rbp

	ret	0

	align	4

appMain	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	create new application object
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	pxApp appNew ()
; returns:	new object or zero for error
;----------------------------------------------------------------------------------------------------------------------

appNew	PROC	FRAME

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 128
	.allocstack	128
	.endprolog

	; -- allocate and set vtable --

	call	GetProcessHeap
	test	rax, rax
	jz	appExit

	mov	r8, sizeof CLASS_INSTALL_APP
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	appExit

	lea	rcx, [rax.CLASS_INSTALL_APP.xInterface]
	mov	[rax.CLASS_INSTALL_APP.vtableThis], rcx

	lea	rdx, appRun
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnRun], rdx
	lea	rdx, appConfirmQuit
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit], rdx
	lea	rdx, appPathMessage
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnPathMessage], rdx
	lea	rdx, appGetOptions
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnGetOptions], rdx
	lea	rdx, appDoInstall
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnDoInstall], rdx
	lea	rdx, appEnableStep
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnEnableStep], rdx
	lea	rdx, appCopyAllFiles
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnCopyAllFiles], rdx
	lea	rdx, appCreateLink
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnCreateLink], rdx
	lea	rdx, appCreateMenu
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnCreateMenu], rdx
	lea	rdx, appPrepareUninstall
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnPrepareUninstall], rdx
	lea	rdx, appStepAndHook
	mov	[rcx.CLASS_INSTALL_APP_IFACE.pfnStepAndHook], rdx
		
appExit:	add	rsp, 128
	pop	rbp
	ret	0

	align	4

appNew	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	run main application, switch between dialogs
; last update:	2002-12-27 - Scholz - created
;	2013-02-20 - Deutsch - make x64
; parameters:	error appRun ()
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

appRun	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 128
	.allocstack	128 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- load resources --

	mov	rcx, 0
	call	GetModuleHandle
	mov	[r12.CLASS_INSTALL_APP.hinstApp], rax

	mov	edx, IDI_MAIN
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadIcon
	mov	[r12.CLASS_INSTALL_APP.hiconApp], rax

	mov	edx, IDI_HOOK
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadIcon
	mov	[r12.CLASS_INSTALL_APP.hiconHook], rax

	mov	edx, 0
	mov	rcx, 0
	call	LoadCursor
	mov	[r12.CLASS_INSTALL_APP.hcurArrow], rax

	lea	rax, szCaptFont
	mov	[rsp + 104], rax
	mov	dword ptr [rsp + 96], FF_ROMAN
	mov	dword ptr [rsp + 88], DEFAULT_QUALITY
	mov	dword ptr [rsp + 80], CLIP_DEFAULT_PRECIS
	mov	dword ptr [rsp + 72], OUT_DEFAULT_PRECIS
	mov	dword ptr [rsp + 64], DEFAULT_CHARSET
	mov	dword ptr [rsp + 56], FALSE
	mov	dword ptr [rsp + 48], FALSE
	mov	eax, 1
	mov	dword ptr [rsp + 40], eax
	mov	eax, FW_BOLD
	mov	dword ptr [rsp + 32], eax
	mov	r9d, 0
	mov	r8d, 0
	mov	edx, 0
	mov	ecx, 28
	call	CreateFont
	mov	[r12.CLASS_INSTALL_APP.hfontDialog], rax

	mov	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_DESKTOP OR SETUP_WITH_STARTMENU

	; -- show welcome dialog --

sesWelcome:	mov	[rsp + 32], r12
	lea	r9, dlgprcWelcome
	mov	r8, HWND_DESKTOP
	mov	edx, IDD_WELCOME
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	DialogBoxParam
	cmp	eax, SETUP_BREAK
	je	sesSuccess

	; -- show license screen --

sesLicense:	mov	[rsp + 32], r12
	lea	r9, dlgprcLicense
	mov	r8, HWND_DESKTOP
	mov	edx, IDD_LICENSE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	DialogBoxParam
	cmp	eax, SETUP_BREAK
	je	sesSuccess
	cmp	eax, SETUP_PREV
	je	sesWelcome

	; -- show path screen --

sesPath:	mov	[rsp + 32], r12
	lea	r9, dlgprcDirectory
	mov	r8, HWND_DESKTOP
	mov	edx, IDD_DIRECTORY
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	DialogBoxParam
	cmp	eax, SETUP_BREAK
	je	sesSuccess
	cmp	eax, SETUP_PREV
	je	sesLicense

	; -- install options --

sesOptions:	mov	[rsp + 32], r12
	lea	r9, dlgprcOptions
	mov	r8, HWND_DESKTOP
	mov	edx, IDD_OPTIONS
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	DialogBoxParam
	cmp	eax, SETUP_BREAK
	je	sesSuccess
	cmp	eax, SETUP_PREV
	je	sesPath

	; -- do and show progress --

	mov	[rsp + 32], r12
	lea	r9, dlgprcProgress
	mov	r8, HWND_DESKTOP
	mov	edx, IDD_PROGRESS
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	DialogBoxParam
	cmp	eax, SETUP_PREV
	je	sesOptions

sesSuccess:	xor	rax, rax

	add	rsp, 128
	add	rsp, 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appRun	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for welcome dialog
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	unError dlgprcWelcome (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;----------------------------------------------------------------------------------------------------------------------

dlgprcWelcome	PROC	FRAME
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
	je	welInit
	cmp	eax, WM_COMMAND
	je	welCommand
	cmp	eax, WM_CTLCOLORSTATIC
	je	welColor

	mov	rax, 0
	jmp	welExit

	; -- handle dialog init --

welInit:	mov	r12, lParam

	mov	qword ptr [rsp + 32], 1
	mov	r9, [r12.CLASS_INSTALL_APP.hfontDialog]
	mov	r8d, WM_SETFONT
	mov	edx, IDC_CAPTION
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	r8, [r12.CLASS_INSTALL_APP.hiconApp]
	mov	edx, GCLP_HICON
	mov	rcx, hwndDlg
	call	SetClassLongPtr

	mov	r8, r12
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	jmp	welHandled

	; -- handle commands --

welCommand:	mov	ax, word ptr wParam + 2
	cmp	ax, BN_CLICKED
	jne	welHandled

	mov	rax, wParam
	cmp	ax, IDC_NEXTPAGE
	je	welNextPage
	cmp	ax, IDCANCEL
	je	welUserExit

	jmp	welHandled

	; -- go to next page --

welNextPage:	mov	edx, SETUP_NEXT
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	welHandled

	; -- cancel installation --

welUserExit:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit]
	cmp	eax, IDYES
	jne	welHandled

	mov	edx, SETUP_BREAK
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	welHandled

	; -- handle background color --

welColor:	mov	ecx, WHITE_BRUSH
	call	GetStockObject
	jmp	welExit

	; -- all done --

welHandled:	mov	rax, 1

welExit:	add	rsp, 128
	add	rsp, 4 * 8 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

dlgprcWelcome	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for license text
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	unError dlgprcLicense (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;----------------------------------------------------------------------------------------------------------------------

dlgprcLicense	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	unSize:DWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	rsi
	.pushreg	rsi
	push	rdi
	.pushreg	rdi
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 5 * 8
	sub	rsp, 128
	.allocstack	128 + 5 * 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	licInit
	cmp	eax, WM_COMMAND
	je	licCommand

	mov	rax, 0
	jmp	licExit

	; -- handle dialog init --

licInit:	mov	r12, lParam

	mov	r8d, RT_RCDATA
	mov	edx, IDR_BIN_LICENSE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	FindResource
	mov	rdi, rax

	mov	rdx, rax
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	SizeofResource
	mov	unSize, eax

	call	GetProcessHeap
	test	rax, rax
	jz	licHandled

	mov	r8d, unSize
	add	r8d, 2

	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	licHandled

	mov	rsi, rax

	mov	rdx, rdi
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadResource

	mov	r8d, unSize
	mov	rdx, rax
	mov	rcx, rsi
	call	RtlCopyMemory

	mov	eax, unSize
	mov	word ptr [rsi + rax], 0

	mov	r8, rsi
	mov	edx, IDC_LIC_FIELD
	mov	rcx, hwndDlg
	call	SetDlgItemText

	mov	r8, r12
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	jmp	licHandled

	; -- handle commands --

licCommand:	cmp	word ptr wParam + 2, BN_CLICKED
	jne	licHandled

	mov	rax, wParam
	cmp	ax, IDC_PREVPAGE
	je	licPrevPage
	cmp	ax, IDC_NEXTPAGE
	je	licNextPage
	cmp	ax, IDCANCEL
	je	licUserExit

	jmp	licHandled

	; -- go to previous page --

licPrevPage:	mov	edx, SETUP_PREV
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	licHandled

	; -- go to next page --

licNextPage:	mov	edx, SETUP_NEXT
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	licHandled

	; -- cancel installation --

licUserExit:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit]
	cmp	eax, IDYES
	jne	licHandled

	mov	edx, SETUP_BREAK
	mov	rcx, hwndDlg
	call	EndDialog

	; -- all done --

licHandled:	mov	rax, TRUE

licExit:	add	rsp, 128
	add	rsp, 5 * 8

	pop	rdi
	pop	rsi
	pop	r12
	pop	rbp
	ret	0

	align	4

dlgprcLicense	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for progress
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	unError dlgprcProgress (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;----------------------------------------------------------------------------------------------------------------------

dlgprcProgress	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	txTitle [128]:WORD
	LOCAL	txText [128]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * 128 + 2 * 128 + 8
	sub	rsp, 128
	.allocstack	128 + 4 * 8 + 2 * 128 + 2 * 128 + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	proInit
	cmp	eax, WM_COMMAND
	je	proCommand

	mov	rax, 0
	jmp	proExit

	; -- init dialog --

proInit:	mov	r12, lParam

	mov	rax, FILE_COUNT
	inc	rax
	shl	rax, 16

	mov	qword ptr [rsp + 32], rax
	mov	r9d, 0
	mov	r8d, PBM_SETRANGE
	mov	edx, IDC_PROGRESSBAR
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	qword ptr [rsp + 32], 0
	mov	r9d, 1
	mov	r8d, PBM_SETSTEP
	mov	edx, IDC_PROGRESSBAR
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	r8, r12
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	jmp	proHandled

	; -- handle commands --

proCommand:	cmp	word ptr wParam + 2, BN_CLICKED
	jne	proHandled

	mov	rax, wParam
	cmp	ax, IDCANCEL
	je	proCancel
	cmp	ax, IDOK
	je	proOK
	cmp	ax, IDC_PREVPAGE
	je	proPrev

	jmp	proHandled

	; -- cancel pressed --

proCancel:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit]
	cmp	eax, IDYES
	jne	proHandled

	mov	edx, SETUP_BREAK
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	proHandled

	; -- ok - do install --

proOK:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnDoInstall]

	; -- separate success message --

	mov	r9d, 128
	lea	r8, txTitle
	mov	edx, IDS_SUCCESS_TITLE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, 128
	lea	r8, txText
	mov	edx, IDS_SUCCESS_TEXT
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, MB_OK OR MB_ICONINFORMATION
	lea	r8, txTitle
	lea	rdx, txText
	mov	rcx, hwndDlg
	call	MessageBox

	mov	edx, TRUE
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	proHandled

	; -- go one dialog back --

proPrev:	mov	edx, SETUP_PREV
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	proHandled

proHandled:	mov	rax, TRUE

proExit:	add	rsp, 128
	add	rsp, 4 * 8 + 2 * 128 + 2 * 128 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

dlgprcProgress	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	displays a message box for quit confirmation
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	idButton ConfirmQuit (pxApp, hwndDlg)
; returns:	resulting button id (IDNO, IDCANCEL)
;----------------------------------------------------------------------------------------------------------------------

appConfirmQuit	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	txTitle [128]:WORD
	LOCAL	txText [128]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 + 2 * 128 + 2 * 128
	sub	rsp, 128
	.allocstack	128 + 8 + 2 * 128 + 2 * 128
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx

	mov	r9d, 128
	lea	r8, txTitle
	mov	edx, IDS_CONFIRM_TITLE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, 128
	lea	r8, txText
	mov	edx, IDS_WANT_QUIT
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, MB_YESNO OR MB_ICONQUESTION
	lea	r8, txTitle
	lea	rdx, txText
	mov	rcx, hwndDlg
	call	MessageBox

	add	rsp, 128
	add	rsp, 8 + 2 * 128 + 2 * 128

	pop	r12
	pop	rbp
	ret	0

	align	4

appConfirmQuit	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	performs the complete installation procedure
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appDoInstall (pxApp, hwndDlg)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appDoInstall	PROC	FRAME
	LOCAL	hwndDlg:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * 128
	sub	rsp, 128
	.allocstack	128 + 1 * 8 + 2 * 128
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx

	lea	rdx, txSlash
	lea	rcx, [r12.CLASS_INSTALL_APP.txPath]
	call	lstrcat

	; -- step progress (1) --

	mov	r8d, IDC_STEP1
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnEnableStep]

	; -- copy installation files --

	lea	r8, xMainFiles
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnCopyAllFiles]

	; -- step progress (1 ok) --

	mov	r8d, IDC_HOOK1
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnStepAndHook]

	; -- install desktop link --

	test	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_DESKTOP
	je	dciFolder

	mov	r8d, IDC_STEP2
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnEnableStep]

	mov	qword ptr [rsp + 40], 1
	lea	rdx, txMicro
	mov	[rsp + 32], rdx
	lea	r9, txLink
	lea	r8, txMainExe
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnCreateLink]

	mov	r8d, IDC_HOOK2
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnStepAndHook]

	; -- install start menu --

dciFolder:	test	[r12.CLASS_INSTALL_APP.dqOptions], SETUP_WITH_STARTMENU
	je	dciUninst

	mov	r8d, IDC_STEP3
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnEnableStep]

	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnCreateMenu]

	mov	qword ptr [rsp + 40], 0
	lea	rdx, txMicro
	mov	[rsp + 32], rdx
	lea	r9, txLink
	lea	r8, txMainExe
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnCreateLink]

	mov	r8d, IDC_HOOK3
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnStepAndHook]

	; -- setup uninstall application --

dciUninst:	mov	r8d, IDC_STEP4
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnEnableStep]

	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnPrepareUninstall]

	mov	r8d, IDC_HOOK4
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnStepAndHook]

	add	rsp, 128
	add	rsp, 1 * 8 + 2 * 128

	pop	r12
	pop	rbp
	ret	0

	align	4

appDoInstall	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	begin next step and display progress text
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appEnableStep (pxApp, hwndDlg, idControl)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appEnableStep	PROC	FRAME
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

	; -- show progress --

	mov	edx, r8d
	mov	rcx, hwndDlg
	call	GetDlgItem

	mov	edx, TRUE
	mov	rcx, rax
	call	EnableWindow

	add	rsp, 128
	add	rsp, 1 * 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appEnableStep	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	end next step and display progress hook
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appStepAndHook (pxApp, hwndDlg, idHook)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appStepAndHook	PROC	FRAME
	LOCAL	hwndDlg:QWORD
	LOCAL	idHook:DWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx
	mov	idHook, r8d

	; -- show progress --

	mov	qword ptr [rsp + 32], 0
	mov	r9d, 1
	mov	r8d, PBM_DELTAPOS
	mov	edx, IDC_PROGRESSBAR
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	qword ptr [rsp + 32], 0
	mov	r9, [r12.CLASS_INSTALL_APP.hiconHook]
	mov	r8d, STM_SETICON
	mov	edx, idHook
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	edx, idHook
	mov	rcx, hwndDlg
	call	GetDlgItem

	mov	r8d, 1
	mov	rdx, 0
	mov	rcx, rax
	call	InvalidateRect

	mov	edx, idHook
	mov	rcx, hwndDlg
	call	GetDlgItem

	mov	rcx, rax
	call	UpdateWindow

	add	rsp, 128
	add	rsp, 2 * 8 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appStepAndHook	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	copies all files from list to the appropriate destination
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appCopyAllFiles (pxApp, hwndDlg, parrFiles)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appCopyAllFiles	PROC	FRAME
	LOCAL	hwndDlg:QWORD
	LOCAL	hresFile:QWORD
	LOCAL	unSize:DWORD
	LOCAL	hfileNew:QWORD
	LOCAL	unWritten:DWORD
	LOCAL	ptxMessage:QWORD
	LOCAL	txFile [1024]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 6 * 8 + 2 * 1024
	sub	rsp, 128
	.allocstack	128 + 6 * 8 + 2 * 1024
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx
	mov	r14, r8

	; -- loop file list --

cafLoop:	mov	rax, [r14]
	test	rax, rax
	je	cafSuccess

	; -- build file name --

	lea	rdx, [r12.CLASS_INSTALL_APP.txPath]
	lea	rcx, txFile
	call	lstrcpy

	mov	rdx, [r14 + 8]
	lea	rcx, txFile
	call	lstrcat

	; -- extract file from resource --

	mov	r8d, RT_RCDATA
	mov	rdx, [r14 + 0]
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	FindResource
	mov	hresFile, rax

	mov	rdx, hresFile
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	SizeOfResource
	mov	unSize, eax

	mov	qword ptr [rsp + 48], 0
	mov	dword ptr [rsp + 40], FILE_ATTRIBUTE_NORMAL
	mov	dword ptr [rsp + 32], CREATE_ALWAYS
	mov	r9, 0
	mov	r8d, 0
	mov	edx, GENERIC_WRITE
	lea	rcx, txFile
	call	CreateFile
	cmp	rax, INVALID_HANDLE_VALUE
	jne	cafClone

	call	GetLastError

	lea	rdx, ptxMessage
	mov	qword ptr [rsp + 48], 0
	mov	dword ptr [rsp + 40], 0
	mov	qword ptr [rsp + 32], rdx
	mov	r9d, 0
	mov	r8d, eax
	mov	rdx, 0
	mov	ecx, FORMAT_MESSAGE_ALLOCATE_BUFFER OR FORMAT_MESSAGE_FROM_SYSTEM
	call	FormatMessage

	mov	r9d, 1024
	lea	r8, txFile
	mov	edx, IDS_ERROR_TITLE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, MB_OK OR MB_ICONSTOP
	lea	r8, txFile
	mov	rdx, ptxMessage
	mov	rcx, hwndDlg
	call	MessageBox

	xor	rax, rax
	jmp	cafExit

cafClone:	mov	hfileNew, rax

	mov	rdx, hresFile
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadResource

	mov	qword ptr [rsp + 32], 0
	lea	r9, unWritten
	mov	r8d, unSize
	mov	rdx, rax
	mov	rcx, hfileNew
	call	WriteFile

	mov	rcx, hfileNew
	call	CloseHandle

cafSkip:	add	r14, 16
	jmp	cafLoop

cafSuccess:	mov	rax, 1

cafExit:	add	rsp, 128
	add	rsp, 6 * 8 + 2 * 1024

	pop	r14
	pop	r12
	pop	rbp
	ret	0

	align	4

appCopyAllFiles	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	creates a link in users environment (desktop / start menu)
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appCreateLink (pxApp, hwndDlg, ptxTarget, ptxLink, ptxName, fDesktop)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appCreateLink	PROC	FRAME
	LOCAL	hobjLink:QWORD
	LOCAL	hobjPersist:QWORD
	LOCAL	pxPidl:QWORD
	LOCAL	hwndDlg:QWORD
	LOCAL	ptxTarget:QWORD
	LOCAL	ptxLink:QWORD
	LOCAL	ptxName:QWORD
	LOCAL	fDesktop:DWORD
	LOCAL	txFile [1024]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8 * 8 + 2 * 1024 + 8
	sub	rsp, 128
	.allocstack	128 + 8 * 8 + 2 * 1024 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx
	mov	ptxTarget, r8
	mov	ptxLink, r9
	mov	rdx, [rbp + 3 * 8 + 32]
	mov	ptxName, rdx
	mov	rdx, [rbp + 3 * 8 + 40]
	mov	fDesktop, edx

	; -- build target path + executable --

	lea	rdx, [r12.CLASS_INSTALL_APP.txPath]
	lea	rcx, txFile
	call	lstrcpy

	mov	rdx, ptxTarget
	lea	rcx, txFile
	call	lstrcat

	; -- get link helper --

	lea	rdx, hobjLink
	mov	[rsp + 32], rdx
	lea	r9, iidShellLinkW
	mov	r8d, CLSCTX_INPROC_SERVER
	mov	rdx, 0
	lea	rcx, xLinkCLSID
	call	CoCreateInstance
	test	eax, eax
	jne	cdlExit

	lea	rdx, txFile
	mov	rcx, hobjLink
	mov	rax, [rcx]
	call	[rax.IShellLink.SetPath]

	mov	rdx, ptxName
	mov	rcx, hobjLink
	mov	rax, [rcx]
	call	[rax.IShellLink.SetDescription]

	lea	r8, hobjPersist
	lea	rdx, xPersistIID
	mov	rcx, hobjLink
	mov	rax, [rcx]
	call	[rax.IShellLink.QueryInterface]
	test	eax, eax
	jne	cdlFree

	; get target - either desktop or start menu

	cmp	fDesktop, 1
	je	cdlDesktop

	; -- build start menu target --

	lea	r8, pxPidl
	mov	edx, CSIDL_PROGRAMS
	mov	rcx, hwndDlg
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	cdlFree

	lea	rdx, txFile
	mov	rcx, pxPidl
	call	SHGetPathFromIDList

	lea	rcx, txFile
	call	lstrlen

	lea	rcx, txFile
	cmp	word ptr [rcx + 2 * rax - 2], "\"
	je	cslAppend

	mov	word ptr [rcx + 2 * rax], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

cslAppend:	lea	rdx, txMicro
	lea	rcx, txFile
	call	lstrcat

	lea	rcx, txFile
	call	lstrlen

	lea	rcx, txFile
	mov	word ptr [rcx + 2 * rax], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

	jmp	cdlCorrect

	; -- build desktop + link name --

cdlDesktop:	lea	r8, pxPidl
	mov	edx, CSIDL_DESKTOP
	mov	rcx, hwndDlg
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	cdlFree

	lea	rdx, txFile
	mov	rcx, pxPidl
	call	SHGetPathFromIDList

	lea	rcx, txFile
	call	lstrlen

	lea	rcx, txFile
	cmp	word ptr [rcx + 2 * rax - 2], "\"
	je	cdlCorrect

	mov	word ptr [rcx + 2 * rax], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

cdlCorrect:	mov	rdx, ptxLink
	lea	rcx, txFile
	call	lstrcat

cdlSave:	mov	r8d, 1
	lea	rdx, txFile
	mov	rcx, hobjPersist
	mov	rax, [rcx]
	call	[rax.IPersistFile.Save]

	mov	rcx, hobjPersist
	mov	rax, [rcx]
	call	[rax.IPersistFile.Release]

cdlFree:	mov	rcx, hobjLink
	mov	rax, [rcx]
	call	[rax.IShellLink.Release]

	xor	rax, rax

cdlExit:	add	rsp, 128
	add	rsp, 8 * 8 + 2 * 1024 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appCreateLink	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	creates a new folder in the start menu program environment
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appCreateMenu (pxApp, hwndDlg)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appCreateMenu	PROC	FRAME
	LOCAL	hwndDlg:QWORD
	LOCAL	pxPidl:QWORD
	LOCAL	txDrawer [128]:WORD
	LOCAL	txFile [1024]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 128 + 2 * 1024 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 8 + 2 * 128 + 2 * 1024 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx

	; -- get start menu folder --

	mov	r9d, 128
	lea	r8, txDrawer
	mov	edx, IDS_PRODUCTNAME
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	lea	r8, pxPidl
	mov	edx, CSIDL_PROGRAMS
	mov	rcx, hwndDlg
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	csfExit

	lea	rdx, txFile
	mov	rcx, pxPidl
	call	SHGetPathFromIDList

	lea	rcx, txFile
	call	lstrlen

	lea	rcx, txFile
	cmp	word ptr [rcx + 2 * rax - 2], "\"
	je	cslAppend

	mov	word ptr [rcx + 2 * rax], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

cslAppend:	lea	rdx, txDrawer
	lea	rcx, txFile
	call	lstrcat

	; -- check for exisiting folder --

	lea	rcx, txFile
	call	GetFileAttributes
	cmp	eax, 0FFFFFFFFh
	je	csfCreate
	test	eax, FILE_ATTRIBUTE_DIRECTORY
	je	csfCreate

	mov	rax, 1
	jmp	csfExit

	; -- create new directory --

csfCreate:	mov	rdx, 0
	lea	rcx, txFile
	call	CreateDirectory
	test	eax, eax
	je	csfExit

	mov	rax, 1

csfExit:	add	rsp, 128
	add	rsp, 2 * 8 + 2 * 128 + 2 * 1024 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appCreateMenu	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	setup registry information for uninstall
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	zero appPrepareUninstall (pxApp)
; returns:	zero for ok
;----------------------------------------------------------------------------------------------------------------------

appPrepareUninstall PROC	FRAME
	LOCAL	hkeyReg:QWORD
	LOCAL	unResult:DWORD
	LOCAL	txText [128]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 128 + 8
	sub	rsp, 128
	.allocstack	128 + 2 * 8 + 2 * 128 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- get registry key --

	lea	rdx, unResult
	mov	qword ptr [rsp + 64], rdx
	lea	rdx, hkeyReg
	mov	qword ptr [rsp + 56], rdx
	mov	qword ptr [rsp + 48], 0
	mov	dword ptr [rsp + 40], KEY_QUERY_VALUE OR KEY_WRITE OR KEY_CREATE_SUB_KEY
	mov	dword ptr [rsp + 32], REG_OPTION_NON_VOLATILE
	mov	r9, 0
	mov	r8d, 0
	lea	rdx, txUninstall
	mov	rcx, HKEY_CURRENT_USER
	call	RegCreateKeyEx
	cmp	eax, ERROR_SUCCESS
	jne	punError

	; --- set display string ---

	mov	r9d, 128
	lea	r8, txText
	mov	edx, IDS_PRODUCTNAME
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	lea	rdx, txText
	add	eax, eax
	add	eax, 2
	mov	[rsp + 40], eax
	mov	[rsp + 32], rdx
	mov	r9d, REG_SZ
	mov	r8d, 0
	lea	rdx, txDisplay
	mov	rcx, hkeyReg
	call	RegSetValueEx

	; --- set command string ---

	lea	r8, [r12.CLASS_INSTALL_APP.txPath]
	lea	rdx, txUninstCmd
	lea	rcx, txText
	call	wsprintf

	lea	rdx, txText
	add	eax, eax
	add	eax, 2
	mov	[rsp + 40], eax
	mov	[rsp + 32], rdx
	mov	r9d, REG_SZ
	mov	r8d, 0
	lea	rdx, txUnString
	mov	rcx, hkeyReg
	call	RegSetValueEx

	mov	rcx, hkeyReg
	call	RegCloseKey

	mov	rax, 1
	jmp	punExit

punError:	xor	rax, rax

punExit:	add	rsp, 128
	add	rsp, 2 * 8 + 2 * 128 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appPrepareUninstall ENDP

	END
