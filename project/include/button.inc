;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - button class
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

buttonNew	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	button class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_BUTTON_IFACE	struc
 pfnInit	dq	?	; init button
 pfnLoadConfig	dq	?	; load configuration
 pfnSaveConfig	dq	?	; save configuration
 pfnGetRect	dq	?	; get buttons rect
 pfnRender	dq	?	; render single button rectangle
CLASS_BUTTON_IFACE	ends

CLASS_BUTTON	struc
 vtableThis	dq	?	; objects methods
 pxApp	dq	?	; parent object
 unCmd	dq	?	; command to execute
 txText	dw	32 dup(?)	; text on button
 txParam	dw	DEF_PATH_LENGTH dup(?)	; parameters for command
 xParams	VIEW_PARAM	<?>	; view parameters
 unShortcut	dq	?	; keyboard shortcut
 unCol	dq	?	; horizontal position
 unRow	dq	?	; vertical position
 txSection	dw	64 dup(?)	; button configuration section
 xInterface	CLASS_BUTTON_IFACE	<?>	; button interface
CLASS_BUTTON	ends
