;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - main application class
; note:	copyright © by digital performance 1997 - 2014, author S. Deutsch, A. Voelskow
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
;
; general register usage:
;	r12 .. holds main app object
;	r14 .. holds local structures
;	r15 .. holds local object
;
;------------------------------------------------------------------------------------------------------------------------------------------

	include	windows.inc
	include	commctrl.inc

	include	app.inc
	include	button.inc
	include	command.inc
	include	config.inc
	include	edit.inc
	include	list.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new application object
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	pxApp appNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

appNew	PROC	FRAME

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
	jz	appExit

	mov	r8, sizeof CLASS_APP
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	appExit

	; -- prepare vtable --

	lea	rcx, [rax.CLASS_APP.xInterface]
	mov	[rax.CLASS_APP.vtableThis], rcx

	lea	rdx, appInit
	mov	[rcx.CLASS_APP_IFACE.pfnInit], rdx
	lea	rdx, appRun
	mov	[rcx.CLASS_APP_IFACE.pfnRun], rdx
	lea	rdx, appRelease
	mov	[rcx.CLASS_APP_IFACE.pfnRelease], rdx
	lea	rdx, appInitLogo
	mov	[rcx.CLASS_APP_IFACE.pfnInitLogo], rdx
	lea	rdx, appInitButtons
	mov	[rcx.CLASS_APP_IFACE.pfnInitButtons], rdx
	lea	rdx, appFindButton
	mov	[rcx.CLASS_APP_IFACE.pfnFindButton], rdx
	lea	rdx, appMatchShortcut
	mov	[rcx.CLASS_APP_IFACE.pfnMatchShortcut], rdx
	lea	rdx, appLoadString
	mov	[rcx.CLASS_APP_IFACE.pfnLoadString], rdx
	lea	rdx, appGetConfigPath
	mov	[rcx.CLASS_APP_IFACE.pfnGetConfigPath], rdx
	lea	rdx, appLoadConfig
	mov	[rcx.CLASS_APP_IFACE.pfnLoadConfig], rdx
	lea	rdx, appSaveConfig
	mov	[rcx.CLASS_APP_IFACE.pfnSaveConfig], rdx
	lea	rdx, appSaveWinConfig
	mov	[rcx.CLASS_APP_IFACE.pfnSaveWinConfig], rdx
	lea	rdx, appCreateViewFont
	mov	[rcx.CLASS_APP_IFACE.pfnCreateViewFont], rdx
	lea	rdx, appSetPath
	mov	[rcx.CLASS_APP_IFACE.pfnSetPath], rdx
	lea	rdx, appSetStatus
	mov	[rcx.CLASS_APP_IFACE.pfnSetStatus], rdx
	lea	rdx, appSetActive
	mov	[rcx.CLASS_APP_IFACE.pfnSetActive], rdx
	lea	rdx, appProcessActive
	mov	[rcx.CLASS_APP_IFACE.pfnProcessActive], rdx
	lea	rdx, appToggleMenu
	mov	[rcx.CLASS_APP_IFACE.pfnToggleMenu], rdx
	lea	rdx, appSetMenuState
	mov	[rcx.CLASS_APP_IFACE.pfnSetMenuState], rdx
	lea	rdx, appSetStatusCmd
	mov	[rcx.CLASS_APP_IFACE.pfnSetStatusCmd], rdx
	lea	rdx, appHandleEvent
	mov	[rcx.CLASS_APP_IFACE.pfnHandleEvent], rdx
	lea	rdx, appResize
	mov	[rcx.CLASS_APP_IFACE.pfnResize], rdx
	lea	rdx, appFillList
	mov	[rcx.CLASS_APP_IFACE.pfnFillList], rdx
	lea	rdx, appConfirmClose
	mov	[rcx.CLASS_APP_IFACE.pfnConfirmClose], rdx

appExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

appNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	init application - user interface, threading, child windows
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	unError appInit ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appInit	PROC	FRAME
	LOCAL	xClass:WNDCLASSEX	; class info
	LOCAL	rcApp:RECT	; main window position
	LOCAL	txClass [64]:WORD	; class name
	LOCAL	txTitle [64]:WORD	; window title mask
	LOCAL	txVerMask [64]:WORD
	LOCAL	unCount:QWORD	; written bytes
	LOCAL	xPlacement:WINDOWPLACEMENT

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * 64 + 2 * 64 + 2 * 64 + sizeof WNDCLASSEX + sizeof RECT + sizeof WINDOWPLACEMENT + 4 + 8
	sub	rsp, 128
	.allocstack	128 + 1 * 8 + 2 * 64 + 2 * 64 + 2 * 64 + sizeof WNDCLASSEX + sizeof RECT + sizeof WINDOWPLACEMENT + 4 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- show logo --

	mov	rcx, 0
	call	GetModuleHandle
	mov	[r12.CLASS_APP.hinstApp], rax

	mov	[r12.CLASS_APP.unLang], SUBLANG_DEFAULT SHL 10 OR LANG_GERMAN

	mov	rdx, 1000
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnInitLogo]
	test	rax, rax
	jnz	appExit

	; -- init main members --

	lea	r14, xClass

	mov	edx, sizeof WNDCLASSEX
	mov	rcx, r14
	call	RtlZeroMemory

	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[r14.WNDCLASSEX.hInstance], rax

	; -- init window class --

	mov	rdx, IDI_APP
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadIcon

	mov	[r12.CLASS_APP.hiconApp], rax
	mov	[r14.WNDCLASSEX.hIcon], rax
	mov	[r14.WNDCLASSEX.hIconSm], rax

	mov	rdx, IDC_ARROW
	mov	rcx, 0
	call	LoadCursor
	mov	[r14.WNDCLASSEX.hCursor], rax

	lea	r9, txClass
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_APPWINCLASS
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	; -- prepare class --

	lea	rax, txClass
	lea	rcx, wndprcApp
	mov	[r14.WNDCLASSEX.cbSize], sizeof WNDCLASSEX
	mov	[r14.WNDCLASSEX.style], CS_HREDRAW OR CS_VREDRAW
	mov	[r14.WNDCLASSEX.lpfnWndProc], rcx
	mov	[r14.WNDCLASSEX.lpszClassName], rax
	mov	[r14.WNDCLASSEX.hbrBackground], COLOR_BTNFACE + 1

	mov	rcx, r14
	call	RegisterClassEx

	; -- check and create default config --

	call	configNew
	mov	[r12.CLASS_APP.pxConfig], rax

	mov	rdx, r12
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnInit]

	lea	r9, [r12.CLASS_APP.txSection]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_CFG_PARAM
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	; -- init main app window --

	lea	r9, txTitle
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_APPTITLE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txVerMask
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_VERMASK
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rcx, txTitle
	call	lstrlen
	mov	unCount, rax

	; -- get exe version --

	mov	r8, RT_VERSION
	mov	rdx, IDV_VERSION
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	FindResource

	mov	rdx, rax
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadResource

	mov	rcx, rax
	call	LockResource

	add	rax, 6 + 30 + 4 + 8
	movzx	r9d, word ptr [rax]
	movzx	r8d, word ptr [rax + 2]

	; -- append version to title --

	mov	rax, unCount
	lea	rcx, txTitle
	lea	rcx, [rcx + 2 * rax]

	lea	rdx, txVerMask
	call	wsprintf

	; -- get application configuration --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadConfig]
	test	rax, rax
	jnz	appExit

	; -- load buttons --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnInitButtons]
	test	rax, rax
	jnz	appExit

	; -- load main menu --

	mov	edx, IDM_APP
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadMenu
	mov	[r12.CLASS_APP.hmenuApp], rax

	; -- create main window --

	mov	qword ptr [rsp + 88], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rsp + 80], rax
	mov	rax, [r12.CLASS_APP.hmenuApp]
	mov	[rsp + 72], rax
	mov	qword ptr [rsp + 64], 0
	mov	eax, [r12.CLASS_APP.rcMain.RECT.bottom]
	cmp	eax, CW_USEDEFAULT
	je	appDefWin1
	sub	eax, [r12.CLASS_APP.rcMain.RECT.top]
appDefWin1:	mov	[rsp + 56], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.right]
	cmp	eax, CW_USEDEFAULT
	je	appDefWin2
	sub	eax, [r12.CLASS_APP.rcMain.RECT.left]
