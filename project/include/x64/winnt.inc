	IFDEF	UNICODE

GetDateFormat		equ	GetDateFormatW
GetTimeFormat		equ	GetTimeFormatW

	ELSE

GetDateFormat		equ	GetDateFormatA
GetTimeFormat		equ	GetTimeFormatA

	ENDIF

GetDateFormatA	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD
GetDateFormatW	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD
GetExitCodeThread	proto	:QWORD, :QWORD
GetTimeFormatA	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD
GetTimeFormatW	proto	:DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :DWORD
RtlZeroMemory	proto	:QWORD, :DWORD
RtlCopyMemory	proto	:QWORD, :DWORD, :QWORD

;
; Define access rights to files and directories
;

;
; The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
; devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
; constants *MUST* always be in sync.
; The values are redefined in devioctl.h because they must be available to
; both DOS and NT.
;

FILE_READ_DATA 		equ 0001h	; file & pipe
FILE_LIST_DIRECTORY  	equ 0001h	; directory
FILE_WRITE_DATA  	equ 0002h	; file & pipe
FILE_ADD_FILE		equ 0002h	; directory
FILE_APPEND_DATA 	equ 0004h	; file
FILE_ADD_SUBDIRECTORY  	equ 0004h	; directory
FILE_CREATE_PIPE_INSTANCE  	equ 0004h	; named pipe
FILE_READ_EA		equ 0008h	; file & directory
FILE_WRITE_EA		equ 0010h	; file & directory
FILE_EXECUTE		equ 0020h	; file
FILE_TRAVERSE		equ 0020h	; directory
FILE_DELETE_CHILD  	equ 0040h	; directory
FILE_READ_ATTRIBUTES 	equ 0080h	; all
FILE_WRITE_ATTRIBUTES  	equ 0100h	; all

FILE_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED + SYNCHRONIZE + 1FFh
FILE_GENERIC_READ	equ STANDARD_RIGHTS_READ + FILE_READ_DATA + FILE_READ_ATTRIBUTES + FILE_READ_EA + SYNCHRONIZE
FILE_GENERIC_WRITE	equ STANDARD_RIGHTS_WRITE + FILE_WRITE_DATA+ FILE_WRITE_ATTRIBUTES+ FILE_WRITE_EA+ FILE_APPEND_DATA + SYNCHRONIZE
FILE_GENERIC_EXECUTE	equ STANDARD_RIGHTS_EXECUTE + FILE_READ_ATTRIBUTES + FILE_EXECUTE + SYNCHRONIZE

FILE_SHARE_READ 		equ 00000001h
FILE_SHARE_WRITE	equ 00000002h
FILE_SHARE_DELETE 	equ 00000004h
FILE_ATTRIBUTE_READONLY 	equ 00000001h
FILE_ATTRIBUTE_HIDDEN 	equ 00000002h
FILE_ATTRIBUTE_SYSTEM 	equ 00000004h
FILE_ATTRIBUTE_DIRECTORY	equ 00000010h
FILE_ATTRIBUTE_ARCHIVE	equ 00000020h
FILE_ATTRIBUTE_NORMAL 	equ 00000080h
FILE_ATTRIBUTE_TEMPORARY	equ 00000100h
FILE_ATTRIBUTE_COMPRESSED 	equ 00000800h
FILE_ATTRIBUTE_OFFLINE	equ 00001000h
FILE_NOTIFY_CHANGE_FILE_NAME	equ 00000001h
FILE_NOTIFY_CHANGE_DIR_NAME 	equ 00000002h
FILE_NOTIFY_CHANGE_ATTRIBUTES 	equ 00000004h
FILE_NOTIFY_CHANGE_SIZE 	equ 00000008h
FILE_NOTIFY_CHANGE_LAST_WRITE 	equ 00000010h
FILE_NOTIFY_CHANGE_LAST_ACCESS	equ 00000020h
FILE_NOTIFY_CHANGE_CREATION 	equ 00000040h
FILE_NOTIFY_CHANGE_SECURITY 	equ 00000100h
FILE_ACTION_ADDED 	equ 00000001h
FILE_ACTION_REMOVED 	equ 00000002h
FILE_ACTION_MODIFIED	equ 00000003h
FILE_ACTION_RENAMED_OLD_NAME	equ 00000004h
FILE_ACTION_RENAMED_NEW_NAME	equ 00000005h
MAILSLOT_NO_MESSAGE	equ -1 
MAILSLOT_WAIT_FOREVER	equ -1 
FILE_CASE_SENSITIVE_SEARCH	equ 00000001h
FILE_CASE_PRESERVED_NAMES 	equ 00000002h
FILE_UNICODE_ON_DISK	equ 00000004h
FILE_PERSISTENT_ACLS	equ 00000008h
FILE_FILE_COMPRESSION 	equ 00000010h
FILE_VOLUME_IS_COMPRESSED 	equ 00008000h

;
;These are the generic rights.
;

GENERIC_READ 	equ 80000000h
GENERIC_WRITE	equ 40000000h
GENERIC_EXECUTE	equ 20000000h
GENERIC_ALL	equ 10000000h

;lint -save -e767 */

STATUS_WAIT_0		equ 00000000h
STATUS_ABANDONED_WAIT_0	equ 00000080h
STATUS_USER_APC	equ 000000C0h
STATUS_TIMEOUT 	equ 00000102h
STATUS_PENDING 		equ 00000103h
STATUS_SEGMENT_NOTIFICATION	equ 40000005h
STATUS_GUARD_PAGE_VIOLATION	equ 80000001h
STATUS_DATATYPE_MISALIGNMENT 	equ 80000002h
STATUS_BREAKPOINT	equ 80000003h
STATUS_SINGLE_STEP 	equ 80000004h
STATUS_ACCESS_VIOLATION	equ 0C0000005h
STATUS_IN_PAGE_ERROR 	equ 0C0000006h
STATUS_INVALID_HANDLE	equ 0C0000008h
STATUS_NO_MEMORY 	equ 0C0000017h
STATUS_ILLEGAL_INSTRUCTION 	equ 0C000001Dh
STATUS_NONCONTINUABLE_EXCEPTION	equ 0C0000025h
STATUS_INVALID_DISPOSITION 	equ 0C0000026h
STATUS_ARRAY_BOUNDS_EXCEEDED 	equ 0C000008Ch
STATUS_FLOAT_DENORMAL_OPERAND	equ 0C000008Dh
STATUS_FLOAT_DIVIDE_BY_ZERO	equ 0C000008Eh
STATUS_FLOAT_INEXACT_RESULT	equ 0C000008Fh
STATUS_FLOAT_INVALID_OPERATION 	equ 0C0000090h
STATUS_FLOAT_OVERFLOW	equ 0C0000091h
STATUS_FLOAT_STACK_CHECK 	equ 0C0000092h
STATUS_FLOAT_UNDERFLOW 	equ 0C0000093h
STATUS_INTEGER_DIVIDE_BY_ZERO	equ 0C0000094h
STATUS_INTEGER_OVERFLOW	equ 0C0000095h
STATUS_PRIVILEGED_INSTRUCTION	equ 0C0000096h
STATUS_STACK_OVERFLOW	equ 0C00000FDh
STATUS_CONTROL_C_EXIT	equ 0C000013Ah

;lint -restore */
MAXIMUM_WAIT_OBJECTS 	equ 64	; Maximum number of wait objects
MAXIMUM_SUSPEND_COUNT	equ MAXCHAR	; Maximum times thread can be suspended

;
; for move macros
;
HEAP_NO_SERIALIZE 	equ 00000001h
HEAP_GROWABLE 		equ 00000002h
HEAP_GENERATE_EXCEPTIONS	equ 00000004h
HEAP_ZERO_MEMORY	equ 00000008h
HEAP_REALLOC_IN_PLACE_ONLY	equ 00000010h
HEAP_TAIL_CHECKING_ENABLED	equ 00000020h
HEAP_FREE_CHECKING_ENABLED	equ 00000040h
HEAP_DISABLE_COALESCE_ON_FREE 	equ 00000080h
HEAP_CREATE_ALIGN_16	equ 00010000h
HEAP_CREATE_ENABLE_TRACING	equ 00020000h
HEAP_MAXIMUM_TAG	equ 0FFFh
HEAP_PSEUDO_TAG_FLAG	equ 8000h
HEAP_TAG_SHIFT		equ 16
; HEAP_MAKE_TAG_FLAGS( b, o ) (((b) + ((o) << 16)))

IS_TEXT_UNICODE_ASCII16 		equ 0001h
IS_TEXT_UNICODE_REVERSE_ASCII16 	equ 0010h
IS_TEXT_UNICODE_STATISTICS		equ 0002h
IS_TEXT_UNICODE_REVERSE_STATISTICS	equ 0020h
IS_TEXT_UNICODE_CONTROLS		equ 0004h
IS_TEXT_UNICODE_REVERSE_CONTROLS	equ 0040h
IS_TEXT_UNICODE_SIGNATURE 		equ 0008h
IS_TEXT_UNICODE_REVERSE_SIGNATURE 	equ 0080h
IS_TEXT_UNICODE_ILLEGAL_CHARS 		equ 0100h
IS_TEXT_UNICODE_ODD_LENGTH		equ 0200h
IS_TEXT_UNICODE_DBCS_LEADBYTE 		equ 0400h
IS_TEXT_UNICODE_NULL_BYTES		equ 1000h
IS_TEXT_UNICODE_UNICODE_MASK		equ 000Fh
IS_TEXT_UNICODE_REVERSE_MASK		equ 00F0h
IS_TEXT_UNICODE_NOT_UNICODE_MASK	equ 0F00h
IS_TEXT_UNICODE_NOT_ASCII_MASK		equ 0F000h

COMPRESSION_FORMAT_NONE	equ 0000h
COMPRESSION_FORMAT_DEFAULT 	equ 0001h
COMPRESSION_FORMAT_LZNT1 	equ 0002h
COMPRESSION_ENGINE_STANDARD	equ 0000h
COMPRESSION_ENGINE_MAXIMUM 	equ 0100h 

;
;Language IDs.
;
;The following two combinations of primary language ID and
;sublanguage ID have special semantics:
;
;Primary Language ID Sublanguage IDResult
;------------------- --------------- ------------------------
;LANG_NEUTRALSUBLANG_NEUTRAL Language neutral
;LANG_NEUTRALSUBLANG_DEFAULT User default language
;LANG_NEUTRALSUBLANG_SYS_DEFAULT System default language
;

;
;Primary language IDs.
;

LANG_NEUTRAL 	equ 00h
LANG_AFRIKAANS 	equ 36h
LANG_ALBANIAN	equ 1ch
LANG_ARABIC	equ 01h
LANG_BASQUE	equ 2dh
LANG_BELARUSIAN	equ 23h
LANG_BULGARIAN 	equ 02h
LANG_CATALAN 	equ 03h
LANG_CHINESE 	equ 04h
LANG_CROATIAN	equ 1ah
LANG_CZECH 	equ 05h
LANG_DANISH	equ 06h
LANG_DUTCH 	equ 13h
LANG_ENGLISH 	equ 09h
LANG_ESTONIAN	equ 25h
LANG_FAEROESE	equ 38h
LANG_FARSI 	equ 29h
LANG_FINNISH 	equ 0bh
LANG_FRENCH	equ 0ch
LANG_GERMAN	equ 07h
LANG_GREEK 	equ 08h
LANG_HEBREW	equ 0dh
LANG_HUNGARIAN 	equ 0eh
LANG_ICELANDIC 	equ 0fh
LANG_INDONESIAN	equ 21h
LANG_ITALIAN 	equ 10h
LANG_JAPANESE	equ 11h
LANG_KOREAN	equ 12h
LANG_LATVIAN 	equ 26h
LANG_LITHUANIAN	equ 27h
LANG_NORWEGIAN 	equ 14h
LANG_POLISH	equ 15h
LANG_PORTUGUESE	equ 16h
LANG_ROMANIAN	equ 18h
LANG_RUSSIAN 	equ 19h
LANG_SERBIAN 	equ 1ah
LANG_SLOVAK	equ 1bh
LANG_SLOVENIAN 	equ 24h
LANG_SPANISH 	equ 0ah
LANG_SWEDISH 	equ 1dh
LANG_THAI	equ 1eh
LANG_TURKISH 	equ 1fh
LANG_UKRAINIAN 	equ 22h
LANG_VIETNAMESE	equ 2ah

;
;Sublanguage IDs.
;
;The name immediately following SUBLANG_ dictates which primary
;language ID that sublanguage ID can be combined with to form a
;valid language ID.
;

SUBLANG_NEUTRAL		equ 00h	; language neutral
SUBLANG_DEFAULT		equ 01h	; user default
SUBLANG_SYS_DEFAULT	equ 02h	; system default
SUBLANG_ARABIC_SAUDI_ARABIA	equ 01h	; Arabic (Saudi Arabia)
SUBLANG_ARABIC_IRAQ	equ 02h	; Arabic (Iraq)
SUBLANG_ARABIC_EGYPT 	equ 03h	; Arabic (Egypt)
SUBLANG_ARABIC_LIBYA 	equ 04h	; Arabic (Libya)
SUBLANG_ARABIC_ALGERIA 	equ 05h	; Arabic (Algeria)
SUBLANG_ARABIC_MOROCCO 	equ 06h	; Arabic (Morocco)
SUBLANG_ARABIC_TUNISIA 	equ 07h	; Arabic (Tunisia)
SUBLANG_ARABIC_OMAN	equ 08h	; Arabic (Oman)
SUBLANG_ARABIC_YEMEN 	equ 09h	; Arabic (Yemen)
SUBLANG_ARABIC_SYRIA 	equ 0ah	; Arabic (Syria)
SUBLANG_ARABIC_JORDAN	equ 0bh	; Arabic (Jordan)
SUBLANG_ARABIC_LEBANON 	equ 0ch	; Arabic (Lebanon)
SUBLANG_ARABIC_KUWAIT	equ 0dh	; Arabic (Kuwait)
SUBLANG_ARABIC_UAE 	equ 0eh	; Arabic (U.A.E)
SUBLANG_ARABIC_BAHRAIN 	equ 0fh	; Arabic (Bahrain)
SUBLANG_ARABIC_QATAR 	equ 10h	; Arabic (Qatar)
SUBLANG_CHINESE_TRADITIONAL	equ 01h	; Chinese (Taiwan)
SUBLANG_CHINESE_SIMPLIFIED 	equ 02h	; Chinese (PR China)
SUBLANG_CHINESE_HONGKONG 	equ 03h	; Chinese (Hong Kong)
SUBLANG_CHINESE_SINGAPORE	equ 04h	; Chinese (Singapore)
SUBLANG_DUTCH		equ 01h	; Dutch
SUBLANG_DUTCH_BELGIAN	equ 02h	; Dutch (Belgian)
SUBLANG_ENGLISH_US 	equ 01h	; English (USA)
SUBLANG_ENGLISH_UK 	equ 02h	; English (UK)
SUBLANG_ENGLISH_AUS	equ 03h	; English (Australian)
SUBLANG_ENGLISH_CAN	equ 04h	; English (Canadian)
SUBLANG_ENGLISH_NZ 	equ 05h	; English (New Zealand)
SUBLANG_ENGLISH_EIRE 	equ 06h	; English (Irish)
SUBLANG_ENGLISH_SOUTH_AFRICA 	equ 07h	; English (South Africa)
SUBLANG_ENGLISH_JAMAICA	equ 08h	; English (Jamaica)
SUBLANG_ENGLISH_CARIBBEAN	equ 09h	; English (Caribbean)
SUBLANG_ENGLISH_BELIZE 	equ 0ah	; English (Belize)
SUBLANG_ENGLISH_TRINIDAD 	equ 0bh	; English (Trinidad)
SUBLANG_FRENCH	 	equ 01h	; French
SUBLANG_FRENCH_BELGIAN 	equ 02h	; French (Belgian)
SUBLANG_FRENCH_CANADIAN	equ 03h	; French (Canadian)
SUBLANG_FRENCH_SWISS 	equ 04h	; French (Swiss)
SUBLANG_FRENCH_LUXEMBOURG	equ 05h	; French (Luxembourg)
SUBLANG_GERMAN	 	equ 01h	; German
SUBLANG_GERMAN_SWISS 	equ 02h	; German (Swiss)
SUBLANG_GERMAN_AUSTRIAN	equ 03h	; German (Austrian)
SUBLANG_GERMAN_LUXEMBOURG	equ 04h	; German (Luxembourg)
SUBLANG_GERMAN_LIECHTENSTEIN 	equ 05h	; German (Liechtenstein)
SUBLANG_ITALIAN		equ 01h	; Italian
SUBLANG_ITALIAN_SWISS	equ 02h	; Italian (Swiss)
SUBLANG_KOREAN 		equ 01h	; Korean (Extended Wansung)
SUBLANG_KOREAN_JOHAB 	equ 02h	; Korean (Johab)
SUBLANG_NORWEGIAN_BOKMAL 	equ 01h	; Norwegian (Bokmal)
SUBLANG_NORWEGIAN_NYNORSK	equ 02h	; Norwegian (Nynorsk)
SUBLANG_PORTUGUESE 	equ 02h	; Portuguese
SUBLANG_PORTUGUESE_BRAZILIAN 	equ 01h	; Portuguese (Brazilian)
SUBLANG_SERBIAN_LATIN	equ 02h	; Serbian (Latin)
SUBLANG_SERBIAN_CYRILLIC 	equ 03h	; Serbian (Cyrillic)
SUBLANG_SPANISH		equ 01h	; Spanish (Castilian)
SUBLANG_SPANISH_MEXICAN	equ 02h	; Spanish (Mexican)
SUBLANG_SPANISH_MODERN 	equ 03h	; Spanish (Modern)
SUBLANG_SPANISH_GUATEMALA	equ 04h	; Spanish (Guatemala)
SUBLANG_SPANISH_COSTA_RICA 	equ 05h	; Spanish (Costa Rica)
SUBLANG_SPANISH_PANAMA 	equ 06h	; Spanish (Panama)
SUBLANG_SPANISH_DOMINICAN_REPUBLIC 	equ 07h	; Spanish (Dominican Republic)
SUBLANG_SPANISH_VENEZUELA	equ 08h	; Spanish (Venezuela)
SUBLANG_SPANISH_COLOMBIA 	equ 09h	; Spanish (Colombia)
SUBLANG_SPANISH_PERU 	equ 0ah	; Spanish (Peru)
SUBLANG_SPANISH_ARGENTINA	equ 0bh	; Spanish (Argentina)
SUBLANG_SPANISH_ECUADOR	equ 0ch	; Spanish (Ecuador)
SUBLANG_SPANISH_CHILE	equ 0dh	; Spanish (Chile)
SUBLANG_SPANISH_URUGUAY	equ 0eh	; Spanish (Uruguay)
SUBLANG_SPANISH_PARAGUAY 	equ 0fh	; Spanish (Paraguay)
SUBLANG_SPANISH_BOLIVIA	equ 10h	; Spanish (Bolivia)
SUBLANG_SPANISH_EL_SALVADOR	equ 11h	; Spanish (El Salvador)
SUBLANG_SPANISH_HONDURAS 	equ 12h	; Spanish (Honduras)
SUBLANG_SPANISH_NICARAGUA	equ 13h	; Spanish (Nicaragua)
SUBLANG_SPANISH_PUERTO_RICO	equ 14h	; Spanish (Puerto Rico)
SUBLANG_SWEDISH	equ 01h	; Swedish
SUBLANG_SWEDISH_FINLAND	equ 02h	; Swedish (Finland)

