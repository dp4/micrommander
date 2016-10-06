
	IFDEF	UNICODE

ChooseColor	equ	ChooseColorW
ChooseFont	equ	ChooseFontW

CHOOSE_FONT	equ	CHOOSE_FONTW

	ELSE

ChooseColor	equ	ChooseColorA
ChooseFont	equ	ChooseFontA

CHOOSE_FONT	equ	CHOOSE_FONTA

	ENDIF

ChooseColorA	proto	:QWORD
ChooseColorW	proto	:QWORD
ChooseFontA	proto	:QWORD
ChooseFontW	proto	:QWORD


PSD_DEFAULTMINMARGINS 	= 00000000h
PSD_INWININIINTLMEASURE 	= 00000000h
PSD_MINMARGINS		= 00000001h
PSD_MARGINS 		= 00000002h
PSD_INTHOUSANDTHSOFINCHES 	= 00000004h
PSD_INHUNDREDTHSOFMILLIMETERS	= 00000008h
PSD_DISABLEMARGINS	= 00000010h
PSD_DISABLEPRINTER	= 00000020h
PSD_NOWARNING 		= 00000080h
PSD_DISABLEORIENTATION	= 00000100h
PSD_DISABLEPAPER		= 00000200h
PSD_RETURNDEFAULT	= 00000400h
PSD_SHOWHELP		= 00000800h
PSD_ENABLEPAGESETUPHOOK 	= 00002000h
PSD_ENABLEPAGESETUPTEMPLATE	= 00008000h
PSD_ENABLEPAGESETUPTEMPLATEHANDLE	= 00020000h
PSD_ENABLEPAGEPAINTHOOK		= 00040000h
PSD_DISABLEPAGEPAINTING		= 00080000h
PSD_NONETWORKBUTTON			= 00200000h

PD_ALLPAGES= 00000000h
PD_SELECTION = 00000001h
PD_PAGENUMS= 00000002h
PD_NOSELECTION = 00000004h
PD_NOPAGENUMS= 00000008h
PD_COLLATE = 00000010h
PD_PRINTTOFILE = 00000020h
PD_PRINTSETUP= 00000040h
PD_NOWARNING = 00000080h
PD_RETURNDC= 00000100h
PD_RETURNIC= 00000200h
PD_RETURNDEFAULT = 00000400h
PD_SHOWHELP= 00000800h
PD_ENABLEPRINTHOOK = 00001000h
PD_ENABLESETUPHOOK = 00002000h
PD_ENABLEPRINTTEMPLATE = 00004000h
PD_ENABLESETUPTEMPLATE = 00008000h
PD_ENABLEPRINTTEMPLATEHANDLE = 00010000h
PD_ENABLESETUPTEMPLATEHANDLE = 00020000h
PD_USEDEVMODECOPIES= 00040000h
PD_USEDEVMODECOPIESANDCOLLATE = 00040000h
PD_DISABLEPRINTTOFILE= 00080000h
PD_HIDEPRINTTOFILE = 00100000h
PD_NONETWORKBUTTON = 00200000h
PD_CURRENTPAGE		equ	00400000h
PD_NOCURRENTPAGE	equ	00800000h
PD_EXCLUSIONFLAGS	equ	01000000h
PD_USELARGETEMPLATE	equ	10000000h
PD_EXCL_COPIESANDCOLLATE	equ	(DM_COPIES OR DM_COLLATE)


; Define the start page for the print dialog when using PrintDlgEx.

START_PAGE_GENERAL	equ	-1


; Result action ids for PrintDlgEx.

PD_RESULT_CANCEL	equ	0
PD_RESULT_PRINT		equ	1
PD_RESULT_APPLY		equ	2

CC_RGBINIT		= 00000001h
CC_FULLOPEN		= 00000002h
CC_PREVENTFULLOPEN	= 00000004h
CC_SHOWHELP		= 00000008h
CC_ENABLEHOOK		= 00000010h
CC_ENABLETEMPLATE	= 00000020h
CC_ENABLETEMPLATEHANDLE	= 00000040h
CC_SOLIDCOLOR		= 00000080h
CC_ANYCOLOR		= 00000100h