appDefWin2:	mov	[rsp + 48], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.top]
	mov	[rsp + 40], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.left]
	mov	[rsp + 32], eax
	mov	r9d, WS_OVERLAPPEDWINDOW OR WS_CLIPCHILDREN
	lea	r8, txTitle
	lea	rdx, txClass
	mov	ecx, 0
	call	CreateWindowEx
	test	rax, rax
	jz	appFail

	mov	[r12.CLASS_APP.hwndApp], rax

	mov	r8, r12
	mov	edx, GWLP_USERDATA
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SetWindowLongPtr

	; -- create list objects --

	call	listNew
	mov	[r12.CLASS_APP.pxLeftList], rax

	call	listNew
	mov	[r12.CLASS_APP.pxRightList], rax

	; -- initialize lists --

	mov	r9, r12
	lea	r8, [r12.CLASS_APP.txLeft]
	mov	rdx, IDC_LEFT
	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnInit]
	test	rax, rax
	jnz	appExit

	mov	r9, r12
	lea	r8, [r12.CLASS_APP.txRight]
	mov	rdx, IDC_RIGHT
	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnInit]
	test	rax, rax
	jnz	appExit

	; -- create edit fields --

	call	pathNew
	mov	[r12.CLASS_APP.pxLeftPath], rax

	call	pathNew
	mov	[r12.CLASS_APP.pxRightPath], rax

	mov	r8, r12
	mov	rdx, IDC_LEFTPATH
	mov	rcx, [r12.CLASS_APP.pxLeftPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnInit]
	test	rax, rax
	jnz	appExit

	mov	r8, r12
	mov	rdx, IDC_RIGHTPATH
	mov	rcx, [r12.CLASS_APP.pxRightPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnInit]
	test	rax, rax
	jnz	appExit

	; -- create status bar --

	mov	r9d, IDC_STATUS
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	rdx, 0
	mov	rcx, WS_CHILD OR WS_VISIBLE
	call	CreateStatusWindow
	mov	[r12.CLASS_APP.hwndStatus], rax

	lea	rdx, rcApp
	mov	rcx, rax
	call	GetWindowRect

	xor	rax, rax
	lea	rcx, rcApp
	mov	eax, [rcx.RECT.bottom]
	sub	eax, [rcx.RECT.top]
	mov	[r12.CLASS_APP.unStHeight], rax

	; -- create brushes and fonts --

	mov	rcx, [r12.CLASS_APP.unCurCol]
	call	CreateSolidBrush
	mov	[r12.CLASS_APP.hbrCurPath], rax

	mov	rcx, [r12.CLASS_APP.unOthCol]
	call	CreateSolidBrush
	mov	[r12.CLASS_APP.hbrOthPath], rax

	; -- create processing events --

	mov	r9, 0
	mov	r8d, 0
	mov	edx, TRUE
	mov	rcx, 0
	call	CreateEvent
	mov	[r12.CLASS_APP.hevStop], rax

	; -- store current and other --

	mov	rax, [r12.CLASS_APP.pxLeftList]
	mov	rcx, [r12.CLASS_APP.pxRightList]

	mov	[r12.CLASS_APP.pxActive], rax
	mov	[r12.CLASS_APP.pxInactive], rcx

	; -- all init done, show window --

	mov	eax, [r12.CLASS_APP.rcMain.RECT.left]
	cmp	eax, CW_USEDEFAULT
	je	appFirstShow

	lea	rdx, xPlacement
	mov	[rdx.WINDOWPLACEMENT.len], sizeof WINDOWPLACEMENT
	mov	[rdx.WINDOWPLACEMENT.flags], 0
	mov	[rdx.WINDOWPLACEMENT.ptMinPosition.POINT.x], 0
	mov	[rdx.WINDOWPLACEMENT.ptMinPosition.POINT.y], 0
	mov	[rdx.WINDOWPLACEMENT.ptMaxPosition.POINT.x], 0
	mov	[rdx.WINDOWPLACEMENT.ptMaxPosition.POINT.y], 0
	mov	rax, [r12.CLASS_APP.unShowMode]
	mov	[rdx.WINDOWPLACEMENT.showCmd], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.left]
	mov	[rdx.WINDOWPLACEMENT.rcNormalPosition.RECT.left], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.top]
	mov	[rdx.WINDOWPLACEMENT.rcNormalPosition.RECT.top], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.right]
	mov	[rdx.WINDOWPLACEMENT.rcNormalPosition.RECT.right], eax
	mov	eax, [r12.CLASS_APP.rcMain.RECT.bottom]
	mov	[rdx.WINDOWPLACEMENT.rcNormalPosition.RECT.bottom], eax

	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SetWindowPlacement

	jmp	appDone

appFirstShow:	mov	rdx, [r12.CLASS_APP.unShowMode]
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	ShowWindow

	; -- end cases --

appFail:	call	GetLastError
	jmp	appExit

appDone:	xor	rax, rax

appExit:	add	rsp, 128
	add	rsp, 1 * 8 + 2 * 64 + 2 * 64 + 2 * 64 + sizeof WNDCLASSEX + sizeof RECT + sizeof WINDOWPLACEMENT + 4 + 8

	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

appInit	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	run main application, main message loop handling
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	unError appRun ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appRun	PROC	FRAME
	LOCAL	xMessage:MSG		; message info

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof MSG + 8
	sub	rsp, 32
	.allocstack	32 + sizeof MSG + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- create main command object --

	call	commandNew
	mov	[r12.CLASS_APP.pxCommand], rax

	mov	rdx, r12
	mov	rcx, [r12.CLASS_APP.pxCommand]
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnInit]
	test	rax, rax
	jnz	appDone

	; -- start list fill threads --

	mov	rdx, LIST_ACTUAL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	mov	rdx, LIST_OTHER
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFillList]

	; -- show new status --

	mov	rdx, IDS_STATUS_READY
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetStatus]

	; -- message loop --

appLoop:	mov	dword ptr [rsp + 32], PM_REMOVE
	mov	r9d, 0
	mov	r8d, 0
	mov	rdx, 0
	lea	rcx, xMessage
	call	PeekMessage
	test	eax, eax
	jz	appWait

	lea	rcx, xMessage
	call	TranslateMessage

	lea	rcx, xMessage
	call	DispatchMessage

	jmp	appLoop

appWait:	mov	dword ptr [rsp + 32], QS_ALLINPUT
	mov	r9d, INFINITE
	mov	r8d, FALSE
	lea	rdx, [r12.CLASS_APP.hevStop]
	mov	ecx, 1
	call	MsgWaitForMultipleObjects
	cmp	eax, WAIT_OBJECT_0 + 1
	je	appLoop

	; -- end program --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSaveWinConfig]

	; -- release application --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnRelease]

	; -- message loop exit --

appDone:	xor	rax, rax

	add	rsp, 32
	add	rsp, sizeof MSG + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appRun	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	release application
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	unError appRelease ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appRelease	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 32
	.allocstack	32 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- store last used paths --

	lea	r9, [r12.CLASS_APP.txLeft]
	mov	r8, IDS_CFG_LEFTPATH
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigText]

	lea	r9, [r12.CLASS_APP.txRight]
	mov	r8, IDS_CFG_RIGHTPATH
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigText]

	; -- release childs --

	mov	rcx, [r12.CLASS_APP.pxCommand]
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnRelease]
	mov	[r12.CLASS_APP.pxCommand], 0

	mov	rcx, [r12.CLASS_APP.pxLeftPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnRelease]
	mov	[r12.CLASS_APP.pxLeftPath], 0

	mov	rcx, [r12.CLASS_APP.pxRightPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnRelease]
	mov	[r12.CLASS_APP.pxRightPath], 0

	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnRelease]
	mov	[r12.CLASS_APP.pxLeftList], 0

	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnRelease]
	mov	[r12.CLASS_APP.pxRightList], 0


	; -- release allocated resources --

	mov	rcx, [r12.CLASS_APP.hevStop]
	call	CloseHandle

	mov	rcx, [r12.CLASS_APP.hbrCurPath]
	call	DeleteObject

	mov	rcx, [r12.CLASS_APP.hbrOthPath]
	call	DeleteObject

	mov	rcx, [r12.CLASS_APP.hiconApp]
	call	DestroyIcon

	mov	rcx, [r12.CLASS_APP.hmenuApp]
	call	DestroyMenu

	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	DestroyWindow

	; -- end process --

	xor	rax, rax

	add	rsp, 32
	add	rsp, 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appRelease	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create button array
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError appInitButtons ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appInitButtons	PROC	FRAME
	LOCAL	unHLoop:QWORD	; loop counter horizontal
	LOCAL	unVLoop:QWORD	; loop counter vertical

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8
	sub	rsp, 32
	.allocstack	32 + 2 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- get size for button data --

	call	GetProcessHeap
	test	rax, rax
	jz	appExit

	mov	r8, sizeof QWORD
	imul	r8, [r12.CLASS_APP.unBtnCols]
	imul	r8, [r12.CLASS_APP.unBtnRows]
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	appExit

	mov	[r12.CLASS_APP.pxButtons], rax
	mov	r15, rax

	; -- load button config --

	mov	unVLoop, 0

	; -- loop rows --

appLines:	mov	unHLoop, 0

	; -- loop buttons --

appLoop:	call	buttonNew
	mov	[r15], rax

	; -- init button --

	mov	r9, r12
	mov	r8, unVLoop
	mov	rdx, unHLoop
	mov	rcx, rax
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnInit]

	add	r15, sizeof QWORD

	inc	unHLoop
	mov	rax, [r12.CLASS_APP.unBtnCols]
	cmp	unHLoop, rax
	jl	appLoop

	inc	unVLoop
	mov	rax, [r12.CLASS_APP.unBtnRows]
	cmp	unVLoop, rax
	jl	appLines

	; -- return result --

	xor	rax, rax

appExit:	add	rsp, 32
	add	rsp, 2 * 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

appInitButtons	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	load application configuration from config file
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError appLoadConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appLoadConfig	PROC	FRAME
	LOCAL	unValue:QWORD	; misc value
	LOCAL	txDefPath [128]:WORD	; default path

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

	; -- get button rows --

	lea	rax, [r12.CLASS_APP.unBtnRows]
	mov	[rsp + 32], rax
	mov	r9, DEF_BUTTON_ROWS
	mov	r8, IDS_CFG_BUTTONROWS
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- get button columns --

	lea	rax, [r12.CLASS_APP.unBtnCols]
	mov	[rsp + 32], rax
	mov	r9, DEF_BUTTON_COLS
	mov	r8, IDS_CFG_BUTTONCOLS
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- get delete confirm --

	lea	rax, [r12.CLASS_APP.fDelConf]
	mov	[rsp + 32], rax
	mov	r9, TRUE
	mov	r8, IDS_CFG_DELCONFIRM
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- get last window rect --

	lea	rax, unValue
	mov	[rsp + 32], rax
	mov	r9, CW_USEDEFAULT
	mov	r8, IDS_CFG_WINLEFT
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	mov	rax, unValue
	mov	[r12.CLASS_APP.rcMain.RECT.left], eax

	lea	rax, unValue
	mov	[rsp + 32], rax
	mov	r9, CW_USEDEFAULT
	mov	r8, IDS_CFG_WINTOP
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	mov	rax, unValue
	mov	[r12.CLASS_APP.rcMain.RECT.top], eax
	
	lea	rax, unValue
	mov	[rsp + 32], rax
	mov	r9, CW_USEDEFAULT
	mov	r8, IDS_CFG_WINRIGHT
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]
	
	mov	rax, unValue
	mov	[r12.CLASS_APP.rcMain.RECT.right], eax

	lea	rax, unValue
	mov	[rsp + 32], rax
	mov	r9, CW_USEDEFAULT
	mov	r8, IDS_CFG_WINBOTTOM
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	mov	rax, unValue
	mov	[r12.CLASS_APP.rcMain.RECT.bottom], eax

	; -- load selection colors --

	lea	rax, [r12.CLASS_APP.unCurCol]
	mov	[rsp + 32], rax
	mov	r9, DEF_CURCOLOR
	mov	r8, IDS_CFG_SELECTCUR
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	lea	rax, [r12.CLASS_APP.unOthCol]
	mov	[rsp + 32], rax
	mov	r9, DEF_OTHCOLOR
	mov	r8, IDS_CFG_SELECTOTH
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- get last used paths --

	lea	r9, txDefPath
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DEFPATH
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, [r12.CLASS_APP.txLeft]
	mov	[rsp + 32], rax
	lea	r9, txDefPath
	mov	r8, IDS_CFG_LEFTPATH
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigText]

	lea	rax, [r12.CLASS_APP.txRight]
	mov	[rsp + 32], rax
	lea	r9, txDefPath
	mov	r8, IDS_CFG_RIGHTPATH
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigText]

	; -- get last used show mode --

	lea	rax, [r12.CLASS_APP.unShowMode]
	mov	[rsp + 32], rax
	mov	r9, SW_SHOWNORMAL
	mov	r8, IDS_CFG_SHOWMODE
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	xor	rax, rax

	add	rsp, 128
	add	rsp, 1 * 8 + 2 * 128

	pop	r12
	pop	rbp

	ret	0

	align	4

appLoadConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	store application configuration to config file
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError appSaveConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSaveConfig	PROC	FRAME

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 8
	sub	rsp, 32
	.allocstack	32 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- save button rows --

	mov	r9, [r12.CLASS_APP.unBtnRows]
	mov	r8, IDS_CFG_BUTTONROWS
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- save button columns --

	mov	r9, [r12.CLASS_APP.unBtnCols]
	mov	r8, IDS_CFG_BUTTONCOLS
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- save delete confirm --

	mov	r9, [r12.CLASS_APP.fDelConf]
	mov	r8, IDS_CFG_DELCONFIRM
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appSaveConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	store application window parameter to config file
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError appSaveWinConfig ()
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSaveWinConfig	PROC	FRAME
	LOCAL	xPlacement:WINDOWPLACEMENT

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof WINDOWPLACEMENT + 4 + 8
	sub	rsp, 32
	.allocstack	32 + sizeof WINDOWPLACEMENT + 4 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- save last window rect --

	lea	rdx, xPlacement
	mov	[rdx.WINDOWPLACEMENT.len], sizeof WINDOWPLACEMENT
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	GetWindowPlacement

	lea	rax, xPlacement
	mov	r9d, [rax.WINDOWPLACEMENT.rcNormalPosition.RECT.left]
	mov	r8, IDS_CFG_WINLEFT
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	lea	rax, xPlacement
	mov	r9d, [rax.WINDOWPLACEMENT.rcNormalPosition.RECT.top]
	mov	r8, IDS_CFG_WINTOP
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	lea	rax, xPlacement
	mov	r9d, [rax.WINDOWPLACEMENT.rcNormalPosition.RECT.right]
	mov	r8, IDS_CFG_WINRIGHT
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	lea	rax, xPlacement
	mov	r9d, [rax.WINDOWPLACEMENT.rcNormalPosition.RECT.bottom]
	mov	r8, IDS_CFG_WINBOTTOM
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- save last used show mode --

	lea	rax, xPlacement
	mov	eax, [rax.WINDOWPLACEMENT.showCmd]

	mov	r9, rax
	mov	r8, IDS_CFG_SHOWMODE
	lea	rdx, [r12.CLASS_APP.txSection]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	xor	rax, rax

	add	rsp, 32
	add	rsp, sizeof WINDOWPLACEMENT + 4 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appSaveWinConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	set new path to active list
; last update:	2013-02-21 - Deutsch - x64 translation
; parameters:	unError appSetPath (ptxPath)
;	[in] ptxPath .. new path to use
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSetPath	PROC	FRAME
	LOCAL	ptxPath:QWORD	; new path

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	ptxPath, rdx

	; -- copy path --

	mov	r8d, DEF_PATH_LENGTH - 1
	mov	rdx, ptxPath
	mov	rcx, [r12.CLASS_APP.pxActive]
	mov	rcx, [rcx.CLASS_LIST.ptxPath]
	call	lstrcpyn

	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appSetPath	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	set status bar to a string id
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appSetStatus (idText)
;	[in] idText .. string ID of text for status bar
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSetStatus	PROC	FRAME
	LOCAL	txStatus [1024]:WORD	; new text

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 1024 + 8
	sub	rsp, 32
	.allocstack	32 + 2 * 1024 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	lea	r9, txStatus
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txStatus
	mov	r8, 0
	mov	edx, SB_SETTEXT
	mov	rcx, [r12.CLASS_APP.hwndStatus]
	call	SendMessage

	xor	rax, rax

	add	rsp, 32
	add	rsp, 2 * 1024 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appSetStatus	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	set status bar to a command name
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appSetStatusCmd (idCommand)
;	[in] idCommand .. string ID of command text
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSetStatusCmd	PROC	FRAME
	LOCAL	txCmd [128]:WORD	; command text
	LOCAL	txMask [1024]:WORD	; text mask
	LOCAL	txStatus [1024]:WORD	; resulting text

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 128 + 2 * 1024 + 2 * 1024 + 8
	sub	rsp, 32
	.allocstack	32 + 2 * 128 + 2 * 1024 + 2 * 1024 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- load command name and mask --

	lea	r9, txCmd
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txMask
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CURRENT_RUN
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r8, txCmd
	lea	rdx, txMask
	lea	rcx, txStatus
	call	wsprintf

	lea	r9, txStatus
	mov	r8, 0
	mov	edx, SB_SETTEXT
	mov	rcx, [r12.CLASS_APP.hwndStatus]
	call	SendMessage

	xor	rax, rax

	add	rsp, 32
	add	rsp, 2 * 128 + 2 * 1024 + 2 * 1024 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appSetStatusCmd	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	check or uncheck menu item
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appSetMenuState (idMenu, punCurState)
;	[in] idMenu .. menu item ID to set
;	[in/out] punCurState .. state to set, gets old state
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSetMenuState	PROC	FRAME
	LOCAL	xItem:MENUITEMINFO	; menu item description

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof MENUITEMINFO + 8
	sub	rsp, 32
	.allocstack	32 + sizeof MENUITEMINFO + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- check or uncheck menu item --

	lea	r9, xItem
	mov	[r9.MENUITEMINFO.cbSize], sizeof MENUITEMINFO
	mov	[r9.MENUITEMINFO.fMask], MIIM_CHECKMARKS OR MIIM_ID OR MIIM_STATE
	mov	[r9.MENUITEMINFO.wID], edx

	mov	[r9.MENUITEMINFO.fType], 0
	mov	[r9.MENUITEMINFO.hSubMenu], 0
	mov	[r9.MENUITEMINFO.hbmpChecked], 0
	mov	[r9.MENUITEMINFO.hbmpUnchecked], 0
	mov	[r9.MENUITEMINFO.dwItemData], 0
	mov	[r9.MENUITEMINFO.dwTypeData], 0
	mov	[r9.MENUITEMINFO.cch], 0
	mov	[r9.MENUITEMINFO.hbmpItem], 0

	mov	rax, [r8]
	cmp	rax, MFS_CHECKED
	je	appOff

	mov	[r9.MENUITEMINFO.fState], MFS_CHECKED
	jmp	appSet

appOff:	mov	[r9.MENUITEMINFO.fState], MFS_UNCHECKED

appSet:	mov	eax, [r9.MENUITEMINFO.fState]
	mov	[r8], rax

	mov	r8d, FALSE
	mov	rcx, [r12.CLASS_APP.hmenuApp]
	call	SetMenuItemInfo

	xor	rax, rax
	add	rsp, 32
	add	rsp, sizeof MENUITEMINFO + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appSetMenuState	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	unmark old list, switch to new list
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appSetActive (idList)
;	[in] idList .. which list to be set active
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appSetActive	PROC	FRAME
	LOCAL	idList:QWORD	; list id (left/right)

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	idList, rdx

	; -- check if already active --

	mov	rax, idList
	mov	rcx, [r12.CLASS_APP.pxActive]
	cmp	[rcx.CLASS_LIST.idList], rax
	je	salDone

	; -- swap list ids --

	mov	rax, [r12.CLASS_APP.pxActive]
	mov	rcx, [r12.CLASS_APP.pxInactive]
	mov	[r12.CLASS_APP.pxInactive], rax
	mov	[r12.CLASS_APP.pxActive], rcx

	; -- swap path --

	mov	rcx, [r12.CLASS_APP.pxLeftPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnUpdate]

	mov	rcx, [r12.CLASS_APP.pxRightPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnUpdate]

salDone:	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8

	pop	r12
	pop	rbp

	ret	0
	
	align	4

appSetActive	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	process all selected entries in given list
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appProcessActive (unList, pfnCallback, pxUser, fRecursive)
;	[in] unList .. which list to process - either active or inactive
;	[in] pfnCallback .. callback proc to be called with each selected list entry
;	[in] pxUser .. user parameter for callback
;	[in] fRecursive .. if true dive into list entries that are folders
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appProcessActive	PROC	FRAME
	LOCAL	unList:QWORD	; use active or inactive list
	LOCAL	pfnCallback:QWORD	; callback function
	LOCAL	pxUser:QWORD	; callback user parameter
	LOCAL	fRecursive:QWORD	; recursive processing flag
	LOCAL	xParam:PROCESS_PARAM	; callback parameter

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + sizeof PROCESS_PARAM + 8
	sub	rsp, 32
	.allocstack	32 + 4 * 8 + sizeof PROCESS_PARAM + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	unList, rdx
	mov	pfnCallback, r8
	mov	pxUser, r9
	mov	rax, [rbp + 3 * 8 + 32]
	mov	fRecursive, rax

	; -- process --

	lea	r8, xParam
	mov	[r8.PROCESS_PARAM.pxApp], r12

	mov	rax, unList
	cmp	rax, LIST_ACTUAL
	je	apaActual

	mov	rcx, [r12.CLASS_APP.pxInactive]
	jmp	apaList

apaActual:	mov	rcx, [r12.CLASS_APP.pxActive]

