;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - setup folder handling
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

	include	setup.inc


;----------------------------------------------------------------------------------------------------------------------
;	code segment
;----------------------------------------------------------------------------------------------------------------------

	.code


;----------------------------------------------------------------------------------------------------------------------
; does:	dialog handler for target folder selection
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	unError dlgprcDirectory (hwndDlg, unMessage, wParam, lParam)
; returns:	zero for ok, or error code
;----------------------------------------------------------------------------------------------------------------------

dlgprcDirectory	PROC	FRAME
	LOCAL	hwndDlg:QWORD	; button dialog
	LOCAL	wParam:QWORD	; message parameter 1
	LOCAL	lParam:QWORD	; message parameter 2
	LOCAL	unMessage:DWORD	; message to process
	LOCAL	unSize:QWORD
	LOCAL	ptxMessage:QWORD
	LOCAL	pxPidl:QWORD
	LOCAL	txPath [1024]:WORD
	LOCAL	txChoose [1024]:WORD
	LOCAL	xBrowseInfo:BROWSEINFO

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 7 * 8 + 2 * 1024 + 2 * 1024 + sizeof BROWSEINFO
	sub	rsp, 128
	.allocstack	128 + 7 * 8 + 2 * 1024 + 2 * 1024 + sizeof BROWSEINFO
	.endprolog

	; -- get parameter --

	mov	hwndDlg, rcx
	mov	unMessage, edx
	mov	wParam, r8
	mov	lParam, r9

	; -- branch on message --

	mov	eax, unMessage
	cmp	eax, WM_INITDIALOG
	je	dirInitDialog
	cmp	eax, WM_COMMAND
	je	dirCommand

	xor	eax, eax
	jmp	dirExit

	; -- init dialog --

dirInitDialog:	mov	r12, lParam

	; -- get default path --

	mov	r9d, 1024 - 1
	lea	r8, txPath
	mov	edx, IDS_PROGRAM_PATH
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	; -- get windows path --

	mov	pxPidl, 0

	lea	r8, pxPidl
	mov	edx, CSIDL_PROGRAM_FILES
	mov	rcx, hwndDlg
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	dirAppend

	lea	rdx, txPath
	mov	rcx, pxPidl
	call	SHGetPathFromIDList
	test	eax, eax
	je	dirAppend

	mov	rcx, pxPidl
	call	CoTaskMemFree

	; -- append name of program --

dirAppend:	lea	rcx, txPath
	call	lstrlen

	lea	r8, txPath
	lea	r8, [r8 + 2 * rax]

	mov	word ptr [r8], "\"
	add	r8, 2

	mov	r9d, 1024
	mov	edx, IDS_DEFAULT_PATH
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	lea	r8, txPath
	mov	edx, ID_DI_PATH
	mov	rcx, hwndDlg
	call	SetDlgItemText

	mov	r8, lParam
	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	SetWindowLongPtr

	jmp	dirHandled


	; -- command handling --

dirCommand:	mov	rax, wParam
	cmp	ax, ID_DI_PATH
	je	dirEditPath

	cmp	word ptr wParam + 2, BN_CLICKED
	jne	dirHandled

	cmp	ax, ID_DI_BUTTON
	je	dirChoosing
	cmp	ax, IDC_PREVPAGE
	je	dirPrevPage
	cmp	ax, IDC_NEXTPAGE
	je	dirNextPage
	cmp	ax, IDCANCEL
	je	dirUserExit

	jmp	dirHandled

	; -- path event - check for kill focus --

dirEditPath:	cmp	word ptr wParam + 2, EN_KILLFOCUS
	jne	dirHandled

	; -- retrieve users input --

	mov	r9d, 1024
	lea	r8, txPath
	mov	edx, ID_DI_PATH
	mov	rcx, hwndDlg
	call	GetDlgItemText
	test	eax, eax
	jne	dirHandled

	; -- reset path to default if no input --

	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	r9, r12
	mov	r8, 0
	mov	edx, WM_INITDIALOG
	mov	rcx, hwndDlg
	call	SendMessage

	jmp	dirHandled

	; -- back button --

dirPrevPage:	mov	edx, SETUP_PREV
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	dirHandled

	; -- next button --

dirNextPage:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	r9d, 1024
	lea	r8, txChoose
	mov	edx, ID_DI_PATH
	mov	rcx, hwndDlg
	call	GetDlgItemText

	lea	r9, unSize
	lea	r8, txPath
	mov	edx, 1024
	lea	rcx, txChoose
	call	GetFullPathNameW

	lea	rcx, txPath
	call	GetFileAttributes

	cmp	eax, INVALID_HANDLE_VALUE
	je	dnpCreate
	test	eax, FILE_ATTRIBUTE_DIRECTORY
	jne	dnpOkay

	; -- choosen directory doesn't exists --

dnpCreate:	lea	rdx, txPath
	mov	dword ptr [rsp + 40], MB_OKCANCEL OR MB_ICONQUESTION
	mov	qword ptr [rsp + 32], rdx
	mov	r9d, IDS_CREATE_DIR
	mov	r8d, IDS_CONFIRM_TITLE
	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnPathMessage]

	cmp	eax, IDCANCEL
	je	dirHandled

	mov	r8, 0
	lea	rdx, txPath
	mov	rcx, hwndDlg
	call	SHCreateDirectoryEx
	cmp	eax, ERROR_SUCCESS
	je	dnpOkay

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
	lea	r8, txPath
	mov	edx, IDS_ERROR_TITLE
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, MB_OK OR MB_ICONSTOP
	lea	r8, txPath
	mov	rdx, ptxMessage
	mov	rcx, hwndDlg
	call	MessageBox

	jmp	dirHandled

	; -- choosen directory exists --

