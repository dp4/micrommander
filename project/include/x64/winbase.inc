
	IFDEF	UNICODE

CopyFile		equ	CopyFileW
CopyFileEx		equ	CopyFileExW
CreateDirectory		equ	CreateDirectoryW
CreateEvent		equ	CreateEventW
CreateFile		equ	CreateFileW
CreateProcess		equ	CreateProcessW
CreateProcessAsUser	equ	CreateProcessAsUserW
DeleteFile		equ	DeleteFileW
FindFirstFile		equ 	FindFirstFileW
FindFirstFileEx		equ	FindFirstFileExW
FindNextFile		equ 	FindNextFileW
FindResource		equ	FindResourceW
FindResourceEx		equ	FindResourceExW
FormatMessage		equ	FormatMessageW
GetCommandLine		equ	GetCommandLineW
GetFileAttributes		equ	GetFileAttributesW
GetModuleFileName		equ	GetModuleFileNameW
GetModuleHandle		equ	GetModuleHandleW
GetProfileInt		equ	GetProfileIntW
GetPrivateProfileInt	equ	GetPrivateProfileIntW
GetPrivateProfileSection	equ	GetPrivateProfileSectionW
GetPrivateProfileSectionNames	equ	GetPrivateProfileSectionNamesW
GetPrivateProfileString	equ	GetPrivateProfileStringW
GetPrivateProfileStruct	equ	GetPrivateProfileStructW
GetProfileSection		equ	GetProfileSectionW
GetProfileString		equ	GetProfileStringW
GetTempFileName		equ	GetTempFileNameW
GetTempPath	equ	GetTempPathW
lstrcat		equ	lstrcatW
lstrcmp		equ	lstrcmpW
lstrcmpi		equ	lstrcmpiW
lstrcpyn		equ	lstrcpynW
lstrcpy		equ	lstrcpyW
lstrlen		equ	lstrlenW
MoveFile	equ	MoveFileW
RemoveDirectory		equ	RemoveDirectoryW
SetFileAttributes		equ	SetFileAttributesW
WritePrivateProfileString	equ	WritePrivateProfileStringW
WritePrivateProfileStruct	equ	WritePrivateProfileStructW

STARTUPINFO	equ	STARTUPINFOW
WIN32_FIND_DATA		equ	WIN32_FIND_DATAW

	ELSE

CopyFile		equ	CopyFileA
CopyFileEx		equ	CopyFileExA
CreateEvent		equ	CreateEventA
CreateFile		equ	CreateFileA
CreateProcess		equ	CreateProcessA
CreateProcessAsUser	equ	CreateProcessAsUserA
CreateDirectory		equ	CreateDirectoryA
DeleteFile		equ	DeleteFileA
FindFirstFile		equ 	FindFirstFileA
FindFirstFileEx		equ	FindFirstFileExA
FindNextFile		equ 	FindNextFileA
FindResource		equ	FindResourceA
FindResourceEx		equ	FindResourceExA
FormatMessage		equ	FormatMessageA
GetCommandLine		equ	GetCommandLineA
GetFileAttributes		equ	GetFileAttributesA
GetModuleFileName		equ	GetModuleFileNameA
GetModuleHandle		equ	GetModuleHandleA
GetProfileInt		equ	GetProfileIntA
GetPrivateProfileInt	equ	GetPrivateProfileIntA
GetPrivateProfileSection	equ	GetPrivateProfileSectionA
GetPrivateProfileSectionNames	equ	GetPrivateProfileSectionNamesA
GetPrivateProfileString	equ	GetPrivateProfileStringA
GetPrivateProfileStruct	equ	GetPrivateProfileStructA
GetProfileSection		equ	GetProfileSectionA
GetProfileString		equ	GetProfileStringA
GetTempFileName		equ	GetTempFileNameA
GetTempPath	equ	GetTempPathA
lstrcat		equ	lstrcatA
lstrcmp		equ	lstrcmpA
lstrcmpi		equ	lstrcmpiA
lstrcpyn		equ	lstrcpynA
lstrcpy		equ	lstrcpyA
lstrlen		equ	lstrlenA
MoveFile	equ	MoveFileA
RemoveDirectory		equ	RemoveDirectoryA
SetFileAttributes		equ	SetFileAttributesA
WritePrivateProfileString	equ	WritePrivateProfileStringA
WritePrivateProfileStruct	equ	WritePrivateProfileStructA

STARTUPINFO		equ	STARTUPINFOA
WIN32_FIND_DATA		equ	WIN32_FIND_DATAA

	ENDIF


CloseHandle		proto	:QWORD
CopyFileA		proto	:QWORD, :QWORD, :DWORD
CopyFileExA		proto	:QWORD, :QWORD, :QWORD, :QWORD, :QWORD, :DWORD
CopyFileExW		proto	:QWORD, :QWORD, :QWORD, :QWORD, :QWORD, :DWORD
CreateDirectoryA		proto	:QWORD, :QWORD
CreateDirectoryW		proto	:QWORD, :QWORD
CreateThread		proto	:QWORD, :QWORD, :QWORD, :QWORD, :DWORD, :QWORD
CopyFileW		proto	:QWORD, :QWORD, :DWORD
CreateEvent		proto	:QWORD, :DWORD, :DWORD, :QWORD
CreateFileA		proto	:QWORD, :DWORD, :DWORD, :QWORD, :DWORD, :DWORD, :QWORD
CreateFileW		proto	:QWORD, :DWORD, :DWORD, :QWORD, :DWORD, :DWORD, :QWORD
CreateProcessA	proto	:QWORD, :QWORD, :QWORD, :QWORD, :DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :QWORD
CreateProcessW	proto	:QWORD, :QWORD, :QWORD, :QWORD, :DWORD, :DWORD, :QWORD, :QWORD, :QWORD, :QWORD
DebugBreak		proto
DeleteCriticalSection	proto	:QWORD
DeleteFileA		proto	:QWORD
DeleteFileW		proto	:QWORD
EnterCriticalSection	proto	:QWORD
ExitProcess		proto	:DWORD
ExitThread		proto	:DWORD
FileTimeToSystemTime	proto	:QWORD, :QWORD
FindClose		proto	:QWORD
FindFirstFileA		proto	:QWORD, :QWORD
FindFirstFileW		proto	:QWORD, :QWORD
FindNextFileA		proto	:QWORD, :QWORD
FindNextFileW		proto	:QWORD, :QWORD
FindResourceA		proto	:QWORD, :QWORD, :QWORD
FindResourceW		proto	:QWORD, :QWORD, :QWORD
FindResourceExA	proto	:QWORD, :QWORD, :QWORD, :QWORD
FindResourceExW		proto	:QWORD, :QWORD, :QWORD, :QWORD
FormatMessage		proto	:DWORD, :QWORD, :DWORD, :DWORD, :QWORD, :DWORD, :QWORD
FreeResource		proto	:QWORD
GetCommandLine	proto
GetCurrentProcessId	proto
GetFileAttributesA		proto	:QWORD
GetFileAttributesW		proto	:QWORD
GetFullPathNameA		proto	:QWORD, :DWORD, :QWORD, :QWORD
GetFullPathNameW		proto	:QWORD, :DWORD, :QWORD, :QWORD
GetLastError		proto
GetModuleFileNameA	proto	:QWORD, :QWORD, :DWORD
GetModuleFileNameW	proto	:QWORD, :QWORD, :DWORD
GetModuleHandleA		proto	:QWORD
GetModuleHandleW		proto	:QWORD
GetPrivateProfileInt	proto	:QWORD, :QWORD, :DWORD, :QWORD
GetPrivateProfileStringA	proto	:QWORD, :QWORD, :QWORD, :QWORD, :DWORD, :QWORD
GetPrivateProfileStringW	proto	:QWORD, :QWORD, :QWORD, :QWORD, :DWORD, :QWORD
GetPrivateProfileStructA	proto	:QWORD, :QWORD, :QWORD, :DWORD, :QWORD
GetPrivateProfileStructW	proto	:QWORD, :QWORD, :QWORD, :DWORD, :QWORD
GetProcessHeap		proto
GetTempFileNameA	proto	:QWORD, :QWORD, :DWORD, :QWORD
GetTempFileNameW	proto	:QWORD, :QWORD, :DWORD, :QWORD
GetTempPathA		proto	:DWORD, :QWORD
GetTempPathW		proto	:DWORD, :QWORD
GlobalAlloc		proto	:DWORD, :DWORD
GlobalFree		proto	:QWORD
HeapAlloc		proto	:QWORD, :DWORD, :QWORD
HeapFree		proto	:QWORD, :DWORD, :QWORD
InitializeCriticalSection	proto	:QWORD
LeaveCriticalSection	proto	:QWORD
LoadResource		proto	:QWORD, :QWORD
LocalFree		proto	:QWORD
LockResource		proto	:QWORD
lstrcatA		proto	:QWORD, :QWORD
lstrcatW		proto	:QWORD, :QWORD
lstrcpyA		proto	:QWORD, :QWORD
lstrcpyW		proto	:QWORD, :QWORD
lstrcpynA		proto	:QWORD, :QWORD, :DWORD
lstrcpynW		proto	:QWORD, :QWORD, :DWORD
lstrcmpA		proto	:QWORD, :QWORD
lstrcmpW		proto	:QWORD, :QWORD
lstrcmpiA		proto	:QWORD, :QWORD
lstrcmpiW		proto	:QWORD, :QWORD
lstrlenA		proto	:QWORD
lstrlenW		proto	:QWORD
MoveFileA		proto	:QWORD, :QWORD
MoveFileW		proto	:QWORD, :QWORD
OpenProcess		proto	:DWORD, :DWORD, :DWORD
RemoveDirectoryA		proto	:QWORD
RemoveDirectoryW		proto	:QWORD
ResetEvent		proto	:QWORD
SetEvent		proto	:QWORD
SetFileAttributesA		proto	:QWORD, :DWORD
SetFileAttributesW		proto	:QWORD, :DWORD
SizeofResource		proto	:QWORD, :QWORD
TerminateThread		proto	:QWORD, :DWORD
WaitForMultipleObjects	proto	:QWORD, :QWORD, :QWORD, :QWORD
WaitForSingleObject	proto	:QWORD, :DWORD
WriteFile		proto	:QWORD, :QWORD, :DWORD, :QWORD, :QWORD
WritePrivateProfileStringA	proto	:QWORD, :QWORD, :QWORD, :QWORD
WritePrivateProfileStringW	proto	:QWORD, :QWORD, :QWORD, :QWORD
WritePrivateProfileStructA	proto	:QWORD, :QWORD, :QWORD, :DWORD, :QWORD
WritePrivateProfileStructW	proto	:QWORD, :QWORD, :QWORD, :DWORD, :QWORD