;
;Sorting IDs.
;

SORT_DEFAULT 		equ 0 ; sorting default
SORT_JAPANESE_XJIS 	equ 0 ; Japanese XJIS order
SORT_JAPANESE_UNICODE	equ 1 ; Japanese Unicode order
SORT_CHINESE_BIG5	equ 0 ; Chinese BIG5 order
SORT_CHINESE_PRCP	equ 0 ; PRC Chinese Phonetic order
SORT_CHINESE_UNICODE 	equ 1 ; Chinese Unicode order
SORT_CHINESE_PRC 	equ 2 ; PRC Chinese Stroke Count order
SORT_KOREAN_KSC	equ 0 ; Korean KSC order
SORT_KOREAN_UNICODE	equ 1 ; Korean Unicode order
SORT_GERMAN_PHONE_BOOK 	equ 1 ; German Phone Book order

; end_r_winnt

;
;A language ID is a 16 bit value which is the combination of a
;primary language ID and a secondary language ID.The bits are
;allocated as follows:
;
; +-----------------------+-------------------------+
; + Sublanguage ID+ Primary Language ID +
; +-----------------------+-------------------------+
;15 10 9 0 bit
;
;
;Language ID creation/extraction macros:
;
;MAKELANGID- construct language id from a primary language id and
;a sublanguage id.
;PRIMARYLANGID - extract primary language id from a language id.
;SUBLANGID - extract sublanguage id from a language id.
;

; MAKELANGID(p, s) (s << 10) + p
; PRIMARYLANGID(lgid) ((lgid) & 0x3ff)
; SUBLANGID(lgid)((lgid) >> 10)


;
;A locale ID is a 32 bit value which is the combination of a
;language ID, a sort ID, and a reserved area.The bits are
;allocated as follows:
;
; +-------------+---------+-------------------------+
; + Reserved+ Sort ID +Language ID+
; +-------------+---------+-------------------------+
;31 20 19 16 150 bit
;
;
;Locale ID creation/extraction macros:
;
;MAKELCID - construct locale id from a language id and a sort id.
;LANGIDFROMLCID - extract language id from a locale id.
;SORTIDFROMLCID - extract sort id from a locale id.
;

NLS_VALID_LOCALE_MASK	equ 000fffffh

; MAKELCID(lgid, srtid) ((srtid << 16) + lgid)
; LANGIDFROMLCID(lcid) (lcid)
; SORTIDFROMLCID(lcid) (lcid & NLS_VALID_LOCALE_MASK) >> 16)

;
;Default System and User IDs for language and locale.
;

LANG_SYSTEM_DEFAULT	equ LANG_NEUTRAL + SUBLANG_SYS_DEFAULT * 1024
LANG_USER_DEFAULT	equ LANG_NEUTRAL + SUBLANG_DEFAULT * 1024

LOCALE_SYSTEM_DEFAULT	equ LANG_SYSTEM_DEFAULT + SORT_DEFAULT * 10000h
LOCALE_USER_DEFAULT	equ LANG_USER_DEFAULT + SORT_DEFAULT * 10000h
LOCALE_NEUTRAL		equ (LANG_NEUTRAL + SUBLANG_NEUTRAL * 1024) + SORT_DEFAULT * 10000h

RTL_CRITICAL_SECTION	struc
 DebugInfo		dq	?
 LockCount		dd	?
 RecursionCount		dd	?
 OwningThread		dq	?	; from the thread's ClientId->UniqueThread
 LockSemaphore		dq	?
 SpinCount		dq	?
RTL_CRITICAL_SECTION	ends
	

;++ BUILD Version: 0093 Increment this if a change has global effects
;
; Copyright (c) 1990-1996Microsoft Corporation
;
; Module Name:
;
; winnt.h
;
; Abstract:
;
; This module defines the 32-Bit Windows types and constants that are
; defined by NT, but exposed through the Win32 API.

ANYSIZE_ARRAY	equ	1

; begin_ntddk begin_nthal begin_ntifs
;
;The following are masks for the predefined standard access types
;

DELETE 	equ 00010000h
READ_CONTROL 	equ 00020000h
WRITE_DAC	equ 00040000h
WRITE_OWNER	equ 00080000h
SYNCHRONIZE	equ 00100000h

STANDARD_RIGHTS_REQUIRED 	equ 000F0000h
STANDARD_RIGHTS_READ	equ READ_CONTROL
STANDARD_RIGHTS_WRITE	equ READ_CONTROL
STANDARD_RIGHTS_EXECUTE	equ READ_CONTROL
STANDARD_RIGHTS_ALL	equ 001F0000h
SPECIFIC_RIGHTS_ALL	equ 0000FFFFh
comment #

;
; Basics
;

CHAR	textequ	db
;SHORT	textequ	dw
LONG	textequ	dd

;
; UNICODE (Wide Character) types
;

WCHAR	textequ	dw	; wc, 16-bit UNICODE character

PWCHAR	textequ	dd
LPWCH	textequ	dd
PWCH	textequ	dd
LPCWCH	textequ	dd
PCWCH	textequ	dd
NWPSTR	textequ	dd
LPWSTR	textequ	dd
PWSTR	textequ	dd
LPCWSTR	textequ	dd
PCWSTR	textequ	dd

;
; ANSI (Multi-byte Character) types
;

PCHAR	textequ	dd
LPCH	textequ	dd
PCH	textequ	dd
LPCCH	textequ	dd
PCCH	textequ	dd
NPSTR	textequ	dd
LPSTR	textequ	dd
PSTR	textequ	dd
LPCSTR	textequ	dd
PCSTR	textequ	dd

;
; Flag (bit) fields
;

FCHAR	textequ	db
FSHORT	textequ	dw
FLONG	textequ	dd

;lint -e624 */
;lint +e624 */
APPLICATION_ERROR_MASK 	equ 20000000h
ERROR_SEVERITY_SUCCESS 	equ 00000000h
ERROR_SEVERITY_INFORMATIONAL 	equ 40000000h
ERROR_SEVERITY_WARNING 	equ 80000000h
ERROR_SEVERITY_ERROR 	equ 0C0000000h

;
; Base data structures for OLE support
;

GUID	struc
 guid_Data1	dd	?
 guid_Data2	dw	?
 guid_Data3	dw	?
 guid_Data4	db	?
 	db	?
 	db	?
 	db	?
	db	?
 	db	?
 	db	?
 	db	?
GUID	ends

CLSID	struc
 clsid_Data1	dd	?
 clsid_Data2	dw	?
 clsid_Data3	dw	?
 clsid_Data4	db	?
 	db	?
 	db	?
 	db	?
	db	?
 	db	?
 	db	?
 	db	?
CLSID	ends

FMTID	struc
 fmtid_Data1	dd	?
 fmtid_Data2	dw	?
 fmtid_Data3	dw	?
 fmtid_Data4	db	?
 	db	?
 	db	?
 	db	?
	db	?
 	db	?
 	db	?
 	db	?
FMTID	ends

OBJECTID	struc
 oid_Lineage	GUID	<?>
 oid_Uniquifier	dd	?
OBJECTID	ends

MINCHAR 	equ 80h
MAXCHAR 	equ 7fh
MINSHORT	equ 8000h
MAXSHORT	equ 7fffh
MINLONG 	equ 80000000h
MAXLONG 	equ 7fffffffh
MAXBYTE 	equ 0ffh
MAXWORD 	equ 0ffffh
MAXDWORD	equ 0ffffffffh


; begin_ntminiport begin_ntndis begin_ntminitape
;

LUID	struc
 luid_LowPart	dd	?
 luid_HighPart	dd	?
LUID	ends

; Macros used to eliminate compiler warning generated when formal
; parameters or local variables are not declared.
;
; Use DBG_UNREFERENCED_PARAMETER() when a parameter is not yet
; referenced but will be once the module is completely developed.
;
; Use DBG_UNREFERENCED_LOCAL_VARIABLE() when a local variable is not yet
; referenced but will be once the module is completely developed.
;
; Use UNREFERENCED_PARAMETER() if a parameter will never be referenced.
;
; DBG_UNREFERENCED_PARAMETER and DBG_UNREFERENCED_LOCAL_VARIABLE will
; eventually be made into a null macro to help determine whether there
; is unfinished work.
;

; UNREFERENCED_PARAMETER(P)(P)
; DBG_UNREFERENCED_PARAMETER(P)(P)
; DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

; Note: lint -e530 says don't complain about uninitialized variables for
; this.line +e530 turns that checking back on.Error 527 has to do with
; unreachable code.

; UNREFERENCED_PARAMETER(P);lint -e527 -e530 */ { (P) = (P); } ;lint +e527 +e530 */
; DBG_UNREFERENCED_PARAMETER(P);lint -e527 -e530 */ { (P) = (P); } ;lint +e527 +e530 */
; DBG_UNREFERENCED_LOCAL_VARIABLE(V) ;lint -e527 -e530 */ { (V) = (V); } ;lint +e527 +e530 */


;
; Define function to return the current Thread Environment Block
;

;
; Disable these two pramas that evaluate to "sti" "cli" on x86 so that driver
; writers to not leave them inadvertantly in their code.
;

GetFiberData	macro
	mov eax, fs:[16]
	mov eax, [eax]
	endm

GetCurrentFiber	macro
	mov eax, fs:[16]
	endm

; begin_wx86

;
;Define the size of the 80387 save area, which is in the context frame.
;

SIZE_OF_80387_REGISTERS	equ	80

;
; The following flags control the contents of the CONTEXT structure.
;

CONTEXT_i386	equ 00010000h	; this assumes that i386 and
CONTEXT_i486	equ 00010000h	; i486 have identical context records

CONTEXT_CONTROL	equ CONTEXT_i386 + 00000001h	; SS:SP, CS:IP, FLAGS, BP
CONTEXT_INTEGER		equ CONTEXT_i386 + 00000002h	; AX, BX, CX, DX, SI, DI
CONTEXT_SEGMENTS	equ CONTEXT_i386 + 00000004h	; DS, ES, FS, GS
CONTEXT_FLOATING_POINT	equ CONTEXT_i386 + 00000008h	; 387 state
CONTEXT_DEBUG_REGISTERS	equ CONTEXT_i386 + 00000010h	; DB 0-3,6,7
CONTEXT_FULL		equ CONTEXT_CONTROL + CONTEXT_INTEGER +CONTEXT_SEGMENTS

; begin_wx86

FLOATING_SAVE_AREA	struc
 fsa_ControlWord	dd	?
 fsa_StatusWord	dd	?
 fsa_TagWord	dd	?
 fsa_ErrorOffset	dd	?
 fsa_ErrorSelector	dd	?
 fsa_DataOffset	dd	?
 fsa_DataSelector	dd	?
 fsa_RegisterArea	db	SIZE_OF_80387_REGISTERS dup(?)
 fsa_Cr0NpxState	dd	?
FLOATING_SAVE_AREA	ends

;
; Context Frame
;
;This frame has a several purposes: 1) it is used as an argument to
;NtContinue, 2) is is used to constuct a call frame for APC delivery,
;and 3) it is used in the user level thread creation routines.
;
;The layout of the record conforms to a standard call frame.
;

CONTEXT	struc

;
; The flags values within this flag control the contents of
; a CONTEXT record.
;
; If the context record is used as an input parameter, then
; for each portion of the context record controlled by a flag
; whose value is set, it is assumed that that portion of the
; context record contains valid context. If the context record
; is being used to modify a threads context, then only that
; portion of the threads context will be modified.
;
; If the context record is used as an IN OUT parameter to capture
; the context of a thread, then only those portions of the thread's
; context corresponding to set flags will be returned.
;
; The context record is never used as an OUT only parameter.
;

 con_ContextFlags	dd	?

;
; This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
; set in ContextFlags.Note that CONTEXT_DEBUG_REGISTERS is NOT
; included in CONTEXT_FULL.
;

 con_Dr0	dd	?
 con_Dr1	dd	?
 con_Dr2	dd	?
 con_Dr3	dd	?
 con_Dr6	dd	?
 con_Dr7	dd	?

;
; This section is specified/returned if the
; ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
;

 con_FloatSave	FLOATING_SAVE_AREA	<?>

;
; This section is specified/returned if the
; ContextFlags word contians the flag CONTEXT_SEGMENTS.
;

 con_SegGs	dd	?
 con_SegFs	dd	?
 con_SegEs	dd	?
 con_SegDs	dd	?

;
; This section is specified/returned if the
; ContextFlags word contians the flag CONTEXT_INTEGER.
;

 con_Edi	dd	?
 con_Esi	dd	?
 con_Ebx	dd	?
 con_Edx	dd	?
 con_Ecx	dd	?
 con_Eax	dd	?

;
; This section is specified/returned if the
; ContextFlags word contians the flag CONTEXT_CONTROL.
;

 con_Ebp	dd	?
 con_Eip	dd	?
 con_SegCs	dd	?	; MUST BE SANITIZED
 con_EFlags	dd	?	; MUST BE SANITIZED
 con_Esp	dd	?
 con_SegSs	dd	?
CONTEXT	ends


LDT_ENTRY	struc
 ldt_LimitLow	dw	?
 ldt_BaseLow	dw	?
union {
struct {
BYTEBaseMid;
BYTEFlags1; ; Declare as bytes to avoid alignment
BYTEFlags2; ; Problems.
BYTEBaseHi;
} Bytes;

struct {
DWORD BaseMid : 8;
DWORD Type : 5;
DWORD Dpl : 2;
DWORD Pres : 1;
DWORD LimitHi : 4;
DWORD Sys : 1;
DWORD Reserved_0 : 1;
DWORD Default_Big : 1;
DWORD Granularity : 1;
DWORD BaseHi : 8;
} Bits;
} HighWord;
LDT_ENTRY	ends


EXCEPTION_NONCONTINUABLE 	equ 1	; Noncontinuable exception
EXCEPTION_MAXIMUM_PARAMETERS	equ 15	; maximum number of exception parameters

;
; Exception record definition.
;

EXCEPTION_RECORD	struc
 exr_ExceptionCode	dd	?
 exr_ExceptionFlags	dd	?
 exr_ExceptionRecord	dd	?
 exr_ExceptionAddress	dd	?
 exr_NumberParameters	dd	?
 exr_ExceptionInformation	dd	EXCEPTION_MAXIMUM_PARAMETERS dup(?)
EXCEPTION_RECORD	ends