apaList:	mov	[r8.PROCESS_PARAM.pxList], rcx
	mov	rax, [rcx.CLASS_LIST.ptxPath]
	mov	[r8.PROCESS_PARAM.ptxPath], rax
	mov	rax, pfnCallback
	mov	[r8.PROCESS_PARAM.pfnCallback], rax
	mov	rax, pxUser
	mov	[r8.PROCESS_PARAM.pxUser], rax
	mov	rax, fRecursive
	mov	[r8.PROCESS_PARAM.fRecursive], rax

	mov	rdx, r8
	mov	rcx, r12
	call	prcStartThread

	; -- wait until finished --

	mov	rcx, r12
	call	prcWaitThread

	; -- check if done regular, or stopped --

	mov	edx, 0
	mov	rcx, [r12.CLASS_APP.hevStop]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	jne	apaUser

	mov	rax, ERROR_OPERATION_ABORTED
	jmp	apaExit

	; -- check if user cancelled --

apaUser:	mov	rax, [r12.CLASS_APP.pxCommand]

	mov	rdx, 0
	mov	rcx, [eax.CLASS_COMMAND.hevUserBreak]
	call	WaitForSingleObject
	cmp	eax, WAIT_OBJECT_0
	jne	apaDone

	mov	rax, ERROR_CANCELLED
	jmp	apaExit

	; -- all done --

apaDone:	xor	rax, rax

apaExit:	add	rsp, 32
	add	rsp, 4 * 8 + sizeof PROCESS_PARAM + 8
	
	pop	r12
	pop	rbp
	
	ret	0
	
	align	4
	
appProcessActive	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	clear listview and read directory from path into list
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	unError appFillList (unList)
;	[in] unList .. which list to process - either active or inactive
; returns:	zero for ok, or error code
;------------------------------------------------------------------------------------------------------------------------------------------

appFillList	PROC	FRAME
	LOCAL	unList:QWORD	; active or inactive list

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	unList, rdx

	; -- get actual list --

	mov	rax, unList
	cmp	rax, LIST_ACTUAL
	je	appActive

	mov	r15, [r12.CLASS_APP.pxInactive]
	jmp	appList

appActive:	mov	r15, [r12.CLASS_APP.pxActive]

	; -- path to edit --

appList:	test	r15, r15
	jz	appDone

	mov	rcx, [r15.CLASS_LIST.ptxPath]
	call	lstrlen

	mov	rcx, [r15.CLASS_LIST.ptxPath]
	cmp	word ptr [rcx + 2 * rax - 2], "\"
	je	appAppend

	mov	word ptr [rcx + 2 * rax], "\"
	mov	word ptr [rcx + 2 * rax + 2], 0

appAppend:	mov	r8, [r15.CLASS_LIST.ptxPath]
	mov	rdx, [r15.CLASS_LIST.idList]
	add	rdx, 2
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SetDlgItemText

	; -- stop running thread, if any --

	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnStopThread]

	; -- start new fill thread --

	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnStartThread]

appDone:	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8 + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

appFillList	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	toogle menu item flags
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appToggleMenu (idMenu, pxList, unColumn)
;	[in] idMenu .. menu item to toggle
;	[in] pxList .. current list object
;	[in] unColumn .. which column in list
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appToggleMenu	PROC	FRAME
	LOCAL	idMenu:QWORD	; menu item id
	LOCAL	unState:QWORD	; state of item
	LOCAL	unColumn:QWORD	; target column
	LOCAL	xItem:MENUITEMINFO	; menu item description

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + sizeof MENUITEMINFO + 8
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + sizeof MENUITEMINFO + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	idMenu, rdx
	mov	r15, r8
	mov	unColumn, r9

	; -- get current state --

	lea	r9, xItem
	mov	[r9.MENUITEMINFO.cbSize], sizeof MENUITEMINFO
	mov	[r9.MENUITEMINFO.fMask], MIIM_ID OR MIIM_STATE

	mov	r8d, FALSE
	mov	rdx, idMenu
	mov	rcx, [r12.CLASS_APP.hmenuApp]
	call	GetMenuItemInfo

	lea	rax, xItem
	mov	eax, [rax.MENUITEMINFO.fState]
	mov	unState, rax

	; -- set new state --

	lea	r8, unState
	mov	rdx, idMenu
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSetMenuState]

	mov	rax, unState
	test	rax, MFS_CHECKED
	setnz	al
	and	rax, 0FFh

	mov	r8, rax
	mov	rdx, unColumn
	mov	rcx, r15
	mov	rax, [r15.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeColumn]

	xor	rax, rax
	add	rsp, 32
	add	rsp, 3 * 8 + sizeof MENUITEMINFO + 8

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

appToggleMenu	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	resize application window and its childs
; last update:	2013-03-11 - Deutsch - extracted
; parameters:	unError appResize (prcSize)
;	[in] prcSize .. new size rectangle
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appResize	PROC	FRAME
	LOCAL	prcApp:QWORD	; menu item id
	LOCAL	unWidth:QWORD	; application child area width
	LOCAL	unHeight:QWORD	; application child area height
	LOCAL	rcSize:RECT	; calculation rectangle

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + sizeof RECT
	sub	rsp, 128
	.allocstack	128 + 3 * 8 + sizeof RECT
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	prcApp, rdx

	; -- size buttons --

	mov	rdx, prcApp
	xor	rax, rax
	mov	eax, [rdx.RECT.right]
	sub	eax, [rdx.RECT.left]
	mov	unWidth, rax

	xor	rax, rax
	mov	eax, [rdx.RECT.bottom]
	mov	unHeight, rax

	; -- calculate button width --

	mov	rcx, [r12.CLASS_APP.unBtnCols]
	test	rcx, rcx
	jz	appList

	inc	rcx
	imul	rcx, DEF_BUTTON_GAP

	mov	rax, unWidth
	sub	rax, rcx
	cdq
	idiv	[r12.CLASS_APP.unBtnCols]

	mov	[r12.CLASS_APP.unBtnWidth], rax

	; -- calculate button height --

	mov	rcx, [r12.CLASS_APP.unBtnRows]
	test	rcx, rcx
	jz	appList

	inc	rcx
	imul	rcx, DEF_BUTTON_GAP

	mov	rax, [r12.CLASS_APP.unBtnRows]
	imul	rax, DEF_BUTTON_HEIGHT
	sub	rax, rcx
	cdq
	idiv	[r12.CLASS_APP.unBtnRows]

	mov	[r12.CLASS_APP.unBtnHeight], rax

	; -- get button area top --

	mov	rax, unHeight
	mov	[r12.CLASS_APP.unBtnTop], rax

	; -- calc real button area size --

	mov	rax, [r12.CLASS_APP.unBtnHeight]
	imul	[r12.CLASS_APP.unBtnRows]
	mov	[r12.CLASS_APP.unBtnArea], rax

	mov	rax, [r12.CLASS_APP.unBtnRows]
	dec	rax
	mov	rcx, DEF_BUTTON_GAP
	imul	rcx
	add	[r12.CLASS_APP.unBtnArea], rax

	; -- calculate list rectangle --

appList:	mov	rcx, prcApp
	lea	rdx, rcSize

	xor	rax, rax
	mov	eax, [rcx.RECT.bottom]
	sub	rax, [r12.CLASS_APP.unEditHeight]
	sub	rax, [r12.CLASS_APP.unBtnArea]
	sub	rax, [r12.CLASS_APP.unStHeight]
	sub	eax, 4 * DEF_CHILD_GAP
	mov	[rdx.RECT.bottom], eax

	mov	eax, [rcx.RECT.right]
	sub	eax, [rcx.RECT.left]
	movsxd	rax, eax
	mov	unWidth, rax

	sub	eax, 3 * DEF_CHILD_GAP
	sar	eax, 1
	mov	[rdx.RECT.right], eax

	mov	eax, [rcx.RECT.top]
	mov	[rdx.RECT.top], eax

	mov	eax, [rcx.RECT.left]
	add	eax, DEF_CHILD_GAP
	mov	[rdx.RECT.left], eax

	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnResize]

	mov	rcx, prcApp
	lea	rdx, rcSize

	mov	rax, unWidth
	sub	eax, DEF_CHILD_GAP
	sub	eax, [rdx.RECT.right]
	mov	[rdx.RECT.left], eax

	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnResize]

	; -- size edits --

	mov	rcx, prcApp
	lea	rdx, rcSize

	mov	[rdx.RECT.left], DEF_CHILD_GAP
	mov	rax, [r12.CLASS_APP.unEditHeight]
	mov	[rdx.RECT.bottom], eax

	mov	rax, unWidth
	sub	eax, 3 * DEF_CHILD_GAP
	sar	eax, 1
	mov	[rdx.RECT.right], eax

	xor	rax, rax
	mov	eax, [rcx.RECT.bottom]
	sub	rax, DEF_CHILD_GAP + DEF_CHILD_GAP
	sub	rax, [r12.CLASS_APP.unEditHeight]
	sub	rax, [r12.CLASS_APP.unBtnArea]
	sub	rax, [r12.CLASS_APP.unStHeight]
	mov	[rdx.RECT.top], eax

	lea	rdx, rcSize
	mov	rcx, [r12.CLASS_APP.pxLeftPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnResize]

	lea	rdx, rcSize
	mov	rax, unWidth
	sub	rax, DEF_CHILD_GAP
	sub	eax, [rdx.RECT.right]
	mov	[rdx.RECT.left], eax

	lea	rdx, rcSize
	mov	rcx, [r12.CLASS_APP.pxRightPath]
	mov	rax, [rcx.CLASS_PATH.vtableThis]
	call	[rax.CLASS_PATH_IFACE.pfnResize]

	; -- size status window --

	mov	dword ptr [rsp + 40], 0
	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, DEF_CHILD_GAP
	mov	edx, DEF_CHILD_GAP
	mov	rcx, [r12.CLASS_APP.hwndStatus]
	call	MoveWindow

	xor	rax, rax
	add	rsp, 128
	add	rsp, 3 * 8 + sizeof RECT

	pop	r12
	pop	rbp

	ret	0

	align	4

