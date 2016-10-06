
	IFDEF	UNICODE

CreateFont		equ	CreateFontW
GetObject		equ	GetObjectW
GetTextExtentPoint32	equ	GetTextExtentPoint32W
TextOut		equ	TextOutW

LOGFONT		equ	LOGFONTW

	ELSE

CreateFont		equ	CreateFontA
GetObject		equ	GetObjectA
GetTextExtentPoint32	equ	GetTextExtentPoint32A
TextOut		equ	TextOutA

LOGFONT		equ	LOGFONTA

	ENDIF


CreateCompatibleDC	proto	:QWORD
CreateFontA		proto	:DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :QWORD
CreateFontW		proto	:DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD, :QWORD
CreateRectRgn		proto	:DWORD, :DWORD, :DWORD, :DWORD
CreateSolidBrush		proto	:DWORD
DeleteDC		proto	:QWORD
DeleteObject		proto	:QWORD
GetDC		proto	:QWORD
GetObjectA		proto	:QWORD, :DWORD, :QWORD
GetObjectW		proto	:QWORD, :DWORD, :QWORD
GetStockObject		proto	:DWORD
GetTextExtentPoint32A	proto	:QWORD, :QWORD, :DWORD, :QWORD
GetTextExtentPoint32W	proto	:QWORD, :QWORD, :DWORD, :QWORD
ReleaseDC		proto	:QWORD, :QWORD
SelectClipRgn		proto	:QWORD, :QWORD
SelectObject		proto	:QWORD, :QWORD
SetBkColor		proto	:QWORD, :DWORD
SetBkMode		proto	:QWORD, :DWORD
SetStretchBltMode		proto	:QWORD, :DWORD
SetTextAlign		proto	:QWORD, :DWORD
SetTextColor		proto	:QWORD, :DWORD
StretchBlt		proto	:QWORD, :DWORD, :DWORD, :DWORD, :DWORD, :QWORD, :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
TextOutA		proto	:QWORD, :DWORD, :DWORD, :QWORD, :DWORD
TextOutW		proto	:QWORD, :DWORD, :DWORD, :QWORD, :DWORD

; Bitmap Header Definition 

BITMAP	STRUC
 bmType	dd	?
 bmWidth	dd	?
 bmHeight	dd	?
 bmWidthBytes	dd	?
 bmPlanes	dw	?, ?
 bmBitsPixel	dw	?, ?
 bmBits	dq	?
BITMAP	ENDS

; StretchBlt() Modes 

BLACKONWHITE		= 1
WHITEONBLACK		= 2
COLORONCOLOR		= 3
HALFTONE		= 4
MAXSTRETCHBLTMODE	= 4

; New StretchBlt() Modes 

STRETCH_ANDSCANS	= BLACKONWHITE
STRETCH_ORSCANS	= WHITEONBLACK
STRETCH_DELETESCANS	= COLORONCOLOR
STRETCH_HALFTONE	= HALFTONE

; Ternary raster operations 

SRCCOPY 		= 00CC0020h	 ; dest = source 
SRCPAINT		= 00EE0086h	 ; dest = source OR dest 
SRCAND		= 008800C6h	 ; dest = source AND dest
SRCINVERT 		= 00660046h	 ; dest = source XOR dest
SRCERASE		= 00440328h	 ; dest = source AND (NOT dest ) 
NOTSRCCOPY		= 00330008h	 ; dest = (NOT source) 
NOTSRCERASE 		= 001100A6h	 ; dest = (NOT src) AND (NOT dest) 
MERGECOPY 		= 00C000CAh	 ; dest = (source AND pattern) 
MERGEPAINT		= 00BB0226h	 ; dest = (NOT source) OR dest 
PATCOPY 		= 00F00021h	 ; dest = pattern
PATPAINT		= 00FB0A09h	 ; dest = DPSnoo 
PATINVERT 		= 005A0049h	 ; dest = pattern XOR dest 
DSTINVERT 		= 00550009h	 ; dest = (NOT dest) 
BLACKNESS 		= 00000042h	 ; dest = BLACK
WHITENESS 		= 00FF0062h	 ; dest = WHITE


OUT_DEFAULT_PRECIS	= 0
OUT_STRING_PRECIS	= 1
OUT_CHARACTER_PRECIS	= 2
OUT_STROKE_PRECIS	= 3
OUT_TT_PRECIS		= 4
OUT_DEVICE_PRECIS	= 5
OUT_RASTER_PRECIS	= 6
OUT_TT_ONLY_PRECIS	= 7
OUT_OUTLINE_PRECIS	= 8
OUT_SCREEN_OUTLINE_PRECIS	= 9

CLIP_DEFAULT_PRECIS	= 0
CLIP_CHARACTER_PRECIS	= 1
CLIP_STROKE_PRECIS	= 2
CLIP_MASK 		= 15
CLIP_LH_ANGLES 		= 16
CLIP_TT_ALWAYS 		= 32
CLIP_EMBEDDED		= 128

DEFAULT_QUALITY	= 0
DRAFT_QUALITY		= 1
PROOF_QUALITY		= 2
NONANTIALIASED_QUALITY	= 3
ANTIALIASED_QUALITY	= 4

DEFAULT_PITCH	= 0
FIXED_PITCH	= 1
VARIABLE_PITCH	= 2
MONO_FONT	= 8

ANSI_CHARSET		= 0
DEFAULT_CHARSET	= 1
SYMBOL_CHARSET		= 2
SHIFTJIS_CHARSET	= 128
HANGEUL_CHARSET	= 129
GB2312_CHARSET		= 134
CHINESEBIG5_CHARSET	= 136
OEM_CHARSET		= 255
JOHAB_CHARSET		= 130
HEBREW_CHARSET		= 177
ARABIC_CHARSET		= 178
GREEK_CHARSET		= 161
TURKISH_CHARSET	= 162
VIETNAMESE_CHARSET	= 163
THAI_CHARSET		= 222
EASTEUROPE_CHARSET	= 238
RUSSIAN_CHARSET	= 204
MAC_CHARSET		= 77
BALTIC_CHARSET		= 186

FS_LATIN1 	= 00000001h
FS_LATIN2 	= 00000002h
FS_CYRILLIC 	= 00000004h
FS_GREEK	= 00000008h
FS_TURKISH	= 00000010h
FS_HEBREW 	= 00000020h
FS_ARABIC 	= 00000040h
FS_BALTIC 	= 00000080h
FS_VIETNAMESE 	= 00000100h
FS_THAI 	= 00010000h
FS_JISJAPAN 	= 00020000h
FS_CHINESESIMP	= 00040000h
FS_WANSUNG	= 00080000h
FS_CHINESETRAD	= 00100000h
FS_JOHAB	= 00200000h
FS_SYMBOL 	= 80000000h

; Font Families 

FF_DONTCARE	= 00h	; Don't care or don't know. 
FF_ROMAN 	= 10h	; Variable stroke width, serifed.  Times Roman, Century Schoolbook, etc. 
FF_SWISS 	= 20h	; Variable stroke width, sans-serifed.  Helvetica, Swiss, etc. 
FF_MODERN	= 30h	; Constant stroke width, serifed or sans-serifed.  Pica, Elite, Courier, etc. 
FF_SCRIPT	= 40h	; Cursive, etc. 
FF_DECORATIVE	= 50h	; Old English, etc. 

; Font Weights 

FW_DONTCARE	= 0
FW_THIN	= 100
FW_EXTRALIGHT	= 200
FW_LIGHT	= 300
FW_NORMAL	= 400
FW_MEDIUM	= 500
FW_SEMIBOLD	= 600
FW_BOLD	= 700
FW_EXTRABOLD	= 800
FW_HEAVY	= 900

FW_ULTRALIGHT	= FW_EXTRALIGHT
FW_REGULAR	= FW_NORMAL
FW_DEMIBOLD	= FW_SEMIBOLD
FW_ULTRABOLD	= FW_EXTRABOLD
FW_BLACK	= FW_HEAVY

PANOSE_COUNT		= 10
PAN_FAMILYTYPE_INDEX	= 0
PAN_SERIFSTYLE_INDEX	= 1
PAN_WEIGHT_INDEX	= 2
PAN_PROPORTION_INDEX	= 3
PAN_CONTRAST_INDEX	= 4
PAN_STROKEVARIATION_INDEX	= 5
PAN_ARMSTYLE_INDEX	= 6
PAN_LETTERFORM_INDEX	= 7
PAN_MIDLINE_INDEX	= 8
PAN_XHEIGHT_INDEX	= 9

PAN_CULTURE_LATIN	= 0

ELF_VERSION		= 0
ELF_CULTURE_LATIN	= 0

; EnumFonts Masks 
RASTER_FONTTYPE 	= 001
DEVICE_FONTTYPE 	= 002
TRUETYPE_FONTTYPE 	= 004

; palette entry flags 

PC_RESERVED 	= 01	; palette index used for animation 
PC_EXPLICIT 	= 02	; palette index is explicit to device 
PC_NOCOLLAPSE 	= 04	; do not match color to system palette 

; Background Modes 
TRANSPARENT	= 1
OPAQUE	= 2
BKMODE_LAST	= 2

; Graphics Modes 

GM_COMPATIBLE	= 1
GM_ADVANCED	= 2
GM_LAST	= 2

; PolyDraw and GetPath point types 
PT_CLOSEFIGURE	= 01
PT_LINETO 	= 02
PT_BEZIERTO 	= 04
PT_MOVETO 	= 06

; Mapping Modes 
MM_TEXT	= 1
MM_LOMETRIC	= 2
MM_HIMETRIC	= 3
MM_LOENGLISH	= 4
MM_HIENGLISH	= 5
MM_TWIPS	= 6
MM_ISOTROPIC	= 7
MM_ANISOTROPIC	= 8

; Min and Max Mapping Mode values 
MM_MIN		= MM_TEXT
MM_MAX		= MM_ANISOTROPIC
MM_MAX_FIXEDSCALE	= MM_TWIPS

; Coordinate Modes 
ABSOLUTE	= 1
RELATIVE	= 2

; Stock Logical Objects 
WHITE_BRUSH		= 0
LTGRAY_BRUSH		= 1
GRAY_BRUSH		= 2
DKGRAY_BRUSH		= 3
BLACK_BRUSH		= 4
NULL_BRUSH		= 5
HOLLOW_BRUSH		= NULL_BRUSH
WHITE_PEN		= 6
BLACK_PEN		= 7
NULL_PEN		= 8
OEM_FIXED_FONT		= 10
ANSI_FIXED_FONT	= 11
ANSI_VAR_FONT		= 12
SYSTEM_FONT		= 13
DEVICE_DEFAULT_FONT	= 14
DEFAULT_PALETTE		= 15
SYSTEM_FIXED_FONT	= 16
DEFAULT_GUI_FONT	= 17

STOCK_LAST		= 17

CLR_INVALID 		= -1

; Brush Styles 
BS_SOLID		= 0
BS_NULL		= 1
BS_HOLLOW		= BS_NULL
BS_HATCHED		= 2
BS_PATTERN		= 3
BS_INDEXED		= 4
BS_DIBPATTERN		= 5
BS_DIBPATTERNPT		= 6
BS_PATTERN8X8		= 7
BS_DIBPATTERN8X8	= 8
BS_MONOPATTERN	= 9

; Hatch Styles 
HS_HORIZONTAL	= 0 ; ----- 
HS_VERTICAL	= 1 ; ||||| 
HS_FDIAGONAL	= 2 ; \\\\\ 
HS_BDIAGONAL	= 3 ; ;;/ 
HS_CROSS	= 4 ; +++++ 
HS_DIAGCROSS	= 5 ; xxxxx 

; Pen Styles 
PS_SOLID	= 0
PS_DASH	= 1 ; -------
PS_DOT	= 2 ; .......
PS_DASHDOT	= 3 ; _._._._
PS_DASHDOTDOT	= 4 ; _.._.._
PS_NULL	= 5
PS_INSIDEFRAME	= 6
PS_USERSTYLE	= 7
PS_ALTERNATE	= 8
PS_STYLE_MASK 	= 0000000Fh

PS_ENDCAP_ROUND 	= 00000000h
PS_ENDCAP_SQUARE	= 00000100h
PS_ENDCAP_FLAT		= 00000200h
PS_ENDCAP_MASK		= 00000F00h
PS_JOIN_ROUND 		= 00000000h
PS_JOIN_BEVEL 		= 00001000h
PS_JOIN_MITER 		= 00002000h
PS_JOIN_MASK		= 0000F000h
PS_COSMETIC 		= 00000000h
PS_GEOMETRIC		= 00010000h
PS_TYPE_MASK		= 000F0000h

AD_COUNTERCLOCKWISE	= 1
AD_CLOCKWISE		= 2

; Device Parameters for GetDeviceCaps()
DRIVERVERSION		= 0
TECHNOLOGY		= 2
HORZSIZE		= 4
VERTSIZE		= 6
HORZRES		= 8
VERTRES		= 10
BITSPIXEL		= 12
PLANES			= 14
NUMBRUSHES		= 16
NUMPENS		= 18
NUMMARKERS		= 20
NUMFONTS		= 22
NUMCOLORS		= 24
PDEVICESIZE		= 26
CURVECAPS		= 28
LINECAPS		= 30
POLYGONALCAPS		= 32
TEXTCAPS		= 34
CLIPCAPS		= 36
RASTERCAPS		= 38
ASPECTX		= 40
ASPECTY		= 42
ASPECTXY		= 44