dnpOkay:	lea	rdx, txPath
	lea	rcx, [r12.CLASS_INSTALL_APP.txPath]
	call	lstrcpy

	mov	edx, SETUP_NEXT
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	dirHandled

	; -- cancel button --

dirUserExit:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	mov	rdx, hwndDlg
	mov	rcx, r12
	mov	rax, [r12.CLASS_INSTALL_APP.vtableThis]
	call	[rax.CLASS_INSTALL_APP_IFACE.pfnConfirmQuit]
	cmp	eax, IDYES
	jne	dirHandled

	mov	edx, SETUP_BREAK
	mov	rcx, hwndDlg
	call	EndDialog

	jmp	dirHandled

	; -- choose directory button --

dirChoosing:	mov	edx, DWLP_USER
	mov	rcx, hwndDlg
	call	GetWindowLongPtr
	mov	r12, rax

	lea	r8, pxPidl
	mov	edx, CSIDL_DRIVES
	mov	rcx, hwndDlg
	call	SHGetSpecialFolderLocation
	test	eax, eax
	jne	dirHandled

	; -- get title string --

	mov	r9d, 1024
	lea	r8, txChoose
	mov	edx, IDS_CHOOSE_PATH
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	; -- fill browse parameters --

	lea	rcx, xBrowseInfo
	mov	rdx, hwndDlg
	mov	[rcx.BROWSEINFO.hwndOwner], rdx
	mov	rdx, pxPidl
	mov	[rcx.BROWSEINFO.pidlRoot], rdx
	lea	rdx, txPath
	mov	[rcx.BROWSEINFO.lpszDisplay], rdx
	lea	rdx, txChoose
	mov	[rcx.BROWSEINFO.lpszTitle], rdx
	mov	[rcx.BROWSEINFO.ulFlags], BIF_RETURNONLYFSDIRS
  	mov	[rcx.BROWSEINFO.lpfn], 0
	mov	[rcx.BROWSEINFO.lParam], 0
	mov	[rcx.BROWSEINFO.iImage], 0

	call	SHBrowseForFolder
	test	eax, eax
	je	dwcFree

	; -- make string from pidl --

	lea	rdx, txPath
	mov	rcx, rax
	call	SHGetPathFromIDList
	test	eax, eax
	je	dwcFree

	lea	rcx, txPath
	call	lstrlen

	lea	r8, txPath
	cmp	word ptr [r8 + 2 * rax - 2], "\"
	je	dchAppend

	mov	word ptr [r8 + 2 * rax], "\"
	inc	eax

dchAppend:	lea	r8, [r8 + 2 * rax]

	mov	r9d, 1024
	mov	edx, IDS_DEFAULT_PATH
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	lea	r8, txPath
	mov	edx, ID_DI_PATH
	mov	rcx, hwndDlg
	call	SetDlgItemText

dwcFree:	mov	rcx, pxPIDL
	call	CoTaskMemFree

dirHandled:	mov	eax, TRUE

dirExit:	add	rsp, 128
	add	rsp, 7 * 8 + 2 * 1024 + 2 * 1024 + sizeof BROWSEINFO

	pop	r12
	pop	rbp
	ret	0

	align	4

dlgprcDirectory	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	displays a message box with extended path information
; last update:	2003-10-13 - Scholz - created
;	2014-08-28 - Deutsch - make x64
; parameters:	idButton appPathMessage (pxApp, hwndDlg, idTitle, idMessage, ptxPath, unMsgFlags)
; returns:	resulting button id (IDNO, IDCANCEL)
;----------------------------------------------------------------------------------------------------------------------

appPathMessage	PROC	FRAME
	LOCAL	hwndDlg:QWORD
	LOCAL	idTitle:DWORD
	LOCAL	idMessage:DWORD
	LOCAL	ptxPath:QWORD
	LOCAL	unMsgFlags:DWORD
	LOCAL	txTitle [128]:WORD
	LOCAL	txText [128]:WORD
	LOCAL	txFormat [128]:WORD

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 5 * 8 + 2 * 128 + 2 * 128 + 2 * 128
	sub	rsp, 128
	.allocstack	128 + 5 * 8 + 2 * 128 + 2 * 128 + 2 * 128
	.endprolog

	; -- get parameter --

	mov	r12, rcx
	mov	hwndDlg, rdx
	mov	idTitle, r8d
	mov	idMessage, r9d
	mov	rdx, [rbp + 3 * 8 + 32]
	mov	ptxPath, rdx
	mov	edx, [rbp + 3 * 8 + 40]
	mov	unMsgFlags, edx

	mov	r9d, 128
	lea	r8, txTitle
	mov	edx, idTitle
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r9d, 128
	lea	r8, txFormat
	mov	edx, idMessage
	mov	rcx, [r12.CLASS_INSTALL_APP.hinstApp]
	call	LoadString

	mov	r8, ptxPath
	lea	rdx, txFormat
	lea	rcx, txText
	call	wsprintfW

	mov	r9d, unMsgFlags
	lea	r8, txTitle
	lea	rdx, txText
	mov	rcx, hwndDlg
	call	MessageBox

	add	rsp, 128
	add	rsp, 5 * 8 + 2 * 128 + 2 * 128 + 2 * 128

	pop	r12
	pop	rbp
	ret	0

	align	4

appPathMessage	ENDP

	END
