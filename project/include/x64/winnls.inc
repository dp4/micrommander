;**************************************************************************
;
; winnls.h -- NLS procedure declarations, constant definitions and macros
;
; Copyright (c) 1991-1996, Microsoft Corp. All rights reserved.
;
;**************************************************************************

	IFDEF	UNICODE

GetDateFormat	equ	GetDateFormatW
GetTimeFormat	equ	GetTimeFormatW

	ELSE

GetDateFormat	equ	GetDateFormatA
GetTimeFormat	equ	GetTimeFormatA

	ENDIF

GetDateFormatA	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD
GetDateFormatW	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD

; Constants - Define all constants for the NLS component here.

; String Length Maximums.

MAX_LEADBYTES		= 12	; 5 ranges, 2 bytes ea., 0 term. 
MAX_DEFAULTCHAR	= 2	; single or double byte 

; MBCS and Unicode Translation Flags.
 
MB_PRECOMPOSED 	equ 00000001h	; use precomposed chars 
MB_COMPOSITE 		equ 00000002h	; use composite chars 
MB_USEGLYPHCHARS 	equ 00000004h	; use glyph chars, not ctrl chars 
MB_ERR_INVALID_CHARS 	equ 00000008h	; error for invalid chars 

WC_DEFAULTCHECK	equ 00000100h	; check for default char 
WC_COMPOSITECHECK	equ 00000200h	; convert composite to precomposed 
WC_DISCARDNS 		equ 00000010h	; discard non-spacing chars 
WC_SEPCHARS		equ 00000020h	; generate separate chars 
WC_DEFAULTCHAR 	equ 00000040h	; replace w; default char 

; Character Type Flags.
 
CT_CTYPE1		equ 00000001h	; ctype 1 information 
CT_CTYPE2		equ 00000002h	; ctype 2 information 
CT_CTYPE3		equ 00000004h	; ctype 3 information 

; CType 1 Flag Bits.
 
C1_UPPER 		equ 0001h	; upper case 
C1_LOWER 		equ 0002h	; lower case 
C1_DIGIT 		equ 0004h	; decimal digits 
C1_SPACE 		equ 0008h	; spacing characters 
C1_PUNCT 		equ 0010h	; punctuation characters 
C1_CNTRL 		equ 0020h	; control characters 
C1_BLANK 		equ 0040h	; blank characters 
C1_XDIGIT		equ 0080h	; other digits 
C1_ALPHA 		equ 0100h	; any linguistic character 

; CType 2 Flag Bits.
 
C2_LEFTTORIGHT 		equ 0001h	; left to right 
C2_RIGHTTOLEFT 		equ 0002h	; right to left 
C2_EUROPENUMBER	equ 0003h	; European number, digit 
C2_EUROPESEPARATOR 	equ 0004h	; European numeric separator 
C2_EUROPETERMINATOR	equ 0005h	; European numeric terminator 
C2_ARABICNUMBER		equ 0006h	; Arabic number 
C2_COMMONSEPARATOR 	equ 0007h	; common numeric separator 
C2_BLOCKSEPARATOR	equ 0008h	; block separator 
C2_SEGMENTSEPARATOR	equ 0009h	; segment separator 
C2_WHITESPACE		equ 000Ah	; white space 
C2_OTHERNEUTRAL	equ 000Bh	; other neutrals 
C2_NOTAPPLICABLE 	equ 0000h	; no implicit directionality 

; CType 3 Flag Bits.
 
C3_NONSPACING		equ 0001h	; nonspacing character 
C3_DIACRITIC 		equ 0002h	; diacritic mark 
C3_VOWELMARK 		equ 0004h	; vowel mark 
C3_SYMBOL		equ 0008h	; symbols 
C3_KATAKANA		equ 0010h	; katakana character 
C3_HIRAGANA		equ 0020h	; hiragana character 
C3_HALFWIDTH 		equ 0040h	; half width character 
C3_FULLWIDTH 		equ 0080h	; full width character 
C3_IDEOGRAPH 		equ 0100h	; ideographic character 
C3_KASHIDA 		equ 0200h	; Arabic kashida character 
C3_LEXICAL 		equ 0400h	; lexical character 
C3_ALPHA 		equ 8000h	; any linguistic char (C1_ALPHA) 
C3_NOTAPPLICABLE 	equ 0000h	; ctype 3 is not applicable 