;
; Typedef for pointer returned by exception_info()
;

EXCEPTION_POINTERS	struc
 exp_ExceptionRecord	dd	?
 exp_ContextRecord	dd	?
EXCEPTION_POINTERS	ends


PROCESS_TERMINATE 	equ 0001h
PROCESS_CREATE_THREAD 	equ 0002h
PROCESS_VM_OPERATION	equ 0008h
PROCESS_VM_READ 	equ 0010h
PROCESS_VM_WRITE	equ 0020h
PROCESS_DUP_HANDLE	equ 0040h
PROCESS_CREATE_PROCESS	equ 0080h
PROCESS_SET_QUOTA 	equ 0100h
PROCESS_SET_INFORMATION 	equ 0200h
PROCESS_QUERY_INFORMATION 	equ 0400h
PROCESS_ALL_ACCESS	equ	STANDARD_RIGHTS_REQUIRED OR SYNCHRONIZE OR 0FFFh

MAXIMUM_PROCESSORS 	equ 32

THREAD_TERMINATE 	equ 0001h
THREAD_SUSPEND_RESUME	equ 0002h
THREAD_GET_CONTEXT 	equ 0008h
THREAD_SET_CONTEXT 	equ 0010h
THREAD_SET_INFORMATION 	equ 0020h
THREAD_QUERY_INFORMATION 	equ 0040h
THREAD_SET_THREAD_TOKEN	equ 0080h
THREAD_IMPERSONATE 	equ 0100h
THREAD_DIRECT_IMPERSONATION	equ 0200h

THREAD_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED + SYNCHRONIZE +  3FFh

TLS_MINIMUM_AVAILABLE	equ 64


NT_TIB {
struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList;
PVOID StackBase;
PVOID StackLimit;
PVOID SubSystemTib;
union {
PVOID FiberData;
DWORD Version;
};
PVOID ArbitraryUserPointer;

struct _NT_TIB *Self;
} NT_TIB;


THREAD_BASE_PRIORITY_LOWRT	equ	15	; value that gets a thread to LowRealtime-1
THREAD_BASE_PRIORITY_MAX	equ	2	; maximum thread base priority boost
THREAD_BASE_PRIORITY_MIN	equ	-2	; minimum thread base priority boost
THREAD_BASE_PRIORITY_IDLE	equ	-15	; value that gets a thread to idle

QUOTA_LIMITS	struc
 qlm_PagedPoolLimit	dd	?
 qlm_NonPagedPoolLimit	dd	?
 qlm_MinimumWorkingSetSize	dd	?
 qlm_MaximumWorkingSetSize	dd	?
 qlm_PagefileLimit		dd	?
 qlm_TimeLimit		LARGE_INTEGER	<?>
QUOTA_LIMITS	ends

EVENT_MODIFY_STATE	equ 0002h
EVENT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED + SYNCHRONIZE + 3

MUTANT_QUERY_STATE	equ 1
MUTANT_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED+SYNCHRONIZE+MUTANT_QUERY_STATE
SEMAPHORE_MODIFY_STATE	equ 2
SEMAPHORE_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED+SYNCHRONIZE+3
TIME_ZONE_ID_UNKNOWN	equ 0
TIME_ZONE_ID_STANDARD	equ 1
TIME_ZONE_ID_DAYLIGHT	equ 2

PROCESSOR_INTEL_386	equ 386
PROCESSOR_INTEL_486	equ 486
PROCESSOR_INTEL_PENTIUM	equ 586
PROCESSOR_MIPS_R4000	equ 4000
PROCESSOR_ALPHA_21064	equ 21064

PROCESSOR_ARCHITECTURE_INTEL	equ 0
PROCESSOR_ARCHITECTURE_MIPS	equ 1
PROCESSOR_ARCHITECTURE_ALPHA	equ 2
PROCESSOR_ARCHITECTURE_PPC	equ 3
PROCESSOR_ARCHITECTURE_UNKNOWN equ 0FFFFh

PF_FLOATING_POINT_PRECISION_ERRATA	equ 0 
PF_FLOATING_POINT_EMULATED		equ 1 
PF_COMPARE_EXCHANGE_DOUBLE		equ 2 
PF_MMX_INSTRUCTIONS_AVAILABLE		equ 3 

MEMORY_BASIC_INFORMATION	struc
 mbi_BaseAddress	dd	?
 mbi_AllocationBase	dd	?
 mbi_AllocationProtect	dd	?
 mbi_RegionSize	dd	?
 mbi_State	dd	?
 mbi_Protect	dd	?
 mbi_Type	dd	?
MEMORY_BASIC_INFORMATION	ends

SECTION_QUERY 		equ 0001
SECTION_MAP_WRITE 	equ 0002
SECTION_MAP_READ	equ 0004
SECTION_MAP_EXECUTE 	equ 0008
SECTION_EXTEND_SIZE 	equ 0010

SECTION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED+SECTION_QUERY+SECTION_MAP_WRITE +SECTION_MAP_READ + SECTION_MAP_EXECUTE +SECTION_EXTEND_SIZE
PAGE_NOACCESS		equ 01h
PAGE_READONLY		equ 02h
PAGE_READWRITE 		equ 04h
PAGE_WRITECOPY 		equ 08h
PAGE_EXECUTE 		equ 10h
PAGE_EXECUTE_READ	equ 20h
PAGE_EXECUTE_READWRITE 	equ 40h
PAGE_EXECUTE_WRITECOPY 	equ 80h
PAGE_GUARD		equ 100h
PAGE_NOCACHE		equ 200h
MEM_COMMIT 		equ 1000h
MEM_RESERVE		equ 2000h
MEM_DECOMMIT 		equ 4000h
MEM_RELEASE		equ 8000h
MEM_FREE		equ 10000h
MEM_PRIVATE 		equ 20000h
MEM_MAPPED		equ 40000h
MEM_RESET 		equ 80000h
MEM_TOP_DOWN 		equ 100000h
SEC_FILE 		equ 800000h
SEC_IMAGE 		equ 1000000h
SEC_RESERVE 		equ 4000000h
SEC_COMMIT		equ 8000000h
SEC_NOCACHE		equ 10000000h
MEM_IMAGE		equ SEC_IMAGE 


;
; Define the file notification information structure
;

FILE_NOTIFY_INFORMATION	struc
 fni_NextEntryOffset	dd	?
 fni_Action		dd	?
 fni_FileNameLength	dd	?
 fni_FileName		dw	?
FILE_NOTIFY_INFORMATION	ends

IO_COMPLETION_MODIFY_STATE	equ 2
IO_COMPLETION_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED+SYNCHRONIZE+3
DUPLICATE_CLOSE_SOURCE	equ 1
DUPLICATE_SAME_ACCESS 	equ 2

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; ACCESS MASK;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
;Define the access mask as a longword sized structure divided up as
;follows:
;
; 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
; 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+---------------+---------------+-------------------------------+
;+G+G+G+G+Res'd+A+ StandardRights+ SpecificRights+
;+R+W+E+A+ +S+ + +
;+-+-------------+---------------+-------------------------------+
;
;typedef struct _ACCESS_MASK {
;WORD SpecificRights;
;BYTEStandardRights;
;BYTEAccessSystemAcl : 1;
;BYTEReserved : 3;
;BYTEGenericAll : 1;
;BYTEGenericExecute : 1;
;BYTEGenericWrite : 1;
;BYTEGenericRead : 1;
;} ACCESS_MASK;
;typedef ACCESS_MASK *PACCESS_MASK;
;
;but to make life simple for programmer's we'll allow them to specify
;a desired access mask by simply OR'ing together mulitple single rights
;and treat an access mask as a DWORD.For example
;
;DesiredAccess = DELETE + READ_CONTROL
;
;So we'll declare ACCESS_MASK as DWORD
;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; ACCESS TYPES ;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;



;
; AccessSystemAcl access type
;

ACCESS_SYSTEM_SECURITY 	equ 01000000h

;
; MaximumAllowed access type
;

MAXIMUM_ALLOWED	equ 02000000h

;
;Define the generic mapping array.This is used to denote the
;mapping of each generic access right to a specific access mask.
;

GENERIC_MAPPING		struc
 gmp_GenericRead		dd	?
 gmp_GenericWrite		dd	?
 gmp_GenericExecute	dd	?
 gmp_GenericAll		dd	?
GENERIC_MAPPING		ends

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;LUID_AND_ATTRIBUTES ;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;

LUID_AND_ATTRIBUTES	struc
 lua_Luid		LUID	<?>
 lua_Attributes		dd	?
LUID_AND_ATTRIBUTES	ends

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;Security Id (SID) ;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;
; Pictorially the structure of an SID is as follows:
;
; 1 1 1 1 1 1
; 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+---------------------------------------------------------------+
;+SubAuthorityCount+Reserved1 (SBZ)+ Revision+
;+---------------------------------------------------------------+
;+ IdentifierAuthority[0]+
;+---------------------------------------------------------------+
;+ IdentifierAuthority[1]+
;+---------------------------------------------------------------+
;+ IdentifierAuthority[2]+
;+---------------------------------------------------------------+
;+ +
;+- -------SubAuthority[]-------- -+
;+ +
;+---------------------------------------------------------------+
;
;

; begin_ntifs

SID_IDENTIFIER_AUTHORITY	struc
 sia_Value	db	6 dup(?)
SID_IDENTIFIER_AUTHORITY	ends

SID		struc
 sid_Revision		db	?
 sid_SubAuthorityCount	db	?
 sid_IdentifierAuthority	SID_IDENTIFIER_AUTHORITY <?>
 sid_SubAuthority		dd	ANYSIZE_ARRAY dup(?)
SID		ends

;SID_REVISION		equ 1	; Current revision level
SID_MAX_SUB_AUTHORITIES	equ 15
SID_RECOMMENDED_SUB_AUTHORITIES equ 1	; Will change to around 6 in a future release.

SID_AND_ATTRIBUTES	struc
 saa_Sid	dd	?
 saa_Attributes	dd	?
SID_AND_ATTRIBUTES	ends


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
; ;
; Universal well-known SIDs ;
; ;
; Null SID S-1-0-0;
; WorldS-1-1-0;
; LocalS-1-2-0;
; Creator Owner ID S-1-3-0;
; Creator Group ID S-1-3-1;
; Creator Owner Server IDS-1-3-2;
; Creator Group Server IDS-1-3-3;
; ;
; (Non-unique IDs) S-1-4;
; ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

SECURITY_NULL_SID_AUTHORITY	equ 0
SECURITY_WORLD_SID_AUTHORITY	equ 1
SECURITY_LOCAL_SID_AUTHORITY	equ 2
SECURITY_CREATOR_SID_AUTHORITY	equ 3
SECURITY_NON_UNIQUE_AUTHORITY	equ 4
SECURITY_NULL_RID 	equ 0
SECURITY_WORLD_RID	equ 0
SECURITY_LOCAL_RID	equ 0
SECURITY_CREATOR_OWNER_RID	equ 0
SECURITY_CREATOR_GROUP_RID	equ 1
SECURITY_CREATOR_OWNER_SERVER_RID 	equ 2
SECURITY_CREATOR_GROUP_SERVER_RID 	equ 3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
; ;
; NT well-known SIDs;
; ;
; NT AuthorityS-1-5 ;
; DialupS-1-5-1 ;
; ;
; Network S-1-5-2 ;
; Batch S-1-5-3 ;
; Interactive S-1-5-4 ;
; Service S-1-5-6 ;
; AnonymousLogonS-1-5-7 (aka null logon session);
; Proxy S-1-5-8 ;
; ServerLogon S-1-5-8 (aka domain controller account) ;
; ;
; (Logon IDs) S-1-5-5-X-Y ;
; ;
; (NT non-unique IDs) S-1-5-0x15-...;
; ;
; (Built-in domain) s-1-5-0x20;
; ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

SECURITY_DIALUP_RID	equ 00000001h
SECURITY_NETWORK_RID	equ 00000002h
SECURITY_BATCH_RID	equ 00000003h
SECURITY_INTERACTIVE_RID	equ 00000004h
SECURITY_SERVICE_RID	equ 00000006h
SECURITY_ANONYMOUS_LOGON_RID	equ 00000007h
SECURITY_PROXY_RID	equ 00000008h
SECURITY_SERVER_LOGON_RID 	equ 00000009h
SECURITY_LOGON_IDS_RID	equ 00000005h
SECURITY_LOGON_IDS_RID_COUNT	equ 3h
SECURITY_LOCAL_SYSTEM_RID 	equ 00000012h
SECURITY_NT_NON_UNIQUE	equ 00000015h
SECURITY_BUILTIN_DOMAIN_RID 	equ 00000020h

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/
; ;
; well-known domain relative sub-authority values (RIDs)... ;
; ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;/

; Well-known users ...

DOMAIN_USER_RID_ADMIN	equ 000001F4h
DOMAIN_USER_RID_GUEST	equ 000001F5h

; well-known groups ...

DOMAIN_GROUP_RID_ADMINS	equ 00000200h
DOMAIN_GROUP_RID_USERS 	equ 00000201h
DOMAIN_GROUP_RID_GUESTS	equ 00000202h

; well-known aliases ...

DOMAIN_ALIAS_RID_ADMINS	equ 00000220h
DOMAIN_ALIAS_RID_USERS 	equ 00000221h
DOMAIN_ALIAS_RID_GUESTS	equ 00000222h
DOMAIN_ALIAS_RID_POWER_USERS 	equ 00000223h
DOMAIN_ALIAS_RID_ACCOUNT_OPS 	equ 00000224h
DOMAIN_ALIAS_RID_SYSTEM_OPS	equ 00000225h
DOMAIN_ALIAS_RID_PRINT_OPS 	equ 00000226h
DOMAIN_ALIAS_RID_BACKUP_OPS	equ 00000227h
DOMAIN_ALIAS_RID_REPLICATOR	equ 00000228h

;
; Allocate the System Luid.The first 1000 LUIDs are reserved.
; Use 999 here (0x3E7 = 999)
;

SYSTEM_LUID	equ	3E70000h

; end_ntifs

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;User and Group related SID attributes ;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; Group attributes
;

SE_GROUP_MANDATORY	equ 00000001h
SE_GROUP_ENABLED_BY_DEFAULT 	equ 00000002h
SE_GROUP_ENABLED	equ 00000004h
SE_GROUP_OWNER		equ 00000008h
SE_GROUP_LOGON_ID 	equ 0C0000000h

;
; User attributes
;

; (None yet defined.)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; ACLandACE;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
;Define an ACL and the ACE format.The structure of an ACL header
;followed by one or more ACEs.Pictorally the structure of an ACL header
;is as follows:
;
; 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
; 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+-------------------------------+---------------+---------------+
;+AclSize+Sbz1 +AclRevision+
;+-------------------------------+---------------+---------------+
;+Sbz2 + AceCount+
;+-------------------------------+-------------------------------+
;
;The current AclRevision is defined to be ACL_REVISION.
;
;AclSize is the size, in bytes, allocated for the ACL.This includes
;the ACL header, ACES, and remaining free space in the buffer.
;
;AceCount is the number of ACES in the ACL.
;

; begin_ntddk begin_ntifs
; This is the *current* ACL revision

ACL_REVISION 	equ 2

; This is the history of ACL revisions.Add a new one whenever
; ACL_REVISION is updated

ACL_REVISION1	equ 1
ACL_REVISION2	equ 2
ACL_REVISION3	equ 3

ACL	struc
 acl_AclRevision	db	?
 acl_Sbz1	db	?
 acl_AclSize	dw	?
 acl_AceCount	dw	?
 acl_Sbz2	dw	?
ACL	ends

; end_ntddk

;
;The structure of an ACE is a common ace header followed by ace type
;specific data.Pictorally the structure of the common ace header is
;as follows:
;
; 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
; 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+---------------+-------+-------+---------------+---------------+
;+AceSize+AceFlags + AceType +
;+---------------+-------+-------+---------------+---------------+
;
;AceType denotes the type of the ace, there are some predefined ace
;types
;
;AceSize is the size, in bytes, of ace.
;
;AceFlags are the Ace flags for audit and inheritance, defined shortly.

ACE_HEADER	struc
 ach_AceType	db	?
 ach_AceFlags	db	?
 ach_AceSize	dw	?
ACE_HEADER	ends

;
;The following are the predefined ace types that go into the AceType
;field of an Ace header.
;

ACCESS_ALLOWED_ACE_TYPE	equ 0
ACCESS_DENIED_ACE_TYPE 	equ 1
SYSTEM_AUDIT_ACE_TYPE	equ 2
SYSTEM_ALARM_ACE_TYPE	equ 3

;
;The following are the inherit flags that go into the AceFlags field
;of an Ace header.
;

OBJECT_INHERIT_ACE	equ 1
CONTAINER_INHERIT_ACE 	equ 2
NO_PROPAGATE_INHERIT_ACE	equ 4
INHERIT_ONLY_ACE	equ 8
VALID_INHERIT_FLAGS 	equ 15

