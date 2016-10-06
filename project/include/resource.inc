;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - resources
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

;------------------------------------------------------------------------------------------------------------------------------------------
;	version information, manifest
;------------------------------------------------------------------------------------------------------------------------------------------

IDV_VERSION	equ	1
IDMF_MAIN	equ	1


;------------------------------------------------------------------------------------------------------------------------------------------
;	graphics
;------------------------------------------------------------------------------------------------------------------------------------------

IDI_APP	equ	100	; main icon
IDB_STARTLOGO	equ	200	; start logo
IDB_CMDICONS	equ	201	; command comboboxex icons
IDB_DEFAULT_INI	equ	300	; default INI file


;------------------------------------------------------------------------------------------------------------------------------------------
;	menu
;------------------------------------------------------------------------------------------------------------------------------------------

IDM_APP	equ	10000	; menu ids
IDM_FILE_CONFIG	equ	10010
IDM_FILE_EXIT	equ	10020
IDM_LEFT_SYMBOL	equ	10100
IDM_LEFT_SIZE	equ	10101
IDM_LEFT_DATE	equ	10102
IDM_LEFT_TYPE	equ	10103
IDM_LEFT_FONT	equ	10110
IDM_LEFT_BGCOLOR	equ	10120
IDM_LEFT_FGCOLOR	equ	10130
IDM_RIGHT_SYMBOL	equ	10200
IDM_RIGHT_SIZE	equ 	10201
IDM_RIGHT_DATE	equ	10202
IDM_RIGHT_TYPE	equ	10203
IDM_RIGHT_FONT	equ	10210
IDM_RIGHT_FGCOLOR	equ	10220
IDM_RIGHT_BGCOLOR	equ	10230
IDM_HELP_ABOUT	equ	10300


;------------------------------------------------------------------------------------------------------------------------------------------
;	button popup menu
;------------------------------------------------------------------------------------------------------------------------------------------

IDM_BUTTONPOP	equ	11000	; popup menu ids
IDM_BPOP_COMMAND	equ	11010
IDM_BPOP_FONT	equ	11020
IDM_BPOP_FGCOLOR	equ	11030
IDM_BPOP_BGCOLOR	equ	11040
IDM_BPOP_SHORTCUT	equ	11050


;------------------------------------------------------------------------------------------------------------------------------------------
;	dialogs
;------------------------------------------------------------------------------------------------------------------------------------------

IDD_PROGRESS	equ	4000
ID_CP_PROGRESS	equ	IDD_PROGRESS + 2
ID_CP_STATE	equ	IDD_PROGRESS + 4
ID_CP_TABS	equ	IDD_PROGRESS + 6

IDD_BUTTON_CMD	equ	5100
ID_BC_CMDLIST	equ	IDD_BUTTON_CMD + 10
ID_BC_TEXT	equ	IDD_BUTTON_CMD + 15
ID_BC_PARAM	equ	IDD_BUTTON_CMD + 20
ID_BC_HINT	equ	IDD_BUTTON_CMD + 30

IDD_BYTEINFO	equ	5200
ID_BI_DIRECTORY	equ	IDD_BYTEINFO + 10
ID_BI_FILES	equ	IDD_BYTEINFO + 20
ID_BI_BYTES	equ	IDD_BYTEINFO + 30

IDD_RENAME	equ	5300
ID_RM_FILENAME	equ	IDD_RENAME + 10

IDD_MAKE_DIR	equ	5400
ID_MK_NEWDIR	equ	IDD_MAKE_DIR + 10
ID_MK_HINT	equ	IDD_MAKE_DIR + 20

IDD_CONFIGURE	equ	5500
ID_CF_BUTTONROWS	equ	IDD_CONFIGURE + 2
ID_CF_BUTTONCOLS	equ	IDD_CONFIGURE + 4
ID_CF_DELCONFIRM	equ	IDD_CONFIGURE + 6

IDD_SHORTCUT	equ	5600
ID_SC_KEY	equ	IDD_SHORTCUT + 2


;------------------------------------------------------------------------------------------------------------------------------------------
;	strings
;------------------------------------------------------------------------------------------------------------------------------------------