; String Flags.
 
NORM_IGNORECASE 	equ 00000001h	; ignore case 
NORM_IGNORENONSPACE 	equ 00000002h	; ignore nonspacing chars 
NORM_IGNORESYMBOLS	equ 00000004h	; ignore symbols 
NORM_IGNOREKANATYPE 	equ 00010000h	; ignore kanatype 
NORM_IGNOREWIDTH	equ 00020000h	; ignore width 

; Locale Independent Mapping Flags.
 
MAP_FOLDCZONE 		equ 00000010h	; fold compatibility zone chars 
MAP_PRECOMPOSED 	equ 00000020h	; convert to precomposed chars 
MAP_COMPOSITE 		equ 00000040h	; convert to composite chars 
MAP_FOLDDIGITS		equ 00000080h	; all digits to ASCII 0-9 

; Locale Dependent Mapping Flags.
 
LCMAP_LOWERCASE 	equ 00000100h	; lower case letters 
LCMAP_UPPERCASE 	equ 00000200h	; upper case letters 
LCMAP_SORTKEY 		equ 00000400h	; WC sort key (normalize) 
LCMAP_BYTEREV 		equ 00000800h	; byte reversal 
LCMAP_HIRAGANA		equ 00100000h	; map katakana to hiragana 
LCMAP_KATAKANA		equ 00200000h	; map hiragana to katakana 
LCMAP_HALFWIDTH 	equ 00400000h	; map double byte to single byte 
LCMAP_FULLWIDTH 	equ 00800000h	; map single byte to double byte 
LCMAP_LINGUISTIC_CASING 	equ 01000000h	; use linguistic rules for casing 
LCMAP_SIMPLIFIED_CHINESE	equ 02000000h	; map traditional chinese to simplified chinese 
LCMAP_TRADITIONAL_CHINESE 	equ 04000000h	; map simplified chinese to traditional chinese 

; Locale Enumeration Flags.
 
LCID_INSTALLED		equ 00000001h	; installed locale ids 
LCID_SUPPORTED		equ 00000002h	; supported locale ids 

; Code Page Enumeration Flags.
 
CP_INSTALLED		equ 00000001h	; installed code page ids 
CP_SUPPORTED		equ 00000002h	; supported code page ids 

; Sorting Flags.
; WORD Sort:culturally correct sort
; hyphen and apostrophe are special cased
; example: "coop" and "co-op" will sort together in a list
; co_op <-------underscore (symbol)
; coat
; comb
; coop
; co-op <-------hyphen (punctuation)
; cork
; went
; were
; we're <-------apostrophe (punctuation)

; STRING Sort:hyphen and apostrophe will sort with all other symbols
; co-op <-------hyphen (punctuation)
; co_op <-------underscore (symbol)
; coat
; comb
; coop
; cork
; we're <-------apostrophe (punctuation)
; went
; were
 
SORT_STRINGSORT 	equ 00001000h	; use string sort method 

; Code Page Default Values.
 
CP_ACP	= 0	; default to ANSI code page 
CP_OEMCP	= 1	; default to OEMcode page 
CP_MACCP	= 2	; default to MACcode page 

CP_UTF7	= 65000	; UTF-7 translation 
CP_UTF8	= 65001	; UTF-8 translation 

; Country Codes.
 