;The following are the currently defined ACE flags that go into the
;AceFlags field of an ACE header.Each ACE type has its own set of
;AceFlags.
;
;SUCCESSFUL_ACCESS_ACE_FLAG - used only with system audit and alarm ACE
;types to indicate that a message is generated for successful accesses.
;
;FAILED_ACCESS_ACE_FLAG - used only with system audit and alarm ACE types
;to indicate that a message is generated for failed accesses.
;

;
;SYSTEM_AUDIT and SYSTEM_ALARM AceFlags
;
;These control the signaling of audit and alarms for success or failure.
;

SUCCESSFUL_ACCESS_ACE_FLAG 	equ 40h
FAILED_ACCESS_ACE_FLAG 	equ 80h

;
;We'll define the structure of the predefined ACE types.Pictorally
;the structure of the predefined ACE's is as follows:
;
; 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
; 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+---------------+-------+-------+---------------+---------------+
;+AceFlags + Resd+Inherit+AceSize+ AceType +
;+---------------+-------+-------+---------------+---------------+
;+Mask +
;+---------------------------------------------------------------+
;+ +
;+ +
;+ +
;+Sid+
;+ +
;+ +
;+ +
;+---------------------------------------------------------------+
;
;Mask is the access mask associated with the ACE.This is either the
;access allowed, access denied, audit, or alarm mask.
;
;Sid is the Sid associated with the ACE.
;

;The following are the four predefined ACE types.

;Examine the AceType field in the Header to determine
;which structure is appropriate to use for casting.

ACCESS_ALLOWED_ACE	struc
 aaa_Header	ACE_HEADER <?>
 aaa_Mask	dd	?
 aaa_SidStart	dd	?
ACCESS_ALLOWED_ACE	ends

ACCESS_DENIED_ACE	struc
 ada_Header	ACE_HEADER <?>
 ada_Mask	dd	?
 ada_SidStart	dd	?
ACCESS_DENIED_ACE	ends

SYSTEM_AUDIT_ACE	struc
 saa_Header	ACE_HEADER <?>
 saa_Mask	dd	?
 saa_SidStart	dd	?
SYSTEM_AUDIT_ACE	ends

SYSTEM_ALARM_ACE	struc
 sal_Header	ACE_HEADER <?>
 sal_Mask	dd	?
 sal_SidStart	dd	?
SYSTEM_ALARM_ACE	ends

; end_ntifs

;
;The following declarations are used for setting and querying information
;about and ACL.First are the various information classes available to
;the user.
;

;
;This record is returned/sent if the user is requesting/setting the
;AclRevisionInformation
;

ACL_REVISION_INFORMATION	struc
 ari_AclRevision	dd	?
ACL_REVISION_INFORMATION	ends

;
;This record is returned if the user is requesting AclSizeInformation
;

ACL_SIZE_INFORMATION	struc
 asi_AceCount	dd	?
 asi_AclBytesInUse	dd	?
 asi_AclBytesFree	dd	?
ACL_SIZE_INFORMATION	ends


; SECURITY_DESCRIPTOR;

SECURITY_DESCRIPTOR_REVISION	equ	1
SECURITY_DESCRIPTOR_REVISION1	equ	1

SECURITY_DESCRIPTOR_MIN_LENGTH	equ	20	; sizeof(SECURITY_DESCRIPTOR

SE_OWNER_DEFAULTED 	equ 0001h
SE_GROUP_DEFAULTED 	equ 0002h
SE_DACL_PRESENT		equ 0004h
SE_DACL_DEFAULTED	equ 0008h
SE_SACL_PRESENT		equ 0010h
SE_SACL_DEFAULTED	equ 0020h
SE_SELF_RELATIVE 	equ 8000h

SECURITY_DESCRIPTOR	struc
 sec_Revision		db	?
 sec_Sbz1		db	?
 sec_Control		dw	?
 sec_Owner		dd	?
 sec_Group		dd	?
 sec_Sacl		dd	?
 sec_Dacl		dd	?
SECURITY_DESCRIPTOR	ends

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; Privilege Related Data Structures;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; begin_ntddk begin_nthal begin_ntifs
;
; Privilege attributes
;

SE_PRIVILEGE_ENABLED_BY_DEFAULT 	equ 00000001h
SE_PRIVILEGE_ENABLED	equ 00000002h
SE_PRIVILEGE_USED_FOR_ACCESS	equ 80000000h

;
; Privilege Set Control flags
;

PRIVILEGE_SET_ALL_NECESSARY	equ 1

;
;Privilege Set - This is defined for a privilege set of one.
;If more than one privilege is needed, then this structure
;will need to be allocated with more space.
;
;Note: don't change this structure without fixing the INITIAL_PRIVILEGE_SET
;structure (defined in se.h)
;


PRIVILEGE_SET	struc
 pset_PrivilegeCount	dd	?
 pset_Control	dd	?
 pset_Privilege	LUID_AND_ATTRIBUTES	<?>
PRIVILEGE_SET	ends


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; NT Defined Privileges;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

SE_CREATE_TOKEN_NAME	equ "SeCreateTokenPrivilege"
SE_ASSIGNPRIMARYTOKEN_NAME	equ "SeAssignPrimaryTokenPrivilege"
SE_LOCK_MEMORY_NAME 	equ "SeLockMemoryPrivilege"
SE_INCREASE_QUOTA_NAME	equ "SeIncreaseQuotaPrivilege"
SE_UNSOLICITED_INPUT_NAME 	equ "SeUnsolicitedInputPrivilege"
SE_MACHINE_ACCOUNT_NAME 	equ "SeMachineAccountPrivilege"
SE_TCB_NAME 		equ "SeTcbPrivilege"
SE_SECURITY_NAME	equ "SeSecurityPrivilege"
SE_TAKE_OWNERSHIP_NAME	equ "SeTakeOwnershipPrivilege"
SE_LOAD_DRIVER_NAME 	equ "SeLoadDriverPrivilege"
SE_SYSTEM_PROFILE_NAME	equ "SeSystemProfilePrivilege"
SE_SYSTEMTIME_NAME	equ "SeSystemtimePrivilege"
SE_PROF_SINGLE_PROCESS_NAME 	equ "SeProfileSingleProcessPrivilege"
SE_INC_BASE_PRIORITY_NAME 	equ "SeIncreaseBasePriorityPrivilege"
SE_CREATE_PAGEFILE_NAME 	equ "SeCreatePagefilePrivilege"
SE_CREATE_PERMANENT_NAME	equ "SeCreatePermanentPrivilege"
SE_BACKUP_NAME		equ "SeBackupPrivilege"
SE_RESTORE_NAME 	equ "SeRestorePrivilege"
SE_SHUTDOWN_NAME	equ "SeShutdownPrivilege"
SE_DEBUG_NAME 		equ "SeDebugPrivilege"
SE_AUDIT_NAME 		equ "SeAuditPrivilege"
SE_SYSTEM_ENVIRONMENT_NAME	equ "SeSystemEnvironmentPrivilege"
SE_CHANGE_NOTIFY_NAME 	equ "SeChangeNotifyPrivilege"
SE_REMOTE_SHUTDOWN_NAME 	equ "SeRemoteShutdownPrivilege"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; Security Quality Of Service;
;;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; begin_ntddk begin_nthal begin_ntifs
;
; Impersonation Level
;
; Impersonation level is represented by a pair of bits in Windows.
; If a new impersonation level is added or lowest value is changed from
; 0 to something else, fix the Windows CreateFile call.
;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
; Token Object Definitions ;
;;
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
; Token Specific Access Rights.
;

TOKEN_ASSIGN_PRIMARY	equ	0001h
TOKEN_DUPLICATE 	equ	0002h
TOKEN_IMPERSONATE 	equ	0004h
TOKEN_QUERY 		equ	0008h
TOKEN_QUERY_SOURCE	equ	0010h
TOKEN_ADJUST_PRIVILEGES 	equ	0020h
TOKEN_ADJUST_GROUPS 	equ	0040h
TOKEN_ADJUST_DEFAULT	equ	0080h

TOKEN_ALL_ACCESS	equ	STANDARD_RIGHTS_REQUIRED OR TOKEN_ASSIGN_PRIMARY OR TOKEN_DUPLICATE OR TOKEN_IMPERSONATE OR TOKEN_QUERY OR TOKEN_QUERY_SOURCE OR TOKEN_ADJUST_PRIVILEGES OR TOKEN_ADJUST_GROUPS OR TOKEN_ADJUST_DEFAULT
TOKEN_READ		equ	STANDARD_RIGHTS_READ OR TOKEN_QUERY
TOKEN_WRITE		equ	STANDARD_RIGHTS_WRITE OR TOKEN_ADJUST_PRIVILEGES OR TOKEN_ADJUST_GROUPS OR TOKEN_ADJUST_DEFAULT
TOKEN_EXECUTE		equ	STANDARD_RIGHTS_EXECUTE

;
;
; Token Types
;

TokenPrimary		equ	1
TokenImpersonation	equ	2

;
; Token Information Classes.
;

TokenUser		equ	1
TokenGroups		equ	2
TokenPrivileges		equ	3
TokenOwner		equ	4
TokenPrimaryGroup		equ	5
TokenDefaultDacl		equ	6
TokenSource		equ	7
TokenType		equ	8
TokenImpersonationLevel	equ	9
TokenStatistics		equ	10
TokenRestrictedSids	equ	11
TokenSessionId		equ	12
TokenGroupsAndPrivileges	equ	13
TokenSessionReference	equ	14
TokenSandBoxInert	equ	15
TokenAuditPolicy		equ	16
TokenOrigin		equ	17
MaxTokenInfoClass 	equ	18

;
; Token information class structures
;


TOKEN_USER		struc
 tku_User		SID_AND_ATTRIBUTES <?>
TOKEN_USER		ends

; begin_ntifs

TOKEN_GROUPS		struc
 tkg_GroupCount		dd	?
 tkg_Groups		SID_AND_ATTRIBUTES <?>
TOKEN_GROUPS		ends

TOKEN_PRIVILEGES	struc
 tkp_PrivilegeCount		dd	?
 tkp_Privileges		LUID_AND_ATTRIBUTES	<?>
TOKEN_PRIVILEGES	ends

; end_ntifs

TOKEN_OWNER	struc
 tko_Owner	dd	?
TOKEN_OWNER	ends


TOKEN_PRIMARY_GROUP	struc
 tpg_PrimaryGroup	dd	?
TOKEN_PRIMARY_GROUP	ends


TOKEN_DEFAULT_DACL	struc
 tdd_DefaultDacl	dd	?
TOKEN_DEFAULT_DACL	ends

TOKEN_SOURCE_LENGTH	equ 8

TOKEN_SOURCE	struc
 tks_SourceName	db	TOKEN_SOURCE_LENGTH dup(?)
 tks_SourceIdentifier	LUID <?>
TOKEN_SOURCE	ends

; end_ntifs


TOKEN_STATISTICS	struc
 tkst_TokenId		LUID <?>
 tkst_AuthenticationId	LUID <?>
 tkst_ExpirationTime	dd	?, ?
 tkst_TokenType		TOKEN_TYPE <?>
 tkst_ImpersonationLevel	SECURITY_IMPERSONATION_LEVEL <?>
 tkst_DynamicCharged	dd	?
 tkst_DynamicAvailable	dd	?
 tkst_GroupCount	dd	?
 tkst_PrivilegeCount	dd	?
 tkst_ModifiedId		LUID <?>
TOKEN_STATISTICS	ends


; begin_ntifs

TOKEN_CONTROL		struc
 tkc_TokenId		LUID <?>
 tkc_AuthenticationId	LUID <?>
 tkc_ModifiedId		LUID <?>
 tkc_TokenSource		TOKEN_SOURCE <?>
TOKEN_CONTROL		ends

;
; Security Tracking Mode
;

SECURITY_DYNAMIC_TRACKING	equ TRUE
SECURITY_STATIC_TRACKING	equ FALSE

;
; Quality Of Service
;

SECURITY_QUALITY_OF_SERVICE	struc
 sqos_Length		dd	?
 sqos_ImpersonationLevel	SECURITY_IMPERSONATION_LEVEL <?>
 sqos_ContextTrackingMode	SECURITY_CONTEXT_TRACKING_MODE <?>
 sqos_EffectiveOnly	dd	?
SECURITY_QUALITY_OF_SERVICE	ends

;
; Used to represent information related to a thread impersonation
;

SE_IMPERSONATION_STATE	struc
 sis_Token		PACCESS_TOKEN	<?>
 sis_CopyOnOpen		dd	?
 sis_EffectiveOnly		dd	?
 sis_Level		SECURITY_IMPERSONATION_LEVEL	<?>
SE_IMPERSONATION_STATE	ends

OWNER_SECURITY_INFORMATION 	equ 00000001h
GROUP_SECURITY_INFORMATION 	equ 00000002h
DACL_SECURITY_INFORMATION	equ 00000004h
SACL_SECURITY_INFORMATION	equ 00000008h

;
; Image Format
;

IMAGE_DOS_SIGNATURE 	equ 5A4Dh	; MZ
IMAGE_OS2_SIGNATURE 	equ 454Eh	; NE
IMAGE_OS2_SIGNATURE_LE	equ 454Ch	; LE
IMAGE_VXD_SIGNATURE 	equ 454Ch	; LE
IMAGE_NT_SIGNATURE	equ 00004550h	; PE00

IMAGE_DOS_HEADER	struc	; DOS .EXE header
 e_magic	dw	?	; Magic number
 e_cblp	dw	?	; Bytes on last page of file
 e_cp	dw	?	; Pages in file
 e_crlc	dw	?	; Relocations
 e_cparhdr	dw	?	; Size of header in paragraphs
 e_minalloc	dw	?	; Minimum extra paragraphs needed
 e_maxalloc	dw	?	; Maximum extra paragraphs needed
 e_ss	dw	?	; Initial (relative) SS value
 e_sp	dw	?	; Initial SP value
 e_csum	dw	?	; Checksum
 e_ip	dw	?	; Initial IP value
 e_cs	dw	?	; Initial (relative) CS value
 e_lfarlc	dw	?	; File address of relocation table
 e_ovno	dw	?	; Overlay number
 e_res	dw	?, ?, ?, ?	; Reserved s
 e_oemid	dw	?	; OEM identifier (for e_oeminfo)
 e_oeminfo	dw	?	; OEM information; e_oemid specific
 e_res2	dw	10 dup(?)	; Reserved words
 e_lfanew	dd	?	; File address of new exe header
IMAGE_DOS_HEADER	ends

IMAGE_OS2_HEADER	struc	; OS/2 .EXE header
 ne_magic	dw	?	; Magic number
 ne_ver	db	?	; Version number
 ne_rev	db	?	; Revision number
 ne_enttab	dw	?	; Offset of Entry Table
 ne_cbenttab	dw	?	; Number of bytes in Entry Table
 ne_crc	dd	?	; Checksum of whole file
 ne_flags	dw	?	; Flag 
 ne_autodata	dw	?	; Automatic data segment number
 ne_heap	dw	?	; Initial heap allocation
 ne_stack	dw	?	; Initial stack allocation
 ne_csip	dd	?	; Initial CS:IP setting
 ne_sssp	dd	?	; Initial SS:SP setting
 ne_cseg	dw	?	; Count of file segments
 ne_cmod	dw	?	; Entries in Module Reference Table
 ne_cbnrestab	dw	?	; Size of non-resident name table
 ne_segtab	dw	?	; Offset of Segment Table
 ne_rsrctab	dw	?	; Offset of Resource Table
 ne_restab	dw	?	; Offset of resident name table
 ne_modtab	dw	?	; Offset of Module Reference Table
 ne_imptab	dw	?	; Offset of Imported Names Table
 ne_nrestab	dd	?	; Offset of Non-resident Names Table
 ne_cmovent	dw	?	; Count of movable entries
 ne_align	dw	?	; Segment alignment shift count
 ne_cres	dw	?	; Count of resource segments
 ne_exetyp	db	?	; Target Operating system
 ne_flagsothers	db	?	; Other .EXE flags
 ne_pretthunks	dw	?	; offset to return thunks
 ne_psegrefbytes	dw	?	; offset to segment ref. bytes
 ne_swaparea	dw	?	; Minimum code swap area size
 ne_expver	dw	?	; Expected Windows version number
IMAGE_OS2_HEADER	ends

IMAGE_VXD_HEADER	struc	; Windows VXD header
 e32_magic	dw	?	; Magic number
 e32_border	db	?	; The byte ordering for the VXD
 e32_worder	db	?	; The word ordering for the VXD
 e32_level	dd	?	; The EXE format level for now = 0
 e32_cpu	dw	?	; The CPU type
 e32_os	dw	?	; The OS type
 e32_ver	dd	?	; Module version
 e32_mflags	dd	?	; Module flags
 e32_mpages	dd	?	; Module pages
 e32_startobj	dd	?	; Object for instruction pointer
 e32_eip	dd	?	; Extended instruction pointer
 e32_stackobj	dd	?	; Object for stack pointer
 e32_esp	dd	?	; Extended stack pointer
 e32_pagesize	dd	?	; VXD page size
 e32_lastpagesize	dd	?	; Last page size in VXD
 e32_fixupsize	dd	?	; Fixup section size
 e32_fixupsum	dd	?	; Fixup section checksum
 e32_ldrsize	dd	?	; Loader section size
 e32_ldrsum	dd	?	; Loader section checksum
 e32_objtab	dd	?	; Object table offset
 e32_objcnt	dd	?	; Number of objects in module
 e32_objmap	dd	?	; Object page map offset
 e32_itermap	dd	?	; Object iterated data map offset
 e32_rsrctab	dd	?	; Offset of Resource Table
 e32_rsrccnt	dd	?	; Number of resource entries
 e32_restab	dd	?	; Offset of resident name table
 e32_enttab	dd	?	; Offset of Entry Table
 e32_dirtab	dd	?	; Offset of Module Directive Table
 e32_dircnt	dd	?	; Number of module directives
 e32_fpagetab	dd	?	; Offset of Fixup Page Table
 e32_frectab	dd	?	; Offset of Fixup Record Table
 e32_impmod	dd	?	; Offset of Import Module Name Table
 e32_impmodcnt	dd	?	; Number of entries in Import Module Name Table
 e32_impproc	dd	?	; Offset of Import Procedure Name Table
 e32_pagesum	dd	?	; Offset of Per-Page Checksum Table
 e32_datapage	dd	?	; Offset of Enumerated Data Pages
 e32_preload	dd	?	; Number of preload pages
 e32_nrestab	dd	?	; Offset of Non-resident Names Table
 e32_cbnrestab	dd	?	; Size of Non-resident Name Table
 e32_nressum	dd	?	; Non-resident Name Table Checksum
 e32_autodata	dd	?	; Object for automatic data object
 e32_debuginfo	dd	?	; Offset of the debugging information
 e32_debuglen	dd	?	; The length of the debugging info. in bytes
 e32_instpreload	dd	?	; Number of instance pages in preload section of VXD file
 e32_instdemand	dd	?	; Number of instance pages in demand load section of VXD file
 e32_heapsize	dd	?	; Size of heap - for 16-bit apps
 e32_res3	db	12 dup(?)	; Reserved words
 e32_winresoff	dd	?
 e32_winreslen	dd	?
 e32_devid	dw	?	; Device ID for VxD
 e32_ddkver	dw	?	; DDK version for VxD
IMAGE_VXD_HEADER	ends

;
; File header format.
;

IMAGE_FILE_HEADER	struc
 ifh_Machine		dw	?	
 ifh_NumberOfSections	dw	?	
 ifh_TimeDateStamp		dd	?	
 ifh_PointerToSymbolTable	dd	?	
 ifh_NumberOfSymbols	dd	?	
 ifh_SizeOfOptionalHeader	dw	?	
 ifh_Characteristics		dw	?	
IMAGE_FILE_HEADER	ends

IMAGE_SIZEOF_FILE_HEADER	equ 20

IMAGE_FILE_RELOCS_STRIPPED 	equ 0001h	; Relocation info stripped from file.
IMAGE_FILE_EXECUTABLE_IMAGE	equ 0002h	; File is executable(i.e. no unresolved externel references).
IMAGE_FILE_LINE_NUMS_STRIPPED	equ 0004h	; Line nunbers stripped from file.
IMAGE_FILE_LOCAL_SYMS_STRIPPED 	equ 0008h	; Local symbols stripped from file.
IMAGE_FILE_AGGRESIVE_WS_TRIM 	equ 0010h	; Agressively trim working set
IMAGE_FILE_BYTES_REVERSED_LO 	equ 0080h	; Bytes of machine word are reversed.
IMAGE_FILE_32BIT_MACHINE 	equ 0100h	; 32 bit word machine.
IMAGE_FILE_DEBUG_STRIPPED	equ 0200h	; Debugging info stripped from file in .DBG file
IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP 	equ 0400h	; If Image is on removable media, copy and run from the swap file.
IMAGE_FILE_NET_RUN_FROM_SWAP 	equ 0800h	; If Image is on Net, copy and run from the swap file.
IMAGE_FILE_SYSTEM	equ 1000h	; System File.
IMAGE_FILE_DLL 		equ 2000h	; File is a DLL.
IMAGE_FILE_UP_SYSTEM_ONLY	equ 4000h	; File should only be run on a UP machine
IMAGE_FILE_BYTES_REVERSED_HI 	equ 8000h	; Bytes of machine word are reversed.

IMAGE_FILE_MACHINE_UNKNOWN	equ 0
IMAGE_FILE_MACHINE_I386	equ 14ch	; Intel 386.
IMAGE_FILE_MACHINE_R3000 	equ 162h	; MIPS little-endian, 0x160 big-endian
IMAGE_FILE_MACHINE_R4000 	equ 166h	; MIPS little-endian
IMAGE_FILE_MACHINE_R10000	equ 168h	; MIPS little-endian
IMAGE_FILE_MACHINE_ALPHA 	equ 184h	; Alpha_AXP
IMAGE_FILE_MACHINE_POWERPC 	equ 1F0h	; IBM PowerPC Little-Endian

;
; Directory format.
;

IMAGE_DATA_DIRECTORY	struc
 idd_VirtualAddress		dd	?
 idd_Size		dd	?
IMAGE_DATA_DIRECTORY	ends

IMAGE_NUMBEROF_DIRECTORY_ENTRIES	equ	16

;
; Optional header format.
;

IMAGE_OPTIONAL_HEADER	struc

;
; Standard fields.
;

 ioh_Magic		dw	?	
 ioh_MajorLinkerVersion	db	?	
 ioh_MinorLinkerVersion	db	?	
 ioh_SizeOfCode		dd	?	
 ioh_SizeOfInitializedData	dd	?	
 ioh_SizeOfUninitializedData	dd	?	
 ioh_AddressOfEntryPoint	dd	?	
 ioh_BaseOfCode		dd	?	
 ioh_BaseOfData		dd	?	

;
; NT additional fields.
;

 ioh_ImageBase		dd	?	
 ioh_SectionAlignment	dd	?	
 ioh_FileAlignment		dd	?	
 ioh_MajorOperatingSystemVersion	dw	?	
 ioh_MinorOperatingSystemVersion	dw	?	
 ioh_MajorImageVersion	dw	?	
 ioh_MinorImageVersion	dw	?	
 ioh_MajorSubsystemVersion	dw	?	
 ioh_MinorSubsystemVersion	dw	?	
 ioh_Win32VersionValue	dd	?	
 ioh_SizeOfImage		dd	?	
 ioh_SizeOfHeaders		dd	?	
 ioh_CheckSum		dd	?	
 ioh_Subsystem		dw	?	
 ioh_DllCharacteristics	dw	?	
 ioh_SizeOfStackReserve	dd	?	
 ioh_SizeOfStackCommit	dd	?	
 ioh_SizeOfHeapReserve	dd	?	
 ioh_SizeOfHeapCommit	dd	?	
 ioh_LoaderFlags		dd	?	
 ioh_NumberOfRvaAndSizes	dd	?	
 ioh_DataDirectory	 	IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>

 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>

	 	IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>

 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
 		IMAGE_DATA_DIRECTORY	<?>
IMAGE_OPTIONAL_HEADER	ends

IMAGE_ROM_OPTIONAL_HEADER	struc
 iroh_Magic		dw	?	
 iroh_MajorLinkerVersion	dd	?	
 iroh_MinorLinkerVersion	dd	?	
 iroh_SizeOfCode		dd	?	
 iroh_SizeOfInitializedData	dd	?	
 iroh_SizeOfUninitializedData	dd	?	
 iroh_AddressOfEntryPoint	dd	?	
 iroh_BaseOfCode		dd	?	
 iroh_BaseOfData		dd	?	
 iroh_BaseOfBss		dd	?	
 iroh_GprMask		dd	?	
 iroh_CprMask		dd	?, ?, ?, ?
 iroh_GpValue		dd	?	
IMAGE_ROM_OPTIONAL_HEADER	ends

IMAGE_SIZEOF_ROM_OPTIONAL_HEADER	equ 56
IMAGE_SIZEOF_STD_OPTIONAL_HEADER	equ 28
IMAGE_SIZEOF_NT_OPTIONAL_HEADER	equ 224

IMAGE_NT_OPTIONAL_HDR_MAGIC		equ 10bh
IMAGE_ROM_OPTIONAL_HDR_MAGIC 		equ 107h

IMAGE_NT_HEADERS	struc
 inth_Signature		dd		?	
 inth_FileHeader		IMAGE_FILE_HEADER	<?>
 inth_OptionalHeader	IMAGE_OPTIONAL_HEADER	<?>
IMAGE_NT_HEADERS	ends

IMAGE_ROM_HEADERS	struc
 irh_FileHeader		IMAGE_FILE_HEADER	<?>
 irh_OptionalHeader	IMAGE_ROM_OPTIONAL_HEADER	<?>
IMAGE_ROM_HEADERS	ends

;IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)(ntheader + FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader ) +  ((PIMAGE_NT_HEADERS)(ntheader))->FileHeader.SizeOfOptionalHeader ))