LOGPIXELSX		= 88
LOGPIXELSY		= 90

SIZEPALETTE		= 104
NUMRESERVED		= 106
COLORRES		= 108

; Printing related DeviceCaps. These replace the appropriate Escapes

PHYSICALWIDTH		= 110
PHYSICALHEIGHT		= 111
PHYSICALOFFSETX	= 112
PHYSICALOFFSETY	= 113
SCALINGFACTORX		= 114
SCALINGFACTORY		= 115

; Display driver specific

VREFRESH		= 116
DESKTOPVERTRES		= 117
DESKTOPHORZRES		= 118
BLTALIGNMENT		= 119

; Device Technologies
DT_PLOTTER		= 0
DT_RASDISPLAY		= 1
DT_RASPRINTER		= 2
DT_RASCAMERA		= 3
DT_CHARSTREAM		= 4
DT_METAFILE		= 5
DT_DISPFILE		= 6

; Curve Capabilities
CC_NONE		= 0
CC_CIRCLES		= 1
CC_PIE			= 2
CC_CHORD		= 4
CC_ELLIPSES		= 8
CC_WIDE		= 16
CC_STYLED		= 32
CC_WIDESTYLED		= 64
CC_INTERIORS		= 128
CC_ROUNDRECT		= 256

; Line Capabilities
LC_NONE		= 0
LC_POLYLINE		= 2
LC_MARKER		= 4
LC_POLYMARKER		= 8
LC_WIDE		= 16
LC_STYLED		= 32
LC_WIDESTYLED		= 64
LC_INTERIORS		= 128

; Polygonal Capabilities
PC_NONE		= 0 
PC_POLYGON		= 1
PC_RECTANGLE		= 2
PC_WINDPOLYGON	= 4
PC_TRAPEZOID		= 4
PC_SCANLINE		= 8
PC_WIDE		= 16
PC_STYLED		= 32
PC_WIDESTYLED		= 64
PC_INTERIORS		= 128
PC_POLYPOLYGON	= 256
PC_PATHS		= 512

; Clipping Capabilities
CP_NONE		= 0
CP_RECTANGLE		= 1
CP_REGION		= 2

; Text Capabilities
TC_OP_CHARACTER	= 00000001h
TC_OP_STROKE		= 00000002h
TC_CP_STROKE		= 00000004h
TC_CR_90		= 00000008h
TC_CR_ANY		= 00000010h
TC_SF_X_YINDEP	= 00000020h
TC_SA_DOUBLE		= 00000040h
TC_SA_INTEGER		= 00000080h
TC_SA_CONTIN		= 00000100h
TC_EA_DOUBLE		= 00000200h
TC_IA_ABLE		= 00000400h
TC_UA_ABLE		= 00000800h
TC_SO_ABLE		= 00001000h
TC_RA_ABLE		= 00002000h
TC_VA_ABLE		= 00004000h
TC_RESERVED		= 00008000h
TC_SCROLLBLT		= 00010000h

; Raster Capabilities
RC_NONE		= 0
RC_BITBLT		= 1
RC_BANDING		= 2
RC_SCALING		= 4
RC_BITMAP64		= 8
RC_GDI20_OUTPUT	= 0010h
RC_GDI20_STATE	= 0020h
RC_SAVEBITMAP		= 0040h
RC_DI_BITMAP		= 0080h
RC_PALETTE		= 0100h
RC_DIBTODEV		= 0200h
RC_BIGFONT		= 0400h
RC_STRETCHBLT		= 0800h
RC_FLOODFILL		= 1000h
RC_STRETCHDIB		= 2000h
RC_OP_DX_OUTPUT	= 4000h
RC_DEVBITS		= 8000h

; DIB color table identifiers 

DIB_RGB_COLORS	= 0 ; color table in RGBs 
DIB_PAL_COLORS	= 1 ; color table in palette indices 

; constants for Get/SetSystemPaletteUse() 

SYSPAL_ERROR		= 0
SYSPAL_STATIC 		= 1
SYSPAL_NOSTATIC	= 2

; constants for CreateDIBitmap 
CBM_INIT		= 04 ; initialize bitmap 

; ExtFloodFill style flags 
FLOODFILLBORDER	= 0
FLOODFILLSURFACE	= 1

; size of a device name string 
CCHDEVICENAME		= 32

; size of a form name string 
CCHFORMNAME		= 32


; Binary raster ops 

R2_BLACK	= 1	; 0 
R2_NOTMERGEPEN	= 2	; DPon 
R2_MASKNOTPEN	= 3	; DPna 
R2_NOTCOPYPEN	= 4	; PN 
R2_MASKPENNOT	= 5	; PDna 
R2_NOT	= 6	; Dn 
R2_XORPEN	= 7	; DPx
R2_NOTMASKPEN	= 8	; DPan 
R2_MASKPEN	= 9	; DPa
R2_NOTXORPEN	= 10	; DPxn 
R2_NOP	= 11	; D
R2_MERGENOTPEN	= 12	; DPno 
R2_COPYPEN	= 13	; P
R2_MERGEPENNOT	= 14	; PDno 
R2_MERGEPEN	= 15	; DPo
R2_WHITE	= 16	; 1 
R2_LAST	= 16


GDI_ERROR		= -1
HGDI_ERROR		= -1

; Region Flags 
;;ERROR	= 0
NULLREGION	= 1
SIMPLEREGION	= 2
COMPLEXREGION	= 3
;;RGN_ERROR	= ERROR

; CombineRgn() Styles 
RGN_AND	= 1
RGN_OR	= 2
RGN_XOR	= 3
RGN_DIFF	= 4
RGN_COPY	= 5
RGN_MIN	= RGN_AND
RGN_MAX	= RGN_COPY


; PolyFill() Modes 
ALTERNATE	= 1
WINDING	= 2
POLYFILL_LAST	= 2

; Text Alignment Options 
TA_NOUPDATECP	= 0
TA_UPDATECP	= 1

TA_LEFT	= 0
TA_RIGHT	= 2
TA_CENTER	= 6

TA_TOP	= 0
TA_BOTTOM	= 8
TA_BASELINE	= 24
TA_RTLREADING	= 256
TA_MASK	= TA_BASELINE + TA_CENTER + TA_UPDATECP + TA_RTLREADING
TA_MASK	= TA_BASELINE + TA_CENTER + TA_UPDATECP

VTA_BASELINE	= TA_BASELINE
VTA_LEFT	= TA_BOTTOM
VTA_RIGHT	= TA_TOP
VTA_CENTER	= TA_CENTER
VTA_BOTTOM	= TA_RIGHT
VTA_TOP	= TA_LEFT

ETO_OPAQUE 		= 0002h
ETO_CLIPPED		= 0004h
ETO_GLYPH_INDEX	= 0010h
ETO_RTLREADING 		= 0080h
ETO_IGNORELANGUAGE 	= 1000h

ASPECT_FILTERING 	= 0001

; Bounds Accumulation APIs 

DCB_RESET 	= 0001
DCB_ACCUMULATE	= 0002
DCB_DIRTY	= DCB_ACCUMULATE
DCB_SET	= DCB_RESET + DCB_ACCUMULATE
DCB_ENABLE	= 0004
DCB_DISABLE 	= 0008

; Metafile Functions 
META_SETBKCOLOR	= 0201h
META_SETBKMODE 	= 0102h
META_SETMAPMODE	= 0103h
META_SETROP2 		= 0104h
META_SETRELABS 		= 0105h
META_SETPOLYFILLMODE 	= 0106h
META_SETSTRETCHBLTMODE 	= 0107h
META_SETTEXTCHAREXTRA	= 0108h
META_SETTEXTCOLOR	= 0209h
META_SETTEXTJUSTIFICATION	= 020Ah
META_SETWINDOWORG	= 020Bh
META_SETWINDOWEXT	= 020Ch
META_SETVIEWPORTORG	= 020Dh
META_SETVIEWPORTEXT	= 020Eh
META_OFFSETWINDOWORG 	= 020Fh
META_SCALEWINDOWEXT	= 0410h
META_OFFSETVIEWPORTORG 	= 0211h
META_SCALEVIEWPORTEXT	= 0412h
META_LINETO		= 0213h
META_MOVETO		= 0214h
META_EXCLUDECLIPRECT 	= 0415h
META_INTERSECTCLIPRECT 	= 0416h
META_ARC 		= 0817h
META_ELLIPSE 		= 0418h
META_FLOODFILL 		= 0419h
META_PIE 		= 081Ah
META_RECTANGLE 		= 041Bh
META_ROUNDRECT 	= 061Ch
META_PATBLT		= 061Dh
META_SAVEDC		= 001Eh
META_SETPIXEL		= 041Fh
META_OFFSETCLIPRGN 	= 0220h
META_TEXTOUT 		= 0521h
META_BITBLT		= 0922h
META_STRETCHBLT	= 0B23h
META_POLYGON 		= 0324h
META_POLYLINE		= 0325h
META_ESCAPE		= 0626h
META_RESTOREDC 	= 0127h
META_FILLREGION	= 0228h
META_FRAMEREGION 	= 0429h
META_INVERTREGION	= 012Ah
META_PAINTREGION 	= 012Bh
META_SELECTCLIPREGION	= 012Ch
META_SELECTOBJECT	= 012Dh
META_SETTEXTALIGN	= 012Eh
META_CHORD 		= 0830h
META_SETMAPPERFLAGS	= 0231h
META_EXTTEXTOUT	= 0a32h
META_SETDIBTODEV 	= 0d33h
META_SELECTPALETTE 	= 0234h
META_REALIZEPALETTE	= 0035h
META_ANIMATEPALETTE	= 0436h
META_SETPALENTRIES 	= 0037h
META_POLYPOLYGON 	= 0538h
META_RESIZEPALETTE 	= 0139h
META_DIBBITBLT 		= 0940h
META_DIBSTRETCHBLT 	= 0b41h
META_DIBCREATEPATTERNBRUSH 	= 0142h
META_STRETCHDIB	= 0f43h
META_EXTFLOODFILL	= 0548h
META_DELETEOBJECT	= 01f0h
META_CREATEPALETTE 	= 00f7h
META_CREATEPATTERNBRUSH	= 01F9h
META_CREATEPENINDIRECT 	= 02FAh
META_CREATEFONTINDIRECT	= 02FBh
META_CREATEBRUSHINDIRECT 	= 02FCh
META_CREATEREGION	= 06FFh

; GDI Escapes 
NEWFRAME		= 1
ABORTDOC		= 2
NEXTBAND		= 3
SETCOLORTABLE		= 4
GETCOLORTABLE		= 5
FLUSHOUTPUT		= 6
DRAFTMODE		= 7
QUERYESCSUPPORT	= 8
SETABORTPROC		= 9
;;STARTDOC		= 10
;;ENDDOC		= 11
GETPHYSPAGESIZE	= 12
GETPRINTINGOFFSET	= 13
GETSCALINGFACTOR	= 14
;;MFCOMMENT		= 15
GETPENWIDTH		= 16
SETCOPYCOUNT		= 17
SELECTPAPERSOURCE	= 18
DEVICEDATA		= 19
PASSTHROUGH		= 19
GETTECHNOLGY		= 20
GETTECHNOLOGY		= 20
SETLINECAP		= 21
SETLINEJOIN		= 22
SETMITERLIMIT		= 23
BANDINFO		= 24
DRAWPATTERNRECT	= 25
GETVECTORPENSIZE	= 26
GETVECTORBRUSHSIZE	= 27
ENABLEDUPLEX		= 28
GETSETPAPERBINS		= 29
GETSETPRINTORIENT	= 30
ENUMPAPERBINS		= 31
SETDIBSCALING		= 32
EPSPRINTING		= 33
ENUMPAPERMETRICS	= 34
GETSETPAPERMETRICS	= 35
POSTSCRIPT_DATA	= 37
POSTSCRIPT_IGNORE	= 38
MOUSETRAILS		= 39
GETDEVICEUNITS		= 42

GETEXTENDEDTEXTMETRICS	= 256
GETEXTENTTABLE		= 257
GETPAIRKERNTABLE	= 258
GETTRACKKERNTABLE	= 259
EXTTEXTOUT		= 512
GETFACENAME		= 513
DOWNLOADFACE		= 514
ENABLERELATIVEWIDTHS	= 768
ENABLEPAIRKERNING	=769
SETKERNTRACK		= 770
SETALLJUSTVALUES	= 771
SETCHARSET		= 772

;;STRETCHBLT		= 2048
GETSETSCREENPARAMS	= 3072
QUERYDIBSUPPORT	= 3073
BEGIN_PATH		= 4096
CLIP_TO_PATH		= 4097
END_PATH		= 4098
EXT_DEVICE_CAPS		= 4099
RESTORE_CTM		= 4100
SAVE_CTM		= 4101
SET_ARC_DIRECTION	= 4102
SET_BACKGROUND_COLOR	= 4103
SET_POLY_MODE		= 4104
SET_SCREEN_ANGLE	= 4105
SET_SPREAD		= 4106
TRANSFORM_CTM		= 4107
SET_CLIP_BOX		= 4108
SET_BOUNDS		= 4109
SET_MIRROR_MODE	= 4110
OPENCHANNEL		= 4110
DOWNLOADHEADER	= 4111
CLOSECHANNEL		= 4112
POSTSCRIPT_PASSTHROUGH	= 4115
ENCAPSULATED_POSTSCRIPT	= 4116