appResize	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle user events
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	unError appHandleEvent (idEvent)
;	[in] idEvent .. number of event to handle
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appHandleEvent	PROC	FRAME
	LOCAL	unLoop:QWORD	; button loop counter
	LOCAL	txAbout [1024]:WORD	; about text
	LOCAL	txTitle [1024]:WORD	; about title

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 2 * 1024 + 2 * 1024 + 8
	sub	rsp, 128
	.allocstack	128 + 1 * 8 + 2 * 1024 + 2 * 1024 + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx

	; -- branch on event --

	mov	rax, rdx
	cmp	rax, IDM_FILE_EXIT
	je	appFileExit
	cmp	rax, IDM_FILE_CONFIG
	je	appFileConfig
	cmp	rax, IDM_LEFT_SYMBOL
	je	appLeftSymbol
	cmp	rax, IDM_LEFT_DATE
	je	appLeftDate
	cmp	rax, IDM_LEFT_TYPE
	je	appLeftType
	cmp	rax, IDM_LEFT_SIZE
	je	appLeftSize
	cmp	rax, IDM_LEFT_BGCOLOR
	je	appLeftBgcolor
	cmp	rax, IDM_LEFT_FGCOLOR
	je	appLeftFgcolor
	cmp	rax, IDM_LEFT_FONT
	je	appLFont
	cmp	rax, IDM_RIGHT_SYMBOL
	je	appRightSymbol
	cmp	rax, IDM_RIGHT_DATE
	je	appRightDate
	cmp	rax, IDM_RIGHT_TYPE
	je	appRightType
	cmp	rax, IDM_RIGHT_SIZE
	je	appRightSize
	cmp	rax, IDM_RIGHT_BGCOLOR
	je	appRightBgcolor
	cmp	rax, IDM_RIGHT_FGCOLOR
	je	appRightFgcolor
	cmp	rax, IDM_RIGHT_FONT
	je	appRFont
	cmp	rax, IDM_HELP_ABOUT
	je	appHelpAbout

	cmp	rax, IDM_BPOP_COMMAND
	je	appBCmd
	cmp	rax, IDM_BPOP_FGCOLOR
	je	appButtonFG
	cmp	rax, IDM_BPOP_BGCOLOR
	je	appButtonBG
	cmp	rax, IDM_BPOP_FONT
	je	appBFont
	cmp	rax, IDM_BPOP_SHORTCUT
	je	appShortcut

	jmp	appDone

	; -- handle file close --

appFileExit:	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_CLOSE
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SendMessage

	jmp	appDone

	; -- handle configure dialog --

appFileConfig:	mov	[rsp + 32], r12
	lea	r9, dlgprcConfig
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_CONFIGURE
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	CreateDialogParam

	jmp	appDone

	; -- show / hide symbols of left list --

appLeftSymbol:	mov	r9, LIST_SYMBOL
	mov	r8, [r12.CLASS_APP.pxLeftList]
	mov	rdx, IDM_LEFT_SYMBOL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide date of left list --

appLeftDate:	mov	r9, LIST_DATE
	mov	r8, [r12.CLASS_APP.pxLeftList]
	mov	rdx, IDM_LEFT_DATE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]
	jmp	appDone

	; -- show / hide type of left list --

appLeftType:	mov	r9, LIST_TYPE
	mov	r8, [r12.CLASS_APP.pxLeftList]
	mov	rdx, IDM_LEFT_TYPE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide size of left list --

appLeftSize:	mov	r9, LIST_SIZE
	mov	r8, [r12.CLASS_APP.pxLeftList]
	mov	rdx, IDM_LEFT_SIZE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide symbols of right list --

appRightSymbol:	mov	r9, LIST_SYMBOL
	mov	r8, [r12.CLASS_APP.pxRightList]
	mov	rdx, IDM_RIGHT_SYMBOL
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide date of right list --

appRightDate:	mov	r9, LIST_DATE
	mov	r8, [r12.CLASS_APP.pxRightList]
	mov	rdx, IDM_RIGHT_DATE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide type of right list --

appRightType:	mov	r9, LIST_TYPE
	mov	r8, [r12.CLASS_APP.pxRightList]
	mov	rdx, IDM_RIGHT_TYPE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- show / hide size of right list --

appRightSize:	mov	r9, LIST_SIZE
	mov	r8, [r12.CLASS_APP.pxRightList]
	mov	rdx, IDM_RIGHT_SIZE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnToggleMenu]

	jmp	appDone

	; -- handle left bgcolor --

appLeftBgcolor:	mov	rdx, CHANGE_BGCOLOR
	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeColor]

	jmp	appDone

	; -- handle left fgcolor --

appLeftFgcolor:	mov	rdx, CHANGE_FGCOLOR
	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeColor]

	jmp	appDone

	; -- handle right bgcolor --

appRightBgcolor:	mov	rdx, CHANGE_BGCOLOR
	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeColor]

	jmp	appDone

	; -- handle right fgcolor setup --

appRightFgcolor:	mov	rdx, CHANGE_FGCOLOR
	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeColor]

	jmp	appDone

	; -- handle left font --

appLFont:	mov	rcx, [r12.CLASS_APP.pxLeftList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeFont]

	jmp	appDone

	; -- handle right font --

appRFont:	mov	rcx, [r12.CLASS_APP.pxRightList]
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnChangeFont]

	jmp	appDone


	; -- handle menu - set button command --

appBCmd:	mov	rax, [r12.CLASS_APP.pxButton]
	test	rax, rax
	je	appDone

	mov	[rsp + 32], rax
	lea	r9, dlgprcButton
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_BUTTON_CMD
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	DialogBoxParam

	jmp	appUpdate

	; -- setup button fore color --

appButtonFG:	mov	rdx, [r12.CLASS_APP.pxButton]
	test	rdx, rdx
	je	appDone

	lea	rdx, [rdx.CLASS_BUTTON.xParams.VIEW_PARAM.unFgColor]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnColorDialog]

	jmp	appUpdate

	; -- set button back color --

appButtonBG:	mov	rdx, [r12.CLASS_APP.pxButton]
	test	rdx, rdx
	je	appDone

	lea	rdx, [rdx.CLASS_BUTTON.xParams.VIEW_PARAM.unBgColor]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnColorDialog]

	jmp	appUpdate

	; -- setup button font --

appBFont:	mov	rdx, [r12.CLASS_APP.pxButton]
	test	rdx, rdx
	je	appDone

	lea	rdx, [rdx.CLASS_BUTTON.xParams]
	mov	rcx, [r12.CLASS_APP.pxConfig]
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnFontDialog]
	test	rax, rax
	jnz	appDone

	jmp	appUpdate

	; -- configure buttons shortcut --

appShortcut:	mov	rax, [r12.CLASS_APP.pxButton]
	test	rax, rax
	je	appDone

	lea	rax, [rax.CLASS_BUTTON.unShortcut]
	mov	[rsp + 32], rax
	lea	r9, dlgprcKey
	mov	r8, [r12.CLASS_APP.hwndApp]
	mov	edx, IDD_SHORTCUT
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	DialogBoxParam

	jmp	appUpdate

	; -- update main window --

appUpdate:	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	InvalidateRect

	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	UpdateWindow

	; -- save configuration --

	mov	r14, [r12.CLASS_APP.pxButtons]

	mov	rax, [r12.CLASS_APP.unBtnCols]
	imul	rax, [r12.CLASS_APP.unBtnRows]
	mov	unLoop, rax

appCLoop:	mov	rcx, [r14]
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnSaveConfig]

	add	r14, sizeof QWORD

	dec	unLoop
	jne	appCLoop

	jmp	appDone

	; -- handle help about --

appHelpAbout:	lea	r9, txAbout
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_ABOUT_TEXT
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txTitle
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_ABOUT_TITLE
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	r9d, MB_OK
	lea	r8, txTitle
	lea	rdx, txAbout
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	MessageBox

appDone:	xor	rax, rax
	add	rsp, 128
	add	rsp, 1 * 8 + 2 * 1024 + 2 * 1024 + 8

	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

appHandleEvent	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	retreive button description by pixel position
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	pxButton appFindButton (unHorz, unVert, prcButton)
;	[in] unHorz .. horizontal pixel position
;	[in] unVert .. vertical pixel position
;	[in] prcButton .. button rectangle
; returns:	found button or zero
;------------------------------------------------------------------------------------------------------------------------------------------

appFindButton	PROC	FRAME
	LOCAL	ptPos:POINT	; position horizontal
	LOCAL	prcButton:QWORD	; button rectangle
	LOCAL	unLoop:QWORD	; loop counter vertical

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + sizeof POINT + 8
	sub	rsp, 32
	.allocstack	32 + 2 * 8 + sizeof POINT + 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	lea	rax, ptPos
	mov	[rax.POINT.x], edx
	mov	[rax.POINT.y], r8d
	mov	prcButton, r9
	mov	r14, [r12.CLASS_APP.pxButtons]

	; -- loop buttons --

	mov	rax, [r12.CLASS_APP.unBtnCols]
	imul	rax, [r12.CLASS_APP.unBtnRows]
	mov	unLoop, rax

	; -- get buttons rect --

btnLoop:	mov	rdx, prcButton
	mov	rcx, [r14]
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnGetRect]

	mov	rdx, qword ptr ptPos
	mov	rcx, prcButton
	call	PtInRect
	test	eax, eax
	jne	gbpFound

	add	r14, sizeof QWORD

	dec	unLoop
	jne	btnLoop

	xor	rax, rax
	jmp	gbpExit

	; -- return found button --

gbpFound:	mov	rax, [r14]

gbpExit:	add	rsp, 32
	add	rsp, 2 * 8 + sizeof POINT + 8

	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

appFindButton	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	check if a button matches a key code
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	pxButton appMatchShortcut (unKey)
;	[in] unKey .. keycode to search for
; returns:	matching button or zero
;------------------------------------------------------------------------------------------------------------------------------------------

appMatchShortcut	PROC	FRAME
	LOCAL	unLoop:QWORD	; loop counter horizontal
	LOCAL	unKey:QWORD	; matching key

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8
	sub	rsp, 32
	.allocstack	32 + 2 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	unKey, rdx
	mov	r14, [r12.CLASS_APP.pxButtons]

	; -- loop buttons --

	mov	rax, [r12.CLASS_APP.unBtnCols]
	imul	rax, [r12.CLASS_APP.unBtnRows]
	mov	unLoop, rax