FR_DOWN		= 00001h
FR_WHOLEWORD		= 00002h
FR_MATCHCASE		= 00004h
FR_FINDNEXT		= 00008h
FR_REPLACE		= 00010h
FR_REPLACEALL		= 00020h
FR_DIALOGTERM		= 00040h
FR_SHOWHELP		= 00080h
FR_ENABLEHOOK		= 00100h
FR_ENABLETEMPLATE	= 00200h
FR_NOUPDOWN		= 00400h
FR_NOMATCHCASE	= 00800h
FR_NOWHOLEWORD	= 01000h
FR_ENABLETEMPLATEHANDLE	= 02000h
FR_HIDEUPDOWN 		= 04000h
FR_HIDEMATCHCASE	= 08000h
FR_HIDEWHOLEWORD	= 10000h


CF_SCREENFONTS		= 00001h
CF_PRINTERFONTS	= 00002h
CF_BOTH		= CF_SCREENFONTS + CF_PRINTERFONTS
CF_SHOWHELP		= 00004h
CF_ENABLEHOOK		= 00008h
CF_ENABLETEMPLATE	= 00010h
CF_ENABLETEMPLATEHANDLE	= 00020h
CF_INITTOLOGFONTSTRUCT	= 00040h
CF_USESTYLE		= 00080h
CF_EFFECTS		= 00100h
CF_APPLY		= 00200h
CF_ANSIONLY		= 00400h
CF_SCRIPTSONLY		= CF_ANSIONLY		; if WIN 4.0
CF_NOVECTORFONTS	= 00800h
CF_NOOEMFONTS		= CF_NOVECTORFONTS
CF_NOSIMULATIONS	= 01000h
CF_LIMITSIZE		= 02000h
CF_FIXEDPITCHONLY	= 04000h
CF_WYSIWYG		= 08000h 	; must also have CF_SCREENFONTS & CF_PRINTERFONTS
CF_FORCEFONTEXIST	= 10000h
CF_SCALABLEONLY	= 20000h
CF_TTONLY		= 40000h
CF_NOFACESEL		= 80000h
CF_NOSTYLESEL		= 0100000h
CF_NOSIZESEL		= 0200000h

CF_SELECTSCRIPT		= 0400000h		; ab WIN 4.0
CF_NOSCRIPTSEL		= 0800000h
CF_NOVERTFONTS		= 1000000h

; these are extra nFontType bits that are added to what is returned to the EnumFonts callback routine

SIMULATED_FONTTYPE	= 8000h
PRINTER_FONTTYPE	= 4000h
SCREEN_FONTTYPE	= 2000h
BOLD_FONTTYPE		= 100h
ITALIC_FONTTYPE		= 200h
REGULAR_FONTTYPE	= 400h

WM_CHOOSEFONT_GETLOGFONT	= WM_USER + 1


OFN_READONLY		= 00000001h
OFN_OVERWRITEPROMPT = 00000002h
OFN_HIDEREADONLY	= 00000004h
OFN_NOCHANGEDIR 	= 00000008h
OFN_SHOWHELP		= 00000010h
OFN_ENABLEHOOK	= 00000020h
OFN_ENABLETEMPLATE	= 00000040h
OFN_ENABLETEMPLATEHANDLE	= 00000080h
OFN_NOVALIDATE	= 00000100h
OFN_ALLOWMULTISELECT= 00000200h
OFN_EXTENSIONDIFFERENT	= 00000400h
OFN_PATHMUSTEXIST 	= 00000800h
OFN_FILEMUSTEXIST 	= 00001000h
OFN_CREATEPROMPT	= 00002000h
OFN_SHAREAWARE	= 00004000h
OFN_NOREADONLYRETURN	= 00008000h
OFN_NOTESTFILECREATE	= 00010000h
OFN_NONETWORKBUTTON 	= 00020000h
OFN_NOLONGNAMES 	= 00040000h
OFN_EXPLORER		= 00080000h
OFN_NODEREFERENCELINKS	= 00100000h
OFN_LONGNAMES 	= 00200000h
OFN_SHAREFALLTHROUGH	= 2
OFN_SHARENOWARN 	= 1
OFN_SHAREWARN 	= 0