; Flag returned from QUERYDIBSUPPORT 
QDI_SETDIBITS		= 1
QDI_GETDIBITS		= 2
QDI_DIBTOSCREEN	= 4
QDI_STRETCHDIB		= 8

; Spooler Error Codes 
SP_NOTREPORTED 		= 4000
SP_ERROR		= -1
SP_APPABORT		= -2
SP_USERABORT		= -3
SP_OUTOFDISK		= -4
SP_OUTOFMEMORY	= -5

PR_JOBSTATUS 		= 0000

; Object Definitions for EnumObjects() 
OBJ_PEN	= 1
OBJ_BRUSH	= 2
OBJ_DC	= 3
OBJ_METADC	= 4
OBJ_PAL	= 5
OBJ_FONT	= 6
OBJ_BITMAP	= 7
OBJ_REGION	= 8
OBJ_METAFILE	= 9
OBJ_MEMDC	= 10
OBJ_EXTPEN	= 11
OBJ_ENHMETADC	= 12
OBJ_ENHMETAFILE	= 13

; xform stuff 
MWT_IDENTITY		= 1
MWT_LEFTMULTIPLY	= 2
MWT_RIGHTMULTIPLY	= 3

MWT_MIN	= MWT_IDENTITY
MWT_MAX	= MWT_RIGHTMULTIPLY

; Logical Font 

LF_FACESIZE	= 32

LF_FULLFACESIZE	= 64

LOGFONTA	struc
 lfHeight	dd	?
 lfWidth	dd	?
 lfEscapement	dd	?
 lfOrientation	dd	?
 lfWeight	dd	?
 lfItalic	db	?
 lfUnderline	db	?
 lfStrikeOut	db	?
 lfCharSet	db	?
 lfOutPrecision	db	?
 lfClipPrecision	db	?
 lfQuality	db	?
 lfPitchAndFamily	db	?
 lfFaceName	db	LF_FACESIZE dup (?)
LOGFONTA	ends

LOGFONTW	struc
 lfHeight	dd	?
 lfWidth	dd	?
 lfEscapement	dd	?
 lfOrientation	dd	?
 lfWeight	dd	?
 lfItalic	db	?
 lfUnderline	db	?
 lfStrikeOut	db	?
 lfCharSet	db	?
 lfOutPrecision	db	?
 lfClipPrecision	db	?
 lfQuality	db	?
 lfPitchAndFamily	db	?
 lfFaceName	dw	LF_FACESIZE dup (?)
LOGFONTW	ends


comment #
;PALETTERGB(r,g,b) (	= 02000000 | RGB(r,g,b))
;PALETTEINDEX(i) ((COLORREF)(	= 01000000 | 	(i)))

;XFORM	STRUC
;FLOAT eM11;
;FLOAT eM12;
;FLOAT eM21;
;FLOAT eM22;
;FLOAT eDx;
;FLOAT eDy;
;XFORM	ENDS



RGBTRIPLE	STRUC
 rgbtBlue	db	?
 rgbtGreen	db	?
 rgbtRed	db	?
RGBTRIPLE	ENDS

; Image Color Matching color definitions 

LCS_CALIBRATED_RGB	= 00000000
LCS_DEVICE_RGB		= 00000001
LCS_DEVICE_CMYK 	= 00000002

LCS_GM_BUSINESS 	= 00000001
LCS_GM_GRAPHICS 	= 00000002
LCS_GM_IMAGES 		= 00000004

; ICM Defines for results from CheckColorInGamut() 
CM_OUT_OF_GAMUT	= 255
CM_IN_GAMUT		= 0

; ICM Color Definitions 
; The following two structures are used for defining RGB's in terms of
; CIEXYZ. The values are fixed point 16.16.

CIEXYZ	STRUC
 ciexyzX	dd	?
 ciexyzY	dd	?
 ciexyzZ	dd	?
CIEXYZ	ENDS

CIEXYZTRIPLE	STRUC
 ciexyzRed	CIEXYZ	<?>
 ciexyzGreen	CIEXYZ	<?>
 ciexyzBlue	CIEXYZ	<?>
CIEXYZTRIPLE	ENDS


; The next structures the logical color space. Unlike pens and brushes,
; but like palettes, there is only one way to create a LogColorSpace.
; A pointer to it must be passed, its elements can't be pushed as
; arguments.

LOGCOLORSPACEA		STRUC
 lcsSignature		dd	?
 lcsVersion		dd	?
 lcsSize		dd	?
 lcsCSType		dd	?
 lcsIntent		dd	?
 lcsEndpoints		CIEXYZTRIPLE	<?>
 lcsGammaRed		dd	?
 lcsGammaGreen		dd	?
 lcsGammaBlue		dd	?
 lcsFilename		db	MAX_PATH dup(?)
LOGCOLORSPACEA		ENDS

LPLOGCOLORSPACE		equ	LPLOGCOLORSPACEA

; structures for defining DIBs 
BITMAPCOREHEADER	STRUC
 bcSize		dd	? ; used to get to color table 
 bcWidth		dw	?
 bcHeight		dw	?
 bcPlanes		dw	?
 bcBitCount		dw	?
BITMAPCOREHEADER	ENDS


BITMAPINFOHEADER	STRUC
 biSize		dd	?
 biWidth		dd	?
 biHeight		dd	?
 biPlanes		dw	?
 biBitCount		dw	?
 biCompression		dd	?
 biSizeImage		dd	?
 biXPelsPerMeter		dd	?
 biYPelsPerMeter		dd	?
 biClrUsed		dd	?
 biClrImportant		dd	?
BITMAPINFOHEADER	ENDS

DIBSECTION	struc
 dsBm	BITMAP	<?>
 dsBmih	BITMAPINFOHEADER	 <?>
 dsBitfields	dd	?, ?, ?
 dshSection	dd	?
 dsOffset	dd	?
DIBSECTION	ends


BITMAPV4HEADER		STRUC
 bV4Size		dd	?
 bV4Width		dd	?
 bV4Height		dd	?
 bV4Planes		dw	?
 bV4BitCount		dw	?
 bV4V4Compression		dd	?
 bV4SizeImage		dd	?
 bV4XPelsPerMeter		dd	?
 bV4YPelsPerMeter		dd	?
 bV4ClrUsed		dd	?
 bV4ClrImportant		dd	?
 bV4RedMask		dd	?
 bV4GreenMask		dd	?
 bV4BlueMask		dd	?
 bV4AlphaMask		dd	?
 bV4CSType		dd	?
 bV4Endpoints		CIEXYZTRIPLE	<?>
 bV4GammaRed		dd	?
 bV4GammaGreen		dd	?
 bV4GammaBlue		dd	?
BITMAPV4HEADER		ENDS

; constants for the biCompression field 
BI_RGB	= 0
BI_RLE8	= 1
BI_RLE4	= 2
BI_BITFIELDS	= 3

RGBQUAD	STRUC
 rgbBlue	db	?
 rgbGreen	db	?
 rgbRed	db	?
 rgbReserved	db	?
RGBQUAD	ENDS

BITMAPINFO	struc
 bmiHeader	BITMAPINFOHEADER	<?>
 bmiColors	RGBQUAD	<?>
BITMAPINFO	ends

BITMAPCOREINFO	STRUC
 bmciHeader	BITMAPCOREHEADER	<?>
 bmciColors	RGBTRIPLE	<?>
BITMAPCOREINFO	ENDS

BITMAPFILEHEADER	STRUC
 bfType	dw	?
 bfSize	dd	?
 bfReserved1	dw	?
 bfReserved2	dw	?
 bfOffBits	dd	?
BITMAPFILEHEADER	ENDS

FONTSIGNATURE	STRUC
  fsUsb	dd	4 dup(?)
  fsCsb	dd	2 dup(?)
FONTSIGNATURE	ENDS

CHARSETINFO	STRUC
 ciCharset	dd	?
 ciACP	dd	?
 cifs	FONTSIGNATURE	<?>
CHARSETINFO	ENDS

TCI_SRCCHARSET	= 1
TCI_SRCCODEPAGE	= 2
TCI_SRCFONTSIG	= 3

LOCALESIGNATURE	STRUC
  lsUsb		dd	4 dup(?)
  lsCsbDefault		dd	2 dup(?)
  lsCsbSupported		dd	2 dup(?)
LOCALESIGNATURE	ENDS

; Clipboard Metafile Picture Structure 
HANDLETABLE	STRUC
 objectHandle	HGDIOBJ	?
HANDLETABLE	ENDS

METARECORD	STRUC
 rdSize	dd	?
 rdFunction	dw	?
 rdParm	dw	?
METARECORD	ENDS

METAFILEPICT	STRUC
 mfp_mm	dd	?
 mfp_xExt	dd	?
 mfp_yExt	dd	?
 mfp_hMF	HMETAFILE	?
METAFILEPICT	ENDS

METAHEADER	STRUC
 mtType	dw	?
 mtHeaderSize	dw	?
 mtVersion	dw	?
 mtSize	dd	?
 mtNoObjects	dw	?
 mtMaxRecord	dd	?
 mtNoParameters	dw	?
METAHEADER	ENDS

; Enhanced Metafile structures 
ENHMETARECORD	STRUC
 emr_iType	dd	?	; Record type EMR_XXX
 emr_nSize	dd	?	; Record size in bytes
 emr_dParm	dd	?	; Parameters
ENHMETARECORD	ENDS

ENHMETAHEADER		STRUC
 emh_iType		dd	?	; Record type EMR_HEADER
 emh_nSize		dd	?	; Record size in bytes.This may be greater than the sizeof(ENHMETAHEADER).
 emh_rclBounds		RECT	<?>	; Inclusive-inclusive bounds in device units
 emh_rclFrame		RECT	<?>	; Inclusive-inclusive Picture Frame of metafile in .01 mm units
 emh_dSignature		dd	?	; Signature.Must be ENHMETA_SIGNATURE.
 emh_nVersion		dd	?	; Version number
 emh_nBytes		dd	?	; Size of the metafile in bytes
 emh_nRecords		dd	?	; Number of records in the metafile
 emh_nHandles		dw	?	; Number of handles in the handle table Handle index zero is reserved.
 emh_sReserved		dw	?	; Reserved.Must be zero.
 emh_nDescription		dd	?	; Number of chars in the unicode description string This is 0 if there is no description string
 emh_offDescription	dd	?	; Offset to the metafile description record. This is 0 if there is no description string
 emh_nPalEntries		dd	?	; Number of entries in the metafile palette.
 emh_szlDevice		dd	?, ?	; Size of the reference device in pels
 emh_szlMillimeters		dd	?, ?	; Size of the reference device in millimeters
 emh_cbPixelFormat	dd	?	; Size of PIXELFORMATDESCRIPTOR information This is 0 if no pixel format is set
 emh_offPixelFormat	dd	?	; Offset to PIXELFORMATDESCRIPTOR This is 0 if no pixel format is set
 emh_bOpenGL		dd	?	; TRUE if OpenGL commands are present in the metafile, otherwise FALSE
ENHMETAHEADER		ENDS

; tmPitchAndFamily flags 
TMPF_FIXED_PITCH	= 01
TMPF_VECTOR 		= 02
TMPF_DEVICE 		= 08
TMPF_TRUETYPE 		= 04

; BCHAR definition for APPs

TEXTMETRICA		STRUC
 tmHeight		dd	?
 tmAscent		dd	?
 tmDescent		dd	?
 tmInternalLeading		dd	?
 tmExternalLeading		dd	?
 tmAveCharWidth		dd	?
 tmMaxCharWidth		dd	?
 tmWeight		dd	?
 tmOverhang		dd	?
 tmDigitizedAspectX	dd	?
 tmDigitizedAspectY	dd	?
 tmFirstChar		db	?
 tmLastChar		db	?
 tmDefaultChar		db	?
 tmBreakChar		db	?
 tmItalic		db	?
 tmUnderlined		db	?
 tmStruckOut		db	?
 tmPitchAndFamily		db	?
 tmCharSet		db	?
TEXTMETRICA		ENDS

TEXTMETRIC		equ	TEXTMETRICA

; ntmFlags field flags 
NTM_REGULAR 	= 00000040h
NTM_BOLD	= 00000020h
NTM_ITALIC	= 00000001h

NEWTEXTMETRICA	STRUC
 tmHeight		dd	?
 tmAscent		dd	?
 tmDescent		dd	?
 tmInternalLeading		dd	?
 tmExternalLeading		dd	?
 tmAveCharWidth		dd	?
 tmMaxCharWidth		dd	?
 tmWeight		dd	?
 tmOverhang		dd	?
 tmDigitizedAspectX	dd	?
 tmDigitizedAspectY	dd	?
 tmFirstChar		db	?
 tmLastChar		db	?
 tmDefaultChar		db	?
 tmBreakChar		db	?
 tmItalic		db	?
 tmUnderlined		db	?
 tmStruckOut		db	?
 tmPitchAndFamily		db	?
 tmCharSet		db	?
 ntmFlags		dd	?
 ntmSizeEM		dd	?
 ntmCellHeight		dd	?
 ntmAvgWidth		dd	?
NEWTEXTMETRICA	ENDS

NEWTEXTMETRIC		equ	NEWTEXTMETRICA

