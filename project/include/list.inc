;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - list class
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

	; new operators

listNew	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	list class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_LIST_IFACE	struc
 pfnInit	dq	?	; initialize list
 pfnRelease	dq	?	; release list resources
 pfnLoadConfig	dq	?	; load configuration from file
 pfnInitControl	dq	?	; initialize list control
 pfnInitColumn	dq	?	; initialize all columns
 pfnChangeColumn	dq	?	; change columns
 pfnChangeColor	dq	?	; request new color from user and apply
 pfnChangeFont	dq	?	; request new font from user and apply
 pfnResize	dq	?	; resize list control
 pfnHandleNotify	dq	?	; handle list notifications
 pfnProcess	dq	?	; process each entry with given callback
 pfnStartThread	dq	?	; start list fill thread
 pfnStopThread	dq	?	; stop list fill thread
 pfnReleaseControl	dq	?	; release list control
CLASS_LIST_IFACE	ends

CLASS_LIST	struc
 vtableThis	dq	?	; objects methods
 hwndList	dq	?	; myself
 idList	dq	?	; list id
 pxApp	dq	?	; parent application object
 ptxPath	dq	?	; path for this list
 hfontList	dq	?	; list font
 unMode	dq	?	; active columns
 unSort	dq	?	; sort by which column
 fSortDir	dq	?	; direction of sorting
 hthFill	dq	?	; filling thread, if present
 hevStop	dq	?	; end thread signal event
 unCwName	dq	?	; width of name column
 unCwType	dq	?	; width of type column
 unCwDate	dq	?	; width of date column
 unCwSize	dq	?	; width of size column
 xParams	VIEW_PARAM	<?>	; viewing params
 txSection	dw	64 dup(?)	; configuration section name
 xInterface	CLASS_LIST_IFACE	<?>	; list interface
CLASS_LIST	ends


	; callback parameter

LISTFILL_DATA	struc
 pxList	dq	?	; list window
 unCount	dq	?	; number of inserted items
 txDirTag	dw	16 dup(?)	; tag for listview marking "folders"
 txSizeFmt	dw	16 dup(?)	; size format mask for listviews file size
 txFmtDate	dw	16 dup(?)	; date format mask
 txFmtTime	dw	16 dup(?)	; time format mask
LISTFILL_DATA	ends


	; list marker

LIST_ACTUAL	equ	1	; use actual list
LIST_OTHER	equ	2	; use non actual list

CHANGE_BGCOLOR	equ	1	; apply new background color
CHANGE_FGCOLOR	equ	2	; apply new foreground color


	; list view column bits

LIST_SYMBOL	equ	1	; symbol column
LIST_SIZE	equ	4	; size of file column
LIST_TYPE	equ	8	; type of file column
LIST_DATE	equ	16	; date of file column


	; refresh speed

LIST_FILL_REFRESH	equ	250	; refresh list during fill at all REFRESH entries
