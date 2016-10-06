;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - configuration helper class
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

configNew	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	button class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_CONFIG_IFACE	struc
 pfnInit	dq	?	; initialize configuration helper object
 pfnColorDialog	dq	?	; show color dialog
 pfnFontDialog	dq	?	; show font dialog
 pfnGetConfigView	dq	?	; get view parameters from configuration file
 pfnSetConfigView	dq	?	; set view parameters to configuration file
 pfnGetConfigNumber	dq	?	; get number from configuration file
 pfnSetConfigNumber	dq	?	; set number to configuration file
 pfnGetConfigText	dq	?	; get text from configuration file
 pfnSetConfigText	dq	?	; set text to configuration file
CLASS_CONFIG_IFACE	ends

CLASS_CONFIG	struc
 vtableThis	dq	?	; objects methods
 pxApp	dq	?	; main app
 txConfig	dw	DEF_PATH_LENGTH dup(?)	; ini file name
 xInterface	CLASS_CONFIG_IFACE	<?>	; button interface
CLASS_CONFIG	ends