CRITICAL_SECTION	equ	RTL_CRITICAL_SECTION


FILE_BEGIN		= 0
FILE_CURRENT		= 1
FILE_END		= 2

TIME_ZONE_ID_INVALID 	= -1
WAIT_FAILED 		= -1

WAIT_OBJECT_0			= STATUS_WAIT_0 + 0
WAIT_ABANDONED 		= STATUS_ABANDONED_WAIT_0 + 0
WAIT_ABANDONED_0 		= STATUS_ABANDONED_WAIT_0 + 0
WAIT_TIMEOUT			= STATUS_TIMEOUT
WAIT_IO_COMPLETION		= STATUS_USER_APC
STILL_ACTIVE			= STATUS_PENDING
EXCEPTION_ACCESS_VIOLATION		= STATUS_ACCESS_VIOLATION
EXCEPTION_DATATYPE_MISALIGNMENT	= STATUS_DATATYPE_MISALIGNMENT
EXCEPTION_BREAKPOINT		= STATUS_BREAKPOINT
EXCEPTION_SINGLE_STEP		= STATUS_SINGLE_STEP
EXCEPTION_ARRAY_BOUNDS_EXCEEDED	= STATUS_ARRAY_BOUNDS_EXCEEDED
EXCEPTION_FLT_DENORMAL_OPERAND	= STATUS_FLOAT_DENORMAL_OPERAND
EXCEPTION_FLT_DIVIDE_BY_ZERO		= STATUS_FLOAT_DIVIDE_BY_ZERO
EXCEPTION_FLT_INEXACT_RESULT		= STATUS_FLOAT_INEXACT_RESULT
EXCEPTION_FLT_INVALID_OPERATION	= STATUS_FLOAT_INVALID_OPERATION
EXCEPTION_FLT_OVERFLOW		= STATUS_FLOAT_OVERFLOW
EXCEPTION_FLT_STACK_CHECK		= STATUS_FLOAT_STACK_CHECK
EXCEPTION_FLT_UNDERFLOW		= STATUS_FLOAT_UNDERFLOW
EXCEPTION_INT_DIVIDE_BY_ZERO		= STATUS_INTEGER_DIVIDE_BY_ZERO
EXCEPTION_INT_OVERFLOW		= STATUS_INTEGER_OVERFLOW
EXCEPTION_PRIV_INSTRUCTION		= STATUS_PRIVILEGED_INSTRUCTION
EXCEPTION_IN_PAGE_ERROR		= STATUS_IN_PAGE_ERROR
EXCEPTION_ILLEGAL_INSTRUCTION		= STATUS_ILLEGAL_INSTRUCTION
EXCEPTION_NONCONTINUABLE_EXCEPTION	= STATUS_NONCONTINUABLE_EXCEPTION
EXCEPTION_STACK_OVERFLOW		= STATUS_STACK_OVERFLOW
EXCEPTION_INVALID_DISPOSITION		= STATUS_INVALID_DISPOSITION
EXCEPTION_GUARD_PAGE		= STATUS_GUARD_PAGE_VIOLATION
EXCEPTION_INVALID_HANDLE		= STATUS_INVALID_HANDLE
CONTROL_C_EXIT			= STATUS_CONTROL_C_EXIT


; Define possible return codes from the CopyFileEx callback routine

PROGRESS_CONTINUE	= 0
PROGRESS_CANCEL	= 1
PROGRESS_STOP		= 2
PROGRESS_QUIET		= 3

; Define CopyFileEx callback routine state change values

CALLBACK_CHUNK_FINISHED	= 0
CALLBACK_STREAM_SWITCH	= 1

; Define CopyFileEx option flags

COPY_FILE_FAIL_IF_EXISTS	= 1
COPY_FILE_RESTARTABLE	= 2

PIPE_ACCESS_INBOUND	= 1
PIPE_ACCESS_OUTBOUND	= 2
PIPE_ACCESS_DUPLEX	= 3

; Define the Named Pipe End flags for GetNamedPipeInfo

PIPE_CLIENT_END		= 0
PIPE_SERVER_END		= 1

; Define the dwPipeMode values for CreateNamedPipe

PIPE_WAIT		= 00000000
PIPE_NOWAIT		= 00000001
PIPE_READMODE_BYTE	= 00000000
PIPE_READMODE_MESSAGE	= 00000002
PIPE_TYPE_BYTE		= 00000000
PIPE_TYPE_MESSAGE	= 00000004

; Define the well known values for CreateNamedPipe nMaxInstances

PIPE_UNLIMITED_INSTANCES	= 255

; Define the Security Quality of Service bits to be passed into CreateFile

;SECURITY_ANONYMOUS	= SecurityAnonymous * 10000h
;SECURITY_IDENTIFICATION	= SecurityIdentification * 10000h
;SECURITY_IMPERSONATION	= SecurityImpersonation * 10000h
;SECURITY_DELEGATION	= SecurityDelegation * 10000h
SECURITY_CONTEXT_TRACKING	= 00040000h
SECURITY_EFFECTIVE_ONLY	= 00080000h
SECURITY_SQOS_PRESENT	= 00100000h
SECURITY_VALID_SQOS_FLAGS	= 001F0000h

; Global Memory Flags 

GMEM_FIXED		= 0000h
GMEM_MOVEABLE		= 0002h
GMEM_NOCOMPACT	= 0010h
GMEM_NODISCARD	= 0020h
GMEM_ZEROINIT		= 0040h
GMEM_MODIFY		= 0080h
GMEM_DISCARDABLE	= 0100h
GMEM_NOT_BANKED	= 1000h
GMEM_SHARE		= 2000h
GMEM_DDESHARE		= 2000h
GMEM_NOTIFY		= 4000h
GMEM_LOWER		= GMEM_NOT_BANKED
GMEM_VALID_FLAGS	= 7F72h
GMEM_INVALID_HANDLE	= 8000h

GHND		= GMEM_MOVEABLE + GMEM_ZEROINIT
GPTR		= GMEM_FIXED + GMEM_ZEROINIT

; Flags returned by GlobalFlags (in addition to GMEM_DISCARDABLE) 

GMEM_DISCARDED		= 4000h
GMEM_LOCKCOUNT	= 00FFh

INVALID_HANDLE_VALUE 	= -1
INVALID_FILE_SIZE	= -1
INVALID_SET_FILE_POINTER	= -1
INVALID_FILE_ATTRIBUTES	= -1

; File creation flags must start at the high end since they are combined with the attributes

FILE_FLAG_WRITE_THROUGH		= 80000000h
FILE_FLAG_OVERLAPPED		= 40000000h
FILE_FLAG_NO_BUFFERING		= 20000000h
FILE_FLAG_RANDOM_ACCESS		= 10000000h
FILE_FLAG_SEQUENTIAL_SCAN		= 08000000h
FILE_FLAG_DELETE_ON_CLOSE		= 04000000h
FILE_FLAG_BACKUP_SEMANTICS		= 02000000h
FILE_FLAG_POSIX_SEMANTICS		= 01000000h

CREATE_NEW		= 1
CREATE_ALWAYS		= 2
OPEN_EXISTING		= 3
OPEN_ALWAYS		= 4
TRUNCATE_EXISTING	= 5