NEWTEXTMETRICEXA	STRUC
 ntmTm	NEWTEXTMETRICA	<?>
 ntmFontSig	FONTSIGNATURE		<?>
NEWTEXTMETRICEXA	ENDS

NEWTEXTMETRICEX	equ	NEWTEXTMETRICEXA

; GDI Logical Objects: 

; Pel Array 

PELARRAY	STRUC
 paXCount		dd	?
 paYCount		dd	?
 paXExt		dd	?
 paYExt		dd	?
 paRGBs		db	?
PELARRAY	ENDS

; Logical Brush (or Pattern) 
LOGBRUSH	STRUC
 lbStyle	HANDLE	?
 lbColor	COLORREF	?
 lbHatch	HANDLE	?
LOGBRUSH	ENDS

; Logical Pen 
LOGPEN	STRUC
 lopnStyle	HANDLE	?
 lopnWidth	POINT	<?>
 lopnColor	COLORREF	?
LOGPEN	ENDS

EXTLOGPEN	STRUC
 elpPenStyle	dd	?
 elpWidth	dd	?
 elpBrushStyle	dd	?
 elpColor	COLORREF	<?>
 elpHatch	dd	?
 elpNumEntries	dd	?
 elpStyleEntry	dd	?
EXTLOGPEN	ENDS

PALETTEENTRY	STRUC
 peRed		db	?
 peGreen		db	?
 peBlue		db	?
 peFlags		db	?
PALETTEENTRY	ENDS

; Logical Palette 
LOGPALETTE	STRUC
 palVersion	dw	?
 palNumEntries	dw	?
LOGPALETTE	ENDS

palPalEntry	equ	sizeof LOGPALETTE


; Structure passed to FONTENUMPROC 
ENUMLOGFONTA	STRUC
 elfLogFont	LOGFONTA	<?>
 elfFullName	db	LF_FULLFACESIZE dup(?)
 elfStyle	db	LF_FACESIZE dup(?)
ENUMLOGFONTA	ENDS

; Structure passed to FONTENUMPROC 

ENUMLOGFONT	equ	ENUMLOGFONTA

ENUMLOGFONTEXA	STRUC
 elfLogFont	LOGFONTA	<?>
 elfFullName	db	LF_FULLFACESIZE dup(?)
 elfStyle	db	LF_FACESIZE dup(?)
 elfScript	db	LF_FACESIZE dup(?)
ENUMLOGFONTEXA	ENDS

ENUMLOGFONTEX	equ	ENUMLOGFONTEXA

PANOSE	STRUC
 bFamilyType	db	?
 bSerifStyle	db	?
 bWeight	db	?
 bProportion	db	?
 bContrast	db	?
 bStrokeVariation	db	?
 bArmStyle	db	?
 bLetterform	db	?
 bMidline	db	?
 bXHeight	db	?
PANOSE	ENDS

PAN_ANY	= 0 ; Any
PAN_NO_FIT	= 1 ; No Fit 

PAN_FAMILY_TEXT_DISPLAY	= 2 ; Text and Display 
PAN_FAMILY_SCRIPT	= 3 ; Script 
PAN_FAMILY_DECORATIVE	= 4 ; Decorative 
PAN_FAMILY_PICTORIAL	= 5 ; Pictorial

PAN_SERIF_COVE		= 2 ; Cove 
PAN_SERIF_OBTUSE_COVE	= 3 ; Obtuse Cove
PAN_SERIF_SQUARE_COVE	= 4 ; Square Cove
PAN_SERIF_OBTUSE_SQUARE_COVE	=5 ; Obtuse Square Cove 
PAN_SERIF_SQUARE	= 6 ; Square 
PAN_SERIF_THIN		= 7 ; Thin 
PAN_SERIF_BONE		= 8 ; Bone 
PAN_SERIF_EXAGGERATED	= 9 ; Exaggerated
PAN_SERIF_TRIANGLE	= 10 ; Triangle 
PAN_SERIF_NORMAL_SANS	= 11 ; Normal Sans
PAN_SERIF_OBTUSE_SANS	= 12 ; Obtuse Sans
PAN_SERIF_PERP_SANS	= 13 ; Prep Sans
PAN_SERIF_FLARED	= 14 ; Flared 
PAN_SERIF_ROUNDED	= 15 ; Rounded

PAN_WEIGHT_VERY_LIGHT	= 2 ; Very Light 
PAN_WEIGHT_LIGHT	= 3 ; Light
PAN_WEIGHT_THIN	= 4 ; Thin 
PAN_WEIGHT_BOOK	= 5 ; Book 
PAN_WEIGHT_MEDIUM	= 6 ; Medium 
PAN_WEIGHT_DEMI	= 7 ; Demi 
PAN_WEIGHT_BOLD	= 8 ; Bold 
PAN_WEIGHT_HEAVY	= 9 ; Heavy
PAN_WEIGHT_BLACK	= 10 ; Black
PAN_WEIGHT_NORD	= 11 ; Nord 

PAN_PROP_OLD_STYLE	= 2 ; Old Style
PAN_PROP_MODERN	= 3 ; Modern 
PAN_PROP_EVEN_WIDTH	= 4 ; Even Width 
PAN_PROP_EXPANDED	= 5 ; Expanded 
PAN_PROP_CONDENSED	= 6 ; Condensed
PAN_PROP_VERY_EXPANDED	= 7 ; Very Expanded
PAN_PROP_VERY_CONDENSED	= 8 ; Very Condensed 
PAN_PROP_MONOSPACED	= 9 ; Monospaced 

PAN_CONTRAST_NONE	= 2 ; None 
PAN_CONTRAST_VERY_LOW	= 3 ; Very Low 
PAN_CONTRAST_LOW	= 4 ; Low
PAN_CONTRAST_MEDIUM_LOW	= 5 ; Medium Low 
PAN_CONTRAST_MEDIUM	= 6 ; Medium 
PAN_CONTRAST_MEDIUM_HIGH	= 7 ; Mediim High
PAN_CONTRAST_HIGH	= 8 ; High 
PAN_CONTRAST_VERY_HIGH	= 9 ; Very High

PAN_STROKE_GRADUAL_DIAG	= 2 ; Gradual/Diagonal 
PAN_STROKE_GRADUAL_TRAN	= 3 ; Gradual/Transitional 
PAN_STROKE_GRADUAL_VERT	= 4 ; Gradual/Vertical 
PAN_STROKE_GRADUAL_HORZ	= 5 ; Gradual/Horizontal 
PAN_STROKE_RAPID_VERT	= 6 ; Rapid/Vertical 
PAN_STROKE_RAPID_HORZ	= 7 ; Rapid/Horizontal 
PAN_STROKE_INSTANT_VERT	= 8 ; Instant/Vertical 

PAN_STRAIGHT_ARMS_HORZ	= 2 ; Straight Arms/Horizontal 
PAN_STRAIGHT_ARMS_WEDGE	= 3 ; Straight Arms/Wedge
PAN_STRAIGHT_ARMS_VERT	= 4 ; Straight Arms/Vertical 
PAN_STRAIGHT_ARMS_SINGLE_SERIF	= 5 ; Straight Arms/Single-Serif 
PAN_STRAIGHT_ARMS_DOUBLE_SERIF	= 6 ; Straight Arms/Double-Serif 
PAN_BENT_ARMS_HORZ	= 7 ; Non-Straight Arms/Horizontal 
PAN_BENT_ARMS_WEDGE	= 8 ; Non-Straight Arms/Wedge
PAN_BENT_ARMS_VERT	= 9 ; Non-Straight Arms/Vertical 
PAN_BENT_ARMS_SINGLE_SERIF	= 10 ; Non-Straight Arms/Single-Serif 
PAN_BENT_ARMS_DOUBLE_SERIF	= 11 ; Non-Straight Arms/Double-Serif 

PAN_LETT_NORMAL_CONTACT	= 2 ; Normal/Contact 
PAN_LETT_NORMAL_WEIGHTED	= 3 ; Normal/Weighted
PAN_LETT_NORMAL_BOXED	= 4 ; Normal/Boxed 
PAN_LETT_NORMAL_FLATTENED	= 5 ; Normal/Flattened 
PAN_LETT_NORMAL_ROUNDED	= 6 ; Normal/Rounded 
PAN_LETT_NORMAL_OFF_CENTER	= 7 ; Normal/Off Center
PAN_LETT_NORMAL_SQUARE	= 8 ; Normal/Square
PAN_LETT_OBLIQUE_CONTACT	= 9 ; Oblique/Contact
PAN_LETT_OBLIQUE_WEIGHTED	= 10 ; Oblique/Weighted 
PAN_LETT_OBLIQUE_BOXED	= 11 ; Oblique/Boxed
PAN_LETT_OBLIQUE_FLATTENED	= 12 ; Oblique/Flattened
PAN_LETT_OBLIQUE_ROUNDED	= 13 ; Oblique/Rounded
PAN_LETT_OBLIQUE_OFF_CENTER	= 14 ; Oblique/Off Center 
PAN_LETT_OBLIQUE_SQUARE	=15 ; Oblique/Square 

PAN_MIDLINE_STANDARD_TRIMMED	= 2 ; Standard/Trimmed 
PAN_MIDLINE_STANDARD_POINTED	= 3 ; Standard/Pointed 
PAN_MIDLINE_STANDARD_SERIFED	= 4 ; Standard/Serifed 
PAN_MIDLINE_HIGH_TRIMMED	= 5 ; High/Trimmed 
PAN_MIDLINE_HIGH_POINTED	= 6 ; High/Pointed 
PAN_MIDLINE_HIGH_SERIFED	= 7 ; High/Serifed 
PAN_MIDLINE_CONSTANT_TRIMMED	= 8 ; Constant/Trimmed 
PAN_MIDLINE_CONSTANT_POINTED	= 9 ; Constant/Pointed 
PAN_MIDLINE_CONSTANT_SERIFED	= 10 ; Constant/Serifed 
PAN_MIDLINE_LOW_TRIMMED	= 11 ; Low/Trimmed
PAN_MIDLINE_LOW_POINTED	= 12 ; Low/Pointed
PAN_MIDLINE_LOW_SERIFED	= 13 ; Low/Serifed

PAN_XHEIGHT_CONSTANT_SMALL	= 2 ; Constant/Small 
PAN_XHEIGHT_CONSTANT_STD	= 3 ; Constant/Standard
PAN_XHEIGHT_CONSTANT_LARGE	= 4 ; Constant/Large 
PAN_XHEIGHT_DUCKING_SMALL	= 5 ; Ducking/Small
PAN_XHEIGHT_DUCKING_STD	= 6 ; Ducking/Standard 
PAN_XHEIGHT_DUCKING_LARGE	= 7 ; Ducking/Large


ELF_VENDOR_SIZE	= 4

; The extended logical font 
; An extension of the ENUMLOGFONT 

EXTLOGFONTA	STRUC
 elfLogFont	LOGFONTA	<?>
 elfFullName	db	LF_FULLFACESIZE	dup(?)
 elfStyle	db	LF_FACESIZE	dup(?)
 elfVersion	dd	? 	; 0 for the first release of NT 
 elfStyleSize	dd	?
 elfMatch	dd	?
 elfReserved	dd	?
 elfVendorId	db	ELF_VENDOR_SIZE	dup(?)
 elfCulture	dd	? ; 0 for Latin 
 elfPanose	PANOSE	<?>
EXTLOGFONTA	ENDS

EXTLOGFONT	equ	EXTLOGFONTA


DEVMODEA		STRUC
 dmDeviceName		db	CCHDEVICENAME	dup(?)
 dmSpecVersion		dw	?
 dmDriverVersion		dw	?
 dmSize		dw	?
 dmDriverExtra		dw	?
 dmFields		dd	?
 dmOrientation		dw	?
 dmPaperSize		dw	?
 dmPaperLength		dw	?
 dmPaperWidth		dw	?
 dmScale		dw	?
 dmCopies		dw	?
 dmDefaultSource		dw	?
 dmPrintQuality		dw	?
 dmColor		dw	?
 dmDuplex		dw	?
 dmYResolution		dw	?
 dmTTOption		dw	?
 dmCollate		dw	?
 dmFormName		db	CCHFORMNAME	dup(?)
 dmLogPixels		dw	?
 dmBitsPerPel		dd	?
 dmPelsWidth		dd	?
 dmPelsHeight		dd	?
 dmDisplayFlags		dd	?
 dmDisplayFrequency	dd	?
 dmICMMethod		dd	?
 dmICMIntent		dd	?
 dmMediaType		dd	?
 dmDitherType		dd	?
 dmICCManufacturer	dd	?
 dmICCModel		dd	?
 dmPanningWidth		dd	?
 dmPanningHeight		dd	?
DEVMODEA		ENDS


DEVMODE		equ	DEVMODEA

DM_SPECVERSION 		= 0401h