IDS_SHELLOPEN	equ	20003
IDS_DECMASK	equ	20004
IDS_VERMASK	equ	20005
IDS_DEFPATH	equ	20006
IDS_COLDATE	equ	20007
IDS_COLNAME	equ	20008
IDS_COLSIZE	equ	20009
IDS_COLACTION	equ	20010
IDS_COLSOURCE	equ	20011
IDS_COLTARGET	equ	20012
IDS_COLTYPE	equ	20017
IDS_CONFIGFILE	equ	20018
IDS_EDITCLASS	equ	20019
IDS_LISTCLASS	equ	20020
IDS_DEF_LISTFONT	equ	20021
IDS_DEF_BTNFONT	equ	20023
IDS_DEF_EDITFONT	equ	20024
IDS_LOGOCLASS	equ	20025
IDS_APPWINCLASS	equ	20026
IDS_APPTITLE	equ	20027
IDS_DIRTAG	equ	20028
IDS_DATEFORMAT	equ	20030
IDS_TIMEFORMAT	equ	20031
IDS_ABOUT_TEXT	equ	20032
IDS_ABOUT_TITLE	equ	20033	;
IDS_DELCONF_TEXT	equ	20042
IDS_CONFIRM_TITLE	equ	20043
IDS_CURRENT_RUN	equ	20044
IDS_STATUS_READY	equ	20045
IDS_COPY_COLLECT	equ	20046
IDS_MOVE_COLLECT	equ	20047
IDS_DELETE_COLLECT	equ	20048
IDS_CONFIRM_TEXT	equ	20049
IDS_PROGRESS_DO	equ	20050
IDS_PROGRESS_FAIL	equ	20051
IDS_CFG_LEFTPATH	equ	20056
IDS_CFG_RIGHTPATH	equ	20057
IDS_CFG_SELECTCUR	equ	20058
IDS_CFG_SELECTOTH	equ	20059
IDS_CFG_LEFTLIST	equ	20060
IDS_CFG_RIGHTLIST	equ	20061
IDS_CFG_PARAM	equ	20062
IDS_CFG_BUTTONS	equ	20063
IDS_CFG_LEFTEDIT	equ	20064
IDS_CFG_RIGHTEDIT	equ	20065
IDS_CFG_SHOWMODE	equ	20066
IDS_CFG_BUTTONROWS	equ	20067
IDS_CFG_BUTTONCOLS	equ	20068
IDS_CFG_DELCONFIRM	equ	20071
IDS_CFG_BUTTONTEXT	equ	20072
IDS_CFG_BUTTONPARAM equ	20073
IDS_CFG_BUTTONCMD	equ	20074
IDS_CFG_WINLEFT	equ	20075
IDS_CFG_WINTOP	equ	20076
IDS_CFG_WINRIGHT	equ	20077
IDS_CFG_WINBOTTOM	equ	20078
IDS_CFG_VIEWBACK	equ	20079
IDS_CFG_VIEWFORE	equ	20080
IDS_CFG_VIEWSIZE	equ	20081
IDS_CFG_VIEWITALIC	equ	20082
IDS_CFG_VIEWWEIGHT	equ	20083
IDS_CFG_VIEWFONT	equ	20084
IDS_CFG_BUTTONSCUT	equ	20085
IDS_CFG_LISTNAMECOL	equ	20086
IDS_CFG_LISTTYPECOL	equ	20087
IDS_CFG_LISTDATECOL	equ	20088
IDS_CFG_LISTSIZECOL	equ	20089
IDS_CFG_LISTMODE	equ	20090
IDS_ERROR_BASE	equ	20100	; keep range free!
IDS_CMDCAT_DRIVES	equ	20195
IDS_CMDCAT_EXTERN	equ	20196
IDS_CMDCAT_FILES	equ	20197
IDS_CMDCAT_FOLDERS	equ	20198
IDS_CMDCAT_DEFAULT	equ	20199
IDS_CMD_EMPTY	equ	20200
IDS_CMD_COPY	equ	20201
IDS_CMD_MOVE	equ	20202
IDS_CMD_PARENT	equ	20203
IDS_CMD_CD	equ	20204
IDS_CMD_ALL	equ	20205
IDS_CMD_NONE	equ	20206
IDS_CMD_BYTE	equ	20207
IDS_CMD_MKDIR	equ	20208
IDS_CMD_DELETE	equ	20209
IDS_CMD_EXIT	equ	20210
IDS_CMD_ROOT	equ	20211
IDS_CMD_RENAME	equ	20212
IDS_CMD_EXECUTE	equ	20213
IDS_CMD_FORMAT	equ	20214
IDS_KEY_SHIFT	equ	20400
IDS_KEY_CTRL	equ	20401
IDS_CMDERR_RETRY	equ	20500
IDS_CMDERR_IGNORE	equ	20501
IDS_CMDERR_IGNORE_ALL equ	20502
IDS_CMD_BASE	equ	21000
