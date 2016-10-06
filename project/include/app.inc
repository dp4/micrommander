;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - main defines
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
;	interface forward declaration
;------------------------------------------------------------------------------------------------------------------------------------------

	; app methods

appInitLogo	proto
prcStartThread	proto
prcWaitThread	proto
prcStopThread	proto
prcWalkFolder	proto

	; static methods

a64toi	proto
dlgprcButton	proto
i64toa	proto
toolDecPoints	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	default styles
;------------------------------------------------------------------------------------------------------------------------------------------

DEF_BGCOLOR	equ	0FFFFFFh	; default backcolor
DEF_FGCOLOR	equ	0000000h	; default forecolor
DEF_CURCOLOR	equ	00B09050h	; default current path color
DEF_OTHCOLOR	equ	00C0C0C0h	; default other path color
DEF_EDITSIZE	equ	12	; default size of font in path edits
DEF_LISTSIZE	equ	12	; default list view font size
DEF_PATH_LENGTH	equ	1024

DEF_BUTTON_COLS	equ	8	; horizontal columns of buttons
DEF_BUTTON_ROWS	equ	5	; vertical rows of buttons
DEF_BUTTONBACK	equ	0C0C0C0h	; default button back color
DEF_BUTTONFORE	equ	0	; default button text color
DEF_BUTTONSIZE	equ	12	; default button font size
DEF_BUTTON_HEIGHT	equ	30	; default size for buttons

DEF_BUTTON_GAP	equ	2	; gap between buttons
DEF_CHILD_GAP	equ	2	; gap between child windows


;------------------------------------------------------------------------------------------------------------------------------------------
;	child windows
;------------------------------------------------------------------------------------------------------------------------------------------

IDC_LEFT	equ	1000	; left file list
IDC_RIGHT	equ	1001	; right file list
IDC_LEFTPATH	equ	1002	; left path edit
IDC_RIGHTPATH	equ	1003	; right path edit
IDC_STATUS	equ	1004	; status line
IDC_PROGRESS_DO	equ	1005	; progress dialog list view - files to be done

ID_BTN_RETRY	equ	32
ID_BTN_IGNORE	equ	33
ID_BTN_IGNORE_ALL	equ	34

;------------------------------------------------------------------------------------------------------------------------------------------
;	main application class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_APP_IFACE	struc
 pfnInit	dq	?	; initialize application
 pfnRun	dq	?	; run main message loop
 pfnRelease	dq	?	; release application
 pfnInitLogo	dq	?	; show logo window during startup
 pfnInitButtons	dq	?	; init button array
 pfnFindButton	dq	?	; find button by position
 pfnMatchShortcut	dq	?	; match shortcut
 pfnLoadString	dq	?	; load string from resource
 pfnGetConfigPath	dq	?	; get configuration file path
 pfnLoadConfig	dq	?	; load configuration from file
 pfnSaveConfig	dq	?	; save configuration to file
 pfnSaveWinConfig	dq	?	; save window parametres to configuration file
 pfnCreateViewFont	dq	?	; create font from view parameters
 pfnSetPath	dq	?	; set new path for active list
 pfnSetStatus	dq	?	; set status bar text
 pfnSetStatusCmd	dq	?	; set status bar text for special command
 pfnToggleMenu	dq	?	; toogle check menu item and its data
 pfnSetMenuState	dq	?	; set menu item state to state
 pfnSetActive	dq	?	; set given list to active
 pfnProcessActive	dq	?	; process all selected entries in active list
 pfnHandleEvent	dq	?	; handle user event
 pfnResize	dq	?	; handle resize event
 pfnFillList	dq	?	; begin fill list
 pfnConfirmClose	dq	?	; confirm quit program
CLASS_APP_IFACE	ends

CLASS_APP	struc
 vtableThis	dq	?	; objects methods
 hinstApp	dq	?	; main instance handle
 hwndApp	dq	?	; main window
 hmenuApp	dq	?	; main window menu
 hiconApp	dq	?	; main app icon
 hevStop	dq	?	; set if processing thread shall end
 hthProcess	dq	?	; user selection processing thread
 unLang	dq	?	; user interface language
 pxLeftList	dq	?	; left list object
 pxRightList	dq	?	; right list object
 hwndStatus	dq	?	; status window
 hwndProgress	dq	?	; progress dialog
 hbrCurPath	dq	?	; color brush for current path
 hbrOthPath	dq	?	; color brush for other path
 unCurCol	dq	?	; color for current path
 unOthCol	dq	?	; color for other path
 pxActive	dq	?	; active list object
 pxInactive	dq	?	; inactive list object
 pxLeftPath	dq	?	; left path edit window
 pxRightPath	dq	?	; right path edit window
 unEditHeight	dq	?	; height of path edit
 unStHeight	dq	?	; height of status window
 pxButtons	dq	?	; array with all buttons
 pxButton	dq	?	; clicked button
 fButton	dq	?	; true if a button is active
 pntButton	POINT	<?>	; last pos clicked
 pxCommand	dq	?	; main command object
 pxConfig	dq	?	; main configuration object
 rcMain	RECT	<?>	; window rect
 unShowMode	dq	?	; window show mode
 unBtnRows	dq	?	; rows of buttons
 unBtnCols	dq	? 	; columns of buttons
 unBtnTop	dq	?	; buttons top position
 unBtnWidth	dq	?	; width of button
 unBtnHeight	dq	?	; height of button
 unBtnArea	dq	?	; height of button area
 fDelConf	dq	?	; if true, confirm deleting files
 txLeft	dw	DEF_PATH_LENGTH dup(?)	; left path string
 txRight	dw	DEF_PATH_LENGTH dup(?)	; right path string
 txSection	dw	64 dup(?)	; app configuration section name
 xInterface	CLASS_APP_IFACE	<?>	; main interface
CLASS_APP	ends


;------------------------------------------------------------------------------------------------------------------------------------------
;	common view parameter
;------------------------------------------------------------------------------------------------------------------------------------------

VIEW_PARAM	struc
 unBgColor	dq	?	; background color
 unFgColor	dq	?	; text color
 unFontSize	dq	?	; size of font
 unItalic	dq	?	; fonts italic mode
 unWeight	dq	?	; fonts weight
 txFontName	dw	64 dup(?)	; name of font
VIEW_PARAM	ends


;------------------------------------------------------------------------------------------------------------------------------------------
;	file/folder list processing
;------------------------------------------------------------------------------------------------------------------------------------------

	; callback parameter

PROCESS_PARAM	struc
 pxApp	dq	?	; main app
 pxList	dq	?	; list to process
 ptxPath	dq	?	; path
 pfnCallback	dq	?	; user callback
 pxUser	dq	?	; user callback parameter
 fRecursive	dq	?	; if true dive into sub directories
PROCESS_PARAM	ends


	; type of list entry

TYPE_FILE	equ	0	; type file
TYPE_DIR	equ	1	; type directory


	; mode of file system processing

PROC_VOID	equ	0	; nothing
PROC_DIRDOWN	equ	1	; going down one directory
PROC_DIRUP	equ	2	; going up one directory
PROC_FILE	equ	3	; doing normal file