; File System time stamps are represented with the following structure:

FILETIME 		STRUC
 ft_dwLowDateTime	dd	?
 ft_dwHighDateTime	dd	?
FILETIME		ENDS

; System time is represented with the following structure:

SYSTEMTIME 		STRUC
 st_wYear		dw	?
 st_wMonth		dw	?
 st_wDayOfWeek		dw	?
 st_wDay		dw	?
 st_wHour		dw	?
 st_wMinute		dw	?
 st_wSecond		dw	?
 st_wMilliseconds		dw	?
SYSTEMTIME		ENDS

WIN32_FIND_DATAA 	STRUC
 dwFileAttributes		dd	?
 ftCreationTime		FILETIME	<?>
 ftLastAccessTime		FILETIME	<?>
 ftLastWriteTime		FILETIME	<?>
 nFileSizeHigh		dd	?
 nFileSizeLow		dd	?
 dwReserved0		dd	?
 dwReserved1		dd	?
 cFileName		db	MAX_PATH dup(?)
 cAlternateFileName	db	14 dup(?)
 		db	?, ?
WIN32_FIND_DATAA	ENDS

WIN32_FIND_DATAW	STRUC
 dwFileAttributes		dd	?
 ftCreationTime		FILETIME	<?>
 ftLastAccessTime		FILETIME	<?>
 ftLastWriteTime		FILETIME	<?>
 nFileSizeHigh		dd	?
 nFileSizeLow		dd	?
 dwReserved0		dd	?
 dwReserved1		dd	?
 cFileName		dw	MAX_PATH dup(?)
 cAlternateFileName	dw	14 dup(?)
WIN32_FIND_DATAW	ENDS

FORMAT_MESSAGE_ALLOCATE_BUFFER	= 00000100h
FORMAT_MESSAGE_IGNORE_INSERTS	= 00000200h
FORMAT_MESSAGE_FROM_STRING		= 00000400h
FORMAT_MESSAGE_FROM_HMODULE		= 00000800h
FORMAT_MESSAGE_FROM_SYSTEM		= 00001000h
FORMAT_MESSAGE_ARGUMENT_ARRAY	= 00002000h
FORMAT_MESSAGE_MAX_WIDTH_MASK	= 000000FFh

;Stream Ids

BACKUP_INVALID		= 00000000
BACKUP_DATA		= 00000001
BACKUP_EA_DATA		= 00000002
BACKUP_SECURITY_DATA	= 00000003
BACKUP_ALTERNATE_DATA	= 00000004
BACKUP_LINK		= 00000005
BACKUP_PROPERTY_DATA	= 00000006

;Stream Attributes

STREAM_NORMAL_ATTRIBUTE	= 00000000
STREAM_MODIFIED_WHEN_READ	= 00000001
STREAM_CONTAINS_SECURITY	= 00000002
STREAM_CONTAINS_PROPERTIES	= 00000004

; Dual Mode API below this line. Dual Mode Structures also included.

STARTF_USESHOWWINDOW	= 00000001h
STARTF_USESIZE		= 00000002h
STARTF_USEPOSITION	= 00000004h
STARTF_USECOUNTCHARS	= 00000008h
STARTF_USEFILLATTRIBUTE	= 00000010h
STARTF_RUNFULLSCREEN	= 00000020h	; ignored for non-x86 platforms
STARTF_FORCEONFEEDBACK	= 00000040h
STARTF_FORCEOFFFEEDBACK	= 00000080h
STARTF_USESTDHANDLES	= 00000100h
STARTF_USEHOTKEY	= 00000200h

IGNORE		= 0 	; Ignore signal
INFINITE		= 0FFFFFFFFh	; Infinite timeout

STARTUPINFOA 	STRUC
 cb			dd	?
 lpReserved		dq	?
 lpDesktop		dq	?
 lpTitle			dq	?
 dwX			dd	?
 dwY			dd	?
 dwXSize		dd	?
 dwYSize		dd	?
 dwXCountChars	dd	?
 dwYCountChars	dd	?
 dwFillAttribute		dd	?
 dwFlags		dd	?
 wShowWindow		dw	?
 cbReserved2		dw	?
 lpReserved2		dq	?
 hStdInput		dq	?
 hStdOutput		dq	?
 hStdError		dq	?
STARTUPINFOA		ENDS

STARTUPINFOW	STRUC
 cb			dd	?
 lpReserved		dq	?
 lpDesktop		dq	?
 lpTitle			dq	?
 dwX			dd	?
 dwY			dd	?
 dwXSize		dd	?
 dwYSize		dd	?
 dwXCountChars	dd	?
 dwYCountChars	dd	?
 dwFillAttribute		dd	?
 dwFlags		dd	?
 wShowWindow		dw	?
 cbReserved2		dw	?
 lpReserved2		dq	?
 hStdInput		dq	?
 hStdOutput		dq	?
 hStdError		dq	?
STARTUPINFOW		ENDS

comment #