; field selection bits 
DM_ORIENTATION	= 00000001h
DM_PAPERSIZE		= 00000002h
DM_PAPERLENGTH		= 00000004h
DM_PAPERWIDTH 		= 00000008h
DM_SCALE		= 00000010h
DM_COPIES 		= 00000100h
DM_DEFAULTSOURCE	= 00000200h
DM_PRINTQUALITY 	= 00000400h
DM_COLOR		= 00000800h
DM_DUPLEX 		= 00001000h
DM_YRESOLUTION	= 00002000h
DM_TTOPTION 		= 00004000h
DM_COLLATE		= 00008000h
DM_FORMNAME 		= 00010000h
DM_LOGPIXELS		= 00020000h
DM_BITSPERPEL 		= 00040000h
DM_PELSWIDTH		= 00080000h
DM_PELSHEIGHT 		= 00100000h
DM_DISPLAYFLAGS 	= 00200000h
DM_DISPLAYFREQUENCY 	= 00400000h
DM_PANNINGWIDTH 	= 00800000h
DM_PANNINGHEIGHT	= 01000000h
DM_ICMMETHOD		= 02000000h
DM_ICMINTENT		= 04000000h
DM_MEDIATYPE		= 08000000h
DM_DITHERTYPE 		= 10000000h
DM_ICCMANUFACTURER	= 20000000h
DM_ICCMODEL 		= 40000000h

; orientation selections 
DMORIENT_PORTRAIT	= 1
DMORIENT_LANDSCAPE	= 2

; paper selections 
DMPAPER_FIRST			= DMPAPER_LETTER
DMPAPER_LETTER			= 1; Letter 8 1/2 x 11 in 
DMPAPER_LETTERSMALL		= 2; Letter Small 8 1/2 x 11 in 
DMPAPER_TABLOID		= 3; Tabloid 11 x 17 in 
DMPAPER_LEDGER			= 4; Ledger 17 x 11 in
DMPAPER_LEGAL			= 5; Legal 8 1/2 x 14 in
DMPAPER_STATEMENT		= 6; Statement 5 1/2 x 8 1/2 in 
DMPAPER_EXECUTIVE		= 7; Executive 7 1/4 x 10 1/2 in
DMPAPER_A3			= 8; A3 297 x 420 mm
DMPAPER_A4			= 9; A4 210 x 297 mm
DMPAPER_A4SMALL		= 10; A4 Small 210 x 297 mm
DMPAPER_A5			= 11; A5 148 x 210 mm
DMPAPER_B4			= 12; B4 (JIS) 250 x 354 
DMPAPER_B5			= 13; B5 (JIS) 182 x 257 mm
DMPAPER_FOLIO			= 14; Folio 8 1/2 x 13 in
DMPAPER_QUARTO		= 15; Quarto 215 x 275 mm
DMPAPER_10X14			= 16; 1	= 14 in 
DMPAPER_11X17			= 17; 11x17 in 
DMPAPER_NOTE			= 18; Note 8 1/2 x 11 in 
DMPAPER_ENV_9			= 19; Envelope 9 3 7/8 x 8 7/8
DMPAPER_ENV_10			= 20; Envelope 10 4 1/8 x 9 1/2 
DMPAPER_ENV_11			= 21; Envelope 11 4 1/2 x 10 3/8
DMPAPER_ENV_12			= 22; Envelope 12 4 \276 x 11 
DMPAPER_ENV_14			= 23; Envelope 14 5 x 11 1/2
DMPAPER_CSHEET			= 24; C size sheet 
DMPAPER_DSHEET			= 25; D size sheet 
DMPAPER_ESHEET			= 26; E size sheet 
DMPAPER_ENV_DL			= 27; Envelope DL 110 x 220mm
DMPAPER_ENV_C5			= 28; Envelope C5 162 x 229 mm 
DMPAPER_ENV_C3			= 29; Envelope C3324 x 458 mm
DMPAPER_ENV_C4			= 30; Envelope C4229 x 324 mm
DMPAPER_ENV_C6			= 31; Envelope C6114 x 162 mm
DMPAPER_ENV_C65		= 32; Envelope C65 114 x 229 mm
DMPAPER_ENV_B4			= 33; Envelope B4250 x 353 mm
DMPAPER_ENV_B5			= 34; Envelope B5176 x 250 mm
DMPAPER_ENV_B6			= 35; Envelope B6176 x 125 mm
DMPAPER_ENV_ITALY		= 36; Envelope 110 x 230 mm
DMPAPER_ENV_MONARCH		= 37; Envelope Monarch 3.875 x 7.5 in
DMPAPER_ENV_PERSONAL		= 38; 6 3/4 Envelope 3 5/8 x 6 1/2 in
DMPAPER_FANFOLD_US		= 39; US Std Fanfold 14 7/8 x 11 in
DMPAPER_FANFOLD_STD_GERMAN		= 40; German Std Fanfold 8 1/2 x 12 in 
DMPAPER_FANFOLD_LGL_GERMAN		= 41; German Legal Fanfold 8 1/2 x 13 in 
DMPAPER_ISO_B4			= 42; B4 (ISO) 250 x 353 mm
DMPAPER_JAPANESE_POSTCARD		= 43; Japanese Postcard 100 x 148 mm 
DMPAPER_9X11			= 44; 9 x 11 in
DMPAPER_10X11			= 45; 10 x 11 in 
DMPAPER_15X11			= 46; 15 x 11 in 
DMPAPER_ENV_INVITE		= 47; Envelope Invite 220 x 220 mm 
DMPAPER_RESERVED_48		= 48; RESERVED--DO NOT USE 
DMPAPER_RESERVED_49		= 49; RESERVED--DO NOT USE 
DMPAPER_LETTER_EXTRA		= 50; Letter Extra 9 \275 x 12 in
DMPAPER_LEGAL_EXTRA		= 51; Legal Extra 9 \275 x 15 in 
DMPAPER_TABLOID_EXTRA		= 52; Tabloid Extra 11.69 x 18 in
DMPAPER_A4_EXTRA		= 53; A4 Extra 9.27 x 12.69 in 
DMPAPER_LETTER_TRANSVERSE		= 54; Letter Transverse 8 \275 x 11 in 
DMPAPER_A4_TRANSVERSE		= 55; A4 Transverse 210 x 297 mm 
DMPAPER_LETTER_EXTRA_TRANSVERSE	= 56 ; Letter Extra Transverse 9\275 x 12 in 
DMPAPER_A_PLUS			= 57; SuperA/SuperA/A4 227 x 356 mm
DMPAPER_B_PLUS			= 58; SuperB/SuperB/A3 305 x 487 mm
DMPAPER_LETTER_PLUS		= 59; Letter Plus 8.5 x 12.69 in 
DMPAPER_A4_PLUS		= 60; A4 Plus 210 x 330 mm 
DMPAPER_A5_TRANSVERSE		= 61; A5 Transverse 148 x 210 mm 
DMPAPER_B5_TRANSVERSE		= 62; B5 (JIS) Transverse 182 x 257 mm 
DMPAPER_A3_EXTRA		= 63; A3 Extra 322 x 445 mm
DMPAPER_A5_EXTRA		= 64; A5 Extra 174 x 235 mm
DMPAPER_B5_EXTRA		= 65; B5 (ISO) Extra 201 x 276 mm
DMPAPER_A2			= 66; A2 420 x 594 mm
DMPAPER_A3_TRANSVERSE		= 67; A3 Transverse 297 x 420 mm 
DMPAPER_A3_EXTRA_TRANSVERSE		= 68; A3 Extra Transverse 322 x 445 mm 

DMPAPER_LAST		= DMPAPER_A3_EXTRA_TRANSVERSE
DMPAPER_USER		= 256

; bin selections 
DMBIN_FIRST		= DMBIN_UPPER
DMBIN_UPPER		= 1
DMBIN_ONLYONE		= 1
DMBIN_LOWER		= 2
DMBIN_MIDDLE		= 3
DMBIN_MANUAL		= 4
DMBIN_ENVELOPE		= 5
DMBIN_ENVMANUAL	= 6
DMBIN_AUTO		= 7
DMBIN_TRACTOR		= 8
DMBIN_SMALLFMT 	= 9
DMBIN_LARGEFMT		= 10
DMBIN_LARGECAPACITY	= 11
DMBIN_CASSETTE		= 14
DMBIN_FORMSOURCE	= 15
DMBIN_LAST		= DMBIN_FORMSOURCE

DMBIN_USER		= 256 ; device specific bins start here 

; print qualities 
DMRES_DRAFT	= -1
DMRES_LOW	= -2
DMRES_MEDIUM	= -3
DMRES_HIGH	= -4

; color enable/disable for color printers 
DMCOLOR_MONOCHROME	= 1
DMCOLOR_COLOR		= 2

; duplex enable 
DMDUP_SIMPLEX		= 1
DMDUP_VERTICAL		= 2
DMDUP_HORIZONTAL	= 3

; TrueType options 
DMTT_BITMAP		= 1 ; print TT fonts as graphics 
DMTT_DOWNLOAD	= 2 ; download TT fonts as soft fonts 
DMTT_SUBDEV		= 3 ; substitute device fonts for TT fonts 
DMTT_DOWNLOAD_OUTLINE	= 4 ; download TT fonts as outline soft fonts 

; Collation selections 
DMCOLLATE_FALSE	= 0
DMCOLLATE_TRUE		= 1

; DEVMODE dmDisplayFlags flags 
;DM_GRAYSCALE		= 00000001 ; This flag is no longer valid 
;DM_INTERLACED 		= 00000002 ; This flag is no longer valid 
DMDISPLAYFLAGS_TEXTMODE 	= 00000004

; ICM methods 
DMICMMETHOD_NONE	= 1 ; ICM disabled 
DMICMMETHOD_SYSTEM	= 2 ; ICM handled by system 
DMICMMETHOD_DRIVER	= 3 ; ICM handled by driver 
DMICMMETHOD_DEVICE	= 4 ; ICM handled by device 

DMICMMETHOD_USER	= 256 ; Device-specific methods start here 

; ICM Intents 
DMICM_SATURATE	= 1 ; Maximize color saturation 
DMICM_CONTRAST	= 2 ; Maximize color contrast 
DMICM_COLORMETRIC	= 3 ; Use specific color metric 
DMICM_USER		= 256 ; Device-specific intents start here 

; Media types 

DMMEDIA_STANDARD	= 1 ; Standard paper 
DMMEDIA_TRANSPARENCY	= 2 ; Transparency 
DMMEDIA_GLOSSY	= 3 ; Glossy paper 
DMMEDIA_USER		= 256 ; Device-specific media start here 

; Dither types 
DMDITHER_NONE		= 1 ; No dithering 
DMDITHER_COARSE	= 2 ; Dither with a coarse brush 
DMDITHER_FINE		= 3 ; Dither with a fine brush 
DMDITHER_LINEART	= 4 ; LineArt dithering 
DMDITHER_GRAYSCALE	= 5 ; Device does grayscaling 
DMDITHER_USER		= 256 ; Device-specific dithers start here 

; GetRegionData/ExtCreateRegion 

RDH_RECTANGLES	= 1

RGNDATAHEADER	STRUC
 dth_dwSize		dd	?
 dth_iType		dd	?
 dth_nCount		dd	?
 dth_nRgnSize		dd	?
 dth_rcBound		RECT	<?>
RGNDATAHEADER	ENDS

RGNDATA	STRUC
 rd_rdh	RGNDATAHEADER	<?>
 rd_charBuffer	dd	?
RGNDATA	ENDS

ABC	STRUC
 abcA	HANDLE	?
 abcB	HANDLE	?
 abcC	HANDLE	?
ABC	ENDS

ABCFLOAT	STRUC
FLOAT abcfA;
FLOAT abcfB;
FLOAT abcfC;
ABCFLOAT, *PABCFLOAT, NEAR *NPABCFLOAT, FAR *LPABCFLOAT;

OUTLINETEXTMETRICA	STRUC
 otmSize		HANDLE	?
 otmTextMetrics		TEXTMETRICA	<?>
 otmFiller		db	?
 otmPanoseNumber		PANOSE	<?>
 otmfsSelection		HANDLE	?
 otmfsType		HANDLE	?
 intotmsCharSlopeRise	dd	?
 intotmsCharSlopeRun	dd	?
 intotmItalicAngle		dd	?
 otmEMSquare		HANDLE	?
 intotmAscent		dd	?
 intotmDescent		dd	?
 otmLineGap		HANDLE	?
 otmsCapEmHeight		HANDLE	?
 otmsXHeight		HANDLE	?
 otmrcFontBox		RECT	<?>
 intotmMacAscent		dd	?
 intotmMacDescent		dd	?
 otmMacLineGap		HANDLE	?
 otmusMinimumPPEM		HANDLE	?
 otmptSubscriptSize		POINT	<?>
 otmptSubscriptOffset	POINT	<?>
 otmptSuperscriptSize	POINT	<?>
 otmptSuperscriptOffset	POINT	<?>
 otmsStrikeoutSize		HANDLE	?
 intotmsStrikeoutPosition	dd	?
 intotmsUnderscoreSize	dd	?
 intotmsUnderscorePosition	dd	?
 otmpFamilyName		dd	?
 otmpFaceName		dd	?
 otmpStyleName		dd	?
 otmpFullName		dd	?
OUTLINETEXTMETRICA	ENDS

OUTLINETEXTMETRIC	equ	OUTLINETEXTMETRICA

POLYTEXTA	STRUC
 pot_x	HANDLE	?
 pot_y	HANDLE	?
 pot_n	HANDLE	?
 pot_lpstr	dd	?
 pot_uiFlags	HANDLE	?
 pot_rcl	RECT	<?>
 pot_pdx	dd	?
POLYTEXTA	ENDS

POLYTEXT	equ	POLYTEXTA

FIXED	STRUC
 fract	dw	?
 value	dw	?
