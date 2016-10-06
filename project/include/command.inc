;----------------------T----------------------T-------------------------------------T------------------------------------------------------
; description:	x64 asm source for "commander style" windows file manager - defines for command and action classes
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

commandNew	proto
actionNew	proto


;------------------------------------------------------------------------------------------------------------------------------------------
;	command class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_COMMAND_IFACE	struc
 pfnInit	dq	?	; initialize command
 pfnRelease	dq	?	; release command resources
 pfnExecute	dq	?	; execute command
 pfnChangeRoot	dq	?	; command change path to root
 pfnCopyFiles	dq	?	; prepare copy selected files
 pfnCopyFile	dq	?	; copy single file
 pfnMoveFiles	dq	?	; prepare move selected files
 pfnMoveFile	dq	?	; move single file
 pfnDeleteFiles	dq	?	; prepare delete selected files
 pfnDeleteFile	dq	?	; delete single files
 pfnRenameFiles	dq	?	; rename selected files
 pfnMakeDir	dq	?	; create new folder
 pfnOpenProgress	dq	?	; open progress dialog
 pfnCloseProgress	dq	?	; close progress dialog
 pfnHandleError	dq	?	; handle os error
 pfnCleanTask	dq	?	; clean up task list
CLASS_COMMAND_IFACE	ends

CLASS_COMMAND	struc
 vtableThis	dq	?	; objects methods
 pxApp	dq	?	; parent object
 htCommand	dq	?	; command thread
 hevStart	dq	?	; command processing start event
 hevCancel	dq	?	; command thread cancel event
 hevUserBreak	dq	?	; set if user cancels operation
 parrCommands	dq	?	; linked list with commands to process, points to CLASS_COMMAND
 fIgnore	dq	?	; if true, ignore all errors in this session	
 unGroup	dq	?	; current continuously command number
 xCritical	CRITICAL_SECTION	<?>	; critical section
 xInterface	CLASS_COMMAND_IFACE <?>	; command interface
CLASS_COMMAND	ends


;------------------------------------------------------------------------------------------------------------------------------------------
;	single action class
;------------------------------------------------------------------------------------------------------------------------------------------

CLASS_ACTION_IFACE	struc
 pfnInit	dq	?	; initialize command
 pfnRelease	dq	?	; release command resources
 pfnSetProgress	dq	?	; add item to progress list
 pfnRemProgress	dq	?	; remove item from progress list
CLASS_ACTION_IFACE	ends

CLASS_ACTION	struc
 vtableThis	dq	?	; objects methods
 unCmd	dq	?	; command to add
 idItem	dq	?	; list item
 unGroup	dq	?	; group number
 ptxSource	dq	?	; source file
 ptxDest	dq	?	; destination file, if any
 pxNext	dq	?	; points to next action, if any
 xInterface	CLASS_ACTION_IFACE	<?>	; command interface
CLASS_ACTION	ends


	; progress parameter

CMD_SIZE_REFRESH	equ	1000	; refresh display at all 1000 files


	; callback parameter

CMD_SELECT_PARAM	struc
 pxThis	dq	?	; list object
 fSelect	dq	?	; select entry or not
CMD_SELECT_PARAM	ends

CMD_SIZE_PARAM	struc
 hwndDlg	dq	?	; info dialog
 unFiles	dq	?	; number of files
 unDirs	dq	?	; number of dirs
 unSize	dq	?	; size in bytes
CMD_SIZE_PARAM	ends

CMD_ADD_ACTION	struc
 pxApp	dq	?	; action object
 unFileAction	dq	?	; action during file
 unDownAction	dq	?	; action during enter folder
 unUpAction	dq	?	; action during leave folder
 unSourcePos	dq	?	; length of source path, remove this from target path
 unTargetPos	dq	?	; length of target path, add this to target path
 unGroup	dq	?	; group number
 txTarget	dw	DEF_PATH_LENGTH dup(?)	; target path
CMD_ADD_ACTION	ends


;------------------------------------------------------------------------------------------------------------------------------------------
;	all commands
;------------------------------------------------------------------------------------------------------------------------------------------

CMD_EMPTY	equ	0	; do nothing!
CMD_ALL	equ	5	; select all
CMD_BYTE	equ	7	; get info about selection
CMD_CD	equ	4	; change dir
CMD_COPY	equ	1	; copy file(s)
CMD_DELETE	equ	9	; delete file(s)
CMD_EXIT	equ	11	; exit program
CMD_MKDIR	equ	8	; make directory
CMD_MOVE	equ	2	; move file(s)
CMD_NONE	equ	6	; select none
CMD_PARENT	equ	3	; go to parent dir
CMD_ROOT	equ	10	; go to root
CMD_RENAME	equ	12	; change name of dir/file
CMD_EXECUTE	equ	13	; execute command
CMD_FORMAT	equ	14	; format drive
