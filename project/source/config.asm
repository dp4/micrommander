;----------------T---------------T--------------------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - configuration load and store
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
	include	commdlg.inc

	include	app.inc
	include	config.inc
	include	resource.inc


;------------------------------------------------------------------------------------------------------------------------------------------
;	code segment
;------------------------------------------------------------------------------------------------------------------------------------------

	.code


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	create new configuration helper object
; last update:	2013-02-20 - Deutsch - make x64
; parameters:	pxConfig configNew ()
; returns:	new object or zero for error
;------------------------------------------------------------------------------------------------------------------------------------------

configNew	PROC	FRAME

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
	jz	conExit

	mov	r8, sizeof CLASS_CONFIG
	mov	edx, HEAP_ZERO_MEMORY
	mov	rcx, rax
	call	HeapAlloc
	test	rax, rax
	jz	conExit

	; -- prepare vtable --

	lea	rcx, [rax.CLASS_CONFIG.xInterface]
	mov	[rax.CLASS_CONFIG.vtableThis], rcx

	lea	rdx, configInit
	mov	[rcx.CLASS_CONFIG_IFACE.pfnInit], rdx
	lea	rdx, configColorDialog
	mov	[rcx.CLASS_CONFIG_IFACE.pfnColorDialog], rdx
	lea	rdx, configFontDialog
	mov	[rcx.CLASS_CONFIG_IFACE.pfnFontDialog], rdx
	lea	rdx, appGetConfigView
	mov	[rcx.CLASS_CONFIG_IFACE.pfnGetConfigView], rdx
	lea	rdx, configSetView
	mov	[rcx.CLASS_CONFIG_IFACE.pfnSetConfigView], rdx
	lea	rdx, configGetNumber
	mov	[rcx.CLASS_CONFIG_IFACE.pfnGetConfigNumber], rdx
	lea	rdx, configSetNumber
	mov	[rcx.CLASS_CONFIG_IFACE.pfnSetConfigNumber], rdx
	lea	rdx, configGetText
	mov	[rcx.CLASS_CONFIG_IFACE.pfnGetConfigText], rdx
	lea	rdx, configSetText
	mov	[rcx.CLASS_CONFIG_IFACE.pfnSetConfigText], rdx

conExit:	add	rsp, 32
	pop	rbp
	ret	0

	align	4

configNew	ENDP


;------------------------------------------------------------------------------------------------------------------------------------------
; does:	init configuration helper - get configuration ini file, get section name
; last update:	2013-02-18 - Deutsch - make x64
; parameters:	unError configInit (pxApp)
;	[in] pxApp .. main application
; returns:	zero for ok, else error code
;------------------------------------------------------------------------------------------------------------------------------------------

configInit	PROC	FRAME
	LOCAL	hresConfig:QWORD	; default configuration
	LOCAL	unSize:QWORD	; default INI size
	LOCAL	hfileNew:QWORD	; default INI file
	LOCAL	unCount:QWORD	; written bytes

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8
	sub	rsp, 64
	.allocstack	64 + 4 * 8
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	r12, rdx

	mov	[r14.CLASS_CONFIG.pxApp], r12

	lea	rdx, [r14.CLASS_CONFIG.txConfig]
	mov	rcx, r12
	mov	rax, [r12.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnGetConfigPath]

	lea	rcx, [r14.CLASS_CONFIG.txConfig]
	call	GetFileAttributes
	cmp	eax, INVALID_FILE_ATTRIBUTES
	jne	cinDone

	; -- save default ini file --

	mov	r8d, RT_RCDATA
	mov	rdx, IDB_DEFAULT_INI
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	FindResource
	mov	hresConfig, rax

	mov	rdx, hresConfig
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	SizeofResource
	mov	unSize, rax

	mov	dword ptr [rsp + 48], 0
	mov	dword ptr [rsp + 40], FILE_ATTRIBUTE_NORMAL
	mov	dword ptr [rsp + 32], CREATE_ALWAYS
	mov	r9d, 0
	mov	r8d, 0
	mov	edx, GENERIC_WRITE
	lea	rcx, [r14.CLASS_CONFIG.txConfig]
	call	CreateFile
	cmp	eax, INVALID_HANDLE_VALUE
	jz	cinDone

	mov	hfileNew, rax

	mov	rdx, hresConfig
	mov	rcx, [r12.CLASS_APP.hinstApp]
	call	LoadResource

	mov	qword ptr [rsp + 32], 0
	lea	r9, unCount
	mov	r8, unSize
	mov	rdx, rax
	mov	rcx, hfileNew
	call	WriteFile

	mov	rcx, hfileNew
	call	CloseHandle