IFDEF UNICODE
AccessCheckAndAuditAlarm	equ	AccessCheckAndAuditAlarmW
AddAtom		equ	AddAtomW
BackupEventLog		equ	BackupEventLogW
BeginUpdateResource	equ	BeginUpdateResourceW
BuildCommDCB		equ	BuildCommDCBW
BuildCommDCBAndTimeouts	equ	BuildCommDCBAndTimeoutsW
CallNamedPipe		equ	CallNamedPipeW
ClearEventLog		equ	ClearEventLogW
CommConfigDialog		equ	CommConfigDialogW
CreateDirectoryEx		equ	CreateDirectoryExW
CreateFileMapping		equ	CreateFileMappingW
CreateMailslot		equ	CreateMailslotW
CreateMutex		equ	CreateMutexW
CreateNamedPipe		equ	CreateNamedPipeW
CreateSemaphore		equ	CreateSemaphoreW
CreateWaitableTimer	equ	CreateWaitableTimerW
DefineDosDevice		equ	DefineDosDeviceW
EndUpdateResource	equ	EndUpdateResourceW
EnumResourceLanguages	equ	EnumResourceLanguagesW
EnumResourceNames	equ	EnumResourceNamesW
EnumResourceTypes	equ	EnumResourceTypesW
ExpandEnvironmentStrings	equ	ExpandEnvironmentStringsW
FatalAppExit		equ	FatalAppExitW
FindAtom		equ	FindAtomW
FindFirstChangeNotification	equ	FindFirstChangeNotificationW
FindResourceEx		equ	FindResourceExW
FormatMessage		equ 	FormatMessageW
FreeEnvironmentStrings	equ	FreeEnvironmentStringsW
GetAtomName		equ	GetAtomNameW
GetBinaryType		equ	GetBinaryTypeW
GetCompressedFileSize	equ	GetCompressedFileSizeW
GetComputerName		equ	GetComputerNameW
GetCurrentDirectory	equ	GetCurrentDirectoryW
GetCurrentHwProfile	equ	GetCurrentHwProfileW
GetDefaultCommConfig	equ	GetDefaultCommConfigW
GetDiskFreeSpace		equ	GetDiskFreeSpaceW
GetDiskFreeSpaceEx	equ	GetDiskFreeSpaceExW
GetDriveType		equ	GetDriveTypeW
GetEnvironmentStrings	equ	GetEnvironmentStringsW
GetEnvironmentVariable	equ	GetEnvironmentVariableW
GetFileAttributesEx		equ	GetFileAttributesExW
GetFileSecurity		equ	GetFileSecurityW
GetFullPathName		equ	GetFullPathNameW
GetLogicalDriveStrings	equ	GetLogicalDriveStringsW
GetNamedPipeHandleState	equ	GetNamedPipeHandleStateW
GetShortPathName		equ	GetShortPathNameW
GetStartupInfo		equ	GetStartupInfoW
GetSystemDirectory	equ	GetSystemDirectoryW
GetUserName		equ	GetUserNameW
GetVersionEx		equ	GetVersionExW
GetVolumeInformation	equ	GetVolumeInformationW
GetWindowsDirectory	equ	GetWindowsDirectoryW
GlobalAddAtom		equ	GlobalAddAtomW
GlobalFindAtom		equ	GlobalFindAtomW
GlobalGetAtomName	equ	GlobalGetAtomNameW
IsBadStringPtr		equ	IsBadStringPtrW
LoadLibrary		equ	LoadLibraryW
LoadLibraryEx		equ	LoadLibraryExW
LogonUser		equ	LogonUserW
LookupAccountSid		equ	LookupAccountSidW
LookupAccountName	equ	LookupAccountNameW
LookupPrivilegeDisplayName	equ	LookupPrivilegeDisplayNameW
LookupPrivilegeName	equ	LookupPrivilegeNameW
LookupPrivilegeValue	equ	LookupPrivilegeValueW
MoveFile		equ	MoveFileW
MoveFileEx		equ	MoveFileExW
ObjectCloseAuditAlarm	equ	ObjectCloseAuditAlarmW
ObjectDeleteAuditAlarm	equ	ObjectDeleteAuditAlarmW
ObjectOpenAuditAlarm	equ	ObjectOpenAuditAlarmW
ObjectPrivilegeAuditAlarm	equ	ObjectPrivilegeAuditAlarmW
OpenBackupEventLog	equ	OpenBackupEventLogW
OpenEvent		equ	OpenEventW
OpenEventLog		equ	OpenEventLogW
OpenFileMapping		equ	OpenFileMappingW
OpenMutex		equ	OpenMutexW
OpenSemaphore		equ	OpenSemaphoreW
OpenWaitableTimer		equ	OpenWaitableTimerW
OutputDebugString		equ	OutputDebugStringW
PrivilegedServiceAuditAlarm	equ	PrivilegedServiceAuditAlarmW
QueryDosDevice		equ	QueryDosDeviceW
ReadEventLog		equ	ReadEventLogW
RegisterEventSource	equ	RegisterEventSourceW
ReportEvent		equ	ReportEventW
SearchPath		equ	SearchPathW
SetComputerName		equ	SetComputerNameW
SetCurrentDirectory	equ	SetCurrentDirectoryW
SetDefaultCommConfig	equ	SetDefaultCommConfigW
SetEnvironmentVariable	equ	SetEnvironmentVariableW
SetFileAttributes		equ	SetFileAttributesW
SetFileSecurity		equ	SetFileSecurityW
SetVolumeLabel		equ	SetVolumeLabelW
UpdateResource		equ	UpdateResourceW
WaitNamedPipe		equ	WaitNamedPipeW
WritePrivateProfileSection	equ	WritePrivateProfileSectionW
WritePrivateProfileString	equ	WritePrivateProfileStringW
WriteProfileSection		equ	WriteProfileSectionW
WriteProfileString		equ	WriteProfileStringW
ELSE
AccessCheckAndAuditAlarm	equ	AccessCheckAndAuditAlarmA
AddAtom		equ	AddAtomA
BackupEventLog		equ	BackupEventLogA
BeginUpdateResource	equ	BeginUpdateResourceA
BuildCommDCB		equ	BuildCommDCBA
BuildCommDCBAndTimeouts	equ	BuildCommDCBAndTimeoutsA
CallNamedPipe		equ	CallNamedPipeA
ClearEventLog		equ	ClearEventLogA
CommConfigDialog		equ	CommConfigDialogA
CopyFile		equ	CopyFileA
CopyFileEx		equ	CopyFileExA
CreateDirectory		equ	CreateDirectoryA
CreateDirectoryEx		equ	CreateDirectoryExA
CreateFileMapping		equ	CreateFileMappingA
CreateMailslot		equ	CreateMailslotA
CreateMutex		equ	CreateMutexA
CreateNamedPipe		equ	CreateNamedPipeA
CreateSemaphore		equ	CreateSemaphoreA
CreateWaitableTimer	equ	CreateWaitableTimerA
DefineDosDevice		equ	DefineDosDeviceA
DeleteFile		equ	DeleteFileA
EndUpdateResource	equ	EndUpdateResourceA
EnumResourceLanguages	equ	EnumResourceLanguagesA
EnumResourceNames	equ	EnumResourceNamesA
EnumResourceTypes	equ	EnumResourceTypesA
ExpandEnvironmentStrings	equ	ExpandEnvironmentStringsA
FatalAppExit		equ	FatalAppExitA
FindAtom		equ	FindAtomA
FindFirstChangeNotification	equ	FindFirstChangeNotificationA
FindFirstFile		equ 	FindFirstFileA
FindNextFile		equ 	FindNextFileA
FindFirstFileEx		equ	FindFirstFileExA
FindResourceEx		equ	FindResourceExA
FormatMessage		equ 	FormatMessageA
FreeEnvironmentStrings	equ	FreeEnvironmentStringsA
GetAtomName		equ	GetAtomNameA
GetBinaryType		equ	GetBinaryTypeA
GetCommandLine		equ	GetCommandLineA
GetCompressedFileSize	equ	GetCompressedFileSizeA
GetComputerName		equ	GetComputerNameA
GetCurrentDirectory	equ	GetCurrentDirectoryA
GetCurrentHwProfile	equ	GetCurrentHwProfileA
GetDefaultCommConfig	equ	GetDefaultCommConfigA
GetDiskFreeSpace		equ	GetDiskFreeSpaceA
GetDiskFreeSpaceEx	equ	GetDiskFreeSpaceExA
GetDriveType		equ	GetDriveTypeA
GetEnvironmentStrings	equ	GetEnvironmentStringsA
GetEnvironmentVariable	equ	GetEnvironmentVariableA
GetFileAttributesEx		equ	GetFileAttributesExA
GetFileSecurity		equ	GetFileSecurityA
GetFullPathName		equ	GetFullPathNameA
GetLogicalDriveStrings	equ	GetLogicalDriveStringsA
GetNamedPipeHandleState	equ	GetNamedPipeHandleStateA
GetShortPathName		equ	GetShortPathNameA
GetStartupInfo		equ	GetStartupInfoA
GetSystemDirectory	equ	GetSystemDirectoryA
GetUserName		equ	GetUserNameA
GetVersionEx		equ	GetVersionExA
GetVolumeInformation	equ	GetVolumeInformationA
GetWindowsDirectory	equ	GetWindowsDirectoryA
GlobalAddAtom		equ	GlobalAddAtomA
GlobalFindAtom		equ	GlobalFindAtomA
GlobalGetAtomName	equ	GlobalGetAtomNameA
IsBadStringPtr		equ	IsBadStringPtrA
LoadLibrary		equ	LoadLibraryA
LoadLibraryEx		equ	LoadLibraryExA
LogonUser		equ	LogonUserA
LookupAccountSid		equ	LookupAccountSidA
LookupAccountName	equ	LookupAccountNameA
LookupPrivilegeDisplayName	equ	LookupPrivilegeDisplayNameA
LookupPrivilegeName	equ	LookupPrivilegeNameA
LookupPrivilegeValue	equ	LookupPrivilegeValueA
MoveFile		equ	MoveFileA
MoveFileEx		equ	MoveFileExA
ObjectCloseAuditAlarm	equ	ObjectCloseAuditAlarmA
ObjectDeleteAuditAlarm	equ	ObjectDeleteAuditAlarmA
ObjectOpenAuditAlarm	equ	ObjectOpenAuditAlarmA
ObjectPrivilegeAuditAlarm	equ	ObjectPrivilegeAuditAlarmA
OpenBackupEventLog	equ	OpenBackupEventLogA
OpenEvent		equ	OpenEventA
OpenEventLog		equ	OpenEventLogA
OpenFileMapping		equ	OpenFileMappingA
OpenMutex		equ	OpenMutexA
OpenSemaphore		equ	OpenSemaphoreA
OpenWaitableTimer		equ	OpenWaitableTimerA
OutputDebugString		equ	OutputDebugStringA
PrivilegedServiceAuditAlarm	equ	PrivilegedServiceAuditAlarmA
QueryDosDevice		equ	QueryDosDeviceA
ReadEventLog		equ	ReadEventLogA
RegisterEventSource	equ	RegisterEventSourceA
RemoveDirectory		equ	RemoveDirectoryA
ReportEvent		equ	ReportEventA
SearchPath		equ	SearchPathA
SetComputerName		equ	SetComputerNameA
SetCurrentDirectory	equ	SetCurrentDirectoryA
SetDefaultCommConfig	equ	SetDefaultCommConfigA
SetEnvironmentVariable	equ	SetEnvironmentVariableA
SetFileAttributes		equ	SetFileAttributesA
SetFileSecurity		equ	SetFileSecurityA
SetVolumeLabel		equ	SetVolumeLabelA
UpdateResource		equ	UpdateResourceA
WaitNamedPipe		equ	WaitNamedPipeA
WritePrivateProfileSection	equ	WritePrivateProfileSectionA
WritePrivateProfileString	equ	WritePrivateProfileStringA
WritePrivateProfileStruct	equ	WritePrivateProfileStructA
WriteProfileSection		equ	WriteProfileSectionA
WriteProfileString		equ	WriteProfileStringA
ENDIF


; dos executable file header - self made !

DOS_FILEHEADER		STRUC
 dfh_wSignum		dw	?
 dfh_wLength		dw	?
 dfh_wLengthAdd		dw	?
 dfh_wSegments		dw	?
 dfh_wHeaderSize		dw	?
 dfh_wMinPara		dw	?
 dfh_wMaxPara		dw	?
 dfh_wStackReg		dw	?
 dfh_wCheckSum		dw	?
 dfh_wInstReg		dw	?
 dfh_wCodeStart		dw	?
 dfh_wReloTable		dw	?
 dfh_wOverlay		dw	?
 dfh_wBuffer		dw	?
DOS_FILEHEADER		ENDS

; File structures