appLoop:	mov	rax, [r14]
	mov	rax, [r14.CLASS_BUTTON.unShortcut]
	cmp	rax, unKey
	je	appFound

	add	r14, sizeof QWORD

	dec	unLoop
	jne	appLoop

	xor	rax, rax
	jmp	appExit

	; -- matching button found --

appFound:	mov	rax, [r14]

appExit:	add	rsp, 32
	add	rsp, 2 * 8

	pop	r12
	pop	r14
	pop	rbp

	ret	0

	align	4

appMatchShortcut	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	create font from view parameter
; last update:	2013-02-28 - Deutsch - extracted
; parameters:	unError appCreateViewFont (pxView, phfontView)
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

appCreateViewFont	PROC	FRAME
	LOCAL	phfontView:QWORD	; resulting font

	push	rbp
	.pushreg	rbp
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 128
	.allocstack	128 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r15, rdx
	mov	phfontView, r8

	; -- setup font --

	lea	rax, [r15.VIEW_PARAM.txFontName]
	mov	[rsp + 104], rax
	mov	dword ptr [rsp + 96], DEFAULT_PITCH OR FF_DONTCARE
	mov	dword ptr [rsp + 88], DEFAULT_QUALITY
	mov	dword ptr [rsp + 80], CLIP_DEFAULT_PRECIS
	mov	dword ptr [rsp + 72], OUT_DEFAULT_PRECIS
	mov	dword ptr [rsp + 64], DEFAULT_CHARSET
	mov	dword ptr [rsp + 56], FALSE
	mov	dword ptr [rsp + 48], FALSE
	mov	eax, dword ptr [r15.VIEW_PARAM.unItalic]
	mov	dword ptr [rsp + 40], eax
	mov	eax, dword ptr [r15.VIEW_PARAM.unWeight]
	mov	dword ptr [rsp + 32], eax
	mov	r9d, 0
	mov	r8d, 0
	mov	edx, 0
	mov	ecx, dword ptr [r15.VIEW_PARAM.unFontSize]
	call	CreateFont

	mov	rcx, phfontView
	mov	[rcx], rax

	xor	rax, rax

	add	rsp, 128
	add	rsp, 1 * 8

	pop	r15
	pop	rbp
	ret	0

	align	4

appCreateViewFont	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	load string with given language from resource table - self implemented to support multiple languages
; last update:	2013-03-20 - Deutsch - make x64
; parameters:	unError appLoadString (idString, unLang, ptxBuffer)
;	[in] idString .. string ID to load
;	[in] unLang .. language to load
;	[out] ptxBuffer .. resulting text, shall be large enough to hold text from string resource!
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appLoadString	PROC	FRAME
	LOCAL	idString:QWORD	; number of points
	LOCAL	ptxBuffer:QWORD
	LOCAL	hresText:QWORD
	LOCAL	ptxText:QWORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 4 * 8 + 8
	.endprolog

	; -- store parameter --

	mov	r12, rcx
	mov	idString, rdx
	mov	ptxBuffer, r9

	; -- get resource --

	mov	r9, r8
	mov	r8, idString
	shr	r8, 4
	inc	r8
	mov	rdx, RT_STRING
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	FindResourceEx
	test	rax, rax
	jz	appFail

	mov	rdx, rax
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadResource
	test	rax, rax
	jz	appFail

	mov	hresText, rax

	mov	rcx, rax
	call	LockResource
	test	rax, rax
	jz	appFree

	mov	ptxText, rax

	; -- goto target string --

	mov	rcx, idString
	and	rcx, 15

appFind:	test	rcx, rcx
	jz	appCopy

	mov	dx, [rax]
	and	rdx, 0FFFFh
	lea	rax, [rax + 2 * rdx + 2]

	dec	rcx
	jmp	appFind

	; -- clone text --

appCopy:	mov	r10, ptxBuffer
	mov	cx, [rax]
	and	rcx, 0FFFFh
	add	rax, 2

appClone:	mov	dx, [rax]
	mov	[r10], dx

	add	rax, 2
	add	r10, 2
	dec	rcx
	jg	appClone

	mov	word ptr [r10], 0

	; -- free stuff --

appFree:	mov	rcx, hresText
	call	FreeResource

	xor	rax, rax
	jmp	appExit

appFail:	mov	rax, E_FAIL

appExit:	add	rsp, 32
	add	rsp, 4 * 8 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

appLoadString	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	get INI file name and path
; last update:	2013-02-28 - Deutsch - extracted
; parameters:	unError appGetConfigPath (ptxConfig)
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

appGetConfigPath	PROC	FRAME
	LOCAL	ptxConfig:QWORD	; ini file name buffer

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	ptxConfig, rdx

	; -- build config file name --

	mov	r8d, DEF_PATH_LENGTH - 1
	mov	rdx, ptxConfig
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	GetModuleFileName

	; -- append ini name --

	mov	rcx, ptxConfig

appScan:	dec	rax
	cmp	word ptr [rcx + 2 * rax], "\"
	jne	appScan

	lea	r9, [rcx + 2 * rax + 2]
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_CONFIGFILE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8

	pop	r12
	pop	rbp
	ret	0

	align	4

appGetConfigPath	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	main program, init all required staff
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	exit code appMain ()
; returns:	process return value
;------------------------------------------------------------------------------------------------------------------------------------------

appMain	PROC	FRAME
	LOCAL	xCtrls:INITCOMMCTRLEX	; common controls initialize information

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof INITCOMMCTRLEX
	sub	rsp, 32
	.allocstack	32 + sizeof INITCOMMCTRLEX
	.endprolog

	; -- prepare comctl library --

	lea	rcx, xCtrls
	mov	[rcx.INITCOMMCTRLEX.dwSize], sizeof INITCOMMCTRLEX
	mov	[rcx.INITCOMMCTRLEX.dwICC], ICC_LISTVIEW_CLASSES OR ICC_BAR_CLASSES OR ICC_PROGRESS_CLASS OR ICC_STANDARD_CLASSES OR ICC_USEREX_CLASSES

	call	InitCommonControlsEx

	; -- allocate new main app object --

	call	appNew
	mov	r12, rax

	; -- init app --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnInit]

	; -- run application --

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnRun]

	; -- free object --

	call	GetProcessHeap

	mov	r8, r12
	mov	edx, 0
	mov	rcx, rax
	call	HeapFree

	; -- end process --

	mov	rcx, 0
	call	ExitProcess

	; (we will never reach here ..)

	add	rsp, 32
	add	rsp, sizeof INITCOMMCTRLEX

	pop	r12
	pop	rbp

	ret	0

	align	4

appMain	ENDP

;------------------------------------------------------------------------------------------------------------------------------------------
; does:	main program, init all required staff
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	unError appConfirmClose ()
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

appConfirmClose	PROC	FRAME
	LOCAL	fTasks:QWORD	; true if tasks are present
	LOCAL	unButton:QWORD	; resulting button
	LOCAL	txTitle [128]:WORD	; confirm dialog title
	LOCAL	txConfirm [128]:WORD	; confirm dialog text

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 2 * 8 + 2 * 128 + 2 * 128
	sub	rsp, 64
	.allocstack	64 + 2 * 8 + 2 * 128 + 2 * 128
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	r15, [r12.CLASS_APP.pxCommand]

	mov	fTasks, 0

	; -- check for running process --

	mov	rax, [r12.CLASS_APP.hthProcess]
	test	rax, rax
	jz	accCmd

	mov	fTasks, 1

	; -- check for tasks in command task list --

accCmd:	mov	rax, [r15.CLASS_COMMAND.parrCommands]
	test	rax, rax
	jz	accDialog

	mov	fTasks, 1

	; -- confirm task cancel --

accDialog:	mov	rax, fTasks
	test	rax, rax
	jz	accExit

	lea	r9, txTitle
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CONFIRM_TITLE
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, txConfirm
	mov	r8, [r12.CLASS_APP.unLang]
	mov	rdx, IDS_CONFIRM_TEXT
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, unButton
	mov	qword ptr [rsp + 56], rax
	mov	qword ptr [rsp + 48], 0
	mov	word ptr [rsp + 48], TD_WARNING_ICON
	mov	qword ptr [rsp + 40], TDCBF_YES_BUTTON OR TDCBF_NO_BUTTON
	mov	qword ptr [rsp + 32], 0
	lea	r9, txConfirm
	lea	r8, txTitle
	mov	rdx, [r12.CLASS_APP.hinstApp]
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	TaskDialog
	test	rax, rax
	jnz	accExit

	; -- cancel close if user wants to --

	mov	rax, unButton
	cmp	rax, IDYES
	je	accCancel

	mov	rax, ERROR_OPERATION_ABORTED
	jmp	accExit

	; -- stop processing thread --

accCancel:	mov	rcx, r12
	call	prcStopThread

	; -- clean up task list --

	mov	rcx, r15
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnCleanTask]

	xor	rax, rax

accExit:	add	rsp, 64
	add	rsp, 2 * 8 + 2 * 128 + 2 * 128

	pop	r15
	pop	r12
	pop	rbp

	ret	0

	align	4

appConfirmClose	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	handle all interesting window events
; last update:	2013-02-21 - Deutsch - x64 translation
; parameters:	result wndprcApp (hwndApp, unMsg, wParam, lParam)
;	[in] hwndApp .. window to handle
;	[in] unMsg .. message code to handle
;	[in] wParam .. message parameter 1
;	[in] lParam .. message parameter 2
; returns:	depending on message
;------------------------------------------------------------------------------------------------------------------------------------------