CTRY_DEFAULT 		equ	0
CTRY_AUSTRALIA		equ	61	; Australia 
CTRY_AUSTRIA		equ	43	; Austria 
CTRY_BELGIUM		equ	32	; Belgium 
CTRY_BRAZIL		equ	55	; Brazil 
CTRY_BULGARIA		equ	359 	; Bulgaria 
CTRY_CANADA		equ	2 	; Canada 
CTRY_CROATIA		equ	385 	; Croatia 
CTRY_CZECH		equ	42	; Czech Republic 
CTRY_DENMARK		equ	45	; Denmark 
CTRY_FINLAND		equ	358 	; Finland 
CTRY_FRANCE		equ	33	; France 
CTRY_GERMANY		equ	49	; Germany 
CTRY_GREECE		equ	30	; Greece 
CTRY_HONG_KONG		equ	852 	; Hong Kong 
CTRY_HUNGARY		equ	36	; Hungary 
CTRY_ICELAND		equ	354 	; Iceland 
CTRY_IRELAND		equ	353 	; Ireland 
CTRY_ITALY		equ	39	; Italy 
CTRY_JAPAN		equ	81	; Japan 
CTRY_MEXICO		equ	52	; Mexico 
CTRY_NETHERLANDS	equ	31	; Netherlands 
CTRY_NEW_ZEALAND	equ	64	; New Zealand 
CTRY_NORWAY		equ	47	; Norway 
CTRY_POLAND		equ	48	; Poland 
CTRY_PORTUGAL		equ	351 	; Portugal 
CTRY_PRCHINA		equ	86	; Peoples' Republic of China 
CTRY_ROMANIA		equ	40	; Romania 
CTRY_RUSSIA		equ	7 	; Russia 
CTRY_SINGAPORE		equ	65	; Singapore 
CTRY_SLOVAK		equ	42	; Slovak Republic 
CTRY_SLOVENIA		equ	386 	; Slovenia 
CTRY_SOUTH_KOREA	equ	82	; South Korea 
CTRY_SPAIN		equ	34	; Spain 
CTRY_SWEDEN		equ	46	; Sweden 
CTRY_SWITZERLAND	equ	41	; Switzerland 
CTRY_TAIWAN		equ	886 	; Taiwan 
CTRY_TURKEY		equ	90	; Turkey 
CTRY_UNITED_KINGDOM	equ	44	; United Kingdom 
CTRY_UNITED_STATES	equ	1 	; United States 

; Locale Types.
; These types are used for the GetLocaleInfoW NLS API routine.
; LOCALE_NOUSEROVERRIDE is also used in GetTimeFormatW and GetDateFormatW.
; LOCALE_USE_CP_ACP is used in many of the A (Ansi) apis that need to do 
; string translation.
 