OVERLAPPED 		STRUC
 ol_Internal		dd	?
 ol_InternalHigh		dd	?
 ol_Offset		dd	?
 ol_OffsetHigh		dd	?
 ol_hEvent		HANDLE	?
OVERLAPPED		ENDS

SECURITY_ATTRIBUTES 	STRUC
 sa_nLength		dd	?
 sa_lpSecurityDescriptor	dd	?
 sa_bInheritHandle		dd	?
SECURITY_ATTRIBUTES	ENDS

PROCESS_INFORMATION 	STRUC
 pin_hProcess	HANDLE	?
 pin_hThread	HANDLE	?
 pin_dwProcessId	dd	?
 pin_dwThreadId	dd	?
PROCESS_INFORMATION	ENDS



MUTEX_MODIFY_STATE	equ	MUTANT_QUERY_STATE
MUTEX_ALL_ACCESS	equ	MUTANT_ALL_ACCESS

; Serial provider type.

SP_SERIALCOMM		= 1

; Provider SubTypes

PST_UNSPECIFIED		= 00000000h
PST_RS232		= 00000001h
PST_PARALLELPORT	= 00000002h
PST_RS422		= 00000003h
PST_RS423		= 00000004h
PST_RS449		= 00000005h
PST_MODEM		= 00000006h
PST_FAX		= 00000021h
PST_SCANNER		= 00000022h
PST_NETWORK_BRIDGE	= 00000100h
PST_LAT		= 00000101h
PST_TCPIP_TELNET	= 00000102h
PST_X25		= 00000103h


; Provider capabilities flags.

PCF_DTRDSR		= 0001h
PCF_RTSCTS		= 0002h
PCF_RLSD		= 0004h
PCF_PARITY_CHECK	= 0008h
PCF_XONXOFF		= 0010h
PCF_SETXCHAR		= 0020h
PCF_TOTALTIMEOUTS	= 0040h
PCF_INTTIMEOUTS	= 0080h
PCF_SPECIALCHARS	= 0100h
PCF_16BITMODE		= 0200h

; Comm provider settable parameters.

SP_PARITY		= 0001h
SP_BAUD		= 0002h
SP_DATABITS		= 0004h
SP_STOPBITS		= 0008h
SP_HANDSHAKING	= 0010h
SP_PARITY_CHECK		= 0020h
SP_RLSD		= 0040h

; Settable baud rates in the provider.

BAUD_075	= 00000001h
BAUD_110	= 00000002h
BAUD_134_5	= 00000004h
BAUD_150	= 00000008h
BAUD_300	= 00000010h
BAUD_600	= 00000020h
BAUD_1200	= 00000040h
BAUD_1800	= 00000080h
BAUD_2400	= 00000100h
BAUD_4800	= 00000200h
BAUD_7200	= 00000400h
BAUD_9600	= 00000800h
BAUD_14400	= 00001000h
BAUD_19200	= 00002000h
BAUD_38400	= 00004000h
BAUD_56K	= 00008000h
BAUD_128K	= 00010000h
BAUD_115200	= 00020000h
BAUD_57600	= 00040000h
BAUD_USER	= 10000000h

; Settable Data Bits

DATABITS_5	= 0001h
DATABITS_6	= 0002h
DATABITS_7	= 0004h
DATABITS_8	= 0008h
DATABITS_16 	= 0010h
DATABITS_16X	= 0020h

;
; Settable Stop and Parity bits.
;

STOPBITS_10 	= 0001h
STOPBITS_15 	= 0002h
STOPBITS_20 	= 0004h
PARITY_NONE 	= 0100h
PARITY_ODD	= 0200h
PARITY_EVEN 	= 0400h
PARITY_MARK 	= 0800h
PARITY_SPACE	= 1000h

COMMPROP 		STRUC
 cmp_wPacketLength	dw	?
 cmp_wPacketVersion	dw	?
 cmp_dwServiceMask	dd	?
 cmp_dwReserved1		dd	?
 cmp_dwMaxTxQueue	dd	?
 cmp_dwMaxRxQueue	dd	?
 cmp_dwMaxBaud		dd	?
 cmp_dwProvSubType	dd	?
 cmp_dwProvCapabilities	dd	?
 cmp_dwSettableParams	dd	?
 cmp_dwSettableBaud	dd	?
 cmp_wSettableData	dd	?
 cmp_wSettableStopParity	dd	?
 cmp_dwCurrentTxQueue	dd	?
 cmp_dwCurrentRxQueue	dd	?
 cmp_dwProvSpec1		dd	?
 cmp_dwProvSpec2		dd	?
 cmp_wcProvChar		db	?
COMMPROP		ENDS

; Set dwProvSpec1 to COMMPROP_INITIALIZED to indicate that wPacketLength
; is valid before a call to GetCommProperties().

COMMPROP_INITIALIZED	= 0E73CF52Eh

COMSTAT 		STRUC
 cst_fCtsHold		dd	TRUE
 cst_fDsrHold		dd	TRUE
 cst_fRlsdHold		dd	TRUE
 cst_fXoffHold		dd	TRUE
 cst_fXoffSent		dd	TRUE
 cst_fEof		dd	TRUE
 cst_fTxim		dd	TRUE
 cst_fReserved		dd	25
 cst_cbInQue		dd	?
 cst_cbOutQue		dd	?
COMSTAT		ENDS

; DTR Control Flow Values.

DTR_CONTROL_DISABLE	= 00
DTR_CONTROL_ENABLE	= 01
DTR_CONTROL_HANDSHAKE	= 02

; RTS Control Flow Values

RTS_CONTROL_DISABLE	= 00
RTS_CONTROL_ENABLE	= 01
RTS_CONTROL_HANDSHAKE	= 02
RTS_CONTROL_TOGGLE	= 03

DCB 		STRUC
 dcb_DCBlength		dd	?	; sizeofDCB) 
 dcb_BaudRate		dd	?	; Baudrate at which running 
 dcb_flags		dd	?

 dcb_fBinary		dd	TRUE	; Binary Mode skip EOF check)
 dcb_fParity		dd	TRUE	; Enable parity checking
 dcb_fOutxCtsFlow		dd	TRUE	; CTS handshaking on output 
 dcb_fOutxDsrFlow		dd	TRUE	; DSR handshaking on output 
 dcb_fDtrControl		dd	2	; DTR Flow control
 dcb_fDsrSensitivity	dd	TRUE	; DSR Sensitivity
 dcb_fTXContinueOnXoff	dd	TRUE	; Continue TX when Xoff sent 
 dcb_fOutX		dd	TRUE	; Enable output X-ON/X-OFF
 dcb_fInX		dd	TRUE	; Enable input X-ON/X-OFF 
 dcb_fErrorChar		dd	TRUE	; Enable Err Replacement
 dcb_fNull		dd	TRUE	; Enable Null stripping 
 dcb_fRtsControl		dd	2	; Rts Flow control
 dcb_fAbortOnError		dd	TRUE	; Abort all reads and writes on Error 
 dcb_fDummy2		dd	17	; Reserved

 dcb_wReserved		dw	?	; Not currently used
 dcb_XonLim		dw	?	; Transmit X-ON threshold 
 dcb_XoffLim		dw	?	; Transmit X-OFF threshold
 dcb_ByteSize		db	?	; Number of bits/byte, 4-8
 dcb_Parity		db	?	; 0-4 = None,Odd,Even,Mark,Space
 dcb_StopBits		db	?	; 0,1,2		= 1, 1.5, 2 
 dcb_XonChar		db	?	; Tx and Rx X-ON character
 dcb_XoffChar		db	?	; Tx and Rx X-OFF character 
 dcb_ErrorChar		db	?	; Error replacement char
 dcb_EofChar		db	?	; End of Input character
 dcb_EvtChar		db	?	; Received Event character
 dcb_wReserved1		dw	?	; Fill for now. 
DCB		ENDS

COMMTIMEOUTS 		STRUC
 cto_ReadIntervalTimeout	dd	?	; Maximum time between read chars. 
 cto_ReadTotalTimeoutMultiplier	dd	?	; Multiplier of characters.
 cto_ReadTotalTimeoutConstant	dd	?	; Constant in milliseconds.
 cto_WriteTotalTimeoutMultiplier	dd	?	; Multiplier of characters.
 cto_WriteTotalTimeoutConstant	dd	?	; Constant in milliseconds.
COMMTIMEOUTS		ENDS

COMMCONFIG 		STRUC
 ccn_dwSize		dd	?	;Size of the entire struct 
 ccn_wVersion		dw	?	; version of the structure 
 ccn_wReserved		dw	?	;alignment 
 ccn_dcb		DCB	<?>	; device control block 
 ccn_dwProviderSubType	dd	?	; ordinal value for identifying provider-defined data structure format
 ccn_dwProviderOffset	dd	?	;Specifies the offset of provider specific data field in bytes from the start 
 ccn_dwProviderSize	dd	?	;size of the provider-specific data field 
 ccn_wcProviderData	dw	?	; provider-specific data 
