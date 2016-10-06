
MAX_PATH	= 260
NULL	equ	0
FALSE	equ	0
TRUE	equ	1


; mode selections for the device mode function

DM_UPDATE	= 1
DM_COPY	= 2
DM_PROMPT	= 4
DM_MODIFY	= 8

DM_IN_BUFFER		= DM_MODIFY
DM_IN_PROMPT		= DM_PROMPT
DM_OUT_BUFFER		= DM_COPY
DM_OUT_DEFAULT	= DM_UPDATE

; device capabilities indices
DC_FIELDS		= 1
DC_PAPERS		= 2
DC_PAPERSIZE		= 3
DC_MINEXTENT		= 4
DC_MAXEXTENT		= 5
DC_BINS		= 6
DC_DUPLEX		= 7
DC_SIZE		= 8
DC_EXTRA		= 9
DC_VERSION		= 10
DC_DRIVER		= 11
DC_BINNAMES		= 12
DC_ENUMRESOLUTIONS	= 13
DC_FILEDEPENDENCIES	= 14
DC_TRUETYPE		= 15
DC_PAPERNAMES		= 16
DC_ORIENTATION		= 17
DC_COPIES		= 18

SIZEL	struc
 scx	dd	?
 scy	dd	?
SIZEL	ends

POINT	struc
 x	dd	?
 y	dd	?
POINT	ends