; Subsystem Values

IMAGE_SUBSYSTEM_UNKNOWN	equ 0 ; Unknown subsystem.
IMAGE_SUBSYSTEM_NATIVE	equ 1 ; Image doesn't require a subsystem.
IMAGE_SUBSYSTEM_WINDOWS_GUI	equ 2 ; Image runs in the Windows GUI subsystem.
IMAGE_SUBSYSTEM_WINDOWS_CUI	equ 3 ; Image runs in the Windows character subsystem.
IMAGE_SUBSYSTEM_OS2_CUI	equ 5 ; image runs in the OS/2 character subsystem.
IMAGE_SUBSYSTEM_POSIX_CUI	equ 7 ; image runin the Posix character subsystem.
IMAGE_SUBSYSTEM_RESERVED8	equ 8 ; image runin the 8 subsystem.

; Directory Entries

IMAGE_DIRECTORY_ENTRY_EXPORT		equ 0 ; Export Directory
IMAGE_DIRECTORY_ENTRY_IMPORT		equ 1 ; Import Directory
IMAGE_DIRECTORY_ENTRY_RESOURCE		equ 2 ; Resource Directory
IMAGE_DIRECTORY_ENTRY_EXCEPTION	equ 3 ; Exception Directory
IMAGE_DIRECTORY_ENTRY_SECURITY		equ 4 ; Security Directory
IMAGE_DIRECTORY_ENTRY_BASERELOC	equ 5 ; Base Relocation Table
IMAGE_DIRECTORY_ENTRY_DEBUG		equ 6 ; Debug Directory
IMAGE_DIRECTORY_ENTRY_COPYRIGHT	equ 7 ; Description String
IMAGE_DIRECTORY_ENTRY_GLOBALPTR	equ 8 ; Machine Value (MIPS GP)
IMAGE_DIRECTORY_ENTRY_TLS		equ 9 ; TLS Directory
IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	equ 10 ; Load Configuration Directory
IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	equ 11 ; Bound Import Directory in headers
IMAGE_DIRECTORY_ENTRY_IAT		equ 12 ; Import Address Table

;
; Section header format.
;

IMAGE_SIZEOF_SHORT_NAME	equ	8

IMAGE_SECTION_HEADER	struc
 ish_Name		db	IMAGE_SIZEOF_SHORT_NAME dup(?)
 ish_PhysicalAddress	dd	?
 ish_VirtualSize		equ	ish_PhysicalAddress
 ish_VirtualAddress		dd	?
 ish_SizeOfRawData		dd	?
 ish_PointerToRawData	dd	?
 ish_PointerToRelocations	dd	?
 ish_PointerToLinenumbers	dd	?
 ish_NumberOfRelocations	dw	?
 ish_NumberOfLinenumbers	dw	?
 ish_Characteristics		dd	?
IMAGE_SECTION_HEADER	ends

IMAGE_SIZEOF_SECTION_HEADER	equ 40

;
; Section characteristics.
;

IMAGE_SCN_TYPE_NO_PAD	equ 00000008h; Reserved.
IMAGE_SCN_CNT_CODE 	equ 00000020h; Section contains code.
IMAGE_SCN_CNT_INITIALIZED_DATA 	equ 00000040h; Section contains initialized data.
IMAGE_SCN_CNT_UNINITIALIZED_DATA 	equ 00000080h; Section contains uninitialized data.
IMAGE_SCN_LNK_OTHER	equ 00000100h; Reserved.
IMAGE_SCN_LNK_INFO 	equ 00000200h; Section contains comments or some other type of information.
IMAGE_SCN_LNK_REMOVE 	equ 00000800h; Section contents will not become part of image.
IMAGE_SCN_LNK_COMDAT 	equ 00001000h; Section contents comdat.
IMAGE_SCN_MEM_FARDATA	equ 00008000h
IMAGE_SCN_MEM_PURGEABLE	equ 00020000h
IMAGE_SCN_MEM_16BIT	equ 00020000h
IMAGE_SCN_MEM_LOCKED 	equ 00040000h
IMAGE_SCN_MEM_PRELOAD	equ 00080000h
IMAGE_SCN_ALIGN_1BYTES 	equ 00100000h
IMAGE_SCN_ALIGN_2BYTES 	equ 00200000h
IMAGE_SCN_ALIGN_4BYTES 	equ 00300000h
IMAGE_SCN_ALIGN_8BYTES 	equ 00400000h
IMAGE_SCN_ALIGN_16BYTES	equ 00500000h	; Default alignment if no others are specified.
IMAGE_SCN_ALIGN_32BYTES	equ 00600000h
IMAGE_SCN_ALIGN_64BYTES	equ 00700000h
IMAGE_SCN_LNK_NRELOC_OVFL	equ 01000000h	; Section contains extended relocations.
IMAGE_SCN_MEM_DISCARDABLE	equ 02000000h	; Section can be discarded.
IMAGE_SCN_MEM_NOT_CACHED 	equ 04000000h	; Section is not cachable.
IMAGE_SCN_MEM_NOT_PAGED	equ 08000000h	; Section is not pageable.
IMAGE_SCN_MEM_SHARED 	equ 10000000h	; Section is shareable.
IMAGE_SCN_MEM_EXECUTE	equ 20000000h	; Section is executable.
IMAGE_SCN_MEM_READ 	equ 40000000h	; Section is readable.
IMAGE_SCN_MEM_WRITE	equ 80000000h	; Section is writeable.

;
; TLS Chaacteristic Flags
;
IMAGE_SCN_SCALE_INDEX	equ 1	; Tls index is scaled

;
; Symbol format.
;

IMAGE_SYMBOL		struc
 isym_ShortName		db	8 dup(?)
 isym_Short		equ	isym_ShortName
 isym_Long		equ	isym_ShortName + 4

 isym_Value		dd	?
 isym_SectionNumber	dw	?
 isym_Type		dw	?
 isym_StorageClass	db	?
 isym_NumberOfAuxSymbols	db	?
IMAGE_SYMBOL		ends

IMAGE_SIZEOF_SYMBOL	equ 18

;
; Section values.
;
; Symbols have a section number of the section in which they are
; defined. Otherwise, section numbers have the following meanings:
;

IMAGE_SYM_UNDEFINED	equ 0	; Symbol is undefined or is common.
IMAGE_SYM_ABSOLUTE	equ -1	; Symbol is an absolute value.
IMAGE_SYM_DEBUG	equ -2	; Symbol is a special debug item.

;
; Type (fundamental) values.
;

IMAGE_SYM_TYPE_NULL 	equ 0000h	; no type.
IMAGE_SYM_TYPE_VOID 	equ 0001h	;
IMAGE_SYM_TYPE_CHAR 	equ 0002h	; type character.
IMAGE_SYM_TYPE_SHORT	equ 0003h	; type short integer.
IMAGE_SYM_TYPE_INT	equ 0004h	;
IMAGE_SYM_TYPE_LONG 	equ 0005h	;
IMAGE_SYM_TYPE_FLOAT	equ 0006h	;
IMAGE_SYM_TYPE_DOUBLE 	equ 0007h	;
IMAGE_SYM_TYPE_STRUCT 	equ 0008h	;
IMAGE_SYM_TYPE_UNION	equ 0009h	;
IMAGE_SYM_TYPE_ENUM 	equ 000Ah	; enumeration.
IMAGE_SYM_TYPE_MOE	equ 000Bh	; member of enumeration.
IMAGE_SYM_TYPE_BYTE 	equ 000Ch	;
IMAGE_SYM_TYPE_WORD 	equ 000Dh	;
IMAGE_SYM_TYPE_UINT 	equ 000Eh	;
IMAGE_SYM_TYPE_DWORD	equ 000Fh	;
IMAGE_SYM_TYPE_PCODE	equ 8000h	;

;
; Type (derived) values.
;