COMMCONFIG		ENDS

SYSTEM_INFO 		STRUC
; sinf_dwOemId:		; Obsolete field...do not use
 sif_wProcessorArchitecture	dw	?
 sif_wReserved		dw	?
 sif_dwPageSize		dd	?
 sif_lpMinimumApplicationAddress	dd	?
 sif_lpMaximumApplicationAddress	dd	?
 sif_dwActiveProcessorMask	dd	?
 sif_dwNumberOfProcessors	dd	?
 sif_dwProcessorType	dd	?
 sif_dwAllocationGranularity	dd	?
 sif_wProcessorLevel	dw	?
 sif_wProcessorRevision	dw	?
SYSTEM_INFO		ENDS



MEMORYSTATUS 		STRUC
 mst_dwLength		dd	?
 mst_dwMemoryLoad	dd	?
 mst_dwTotalPhys		dd	?
 mst_dwAvailPhys		dd	?
 mst_dwTotalPageFile	dd	?
 mst_dwAvailPageFile	dd	?
 mst_dwTotalVirtual		dd	?
 mst_dwAvailVirtual		dd	?
MEMORYSTATUS		ENDS

; Local Memory Flags

LMEM_FIXED		= 0000h
LMEM_MOVEABLE		= 0002h
LMEM_NOCOMPACT	= 0010h
LMEM_NODISCARD	= 0020h
LMEM_ZEROINIT		= 0040h
LMEM_MODIFY		= 0080h
LMEM_DISCARDABLE	= 0F00h
LMEM_VALID_FLAGS	= 0F72h
LMEM_INVALID_HANDLE	= 8000h

LHND		= LMEM_MOVEABLE + LMEM_ZEROINIT
LPTR		= LMEM_FIXED + LMEM_ZEROINIT
NONZEROLHND		= LMEM_MOVEABLE
NONZEROLPTR		= LMEM_FIXED

; Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE) 

LMEM_DISCARDED		= 4000h
LMEM_LOCKCOUNT	= 00FFh

; dwCreationFlag values

DEBUG_PROCESS		= 00000001h
DEBUG_ONLY_THIS_PROCESS	= 00000002h
CREATE_SUSPENDED	= 00000004h
DETACHED_PROCESS	= 00000008h
CREATE_NEW_CONSOLE	= 00000010h
NORMAL_PRIORITY_CLASS	= 00000020h
IDLE_PRIORITY_CLASS	= 00000040h
HIGH_PRIORITY_CLASS	= 00000080h
REALTIME_PRIORITY_CLASS	= 00000100h
CREATE_NEW_PROCESS_GROUP	= 00000200h
CREATE_UNICODE_ENVIRONMENT	= 00000400h
CREATE_SEPARATE_WOW_VDM	= 00000800h
CREATE_SHARED_WOW_VDM	= 00001000h
CREATE_FORCEDOS	= 00002000h
CREATE_DEFAULT_ERROR_MODE	= 04000000h
CREATE_NO_WINDOW	= 08000000h
PROFILE_USER		= 10000000h
PROFILE_KERNEL		= 20000000h
PROFILE_SERVER		= 40000000h

THREAD_PRIORITY_LOWEST	= THREAD_BASE_PRIORITY_MIN
THREAD_PRIORITY_BELOW_NORMAL	= THREAD_PRIORITY_LOWEST + 1
THREAD_PRIORITY_NORMAL	= 0
THREAD_PRIORITY_HIGHEST	= THREAD_BASE_PRIORITY_MAX
THREAD_PRIORITY_ABOVE_NORMAL	= THREAD_PRIORITY_HIGHEST - 1
THREAD_PRIORITY_ERROR_RETURN	= MAXLONG
THREAD_PRIORITY_TIME_CRITICAL	= THREAD_BASE_PRIORITY_LOWRT
THREAD_PRIORITY_IDLE	= THREAD_BASE_PRIORITY_IDLE

; Debug APIs

EXCEPTION_DEBUG_EVENT	= 1
CREATE_THREAD_DEBUG_EVENT	= 2
CREATE_PROCESS_DEBUG_EVENT	= 3
EXIT_THREAD_DEBUG_EVENT	= 4
EXIT_PROCESS_DEBUG_EVENT	= 5
LOAD_DLL_DEBUG_EVENT	= 6
UNLOAD_DLL_DEBUG_EVENT	= 7
OUTPUT_DEBUG_STRING_EVENT	= 8
RIP_EVENT		= 9

;EXCEPTION_DEBUG_INFO 	STRUC
; edi_ExceptionRecord	EXCEPTION_RECORD	<?>
; edi_dwFirstChance		dd	?
;EXCEPTION_DEBUG_INFO	ENDS

CREATE_THREAD_DEBUG_INFO 	STRUC
 ctdi_hThread		HANDLE	?
 ctdi_lpThreadLocalBase	dd	?
 ctdi_lpStartAddress	dd	?
CREATE_THREAD_DEBUG_INFO	ENDS

CREATE_PROCESS_DEBUG_INFO 	STRUC
 cpdi_hFile		HANDLE	?
 cpdi_hProcess		HANDLE	?
 cpdi_hThread		HANDLE	?
 cpdi_lpBaseOfImage	dd	?
 cpdi_dwDebugInfoFileOffset	dd	?
 cpdi_nDebugInfoSize	dd	?
 cpdi_lpThreadLocalBase	dd	?
 cpdi_lpStartAddress	dd	?
 cpdi_lpImageName		dd	?
 cpdi_fUnicode		dw	?
CREATE_PROCESS_DEBUG_INFO	ENDS

EXIT_THREAD_DEBUG_INFO 	STRUC
 etdi_dwExitCode		dd	?
EXIT_THREAD_DEBUG_INFO	ENDS

EXIT_PROCESS_DEBUG_INFO 	STRUC
 epdi_dwExitCode		dd	?
EXIT_PROCESS_DEBUG_INFO	ENDS

LOAD_DLL_DEBUG_INFO 	STRUC
 lddi_hFile		HANDLE	?
 lddi_lpBaseOfDll		dd	?
 lddi_dwDebugInfoFileOffset	dd	?
 lddi_nDebugInfoSize	dd	?
 lddi_lpImageName		dd	?
 lddi_fUnicode		dw	?
LOAD_DLL_DEBUG_INFO	ENDS

UNLOAD_DLL_DEBUG_INFO 	STRUC
 uddi_lpBaseOfDll		dd	?
UNLOAD_DLL_DEBUG_INFO	ENDS

OUTPUT_DEBUG_STRING_INFO 	STRUC
 odsi_lpDebugStringData	dd	?
 odsi_fUnicode		dw	?
 odsi_nDebugStringLength	dw	?
OUTPUT_DEBUG_STRING_INFO	ENDS

RIP_INFO 		STRUC
 rinf_dwError		dd	?
 rinf_dwType		dd	?
RIP_INFO		ENDS

;; DEBUG_EVENT

DRIVE_UNKNOWN		= 0
DRIVE_NO_ROOT_DIR	= 1
DRIVE_REMOVABLE	= 2
DRIVE_FIXED		= 3
DRIVE_REMOTE		= 4
DRIVE_CDROM		= 5
DRIVE_RAMDISK		= 6

GetFreeSpace		= 100000h

FILE_TYPE_UNKNOWN	= 0000h
FILE_TYPE_DISK		= 0001h
FILE_TYPE_CHAR		= 0002h
FILE_TYPE_PIPE		= 0003h
FILE_TYPE_REMOTE	= 8000h

STD_INPUT_HANDLE	= -10
STD_OUTPUT_HANDLE	= -11
STD_ERROR_HANDLE	= -12

NOPARITY		= 0
ODDPARITY		= 1
EVENPARITY		= 2
MARKPARITY		= 3
SPACEPARITY		= 4

ONESTOPBIT		= 0
ONE5STOPBITS		= 1
TWOSTOPBITS		= 2


; Baud rates at which the communication device operates

CBR_110		= 110
CBR_300		= 300
CBR_600		= 600
CBR_1200		= 1200
CBR_2400		= 2400
CBR_4800		= 4800
CBR_9600		= 9600
CBR_14400		= 14400
CBR_19200		= 19200
CBR_38400		= 38400
CBR_56000		= 56000
CBR_57600		= 57600
CBR_115200		= 115200
CBR_128000		= 128000
CBR_256000		= 256000

; Error Flags

CE_RXOVER		= 0001h	; Receive Queue overflow
CE_OVERRUN		= 0002h	; Receive Overrun Error
CE_RXPARITY		= 0004h	; Receive Parity Error
CE_FRAME		= 0008h	; Receive Framing error
CE_BREAK		= 0010h	; Break Detected
CE_TXFULL		= 0100h	; TX Queue is full
CE_PTO		= 0200h	; LPTx Timeout
CE_IOE		= 0400h	; LPTx I/O Error
CE_DNS		= 0800h	; LPTx Device not selected
CE_OOP		= 1000h	; LPTx Out-Of-Paper
CE_MODE		= 8000h	; Requested mode unsupported