LOCALE_NOUSEROVERRIDE 	equ 80000000h	; do not use user overrides 
LOCALE_USE_CP_ACP 	equ 40000000h	; use the system ACP 
LOCALE_ILANGUAGE	equ 00000001h	; language id 
LOCALE_SLANGUAGE	equ 00000002h	; localized name of language 
LOCALE_SENGLANGUAGE 	equ 00001001h	; English name of language 
LOCALE_SABBREVLANGNAME	equ 00000003h	; abbreviated language name 
LOCALE_SNATIVELANGNAME	equ 00000004h	; native name of language 
LOCALE_ICOUNTRY 	equ 00000005h	; country code 
LOCALE_SCOUNTRY 	equ 00000006h	; localized name of country 
LOCALE_SENGCOUNTRY	equ 00001002h	; English name of country 
LOCALE_SABBREVCTRYNAME	equ 00000007h	; abbreviated country name 
LOCALE_SNATIVECTRYNAME	equ 00000008h	; native name of country 
LOCALE_IDEFAULTLANGUAGE 	equ 00000009h	; default language id 
LOCALE_IDEFAULTCOUNTRY	equ 0000000Ah	; default country code 
LOCALE_IDEFAULTCODEPAGE 	equ 0000000Bh	; default oem code page 
LOCALE_IDEFAULTANSICODEPAGE 	equ 00001004h	; default ansi code page 
LOCALE_IDEFAULTMACCODEPAGE	equ 00001011h	; default mac code page 
LOCALE_SLIST		equ 0000000Ch	; list item separator 
LOCALE_IMEASURE 	equ 0000000Dh	; 0 = metric, 1 = US 
LOCALE_SDECIMAL 	equ 0000000Eh	; decimal separator 
LOCALE_STHOUSAND	equ 0000000Fh	; thousand separator 
LOCALE_SGROUPING	equ 00000010h	; digit grouping 
LOCALE_IDIGITS		equ 00000011h	; number of fractional digits 
LOCALE_ILZERO 		equ 00000012h	; leading zeros for decimal 
LOCALE_INEGNUMBER 	equ 00001010h	; negative number mode 
LOCALE_SNATIVEDIGITS	equ 00000013h	; native ascii 0-9 
LOCALE_SCURRENCY	equ 00000014h	; local monetary symbol 
LOCALE_SINTLSYMBOL	equ 00000015h	; intl monetary symbol 
LOCALE_SMONDECIMALSEP 	equ 00000016h	; monetary decimal separator 
LOCALE_SMONTHOUSANDSEP	equ 00000017h	; monetary thousand separator 
LOCALE_SMONGROUPING 	equ 00000018h	; monetary grouping 
LOCALE_ICURRDIGITS	equ 00000019h	; # local monetary digits 
LOCALE_IINTLCURRDIGITS	equ 0000001Ah	; # intl monetary digits 
LOCALE_ICURRENCY	equ 0000001Bh	; positive currency mode 
LOCALE_INEGCURR 	equ 0000001Ch	; negative currency mode 
LOCALE_SDATE		equ 0000001Dh	; date separator 
LOCALE_STIME		equ 0000001Eh	; time separator 
LOCALE_SSHORTDATE 	equ 0000001Fh	; short date format string 
LOCALE_SLONGDATE	equ 00000020h	; long date format string 
LOCALE_STIMEFORMAT	equ 00001003h	; time format string 
LOCALE_IDATE		equ 00000021h	; short date format ordering 
LOCALE_ILDATE 		equ 00000022h	; long date format ordering 
LOCALE_ITIME		equ 00000023h	; time format specifier 
LOCALE_ITIMEMARKPOSN	equ 00001005h	; time marker position 
LOCALE_ICENTURY 	equ 00000024h	; century format specifier (short date) 
LOCALE_ITLZERO		equ 00000025h	; leading zeros in time field 
LOCALE_IDAYLZERO	equ 00000026h	; leading zeros in day field (short date) 
LOCALE_IMONLZERO	equ 00000027h	; leading zeros in month field (short date) 
LOCALE_S1159		equ 00000028h	; AM designator 
LOCALE_S2359		equ 00000029h	; PM designator 
LOCALE_ICALENDARTYPE	equ 00001009h	; type of calendar specifier 
LOCALE_IOPTIONALCALENDAR	equ 0000100Bh	; additional calendar types specifier 
LOCALE_IFIRSTDAYOFWEEK	equ 0000100Ch	; first day of week specifier 
LOCALE_IFIRSTWEEKOFYEAR 	equ 0000100Dh	; first week of year specifier 
LOCALE_SDAYNAME1	equ 0000002Ah	; long name for Monday 
LOCALE_SDAYNAME2	equ 0000002Bh	; long name for Tuesday 
LOCALE_SDAYNAME3	equ 0000002Ch	; long name for Wednesday 
LOCALE_SDAYNAME4	equ 0000002Dh	; long name for Thursday 
LOCALE_SDAYNAME5	equ 0000002Eh	; long name for Friday 
LOCALE_SDAYNAME6	equ 0000002Fh	; long name for Saturday 
LOCALE_SDAYNAME7	equ 00000030h	; long name for Sunday 
LOCALE_SABBREVDAYNAME1	equ 00000031h	; abbreviated name for Monday 
LOCALE_SABBREVDAYNAME2	equ 00000032h	; abbreviated name for Tuesday 
LOCALE_SABBREVDAYNAME3	equ 00000033h	; abbreviated name for Wednesday 
LOCALE_SABBREVDAYNAME4	equ 00000034h	; abbreviated name for Thursday 
LOCALE_SABBREVDAYNAME5	equ 00000035h	; abbreviated name for Friday 
LOCALE_SABBREVDAYNAME6	equ 00000036h	; abbreviated name for Saturday 
LOCALE_SABBREVDAYNAME7	equ 00000037h	; abbreviated name for Sunday 
LOCALE_SMONTHNAME1	equ 00000038h	; long name for January 
LOCALE_SMONTHNAME2	equ 00000039h	; long name for February 
LOCALE_SMONTHNAME3	equ 0000003Ah	; long name for March 
LOCALE_SMONTHNAME4	equ 0000003Bh	; long name for April 
LOCALE_SMONTHNAME5	equ 0000003Ch	; long name for May 
LOCALE_SMONTHNAME6	equ 0000003Dh	; long name for June 
LOCALE_SMONTHNAME7	equ 0000003Eh	; long name for July 
LOCALE_SMONTHNAME8	equ 0000003Fh	; long name for August 
LOCALE_SMONTHNAME9	equ 00000040h	; long name for September 
LOCALE_SMONTHNAME10 	equ 00000041h	; long name for October 
LOCALE_SMONTHNAME11 	equ 00000042h	; long name for November 
LOCALE_SMONTHNAME12 	equ 00000043h	; long name for December 
LOCALE_SMONTHNAME13 	equ 0000100Eh	; long name for 13th month (if exists) 
LOCALE_SABBREVMONTHNAME1	equ 00000044h	; abbreviated name for January 
LOCALE_SABBREVMONTHNAME2	equ 00000045h	; abbreviated name for February 
LOCALE_SABBREVMONTHNAME3	equ 00000046h	; abbreviated name for March 
LOCALE_SABBREVMONTHNAME4	equ 00000047h	; abbreviated name for April 
LOCALE_SABBREVMONTHNAME5	equ 00000048h	; abbreviated name for May 
LOCALE_SABBREVMONTHNAME6	equ 00000049h	; abbreviated name for June 
LOCALE_SABBREVMONTHNAME7	equ 0000004Ah	; abbreviated name for July 
LOCALE_SABBREVMONTHNAME8	equ 0000004Bh	; abbreviated name for August 
LOCALE_SABBREVMONTHNAME9	equ 0000004Ch	; abbreviated name for September 
LOCALE_SABBREVMONTHNAME10 	equ 0000004Dh	; abbreviated name for October 
LOCALE_SABBREVMONTHNAME11 	equ 0000004Eh	; abbreviated name for November 
LOCALE_SABBREVMONTHNAME12 	equ 0000004Fh	; abbreviated name for December 
LOCALE_SABBREVMONTHNAME13 	equ 0000100Fh	; abbreviated name for 13th month (if exists) 
LOCALE_SPOSITIVESIGN	equ 00000050h	; positive sign 
LOCALE_SNEGATIVESIGN	equ 00000051h	; negative sign 
LOCALE_IPOSSIGNPOSN 	equ 00000052h	; positive sign position 
LOCALE_INEGSIGNPOSN 	equ 00000053h	; negative sign position 
LOCALE_IPOSSYMPRECEDES	equ 00000054h	; mon sym precedes pos amt 
LOCALE_IPOSSEPBYSPACE 	equ 00000055h	; mon sym sep by space from pos amt 
LOCALE_INEGSYMPRECEDES	equ 00000056h	; mon sym precedes neg amt 
LOCALE_INEGSEPBYSPACE 	equ 00000057h	; mon sym sep by space from neg amt 
LOCALE_FONTSIGNATURE	equ 00000058h	; font signature 
LOCALE_SISO639LANGNAME	equ 00000059h	; ISO abbreviated language name 
LOCALE_SISO3166CTRYNAME 	equ 0000005Ah	; ISO abbreviated country name 