IMAGE_SYM_DTYPE_NULL	equ 0 ; no derived type.
IMAGE_SYM_DTYPE_POINTER	equ 1 ; pointer.
IMAGE_SYM_DTYPE_FUNCTION	equ 2 ; function.
IMAGE_SYM_DTYPE_ARRAY	equ 3 ; array.

;
; Storage classes.
;

IMAGE_SYM_CLASS_END_OF_FUNCTION	equ -1
IMAGE_SYM_CLASS_NULL		equ 0000h
IMAGE_SYM_CLASS_AUTOMATIC 		equ 0001h
IMAGE_SYM_CLASS_EXTERNAL		equ 0002h
IMAGE_SYM_CLASS_STATIC		equ 0003h
IMAGE_SYM_CLASS_REGISTER		equ 0004h
IMAGE_SYM_CLASS_EXTERNAL_DEF		equ 0005h
IMAGE_SYM_CLASS_LABEL 		equ 0006h
IMAGE_SYM_CLASS_UNDEFINED_LABEL 	equ 0007h
IMAGE_SYM_CLASS_MEMBER_OF_STRUCT	equ 0008h
IMAGE_SYM_CLASS_ARGUMENT		equ 0009h
IMAGE_SYM_CLASS_STRUCT_TAG		equ 000Ah
IMAGE_SYM_CLASS_MEMBER_OF_UNION 	equ 000Bh
IMAGE_SYM_CLASS_UNION_TAG 		equ 000Ch
IMAGE_SYM_CLASS_TYPE_DEFINITION 	equ 000Dh
IMAGE_SYM_CLASS_UNDEFINED_STATIC	equ 000Eh
IMAGE_SYM_CLASS_ENUM_TAG		equ 000Fh
IMAGE_SYM_CLASS_MEMBER_OF_ENUM	equ 0010h
IMAGE_SYM_CLASS_REGISTER_PARAM		equ 0011h
IMAGE_SYM_CLASS_BIT_FIELD 		equ 0012h
IMAGE_SYM_CLASS_FAR_EXTERNAL		equ 0044h
IMAGE_SYM_CLASS_BLOCK 		equ 0064h
IMAGE_SYM_CLASS_FUNCTION		equ 0065h
IMAGE_SYM_CLASS_END_OF_STRUCT 	equ 0066h
IMAGE_SYM_CLASS_FILE		equ 0067h
IMAGE_SYM_CLASS_SECTION 		equ 0068h
IMAGE_SYM_CLASS_WEAK_EXTERNAL 	equ 0069h

; type packing constants

N_BTMASK	equ 000Fh
N_TMASK 	equ 0030h
N_TMASK1	equ 00C0h
N_TMASK2	equ 00F0h
N_BTSHFT	equ 4
N_TSHIFT	equ 2

; MACROS

; Basic Type ofx
; BTYPE(x) ((x) & N_BTMASK)

; Is x a pointer?
; ISPTR(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_POINTER << N_BTSHFT))

; Is x a function?
; ISFCN(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_FUNCTION << N_BTSHFT))

; Is x an array?
; ISARY(x) (((x) & N_TMASK) == (IMAGE_SYM_DTYPE_ARRAY << N_BTSHFT))

; Is x a structure, union, or enumeration TAG?
; ISTAG(x) ((x)==IMAGE_SYM_CLASS_STRUCT_TAG ++ (x)==IMAGE_SYM_CLASS_UNION_TAG ++ (x)==IMAGE_SYM_CLASS_ENUM_TAG)
; INCREF(x) ((((x)&~N_BTMASK)<<N_TSHIFT)+(IMAGE_SYM_DTYPE_POINTER<<N_BTSHFT)+((x)&N_BTMASK))
; DECREF(x) ((((x)>>N_TSHIFT)&~N_BTMASK)+((x)&N_BTMASK))

;
; Auxiliary entry format.
;

IMAGE_AUX_SYMBOL	ends
    struct {
  ias_TagIndex		dd	?	; struct, union, or enum tag index
  ias_TotalSize		dd	?
  ias_Linenumber		equ	ias_TotalSize
  ias_Size		equ	ias_TotalSize + 2

  ias_PointerToLinenumber	dd	?
  ias_PointerToNextFunction	dd	?
  ias_Dimension		equ	ias_PointerToLinenumber
  ias_TvIndex		dw	?	; tv index
    } Sym;
    struct {
        BYTE    Name[IMAGE_SIZEOF_SYMBOL];
    } File;
    struct {
        DWORD   Length;                         // section length
        WORD    NumberOfRelocations;            // number of relocation entries
        WORD    NumberOfLinenumbers;            // number of line numbers
        DWORD   CheckSum;                       // checksum for communal
        SHORT   Number;                         // section number to associate with
        BYTE    Selection;                      // communal selection type
    } Section;
IMAGE_AUX_SYMBOL	ends

IMAGE_SIZEOF_AUX_SYMBOL	equ 18

;
; Communal selection types.
;

IMAGE_COMDAT_SELECT_NODUPLICATES	equ 1
IMAGE_COMDAT_SELECT_ANY		equ 2
IMAGE_COMDAT_SELECT_SAME_SIZE		equ 3
IMAGE_COMDAT_SELECT_EXACT_MATCH	equ 4
IMAGE_COMDAT_SELECT_ASSOCIATIVE	equ 5
IMAGE_COMDAT_SELECT_LARGEST		equ 6
IMAGE_COMDAT_SELECT_NEWEST		equ 7

IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY	equ 1
IMAGE_WEAK_EXTERN_SEARCH_LIBRARY	equ 2
IMAGE_WEAK_EXTERN_SEARCH_ALIAS		equ 3

;
; Relocation format.
;

IMAGE_RELOCATION	struc
 irl_VirtualAddress		dd	?
 irl_RelocCount		equ	irl_VirtualAddress	; Set to the real count when IMAGE_SCN_LNK_NRELOC_OVFL is set
 irl_SymbolTableIndex	dd	?
 irl_Type		dw	?
IMAGE_RELOCATION	ends

IMAGE_SIZEOF_RELOCATION	equ 10

;
; I386 relocation types.
;

IMAGE_REL_I386_ABSOLUTE 	equ 0000h	; Reference is absolute, no relocation is necessary
IMAGE_REL_I386_DIR16	equ 0001h	; Direct 16-bit reference to the symbols virtual address
IMAGE_REL_I386_REL16	equ 0002h	; PC-relative 16-bit reference to the symbols virtual address
IMAGE_REL_I386_DIR32	equ 0006h	; Direct 32-bit reference to the symbols virtual address
IMAGE_REL_I386_DIR32NB	equ 0007h	; Direct 32-bit reference to the symbols virtual address, base not included
IMAGE_REL_I386_SEG12	equ 0009h	; Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
IMAGE_REL_I386_SECTION	equ 000Ah
IMAGE_REL_I386_SECREL 	equ 000Bh
IMAGE_REL_I386_REL32	equ 0014h	; PC-relative 32-bit reference to the symbols virtual address

;
; MIPS relocation types.
;

IMAGE_REL_MIPS_ABSOLUTE 	equ 0000h	; Reference is absolute, no relocation is necessary
IMAGE_REL_MIPS_REFHALF	equ 0001h
IMAGE_REL_MIPS_REFWORD	equ 0002h
IMAGE_REL_MIPS_JMPADDR	equ 0003h
IMAGE_REL_MIPS_REFHI	equ 0004h
IMAGE_REL_MIPS_REFLO	equ 0005h
IMAGE_REL_MIPS_GPREL	equ 0006h
IMAGE_REL_MIPS_LITERAL	equ 0007h
IMAGE_REL_MIPS_SECTION	equ 000Ah
IMAGE_REL_MIPS_SECREL 	equ 000Bh
IMAGE_REL_MIPS_SECRELLO 	equ 000Ch	; Low 16-bit section relative referemce (used for >32k TLS)
IMAGE_REL_MIPS_SECRELHI 	equ 000Dh	; High 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_MIPS_REFWORDNB	equ 0022h
IMAGE_REL_MIPS_PAIR 	equ 0025h

;
; Alpha Relocation types.
;

IMAGE_REL_ALPHA_ABSOLUTE	equ 0000h
IMAGE_REL_ALPHA_REFLONG 	equ 0001h
IMAGE_REL_ALPHA_REFQUAD 	equ 0002h
IMAGE_REL_ALPHA_GPREL32 	equ 0003h
IMAGE_REL_ALPHA_LITERAL 	equ 0004h
IMAGE_REL_ALPHA_LITUSE	equ 0005h
IMAGE_REL_ALPHA_GPDISP	equ 0006h
IMAGE_REL_ALPHA_BRADDR	equ 0007h
IMAGE_REL_ALPHA_HINT	equ 0008h
IMAGE_REL_ALPHA_INLINE_REFLONG	equ 0009h
IMAGE_REL_ALPHA_REFHI 	equ 000Ah
IMAGE_REL_ALPHA_REFLO 	equ 000Bh
IMAGE_REL_ALPHA_PAIR	equ 000Ch
IMAGE_REL_ALPHA_MATCH 	equ 000Dh
IMAGE_REL_ALPHA_SECTION 	equ 000Eh
IMAGE_REL_ALPHA_SECREL	equ 000Fh
IMAGE_REL_ALPHA_REFLONGNB 	equ 0010h
IMAGE_REL_ALPHA_SECRELLO	equ 0011h	; Low 16-bit section relative reference
IMAGE_REL_ALPHA_SECRELHI	equ 0012h	; High 16-bit section relative reference

;
; IBM PowerPC relocation types.
;

IMAGE_REL_PPC_ABSOLUTE	equ 0000h	; NOP
IMAGE_REL_PPC_ADDR64	equ 0001h	; 64-bit address
IMAGE_REL_PPC_ADDR32	equ 0002h	; 32-bit address
IMAGE_REL_PPC_ADDR24	equ 0003h	; 26-bit address, shifted left 2 (branch absolute)
IMAGE_REL_PPC_ADDR16	equ 0004h	; 16-bit address
IMAGE_REL_PPC_ADDR14	equ 0005h	; 16-bit address, shifted left 2 (load doubleword)
IMAGE_REL_PPC_REL24 	equ 0006h	; 26-bit PC-relative offset, shifted left 2 (branch relative)
IMAGE_REL_PPC_REL14 	equ 0007h	; 16-bit PC-relative offset, shifted left 2 (br cond relative)
IMAGE_REL_PPC_TOCREL16	equ 0008h	; 16-bit offset from TOC base
IMAGE_REL_PPC_TOCREL14	equ 0009h	; 16-bit offset from TOC base, shifted left 2 (load doubleword)
IMAGE_REL_PPC_ADDR32NB	equ 000Ah	; 32-bit addr w/o image base
IMAGE_REL_PPC_SECREL	equ 000Bh	; va of containing section (as in an image sectionhdr)
IMAGE_REL_PPC_SECTION 	equ 000Ch	; sectionheader number
IMAGE_REL_PPC_IFGLUE	equ 000Dh	; substitute TOC restore instruction iff symbol is glue code
IMAGE_REL_PPC_IMGLUE	equ 000Eh	; symbol is glue codeh	; virtual address is TOC restore instruction
IMAGE_REL_PPC_SECREL16	equ 000Fh	; va of containing section (limited to 16 bits)
IMAGE_REL_PPC_REFHI 	equ 0010h
IMAGE_REL_PPC_REFLO 	equ 0011h
IMAGE_REL_PPC_PAIR	equ 0012h
IMAGE_REL_PPC_SECRELLO	equ 0013h	; Low 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_PPC_SECRELHI	equ 0014h	; High 16-bit section relative reference (used for >32k TLS)
IMAGE_REL_PPC_TYPEMASK	equ 00FFh	; mask to isolate above values in IMAGE_RELOCATION.Type

; Flag bits in IMAGE_RELOCATION.TYPE

IMAGE_REL_PPC_NEG 	equ 0100h	; subtract reloc value rather than adding it
IMAGE_REL_PPC_BRTAKEN 	equ 0200h	; fix branch prediction bit to predict branch taken
IMAGE_REL_PPC_BRNTAKEN	equ 0400h	; fix branch prediction bit to predict branch not taken
IMAGE_REL_PPC_TOCDEFN 	equ 0800h	; toc slot defined in file (or, data in toc)

;
; Line number format.
;

IMAGE_LINENUMBER	struc
 iln_SymbolTableIndex	dd	?		; Symbol table index of function name if Linenumber is 0.
 iln_VirtualAddress		equ	iln_SymbolTableIndex	; Virtual address of line number.
 iln_Linenumber		dw	?		; Line number.
IMAGE_LINENUMBER	ends

IMAGE_SIZEOF_LINENUMBER	equ	6

;
; Based relocation format.
;

IMAGE_BASE_RELOCATION	struc
 ibr_VirtualAddress	dd	?
 ibr_SizeOfBlock	dd	?
 ibr_TypeOffset	dw	?
IMAGE_BASE_RELOCATION	ends

IMAGE_SIZEOF_BASE_RELOCATION	equ 8

;
; Based relocation types.
;

IMAGE_REL_BASED_ABSOLUTE	equ 0
IMAGE_REL_BASED_HIGH	equ 1
IMAGE_REL_BASED_LOW	equ 2
IMAGE_REL_BASED_HIGHLOW	equ 3
IMAGE_REL_BASED_HIGHADJ	equ 4
IMAGE_REL_BASED_MIPS_JMPADDR	equ 5
IMAGE_REL_BASED_SECTION	equ 6
IMAGE_REL_BASED_REL32	equ 7

;
; Archive format.
;

IMAGE_ARCHIVE_START_SIZE		equ 8
IMAGE_ARCHIVE_START		equ "!<arch>\n"
IMAGE_ARCHIVE_END		equ "`\n"
IMAGE_ARCHIVE_PAD		equ "\n"
IMAGE_ARCHIVE_LINKER_MEMBER		equ "/ "
IMAGE_ARCHIVE_LONGNAMES_MEMBER	equ ";"