cinDone:	xor	rax, rax

	add	rsp, 64
	add	rsp, 4 * 8

	pop	r14
	pop	r12
	pop	rbp

	ret	0

	align	4

configInit	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	open font selection dialog
; last update:	1999-04-14 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError configFontDialog (pxView)
;	[in/out] pxView .. view with font attributes
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

configFontDialog	PROC	FRAME
	LOCAL	xFont:LOGFONT	; font description
	LOCAL	xChoose:CHOOSE_FONT	; dialog parameter

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, sizeof CHOOSE_FONT + sizeof LOGFONT + 4 + 8
	sub	rsp, 32
	.allocstack	32 + sizeof CHOOSE_FONT + sizeof LOGFONT + 4 + 8
	.endprolog

	; -- get parameter --

	mov	r12, [rcx.CLASS_CONFIG.pxApp]
	mov	r15, rdx

	; -- fill font information from view parameter --

	lea	rcx, xFont
	mov	rax, [r15.VIEW_PARAM.unFontSize]
	mov	[rcx.LOGFONT.lfHeight], eax
	mov	[rcx.LOGFONT.lfWidth], 0
	mov	[rcx.LOGFONT.lfEscapement], 0
	mov	[rcx.LOGFONT.lfOrientation], 0
	mov	rax, [r15.VIEW_PARAM.unWeight]
	mov	[rcx.LOGFONT.lfWeight], eax
	mov	rax, [r15.VIEW_PARAM.unItalic]
	mov	[rcx.LOGFONT.lfItalic], al
	mov	[rcx.LOGFONT.lfUnderline], FALSE
	mov	[rcx.LOGFONT.lfStrikeOut], FALSE
	mov	[rcx.LOGFONT.lfCharSet], DEFAULT_CHARSET
	mov	[rcx.LOGFONT.lfOutPrecision], OUT_DEFAULT_PRECIS
	mov	[rcx.LOGFONT.lfClipPrecision], CLIP_DEFAULT_PRECIS
	mov	[rcx.LOGFONT.lfQuality], DEFAULT_QUALITY
	mov	[rcx.LOGFONT.lfPitchAndFamily], DEFAULT_PITCH OR FF_DONTCARE
	
	mov	r8d, LF_FACESIZE
	lea	rdx, [r15.VIEW_PARAM.txFontName]
	lea	rcx, [rcx.LOGFONT.lfFaceName]
	call	lstrcpyn 

	; -- font dialog --

	lea	rcx, xChoose
	mov	[rcx.CHOOSE_FONT.lStructSize], sizeof CHOOSE_FONT
	mov	rax, [r12.CLASS_APP.hwndApp]
	mov	[rcx.CHOOSE_FONT.hwndOwner], rax
	mov	[rcx.CHOOSE_FONT.hDC], 0
	lea	rax, xFont
	mov	[rcx.CHOOSE_FONT.lpLogFont], rax
	mov	[rcx.CHOOSE_FONT.iPointSize], 0
	mov	[rcx.CHOOSE_FONT.Flags], CF_SCREENFONTS OR CF_FORCEFONTEXIST OR CF_INITTOLOGFONTSTRUCT
	mov	[rcx.CHOOSE_FONT.rgbColors], 0
	mov	[rcx.CHOOSE_FONT.lCustData], 0
	mov	[rcx.CHOOSE_FONT.lpfnHook], 0
	mov	[rcx.CHOOSE_FONT.lpTemplateName], 0
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rcx.CHOOSE_FONT.hInstance], rax
	mov	[rcx.CHOOSE_FONT.lpszStyle], 0
	mov	[rcx.CHOOSE_FONT.nFontType], 0
	mov	[rcx.CHOOSE_FONT.nSizeMin], 0
	mov	[rcx.CHOOSE_FONT.nSizeMax], 0
	call	ChooseFont
	test	eax, eax
	jz	cfdExit

	; -- fill font information from view parameter --

	lea	rcx, xFont
	mov	eax, [rcx.LOGFONT.lfHeight]
	and	rax, 0FFFFFFFFh
	mov	[r15.VIEW_PARAM.unFontSize], rax
	mov	eax, [rcx.LOGFONT.lfWeight]
	and	rax, 0FFFFFFFFh
	mov	[r15.VIEW_PARAM.unWeight], rax
	mov	al, [rcx.LOGFONT.lfItalic]
	and	rax, 0FFh
	mov	[r15.VIEW_PARAM.unItalic], rax
	
	mov	r8d, LF_FACESIZE
	lea	rdx, [rcx.LOGFONT.lfFaceName]
	lea	rcx, [r15.VIEW_PARAM.txFontName]
	call	lstrcpyn 

	xor	rax, rax