wndprcApp	PROC	FRAME
	LOCAL	hwndApp:QWORD	; main window
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	pxActive:QWORD	; active button during click
	LOCAL	hdcApp:QWORD	; paint device
	LOCAL	unKey:QWORD	; pressed key during key handling
	LOCAL	unLoop:QWORD	; loop counter
	LOCAL	hmenuConfig:QWORD	; popup menu
	LOCAL	hmenuPopup:QWORD	; popup sub menu
	LOCAL	hbrColor:QWORD	; brush with color
	LOCAL	ptMenu:POINT	; popup menu position
	LOCAL	rcApp:RECT	; window size rectangle
	LOCAL	rcEdit:RECT		; edit size rectangle
	LOCAL	rcButton:RECT	; button rectangle
	LOCAL	xPaint:PAINTSTRUCT	; paint information

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 10 * 8 + 4 + sizeof POINT + 3 * sizeof RECT + sizeof PAINTSTRUCT + 8
	sub	rsp, 128
	.allocstack	128 + 10 * 8 + 4 + sizeof POINT + 3 * sizeof RECT + sizeof PAINTSTRUCT + 8
	.endprolog

	; -- get parameter --

	mov	hwndApp, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- check for my messages --

	mov	edx, GWLP_USERDATA
	mov	rcx, hwndApp
	call	GetWindowLongPtr
	test	rax, rax
	jz	wpoBack

	mov	r12, rax

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_SIZING
	je	wpoSizing
	cmp	eax, WM_PAINT
	je	wpoPaint
	cmp	eax, WM_SIZE
	je	wpoLayout
	cmp	eax, WM_CTLCOLOREDIT
	je	wpoPathColor
	cmp	eax, WM_LBUTTONDOWN
	je	wpoLeftDown
	cmp	eax, WM_LBUTTONUP
	je	wpoLeftUp
	cmp	eax, WM_RBUTTONUP
	je	wpoRightUp
	cmp	eax, WM_MOUSEMOVE
	je	wpoMouseMove
	cmp	eax, WM_NOTIFY
	je	wpoNotify
;	cmp	eax, WM_KEYDOWN
;	je	wpoKeyDown
	cmp	eax, WM_CHAR
	je	wpoChar
;	cmp	eax, WM_DEADCHAR
;	je	wpoChar
	cmp	eax, WM_COMMAND
	je	wpoCommand
	cmp	eax, WM_CLOSE
	je	wpoClose

	jmp	wpoBack

	; -- handle sizing --

wpoSizing:	mov	rcx, lParam
	mov	eax, [rcx.RECT.right]
	sub	eax, [rcx.RECT.left]

	mov	rcx, [r12.CLASS_APP.unBtnRows]
	inc	rcx
	imul	rcx, DEF_BUTTON_GAP

	sub	eax, ecx
	jle	wpoZero

	cdq
	idiv	[r12.CLASS_APP.unBtnRows]
	imul	[r12.CLASS_APP.unBtnRows]
	add	eax, ecx

	mov	rcx, lParam
	add	eax, [rcx.RECT.left]
	mov	[rcx.RECT.right], eax
	jmp	wpoZero

	; -- layout main and child windows --

wpoLayout:	lea	rdx, rcApp
	mov	rcx, hwndApp
	call	GetClientRect

	lea	rdx, rcApp
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnResize]

	jmp	wpoZero

	; -- paint main window --

wpoPaint:	lea	rdx, xPaint
	mov	rcx, hwndApp
	call	BeginPaint
	mov	hdcApp, rax

	; -- loop buttons --

	mov	r14, [r12.CLASS_APP.pxButtons]
	mov	rax, [r12.CLASS_APP.unBtnCols]
	imul	rax, [r12.CLASS_APP.unBtnRows]

	mov	unLoop, rax

appPLoop:	lea	rdx, rcButton
	mov	rcx, [r14]
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnGetRect]

	lea	r9, rcButton
	mov	r8, DFCS_BUTTONPUSH
	mov	rdx, hdcApp
	mov	rcx, [r14]
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnRender]

	add	r14, sizeof QWORD

	dec	unLoop
	jne	appPLoop

	lea	rdx, xPaint
	mov	rcx, hwndApp
	call	EndPaint

	jmp	wpoBack

	; -- set path color --

wpoPathColor:	mov	rcx, lParam
	call	GetDlgCtrlID

	movsxd	rax, eax
	sub	rax, 2

	mov	rcx, [r12.CLASS_APP.pxActive]
	cmp	rax, [rcx.CLASS_LIST.idList]
	je	wpoSetCurPath

	mov	rdx, [r12.CLASS_APP.unOthCol]
	mov	rax, [r12.CLASS_APP.hbrOthPath]
	jmp	wpoSetAktPath

wpoSetCurPath:	mov	rdx, [r12.CLASS_APP.unCurCol]
	mov	rax, [r12.CLASS_APP.hbrCurPath]

wpoSetAktPath:	mov	hbrColor, rax

	mov	rcx, wParam
	call	SetBkColor

	mov	rax, hbrColor
	jmp	wpoExit

	; -- click start --

wpoLeftDown:	mov	rax, lParam
	mov	rdx, rax
	shr	rdx, 16
	and	rax, 0FFFFh
	and	rdx, 0FFFFh

	mov	[r12.CLASS_APP.pntButton.POINT.y], edx
	mov	[r12.CLASS_APP.pntButton.POINT.x], eax

	lea	r9, rcApp
	mov	r8, rdx
	mov	rdx, rax
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFindButton]
	test	rax, rax
	jz	wpoZero

	mov	pxActive, rax

	mov	rcx, hwndApp
	call	GetDC
	mov	hdcApp, rax

	lea	r9, rcApp
	mov	r8, DFCS_BUTTONPUSH OR DFCS_PUSHED
	mov	rdx, hdcApp
	mov	rcx, pxActive
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnRender]

	mov	rdx, hdcApp
	mov	rcx, hwndApp
	call	ReleaseDC

	mov	[r12.CLASS_APP.fButton], TRUE
	jmp	wpoZero

	; -- click end --

wpoLeftUp:	cmp	[r12.CLASS_APP.fButton], FALSE
	je	wpoZero

	lea	r9, rcApp
	movsxd	r8, [r12.CLASS_APP.pntButton.POINT.y]
	movsxd	rdx, [r12.CLASS_APP.pntButton.POINT.x]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFindButton]
	test	rax, rax
	jz	wpoZero

	mov	pxActive, rax

	; -- draw new button shape --

	mov	rcx, hwndApp
	call	GetDC
	mov	hdcApp, rax

	lea	r9, rcApp
	mov	r8, DFCS_BUTTONPUSH
	mov	rdx, hdcApp
	mov	rcx, pxActive
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnRender]

	mov	rdx, hdcApp
	mov	rcx, hwndApp
	call	ReleaseDC

	; -- execute button --

	mov	rdx, pxActive
	mov	rcx, [r12.CLASS_APP.pxCommand]
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnExecute]

	mov	[r12.CLASS_APP.fButton], FALSE
	jmp	wpoZero

	; -- clicked right --

wpoRightUp:	mov	rax, lParam
	mov	rdx, rax
	shr	rdx, 16
	and	rax, 0FFFFh
	and	rdx, 0FFFFh

	lea	r9, ptMenu
	mov	[r9.POINT.x], eax
	mov	[r9.POINT.y], edx

	lea	r9, rcApp
	mov	r8, rdx
	mov	rdx, rax
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFindButton]
	test	rax, rax
	jz	wpoZero

	mov	[r12.CLASS_APP.pxButton], rax

	; -- load and open popup menu --

	mov	edx, IDM_BUTTONPOP
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadMenu
	mov	hmenuConfig, rax

	mov	edx, 0
	mov	rcx, hmenuConfig
	call	GetSubMenu
	mov	hmenuPopup, rax

	lea	edx, ptMenu
	mov	rcx, hwndApp
	call	ClientToScreen

	lea	rdx, ptMenu
	mov	qword ptr [rsp + 48], 0
	mov	rax, hwndApp
	mov	[rsp + 40], rax
	mov	dword ptr [rsp + 32], 0
	mov	r9d, [rdx.POINT.y]
	mov	r8d, [rdx.POINT.x]
	mov	edx, 0
	mov	rcx, hmenuPopup
	call	TrackPopupMenu

	mov	rcx, hmenuConfig
	call	DestroyMenu

	jmp	wpoZero

	; -- handle mouse moves --

wpoMouseMove:	cmp	[r12.CLASS_APP.fButton], FALSE
	je	wpoZero

	lea	r9, rcApp
	movsxd	r8, [r12.CLASS_APP.pntButton.POINT.y]
	movsxd	rdx, [r12.CLASS_APP.pntButton.POINT.x]
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFindButton]
	test	rax, rax
	je	wpoZero

	mov	pxActive, rax

	; -- get new hovering button --

	mov	rdx, lParam
	mov	r8, rdx
	shr	r8, 16
	and	rdx, 0FFFFh
	and	r8, 0FFFFh

	lea	r9, rcEdit
	mov	rcx, r12
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnFindButton]
	test	rax, rax
	je	wpoZero
	cmp	rax, pxActive
	je	wpoZero

	; -- "unpush" old button --

	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	GetDC
	mov	hdcApp, rax

	lea	r9, rcApp
	mov	r8, DFCS_BUTTONPUSH
	mov	rdx, hdcApp
	mov	rcx, pxActive
	mov	rax, [rcx.CLASS_BUTTON.vtableThis]
	call	[rax.CLASS_BUTTON_IFACE.pfnRender]

	mov	rdx, hdcApp
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	ReleaseDC

	mov	[r12.CLASS_APP.fButton], FALSE
	jmp	wpoZero

	; -- handle notifications --

wpoNotify:	mov	rax, lParam
	mov	rax, [rax.NMHDR.idFrom]

	cmp	rax, IDC_LEFT
	je	wpoList
	cmp	rax, IDC_RIGHT
	je	wpoList

	jmp	wpoZero

	; -- notify from list --

wpoList:	mov	rax, lParam
	mov	rcx, [rax.NMHDR.hwndFrom]
	test	rcx, rcx
	jz	wpoZero

	mov	rcx, [rax.NMHDR.hwndFrom]
	mov	edx, [rax.NMHDR.lcode]
	cmp	edx, HDN_ITEMCHANGED
	jne	listDirect

	mov	rcx, [rax.NMHDR.hwndFrom]
	call	GetParent
	mov	rcx, rax

listDirect:	mov	edx, GWLP_USERDATA
	call	GetWindowLongPtr
	test	rax, rax
	jz	wpoZero

	mov	rdx, lParam
	mov	rcx, rax
	mov	rax, [rcx.CLASS_LIST.vtableThis]
	call	[rax.CLASS_LIST_IFACE.pfnHandleNotify]

	jmp	wpoZero

	; -- key down --