IE_BADID		= (-1)	; Invalid or unsupported id
IE_OPEN		= (-2)	; Device Already Open
IE_NOPEN		= (-3)	; Device Not Open
IE_MEMORY		= (-4)	; Unable to allocate queues
IE_DEFAULT		= (-5)	; Error in default parameters
IE_HARDWARE		= (-10)	; Hardware Not Present
IE_BYTESIZE		= (-11) 	; Illegal Byte Size
IE_BAUDRATE		= (-12) 	; Unsupported BaudRate

; Events

EV_RXCHAR		= 0001h	; Any Character received
EV_RXFLAG		= 0002h	; Received certain character
EV_TXEMPTY		= 0004h	; Transmitt Queue Empty
EV_CTS		= 0008h	; CTS changed state
EV_DSR		= 0010h	; DSR changed state
EV_RLSD		= 0020h	; RLSD changed state
EV_BREAK		= 0040h	; BREAK received
EV_ERR		= 0080h	; Line status error occurred
EV_RING		= 0100h	; Ring signal detected
EV_PERR		= 0200h	; Printer error occured
EV_RX80FULL		= 0400h	; Receive buffer is 80 percent full
EV_EVENT1		= 0800h	; Provider specific event 1
EV_EVENT2		= 1000h	; Provider specific event 2

; Escape Functions

SETXOFF		= 1 	; Simulate XOFF received
SETXON		= 2	 ; Simulate XON received
SETRTS		= 3	 ; Set RTS high
CLRRTS		= 4	 ; Set RTS low
SETDTR		= 5	 ; Set DTR high
CLRDTR		= 6	 ; Set DTR low
RESETDEV		= 7	 ; Reset device if possible
SETBREAK		= 8	 ; Set the device break line.
CLRBREAK		= 9	 ; Clear the device break line.

; PURGE function flags.

PURGE_TXABORT		= 0001h	; Kill the pending/current writes to the comm port.
PURGE_RXABORT		= 0002h	; Kill the pending/current reads to the comm port.
PURGE_TXCLEAR		= 0004h	; Kill the transmit queue if there.
PURGE_RXCLEAR		= 0008h	; Kill the typeahead buffer if there.

LPTx		= 80h	; Set if ID is for LPT device

; Modem Status Flags

MS_CTS_ON		= 0010h
MS_DSR_ON		= 0020h
MS_RING_ON		= 0040h
MS_RLSD_ON		= 0080h

; WaitSoundState() Constants

S_QUEUEEMPTY		= 0
S_THRESHOLD		= 1
S_ALLTHRESHOLD		= 2

; Accent Modes

S_NORMAL		= 0
S_LEGATO		= 1
S_STACCATO		= 2

; SetSoundNoise() Sources

S_PERIOD512		= 0 ; Freq		= N/512 high pitch, less coarse hiss
S_PERIOD1024		= 1 ; Freq		= N/1024
S_PERIOD2048		= 2 ; Freq		= N/2048 low pitch, more coarse hiss
S_PERIODVOICE		= 3 ; Source is frequency from voice channel (3)
S_WHITE512		= 4 ; Freq		= N/512 high pitch, less coarse hiss
S_WHITE1024		= 5 ; Freq		= N/1024
S_WHITE2048		= 6 ; Freq		= N/2048 low pitch, more coarse hiss
S_WHITEVOICE		= 7 ; Source is frequency from voice channel (3)

S_SERDVNA		= -1	; Device not available
S_SEROFM		= -2	; Out of memory
S_SERMACT		= -3	; Music active
S_SERQFUL		= -4	; Queue full
S_SERBDNT		= -5	; Invalid note
S_SERDLN		= -6	; Invalid note length
S_SERDCC		= -7	; Invalid note count
S_SERDTP		= -8	; Invalid tempo
S_SERDVL		= -9	; Invalid volume
S_SERDMD		= -10	 ; Invalid mode
S_SERDSH		= -11	 ; Invalid shape
S_SERDPT		= -12	 ; Invalid pitch
S_SERDFQ		= -13	 ; Invalid frequency
S_SERDDR		= -14	 ; Invalid duration
S_SERDSR		= -15	 ; Invalid source
S_SERDST		= -16	 ; Invalid state

NMPWAIT_WAIT_FOREVER	= -1
NMPWAIT_NOWAIT	= 00000001
NMPWAIT_USE_DEFAULT_WAIT	= 00000000

FS_CASE_IS_PRESERVED	= FILE_CASE_PRESERVED_NAMES
FS_CASE_SENSITIVE	= FILE_CASE_SENSITIVE_SEARCH
FS_UNICODE_STORED_ON_DISK	= FILE_UNICODE_ON_DISK
FS_PERSISTENT_ACLS	= FILE_PERSISTENT_ACLS
FS_VOL_IS_COMPRESSED	= FILE_VOLUME_IS_COMPRESSED
FS_FILE_COMPRESSION	= FILE_FILE_COMPRESSION

FILE_MAP_COPY		= SECTION_QUERY
FILE_MAP_WRITE		= SECTION_MAP_WRITE
FILE_MAP_READ		= SECTION_MAP_READ
FILE_MAP_ALL_ACCESS	= SECTION_ALL_ACCESS

OF_READ		= 00000000h
OF_WRITE		= 00000001h
OF_READWRITE		= 00000002h
OF_SHARE_COMPAT	= 00000000h
OF_SHARE_EXCLUSIVE	= 00000010h
OF_SHARE_DENY_WRITE	= 00000020h
OF_SHARE_DENY_READ	= 00000030h
OF_SHARE_DENY_NONE	= 00000040h
OF_PARSE		= 00000100h
OF_DELETE		= 00000200h
OF_VERIFY		= 00000400h
OF_CANCEL		= 00000800h
OF_CREATE		= 00001000h
OF_PROMPT		= 00002000h
OF_EXIST		= 00004000h
OF_REOPEN		= 00008000h

OFS_MAXPATHNAME	=128


OFSTRUCT 		STRUC
 of_cBytes		db	?
 of_fFixedDisk		db	?
 of_nErrCode		dw	?
 of_Reserved1		dw	?
 of_Reserved2		dw	?
 of_szPathName		db	OFS_MAXPATHNAME dup(?)
OFSTRUCT		ENDS

PROCESS_HEAP_ENTRY 	STRUC
 phe_lpData		dd	?	;; dq ?
 phe_cbData		dd	?
 phe_cbOverhead		db	?
 phe_iRegionIndex		db	?
 phe_wFlags		dw	?

; phe_hMem:
 phe_dwCommittedSize	dd	?
; phe_dwReserved:
 phe_dwUnCommittedSize	dd	?
 phe_lpFirstBlock		dd	?
 phe_lpLastBlock		dd	?
; phe_Block:
 phe_Region		dd	?
PROCESS_HEAP_ENTRY	ENDS

PROCESS_HEAP_REGION		= 0001h
PROCESS_HEAP_UNCOMMITTED_RANGE	= 0002h
PROCESS_HEAP_ENTRY_BUSY		= 0004h
PROCESS_HEAP_ENTRY_MOVEABLE		= 0010h
PROCESS_HEAP_ENTRY_DDESHARE		= 0020h

; GetBinaryType return values.

SCS_32BIT_BINARY	= 0
SCS_DOS_BINARY		= 1
SCS_WOW_BINARY	= 2
SCS_PIF_BINARY		= 3
SCS_POSIX_BINARY	= 4
SCS_OS216_BINARY	= 5

SEM_FAILCRITICALERRORS	= 0001h
SEM_NOGPFAULTERRORBOX	= 0002h
SEM_NOALIGNMENTFAULTEXCEPT	= 0004h
SEM_NOOPENFILEERRORBOX	= 8000h

LOCKFILE_FAIL_IMMEDIATELY	= 1
LOCKFILE_EXCLUSIVE_LOCK	= 2

BY_HANDLE_FILE_INFORMATION 	STRUC
 bhfi_dwFileAttributes	dd	?
 bhfi_ftCreationTime	FILETIME	<?>
 bhfi_ftLastAccessTime	FILETIME	<?>
 bhfi_ftLastWriteTim	FILETIME	<?>
 bhfi_dwVolumeSerialNumber	dd	?
 bhfi_nFileSizeHigh		dd	?
 bhfi_nFileSizeLow		dd	?
 bhfi_nNumberOfLinks	dd	?
 bhfi_nFileIndexHigh	dd	?
 bhfi_nFileIndexLow	dd	?
BY_HANDLE_FILE_INFORMATION	ENDS

HANDLE_FLAG_INHERIT		= 00000001
HANDLE_FLAG_PROTECT_FROM_CLOSE	= 00000002


HINSTANCE_ERROR 	=32

GET_TAPE_MEDIA_INFORMATION 	= 0
GET_TAPE_DRIVE_INFORMATION	= 1

SET_TAPE_MEDIA_INFORMATION	= 0
SET_TAPE_DRIVE_INFORMATION	= 1

