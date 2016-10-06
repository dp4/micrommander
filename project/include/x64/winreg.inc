
RegCreateKeyExW	proto
RegOpenKeyExW		proto
RegQueryValueExW	proto
RegSetValueExW		proto
RegDeleteKeyW		proto
RegDeleteValueW		proto
RegEnumKeyExW		proto
RegEnumValueW		proto
RegQueryInfoKeyW	proto

RegCreateKeyExA	proto
RegOpenKeyExA		proto
RegQueryValueExA	proto
RegSetValueExA		proto
RegDeleteKeyA		proto
RegDeleteValueA		proto
RegEnumKeyExA		proto
RegEnumValueA		proto
RegQueryInfoKeyA	proto

RegCloseKey	proto

IFDEF	UNICODE

RegCreateKeyEx		equ	RegCreateKeyExW
RegOpenKeyEx		equ	RegOpenKeyExW
RegQueryValueEx		equ	RegQueryValueExW
RegSetValueEx		equ	RegSetValueExW
RegDeleteKey		equ	RegDeleteKeyW
RegDeleteValue		equ	RegDeleteValueW
RegEnumKeyEx		equ	RegEnumKeyExW
RegEnumValue		equ	RegEnumValueW
RegQueryInfoKey		equ	RegQueryInfoKeyW

ELSE

RegCreateKeyEx		equ	RegCreateKeyExA
RegOpenKeyEx		equ	RegOpenKeyExA
RegQueryValueEx		equ	RegQueryValueExA
RegSetValueEx		equ	RegSetValueExA
RegDeleteKey		equ	RegDeleteKeyA
RegDeleteValue		equ	RegDeleteValueA
RegEnumKeyEx		equ	RegEnumKeyExA
RegEnumValue		equ	RegEnumValueA
RegQueryInfoKey		equ	RegQueryInfoKeyA

ENDIF


HKEY_CLASSES_ROOT		= 80000000h
HKEY_CURRENT_USER		= 80000001h
HKEY_LOCAL_MACHINE		= 80000002h
HKEY_USERS			= 80000003h
HKEY_PERFORMANCE_DATA	= 80000004h
HKEY_CURRENT_CONFIG		= 80000005h
HKEY_DYN_DATA			= 80000006h