; Time Flags for GetTimeFormatW.
 
TIME_NOMINUTESORSECONDS	equ 00000001h	; do not use minutes or seconds 
TIME_NOSECONDS 	equ 00000002h	; do not use seconds 
TIME_NOTIMEMARKER	equ 00000004h	; do not use time marker 
TIME_FORCE24HOURFORMAT 	equ 00000008h	; always use 24 hour format 

; Date Flags for GetDateFormatW.
 
DATE_SHORTDATE 	equ 00000001h	; use short date picture 
DATE_LONGDATE		equ 00000002h	; use long date picture 
DATE_USE_ALT_CALENDAR	equ 00000004h	; use alternate calendar (if any) 

; Calendar Types.
; These types are used for the GetALTCalendarInfoW NLS API routine.
 
CAL_ICALINTVALUE 	equ 00000001h	; calendar type 
CAL_SCALNAME 		equ 00000002h	; native name of calendar 
CAL_IYEAROFFSETRANGE 	equ 00000003h	; starting years of eras 
CAL_SERASTRING 		equ 00000004h	; era name for IYearOffsetRanges 
CAL_SSHORTDATE 		equ 00000005h	; short date format string 
CAL_SLONGDATE		equ 00000006h	; long date format string 
CAL_SDAYNAME1		equ 00000007h	; native name for Monday 
CAL_SDAYNAME2		equ 00000008h	; native name for Tuesday 
CAL_SDAYNAME3		equ 00000009h	; native name for Wednesday 
CAL_SDAYNAME4		equ 0000000ah	; native name for Thursday 
CAL_SDAYNAME5		equ 0000000bh	; native name for Friday 
CAL_SDAYNAME6		equ 0000000ch	; native name for Saturday 
CAL_SDAYNAME7		equ 0000000dh	; native name for Sunday 
CAL_SABBREVDAYNAME1	equ 0000000eh	; abbreviated name for Monday 
CAL_SABBREVDAYNAME2	equ 0000000fh	; abbreviated name for Tuesday 
CAL_SABBREVDAYNAME3	equ 00000010h	; abbreviated name for Wednesday 
CAL_SABBREVDAYNAME4	equ 00000011h	; abbreviated name for Thursday 
CAL_SABBREVDAYNAME5	equ 00000012h	; abbreviated name for Friday 
CAL_SABBREVDAYNAME6	equ 00000013h	; abbreviated name for Saturday 
CAL_SABBREVDAYNAME7	equ 00000014h	; abbreviated name for Sunday 
CAL_SMONTHNAME1	equ 00000015h	; native name for January 
CAL_SMONTHNAME2	equ 00000016h	; native name for February 
CAL_SMONTHNAME3	equ 00000017h	; native name for March 
CAL_SMONTHNAME4	equ 00000018h	; native name for April 
CAL_SMONTHNAME5	equ 00000019h	; native name for May 
CAL_SMONTHNAME6	equ 0000001ah	; native name for June 
CAL_SMONTHNAME7	equ 0000001bh	; native name for July 
CAL_SMONTHNAME8	equ 0000001ch	; native name for August 
CAL_SMONTHNAME9	equ 0000001dh	; native name for September 
CAL_SMONTHNAME10 	equ 0000001eh	; native name for October 
CAL_SMONTHNAME11 	equ 0000001fh	; native name for November 
CAL_SMONTHNAME12 	equ 00000020h	; native name for December 
CAL_SMONTHNAME13 	equ 00000021h	; native name for 13th month (if any) 
CAL_SABBREVMONTHNAME1	equ 00000022h	; abbreviated name for January 
CAL_SABBREVMONTHNAME2	equ 00000023h	; abbreviated name for February 
CAL_SABBREVMONTHNAME3	equ 00000024h	; abbreviated name for March 
CAL_SABBREVMONTHNAME4	equ 00000025h	; abbreviated name for April 
CAL_SABBREVMONTHNAME5	equ 00000026h	; abbreviated name for May 
CAL_SABBREVMONTHNAME6	equ 00000027h	; abbreviated name for June 
CAL_SABBREVMONTHNAME7	equ 00000028h	; abbreviated name for July 
CAL_SABBREVMONTHNAME8	equ 00000029h	; abbreviated name for August 
CAL_SABBREVMONTHNAME9	equ 0000002ah	; abbreviated name for September 
CAL_SABBREVMONTHNAME10 	equ 0000002bh	; abbreviated name for October 
CAL_SABBREVMONTHNAME11 	equ 0000002ch	; abbreviated name for November 
CAL_SABBREVMONTHNAME12 	equ 0000002dh	; abbreviated name for December 
CAL_SABBREVMONTHNAME13 	equ 0000002eh	; abbreviated name for 13th month (if any) 