TIME_ZONE_INFORMATION 	STRUC
 tzi_Bias		dd	?
 tzi_StandardName		dw	32 dup(?)
 tzi_StandardDate		SYSTEMTIME	<?>
 tzi_StandardBias		dd	?
 tzi_DaylightName		dw	32 dup(?)
 tzi_DaylightDate		SYSTEMTIME	<?>
 tzi_DaylightBias		dd	?
TIME_ZONE_INFORMATION	ENDS






SHUTDOWN_NORETRY	= 00000001


WIN32_FILE_ATTRIBUTE_DATA 	STRUC
 wfad_dwFileAttributes	dd	?
 wfad_ftCreationTime	FILETIME	<?>
 wfad_ftLastAccessTime	FILETIME	<?>
 wfad_ftLastWriteTime	FILETIME	<?>
 wfad_nFileSizeHigh	dd	?
 wfad_nFileSizeLow		dd	?
WIN32_FILE_ATTRIBUTE_DATA	ENDS

DONT_RESOLVE_DLL_REFERENCES		= 00000001
LOAD_LIBRARY_AS_DATAFILE		= 00000002
LOAD_WITH_ALTERED_SEARCH_PATH	= 00000008

DDD_RAW_TARGET_PATH		= 00000001
DDD_REMOVE_DEFINITION		= 00000002
DDD_EXACT_MATCH_ON_REMOVE		= 00000004
DDD_NO_BROADCAST_SYSTEM		= 00000008

FIND_FIRST_EX_CASE_SENSITIVE		= 00000001

MOVEFILE_REPLACE_EXISTING		= 00000001
MOVEFILE_COPY_ALLOWED		= 00000002
MOVEFILE_DELAY_UNTIL_REBOOT		= 00000004
MOVEFILE_WRITE_THROUGH		= 00000008

; Logon Support APIs

LOGON32_LOGON_INTERACTIVE		= 2
LOGON32_LOGON_NETWORK		= 3
LOGON32_LOGON_BATCH		= 4
LOGON32_LOGON_SERVICE		= 5

LOGON32_PROVIDER_DEFAULT		= 0
;;LOGON32_PROVIDER_WINNT351
LOGON32_PROVIDER_WINNT		= 402

; Plug-and-Play API's

HW_PROFILE_GUIDLEN		= 39	; 36-characters plus NULL terminator
MAX_PROFILE_LEN		= 80

DOCKINFO_UNDOCKED		= 1
DOCKINFO_DOCKED		= 2
DOCKINFO_USER_SUPPLIED		= 4
DOCKINFO_USER_UNDOCKED		= DOCKINFO_USER_SUPPLIED + DOCKINFO_UNDOCKED
DOCKINFO_USER_DOCKED		= DOCKINFO_USER_SUPPLIED + DOCKINFO_DOCKED

OSVERSIONINFOA 	STRUC
 ovi_dwOSVersionInfoSize	dd	?
 ovi_dwMajorVersion	dd	?
 ovi_dwMinorVersion	dd	?
 ovi_dwBuildNumber		dd	?
 ovi_dwPlatformId		dd	?
 ovi_szCSDVersion		db	128 dup(?)	; Maintenance string for PSS usage
OSVERSIONINFOA	ENDS

OSVERSIONINFO		equ	OSVERSIONINFOA

; dwPlatformId defines:

VER_PLATFORM_WIN32s	= 0
VER_PLATFORM_WIN32_WINDOWS	= 1
VER_PLATFORM_WIN32_NT	= 2

; Abnormal termination codes 

TC_NORMAL		= 0
TC_HARDERR		= 1
TC_GP_TRAP		= 2
TC_SIGNAL		= 3

; Power Management APIs

AC_LINE_OFFLINE		= 00h
AC_LINE_ONLINE		= 01h
AC_LINE_BACKUP_POWER	= 02h
AC_LINE_UNKNOWN	= 0FFh

BATTERY_FLAG_HIGH	= 01h
BATTERY_FLAG_LOW	= 02h
BATTERY_FLAG_CRITICAL	= 04h
BATTERY_FLAG_CHARGING	= 08h
BATTERY_FLAG_NO_BATTERY	= 80h
BATTERY_FLAG_UNKNOWN	= 0FFh

BATTERY_PERCENTAGE_UNKNOWN	= 0FFh

BATTERY_LIFE_UNKNOWN	= 0FFFFFFFFh

SYSTEM_POWER_STATUS 	STRUC
 sps_ACLineStatus		db	?
 sps_BatteryFlag		db	?
 sps_BatteryLifePercent	db	?
 sps_Reserved1		db	?
 sps_BatteryLifeTime	dd	?
 sps_BatteryFullLifeTime	dd	?
SYSTEM_POWER_STATUS	ENDS

;Win Certificate API and Structures ;

; Structures

WIN_CERTIFICATE 	STRUC
 wcert_dwLength		dd	?
 wcert_wRevision		dw	?
 wcert_wCertificateType	dw	?	 ; WIN_CERT_TYPE_xxx
 wcert_bCertificate		db	?
WIN_CERTIFICATE	ENDS

; Currently, the only defined certificate revision is WIN_CERT_REVISION_1_0

WIN_CERT_REVISION_1_0	= 0100h

; Possible certificate types are specified by the following values

 WIN_CERT_TYPE_X509		= 0001 ; bCertificate contains an X.509 Certificate
 WIN_CERT_TYPE_PKCS_SIGNED_DATA	= 0002 ; bCertificate contains a PKCS SignedData structure
 WIN_CERT_TYPE_RESERVED_1		= 0003 ; Reserved

; Two commonly used ActionData structures

; die spinnen, die römer :))

; Currently defined Subject Type Identifiers.All of the below /
; use the WIN_TRUST_SUBJECT_FILE subject form, defined below. /

; RawFile		= 959dc450-8d9e-11cf-8736-00aa00a485eb 

WIN_TRUST_SUBJTYPE_RAW_FILE	equ	959dc450h, 8d9eh, 11cfh, 87, 36, 00, 0aah, 00, 0a4h, 85h, 0ebh

; PeImage		= 43c9a1e0-8da0-11cf-8736-00aa00a485eb 

WIN_TRUST_SUBJTYPE_PE_IMAGE	equ	43c9a1e0h, 8da0h, 11cfh, 87, 36, 00, 0aah, 00, 0a4h, 85, 0ebh

; JavaClass		= 08ad3990-8da1-11cf-8736-00aa00a485eb 

WIN_TRUST_SUBJTYPE_JAVA_CLASS	equ 	08ad3990h, 8da1h, 11cfh,87, 36, 00, 0aah, 00, 0a4h, 85, 0ebh

; Cabinet		= d17c5374-a392-11cf-9df5-00aa00c184e0 

WIN_TRUST_SUBJTYPE_CABINET	equ	0d17c5374h, 0a392h, 11cfh, 9dh, 0f5h, 0, 0aah, 0, 0c1h, 84h, 0e0h

; Associated Subject Data Structure:

WIN_TRUST_SUBJECT_FILE 	STRUC
 wtsf_hFile		HANDLE	?
 wtsf_lpPath		dd	?
WIN_TRUST_SUBJECT_FILE	ENDS

; Associated Subject Data Structure:

WIN_TRUST_SUBJECT_FILE_AND_DISPLAY 	STRUC
 wtsfad_hFile		HANDLE	?	; handle to the open file if you got it
 wtsfad_lpPath		dd	?	; ; the path to open if you don't
 wtsfad_lpDisplayName	dd	?	;; (optional) display name to show to user in place of path
WIN_TRUST_SUBJECT_FILE_AND_DISPLAY	ENDS


;WIN_SPUB_TRUSTED_PUBLISHER_DATA 	STRUC
 ;wstpd_hClientToken		HANDLE	?
 ;wstpd_lpCertificate		LPWIN_CERTIFICATE	<?>
;WIN_SPUB_TRUSTED_PUBLISHER_DATA	ENDP

ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID	equ	00000001
ACTCTX_FLAG_LANGID_VALID		equ	00000002
ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID	equ	00000004
ACTCTX_FLAG_RESOURCE_NAME_VALID 	equ	00000008
ACTCTX_FLAG_SET_PROCESS_DEFAULT 	equ	00000010
ACTCTX_FLAG_APPLICATION_NAME_VALID	equ	00000020
ACTCTX_FLAG_SOURCE_IS_ASSEMBLYREF 	equ	00000040
ACTCTX_FLAG_HMODULE_VALID 		equ	00000080

ACTCTXA		struc
 actc_cbSize		dd	?
 actc_dwFlags		dd	?
 actc_lpSource		dd	?
 actc_wProcessorArchitecture	dw	?
 actc_wLangId		dw	?
 actc_lpAssemblyDirectory	dd	?
 actc_lpResourceName	dd	?
 actc_lpApplicationName	dd	?
 actc_hModule		dd	?
ACTCTXA		ends
-#
