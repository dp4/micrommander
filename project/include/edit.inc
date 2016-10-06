;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - path edit class
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

	; new operator

pathNew	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	path edit class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_PATH_IFACE	struc
 pfnInit	dq	?	; initialize path object
 pfnLoadConfig	dq	?	; load configuration
 pfnResize	dq	?	; resize path control
 pfnUpdate	dq	?	; update control after color change
 pfnRelease	dq	?	; release object
CLASS_PATH_IFACE	ends

CLASS_PATH	struc
 vtableThis	dq	?	; objects methods
 pxApp	dq	?	; parent object
 hwndEdit	dq	?	; edit control window
 idPath	dq	?	; path control id
 hfontEdit	dq	?	; edit font
 xParams	VIEW_PARAM	<?>	; view parameters
 xInterface	CLASS_PATH_IFACE	<?>	; path interface
CLASS_PATH	ends

EDIT_BORDER	equ	3	; size of border around text