FIXED	ENDS

MAT2	STRUC
 eM11	FIXED	<?>
 eM12	FIXED	<?>
 eM21	FIXED	<?>
 eM22	FIXED	<?>
MAT2	ENDS


GLYPHMETRICS	STRUC
 gmBlackBoxX	HANDLE	?
 gmBlackBoxY	HANDLE	?
 gmptGlyphOrigin	HANDLE	?, ?
 gmCellIncX	dw	?
 gmCellIncY	dw	?
GLYPHMETRICS	ENDS

;GetGlyphOutline constants

GGO_METRICS		= 0
GGO_BITMAP		= 1
GGO_NATIVE		= 2
GGO_GRAY2_BITMAP	= 4
GGO_GRAY4_BITMAP	= 5
GGO_GRAY8_BITMAP	= 6
GGO_GLYPH_INDEX	= 0080h

TT_POLYGON_TYPE	= 24
TT_PRIM_LINE		= 1
TT_PRIM_QSPLINE	= 2

POINTFX	STRUC
 pfx_x	FIXED	<?>
 pfx_y	FIXED	<?>
POINTFX	ENDS

TTPOLYCURVE	STRUC
 wType	dw	?
 cpfx	dw	?
 apfx	POINTFX	<?>
TTPOLYCURVE	ENDS

TTPOLYGONHEADER	STRUC
  tph_cb		dd	?
  tph_dwType		dd	?
 tph_pfxStart		POINTFX	<?>
TTPOLYGONHEADER	ENDS

GCP_DBCS 		= 0001h
GCP_REORDER		= 0002h
GCP_USEKERNING 		= 0008h
GCP_GLYPHSHAPE 		= 0010h
GCP_LIGATE 		= 0020h
;;GCP_GLYPHINDEXING	= 0080h
GCP_DIACRITIC		= 0100h
GCP_KASHIDA		= 0400h
GCP_ERROR		= 8000h
FLI_MASK 		= 103Bh

GCP_JUSTIFY		= 00010000h
;;GCP_NODIACRITICS 	= 00020000h
FLI_GLYPHS 		= 00040000h
GCP_CLASSIN		= 00080000h
GCP_MAXEXTENT		= 00100000h
GCP_JUSTIFYIN		= 00200000h
GCP_DISPLAYZWG		= 00400000h
GCP_SYMSWAPOFF		= 00800000h
GCP_NUMERICOVERRIDE 	= 01000000h
GCP_NEUTRALOVERRIDE 	= 02000000h
GCP_NUMERICSLATIN 	= 04000000h
GCP_NUMERICSLOCAL 	= 08000000h

GCPCLASS_LATIN			= 1
GCPCLASS_HEBREW		= 2
GCPCLASS_ARABIC			= 2
GCPCLASS_NEUTRAL		= 3
GCPCLASS_LOCALNUMBER		= 4
GCPCLASS_LATINNUMBER		= 5
GCPCLASS_LATINNUMERICTERMINATOR	= 6
GCPCLASS_LATINNUMERICSEPARATOR	= 7
GCPCLASS_NUMERICSEPARATOR		= 8
GCPCLASS_PREBOUNDLTR 		= 80h
GCPCLASS_PREBOUNDRTL 		= 40h
GCPCLASS_POSTBOUNDLTR		= 20h
GCPCLASS_POSTBOUNDRTL		= 10h
GCPGLYPH_LINKBEFORE		= 8000h
GCPGLYPH_LINKAFTER 		= 4000h


GCP_RESULTSA		STRUC
 gcp_lStructSize		dd	?
 gcp_lpOutString		dd	?
 gcp_lpOrder		dd	?
 gcp_lpDx		dd	?
 gcp_lpCaretPos		dd	?
 gcp_lpClass		dd	?
 gcp_lpGlyphs		dd	?
 gcp_nGlyphs		dd	?
 gcp_nMaxFit		dd	?
GCP_RESULTSA		ENDS

GCP_RESULTS		equ	GCP_RESULTSA

RASTERIZER_STATUS	STRUC
 ras_nSize		dw	?
 ras_wFlags		dw	?
 ras_nLanguageID		dw	?
RASTERIZER_STATUS	ENDS

; bits defined in wFlags of RASTERIZER_STATUS 
TT_AVAILABLE	= 0001
TT_ENABLED	= 0002

; Pixel format descriptor 
PIXELFORMATDESCRIPTOR	STRUC
 pfd_nSize		dw	?
 pfd_nVersion		dw	?
 pfd_dwFlags		dd	?
 pfd_iPixelType		db	?
 pfd_cColorBits		db	?
 pfd_cRedBits		db	?
 pfd_cRedShift		db	?
 pfd_cGreenBits		db	?
 pfd_cGreenShift		db	?
 pfd_cBlueBits		db	?
 pfd_cBlueShift		db	?
 pfd_cAlphaBits		db	?
 pfd_cAlphaShift		db	?
 pfd_cAccumBits		db	?
 pfd_cAccumRedBits	db	?
 pfd_cAccumGreenBits	db	?
 pfd_cAccumBlueBits	db	?
 pfd_cAccumAlphaBits	db	?
 pfd_cDepthBits		db	?
 pfd_cStencilBits		db	?
 pfd_cAuxBuffers		db	?
 pfd_iLayerType		db	?
 pfd_bReserved		db	?
 pfd_dwLayerMask		dd	?
 pfd_dwVisibleMask		dd	?
 pfd_dwDamageMask	dd	?
PIXELFORMATDESCRIPTOR	ENDS

; pixel types 
PFD_TYPE_RGBA		= 0
PFD_TYPE_COLORINDEX	= 1

; layer types 
PFD_MAIN_PLANE		=  0
PFD_OVERLAY_PLANE	=  1
PFD_UNDERLAY_PLANE	=  -1

; PIXELFORMATDESCRIPTOR flags 
PFD_DOUBLEBUFFER	= 00000001h
PFD_STEREO		= 00000002h
PFD_DRAW_TO_WINDOW	= 00000004h
PFD_DRAW_TO_BITMAP	= 00000008h
PFD_SUPPORT_GDI 	= 00000010h
PFD_SUPPORT_OPENGL	= 00000020h
PFD_GENERIC_FORMAT	= 00000040h
PFD_NEED_PALETTE	= 00000080h
PFD_NEED_SYSTEM_PALETTE 	= 00000100h
PFD_SWAP_EXCHANGE 	= 00000200h
PFD_SWAP_COPY 		= 00000400h
PFD_SWAP_LAYER_BUFFERS	= 00000800h
PFD_GENERIC_ACCELERATED 	= 00001000h

; PIXELFORMATDESCRIPTOR flags for use in ChoosePixelFormat only 
PFD_DEPTH_DONTCARE	= 20000000h
PFD_DOUBLEBUFFER_DONTCARE 	= 40000000h
PFD_STEREO_DONTCARE 	= 80000000h


; mode selections for the device mode function 
DM_UPDATE	=  1
DM_COPY	=  2
DM_PROMPT	=  4
DM_MODIFY	=  8

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
DC_BINADJUST		= 19
DC_EMF_COMPLIANT	= 20
DC_DATATYPE_PRODUCED	= 21
DC_COLLATE		= 22


; bit fields of the return value 	 for DC_TRUETYPE 
DCTT_BITMAP 		= 0000001
DCTT_DOWNLOAD 	= 0000002
DCTT_SUBDEV 		= 0000004
DCTT_DOWNLOAD_OUTLINE 	= 0000008

; return values for DC_BINADJUST 
DCBA_FACEUPNONE 	= 0000h
DCBA_FACEUPCENTER 	= 0001h
DCBA_FACEUPLEFT 	= 0002h
DCBA_FACEUPRIGHT	= 0003h
DCBA_FACEDOWNNONE 	= 0100h
DCBA_FACEDOWNCENTER 	= 0101h
DCBA_FACEDOWNLEFT 	= 0102h
DCBA_FACEDOWNRIGHT	= 0103h

; Flags value for COLORADJUSTMENT 
CA_NEGATIVE 	= 0001
CA_LOG_FILTER 	= 0002

; IlluminantIndex values 
ILLUMINANT_DEVICE_DEFAULT	= 0
ILLUMINANT_A		= 1
ILLUMINANT_B		= 2
ILLUMINANT_C		= 3
ILLUMINANT_D50		= 4
ILLUMINANT_D55		= 5
ILLUMINANT_D65		= 6
ILLUMINANT_D75		= 7
ILLUMINANT_F2		= 8
ILLUMINANT_MAX_INDEX	= ILLUMINANT_F2

ILLUMINANT_TUNGSTEN	= ILLUMINANT_A
ILLUMINANT_DAYLIGHT	= ILLUMINANT_C
ILLUMINANT_FLUORESCENT	= ILLUMINANT_F2
ILLUMINANT_NTSC	= ILLUMINANT_C

; Min and max for RedGamma, GreenGamma, BlueGamma 
RGB_GAMMA_MIN 		= 02500
RGB_GAMMA_MAX		= 65000

; Min and max for ReferenceBlack and ReferenceWhite 
REFERENCE_WHITE_MIN	= 6000
REFERENCE_WHITE_MAX	= 10000
REFERENCE_BLACK_MIN	= 0
REFERENCE_BLACK_MAX	= 4000

; Min and max for Contrast, Brightness, Colorfulness, RedGreenTint 
COLOR_ADJ_MIN		= -100
COLOR_ADJ_MAX		= 100

COLORADJUSTMENT	STRUC
 caSize		dw	?
 caFlags		dw	?
 caIlluminantIndex		dw	?
 caRedGamma		dw	?
 caGreenGamma		dw	?
 caBlueGamma		dw	?
 caReferenceBlack		dw	?
 caReferenceWhite		dw	?
 caContrast		dw	?
 caBrightness		dw	?
 caColorfulness		dw	?
 caRedGreenTint		dw	?
COLORADJUSTMENT	ENDS

DOCINFOA	STRUC
 din_cbSize	dd	?
 din_lpszDocName	dd	?
 din_lpszOutput	dd	?
IFDEF	WIN32
 din_lpszDatatype	dd	?
 din_fwType	dd	?
ENDIF
DOCINFOA	ENDS

DOCINFO	equ	DOCINFOA

DI_APPBANDING 		= 0001
FONTMAPPER_MAX	= 10

KERNINGPAIR	STRUC
 wFirst	dw	?
 wSecond	dw	?
 intiKernAmount	dd	?
KERNINGPAIR	ENDS

ICM_OFF	= 1
ICM_ON	= 2
ICM_QUERY	= 3

; Enhanced metafile constants.

ENHMETA_SIGNATURE 	= 464D4520h

; Stock object flag used in the object handle index in the enhanced
; metafile records.
; E.g. The object handle index (META_STOCK_OBJECT | BLACK_BRUSH)
; represents the stock object BLACK_BRUSH.

ENHMETA_STOCK_OBJECT	= 80000000h

; Enhanced metafile record types.

EMR_HEADER		= 1
EMR_POLYBEZIER		= 2
EMR_POLYGON		= 3
EMR_POLYLINE		= 4
EMR_POLYBEZIERTO	= 5
EMR_POLYLINETO		= 6
EMR_POLYPOLYLINE	= 7
EMR_POLYPOLYGON	= 8
EMR_SETWINDOWEXTEX	= 9
EMR_SETWINDOWORGEX	= 10
EMR_SETVIEWPORTEXTEX	= 11
EMR_SETVIEWPORTORGEX	= 12
EMR_SETBRUSHORGEX	= 13
EMR_EOF		= 14
EMR_SETPIXELV		= 15
EMR_SETMAPPERFLAGS	= 16
EMR_SETMAPMODE	= 17
EMR_SETBKMODE		= 18
EMR_SETPOLYFILLMODE	= 19
EMR_SETROP2		= 20
EMR_SETSTRETCHBLTMODE	= 21
EMR_SETTEXTALIGN	= 22
EMR_SETCOLORADJUSTMENT	= 23
EMR_SETTEXTCOLOR	= 24
EMR_SETBKCOLOR		= 25
EMR_OFFSETCLIPRGN	= 26
EMR_MOVETOEX		= 27
EMR_SETMETARGN		= 28
EMR_EXCLUDECLIPRECT	= 29
EMR_INTERSECTCLIPRECT	= 30
EMR_SCALEVIEWPORTEXTEX	= 31
EMR_SCALEWINDOWEXTEX	= 32
EMR_SAVEDC		= 33
EMR_RESTOREDC		= 34
EMR_SETWORLDTRANSFORM	= 35
EMR_MODIFYWORLDTRANSFORM	= 36
EMR_SELECTOBJECT	= 37
EMR_CREATEPEN		= 38
EMR_CREATEBRUSHINDIRECT	= 39
EMR_DELETEOBJECT	= 40
EMR_ANGLEARC		= 41
EMR_ELLIPSE		= 42
EMR_RECTANGLE		= 43
EMR_ROUNDRECT		= 44
EMR_ARC		= 45
EMR_CHORD		= 46
EMR_PIE		= 47
EMR_SELECTPALETTE	= 48
EMR_CREATEPALETTE	= 49
EMR_SETPALETTEENTRIES	= 50
EMR_RESIZEPALETTE	= 51
EMR_REALIZEPALETTE	= 52
EMR_EXTFLOODFILL	= 53
EMR_LINETO		= 54
EMR_ARCTO		= 55
EMR_POLYDRAW		= 56
EMR_SETARCDIRECTION	= 57
EMR_SETMITERLIMIT	= 58
EMR_BEGINPATH		= 59
EMR_ENDPATH		= 60
EMR_CLOSEFIGURE	= 61
EMR_FILLPATH		= 62
EMR_STROKEANDFILLPATH	= 63
EMR_STROKEPATH		= 64
EMR_FLATTENPATH	= 65
EMR_WIDENPATH		= 66
EMR_SELECTCLIPPATH	= 67
EMR_ABORTPATH		= 68