; Calendar Enumeration Value.
 
ENUM_ALL_CALENDARS 	equ -1	; enumerate all calendars 

; Calendar ID Values.
 
CAL_GREGORIAN		equ 1	; Gregorian (localized) calendar 
CAL_GREGORIAN_US	equ 2	; Gregorian (U.S.) calendar 
CAL_JAPAN		equ 3	; Japanese Emperor Era calendar 
CAL_TAIWAN		equ 4	; Republic of China Era calendar 
CAL_KOREA		equ 5	; Korean Tangun Era calendar 
CAL_HIJRI		equ 6	; Hijri (Arabic Lunar) calendar 
CAL_THAI		equ 7	; Thai calendar 
CAL_HEBREW		equ 8	; Hebrew calendar 

; Typedefs
; Define all types for the NLS component here.

; Locale type constant.
 
LCTYPE	textequ	DWORD

; *Calendar type constant.
 
CALTYPE	textequ	DWORD

; Calendar ID.
 
CALID	textequ	DWORD

; CP Info.

CPINFO	struc
 cpi_MaxCharSize	dd	?		; max length (bytes) of a char 
 cpi_DefaultChar	db	MAX_DEFAULTCHAR dup(?)	; default character 
 cpi_LeadByte	db	MAX_LEADBYTES dup(?)	; lead byte ranges 