IMAGE_ARCHIVE_MEMBER_HEADER	struc
 iamh_Name	db	16 dup(?)	; File member name - `/' terminated.
 iamh_Date	db	12 dup(?)	; File member date - decimal.
 iamh_UserID	db	6 dup(?)	; File member user id - decimal.
 iamh_GroupID	db	6 dup(?)	; File member group id - decimal.
 iamh_Mode	db	8 dup(?)	; File member mode - octal.
 iamh_Size	db	10 dup(?)	; File member size - decimal.
 iamh_EndHeader	db	2 dup(?)	; String to end header.
IMAGE_ARCHIVE_MEMBER_HEADER	ends

IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR	equ	60

;
; DLL support.
;

;
; Export Format
;

IMAGE_EXPORT_DIRECTORY	struc
 ied_Characteristics	dd	?
 ied_TimeDateStamp	dd	?
 ied_MajorVersion		dw	?
 ied_MinorVersion		dw	?
 ied_Name		dd	?
 ied_Base		dd	?
 ied_NumberOfFunctions	dd	?
 ied_NumberOfNames	dd	?
 ied_AddressOfFunctions	dd	?
 ied_AddressOfNames	dd	?
 ied_AddressOfNameOrdinals	dd	?
IMAGE_EXPORT_DIRECTORY	ends

;
; Import Format
;

IMAGE_IMPORT_BY_NAME	struc
 iibn_Hint	dw	?
 iibn_Name	db	?
IMAGE_IMPORT_BY_NAME	ends

IMAGE_THUNK_DATA	struc
 itd_ForwarderString	dd	?
 itd_Function		equ	itd_ForwarderString
 itd_Ordinal		equ	itd_ForwarderString
 itd_AddressOfData	equ	itd_ForwarderString
IMAGE_THUNK_DATA	ends

IMAGE_ORDINAL_FLAG 	equ 80000000
;;IMAGE_SNAP_BY_ORDINAL(Ordinal) ((Ordinal & IMAGE_ORDINAL_FLAG) != 0)
;;IMAGE_ORDINAL(Ordinal) (Ordinal & 0xffff)

IMAGE_IMPORT_DESCRIPTOR	struc
 iid_OriginalFirstThunk	dd	?
 iid_Characteristics		equ	iid_OriginalFirstThunk
 iid_TimeDateStamp	dd	?
 iid_ForwarderChain	dd	?
 iid_Name		dd	?
 iid_FirstThunk		dd	?
IMAGE_IMPORT_DESCRIPTOR	ends

;
; New format import descriptors pointed to by DataDirectory[ IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT ]
;

IMAGE_BOUND_IMPORT_DESCRIPTOR	struc
 ibid_TimeDateStamp	dd	?
 ibid_OffsetModuleName	dw	?
 ibid_NumberOfModuleForwarderRefs	dw	?
IMAGE_BOUND_IMPORT_DESCRIPTOR	ends

IMAGE_BOUND_FORWARDER_REF	struc
 ibfr_TimeDateStamp	dd	?
 ibfr_OffsetModuleName	dw	?
 ibfr_Reserved		dw	?
IMAGE_BOUND_FORWARDER_REF	ends

;
; Thread Local Storage
;

IMAGE_TLS_DIRECTORY	struc
 itd_StartAddressOfRawData	dd	?
 itd_EndAddressOfRawData	dd	?
 itd_AddressOfIndex	dd	?
 itd_AddressOfCallBacks	dd	?
 itd_SizeOfZeroFill		dd	?
 itd_Characteristics	dd	?
IMAGE_TLS_DIRECTORY	ends


;
; Resource Format.
;

;
; Resource directory consists of two counts, following by a variable length
; array of directory entries.The first count is the number of entries at
; beginning of the array that have actual names associated with each entry.
; The entries are in ascending order, case insensitive strings.The second
; count is the number of entries that immediately follow the named entries.
; This second count identifies the number of entries that have 16-bit integer
; Ids as their name.These entries are also sorted in ascending order.
;
; This structure allows fast lookup by either name or number, but for any
; given resource entry only one form of lookup is supported, not both.
; This is consistant with the syntax of the .RC file and the .RES file.
;

IMAGE_RESOURCE_DIRECTORY	struc
 ird_Characteristics	dd	?
 ird_TimeDateStamp	dd	?
 ird_MajorVersion		dw	?
 ird_MinorVersion		dw	?
 ird_NumberOfNamedEntries	dw	?
 ird_NumberOfIdEntries	dw	?
; ird_DirectoryEntries:
IMAGE_RESOURCE_DIRECTORY	ends

ird_DirectoryEntries	equ	sizeof IMAGE_RESOURCE_DIRECTORY

; Each directory contains the 32-bit Name of the entry and an offset,
; relative to the beginning of the resource directory of the data associated
; with this directory entry.If the name of the entry is an actual text
; string instead of an integer Id, then the high order bit of the name field
; is set to one and the low order 31-bits are an offset, relative to the
; beginning of the resource directory of the string, which is of type
; IMAGE_RESOURCE_DIRECTORY_STRING.Otherwise the high bit is clear and the
; low-order 16-bits are the integer Id that identify this resource directory
; entry. If the directory entry is yet another resource directory (i.e. a
; subdirectory), then the high order bit of the offset field will be
; set to indicate this.Otherwise the high bit is clear and the offset
; field points to a resource data entry.
;

IMAGE_RESOURCE_DIRECTORY_ENTRY	struc
 irde_Name		dd	?
 irde_OffsetToData		dd	?
IMAGE_RESOURCE_DIRECTORY_ENTRY	ends

IMAGE_RESOURCE_NAME_IS_STRING		equ 80000000h
IMAGE_RESOURCE_DATA_IS_DIRECTORY 	equ 80000000h

;
; For resource directory entries that have actual string names, the Name
; field of the directory entry points to an object of the following type.
; All of these string objects are stored together after the last resource
; directory entry and before the first resource data object.This minimizes
; the impact of these variable length objects on the alignment of the fixed
; size directory entry objects.
;

IMAGE_RESOURCE_DIRECTORY_STRING	struc
 irds_Length	dw	?
 irds_NameString	db	?
IMAGE_RESOURCE_DIRECTORY_STRING	ends

IMAGE_RESOURCE_DIR_STRING_U	struc
 irdsu_Length	dw	?
 irdsu_NameString	dw	?
IMAGE_RESOURCE_DIR_STRING_U	ends


;
; Each resource data entry describes a leaf node in the resource directory
; tree.It contains an offset, relative to the beginning of the resource
; directory of the data for the resource, a size field that gives the number
; of bytes of data at that offset, a CodePage that should be used when
; decoding code point values within the resource data.Typically for new
; applications the code page would be the unicode code page.
;

IMAGE_RESOURCE_DATA_ENTRY	struc
 irdt_OffsetToData		dd	?
 irdt_Size		dd	?
 irdt_CodePage		dd	?
 irdt_Reserved		dd	?
IMAGE_RESOURCE_DATA_ENTRY	ends

;
; Load Configuration Directory Entry
;

IMAGE_LOAD_CONFIG_DIRECTORY	struc
 ilcd_Characteristics	dd	?
 ilcd_TimeDateStamp	dd	?
 ilcd_MajorVersion		dw	?
 ilcd_MinorVersion		dw	?
 ilcd_GlobalFlagsClear	dd	?
 ilcd_GlobalFlagsSet	dd	?
 ilcd_CriticalSectionDefaultTimeout	dd	?
 ilcd_DeCommitFreeBlockThreshold	dd	?
 ilcd_DeCommitTotalFreeThreshold	dd	?
 ilcd_LockPrefixTable	dd	?
 ilcd_MaximumAllocationSize	dd	?
 ilcd_VirtualMemoryThreshold	dd	?
 ilcd_ProcessHeapFlags	dd	?
 ilcd_ProcessAffinityMask	dd	?
 ilcd_Reserved		dd	?, ?, ?
IMAGE_LOAD_CONFIG_DIRECTORY	ends

;
; Function table entry format for MIPS/ALPHA images.Function table is
; pointed to by the IMAGE_DIRECTORY_ENTRY_EXCEPTION directory entry.
; This definition duplicates ones in ntmips.h and ntalpha.h for use
; by portable image file mungers.
;

IMAGE_RUNTIME_FUNCTION_ENTRY	struc
 irfe_BeginAddress		dd	?
 irfe_EndAddress		dd	?
 irfe_ExceptionHandler	dd	?
 irfe_HandlerData		dd	?
 irfe_PrologEndAddress	dd	?
IMAGE_RUNTIME_FUNCTION_ENTRY	ends

;
; Debug Format
;

IMAGE_DEBUG_DIRECTORY	struc
 idd_Characteristics	dd	?
 idd_TimeDateStamp	dd	?
 idd_MajorVersion		dw	?
 idd_MinorVersion		dw	?
 idd_Type		dd	?
 idd_SizeOfData		dd	?
 idd_AddressOfRawData	dd	?
 idd_PointerToRawData	dd	?
IMAGE_DEBUG_DIRECTORY	ends

IMAGE_DEBUG_TYPE_UNKNOWN		equ	0
IMAGE_DEBUG_TYPE_COFF		equ	1
IMAGE_DEBUG_TYPE_CODEVIEW		equ	2
IMAGE_DEBUG_TYPE_FPO		equ	3
IMAGE_DEBUG_TYPE_MISC		equ	4
IMAGE_DEBUG_TYPE_EXCEPTION		equ	5
IMAGE_DEBUG_TYPE_FIXUP		equ	6
IMAGE_DEBUG_TYPE_OMAP_TO_SRC		equ	7
IMAGE_DEBUG_TYPE_OMAP_FROM_SRC	equ	8

IMAGE_COFF_SYMBOLS_HEADER	struc
 icsh_NumberOfSymbols	dd	?
 icsh_LvaToFirstSymbol	dd	?
 icsh_NumberOfLinenumbers	dd	?
 icsh_LvaToFirstLinenumber	dd	?
 icsh_RvaToFirstByteOfCode	dd	?
 icsh_RvaToLastByteOfCode	dd	?
 icsh_RvaToFirstByteOfData	dd	?
 icsh_RvaToLastByteOfData	dd	?
IMAGE_COFF_SYMBOLS_HEADER	ends

FRAME_FPO	equ	0
FRAME_TRAP	equ	1
FRAME_TSS	equ	2
FRAME_NONFPO	equ	3

FPO_DATA	struc
 pfo_ulOffStart	dd	?	; offset 1st byte of function code
 pfo_cbProcSize	dd	?	; bytes in function
 pfo_cdwLocals	dd	?	; bytes in locals/4
 pfo_cdwParams	dw	?	; bytes in params/4
 pfo_cbProlog	dw	8	; bytes in prolog
 pfo_cbRegs	dw	3	; regs saved
 pfo_fHasSEH	dw	1	; TRUE if SEH in func
 pfo_fUseBP	dw	1	; TRUE if EBP has been allocated
 pfo_reserved	dw	1	; reserved for future use
 pfo_cbFrame	dw	2	; frame type
FPO_DATA	ends

SIZEOF_RFPO_DATA	equ	16

IMAGE_DEBUG_MISC_EXENAME	equ	1

IMAGE_DEBUG_MISC	struc
 idm_DataType	dd	?	;type of misc data, see defines
 idm_Length	dd	?	; total length of record, rounded to four
 idm_Unicode	dd	?	; TRUE if data is unicode string
 idm_Reserved	db	3 dup(?)
 idm_Data	db	?	; Actual data
IMAGE_DEBUG_MISC	ends

;
; Function table extracted from MIPS/ALPHA images.Does not contain
; information needed only for runtime support.Just those fields for
; each entry needed by a debugger.
;

IMAGE_FUNCTION_ENTRY	struc
 ife_StartingAddress	dd	?
 ife_EndingAddress	dd	?
 ife_EndOfPrologue	dd	?
IMAGE_FUNCTION_ENTRY	ends

;
; Debugging information can be stripped from an image file and placed
; in a separate .DBG file, whose file name part is the same as the
; image file name part (e.g. symbols for CMD.EXE could be stripped
; and placed in CMD.DBG).This is indicated by the IMAGE_FILE_DEBUG_STRIPPED
; flag in the Characteristics field of the file header.The beginning of
; the .DBG file contains the following structure which captures certain
; information from the image file.This allows a debug to proceed even if
; the original image file is not accessable.This header is followed by
; zero of more IMAGE_SECTION_HEADER structures, followed by zero or more
; IMAGE_DEBUG_DIRECTORY structures.The latter structures and those in
; the image file contain file offsets relative to the beginning of the
; .DBG file.
;
; If symbols have been stripped from an image, the IMAGE_DEBUG_MISC structure
; is left in the image file, but not mapped.This allows a debugger to
; compute the name of the .DBG file, from the name of the image in the
; IMAGE_DEBUG_MISC structure.
;

IMAGE_SEPARATE_DEBUG_HEADER	struc
 isdh_Signature		dw	?
 isdh_Flags		dw	?
 isdh_Machine		dw	?
 isdh_Characteristics	dw	?
 isdh_TimeDateStamp	dd	?
 isdh_CheckSum		dd	?
 isdh_ImageBase		dd	?
 isdh_SizeOfImage		dd	?
 isdh_NumberOfSections	dd	?
 isdh_ExportedNamesSize	dd	?
 isdh_DebugDirectorySize	dd	?
 isdh_SectionAlignment	dd	?
 isdh_Reserved		dd	?, ?
IMAGE_SEPARATE_DEBUG_HEADER	ends

IMAGE_SEPARATE_DEBUG_SIGNATURE		equ 4944
IMAGE_SEPARATE_DEBUG_FLAGS_MASK 	equ 8000
IMAGE_SEPARATE_DEBUG_MISMATCH 		equ 8000	; when DBG was updated, the

;
; End Image Format
;


MESSAGE_RESOURCE_ENTRY	struc
 mre_Length		dw	?
 mre_Flags		dw	?
 mre_Text		db	?
MESSAGE_RESOURCE_ENTRY	ends

MESSAGE_RESOURCE_UNICODE 	equ 0001

MESSAGE_RESOURCE_BLOCK	struc
 mrb_LowId		dd	?
 mrb_HighId		dd	?
 mrb_OffsetToEntries	dd	?
MESSAGE_RESOURCE_BLOCK	ends

MESSAGE_RESOURCE_DATA	struc
 mrd_NumberOfBlocks	dd	?
 mrd_Blocks		MESSAGE_RESOURCE_BLOCK	<?>
MESSAGE_RESOURCE_DATA	ends


RTL_CRITICAL_SECTION_DEBUG	struc
 rcsd_Type		dw	?
 rcsd_CreatorBackTraceIndex	dw	?
 rcsd_CriticalSection	dd	?
 rcsd_ProcessLocksList	dd	?
 		dd	?
 rcsd_EntryCount		dd	?
 rcsd_ContentionCount	dd	?
 rcsd_Spare		dd	?
 		dd	?
RTL_CRITICAL_SECTION_DEBUG	ends


RTL_CRITSECT_TYPE	equ	0
RTL_RESOURCE_TYPE	equ	1


DLL_PROCESS_ATTACH	equ 1
DLL_THREAD_ATTACH	equ 2
DLL_THREAD_DETACH	equ 3
DLL_PROCESS_DETACH	equ 0

;
; Defines for the READ flags for Eventlogging
;

EVENTLOG_SEQUENTIAL_READ	equ 1
EVENTLOG_SEEK_READ	equ 2
EVENTLOG_FORWARDS_READ	equ 4
EVENTLOG_BACKWARDS_READ 	equ 8

;
; The types of events that can be logged.
;
EVENTLOG_SUCCESS	equ 0000h
EVENTLOG_ERROR_TYPE 	equ 0001h
EVENTLOG_WARNING_TYPE 	equ 0002h
EVENTLOG_INFORMATION_TYPE 	equ 0004h
EVENTLOG_AUDIT_SUCCESS	equ 0008h
EVENTLOG_AUDIT_FAILURE	equ 0010h

;
; Defines for the WRITE flags used by Auditing for paired events
; These are not implemented in Product 1
;

EVENTLOG_START_PAIRED_EVENT	equ 0001h
EVENTLOG_END_PAIRED_EVENT	equ 0002h
EVENTLOG_END_ALL_PAIRED_EVENTS 	equ 0004h
EVENTLOG_PAIRED_EVENT_ACTIVE 	equ 0008h
EVENTLOG_PAIRED_EVENT_INACTIVE 	equ 0010h

;
; Structure that defines the header of the Eventlog record. This is the
; fixed-sized portion before all the variable-length strings, binary
; data and pad bytes.
;
; TimeGenerated is the time it was generated at the client.
; TimeWritten is the time it was put into the log at the server end.
;


EVENTLOGRECORD	struc
DWORDLength;; Length of full record
DWORDReserved;; Used by the service
DWORDRecordNumber;; Absolute record number
DWORDTimeGenerated; ; Seconds since 1-1-1970
DWORDTimeWritten; ; Seconds since 1-1-1970
DWORDEventID;
WORD EventType;
WORD NumStrings;
WORD EventCategory;
WORD ReservedFlags; ; For use with paired events (auditing)
DWORDClosingRecordNumber; ; For use with paired events (auditing)
DWORDStringOffset;; Offset from beginning of record
DWORDUserSidLength;
DWORDUserSidOffset;
DWORDDataLength;
DWORDDataOffset;; Offset from beginning of record
;
; Then follow:
;
; WCHAR SourceName[]
; WCHAR Computername[]
; SID UserSid
; WCHAR Strings[]
; BYTEData[]
; CHARPad[]
; DWORD Length;
;
} EVENTLOGRECORD, *PEVENTLOGRECORD;


DBG_CONTINUE		equ 00010002h
DBG_TERMINATE_THREAD	equ 40010003h
DBG_TERMINATE_PROCESS	equ 40010004h
DBG_CONTROL_C		equ 40010005h
DBG_CONTROL_BREAK	equ 40010008h
DBG_EXCEPTION_NOT_HANDLED	equ 80010001h

; begin_ntddk begin_nthal
;
; Registry Specific Access Rights.
;
-#
KEY_QUERY_VALUE		equ 0001h
KEY_SET_VALUE		equ 0002h
KEY_CREATE_SUB_KEY	equ 0004h
KEY_ENUMERATE_SUB_KEYS	equ 0008h
KEY_NOTIFY		equ 0010h
KEY_CREATE_LINK		equ 0020h

KEY_READ	equ (STANDARD_RIGHTS_READ + KEY_QUERY_VALUE + KEY_ENUMERATE_SUB_KEYS + KEY_NOTIFY) AND (NOT SYNCHRONIZE)
KEY_WRITE	equ (STANDARD_RIGHTS_WRITE+KEY_SET_VALUE+KEY_CREATE_SUB_KEY) AND  (NOT SYNCHRONIZE)
KEY_EXECUTE	equ KEY_READ AND (NOT SYNCHRONIZE)
KEY_ALL_ACCESS	equ (STANDARD_RIGHTS_ALL+KEY_QUERY_VALUE+KEY_SET_VALUE+KEY_CREATE_SUB_KEY +KEY_ENUMERATE_SUB_KEYS +KEY_NOTIFY +KEY_CREATE_LINK) AND  (NOT SYNCHRONIZE)

;
; Open/Create Options
;

REG_OPTION_RESERVED 	equ 00000000h ; Parameter is reserved
REG_OPTION_NON_VOLATILE 	equ 00000000h ; Key is preserved
; when system is rebooted

REG_OPTION_VOLATILE 	equ 00000001h ; Key is not preserved
; when system is rebooted

REG_OPTION_CREATE_LINK	equ 00000002h ; Created key is a
; symbolic link

REG_OPTION_BACKUP_RESTORE 	equ 00000004h ; open for backup or restore
; special access rules
; privilege required

REG_OPTION_OPEN_LINK	equ 00000008h ; Open symbolic link
REG_LEGAL_OPTION	equ REG_OPTION_RESERVED+ REG_OPTION_NON_VOLATILE+ REG_OPTION_VOLATILE+ REG_OPTION_CREATE_LINK + REG_OPTION_BACKUP_RESTORE+ REG_OPTION_OPEN_LINK

;
; Key creation/open disposition
;

REG_CREATED_NEW_KEY 	equ 00000001h ; New Registry Key created
REG_OPENED_EXISTING_KEY 	equ 00000002h ; Existing Key opened

;
; Key restore flags
;

REG_WHOLE_HIVE_VOLATILE 	equ 00000001h ; Restore whole hive volatile
REG_REFRESH_HIVE	equ 00000002h ; Unwind changes to last flush
REG_NO_LAZY_FLUSH 	equ 00000004h ; Never lazy flush this hive

; end_ntddk end_nthal

;
; Notify filter values
;
REG_NOTIFY_CHANGE_NAME	equ 00000001h ; Create or delete child)
REG_NOTIFY_CHANGE_ATTRIBUTES	equ 00000002h
REG_NOTIFY_CHANGE_LAST_SET	equ 00000004h ; time stamp
REG_NOTIFY_CHANGE_SECURITY	equ 00000008h

REG_LEGAL_CHANGE_FILTER	equ REG_NOTIFY_CHANGE_NAME+ REG_NOTIFY_CHANGE_ATTRIBUTES+ REG_NOTIFY_CHANGE_LAST_SET+ REG_NOTIFY_CHANGE_SECURITY

;
;
; Predefined Value Types.
;

REG_NONE		equ 0	; No value type
REG_SZ		equ 1	; Unicode nul terminated string
REG_EXPAND_SZ		equ 2	; Unicode nul terminated string with environment variable references
REG_BINARY		equ 3	; Free form binary
REG_DWORD		equ 4	; 32-bit number
REG_DWORD_LITTLE_ENDIAN	equ 4	; 32-bit number same as REG_DWORD)
REG_DWORD_BIG_ENDIAN	equ 5	; 32-bit number
REG_LINK		equ 6	; Symbolic Link unicode)
REG_MULTI_SZ		equ 7	; Multiple Unicode strings
REG_RESOURCE_LIST	equ 8	; Resource list in the resource map
REG_FULL_RESOURCE_DESCRIPTOR	equ 9	; Resource list in the hardware description
REG_RESOURCE_REQUIREMENTS_LIST	equ 10

; end_ntddk end_nthal

; begin_ntddk begin_nthal
;
; Service Types (Bit Mask)
;

SERVICE_KERNEL_DRIVER	equ 00000001h
SERVICE_FILE_SYSTEM_DRIVER 	equ 00000002h
SERVICE_ADAPTER		equ 00000004h
SERVICE_RECOGNIZER_DRIVER	equ 00000008h
SERVICE_DRIVER		equ SERVICE_KERNEL_DRIVER + SERVICE_FILE_SYSTEM_DRIVER + SERVICE_RECOGNIZER_DRIVER
SERVICE_WIN32_OWN_PROCESS	equ 00000010h
SERVICE_WIN32_SHARE_PROCESS	equ 00000020h
SERVICE_WIN32		equ SERVICE_WIN32_OWN_PROCESS + SERVICE_WIN32_SHARE_PROCESS
SERVICE_INTERACTIVE_PROCESS	equ 00000100h
SERVICE_TYPE_ALL	equ SERVICE_WIN32+ SERVICE_ADAPTER + SERVICE_DRIVER+ SERVICE_INTERACTIVE_PROCESS

;
; Start Type
;

SERVICE_BOOT_START 	equ 00000000h
SERVICE_SYSTEM_START 	equ 00000001h
SERVICE_AUTO_START 	equ 00000002h
SERVICE_DEMAND_START 	equ 00000003h
SERVICE_DISABLED 	equ 00000004h

;
; Error control type
;
SERVICE_ERROR_IGNORE 	equ 00000000h
SERVICE_ERROR_NORMAL 	equ 00000001h
SERVICE_ERROR_SEVERE 	equ 00000002h
SERVICE_ERROR_CRITICAL 	equ 00000003h
comment #
;
;
; Define the registry driver node enumerations
;

;
; IOCTL_TAPE_ERASE definitions
;

TAPE_ERASE_SHORT	= 0
TAPE_ERASE_LONG		= 1

TAPE_ERASE	struc
 tae_Type	dd	?
 tae_Immediate	dd	?
TAPE_ERASE	ends

;
; IOCTL_TAPE_PREPARE definitions
;

TAPE_LOAD	equ 0h
TAPE_UNLOAD	equ 1h
TAPE_TENSION	equ 2h
TAPE_LOCK	equ 3h
TAPE_UNLOCK	equ 4h
TAPE_FORMAT	equ 5h

TAPE_PREPARE	struc
 tap_Operation	dd	?
 tap_Immediate	dd	?
TAPE_PREPARE	ends

;
; IOCTL_TAPE_WRITE_MARKS definitions
;

TAPE_SETMARKS		equ 0h
TAPE_FILEMARKS		equ 1h
TAPE_SHORT_FILEMARKS	equ 2h
TAPE_LONG_FILEMARKS	equ 3h

TAPE_WRITE_MARKS	struc
 twm_Type	dd	?
 twm_Count	dd	?
 twm_Immediate	dd	?
TAPE_WRITE_MARKS	ends

;
; IOCTL_TAPE_GET_POSITION definitions
;

TAPE_ABSOLUTE_POSITION	equ 0
TAPE_LOGICAL_POSITION	equ 1
TAPE_PSEUDO_LOGICAL_POSITION	equ 2

TAPE_GET_POSITION	struc
 tgp_Type	dd	?
 tgp_Partition	dd	?
 tgp_Offset	dd	?, ?
TAPE_GET_POSITION	ends

;
; IOCTL_TAPE_SET_POSITION definitions
;

TAPE_REWIND		equ 0
TAPE_ABSOLUTE_BLOCK	equ 1
TAPE_LOGICAL_BLOCK	equ 2
TAPE_PSEUDO_LOGICAL_BLOCK	equ 3
TAPE_SPACE_END_OF_DATA	equ 4
TAPE_SPACE_RELATIVE_BLOCKS	equ 5
TAPE_SPACE_FILEMARKS	equ 6
TAPE_SPACE_SEQUENTIAL_FMKS	equ 7
TAPE_SPACE_SETMARKS	equ 8
TAPE_SPACE_SEQUENTIAL_SMKS	equ 9

TAPE_SET_POSITION	struc
 tsp_Method	dd	?
 tsp_Partition	dd	?
 tsp_Offset	dd	?, ?
 tsp_Immediate	dd	?
TAPE_SET_POSITION	ends

;
; IOCTL_TAPE_GET_DRIVE_PARAMS definitions
;

;
; Definitions for FeaturesLow parameter
;

TAPE_DRIVE_FIXED	equ 00000001h
TAPE_DRIVE_SELECT 	equ 00000002h
TAPE_DRIVE_INITIATOR	equ 00000004h
TAPE_DRIVE_ERASE_SHORT	equ 00000010h
TAPE_DRIVE_ERASE_LONG 	equ 00000020h
TAPE_DRIVE_ERASE_BOP_ONLY 	equ 00000040h
TAPE_DRIVE_ERASE_IMMEDIATE	equ 00000080h
TAPE_DRIVE_TAPE_CAPACITY	equ 00000100h
TAPE_DRIVE_TAPE_REMAINING 	equ 00000200h
TAPE_DRIVE_FIXED_BLOCK	equ 00000400h
TAPE_DRIVE_VARIABLE_BLOCK 	equ 00000800h
TAPE_DRIVE_WRITE_PROTECT	equ 00001000h
TAPE_DRIVE_EOT_WZ_SIZE	equ 00002000h
TAPE_DRIVE_ECC		equ 00010000h
TAPE_DRIVE_COMPRESSION	equ 00020000h
TAPE_DRIVE_PADDING	equ 00040000h
TAPE_DRIVE_REPORT_SMKS	equ 00080000h
TAPE_DRIVE_GET_ABSOLUTE_BLK 	equ 00100000h
TAPE_DRIVE_GET_LOGICAL_BLK	equ 00200000h
TAPE_DRIVE_SET_EOT_WZ_SIZE	equ 00400000h
TAPE_DRIVE_EJECT_MEDIA	equ 01000000h
TAPE_DRIVE_RESERVED_BIT 	equ 80000000h	;don't use this bit!

;;can't be a low features bit!
;;reserved; high features only

;
; Definitions for FeaturesHigh parameter
;

TAPE_DRIVE_LOAD_UNLOAD	equ 80000001h
TAPE_DRIVE_TENSION	equ 80000002h
TAPE_DRIVE_LOCK_UNLOCK	equ 80000004h
TAPE_DRIVE_REWIND_IMMEDIATE 	equ 80000008h
TAPE_DRIVE_SET_BLOCK_SIZE 	equ 80000010h
TAPE_DRIVE_LOAD_UNLD_IMMED	equ 80000020h
TAPE_DRIVE_TENSION_IMMED	equ 80000040h
TAPE_DRIVE_LOCK_UNLK_IMMED	equ 80000080h
TAPE_DRIVE_SET_ECC	equ 80000100h
TAPE_DRIVE_SET_COMPRESSION	equ 80000200h
TAPE_DRIVE_SET_PADDING	equ 80000400h
TAPE_DRIVE_SET_REPORT_SMKS	equ 80000800h
TAPE_DRIVE_ABSOLUTE_BLK 	equ 80001000h
TAPE_DRIVE_ABS_BLK_IMMED	equ 80002000h
TAPE_DRIVE_LOGICAL_BLK	equ 80004000h
TAPE_DRIVE_LOG_BLK_IMMED	equ 80008000h
TAPE_DRIVE_END_OF_DATA	equ 80010000h
TAPE_DRIVE_RELATIVE_BLKS	equ 80020000h
TAPE_DRIVE_FILEMARKS	equ 80040000h
TAPE_DRIVE_SEQUENTIAL_FMKS	equ 80080000h
TAPE_DRIVE_SETMARKS 	equ 80100000h
TAPE_DRIVE_SEQUENTIAL_SMKS	equ 80200000h
TAPE_DRIVE_REVERSE_POSITION 	equ 80400000h
TAPE_DRIVE_SPACE_IMMEDIATE	equ 80800000h
TAPE_DRIVE_WRITE_SETMARKS 	equ 81000000h
TAPE_DRIVE_WRITE_FILEMARKS	equ 82000000h
TAPE_DRIVE_WRITE_SHORT_FMKS 	equ 84000000h
TAPE_DRIVE_WRITE_LONG_FMKS	equ 88000000h
TAPE_DRIVE_WRITE_MARK_IMMED 	equ 90000000h
TAPE_DRIVE_FORMAT 	equ 0A0000000h
TAPE_DRIVE_FORMAT_IMMEDIATE 	equ 0C0000000h
TAPE_DRIVE_HIGH_FEATURES	equ 80000000h	;mask for high features flag

TAPE_GET_DRIVE_PARAMETERS	struc
 tgdp_ECC	dd	?
 tgdp_Compression	dd	?
 tgdp_DataPadding	dd	?
 tgdp_ReportSetmarks	dd	?
 tgdp_DefaultBlockSize	dd	?
 tgdp_MaximumBlockSize	dd	?
 tgdp_MinimumBlockSize	dd	?
 tgdp_MaximumPartitionCount	dd	?
 tgdp_FeaturesLow	dd	?
 tgdp_FeaturesHigh	dd	?
 tgdp_EOTWarningZoneSize	dd	?
TAPE_GET_DRIVE_PARAMETERS	ends

;
; IOCTL_TAPE_SET_DRIVE_PARAMETERS definitions
;

TAPE_SET_DRIVE_PARAMETERS	struc
 tsdp_ECC		dd	?
 tsdp_Compression		dd	?
 tsdp_DataPadding		dd	?
 tsdp_ReportSetmarks	dd	?
 tsdp_EOTWarningZoneSize	dd	?
TAPE_SET_DRIVE_PARAMETERS	ends

;
; IOCTL_TAPE_GET_MEDIA_PARAMETERS definitions
;

TAPE_GET_MEDIA_PARAMETERS	struc
 tgmp_Capacity		dd	?, ?
 tgmp_Remaining		dd	?, ?
 tgmp_BlockSize		dd	?
 tgmp_PartitionCount	dd	?
 tgmp_WriteProtected	dd	?
TAPE_GET_MEDIA_PARAMETERS	ends

;
; IOCTL_TAPE_SET_MEDIA_PARAMETERS definitions
;

TAPE_SET_MEDIA_PARAMETERS	struc
 tsmp_BlockSize		dd	?
TAPE_SET_MEDIA_PARAMETERS	ends

;
; IOCTL_TAPE_CREATE_PARTITION definitions
;

TAPE_FIXED_PARTITIONS	equ 0
TAPE_SELECT_PARTITIONS	equ 1
TAPE_INITIATOR_PARTITIONS	equ 2

TAPE_CREATE_PARTITION	struc
 tcp_Method	dd	?
 tcp_Count	dd	?
 tcp_Size	dd	?
TAPE_CREATE_PARTITION	ends

; Power Policy Management interfaces

POWER_ACTION_POLICY	struc
 pap_Action		dd	?
 pap_Flags		dd	?
 pap_EventCode		dd	?
POWER_ACTION_POLICY	ends

; POWER_ACTION_POLICY->Flags:

POWER_ACTION_QUERY_ALLOWED		equ	00000001h
POWER_ACTION_UI_ALLOWED		equ	00000002h
POWER_ACTION_OVERRIDE_APPS		equ	00000004h
POWER_ACTION_LIGHTEST_FIRST		equ	10000000h
POWER_ACTION_LOCK_CONSOLE		equ	20000000h
POWER_ACTION_DISABLE_WAKES		equ	40000000h
POWER_ACTION_CRITICAL		equ	80000000h

; POWER_ACTION_POLICY->EventCode flags

POWER_LEVEL_USER_NOTIFY_TEXT		equ	00000001h
POWER_LEVEL_USER_NOTIFY_SOUND		equ	00000002h
POWER_LEVEL_USER_NOTIFY_EXEC		equ	00000004h
POWER_USER_NOTIFY_BUTTON		equ	00000008h
POWER_USER_NOTIFY_SHUTDOWN		equ	00000010h
POWER_FORCE_TRIGGER_RESET		equ	80000000h

; system battery drain policies

SYSTEM_POWER_LEVEL	struc
 spl_Enable		db	?
 spl_Spare		db	?, ?, ?
 spl_BatteryLevel		dd	?
 spl_PowerPolicy		POWER_ACTION_POLICY	<?>
 spl_MinSystemState	dd	?
SYSTEM_POWER_LEVEL	ends


; processor power policy state

PROCESSOR_POWER_POLICY_INFO	struc
 pppi_TimeCheck		dd	?
 pppi_DemoteLimit		dd	?
 pppi_PromoteLimit		dd	?
 pppi_DemotePercent	db	?
 pppi_PromotePercent	db	?
; pppi_Spare		db	?, ?
; pppi_AllowDemotion:
; pppi_AllowPromotion:
 pppi_Reserved		dd	?
PROCESSOR_POWER_POLICY_INFO	ends

; processor power policy state

PROCESSOR_POWER_POLICY	struc
 ppp_Revision		dd	?
 ppp_DynamicThrottle	db	?
 ppp_Spare		db	?, ?, ?
; ppp_DisableCStates:
 ppp_Reserved		dd	?
 ppp_PolicyCount		dd	?
 ppp_Policy		PROCESSOR_POWER_POLICY_INFO	<?>
 ppp_Policy2		PROCESSOR_POWER_POLICY_INFO	<?>
 ppp_Policy3		PROCESSOR_POWER_POLICY_INFO	<?> 
PROCESSOR_POWER_POLICY	ends

; POWER_INFORMATION_LEVEL

SystemPowerPolicyAc		equ	0
SystemPowerPolicyDc		equ	1
VerifySystemPolicyAc		equ	2
VerifySystemPolicyDc		equ	3
SystemPowerCapabilities		equ	4
SystemBatteryState		equ	5
SystemPowerStateHandler		equ	6
ProcessorStateHandler		equ	7
SystemPowerPolicyCurrent		equ	8
AdministratorPowerPolicy		equ	9
SystemReserveHiberFile		equ	10
ProcessorInformation		equ	11
SystemPowerInformation		equ	12
ProcessorStateHandler2		equ	13
LastWakeTime			equ	14	; Compare with KeQueryInterruptTime()
LastSleepTime			equ	15	; Compare with KeQueryInterruptTime()
SystemExecutionState		equ	16
SystemPowerStateNotifyHandler		equ	17
ProcessorPowerPolicyAc		equ	18
ProcessorPowerPolicyDc		equ	19
VerifyProcessorPowerPolicyAc		equ	20
VerifyProcessorPowerPolicyDc		equ	21
ProcessorPowerPolicyCurrent		equ	22
SystemPowerStateLogging		equ	23
SystemPowerLoggingEntry		equ	24
-#