CHOOSE_COLOR	struc
 lStructSize	dd	?
 	dd	?
 hwndOwner	dq	?
 hInstance	dq	?
 rgbResult	dd	?
 	dd	?
 lpCustColors	dq	?
 Flags	dd	?
 	dd	?
 lCustData	dq	?
 lpfnHook	dq	?
 lpTemplateName	dq	?
CHOOSE_COLOR	ends

CHOOSE_FONTA	struc
 lStructSize	dd	?
 	dd	?
 hwndOwner	dq	?	; caller's window handle
 hDC	dq	?	; printer DC/IC or NULL
 lpLogFont	dq	?	; ptr. to a LOGFONT struct
 iPointSize	dd	?	; 10 * size in points of selected font
 Flags	dd	?	; enum. type flags
 rgbColors	dd	?	; returned text color
 	dd	?
 lCustData	dq	?	; data passed to hook fn.
 lpfnHook	dq	?	; ptr. to hook function
 lpTemplateName	dq	?	; custom template name
 hInstance	dq	?	; instance handle of.EXE that contains cust. dlg. template
 lpszStyle	dq	?	; return the style field here must be LF_FACESIZE or bigger
 nFontType	dw	?	; same value reported to the EnumFonts call back with the extra FONTTYPE_ bits added
 	dw	?
 nSizeMin	dd	?	; minimum pt size allowed &
 nSizeMax	dd	?	; max pt size allowed if CF_LIMITSIZE is used
 	dd	?
CHOOSE_FONTA	ends

CHOOSE_FONTW	struc
 lStructSize	dd	?
 	dd	?
 hwndOwner	dq	?	; caller's window handle
 hDC	dq	?	; printer DC/IC or NULL
 lpLogFont	dq	?	; ptr. to a LOGFONT struct
 iPointSize	dd	?	; 10 * size in points of selected font
 Flags	dd	?	; enum. type flags
 rgbColors	dd	?	; returned text color
 	dd	?
 lCustData	dq	?	; data passed to hook fn.
 lpfnHook	dq	?	; ptr. to hook function
 lpTemplateName	dq	?	; custom template name
 hInstance	dq	?	; instance handle of.EXE that contains cust. dlg. template
 lpszStyle	dq	?	; return the style field here must be LF_FACESIZE or bigger
 nFontType	dw	?	; same value reported to the EnumFonts call back with the extra FONTTYPE_ bits added
 	dw	?
 nSizeMin	dd	?	; minimum pt size allowed &
 nSizeMax	dd	?	; max pt size allowed if CF_LIMITSIZE is used
 	dd	?
CHOOSE_FONTW	ends

comment #

; IPrintDialogServices

ipds_QueryInterface	equ	0
ipds_AddRef		equ	4
ipds_Release		equ	8
ipds_GetCurrentDevMode	equ	12
ipds_GetCurrentPrinterName	equ	16
ipds_GetCurrentPortName	equ	20

; Page Range structure for PrintDlgEx.

PRINTPAGERANGE		struc
 ppr_nFromPage		dd	?
 ppr_nToPage		dd	?
PRINTPAGERANGE		ends

; PrintDlgEx structure.

PRINTDLGEXA		struc
 prde_lStructSize		dd	?		;  size of structure in bytes
 prde_hwndOwner		dd	?		;  caller's window handle
 prde_hDevMode		dd	?		;  handle to DevMode
 prde_hDevNames		dd	?		;  handle to DevNames
 prde_hDC		dd	?		;  printer DC/IC or NULL
 prde_Flags		dd	?		;  PD_ flags
 prde_Flags2		dd	?		;  reserved
 prde_ExclusionFlags	dd	?		;  items to exclude from driver pages
 prde_nPageRanges	dd	?		;  number of page ranges
 prde_nMaxPageRanges	dd	?		;  max number of page ranges
 prde_lpPageRanges	dd	?		;  array of page ranges
 prde_nMinPage		dd	?		;  min page number
 prde_nMaxPage		dd	?		;  max page number
 prde_nCopies		dd	?		;  number of copies
 prde_hInstance		dd	?		;  instance handle
 prde_lpPrintTemplateName	dd	?		;  template name for app specific area
 prde_lpCallback		dd	?		;  app callback interface
 prde_nPropertyPages	dd	?		;  number of app property pages in lphPropertyPages
 prde_lphPropertyPages	dd	?		;  array of app property page handles
 prde_nStartPage		dd	?		;  start page id
 prde_dwResultAction	dd	?		;  result action if S_OK is returned