CPINFO	ends

; Number format.

NUMBERFMTA		struc
 nfm_NumDigits		dd	? 	; number of decimal digits 
 nfm_LeadingZero		dd	? 	; if leading zero in decimal fields 
 nfm_Grouping		dd	?	; group size left of decimal 
 nfm_lpDecimalSep		dd	?	; ptr to decimal separator string 
 nfm_lpThousandSep	dd	? 	; ptr to thousand separator string 
 nfm_NegativeOrder	dd	? 	; negative number ordering 
NUMBERFMTA		ends

NUMBERFMT	equ	NUMBERFMTA

; Currency format.

CURRENCYFMTA		struc
 cfm_NumDigits		dd	? 	; number of decimal digits 
 cfm_LeadingZero		dd	? 	; if leading zero in decimal fields 
 cfm_Grouping		dd	?	; group size left of decimal 
 cfm_lpDecimalSep		dd	?	; ptr to decimal separator string 
 cfm_lpThousandSep	dd	? 	; ptr to thousand separator string 
 cfm_NegativeOrder	dd	? 	; negative currency ordering 
 cfm_PositiveOrder		dd	? 	; positive currency ordering 
 cfm_lpCurrencySymbol	dd	?	; ptr to currency symbol string 
CURRENCYFMTA		ends

CURRENCYFMT	equ	CURRENCYFMTA

; Enumeration function constants.

; Macros
; Define all macros for the NLS component here.

; Function Prototypes
; Only prototypes for the NLS APIs should go here.

; Code Page Dependent APIs.
 

CompareString	equ	CompareStringA

LCMapString	equ	LCMapStringA

GetLocaleInfo	equ	GetLocaleInfoA

SetLocaleInfo	equ	SetLocaleInfoA

GetNumberFormat	equ	GetNumberFormatA

GetCurrencyFormat	equ	GetCurrencyFormatA

EnumCalendarInfo	equ	EnumCalendarInfoA

EnumTimeFormats	equ	EnumTimeFormatsA

EnumDateFormats	equ	EnumDateFormatsA

; Locale Independent APIs.
 
GetStringTypeEx	equ	GetStringTypeExA

; NOTE: The parameters for GetStringTypeA and GetStringTypeW are
; NOT the same.The W version was shipped in NT 3.1.The
; A version was then shipped in 16-bit OLE with the wrong
; parameters (ported from Win95).To be compatible, we
; must break the relationship between the A and W versions
; of GetStringType.There will be NO function call for the
; generic GetStringType.
; GetStringTypeEx (above) should be used instead.
 
FoldString	equ	FoldStringA

EnumSystemLocales	equ	EnumSystemLocalesA
EnumSystemCodePages	equ	EnumSystemCodePagesA