cfdExit:	add	rsp, 32
	add	rsp, sizeof CHOOSE_FONT + sizeof LOGFONT + 4 + 8

	pop	r15
	pop	r12
	pop	rbp
	ret	0

	align	4

configFontDialog	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	open color selection dialog
; last update:	1999-04-14 - Scholz - created
;	2013-02-28 - Deutsch - make x64
; parameters:	unError configColorDialog (punColor)
;	[in/out] punColor .. pointer to color
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

configColorDialog	PROC	FRAME
	LOCAL	punColor:QWORD	; ini file name buffer
	LOCAL	xChoose:CHOOSE_COLOR	; dialog parameter
	LOCAL	xColors [16]:DWORD	; user colors

	push	rbp
	.pushreg	rbp
	push	r12
	.pushreg	r12
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + sizeof CHOOSE_COLOR + 4 * 16 + 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8 + sizeof CHOOSE_COLOR + 4 * 16 + 8
	.endprolog

	; -- get parameter --

	mov	r12, [rcx.CLASS_CONFIG.pxApp]
	mov	punColor, rdx

	; -- open dialog --

	lea	rcx, xChoose
	mov	[rcx.CHOOSE_COLOR.lStructSize], sizeof CHOOSE_COLOR
	mov	rax, [r12.CLASS_APP.hwndApp]
	mov	[rcx.CHOOSE_COLOR.hwndOwner], rax
	mov	rax, [r12.CLASS_APP.hinstApp]
	mov	[rcx.CHOOSE_COLOR.hInstance], rax
	lea	rax, xColors
	mov	[rcx.CHOOSE_COLOR.lpCustColors], rax
	mov	rax, punColor
	mov	rax, [rax]
	mov	[rcx.CHOOSE_COLOR.rgbResult], eax
	mov	[rcx.CHOOSE_COLOR.Flags], CC_FULLOPEN OR CC_RGBINIT OR CC_SHOWHELP
	mov	[rcx.CHOOSE_COLOR.lCustData], 0
	mov	[rcx.CHOOSE_COLOR.lpfnHook], 0
	mov	[rcx.CHOOSE_COLOR.lpTemplateName], 0
	call	ChooseColor
	test	eax, eax
	jz	ccdCancel

	lea	rcx, xChoose
	mov	rdx, punColor
	mov	eax, [rcx.CHOOSE_COLOR.rgbResult]
	and	rax, 0FFFFFFFFh
	mov	[rdx], rax

	xor	rax, rax
	jmp	ccdExit

ccdCancel:	mov	rax, -1

ccdExit:	add	rsp, 32
	add	rsp, 1 * 8 + sizeof CHOOSE_COLOR + 4 * 16 + 8

	pop	r12
	pop	rbp
	ret	0

	align	4

configColorDialog	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	save a given text to config file
; last update:	2004-01-29 - Scholz - created
;	2013-02-28 - Deutsch - x64 translation
; parameters:	result configSetText (ptxSection, idParam, ptxValue)
;	[in] ptxSection .. name of section
;	[in] idParam .. key name string ID
;	[in] ptxText .. text to store
; returns:	depending on message
;----------------------------------------------------------------------------------------------------------------------