;EMR_GDICOMMENT	= 70
EMR_FILLRGN		= 71
EMR_FRAMERGN		= 72
EMR_INVERTRGN		= 73
EMR_PAINTRGN		= 74
EMR_EXTSELECTCLIPRGN	= 75
EMR_BITBLT		= 76
EMR_STRETCHBLT		= 77
EMR_MASKBLT		= 78
EMR_PLGBLT		= 79
EMR_SETDIBITSTODEVICE	= 80
EMR_STRETCHDIBITS	= 81
EMR_EXTCREATEFONTINDIRECTW	= 82
EMR_EXTTEXTOUTA	= 83
EMR_EXTTEXTOUTW	= 84
EMR_POLYBEZIER16	= 85
EMR_POLYGON16		= 86
EMR_POLYLINE16		= 87
EMR_POLYBEZIERTO16	= 88
EMR_POLYLINETO16	= 89
EMR_POLYPOLYLINE16	= 90
EMR_POLYPOLYGON16	= 91
EMR_POLYDRAW16		= 92
EMR_CREATEMONOBRUSH	= 93
EMR_CREATEDIBPATTERNBRUSHPT	= 94
EMR_EXTCREATEPEN	= 95
EMR_POLYTEXTOUTA	= 96
EMR_POLYTEXTOUTW	= 97
EMR_SETICMMODE	= 98
EMR_CREATECOLORSPACE	= 99
EMR_SETCOLORSPACE	= 100
EMR_DELETECOLORSPACE	= 101
EMR_GLSRECORD		= 102
EMR_GLSBOUNDEDRECORD	= 103
EMR_PIXELFORMAT	= 104

EMR_MIN		=  1
EMR_MAX		= 104

; Base record type for the enhanced metafile.

EMR	STRUC
 emr_iType:	dd	?	; Enhanced metafile record type
 rmd_nSize:	dd	?	; Length of the record in bytes. This must be a multiple of 4.
EMR	ENDS

; Base text record type for the enhanced metafile.

EMRTEXT	STRUC
POINTLptlReference;
DWORD nChars;
DWORD offString;; Offset to the string
DWORD fOptions;
RECTL rcl;
DWORD offDx;; Offset to the inter-character spacing array.
; This is always given.
EMRTEXT	ENDS

; Record structures for the enhanced metafile.

ABORTPATH
EMR emr;
EMRABORTPATH,*PEMRABORTPATH,
EMRBEGINPATH,*PEMRBEGINPATH,
EMRENDPATH,*PEMRENDPATH,
EMRCLOSEFIGURE,*PEMRCLOSEFIGURE,
EMRFLATTENPATH,*PEMRFLATTENPATH,
EMRWIDENPATH,*PEMRWIDENPATH,
EMRSETMETARGN, *PEMRSETMETARGN,
EMRSAVEDC, *PEMRSAVEDC,
EMRREALIZEPALETTE, *PEMRREALIZEPALETTE;

EMRSELECTCLIPPATH
EMR emr;
DWORD iMode;
EMRSELECTCLIPPATH,*PEMRSELECTCLIPPATH,
EMRSETBKMODE, *PEMRSETBKMODE,
EMRSETMAPMODE,*PEMRSETMAPMODE,
EMRSETPOLYFILLMODE, *PEMRSETPOLYFILLMODE,
EMRSETROP2, *PEMRSETROP2,
EMRSETSTRETCHBLTMODE, *PEMRSETSTRETCHBLTMODE,
EMRSETICMMODE,*PEMRSETICMMODE,
EMRSETTEXTALIGN,*PEMRSETTEXTALIGN;