PRINTDLGEXA		ends

PRINTDIALOG		STRUC
 prd_lStructSize		dd	?
 prd_hwndOwner		HWND	?
 prd_hDevMode		HGLOBAL	?
 prd_hDevNames		HGLOBAL	?
 prd_hDC		HDC	?
 prd_Flags		dd	?
 prd_nFromPage		dw	?
 prd_nToPage		dw	?
 prd_nMinPage		dw	?
 prd_nMaxPage		dw	?
 prd_nCopies		dw	?
 prd_hInstance		HINSTANCE	?
 prd_lCustData		dd	?
 prd_lpfnPrintHook		dd	?
 prd_lpfnSetupHook	dd	?
 prd_lpPrintTemplateName	dd	?
 prd_lpSetupTemplateName	dd	?
 prd_hPrintTemplate	HGLOBAL	?
 prd_hSetupTemplate	HGLOBAL	?
PRINTDIALOG		ENDS

DEVNAMES		STRUC
 wDriverOffset	dw	?
 wDeviceOffset	dw	?
 wOutputOffset	dw	?
 wDefault	dw	?
DEVNAMES		ENDS

; VERY IMPORTANT:
; double and more definitions of labels in structures
; use instead Flags -> ofn_Flagshint: ofn_ als structure identifier


OPENFILENAMESIZE		equ 76	; use sizeof(OPENFILENAME)

OPENFILENAME		STRUC
 ofn_lStructSize		dd	sizeof OPENFILENAME
 ofn_hwndOwner		HWND	?
 ofn_hInstance		HINSTANCE	?
 ofn_lpstrFilter		dd	?
 ofn_lpstrCustomFilter	dd	?
 ofn_nMaxCustFilter	dd	?
 ofn_nFilterIndex		dd	?
 ofn_lpstrFile		dd	?
 ofn_nMaxFile		dd	?
 ofn_lpstrFileTitle		dd	?
 ofn_nMaxFileTitle		dd	?
 ofn_lpstrInitialDir		dd	?
 ofn_lpstrTitle		dd	?
 ofn_Flags		dd	?
 ofn_nFileOffset		dw	?
 ofn_nFileExtension		dw	?
 ofn_lpstrDefExt		dd	?
 ofn_lCustData		dd	?
 ofn_lpfnHook		dd	?
 ofn_lpTemplateName	dd	?
OPENFILENAME		ENDS


FINDREPLACE		STRUC
fr_lStructSize		dd	?
fr_hwndOwner		HWND	?
fr_hInstance		HINSTANCE	?
fr_Flags		dd	?
fr_lpstrFindWhat		dd	?
fr_lpstrReplaceWith	dd	?
fr_wFindWhatLen		dw	?
fr_wReplaceWithLen	dw	?
fr_lCustData		dd	?
fr_lpfnHook		dd	?
fr_lpTemplateName		dd	?
FINDREPLACE		ENDS

PageSetupDlg	equ	PageSetupDlgA

PAGESETUPDIALOG	STRUC
  psd_lStructSize		dd	?
  psd_hwndOwner		HWND	?
  psd_hDevMode		HGLOBAL	?
  psd_hDevNames		HGLOBAL	?
  psd_Flags		dd	?
  psd_ptPaperSize		dd	?, ?
  psd_rtMinMargin		dd	?, ?, ?, ?
  psd_rtMargin		RECT	<?>
  psd_hInstance		HINSTANCE	?
  psd_lCustData		dd	?
  psd_lpfnPageSetupHook	dd	?
  psd_lpfnPagePaintHook	dd	?
  psd_lpPageSetupTemplateName	dd	?
  psd_hPageSetupTemplate	HGLOBAL	?
PAGESETUPDIALOG	ENDS

-#