wpoKeyDown:	mov	rax, wParam
	and	rax, 0FFFFH

	; -- skip some keys --

	cmp	rax, VK_ESCAPE
	je	wpoChar
	cmp	rax, VK_RETURN
	je	wpoChar
	cmp	rax, VK_TAB
	je	wpoChar
	cmp	rax, VK_CLEAR
	je	wpoChar
	cmp	rax, VK_PRIOR
	jge	wpoRange1
	jmp	wpoBack

wpoRange1:	cmp	rax, VK_HELP
	jle	wpoChar
	cmp	rax, VK_F1
	jge	wpoRange2
	jmp	wpoBack

wpoRange2:	cmp	rax, VK_F24
	jle	wpoChar
	jmp	wpoBack

	; -- char pressed --

wpoChar:	mov	rcx, wParam
	call	VkKeyScan
comment #
	mov	rax, wParam;lParam
;	shr	rax, 16
;	and	rax, 01FFh
;	mov	unKey, rax

	mov	ecx, VK_SHIFT
	call	GetAsyncKeyState
	test	ax, 8000h
	jz	wpoCtrl

	or	word ptr unKey + 2, HOTKEYF_SHIFT

wpoCtrl:	mov	ecx,VK_CONTROL
	call	GetAsyncKeyState
	test	ax, 8000h
	jz	wpoDoChar

	or	word ptr unKey + 2, HOTKEYF_CONTROL

	; -- match key for button shortcuts --
-#

wpoDoChar:	mov	rdx, unKey
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnMatchShortcut]
	test	rax, rax
	jz	wpoZero

	mov	pxActive, rax

	; -- execute button --

	mov	rdx, pxActive
	mov	rcx, [r12.CLASS_APP.pxCommand]
	mov	rax, [rcx.CLASS_COMMAND.vtableThis]
	call	[rax.CLASS_COMMAND_IFACE.pfnExecute]

	jmp	wpoZero

	; -- handle commands --

wpoCommand:	mov	rdx, wParam
	and	rdx, 0FFFFh
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnHandleEvent]

	jmp	wpoZero

	; -- close window --

wpoClose:	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnConfirmClose]
	test	rax, rax
	jnz	wpoZero

	mov	rcx, [r12.CLASS_APP.hevStop]
	call	SetEvent

	jmp	wpoZero

	; -- use default processing --

wpoBack:	mov	rax, lParam
	mov	[rsp + 32], rax
	mov	r9, wParam
	mov	r8d, unMessage
	mov	rdx, hwndApp
	lea	rcx, DefWindowProc
	call	CallWindowProc

	jmp	wpoExit

wpoZero:	xor	rax, rax

wpoExit:	add	rsp, 128
	add	rsp, 10 * 8 + 4 + sizeof POINT + 3 * sizeof RECT + sizeof PAINTSTRUCT + 8

	pop	r12
	pop	rbp
	ret	0

	align 4

wndprcApp	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for main configuration dialog
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	fHandled dlgprcConfig (hwndDlg, unMsg, wParam, lParam)
;	[in] hwndDlg .. dialog to handle
;	[in] unMsg .. message code to handle
;	[in] wParam .. message parameter 1
;	[in] lParam .. message parameter 2
; returns:	true for handled, else zero
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcConfig	PROC	FRAME
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
	sub	rsp, 64
	sub	rsp, 4 * 8 + 8
	.allocstack	64 + 4 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dpcInit
	cmp	eax, WM_COMMAND
	je	dpcCommand
	cmp	eax, WM_CLOSE
	je	dpcClose

	jmp	dpcZero

	; -- init dialog --

dpcInit:	mov	r12, lParam

	mov	rax, [r12.CLASS_APP.unBtnRows]
	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, UDM_SETPOS32
	mov	edx, ID_CF_BUTTONROWS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	rax, [r12.CLASS_APP.unBtnCols]
	mov	[rsp + 32], rax
	mov	r9d, 0
	mov	r8d, UDM_SETPOS32
	mov	edx, ID_CF_BUTTONCOLS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	dword ptr [rsp + 32], 12
	mov	r9d, 4
	mov	r8d, UDM_SETRANGE32
	mov	edx, ID_CF_BUTTONROWS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	dword ptr [rsp + 32], 8
	mov	r9d, 1
	mov	r8d, UDM_SETRANGE32
	mov	edx, ID_CF_BUTTONCOLS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- set delete confirm --

	mov	rax, [r12.CLASS_APP.fDelConf]
	test	rax, rax
	jnz	dpcCheck

	mov	r9d, BST_UNCHECKED
	jmp	dpcDelCnf

dpcCheck:	mov	r9d, BST_CHECKED

dpcDelCnf:	mov	r8d, BM_SETCHECK
	mov	edx, ID_CF_DELCONFIRM
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	; -- put main to dialog --

	mov	r8, r12
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	rax, TRUE
	jmp	dpcExit

	; -- handle user actions --

dpcCommand:	mov	rax, wParam
	cmp	ax, IDOK
	je	dpcOK
	cmp	ax, IDCANCEL
	je	dpcCancel

	jmp	dpcZero

	; -- ok pressed --

dpcOK:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	test	rax, rax
	jz	dpcExit

	mov	r12, rax

	; -- get del confirm --

	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, BM_GETCHECK
	mov	edx, ID_CF_DELCONFIRM
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	cmp	eax, BST_CHECKED
	je	dpcDelOn

	mov	[r12.CLASS_APP.fDelConf], FALSE
	jmp	dpcStCols

dpcDelOn:	mov	[r12.CLASS_APP.fDelConf], TRUE

	; -- get cols --

dpcStCols:	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, UDM_GETPOS32
	mov	edx, ID_CF_BUTTONCOLS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	and	rax, 0FFFFFFFFh

	cmp	rax, 4
	jl	dpcClip
	cmp	rax, 12
	jg	dpcClip

	mov	[r12.CLASS_APP.unBtnCols], rax
	jmp	dpcRows

dpcClip:	mov	[r12.CLASS_APP.unBtnCols], DEF_BUTTON_COLS

	; -- get rows --

dpcRows:	mov	dword ptr [rsp + 32], 0
	mov	r9d, 0
	mov	r8d, UDM_GETPOS32
	mov	edx, ID_CF_BUTTONROWS
	mov	rcx, hwndDlg
	call	SendDlgItemMessage
	and	rax, 0FFFFFFFFh

	cmp	rax, 1
	jl	dpcClip2
	cmp	rax, 8
	jg	dpcClip2

	mov	[r12.CLASS_APP.unBtnRows], rax
	jmp	dpcStore

dpcClip2:	mov	[r12.CLASS_APP.unBtnRows], DEF_BUTTON_ROWS

	; -- store data --

dpcStore:	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnSaveConfig]

	; -- reload button config --

	mov	rcx, [r12.CLASS_APP.pxButtons]
	call	GlobalFree

	mov	[r12.CLASS_APP.pxButtons], 0

	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnInitButtons]

	; -- resize window --

	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_SIZE
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	SendMessage

	mov	r8d, TRUE
	mov	rdx, 0
	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	InvalidateRect

	mov	rcx, [r12.CLASS_APP.hwndApp]
	call	UpdateWindow

	; -- cancel pressed --

dpcCancel:	mov	r9d, 0
	mov	r8d, 0
	mov	edx, WM_CLOSE
	mov	rcx, hwndDlg
	call	SendMessage

	mov	rax, TRUE
	jmp	dpcExit

	; -- close dialog --

dpcClose:	mov	rcx, hwndDlg
	call	DestroyWindow

	mov	rax, TRUE
	jmp	dpcExit

dpcZero:	xor	rax, rax

dpcExit:	add	rsp, 64
	add	rsp, 4 * 8 + 8

	pop	r12
	pop	rbp

	ret	0

	align	4

dlgprcConfig	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for shortcut key configuration
; last update:	2013-02-28 - Deutsch - make x64
; parameters:	fHandled dlgprcKey (hwndDlg, unMsg, wParam, lParam)
;	[in] hwndDlg .. dialog to handle
;	[in] unMsg .. message code to handle
;	[in] wParam .. message parameter 1
;	[in] lParam .. message parameter 2
; returns:	true for handled, else zero
;------------------------------------------------------------------------------------------------------------------------------------------

dlgprcKey	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	punKey:QWORD	; result value

	push	rbp
	.pushreg	rbp
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 48
	sub	rsp, 5 * 8 + 8
	.allocstack	48 + 5 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dpkInit
	cmp	eax, WM_COMMAND
	je	dpkCmd
	cmp	eax, WM_CLOSE
	je	dpkClose

	jmp	dpkZero

	; --  init dialog --

dpkInit:	mov	r8, lParam
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	mov	rax, lParam

	mov	qword ptr [rsp + 32], 0
	mov	r9, [rax]
	mov	r8, HKM_SETHOTKEY
	mov	edx, ID_SC_KEY
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	 ; -- init done --

	mov	rax, TRUE
	jmp	dpkExit

	; -- handle commands --

dpkCmd:	mov	rax, wParam
	shr	rax, 16
	cmp	ax, BN_CLICKED
	je	dpkButton

	jmp	dpkZero

	; -- button pressed --

dpkButton:	mov	rax, wParam
	cmp	ax, IDOK
	je	dpkDone
	cmp	ax, IDCANCEL
	je	dpkClose

	jmp	dpkClose

	; -- store new key --

dpkDone:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	test	rax, rax
	jz	dpkClose

	mov	punKey, rax

	; -- get resulting scan code --

	mov	qword ptr [rsp + 32], 0
	mov	r9, 0
	mov	r8, HKM_GETHOTKEY
	mov	edx, ID_SC_KEY
	mov	rcx, hwndDlg
	call	SendDlgItemMessage

	mov	rcx, punKey
	mov	[rcx], rax

	jmp	dpkClose

	; -- close dialog --

dpkClose:	mov	rdx, 0
	mov	rcx, hwndDlg
	call	EndDialog

dpkZero:	xor	rax, rax

dpkExit:	add	rsp, 48
	add	rsp, 5 * 8 + 8

	pop	rbp

	ret	0

	align	4

dlgprcKey	ENDP

	END