configSetText	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name
	LOCAL	idParam:QWORD
	LOCAL	ptxValue:QWORD
	LOCAL	txValue [64]:WORD	; value name

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * 64
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 2 * 64
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	idParam, r8
	mov	ptxValue, r9

	; -- get value name --

	lea	r9, txValue
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, idParam
	mov	rcx, [r14.CLASS_CONFIG.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, [r14.CLASS_CONFIG.txConfig]
	mov	r8, ptxValue
	lea	rdx, txValue
	mov	rcx, ptxSection
	call	WritePrivateProfileString

	xor	rax, rax

	add	rsp, 32
	add	rsp, 3 * 8 + 2 * 64

	pop	r14
	pop	rbp
	ret	0

	align	4

configSetText	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	save a given number to config file
; last update:	2004-01-29 - Scholz - created
;	2013-02-28 - Deutsch - x64 translation
; parameters:	unError configSetNumber (ptxSection, idParam, unValue)
;	[in] ptxSection .. name of section
;	[in] idParam .. key name string ID
;	[in] unValue .. number to store
; returns:	zero for ok, else error code
;----------------------------------------------------------------------------------------------------------------------

configSetNumber	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name
	LOCAL	idParam:QWORD
	LOCAL	unValue:QWORD
	LOCAL	txKey [64]:WORD	; value name
	LOCAL	txValue [64]:WORD	; value name
	LOCAL	txMask [64]:WORD	; decimal mask

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 3 * 8 + 2 * 64 + 2 * 64 + 2 * 64
	sub	rsp, 32
	.allocstack	32 + 3 * 8 + 2 * 64 + 2 * 64 + 2 * 64
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	idParam, r8
	mov	unValue, r9

	; -- value to string --

	lea	r9, txMask
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, IDS_DECMASK
	mov	rcx, [r14.CLASS_CONFIG.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	mov	r8, unValue
	lea	rdx, txMask
	lea	rcx, txValue
	call	wsprintf

	; -- get value name --

	lea	r9, txKey
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, idParam
	mov	rcx, [r14.CLASS_CONFIG.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, [r14.CLASS_CONFIG.txConfig]
	lea	r8, txValue
	lea	rdx, txKey
	mov	rcx, ptxSection
	call	WritePrivateProfileString

	xor	rax, rax

	add	rsp, 32
	add	rsp, 3 * 8 + 2 * 64 + 2 * 64 + 2 * 64

	pop	r14
	pop	rbp
	ret	0

	align	4

configSetNumber	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	save a given view configuration to config file
; last update:	2004-01-29 - Scholz - created
;	2013-02-28 - Deutsch - x64 translation
; parameters:	result configSetView (ptxSection, pxView)
;	[in] ptxSection .. name of section
;	[in] pxView .. view to store
; returns:	depending on message
;----------------------------------------------------------------------------------------------------------------------

configSetView	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 8
	sub	rsp, 32
	.allocstack	32 + 1 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	r15, r8

	; -- store background color --

	mov	r9, [r15.VIEW_PARAM.unBgColor]
	mov	r8, IDS_CFG_VIEWBACK
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- store foreground color --

	mov	r9, [r15.VIEW_PARAM.unFgColor]
	mov	r8, IDS_CFG_VIEWFORE
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- store font size --

	mov	r9, [r15.VIEW_PARAM.unFontSize]
	mov	r8, IDS_CFG_VIEWSIZE
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- store italic prop --

	mov	r9, [r15.VIEW_PARAM.unItalic]
	mov	r8, IDS_CFG_VIEWITALIC
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- store weight prop --

	mov	r9, [r15.VIEW_PARAM.unWeight]
	mov	r8, IDS_CFG_VIEWWEIGHT
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigNumber]

	; -- store font name --

	lea	r9, [r15.VIEW_PARAM.txFontName]
	mov	r8, IDS_CFG_VIEWFONT
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnSetConfigText]

	xor	rax, rax

	add	rsp, 32
	add	rsp, 1 * 8 + 8

	pop	r15
	pop	r14
	pop	rbp
	ret	0

	align	4

configSetView	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	load text from config file
; last update:	2013-02-28 - Deutsch - created
; parameters:	unError configGetText (ptxSection, idParam, ptxDefault, ptxValue)
;	[in] ptxSection .. name of section
;	[in] idParam .. key name string ID
;	[in] ptxDefault .. default value, if not present
;	[out] ptxValue .. resulting value
; returns:	depending on message
;----------------------------------------------------------------------------------------------------------------------

configGetText	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name
	LOCAL	idParam:QWORD
	LOCAL	ptxDefault:QWORD
	LOCAL	ptxValue:QWORD
	LOCAL	txValue [64]:WORD	; value name

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * 64 + 8
	sub	rsp, 64
	.allocstack	64 + 4 * 8 + 2 * 64 + 8
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	idParam, r8
	mov	ptxDefault, r9
	mov	rax, [rbp + 3 * 8 + 32]
	mov	ptxValue, rax

	; -- get value name --

	lea	r9, txValue
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, idParam
	mov	rcx, [r14.CLASS_CONFIG.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	rax, [r14.CLASS_CONFIG.txConfig]
	mov	[rsp + 40], rax
	mov	dword ptr [rsp + 32], DEF_PATH_LENGTH - 1
	mov	r9, ptxValue
	mov	r8, ptxDefault
	lea	rdx, txValue
	mov	rcx, ptxSection
	call	GetPrivateProfileString

	xor	rax, rax

	add	rsp, 64
	add	rsp, 4 * 8 + 2 * 64 + 8

	pop	r14
	pop	rbp
	ret	0

	align	4

configGetText	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	load number from config file
; last update:	2013-02-28 - Deutsch - created
; parameters:	unError configGetNumber (ptxSection, idParam, unDefault, punValue)
;	[in] ptxSection .. name of section
;	[in] idParam .. key name string ID
;	[in] unDefault .. default value, if not present
;	[out] punValue .. resulting value
; returns:	depending on message
;----------------------------------------------------------------------------------------------------------------------

configGetNumber	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name
	LOCAL	idParam:QWORD
	LOCAL	unDefault:QWORD
	LOCAL	punValue:QWORD
	LOCAL	txKey [64]:WORD	; value name

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 4 * 8 + 2 * 64 + 8
	sub	rsp, 32
	.allocstack	32 + 4 * 8 + 2 * 64 + 8
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	idParam, r8
	mov	unDefault, r9
	mov	rax, [rbp + 3 * 8 + 32]
	mov	punValue, rax

	; -- get value name --

	mov	rcx, punValue
	mov	rax, unDefault
	mov	[rcx], rax

	lea	r9, txKey
	mov	r8, SUBLANG_NEUTRAL SHL 10 OR LANG_NEUTRAL
	mov	rdx, idParam
	mov	rcx, [r14.CLASS_CONFIG.pxApp]
	mov	rax, [rcx.CLASS_APP.vtableThis]
	call	[rax.CLASS_APP_IFACE.pfnLoadString]

	lea	r9, [r14.CLASS_CONFIG.txConfig]
	mov	r8, unDefault
	lea	rdx, txKey
	mov	rcx, ptxSection
	call	GetPrivateProfileInt

	mov	rcx, punValue
	mov	[rcx], rax

	xor	rax, rax

	add	rsp, 32
	add	rsp, 4 * 8 + 2 * 64 + 8

	pop	r14
	pop	rbp
	ret	0

	align	4

configGetNumber	ENDP


;----------------------------------------------------------------------------------------------------------------------
; does:	load a given view configuration from config file
; last update:	2004-01-29 - Scholz - created
;	2013-02-28 - Deutsch - x64 translation
; parameters:	result appGetConfigView (ptxSection, pxView)
;	[in] ptxSection .. name of section
;	[out] pxView .. resulting view information
; returns:	depending on message
;----------------------------------------------------------------------------------------------------------------------

appGetConfigView	PROC	FRAME
	LOCAL	ptxSection:QWORD	; section name

	push	rbp
	.pushreg	rbp
	push	r14
	.pushreg	r14
	push	r15
	.pushreg	r15
	mov	rbp, rsp
	.setframe	rbp, 0
	sub	rsp, 1 * 8 + 8
	sub	rsp, 48
	.allocstack	48 + 1 * 8 + 8
	.endprolog

	; -- get parameter --

	mov	r14, rcx
	mov	ptxSection, rdx
	mov	r15, r8

	; -- load background color --

	lea	rax, [r15.VIEW_PARAM.unBgColor]
	mov	[rsp + 32], rax
	mov	r9, [r15.VIEW_PARAM.unBgColor]
	mov	r8, IDS_CFG_VIEWBACK
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load foreground color --

	lea	rax, [r15.VIEW_PARAM.unFgColor]
	mov	[rsp + 32], rax
	mov	r9, [r15.VIEW_PARAM.unFgColor]
	mov	r8, IDS_CFG_VIEWFORE
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load font size --

	lea	rax, [r15.VIEW_PARAM.unFontSize]
	mov	[rsp + 32], rax
	mov	r9, [r15.VIEW_PARAM.unFontSize]
	mov	r8, IDS_CFG_VIEWSIZE
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load italic prop --

	lea	rax, [r15.VIEW_PARAM.unItalic]
	mov	[rsp + 32], rax
	mov	r9, [r15.VIEW_PARAM.unItalic]
	mov	r8, IDS_CFG_VIEWITALIC
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load weight prop --

	lea	rax, [r15.VIEW_PARAM.unWeight]
	mov	[rsp + 32], rax
	mov	r9, [r15.VIEW_PARAM.unWeight]
	mov	r8, IDS_CFG_VIEWWEIGHT
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigNumber]

	; -- load font name --

	lea	rax, [r15.VIEW_PARAM.txFontName]
	mov	[rsp + 32], rax
	lea	r9, [r15.VIEW_PARAM.txFontName]
	mov	r8, IDS_CFG_VIEWFONT
	mov	rdx, ptxSection
	mov	rcx, r14
	mov	rax, [rcx.CLASS_CONFIG.vtableThis]
	call	[rax.CLASS_CONFIG_IFACE.pfnGetConfigText]

	xor	rax, rax

	add	rsp, 48
	add	rsp, 1 * 8 + 8

	pop	r15
	pop	r14
	pop	rbp
	ret	0

	align	4

appGetConfigView	ENDP

	END
