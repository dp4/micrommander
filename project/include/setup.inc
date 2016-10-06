;---------------------------T-----------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - setup defines
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
;------------------------------------------------------------------------------------------------------------------------------------------

;----------------------------------------------------------------------------------------------------------------------
;	main application class
;----------------------------------------------------------------------------------------------------------------------

CLASS_INSTALL_APP_IFACE	struc
 pfnRun	dq	?	; run main message loop
 pfnConfirmQuit	dq	?	; show confirmation message box
 pfnPathMessage	dq	?	; display path creation confirmation
 pfnGetOptions	dq	?	; get install options
 pfnDoInstall	dq	?	; do installation
 pfnEnableStep	dq	?	; enable progress step label
 pfnCopyAllFiles	dq	?	; copy all target files
 pfnCreateMenu	dq	?	; create start menu
 pfnCreateLink	dq	?	; create link
 pfnPrepareUninstall	dq	?	; prepare uninstall in registry
 pfnStepAndHook	dq	?	; progress done
CLASS_INSTALL_APP_IFACE	ends

CLASS_INSTALL_APP	struc
 vtableThis	dq	?	; objects methods
 hinstApp	dq	?	; main instance handle
 hiconApp	dq	?	; main app icon
 hiconHook	dq	?	; progress ok hook icon
 hcurArrow	dq	?	; arrow cursor
 hfontDialog	dq	?	; large title font
 dqOptions	dq	?	; install options
 txPath	dw	1024 dup(?)	; install path
 xInterface	CLASS_INSTALL_APP_IFACE <?>	; interface
CLASS_INSTALL_APP	ends


; number of progress steps

FILE_COUNT	equ	3


; dialog result action

SETUP_BREAK	equ	1
SETUP_NEXT	equ	2
SETUP_PREV	equ	3


; install options

SETUP_WITH_DESKTOP	equ	1
SETUP_WITH_STARTMENU	equ	2


;----------------------------------------------------------------------------------------------------------------------
;	resources
;----------------------------------------------------------------------------------------------------------------------

IDI_MAIN	equ	1001
IDI_HOOK	equ	1002

IDR_BIN_FILE1	equ	2000
IDR_BIN_FILE2	equ	2001
IDR_BIN_FILE3	equ	2002
IDR_BIN_LICENSE	equ	2901

IDD_WELCOME	equ	4000
IDD_LICENSE	equ	4100
IDD_PROGRESS	equ	4400

IDC_CAPTION	equ	101
IDC_PROGRESSBAR	equ	109
IDC_LIC_FIELD	equ	110
IDC_HOOK1	equ	112
IDC_HOOK2	equ	114
IDC_HOOK3	equ	116
IDC_HOOK4	equ	117
IDC_STEP1	equ	118
IDC_STEP2	equ	120
IDC_STEP3	equ	122
IDC_STEP4	equ	124
IDC_INST_LIST	equ	130
IDC_NEXTPAGE	equ	200
IDC_PREVPAGE	equ	201

IDD_DIRECTORY	equ	4200
ID_DI_FRAME	equ	IDD_DIRECTORY + 10
ID_DI_PATH	equ	IDD_DIRECTORY + 11
ID_DI_BUTTON	equ	IDD_DIRECTORY + 12

IDD_OPTIONS	equ	4300
ID_OP_DESKTOP	equ	IDD_OPTIONS + 10
ID_OP_START	equ	IDD_OPTIONS + 11
ID_OP_CONTEXT	equ	IDD_OPTIONS + 12

IDS_PRODUCTNAME	equ	20000
IDS_CONFIRM_TITLE	equ	20003
IDS_WANT_QUIT	equ	20004
IDS_SUCCESS_TITLE	equ	20005
IDS_SUCCESS_TEXT	equ	20006
IDS_DEFAULT_PATH	equ	20007
IDS_CREATE_DIR	equ	20008
IDS_ERROR_TITLE	equ	20009
IDS_NOT_EMPTY	equ	20010
IDS_CHOOSE_PATH	equ	20011
IDS_PROGRAM_PATH	equ	20012