tEMRSETMITERLIMIT
{
EMR emr;
FLOAT eMiterLimit;
EMRSETMITERLIMIT, *PEMRSETMITERLIMIT;

tEMRRESTOREDC
{
EMR emr;
LONGiRelative;; Specifies a relative instance
EMRRESTOREDC, *PEMRRESTOREDC;

tEMRSETARCDIRECTION
{
EMR emr;
DWORD iArcDirection;; Specifies the arc direction in the
; advanced graphics mode.
EMRSETARCDIRECTION, *PEMRSETARCDIRECTION;

tEMRSETMAPPERFLAGS
{
EMR emr;
DWORD dwFlags;
EMRSETMAPPERFLAGS, *PEMRSETMAPPERFLAGS;

tEMRSETTEXTCOLOR
{
EMR emr;
COLORREF crColor;
EMRSETBKCOLOR, *PEMRSETBKCOLOR,
EMRSETTEXTCOLOR, *PEMRSETTEXTCOLOR;

tEMRSELECTOBJECT
{
EMR emr;
DWORD ihObject; ; Object handle index
EMRSELECTOBJECT, *PEMRSELECTOBJECT,
EMRDELETEOBJECT, *PEMRDELETEOBJECT;

tEMRSELECTCOLORSPACE
{
EMR emr;
DWORD ihCS; ; ColorSpace handle index
EMRSELECTCOLORSPACE, *PEMRSELECTCOLORSPACE,
EMRDELETECOLORSPACE, *PEMRDELETECOLORSPACE;

tEMRSELECTPALETTE
{
EMR emr;
DWORD ihPal;; Palette handle index, background mode only
EMRSELECTPALETTE, *PEMRSELECTPALETTE;

tEMRRESIZEPALETTE
{
EMR emr;
DWORD ihPal;; Palette handle index
DWORD cEntries;
EMRRESIZEPALETTE, *PEMRRESIZEPALETTE;

tEMRSETPALETTEENTRIES
{
EMR emr;
DWORD ihPal;; Palette handle index
DWORD iStart;
DWORD cEntries;
PALETTEENTRY aPalEntries[1];; The peFlags fields do not contain any flags
EMRSETPALETTEENTRIES, *PEMRSETPALETTEENTRIES;

tEMRSETCOLORADJUSTMENT
{
EMR emr;
COLORADJUSTMENT ColorAdjustment;
EMRSETCOLORADJUSTMENT, *PEMRSETCOLORADJUSTMENT;

tEMRGDICOMMENT
{
EMR emr;
DWORD cbData; ; Size of data in bytes
BYTEData[1];
EMRGDICOMMENT, *PEMRGDICOMMENT;

tEMREOF
{
EMR emr;
DWORD nPalEntries;; Number of palette entries
DWORD offPalEntries;; Offset to the palette entries
DWORD nSizeLast;; Same as nSize and must be the last DWORD
; of the record.The palette entries,
; if exist, precede this field.
EMREOF, *PEMREOF;

tEMRLINETO
{
EMR emr;
POINTLptl;
EMRLINETO, *PEMRLINETO,
EMRMOVETOEX, *PEMRMOVETOEX;

tEMROFFSETCLIPRGN
{
EMR emr;
POINTLptlOffset;
EMROFFSETCLIPRGN, *PEMROFFSETCLIPRGN;

tEMRFILLPATH
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
EMRFILLPATH,*PEMRFILLPATH,
EMRSTROKEANDFILLPATH, *PEMRSTROKEANDFILLPATH,
EMRSTROKEPATH,*PEMRSTROKEPATH;

tEMREXCLUDECLIPRECT
{
EMR emr;
RECTL rclClip;
EMREXCLUDECLIPRECT, *PEMREXCLUDECLIPRECT,
EMRINTERSECTCLIPRECT, *PEMRINTERSECTCLIPRECT;

tEMRSETVIEWPORTORGEX
{
EMR emr;
POINTLptlOrigin;
EMRSETVIEWPORTORGEX, *PEMRSETVIEWPORTORGEX,
EMRSETWINDOWORGEX, *PEMRSETWINDOWORGEX,
EMRSETBRUSHORGEX,*PEMRSETBRUSHORGEX;

tEMRSETVIEWPORTEXTEX
{
EMR emr;
SIZEL szlExtent;
EMRSETVIEWPORTEXTEX, *PEMRSETVIEWPORTEXTEX,
EMRSETWINDOWEXTEX, *PEMRSETWINDOWEXTEX;

tEMRSCALEVIEWPORTEXTEX
{
EMR emr;
LONGxNum;
LONGxDenom;
LONGyNum;
LONGyDenom;
EMRSCALEVIEWPORTEXTEX, *PEMRSCALEVIEWPORTEXTEX,
EMRSCALEWINDOWEXTEX, *PEMRSCALEWINDOWEXTEX;

tEMRSETWORLDTRANSFORM
{
EMR emr;
XFORM xform;
EMRSETWORLDTRANSFORM, *PEMRSETWORLDTRANSFORM;

tEMRMODIFYWORLDTRANSFORM
{
EMR emr;
XFORM xform;
DWORD iMode;
EMRMODIFYWORLDTRANSFORM, *PEMRMODIFYWORLDTRANSFORM;

tEMRSETPIXELV
{
EMR emr;
POINTLptlPixel;
COLORREF crColor;
EMRSETPIXELV, *PEMRSETPIXELV;

tEMREXTFLOODFILL
{
EMR emr;
POINTLptlStart;
COLORREF crColor;
DWORD iMode;
EMREXTFLOODFILL, *PEMREXTFLOODFILL;

tEMRELLIPSE
{
EMR emr;
RECTL rclBox; ; Inclusive-inclusive bounding rectangle
EMRELLIPSE,*PEMRELLIPSE,
EMRRECTANGLE, *PEMRRECTANGLE;

tEMRROUNDRECT
{
EMR emr;
RECTL rclBox; ; Inclusive-inclusive bounding rectangle
SIZEL szlCorner;
EMRROUNDRECT, *PEMRROUNDRECT;

tEMRARC
{
EMR emr;
RECTL rclBox; ; Inclusive-inclusive bounding rectangle
POINTLptlStart;
POINTLptlEnd;
EMRARC, *PEMRARC,
EMRARCTO, *PEMRARCTO,
EMRCHORD, *PEMRCHORD,
EMRPIE, *PEMRPIE;

tEMRANGLEARC
{
EMR emr;
POINTLptlCenter;
DWORD nRadius;
FLOAT eStartAngle;
FLOAT eSweepAngle;
EMRANGLEARC, *PEMRANGLEARC;

tEMRPOLYLINE
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cptl;
POINTLaptl[1];
EMRPOLYLINE, *PEMRPOLYLINE,
EMRPOLYBEZIER, *PEMRPOLYBEZIER,
EMRPOLYGON,*PEMRPOLYGON,
EMRPOLYBEZIERTO, *PEMRPOLYBEZIERTO,
EMRPOLYLINETO, *PEMRPOLYLINETO;

tEMRPOLYLINE16
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cpts;
POINTSapts[1];
EMRPOLYLINE16, *PEMRPOLYLINE16,
EMRPOLYBEZIER16, *PEMRPOLYBEZIER16,
EMRPOLYGON16,*PEMRPOLYGON16,
EMRPOLYBEZIERTO16, *PEMRPOLYBEZIERTO16,
EMRPOLYLINETO16, *PEMRPOLYLINETO16;

tEMRPOLYDRAW
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cptl; ; Number of points
POINTLaptl[1];; Array of points
BYTEabTypes[1]; ; Array of point types
EMRPOLYDRAW, *PEMRPOLYDRAW;

tEMRPOLYDRAW16
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cpts; ; Number of points
POINTSapts[1];; Array of points
BYTEabTypes[1]; ; Array of point types
EMRPOLYDRAW16, *PEMRPOLYDRAW16;

tEMRPOLYPOLYLINE
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD nPolys; ; Number of polys
DWORD cptl; ; Total number of points in all polys
DWORD aPolyCounts[1]; ; Array of point counts for each poly
POINTLaptl[1];; Array of points
EMRPOLYPOLYLINE, *PEMRPOLYPOLYLINE,
EMRPOLYPOLYGON,*PEMRPOLYPOLYGON;

tEMRPOLYPOLYLINE16
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD nPolys; ; Number of polys
DWORD cpts; ; Total number of points in all polys
DWORD aPolyCounts[1]; ; Array of point counts for each poly
POINTSapts[1];; Array of points
EMRPOLYPOLYLINE16, *PEMRPOLYPOLYLINE16,
EMRPOLYPOLYGON16,*PEMRPOLYPOLYGON16;

tEMRINVERTRGN
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cbRgnData;; Size of region data in bytes
BYTERgnData[1];
EMRINVERTRGN, *PEMRINVERTRGN,
EMRPAINTRGN,*PEMRPAINTRGN;

tEMRFILLRGN
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cbRgnData;; Size of region data in bytes
DWORD ihBrush;; Brush handle index
BYTERgnData[1];
EMRFILLRGN, *PEMRFILLRGN;

tEMRFRAMERGN
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD cbRgnData;; Size of region data in bytes
DWORD ihBrush;; Brush handle index
SIZEL szlStroke;
BYTERgnData[1];
EMRFRAMERGN, *PEMRFRAMERGN;

tEMREXTSELECTCLIPRGN
{
EMR emr;
DWORD cbRgnData;; Size of region data in bytes
DWORD iMode;
BYTERgnData[1];
EMREXTSELECTCLIPRGN, *PEMREXTSELECTCLIPRGN;

tEMREXTTEXTOUTA
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD iGraphicsMode;; Current graphics mode
FLOAT exScale;; X and Y scales from Page units to .01mm units
FLOAT eyScale;; if graphics mode is GM_COMPATIBLE.
EMRTEXT emrtext;; This is followed by the string and spacing
; array
EMREXTTEXTOUTA, *PEMREXTTEXTOUTA,
EMREXTTEXTOUTW, *PEMREXTTEXTOUTW;

tEMRPOLYTEXTOUTA
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
DWORD iGraphicsMode;; Current graphics mode
FLOAT exScale;; X and Y scales from Page units to .01mm units
FLOAT eyScale;; if graphics mode is GM_COMPATIBLE.
LONGcStrings;
EMRTEXT aemrtext[1];; Array of EMRTEXT structures.This is
; followed by the strings and spacing arrays.
EMRPOLYTEXTOUTA, *PEMRPOLYTEXTOUTA,
EMRPOLYTEXTOUTW, *PEMRPOLYTEXTOUTW;

tEMRBITBLT
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
LONGxDest;
LONGyDest;
LONGcxDest;
LONGcyDest;
DWORD dwRop;
LONGxSrc;
LONGySrc;
XFORM xformSrc; ; Source DC transform
COLORREF crBkColorSrc;; Source DC BkColor in RGB
DWORD iUsageSrc;; Source bitmap info color table usage
; (DIB_RGB_COLORS)
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
EMRBITBLT		ENDS

tEMRSTRETCHBLT
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
LONGxDest;
LONGyDest;
LONGcxDest;
LONGcyDest;
DWORD dwRop;
LONGxSrc;
LONGySrc;
XFORM xformSrc; ; Source DC transform
COLORREF crBkColorSrc;; Source DC BkColor in RGB
DWORD iUsageSrc;; Source bitmap info color table usage
; (DIB_RGB_COLORS)
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
LONGcxSrc;
LONGcySrc;
EMRSTRETCHBLT		ENDS

tEMRMASKBLT
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
LONGxDest;
LONGyDest;
LONGcxDest;
LONGcyDest;
DWORD dwRop;
LONGxSrc;
LONGySrc;
XFORM xformSrc; ; Source DC transform
COLORREF crBkColorSrc;; Source DC BkColor in RGB
DWORD iUsageSrc;; Source bitmap info color table usage
; (DIB_RGB_COLORS)
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
LONGxMask;
LONGyMask;
DWORD iUsageMask; ; Mask bitmap info color table usage
DWORD offBmiMask; ; Offset to the mask BITMAPINFO structure if any
DWORD cbBmiMask;; Size of the mask BITMAPINFO structure if any
DWORD offBitsMask;; Offset to the mask bitmap bits if any
DWORD cbBitsMask; ; Size of the mask bitmap bits if any
EMRMASKBLT		ENDS

tEMRPLGBLT
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
POINTLaptlDest[3];
LONGxSrc;
LONGySrc;
LONGcxSrc;
LONGcySrc;
XFORM xformSrc; ; Source DC transform
COLORREF crBkColorSrc;; Source DC BkColor in RGB
DWORD iUsageSrc;; Source bitmap info color table usage
; (DIB_RGB_COLORS)
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
LONGxMask;
LONGyMask;
DWORD iUsageMask; ; Mask bitmap info color table usage
DWORD offBmiMask; ; Offset to the mask BITMAPINFO structure if any
DWORD cbBmiMask;; Size of the mask BITMAPINFO structure if any
DWORD offBitsMask;; Offset to the mask bitmap bits if any
DWORD cbBitsMask; ; Size of the mask bitmap bits if any
EMRPLGBLT		ENDS

tEMRSETDIBITSTODEVICE
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
LONGxDest;
LONGyDest;
LONGxSrc;
LONGySrc;
LONGcxSrc;
LONGcySrc;
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
DWORD iUsageSrc;; Source bitmap info color table usage
DWORD iStartScan;
DWORD cScans;
EMRSETDIBITSTODEVICE		ENDS

tEMRSTRETCHDIBITS
{
EMR emr;
RECTL rclBounds;; Inclusive-inclusive bounds in device units
LONGxDest;
LONGyDest;
LONGxSrc;
LONGySrc;
LONGcxSrc;
LONGcySrc;
DWORD offBmiSrc;; Offset to the source BITMAPINFO structure
DWORD cbBmiSrc; ; Size of the source BITMAPINFO structure
DWORD offBitsSrc; ; Offset to the source bitmap bits
DWORD cbBitsSrc;; Size of the source bitmap bits
DWORD iUsageSrc;; Source bitmap info color table usage
DWORD dwRop;
LONGcxDest;
LONGcyDest;
EMRSTRETCHDIBITS		ENDS

tEMREXTCREATEFONTINDIRECTW
{
EMR emr;
DWORD ihFont; ; Font handle index
EXTLOGFONTW elfw;
EMREXTCREATEFONTINDIRECTW		ENDS

tEMRCREATEPALETTE
{
EMR emr;
DWORD ihPal;; Palette handle index
LOGPALETTE lgpl;; The peFlags fields in the palette entries
; do not contain any flags
EMRCREATEPALETTE		ENDS


tEMRCREATECOLORSPACE
{
EMR emr;
DWORD ihCS; ; ColorSpace handle index
LOGCOLORSPACEWlcs;
EMRCREATECOLORSPACE		ENDS

tEMRCREATEPEN
{
EMR emr;
DWORD ihPen;; Pen handle index
LOGPENlopn;
EMRCREATEPEN		ENDS

tEMREXTCREATEPEN
{
EMR emr;
DWORD ihPen;; Pen handle index
DWORD offBmi; ; Offset to the BITMAPINFO structure if any
DWORD cbBmi;; Size of the BITMAPINFO structure if any
; The bitmap info is followed by the bitmap
; bits to form a packed DIB.
DWORD offBits;; Offset to the brush bitmap bits if any
DWORD cbBits; ; Size of the brush bitmap bits if any
EXTLOGPEN elp;; The extended pen with the style array.
EMREXTCREATEPEN	ENDS

tEMRCREATEBRUSHINDIRECT
{
EMR emr;
DWORD ihBrush;; Brush handle index
LOGBRUSH lb;; The style must be BS_SOLID, BS_HOLLOW,
; BS_NULL or BS_HATCHED.
EMRCREATEBRUSHINDIRECT		ENDS

tEMRCREATEMONOBRUSH
{
EMR emr;
DWORD ihBrush;; Brush handle index
DWORD iUsage; ; Bitmap info color table usage
DWORD offBmi; ; Offset to the BITMAPINFO structure
DWORD cbBmi;; Size of the BITMAPINFO structure
DWORD offBits;; Offset to the bitmap bits
DWORD cbBits; ; Size of the bitmap bits
EMRCREATEMONOBRUSH		ENDS

tEMRCREATEDIBPATTERNBRUSHPT
{
EMR emr;
DWORD ihBrush;; Brush handle index
DWORD iUsage; ; Bitmap info color table usage
DWORD offBmi; ; Offset to the BITMAPINFO structure
DWORD cbBmi;; Size of the BITMAPINFO structure
; The bitmap info is followed by the bitmap
; bits to form a packed DIB.
DWORD offBits;; Offset to the bitmap bits
DWORD cbBits; ; Size of the bitmap bits
EMRCREATEDIBPATTERNBRUSHPT		ENDS

tEMRFORMAT
{
DWORD dSignature; ; Format signature, e.g. ENHMETA_SIGNATURE.
DWORD nVersion; ; Format version number.
DWORD cbData; ; Size of data in bytes.
DWORD offData;; Offset to data from GDICOMMENT_IDENTIFIER.
; It must begin at a DWORD offset.
EMRFORMAT		ENDS

tEMRGLSRECORD
{
EMR emr;
DWORD cbData; ; Size of data in bytes
BYTEData[1];
EMRGLSRECORD		ENDS

tEMRGLSBOUNDEDRECORD
{
EMR emr;
RECTL rclBounds;; Bounds in recording coordinates
DWORD cbData; ; Size of data in bytes
BYTEData[1];
EMRGLSBOUNDEDRECORD		ENDS

tEMRPIXELFORMAT
{
EMR emr;
PIXELFORMATDESCRIPTOR pfd;
EMRPIXELFORMAT		ENDS

GDICOMMENT_IDENTIFIER 	= 43494447h
GDICOMMENT_WINDOWS_METAFILE = 80000001h
GDICOMMENT_BEGINGROUP 	= 00000002h
GDICOMMENT_ENDGROUP 	= 00000003h
GDICOMMENT_MULTIFORMATS 	= 40000004h
EPS_SIGNATURE 		= 46535045h


; OpenGL wgl prototypes

POINTFLOAT	STRUC
 pf_x	FLOAT	<?>
 pf_y	FLOAT	<?>
POINTFLOAT	ENDS


GLYPHMETRICSFLOAT	STRUC
FLOAT gmfBlackBoxX	FLOAT	<?>
FLOAT gmfBlackBoxY	FLOAT	<?>
POINTFLOATgmfptGlyphOrigin	POINTFLOAT	<?>
FLOAT gmfCellIncX	FLOAT	<?>
FLOAT gmfCellIncY	FLOAT	<?>
GLYPHMETRICSFLOAT	ENDS

WGL_FONT_LINES		= 0
WGL_FONT_POLYGONS	= 1

; Layer plane descriptor 
LAYERPLANEDESCRIPTOR	STRUC
 lpd_nSize		dw	?
 lpd_nVersion		dw	?
 lpd_dwFlags		dd	?
 lpd_iPixelType		db	?
 lpd_cColorBits		db	?
 lpd_cRedBits		db	?
 lpd_cRedShift		db	?
 lpd_cGreenBits		db	?
 lpd_cGreenShift		db	?
 lpd_cBlueBits		db	?
 lpd_cBlueShift		db	?
 lpd_cAlphaBits		db	?
 lpd_cAlphaShift		db	?
 lpd_cAccumBits		db	?
 lpd_cAccumRedBits		db	?
 lpd_cAccumGreenBits	db	?
 lpd_cAccumBlueBits	db	?
 lpd_cAccumAlphaBits	db	?
 lpd_cDepthBits		db	?
 lpd_cStencilBits		db	?
 lpd_cAuxBuffers		db	?
 lpd_iLayerPlane		db	?
 lpd_bReserved		db	?
 lpd_crTransparent		COLORREF	<?>
LAYERPLANEDESCRIPTOR	ENDS

; LAYERPLANEDESCRIPTOR flags 
LPD_DOUBLEBUFFER	= 00000001h
LPD_STEREO		= 00000002h
LPD_SUPPORT_GDI 	= 00000010h
LPD_SUPPORT_OPENGL	= 00000020h
LPD_SHARE_DEPTH 	= 00000040h
LPD_SHARE_STENCIL 	= 00000080h
LPD_SHARE_ACCUM 	= 00000100h
LPD_SWAP_EXCHANGE 	= 00000200h
LPD_SWAP_COPY 		= 00000400h
LPD_TRANSPARENT 	= 00001000h

LPD_TYPE_RGBA		= 0
LPD_TYPE_COLORINDEX	= 1

; wglSwapLayerBuffers flags 
WGL_SWAP_MAIN_PLANE 	= 00000001h
WGL_SWAP_OVERLAY1 	= 00000002h
WGL_SWAP_OVERLAY2 	= 00000004h
WGL_SWAP_OVERLAY3 	= 00000008h
WGL_SWAP_OVERLAY4 	= 00000010h
WGL_SWAP_OVERLAY5 	= 00000020h
WGL_SWAP_OVERLAY6 	= 00000040h
WGL_SWAP_OVERLAY7 	= 00000080h
WGL_SWAP_OVERLAY8 	= 00000100h
WGL_SWAP_OVERLAY9 	= 00000200h
WGL_SWAP_OVERLAY10	= 00000400h
WGL_SWAP_OVERLAY11	= 00000800h
WGL_SWAP_OVERLAY12	= 00001000h
WGL_SWAP_OVERLAY13	= 00002000h
WGL_SWAP_OVERLAY14	= 00004000h
WGL_SWAP_OVERLAY15	= 00008000h
WGL_SWAP_UNDERLAY1	= 00010000h
WGL_SWAP_UNDERLAY2	= 00020000h
WGL_SWAP_UNDERLAY3	= 00040000h
WGL_SWAP_UNDERLAY4	= 00080000h
WGL_SWAP_UNDERLAY5	= 00100000h
WGL_SWAP_UNDERLAY6	= 00200000h
WGL_SWAP_UNDERLAY7	= 00400000h
WGL_SWAP_UNDERLAY8	= 00800000h
WGL_SWAP_UNDERLAY9	= 01000000h
WGL_SWAP_UNDERLAY10 	= 02000000h
WGL_SWAP_UNDERLAY11 	= 04000000h
WGL_SWAP_UNDERLAY12 	= 08000000h
WGL_SWAP_UNDERLAY13 	= 10000000h
WGL_SWAP_UNDERLAY14 	= 20000000h
WGL_SWAP_UNDERLAY15 	= 40000000h

-#
