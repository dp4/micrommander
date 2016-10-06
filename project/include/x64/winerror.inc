;***********************************************************************
;* *
;* winerror.h --error code definitions for the Win32 API functions *
;* *
;* Copyright (c) 1991-1996, Microsoft Corp. All rights reserved. *
;* *
;************************************************************************/

FACILITY_WINDOWS	equ	8
FACILITY_STORAGE	equ	3
FACILITY_RPC		equ	1
FACILITY_SSPI		equ	9
FACILITY_WIN32		equ	7
FACILITY_CONTROL	equ	10
FACILITY_NULL		equ	0
FACILITY_INTERNET	equ	12
FACILITY_ITF		equ	4
FACILITY_DISPATCH	equ	2
FACILITY_CERT		equ	11

; Define the severity codes

;The operation completed successfully.
ERROR_SUCCESS	equ	0h

NO_ERROR	equ	0h

;Incorrect function.
ERROR_INVALID_FUNCTION	equ	1

;The system cannot find the file specified.
ERROR_FILE_NOT_FOUND	equ	2

;The system cannot find the path specified.
ERROR_PATH_NOT_FOUND	equ	3

;The system cannot open the file.
ERROR_TOO_MANY_OPEN_FILES	equ	4

;Access is denied.
ERROR_ACCESS_DENIED	equ	5

;The handle is invalid.
ERROR_INVALID_HANDLE	equ	 6

;The storage control blocks were destroyed.
ERROR_ARENA_TRASHED	equ	7

;Not enough storage is available to process this command.
ERROR_NOT_ENOUGH_MEMORY	equ	8

;The storage control block address is invalid.
ERROR_INVALID_BLOCK	equ	9

;The environment is incorrect.
ERROR_BAD_ENVIRONMENT	equ	10

;An attempt was made to load a program with an
;incorrect format.
ERROR_BAD_FORMAT	equ	 11

;The access code is invalid.
ERROR_INVALID_ACCESS	equ	 12

;The data is invalid.
ERROR_INVALID_DATA	equ	 13

;Not enough storage is available to complete this operation.
ERROR_OUTOFMEMORY	equ	14

;The system cannot find the drive specified.
ERROR_INVALID_DRIVE	equ	15

;The directory cannot be removed.
ERROR_CURRENT_DIRECTORY	equ	16

;The system cannot move the file
;to a different disk drive.
ERROR_NOT_SAME_DEVICE	equ	17

;There are no more files.
ERROR_NO_MORE_FILES	equ	18

;The media is write protected.
ERROR_WRITE_PROTECT	equ	19

;The system cannot find the device specified.
ERROR_BAD_UNIT	equ	 20

;The device is not ready.
ERROR_NOT_READY	equ	21

;The device does not recognize the command.
ERROR_BAD_COMMAND	equ	22

;Data error (cyclic redundancy check)
ERROR_CRC	equ	23

;The program issued a command but the
;command length is incorrect.
ERROR_BAD_LENGTH	equ	 24

;The drive cannot locate a specific
;area or track on the disk.
ERROR_SEEK	equ	 25

;The specified disk or diskette cannot be accessed.
ERROR_NOT_DOS_DISK	equ	 26

;The drive cannot find the sector requested.
ERROR_SECTOR_NOT_FOUND	equ	 27

;The printer is out of paper.
ERROR_OUT_OF_PAPER	equ	 28

;The system cannot write to the specified device.
ERROR_WRITE_FAULT	equ	29

;The system cannot read from the specified device.
ERROR_READ_FAULT 	equ	30

;A device attached to the system is not functioning.
ERROR_GEN_FAILURE	equ	31

;The process cannot access the file because
;it is being used by another process.
ERROR_SHARING_VIOLATION	equ	32

;The process cannot access the file because
;another process has locked a portion of the file.
ERROR_LOCK_VIOLATION 	equ	33

;The wrong diskette is in the drive.
;Insert %2 (Volume Serial Number: %3)
;into drive %1.
ERROR_WRONG_DISK 	equ	34

;Too many files opened for sharing.
ERROR_SHARING_BUFFER_EXCEEDED	equ	36

;Reached end of file.
ERROR_HANDLE_EOF 	equ	38

;The disk is full.
ERROR_HANDLE_DISK_FULL 	equ	39

;The network request is not supported.
ERROR_NOT_SUPPORTED	equ	50

;The remote computer is not available.
ERROR_REM_NOT_LIST 	equ	51

;A duplicate name exists on the network.
ERROR_DUP_NAME 	equ	52

;The network path was not found.
ERROR_BAD_NETPATH	equ	53

;The network is busy.
ERROR_NETWORK_BUSY 	equ	54

;The specified network resource or device is no longer
;available.
ERROR_DEV_NOT_EXIST	equ	55

;The network BIOS command limit has been reached.
ERROR_TOO_MANY_CMDS	equ	56

;A network adapter hardware error occurred.
ERROR_ADAP_HDW_ERR 	equ	57

;The specified server cannot perform the requested
;operation.
ERROR_BAD_NET_RESP 	equ	58

;An unexpected network error occurred.
ERROR_UNEXP_NET_ERR	equ	59

;The remote adapter is not compatible.
ERROR_BAD_REM_ADAP	equ	60

;The printer queue is full.
ERROR_PRINTQ_FULL	equ	61

;Space to store the file waiting to be printed is
;not available on the server.
ERROR_NO_SPOOL_SPACE	equ	62

;Your file waiting to be printed was deleted.
ERROR_PRINT_CANCELLED	equ	63

;The specified network name is no longer available.
ERROR_NETNAME_DELETED	equ	64

;Network access is denied.
ERROR_NETWORK_ACCESS_DENIED	equ	65

;The network resource type is not correct.
ERROR_BAD_DEV_TYPE 	equ	66

;The network name cannot be found.
ERROR_BAD_NET_NAME 	equ	67

;The name limit for the local computer network
;adapter card was exceeded.
ERROR_TOO_MANY_NAMES 	equ	68

;The network BIOS session limit was exceeded.
ERROR_TOO_MANY_SESS	equ	69

;The remote server has been paused or is in the
;process of being started.
ERROR_SHARING_PAUSED	equ	70

;No more connections can be made to this remote computer at this time
;because there are already as many connections as the computer can accept.
ERROR_REQ_NOT_ACCEP	equ	71

;The specified printer or disk device has been paused.
ERROR_REDIR_PAUSED 	equ	72

;The file exists.
ERROR_FILE_EXISTS	equ	80

;The directory or file cannot be created.
ERROR_CANNOT_MAKE	equ	82

;Fail on INT 24
ERROR_FAIL_I24 	equ	83

;Storage to process this request is not available.
ERROR_OUT_OF_STRUCTURES	equ	84

;The local device name is already in use.
ERROR_ALREADY_ASSIGNED 	equ	85

;The specified network password is not correct.
ERROR_INVALID_PASSWORD 	equ	86

;The parameter is incorrect.
ERROR_INVALID_PARAMETER	equ	87

;A write fault occurred on the network.
ERROR_NET_WRITE_FAULT	equ	88

;The system cannot start another process at
;this time.
ERROR_NO_PROC_SLOTS	equ	89

;Cannot create another system semaphore.
ERROR_TOO_MANY_SEMAPHORES	equ	100

;The exclusive semaphore is owned by another process.
ERROR_EXCL_SEM_ALREADY_OWNED 	equ	101

;The semaphore is set and cannot be closed.
ERROR_SEM_IS_SET 	equ	102

;The semaphore cannot be set again.
ERROR_TOO_MANY_SEM_REQUESTS	equ	103

;Cannot request exclusive semaphores at interrupt time.
ERROR_INVALID_AT_INTERRUPT_TIME	equ	104

;The previous ownership of this semaphore has ended.
ERROR_SEM_OWNER_DIED 	equ	105

;Insert the diskette for drive %1.
ERROR_SEM_USER_LIMIT 	equ	106

;Program stopped because alternate diskette was not inserted.
ERROR_DISK_CHANGE	equ	107

;The disk is in use or locked by
;another process.
ERROR_DRIVE_LOCKED 	equ	108

;The pipe has been ended.
ERROR_BROKEN_PIPE	equ	109

;The system cannot open the
;device or file specified.
ERROR_OPEN_FAILED	equ	110

;The file name is too long.
ERROR_BUFFER_OVERFLOW	equ	111

;There is not enough space on the disk.
ERROR_DISK_FULL	equ	112

;No more internal file identifiers available.
ERROR_NO_MORE_SEARCH_HANDLES 	equ	113

;The target internal file identifier is incorrect.
ERROR_INVALID_TARGET_HANDLE	equ	114

;The IOCTL call made by the application program is
;not correct.
ERROR_INVALID_CATEGORY 	equ	117

;The verify-on-write switch parameter value is not
;correct.
ERROR_INVALID_VERIFY_SWITCH	equ	118

;The system does not support the command requested.
ERROR_BAD_DRIVER_LEVEL 	equ	119

;This function is only valid in Windows NT mode.
ERROR_CALL_NOT_IMPLEMENTED 	equ	120

;The semaphore timeout period has expired.
ERROR_SEM_TIMEOUT	equ	121

;The data area passed to a system call is too
;small.
ERROR_INSUFFICIENT_BUFFER	equ	122

;The filename, directory name, or volume label syntax is incorrect.
ERROR_INVALID_NAME 	equ	123

;The system call level is not correct.
ERROR_INVALID_LEVEL	equ	124

;The disk has no volume label.
ERROR_NO_VOLUME_LABEL	equ	125

;The specified module could not be found.
ERROR_MOD_NOT_FOUND	equ	126

;The specified procedure could not be found.
ERROR_PROC_NOT_FOUND 	equ	127

;There are no child processes to wait for.
ERROR_WAIT_NO_CHILDREN 	equ	128

;The %1 application cannot be run in Windows NT mode.
ERROR_CHILD_NOT_COMPLETE 	equ	129

;Attempt to use a file handle to an open disk partition for an
;operation other than raw disk I/O.
ERROR_DIRECT_ACCESS_HANDLE 	equ	130

;An attempt was made to move the file pointer before the beginning of the file.
ERROR_NEGATIVE_SEEK	equ	131

;The file pointer cannot be set on the specified device or file.
ERROR_SEEK_ON_DEVICE 	equ	132

;A JOIN or SUBST command
;cannot be used for a drive that
;contains previously joined drives.
ERROR_IS_JOIN_TARGET 	equ	133

;An attempt was made to use a
;JOIN or SUBST command on a drive that has
;already been joined.
ERROR_IS_JOINED	equ	134

;An attempt was made to use a
;JOIN or SUBST command on a drive that has
;already been substituted.
ERROR_IS_SUBSTED 	equ	135

;The system tried to delete
;the JOIN of a drive that is not joined.
ERROR_NOT_JOINED 	equ	136

;The system tried to delete the
;substitution of a drive that is not substituted.
ERROR_NOT_SUBSTED	equ	137

;The system tried to join a drive
;to a directory on a joined drive.
ERROR_JOIN_TO_JOIN 	equ	138

;The system tried to substitute a
;drive to a directory on a substituted drive.
ERROR_SUBST_TO_SUBST 	equ	139

;The system tried to join a drive to
;a directory on a substituted drive.
ERROR_JOIN_TO_SUBST	equ	140

;The system tried to SUBST a drive
;to a directory on a joined drive.
ERROR_SUBST_TO_JOIN	equ	141

;The system cannot perform a JOIN or SUBST at this time.
ERROR_BUSY_DRIVE 	equ	142

;The system cannot join or substitute a
;drive to or for a directory on the same drive.
ERROR_SAME_DRIVE 	equ	143

;The directory is not a subdirectory of the root directory.
ERROR_DIR_NOT_ROOT 	equ	144

;The directory is not empty.
ERROR_DIR_NOT_EMPTY	equ	145

;The path specified is being used in
;a substitute.
ERROR_IS_SUBST_PATH	equ	146

;Not enough resources are available to
;process this command.
ERROR_IS_JOIN_PATH 	equ	147

;The path specified cannot be used at this time.
ERROR_PATH_BUSY	equ	148

;An attempt was made to join
;or substitute a drive for which a directory
;on the drive is the target of a previous
;substitute.
ERROR_IS_SUBST_TARGET	equ	149

;System trace information was not specified in your
;CONFIG.SYS file, or tracing is disallowed.
ERROR_SYSTEM_TRACE 	equ	150

;The number of specified semaphore events for
;DosMuxSemWait is not correct.
ERROR_INVALID_EVENT_COUNT	equ	151

;DosMuxSemWait did not execute; too many semaphores
;are already set.
ERROR_TOO_MANY_MUXWAITERS	equ	152

;The DosMuxSemWait list is not correct.
ERROR_INVALID_LIST_FORMAT	equ	153

;The volume label you entered exceeds the label character
;limit of the target file system.
ERROR_LABEL_TOO_LONG 	equ	154

;Cannot create another thread.
ERROR_TOO_MANY_TCBS	equ	155

;The recipient process has refused the signal.
ERROR_SIGNAL_REFUSED 	equ	156

;The segment is already discarded and cannot be locked.
ERROR_DISCARDED	equ	157

;The segment is already unlocked.
ERROR_NOT_LOCKED 	equ	158

;The address for the thread ID is not correct.
ERROR_BAD_THREADID_ADDR	equ	159

;The argument string passed to DosExecPgm is not correct.
ERROR_BAD_ARGUMENTS	equ	160

;The specified path is invalid.
ERROR_BAD_PATHNAME 	equ	161

;A signal is already pending.
ERROR_SIGNAL_PENDING 	equ	162

;No more threads can be created in the system.
ERROR_MAX_THRDS_REACHED	equ	164

;Unable to lock a region of a file.
ERROR_LOCK_FAILED	equ	167

;The requested resource is in use.
ERROR_BUSY 	equ	170

;A lock request was not outstanding for the supplied cancel region.
ERROR_CANCEL_VIOLATION 	equ	173

;The file system does not support atomic changes to the lock type.
ERROR_ATOMIC_LOCKS_NOT_SUPPORTED 	equ	174

;The system detected a segment number that was not correct.
ERROR_INVALID_SEGMENT_NUMBER 	equ	180

;The operating system cannot run %1.
ERROR_INVALID_ORDINAL	equ	182

;Cannot create a file when that file already exists.
ERROR_ALREADY_EXISTS 	equ	183

;The flag passed is not correct.
ERROR_INVALID_FLAG_NUMBER	equ	186

;The specified system semaphore name was not found.
ERROR_SEM_NOT_FOUND	equ	187

;The operating system cannot run %	equ	1.
ERROR_INVALID_STARTING_CODESEG 	equ	188

;The operating system cannot run %1.
ERROR_INVALID_STACKSEG 	equ	189

;The operating system cannot run %1.
ERROR_INVALID_MODULETYPE 	equ	190

;Cannot run %1 in Windows NT mode.
ERROR_INVALID_EXE_SIGNATURE	equ	191

;The operating system cannot run %1.
ERROR_EXE_MARKED_INVALID 	equ	192

;%1 is not a valid Windows NT application.
ERROR_BAD_EXE_FORMAT 	equ	193

;The operating system cannot run %1.
ERROR_ITERATED_DATA_EXCEEDS_64k	equ	194

;The operating system cannot run %1.
ERROR_INVALID_MINALLOCSIZE 	equ	195

;The operating system cannot run this
;application program.
ERROR_DYNLINK_FROM_INVALID_RING	equ	196

;The operating system is not presently
;configured to run this application.
ERROR_IOPL_NOT_ENABLED 	equ	197

;The operating system cannot run %1.
ERROR_INVALID_SEGDPL 	equ	198

;The operating system cannot run this
;application program.
ERROR_AUTODATASEG_EXCEEDS_64k	equ	199

;The code segment cannot be greater than or equal to 64KB.
ERROR_RING2SEG_MUST_BE_MOVABLE 	equ	200

;The operating system cannot run %1.
ERROR_RELOC_CHAIN_XEEDS_SEGLIM 	equ	201

;The operating system cannot run %1.
ERROR_INFLOOP_IN_RELOC_CHAIN 	equ	202

;The system could not find the environment
;option that was entered.
ERROR_ENVVAR_NOT_FOUND 	equ	203

;No process in the command subtree has a
;signal handler.
ERROR_NO_SIGNAL_SENT 	equ	205

;The filename or extension is too long.
ERROR_FILENAME_EXCED_RANGE 	equ	206

;The ring 2 stack is in use.
ERROR_RING2_STACK_IN_USE 	equ	207

;The global filename characters, * or ?, are entered
;incorrectly or too many global filename characters are specified.
ERROR_META_EXPANSION_TOO_LONG	equ	208

;The signal being posted is not correct.
ERROR_INVALID_SIGNAL_NUMBER	equ	209

;The signal handler cannot be set.
ERROR_THREAD_1_INACTIVE	equ	210

;The segment is locked and cannot be reallocated.
ERROR_LOCKED 	equ	212

;Too many dynamic link modules are attached to this
;program or dynamic link module.
ERROR_TOO_MANY_MODULES 	equ	214

;Can't nest calls to LoadModule.
ERROR_NESTING_NOT_ALLOWED	equ	215

;The image file %1 is valid, but is for a machine type other
;than the current machine.
ERROR_EXE_MACHINE_TYPE_MISMATCH	equ	216

;The pipe state is invalid.
ERROR_BAD_PIPE 	equ	230

;All pipe instances are busy.
ERROR_PIPE_BUSY	equ	231

;The pipe is being closed.
ERROR_NO_DATA	equ	232

;No process is on the other end of the pipe.
ERROR_PIPE_NOT_CONNECTED 	equ	233

;More data is available.
ERROR_MORE_DATA	equ	234

;The session was cancelled.
ERROR_VC_DISCONNECTED	equ	240

;The specified extended attribute name was invalid.
ERROR_INVALID_EA_NAME	equ	254

;The extended attributes are inconsistent.
ERROR_EA_LIST_INCONSISTENT 	equ	255

;No more data is available.
ERROR_NO_MORE_ITEMS	equ	259

;The Copy API cannot be used.
ERROR_CANNOT_COPY	equ	266

;The directory name is invalid.
ERROR_DIRECTORY	equ	267

;The extended attributes did not fit in the buffer.
ERROR_EAS_DIDNT_FIT	equ	275

;The extended attribute file on the mounted file system is corrupt.
ERROR_EA_FILE_CORRUPT	equ	276

;The extended attribute table file is full.
ERROR_EA_TABLE_FULL	equ	277

;The specified extended attribute handle is invalid.
ERROR_INVALID_EA_HANDLE	equ	278

;The mounted file system does not support extended attributes.
ERROR_EAS_NOT_SUPPORTED	equ	282

;Attempt to release mutex not owned by caller.
ERROR_NOT_OWNER	equ	288

;Too many posts were made to a semaphore.
ERROR_TOO_MANY_POSTS 	equ	298

;Only part of a Read/WriteProcessMemory request was completed.
ERROR_PARTIAL_COPY 	equ	299

;The system cannot find message for message number	equ	%1
;in message file for %2.
ERROR_MR_MID_NOT_FOUND 	equ	317

;Attempt to access invalid address.
ERROR_INVALID_ADDRESS	equ	487

;Arithmetic result exceeded 32 bits.
ERROR_ARITHMETIC_OVERFLOW	equ	534

;There is a process on other end of the pipe.
ERROR_PIPE_CONNECTED	equ	 535

;Waiting for a process to open the other end of the pipe.
ERROR_PIPE_LISTENING	equ	 536

;Access to the extended attribute was denied.
ERROR_EA_ACCESS_DENIED	equ	 994

;The I/O operation has been aborted because of either a thread exit
;or an application request.
ERROR_OPERATION_ABORTED	equ	995

;Overlapped I/O event is not in a signalled state.
ERROR_IO_INCOMPLETE	equ	996

;Overlapped I/O operation is in progress.
ERROR_IO_PENDING	equ	 997

;Invalid access to memory location.
ERROR_NOACCESS	equ	 998

;Error performing inpage operation.
ERROR_SWAPERROR	equ	999

;Recursion too deep, stack overflowed.
ERROR_STACK_OVERFLOW 	equ	1001

;The window cannot act on the sent message.
ERROR_INVALID_MESSAGE	equ	1002

;Cannot complete this function.
ERROR_CAN_NOT_COMPLETE 	equ	1003

;Invalid flags.
ERROR_INVALID_FLAGS	equ	1004

;The volume does not contain a recognized file system.
;Please make sure that all required file system drivers are loaded and that the
;volume is not corrupt.
ERROR_UNRECOGNIZED_VOLUME	equ	1005

;The volume for a file has been externally altered such that the
;opened file is no longer valid.
ERROR_FILE_INVALID 	equ	1006

;The requested operation cannot be performed in full-screen mode.
ERROR_FULLSCREEN_MODE	equ	1007

;An attempt was made to reference a token that does not exist.
ERROR_NO_TOKEN 	equ	1008

;The configuration registry database is corrupt.
ERROR_BADDB	equ	1009

;The configuration registry key is invalid.
ERROR_BADKEY 	equ	1010

;The configuration registry key could not be opened.
ERROR_CANTOPEN 	equ	1011

;The configuration registry key could not be read.
ERROR_CANTREAD 	equ	1012

;The configuration registry key could not be written.
ERROR_CANTWRITE	equ	1013

;One of the files in the Registry database had to be recovered
;by use of a log or alternate copy.The recovery was successful.
ERROR_REGISTRY_RECOVERED 	equ	1014

;The Registry is corrupt. The structure of one of the files that contains
;Registry data is corrupt, or the system's image of the file in memory
;is corrupt, or the file could not be recovered because the alternate
;copy or log was absent or corrupt.
ERROR_REGISTRY_CORRUPT 	equ	1015

;An I/O operation initiated by the Registry failed unrecoverably.
;The Registry could not read in, or write out, or flush, one of the files
;that contain the system's image of the Registry.
ERROR_REGISTRY_IO_FAILED 	equ	1016

;The system has attempted to load or restore a file into the Registry, but the
;specified file is not in a Registry file format.
ERROR_NOT_REGISTRY_FILE	equ	1017

;Illegal operation attempted on a Registry key which has been marked for deletion.
ERROR_KEY_DELETED	equ	1018

;System could not allocate the required space in a Registry log.
ERROR_NO_LOG_SPACE 	equ	1019

;Cannot create a symbolic link in a Registry key that already
;has subkeys or values.
ERROR_KEY_HAS_CHILDREN 	equ	1020

;Cannot create a stable subkey under a volatile parent key.
ERROR_CHILD_MUST_BE_VOLATILE 	equ	1021

;A notify change request is being completed and the information
;is not being returned in the caller's buffer. The caller now
;needs to enumerate the files to find the changes.
ERROR_NOTIFY_ENUM_DIR	equ	1022

;A stop control has been sent to a service which other running services
;are dependent on.
ERROR_DEPENDENT_SERVICES_RUNNING 	equ	1051

;The requested control is not valid for this service
ERROR_INVALID_SERVICE_CONTROL	equ	1052

;The service did not respond to the start or control request in a timely
;fashion.
ERROR_SERVICE_REQUEST_TIMEOUT	equ	1053

;A thread could not be created for the service.
ERROR_SERVICE_NO_THREAD	equ	1054

;The service database is locked.
ERROR_SERVICE_DATABASE_LOCKED	equ	1055

;An instance of the service is already running.
ERROR_SERVICE_ALREADY_RUNNING	equ	1056

;The account name is invalid or does not exist.
ERROR_INVALID_SERVICE_ACCOUNT	equ	1057

;The specified service is disabled and cannot be started.
ERROR_SERVICE_DISABLED 	equ	1058

;Circular service dependency was specified.
ERROR_CIRCULAR_DEPENDENCY	equ	1059

;The specified service does not exist as an installed service.
ERROR_SERVICE_DOES_NOT_EXIST 	equ	1060

;The service cannot accept control messages at this time.
ERROR_SERVICE_CANNOT_ACCEPT_CTRL 	equ	1061

;The service has not been started.
ERROR_SERVICE_NOT_ACTIVE 	equ	1062

;The service process could not connect to the service controller.
ERROR_FAILED_SERVICE_CONTROLLER_CONNECT 	equ	1063

;An exception occurred in the service when handling the control request.
ERROR_EXCEPTION_IN_SERVICE 	equ	1064

;The database specified does not exist.
ERROR_DATABASE_DOES_NOT_EXIST	equ	1065

;The service has returned a service-specific error code.
ERROR_SERVICE_SPECIFIC_ERROR 	equ	1066

;The process terminated unexpectedly.
ERROR_PROCESS_ABORTED	equ	1067

;The dependency service or group failed to start.
ERROR_SERVICE_DEPENDENCY_FAIL	equ	1068

;The service did not start due to a logon failure.
ERROR_SERVICE_LOGON_FAILED 	equ	1069

;After starting, the service hung in a start-pending state.
ERROR_SERVICE_START_HANG 	equ	1070

;The specified service database lock is invalid.
ERROR_INVALID_SERVICE_LOCK 	equ	1071

;The specified service has been marked for deletion.
ERROR_SERVICE_MARKED_FOR_DELETE	equ	1072

;The specified service already exists.
ERROR_SERVICE_EXISTS 	equ	1073

;The system is currently running with the last-known-good configuration.
ERROR_ALREADY_RUNNING_LKG	equ	1074

;The dependency service does not exist or has been marked for
;deletion.
ERROR_SERVICE_DEPENDENCY_DELETED 	equ	1075

;The current boot has already been accepted for use as the
;last-known-good control set.
ERROR_BOOT_ALREADY_ACCEPTED	equ	1076

;No attempts to start the service have been made since the last boot.
ERROR_SERVICE_NEVER_STARTED	equ	1077

;The name is already in use as either a service name or a service display
;name.
ERROR_DUPLICATE_SERVICE_NAME 	equ	1078

;The account specified for this service is different from the account
;specified for other services running in the same process.
ERROR_DIFFERENT_SERVICE_ACCOUNT	equ	1079

;The physical end of the tape has been reached.
ERROR_END_OF_MEDIA 	equ	1100

;A tape access reached a filemark.
ERROR_FILEMARK_DETECTED	equ	1101

;Beginning of tape or partition was encountered.
ERROR_BEGINNING_OF_MEDIA 	equ	1102

;A tape access reached the end of a set of files.
ERROR_SETMARK_DETECTED 	equ	1103

;No more data is on the tape.
ERROR_NO_DATA_DETECTED 	equ	1104

;Tape could not be partitioned.
ERROR_PARTITION_FAILURE	equ	1105

;When accessing a new tape of a multivolume partition, the current
;blocksize is incorrect.
ERROR_INVALID_BLOCK_LENGTH 	equ	1106

;Tape partition information could not be found when loading a tape.
ERROR_DEVICE_NOT_PARTITIONED 	equ	1107

;Unable to lock the media eject mechanism.
ERROR_UNABLE_TO_LOCK_MEDIA 	equ	1108

;Unable to unload the media.
ERROR_UNABLE_TO_UNLOAD_MEDIA 	equ	1109

;Media in drive may have changed.
ERROR_MEDIA_CHANGED	equ	1110

;The I/O bus was reset.
ERROR_BUS_RESET	equ	1111

;No media in drive.
ERROR_NO_MEDIA_IN_DRIVE	equ	1112

;No mapping for the Unicode character exists in the target multi-byte code page.
ERROR_NO_UNICODE_TRANSLATION 	equ	1113

;A dynamic link library (DLh initialization routine failed.
ERROR_DLL_INIT_FAILED	equ	1114

;A system shutdown is in progress.
ERROR_SHUTDOWN_IN_PROGRESS 	equ	1115

;Unable to abort the system shutdown because no shutdown was in progress.
ERROR_NO_SHUTDOWN_IN_PROGRESS	equ	1116

;The request could not be performed because of an I/O device error.
ERROR_IO_DEVICE	equ	1117

;No serial device was successfully initialized.The serial driver will unload.
ERROR_SERIAL_NO_DEVICE 	equ	1118

;Unable to open a device that was sharing an interrupt request (IRQ)
;with other devices. At least one other device that uses that IRQ
;was already opened.
ERROR_IRQ_BUSY 	equ	1119

;A serial I/O operation was completed by another write to the serial port.
;(The IOCTL_SERIAL_XOFF_COUNTER reached zero.)
ERROR_MORE_WRITES	equ	1120

;A serial I/O operation completed because the time-out period expired.
;(The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)
ERROR_COUNTER_TIMEOUT	equ	1121

;No ID address mark was found on the floppy disk.
ERROR_FLOPPY_ID_MARK_NOT_FOUND 	equ	1122

;Mismatch between the floppy disk sector ID field and the floppy disk
;controller track address.
ERROR_FLOPPY_WRONG_CYLINDER	equ	1123

;The floppy disk controller reported an error that is not recognized
;by the floppy disk driver.
ERROR_FLOPPY_UNKNOWN_ERROR 	equ	1124

;The floppy disk controller returned inconsistent results in its registers.
ERROR_FLOPPY_BAD_REGISTERS 	equ	1125

;While accessing the hard disk, a recalibrate operation failed, even after retries.
ERROR_DISK_RECALIBRATE_FAILED	equ	1126

;While accessing the hard disk, a disk operation failed even after retries.
ERROR_DISK_OPERATION_FAILED	equ	1127

;While accessing the hard disk, a disk controller reset was needed, but
;even that failed.
ERROR_DISK_RESET_FAILED	equ	1128

;Physical end of tape encountered.
ERROR_EOM_OVERFLOW 	equ	1129

;Not enough server storage is available to process this command.
ERROR_NOT_ENOUGH_SERVER_MEMORY 	equ	1130

;A potential deadlock condition has been detected.
ERROR_POSSIBLE_DEADLOCK	equ	1131

;The base address or the file offset specified does not have the proper
;alignment.
ERROR_MAPPED_ALIGNMENT 	equ	1132

;An attempt to change the system power state was vetoed by another
;application or driver.
ERROR_SET_POWER_STATE_VETOED 	equ	1140

;The system BIOS failed an attempt to change the system power state.
ERROR_SET_POWER_STATE_FAILED 	equ	1141

;An attempt was made to create more links on a file than
;the file system supports.
ERROR_TOO_MANY_LINKS 	equ	1142

;The specified program requires a newer version of Windows.
ERROR_OLD_WIN_VERSION	equ	1150

;The specified program is not a Windows or MS-DOS program.
ERROR_APP_WRONG_OS 	equ	1151

;Cannot start more than one instance of the specified program.
ERROR_SINGLE_INSTANCE_APP	equ	1152

;The specified program was written for an older version of Windows.
ERROR_RMODE_APP	equ	1153

;One of the library files needed to run this application is damaged.
ERROR_INVALID_DLL	equ	1154

;No application is associated with the specified file for this operation.
ERROR_NO_ASSOCIATION 	equ	1155

;An error occurred in sending the command to the application.
ERROR_DDE_FAIL 	equ	1156

;One of the library files needed to run this application cannot be found.
ERROR_DLL_NOT_FOUND	equ	1157




;;;;;;;;;;;;;/
; ; Winnet32 Status Codes ; ;;;;;;;;;;;;;/


;The specified username is invalid.
ERROR_BAD_USERNAME 	equ	2202

;This network connection does not exist.
ERROR_NOT_CONNECTED	equ	2250

;This network connection has files open or requests pending.
ERROR_OPEN_FILES 	equ	2401

;Active connections still exist.
ERROR_ACTIVE_CONNECTIONS 	equ	2402

;The device is in use by an active process and cannot be disconnected.
ERROR_DEVICE_IN_USE	equ	2404

;The specified device name is invalid.
ERROR_BAD_DEVICE 	equ	1200

;The device is not currently connected but it is a remembered connection.
ERROR_CONNECTION_UNAVAIL 	equ	1201

;An attempt was made to remember a device that had previously been remembered.
ERROR_DEVICE_ALREADY_REMEMBERED	equ	1202

;No network provider accepted the given network path.
ERROR_NO_NET_OR_BAD_PATH 	equ	1203

;The specified network provider name is invalid.
ERROR_BAD_PROVIDER 	equ	1204

;Unable to open the network connection profile.
ERROR_CANNOT_OPEN_PROFILE	equ	1205

;The network connection profile is corrupt.
ERROR_BAD_PROFILE	equ	1206

;Cannot enumerate a non-container.
ERROR_NOT_CONTAINER	equ	1207

;An extended error has occurred.
ERROR_EXTENDED_ERROR 	equ	1208

;The format of the specified group name is invalid.
ERROR_INVALID_GROUPNAME	equ	1209

;The format of the specified computer name is invalid.
ERROR_INVALID_COMPUTERNAME 	equ	1210

;The format of the specified event name is invalid.
ERROR_INVALID_EVENTNAME	equ	1211

;The format of the specified domain name is invalid.
ERROR_INVALID_DOMAINNAME 	equ	1212

;The format of the specified service name is invalid.
ERROR_INVALID_SERVICENAME	equ	1213

;The format of the specified network name is invalid.
ERROR_INVALID_NETNAME	equ	1214

;The format of the specified share name is invalid.
ERROR_INVALID_SHARENAME	equ	1215

;The format of the specified password is invalid.
ERROR_INVALID_PASSWORDNAME 	equ	1216

;The format of the specified message name is invalid.
ERROR_INVALID_MESSAGENAME	equ	1217

;The format of the specified message destination is invalid.
ERROR_INVALID_MESSAGEDEST	equ	1218

;The credentials supplied conflict with an existing set of credentials.
ERROR_SESSION_CREDENTIAL_CONFLICT 	equ	1219

;An attempt was made to establish a session to a network server, but there
;are already too many sessions established to that server.
ERROR_REMOTE_SESSION_LIMIT_EXCEEDED 	equ	1220

;The workgroup or domain name is already in use by another computer on the
;network.
ERROR_DUP_DOMAINNAME 	equ	1221

;The network is not present or not started.
ERROR_NO_NETWORK 	equ	1222

;The operation was cancelled by the user.
ERROR_CANCELLED	equ	1223

;The requested operation cannot be performed on a file with a user mapped section open.
ERROR_USER_MAPPED_FILE 	equ	1224

;The remote system refused the network connection.
ERROR_CONNECTION_REFUSED 	equ	1225

;The network connection was gracefully closed.
ERROR_GRACEFUL_DISCONNECT	equ	1226

;The network transport endpoint already has an address associated with it.
ERROR_ADDRESS_ALREADY_ASSOCIATED 	equ	1227

;An address has not yet been associated with the network endpoint.
ERROR_ADDRESS_NOT_ASSOCIATED 	equ	1228

;An operation was attempted on a non-existent network connection.
ERROR_CONNECTION_INVALID 	equ	1229

;An invalid operation was attempted on an active network connection.
ERROR_CONNECTION_ACTIVE	equ	1230

;The remote network is not reachable by the transport.
ERROR_NETWORK_UNREACHABLE	equ	1231

;The remote system is not reachable by the transport.
ERROR_HOST_UNREACHABLE 	equ	1232

;The remote system does not support the transport protocol.
ERROR_PROTOCOL_UNREACHABLE 	equ	1233

;No service is operating at the destination network endpoint
;on the remote system.
ERROR_PORT_UNREACHABLE 	equ	1234

;The request was aborted.
ERROR_REQUEST_ABORTED	equ	1235

;The network connection was aborted by the local system.
ERROR_CONNECTION_ABORTED 	equ	1236

;The operation could not be completed.A retry should be performed.
ERROR_RETRY	equ	1237

;A connection to the server could not be made because the limit on the number of
;concurrent connections for this account has been reached.
ERROR_CONNECTION_COUNT_LIMIT 	equ	1238

;Attempting to login during an unauthorized time of day for this account.
ERROR_LOGIN_TIME_RESTRICTION 	equ	1239

;The account is not authorized to login from this station.
ERROR_LOGIN_WKSTA_RESTRICTION	equ	1240

;The network address could not be used for the operation requested.
ERROR_INCORRECT_ADDRESS	equ	1241

;The service is already registered.
ERROR_ALREADY_REGISTERED 	equ	1242

;The specified service does not exist.
ERROR_SERVICE_NOT_FOUND	equ	1243

;The operation being requested was not performed because the user
;has not been authenticated.
ERROR_NOT_AUTHENTICATED	equ	1244

;The operation being requested was not performed because the user
;has not logged on to the network.
;The specified service does not exist.
ERROR_NOT_LOGGED_ON	equ	1245

;Return that wants caller to continue with work in progress.
ERROR_CONTINUE 	equ	1246

;An attempt was made to perform an initialization operation when
;initialization has already been completed.
ERROR_ALREADY_INITIALIZED	equ	1247

;No more local devices.
ERROR_NO_MORE_DEVICES	equ	1248




;;;;;;;;;;;;;/
; ; Security Status Codes ; ;;;;;;;;;;;;;/


;Not all privileges referenced are assigned to the caller.
ERROR_NOT_ALL_ASSIGNED 	equ	1300

;Some mapping between account names and security IDs was not done.
ERROR_SOME_NOT_MAPPED	equ	1301

;No system quota limits are specifically set for this account.
ERROR_NO_QUOTAS_FOR_ACCOUNT	equ	1302

;No encryption key is available.A well-known encryption key was returned.
ERROR_LOCAL_USER_SESSION_KEY 	equ	1303

;The NT password is too complex to be converted to a LAN Manager
;password.The LAN Manager password returned is a NULL string.
ERROR_NULL_LM_PASSWORD 	equ	1304

;The revision level is unknown.
ERROR_UNKNOWN_REVISION 	equ	1305

;Indicates two revision levels are incompatible.
ERROR_REVISION_MISMATCH	equ	1306

;This security ID may not be assigned as the owner of this object.
ERROR_INVALID_OWNER	equ	1307

;This security ID may not be assigned as the primary group of an object.
ERROR_INVALID_PRIMARY_GROUP	equ	1308

;An attempt has been made to operate on an impersonation token
;by a thread that is not currently impersonating a client.
ERROR_NO_IMPERSONATION_TOKEN 	equ	1309

;The group may not be disabled.
ERROR_CANT_DISABLE_MANDATORY 	equ	1310

;There are currently no logon servers available to service the logon
;request.
ERROR_NO_LOGON_SERVERS 	equ	1311

; A specified logon session does not exist.It may already have
; been terminated.
ERROR_NO_SUCH_LOGON_SESSION	equ	1312

; A specified privilege does not exist.
ERROR_NO_SUCH_PRIVILEGE	equ	1313

; A required privilege is not held by the client.
ERROR_PRIVILEGE_NOT_HELD 	equ	1314

;The name provided is not a properly formed account name.
ERROR_INVALID_ACCOUNT_NAME 	equ	1315

;The specified user already exists.
ERROR_USER_EXISTS	equ	1316

;The specified user does not exist.
ERROR_NO_SUCH_USER 	equ	1317

;The specified group already exists.
ERROR_GROUP_EXISTS 	equ	1318

;The specified group does not exist.
ERROR_NO_SUCH_GROUP	equ	1319

;Either the specified user account is already a member of the specified
;group, or the specified group cannot be deleted because it contains
;a member.
ERROR_MEMBER_IN_GROUP	equ	1320

;The specified user account is not a member of the specified group account.
ERROR_MEMBER_NOT_IN_GROUP	equ	1321

;The last remaining administration account cannot be disabled
;or deleted.
ERROR_LAST_ADMIN 	equ	1322

;Unable to update the password.The value provided as the current
;password is incorrect.
ERROR_WRONG_PASSWORD 	equ	1323

;Unable to update the password.The value provided for the new password
;contains values that are not allowed in passwords.
ERROR_ILL_FORMED_PASSWORD	equ	1324

;Unable to update the password because a password update rule has been
;violated.
ERROR_PASSWORD_RESTRICTION 	equ	1325

;Logon failure: unknown user name or bad password.
ERROR_LOGON_FAILURE	equ	1326

;Logon failure: user account restriction.
ERROR_ACCOUNT_RESTRICTION	equ	1327

;Logon failure: account logon time restriction violation.
ERROR_INVALID_LOGON_HOURS	equ	1328

;Logon failure: user not allowed to log on to this computer.
ERROR_INVALID_WORKSTATION	equ	1329

;Logon failure: the specified account password has expired.
ERROR_PASSWORD_EXPIRED 	equ	1330

;Logon failure: account currently disabled.
ERROR_ACCOUNT_DISABLED 	equ	1331

;No mapping between account names and security IDs was done.
ERROR_NONE_MAPPED	equ	1332

;Too many local user identifiers (LUIDs) were requested at one time.
ERROR_TOO_MANY_LUIDS_REQUESTED 	equ	1333

;No more local user identifiers (LUIDs) are available.
ERROR_LUIDS_EXHAUSTED	equ	1334

;The subauthority part of a security ID is invalid for this particular use.
ERROR_INVALID_SUB_AUTHORITY	equ	1335

;The access control list (ACh structure is invalid.
ERROR_INVALID_ACL	equ	1336

;The security ID structure is invalid.
ERROR_INVALID_SID	equ	1337

;The security descriptor structure is invalid.
ERROR_INVALID_SECURITY_DESCR 	equ	1338

;The inherited access control list (ACh or access control entry (ACE)
;could not be built.
ERROR_BAD_INHERITANCE_ACL	equ	1340

;The server is currently disabled.
ERROR_SERVER_DISABLED	equ	1341

;The server is currently enabled.
ERROR_SERVER_NOT_DISABLED	equ	1342

;The value provided was an invalid value for an identifier authority.
ERROR_INVALID_ID_AUTHORITY 	equ	1343

;No more memory is available for security information updates.
ERROR_ALLOTTED_SPACE_EXCEEDED	equ	1344

;The specified attributes are invalid, or incompatible with the
;attributes for the group as a whole.
ERROR_INVALID_GROUP_ATTRIBUTES 	equ	1345

;Either a required impersonation level was not provided, or the
;provided impersonation level is invalid.
ERROR_BAD_IMPERSONATION_LEVEL	equ	1346

;Cannot open an anonymous level security token.
ERROR_CANT_OPEN_ANONYMOUS	equ	1347

;The validation information class requested was invalid.
ERROR_BAD_VALIDATION_CLASS 	equ	1348

;The type of the token is inappropriate for its attempted use.
ERROR_BAD_TOKEN_TYPE 	equ	1349

;Unable to perform a security operation on an object
;which has no associated security.
ERROR_NO_SECURITY_ON_OBJECT	equ	1350

;Indicates a Windows NT Server could not be contacted or that
;objects within the domain are protected such that necessary
;information could not be retrieved.
ERROR_CANT_ACCESS_DOMAIN_INFO	equ	1351

;The security account manager (SAM) or local security
;authority (LSA) server was in the wrong state to perform
;the security operation.
ERROR_INVALID_SERVER_STATE 	equ	1352

;The domain was in the wrong state to perform the security operation.
ERROR_INVALID_DOMAIN_STATE 	equ	1353

;This operation is only allowed for the Primary Domain Controller of the domain.
ERROR_INVALID_DOMAIN_ROLE	equ	1354

;The specified domain did not exist.
ERROR_NO_SUCH_DOMAIN 	equ	1355

;The specified domain already exists.
ERROR_DOMAIN_EXISTS	equ	1356

;An attempt was made to exceed the limit on the number of domains per server.
ERROR_DOMAIN_LIMIT_EXCEEDED	equ	1357

;Unable to complete the requested operation because of either a
;catastrophic media failure or a data structure corruption on the disk.
ERROR_INTERNAL_DB_CORRUPTION 	equ	1358

;The security account database contains an internal inconsistency.
ERROR_INTERNAL_ERROR 	equ	1359

;Generic access types were contained in an access mask which should
;already be mapped to non-generic types.
ERROR_GENERIC_NOT_MAPPED 	equ	1360

;A security descriptor is not in the right format (absolute or self-relative).
ERROR_BAD_DESCRIPTOR_FORMAT	equ	1361

;The requested action is restricted for use by logon processes
;only.The calling process has not registered as a logon process.
ERROR_NOT_LOGON_PROCESS	equ	1362

;Cannot start a new logon session with an ID that is already in use.
ERROR_LOGON_SESSION_EXISTS 	equ	1363

;A specified authentication package is unknown.
ERROR_NO_SUCH_PACKAGE	equ	1364

;The logon session is not in a state that is consistent with the
;requested operation.
ERROR_BAD_LOGON_SESSION_STATE	equ	1365

;The logon session ID is already in use.
ERROR_LOGON_SESSION_COLLISION	equ	1366

;A logon request contained an invalid logon type value.
ERROR_INVALID_LOGON_TYPE 	equ	1367

;Unable to impersonate via a named pipe until data has been read
;from that pipe.
ERROR_CANNOT_IMPERSONATE 	equ	1368

;The transaction state of a Registry subtree is incompatible with the
;requested operation.
ERROR_RXACT_INVALID_STATE	equ	1369

;An internal security database corruption has been encountered.
ERROR_RXACT_COMMIT_FAILURE 	equ	1370

;Cannot perform this operation on built-in accounts.
ERROR_SPECIAL_ACCOUNT	equ	1371

;Cannot perform this operation on this built-in special group.
ERROR_SPECIAL_GROUP	equ	1372

;Cannot perform this operation on this built-in special user.
ERROR_SPECIAL_USER 	equ	1373

;The user cannot be removed from a group because the group
;is currently the user's primary group.
ERROR_MEMBERS_PRIMARY_GROUP	equ	1374

;The token is already in use as a primary token.
ERROR_TOKEN_ALREADY_IN_USE 	equ	1375

;The specified local group does not exist.
ERROR_NO_SUCH_ALIAS	equ	1376

;The specified account name is not a member of the local group.
ERROR_MEMBER_NOT_IN_ALIAS	equ	1377

;The specified account name is already a member of the local group.
ERROR_MEMBER_IN_ALIAS	equ	1378

;The specified local group already exists.
ERROR_ALIAS_EXISTS 	equ	1379

;Logon failure: the user has not been granted the requested
;logon type at this computer.
ERROR_LOGON_NOT_GRANTED	equ	1380

;The maximum number of secrets that may be stored in a single system has been
;exceeded.
ERROR_TOO_MANY_SECRETS 	equ	1381

;The length of a secret exceeds the maximum length allowed.
ERROR_SECRET_TOO_LONG	equ	1382

;The local security authority database contains an internal inconsistency.
ERROR_INTERNAL_DB_ERROR	equ	1383

;During a logon attempt, the user's security context accumulated too many
;security IDs.
ERROR_TOO_MANY_CONTEXT_IDS 	equ	1384

;Logon failure: the user has not been granted the requested logon type
;at this computer.
ERROR_LOGON_TYPE_NOT_GRANTED 	equ	1385

;A cross-encrypted password is necessary to change a user password.
ERROR_NT_CROSS_ENCRYPTION_REQUIRED 	equ	1386

;A new member could not be added to a local group because the member does
;not exist.
ERROR_NO_SUCH_MEMBER 	equ	1387

;A new member could not be added to a local group because the member has the
;wrong account type.
ERROR_INVALID_MEMBER 	equ	1388

;Too many security IDs have been specified.
ERROR_TOO_MANY_SIDS	equ	1389

;A cross-encrypted password is necessary to change this user password.
ERROR_LM_CROSS_ENCRYPTION_REQUIRED 	equ	1390

;Indicates an ACL contains no inheritable components
ERROR_NO_INHERITANCE 	equ	1391

;The file or directory is corrupt and non-readable.
ERROR_FILE_CORRUPT 	equ	1392

;The disk structure is corrupt and non-readable.
ERROR_DISK_CORRUPT 	equ	1393

;There is no user session key for the specified logon session.
ERROR_NO_USER_SESSION_KEY	equ	1394

;The service being accessed is licensed for a particular number of connections.
;No more connections can be made to the service at this time
;because there are already as many connections as the service can accept.
ERROR_LICENSE_QUOTA_EXCEEDED 	equ	1395

; End of security error codes



;;;;;;;;;;;;;/
; ; WinUser Error Codes ; ;;;;;;;;;;;;;/


;Invalid window handle.
ERROR_INVALID_WINDOW_HANDLE	equ	1400

;Invalid menu handle.
ERROR_INVALID_MENU_HANDLE	equ	1401

;Invalid cursor handle.
ERROR_INVALID_CURSOR_HANDLE	equ	1402

;Invalid accelerator table handle.
ERROR_INVALID_ACCEL_HANDLE 	equ	1403

;Invalid hook handle.
ERROR_INVALID_HOOK_HANDLE	equ	1404

;Invalid handle to a multiple-window position structure.
ERROR_INVALID_DWP_HANDLE 	equ	1405

;Cannot create a top-level child window.
ERROR_TLW_WITH_WSCHILD 	equ	1406

;Cannot find window class.
ERROR_CANNOT_FIND_WND_CLASS	equ	1407

;Invalid window, belongs to other thread.
ERROR_WINDOW_OF_OTHER_THREAD 	equ	1408

;Hot key is already registered.
ERROR_HOTKEY_ALREADY_REGISTERED	equ	1409

;Class already exists.
ERROR_CLASS_ALREADY_EXISTS 	equ	1410

;Class does not exist.
ERROR_CLASS_DOES_NOT_EXIST 	equ	1411

;Class still has open windows.
ERROR_CLASS_HAS_WINDOWS	equ	1412

;Invalid index.
ERROR_INVALID_INDEX	equ	1413

;Invalid icon handle.
ERROR_INVALID_ICON_HANDLE	equ	1414

;Using private DIALOG window words.
ERROR_PRIVATE_DIALOG_INDEX 	equ	1415

;The listbox identifier was not found.
ERROR_LISTBOX_ID_NOT_FOUND 	equ	1416

;No wildcards were found.
ERROR_NO_WILDCARD_CHARACTERS 	equ	1417

;Thread does not have a clipboard open.
ERROR_CLIPBOARD_NOT_OPEN 	equ	1418

;Hot key is not registered.
ERROR_HOTKEY_NOT_REGISTERED	equ	1419

;The window is not a valid dialog window.
ERROR_WINDOW_NOT_DIALOG	equ	1420

;Control ID not found.
ERROR_CONTROL_ID_NOT_FOUND 	equ	1421

;Invalid message for a combo box because it does not have an edit control.
ERROR_INVALID_COMBOBOX_MESSAGE 	equ	1422

;The window is not a combo box.
ERROR_WINDOW_NOT_COMBOBOX	equ	1423

;Height must be less than 256.
ERROR_INVALID_EDIT_HEIGHT	equ	1424

;Invalid device context (DC) handle.
ERROR_DC_NOT_FOUND 	equ	1425

;Invalid hook procedure type.
ERROR_INVALID_HOOK_FILTER	equ	1426

;Invalid hook procedure.
ERROR_INVALID_FILTER_PROC	equ	1427

;Cannot set non-local hook without a module handle.
ERROR_HOOK_NEEDS_HMOD	equ	1428

;This hook procedure can only be set globally.
ERROR_GLOBAL_ONLY_HOOK 	equ	1429

;The journal hook procedure is already installed.
ERROR_JOURNAL_HOOK_SET 	equ	1430

;The hook procedure is not installed.
ERROR_HOOK_NOT_INSTALLED 	equ	1431

;Invalid message for single-selection listbox.
ERROR_INVALID_LB_MESSAGE 	equ	1432

;LB_SETCOUNT sent to non-lazy listbox.
ERROR_SETCOUNT_ON_BAD_LB 	equ	1433

;This list box does not support tab stops.
ERROR_LB_WITHOUT_TABSTOPS	equ	1434

;Cannot destroy object created by another thread.
ERROR_DESTROY_OBJECT_OF_OTHER_THREAD 	equ	1435

;Child windows cannot have menus.
ERROR_CHILD_WINDOW_MENU	equ	1436

;The window does not have a system menu.
ERROR_NO_SYSTEM_MENU 	equ	1437

;Invalid message box style.
ERROR_INVALID_MSGBOX_STYLE 	equ	1438

;Invalid system-wide (SPI_*) parameter.
ERROR_INVALID_SPI_VALUE	equ	1439

;Screen already locked.
ERROR_SCREEN_ALREADY_LOCKED	equ	1440

;All handles to windows in a multiple-window position structure must
;have the same parent.
ERROR_HWNDS_HAVE_DIFF_PARENT 	equ	1441

;The window is not a child window.
ERROR_NOT_CHILD_WINDOW 	equ	1442

;Invalid GW_* command.
ERROR_INVALID_GW_COMMAND 	equ	1443

;Invalid thread identifier.
ERROR_INVALID_THREAD_ID	equ	1444

;Cannot process a message from a window that is not a multiple document
;interface (MDI) window.
ERROR_NON_MDICHILD_WINDOW	equ	1445

;Popup menu already active.
ERROR_POPUP_ALREADY_ACTIVE 	equ	1446

;The window does not have scroll bars.
ERROR_NO_SCROLLBARS	equ	1447

;Scroll bar range cannot be greater than	equ	7FFF.
ERROR_INVALID_SCROLLBAR_RANGE	equ	1448

;Cannot show or remove the window in the way specified.
ERROR_INVALID_SHOWWIN_COMMAND	equ	1449

;Insufficient system resources exist to complete the requested service.
ERROR_NO_SYSTEM_RESOURCES	equ	1450

;Insufficient system resources exist to complete the requested service.
ERROR_NONPAGED_SYSTEM_RESOURCES	equ	1451

;Insufficient system resources exist to complete the requested service.
ERROR_PAGED_SYSTEM_RESOURCES 	equ	1452

;Insufficient quota to complete the requested service.
ERROR_WORKING_SET_QUOTA	equ	1453

;Insufficient quota to complete the requested service.
ERROR_PAGEFILE_QUOTA 	equ	1454

;The paging file is too small for this operation to complete.
ERROR_COMMITMENT_LIMIT 	equ	1455

;A menu item was not found.
ERROR_MENU_ITEM_NOT_FOUND	equ	1456

;Invalid keyboard layout handle.
ERROR_INVALID_KEYBOARD_HANDLE	equ	1457

;Hook type not allowed.
ERROR_HOOK_TYPE_NOT_ALLOWED	equ	1458

;This operation requires an interactive windowstation.
ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION 	equ	1459

;This operation returned because the timeout period expired.
ERROR_TIMEOUT	equ	1460

; End of WinUser error codes



;;;;;;;;;;;;;/
; ; Eventlog Status Codes ; ;;;;;;;;;;;;;/


;The event log file is corrupt.
ERROR_EVENTLOG_FILE_CORRUPT	equ	1500

;No event log file could be opened, so the event logging service did not start.
ERROR_EVENTLOG_CANT_START	equ	1501

;The event log file is full.
ERROR_LOG_FILE_FULL	equ	1502

;The event log file has changed between reads.
ERROR_EVENTLOG_FILE_CHANGED	equ	1503

; End of eventlog error codes



;;;;;;;;;;;;;/
; ; RPC Status Codes; ;;;;;;;;;;;;;/


;The string binding is invalid.
RPC_S_INVALID_STRING_BINDING 	equ	1700

;The binding handle is not the correct type.
RPC_S_WRONG_KIND_OF_BINDING	equ	1701

;The binding handle is invalid.
RPC_S_INVALID_BINDING	equ	1702

;The RPC protocol sequence is not supported.
RPC_S_PROTSEQ_NOT_SUPPORTED	equ	1703

;The RPC protocol sequence is invalid.
RPC_S_INVALID_RPC_PROTSEQ	equ	1704

;The string universal unique identifier (UUID) is invalid.
RPC_S_INVALID_STRING_UUID	equ	1705

;The endpoint format is invalid.
RPC_S_INVALID_ENDPOINT_FORMAT	equ	1706

;The network address is invalid.
RPC_S_INVALID_NET_ADDR 	equ	1707

;No endpoint was found.
RPC_S_NO_ENDPOINT_FOUND	equ	1708

;The timeout value is invalid.
RPC_S_INVALID_TIMEOUT	equ	1709

;The object universal unique identifier (UUID) was not found.
RPC_S_OBJECT_NOT_FOUND 	equ	1710

;The object universal unique identifier (UUID) has already been registered.
RPC_S_ALREADY_REGISTERED 	equ	1711

;The type universal unique identifier (UUID) has already been registered.
RPC_S_TYPE_ALREADY_REGISTERED	equ	1712

;The RPC server is already listening.
RPC_S_ALREADY_LISTENING	equ	1713

;No protocol sequences have been registered.
RPC_S_NO_PROTSEQS_REGISTERED 	equ	1714

;The RPC server is not listening.
RPC_S_NOT_LISTENING	equ	1715

;The manager type is unknown.
RPC_S_UNKNOWN_MGR_TYPE 	equ	1716

;The interface is unknown.
RPC_S_UNKNOWN_IF 	equ	1717

;There are no bindings.
RPC_S_NO_BINDINGS	equ	1718

;There are no protocol sequences.
RPC_S_NO_PROTSEQS	equ	1719

;The endpoint cannot be created.
RPC_S_CANT_CREATE_ENDPOINT 	equ	1720

;Not enough resources are available to complete this operation.
RPC_S_OUT_OF_RESOURCES 	equ	1721

;The RPC server is unavailable.
RPC_S_SERVER_UNAVAILABLE 	equ	1722

;The RPC server is too busy to complete this operation.
RPC_S_SERVER_TOO_BUSY	equ	1723

;The network options are invalid.
RPC_S_INVALID_NETWORK_OPTIONS	equ	1724

;There is not a remote procedure call active in this thread.
RPC_S_NO_CALL_ACTIVE 	equ	1725

;The remote procedure call failed.
RPC_S_CALL_FAILED	equ	1726

;The remote procedure call failed and did not execute.
RPC_S_CALL_FAILED_DNE	equ	1727

;A remote procedure call (RPC) protocol error occurred.
RPC_S_PROTOCOL_ERROR 	equ	1728

;The transfer syntax is not supported by the RPC server.
RPC_S_UNSUPPORTED_TRANS_SYN	equ	1730

;The universal unique identifier (UUID) type is not supported.
RPC_S_UNSUPPORTED_TYPE 	equ	1732

;The tag is invalid.
RPC_S_INVALID_TAG	equ	1733

;The array bounds are invalid.
RPC_S_INVALID_BOUND	equ	1734

;The binding does not contain an entry name.
RPC_S_NO_ENTRY_NAME	equ	1735

;The name syntax is invalid.
RPC_S_INVALID_NAME_SYNTAX	equ	1736

;The name syntax is not supported.
RPC_S_UNSUPPORTED_NAME_SYNTAX	equ	1737

;No network address is available to use to construct a universa
;unique identifier (UUID).
RPC_S_UUID_NO_ADDRESS	equ	1739

;The endpoint is a duplicate.
RPC_S_DUPLICATE_ENDPOINT 	equ	1740

;The authentication type is unknown.
RPC_S_UNKNOWN_AUTHN_TYPE 	equ	1741

;The maximum number of calls is too small.
RPC_S_MAX_CALLS_TOO_SMALL	equ	1742

;The string is too long.
RPC_S_STRING_TOO_LONG	equ	1743

;The RPC protocol sequence was not found.
RPC_S_PROTSEQ_NOT_FOUND	equ	1744

;The procedure number is out of range.
RPC_S_PROCNUM_OUT_OF_RANGE 	equ	1745

;The binding does not contain any authentication information.
RPC_S_BINDING_HAS_NO_AUTH	equ	1746

;The authentication service is unknown.
RPC_S_UNKNOWN_AUTHN_SERVICE	equ	1747

;The authentication level is unknown.
RPC_S_UNKNOWN_AUTHN_LEVEL	equ	1748

;The security context is invalid.
RPC_S_INVALID_AUTH_IDENTITY	equ	1749

;The authorization service is unknown.
RPC_S_UNKNOWN_AUTHZ_SERVICE	equ	1750

;The entry is invalid.
EPT_S_INVALID_ENTRY	equ	1751

;The server endpoint cannot perform the operation.
EPT_S_CANT_PERFORM_OP	equ	1752

;There are no more endpoints available from the endpoint mapper.
EPT_S_NOT_REGISTERED 	equ	1753

;No interfaces have been exported.
RPC_S_NOTHING_TO_EXPORT	equ	1754

;The entry name is incomplete.
RPC_S_INCOMPLETE_NAME	equ	1755

;The version option is invalid.
RPC_S_INVALID_VERS_OPTION	equ	1756

;There are no more members.
RPC_S_NO_MORE_MEMBERS	equ	1757

;There is nothing to unexport.
RPC_S_NOT_ALL_OBJS_UNEXPORTED	equ	1758

;The interface was not found.
RPC_S_INTERFACE_NOT_FOUND	equ	1759

;The entry already exists.
RPC_S_ENTRY_ALREADY_EXISTS 	equ	1760

;The entry is not found.
RPC_S_ENTRY_NOT_FOUND	equ	1761

;The name service is unavailable.
RPC_S_NAME_SERVICE_UNAVAILABLE 	equ	1762

;The network address family is invalid.
RPC_S_INVALID_NAF_ID 	equ	1763

;The requested operation is not supported.
RPC_S_CANNOT_SUPPORT 	equ	1764

;No security context is available to allow impersonation.
RPC_S_NO_CONTEXT_AVAILABLE 	equ	1765

;An internal error occurred in a remote procedure call (RPC).
RPC_S_INTERNAL_ERROR 	equ	1766

;The RPC server attempted an integer division by zero.
RPC_S_ZERO_DIVIDE	equ	1767

;An addressing error occurred in the RPC server.
RPC_S_ADDRESS_ERROR	equ	1768

;A floating-point operation at the RPC server caused a division by zero.
RPC_S_FP_DIV_ZERO	equ	1769

;A floating-point underflow occurred at the RPC server.
RPC_S_FP_UNDERFLOW 	equ	1770

;A floating-point overflow occurred at the RPC server.
RPC_S_FP_OVERFLOW	equ	1771

;The list of RPC servers available for the binding of auto handles
;has been exhausted.
RPC_X_NO_MORE_ENTRIES	equ	1772

;Unable to open the character translation table file.
RPC_X_SS_CHAR_TRANS_OPEN_FAIL	equ	1773

;The file containing the character translation table has fewer than
;512 bytes.
RPC_X_SS_CHAR_TRANS_SHORT_FILE 	equ	1774

;A null context handle was passed from the client to the host during
;a remote procedure call.
RPC_X_SS_IN_NULL_CONTEXT 	equ	1775

;The context handle changed during a remote procedure call.
RPC_X_SS_CONTEXT_DAMAGED 	equ	1777

;The binding handles passed to a remote procedure call do not match.
RPC_X_SS_HANDLES_MISMATCH	equ	1778

;The stub is unable to get the remote procedure call handle.
RPC_X_SS_CANNOT_GET_CALL_HANDLE	equ	1779

;A null reference pointer was passed to the stub.
RPC_X_NULL_REF_POINTER 	equ	1780

;The enumeration value is out of range.
RPC_X_ENUM_VALUE_OUT_OF_RANGE	equ	1781

;The byte count is too small.
RPC_X_BYTE_COUNT_TOO_SMALL 	equ	1782

;The stub received bad data.
RPC_X_BAD_STUB_DATA	equ	1783

;The supplied user buffer is not valid for the requested operation.
ERROR_INVALID_USER_BUFFER	equ	1784

;The disk media is not recognized.It may not be formatted.
ERROR_UNRECOGNIZED_MEDIA 	equ	1785

;The workstation does not have a trust secret.
ERROR_NO_TRUST_LSA_SECRET	equ	1786

;The SAM database on the Windows NT Server does not have a computer
;account for this workstation trust relationship.
ERROR_NO_TRUST_SAM_ACCOUNT 	equ	1787

;The trust relationship between the primary domain and the trusted
;domain failed.
ERROR_TRUSTED_DOMAIN_FAILURE 	equ	1788

;The trust relationship between this workstation and the primary
;domain failed.
ERROR_TRUSTED_RELATIONSHIP_FAILURE 	equ	1789

;The network logon failed.
ERROR_TRUST_FAILURE	equ	1790

;A remote procedure call is already in progress for this thread.
RPC_S_CALL_IN_PROGRESS 	equ	1791

;An attempt was made to logon, but the network logon service was not started.
ERROR_NETLOGON_NOT_STARTED 	equ	1792

;The user's account has expired.
ERROR_ACCOUNT_EXPIRED	equ	1793

;The redirector is in use and cannot be unloaded.
ERROR_REDIRECTOR_HAS_OPEN_HANDLES 	equ	1794

;The specified printer driver is already installed.
ERROR_PRINTER_DRIVER_ALREADY_INSTALLED 	equ	1795

;The specified port is unknown.
ERROR_UNKNOWN_PORT 	equ	1796

;The printer driver is unknown.
ERROR_UNKNOWN_PRINTER_DRIVER 	equ	1797

;The print processor is unknown.
ERROR_UNKNOWN_PRINTPROCESSOR 	equ	1798

;The specified separator file is invalid.
ERROR_INVALID_SEPARATOR_FILE 	equ	1799

;The specified priority is invalid.
ERROR_INVALID_PRIORITY 	equ	1800

;The printer name is invalid.
ERROR_INVALID_PRINTER_NAME 	equ	1801

;The printer already exists.
ERROR_PRINTER_ALREADY_EXISTS 	equ	1802

;The printer command is invalid.
ERROR_INVALID_PRINTER_COMMAND	equ	1803

;The specified datatype is invalid.
ERROR_INVALID_DATATYPE 	equ	1804

;The Environment specified is invalid.
ERROR_INVALID_ENVIRONMENT	equ	1805

;There are no more bindings.
RPC_S_NO_MORE_BINDINGS 	equ	1806

;The account used is an interdomain trust account.Use your global user account or local user account to access this server.
ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT 	equ	1807

;The account used is a Computer Account.Use your global user account or local user account to access this server.
ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT 	equ	1808

;The account used is an server trust account.Use your global user account or local user account to access this server.
ERROR_NOLOGON_SERVER_TRUST_ACCOUNT 	equ	1809

;The name or security ID (SID) of the domain specified is inconsistent
;with the trust information for that domain.
ERROR_DOMAIN_TRUST_INCONSISTENT	equ	1810

;The server is in use and cannot be unloaded.
ERROR_SERVER_HAS_OPEN_HANDLES	equ	1811

;The specified image file did not contain a resource section.
ERROR_RESOURCE_DATA_NOT_FOUND	equ	1812

;The specified resource type can not be found in the image file.
ERROR_RESOURCE_TYPE_NOT_FOUND	equ	1813

;The specified resource name can not be found in the image file.
ERROR_RESOURCE_NAME_NOT_FOUND	equ	1814

;The specified resource language ID cannot be found in the image file.
ERROR_RESOURCE_LANG_NOT_FOUND	equ	1815

;Not enough quota is available to process this command.
ERROR_NOT_ENOUGH_QUOTA 	equ	1816

;No interfaces have been registered.
RPC_S_NO_INTERFACES	equ	1817

;The server was altered while processing this call.
RPC_S_CALL_CANCELLED 	equ	1818

;The binding handle does not contain all required information.
RPC_S_BINDING_INCOMPLETE 	equ	1819

;Communications failure.
RPC_S_COMM_FAILURE 	equ	1820

;The requested authentication level is not supported.
RPC_S_UNSUPPORTED_AUTHN_LEVEL	equ	1821

;No principal name registered.
RPC_S_NO_PRINC_NAME	equ	1822

;The error specified is not a valid Windows NT RPC error code.
RPC_S_NOT_RPC_ERROR	equ	1823

;A UUID that is valid only on this computer has been allocated.
RPC_S_UUID_LOCAL_ONLY	equ	1824

;A security package specific error occurred.
RPC_S_SEC_PKG_ERROR	equ	1825

;Thread is not cancelled.
RPC_S_NOT_CANCELLED	equ	1826

;Invalid operation on the encoding/decoding handle.
RPC_X_INVALID_ES_ACTION	equ	1827

;Incompatible version of the serializing package.
RPC_X_WRONG_ES_VERSION 	equ	1828

;Incompatible version of the RPC stub.
RPC_X_WRONG_STUB_VERSION 	equ	1829

;The idl pipe object is invalid or corrupted.
RPC_X_INVALID_PIPE_OBJECT	equ	1830

;The operation is invalid for a given idl pipe object.
RPC_X_INVALID_PIPE_OPERATION 	equ	1831

;The idl pipe version is not supported.
RPC_X_WRONG_PIPE_VERSION 	equ	1832

;The group member was not found.
RPC_S_GROUP_MEMBER_NOT_FOUND 	equ	1898

;The endpoint mapper database could not be created.
EPT_S_CANT_CREATE	equ	1899

;The object universal unique identifier (UUID) is the nil UUID.
RPC_S_INVALID_OBJECT 	equ	1900

;The specified time is invalid.
ERROR_INVALID_TIME 	equ	1901

;The specified Form name is invalid.
ERROR_INVALID_FORM_NAME	equ	1902

;The specified Form size is invalid
ERROR_INVALID_FORM_SIZE	equ	1903

;The specified Printer handle is already being waited on
ERROR_ALREADY_WAITING	equ	1904

;The specified Printer has been deleted
ERROR_PRINTER_DELETED	equ	1905

;The state of the Printer is invalid
ERROR_INVALID_PRINTER_STATE	equ	1906

;The user must change his password before he logs on the first time.
ERROR_PASSWORD_MUST_CHANGE 	equ	1907

;Could not find the domain controller for this domain.
ERROR_DOMAIN_CONTROLLER_NOT_FOUND 	equ	1908

;The referenced account is currently locked out and may not be logged on to.
ERROR_ACCOUNT_LOCKED_OUT 	equ	1909

;The object exporter specified was not found.
OR_INVALID_OXID	equ	1910

;The object specified was not found.
OR_INVALID_OID 	equ	1911

;The object resolver set specified was not found.
OR_INVALID_SET 	equ	1912

;Some data remains to be sent in the request buffer.
RPC_S_SEND_INCOMPLETE	equ	1913

;The list of servers for this workgroup is not currently available
ERROR_NO_BROWSER_SERVERS_FOUND	equ	6118




;;;;;;;;;;;;;/
; ; OpenGL Error Code ; ;;;;;;;;;;;;;/


;The pixel format is invalid.
ERROR_INVALID_PIXEL_FORMAT 	equ	2000

;The specified driver is invalid.
ERROR_BAD_DRIVER 	equ	2001

;The window style or class attribute is invalid for this operation.
ERROR_INVALID_WINDOW_STYLE 	equ	2002

;The requested metafile operation is not supported.
ERROR_METAFILE_NOT_SUPPORTED 	equ	2003

;The requested transformation operation is not supported.
ERROR_TRANSFORM_NOT_SUPPORTED	equ	2004

;The requested clipping operation is not supported.
ERROR_CLIPPING_NOT_SUPPORTED 	equ	2005

; End of OpenGL error codes



;;;;;;;;;;;;;;;;;;; Win32 Spooler Error Codes;;;;;;;;;;;;;;;;;;;The specified print monitor is unknown.
ERROR_UNKNOWN_PRINT_MONITOR	equ	3000

;The specified printer driver is currently in use.
ERROR_PRINTER_DRIVER_IN_USE	equ	3001

;The spool file was not found.
ERROR_SPOOL_FILE_NOT_FOUND 	equ	3002

;A StartDocPrinter call was not issued.
ERROR_SPL_NO_STARTDOC	equ	3003

;An AddJob call was not issued.
ERROR_SPL_NO_ADDJOB	equ	3004

;The specified print processor has already been installed.
ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED 	equ	3005

;The specified print monitor has already been installed.
ERROR_PRINT_MONITOR_ALREADY_INSTALLED 	equ	3006

;The specified print monitor does not have the required functions.
ERROR_INVALID_PRINT_MONITOR	equ	3007

;The specified print monitor is currently in use.
ERROR_PRINT_MONITOR_IN_USE 	equ	3008

;The requested operation is not allowed when there are jobs queued to the printer.
ERROR_PRINTER_HAS_JOBS_QUEUED	equ	3009

;The requested operation is successful.Changes will not be effective until the system is rebooted.
ERROR_SUCCESS_REBOOT_REQUIRED	equ	3010

;The requested operation is successful.Changes will not be effective until the service is restarted.
ERROR_SUCCESS_RESTART_REQUIRED 	equ	3011

;;;;;;;;;;;;;;;;;;; Wins Error Codes ;;;;;;;;;;;;;;;;;;;WINS encountered an error while processing the command.
ERROR_WINS_INTERNAL	equ	4000

;The local WINS can not be deleted.
ERROR_CAN_NOT_DEL_LOCAL_WINS 	equ	4001

;The importation from the file failed.
ERROR_STATIC_INIT	equ	4002

;The backup Failed.Was a full backup done before ?
ERROR_INC_BACKUP 	equ	4003

;The backup Failed.Check the directory that you are backing the database to.
ERROR_FULL_BACKUP	equ	4004

;The name does not exist in the WINS database.
ERROR_REC_NON_EXISTENT 	equ	4005

;Replication with a non-configured partner is not allowed.
ERROR_RPL_NOT_ALLOWED	equ	4006

;;;;;;;;;;;;;;;;;;; OLE Error Codes;;;;;;;;;;;;;;;;;;
; OLE error definitions and values
; The return value of OLE APIs and methods is an HRESULT.
; This is not a handle to anything, but is merely a 32-bit value
; with several fields encoded in the value.The parts of an
; HRESULT are shown below.
; Many of the macros and functions below were orginally defined to
; operate on SCODEs.SCODEs are no longer used.The macros are
; still present for compatibility and easy porting of Win16 code.
; Newly written code should use the HRESULT macros and functions.

;HRESULTs are 32 bit values layed out as follows:
; 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
; 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
;+-+-+-+-+-+---------------------+-------------------------------+
;|S|R|C|N|r|Facility | Code|
;+-+-+-+-+-+---------------------+-------------------------------+
;where
;S - Severity - indicates success/faih
;0 - Success
;1 - Fail (COERROR)
;R - reserved portion of the facility code, corresponds to NT's
;second severity bit.
;C - reserved portion of the facility code, corresponds to NT's
;C field.
;N - reserved portion of the facility code. Used to indicate a
;mapped NT status value.
;r - reserved portion of the facility code. Reserved for internah
;use. Used to indicate HRESULT values that are not status
;values, but are instead message ids for display strings.
;Facility - is the facility code
;Code - is the facility's status code

; Severity values

SEVERITY_SUCCESS	equ	0
SEVERITY_ERROR	equ	1



; Create an HRESULT value from component pieces

;MAKE_HRESULT(sev,fac,code) ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
;MAKE_SCODE(sev,fac,code) ((SCODE) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )


; Map a WIN32 error value into a HRESULT
; Note: This assumes that WIN32 errors fall in the range -32k to 32k.
; Define bits here so macros are guaranteed to work

FACILITY_NT_BIT	equ		equ	10000000
;HRESULT_FROM_WIN32(x) (x ? ((HRESULT) (((x) &	equ	0000FFFF) | (FACILITY_WIN32 << 16) |	equ	80000000)) : 0 )

; Map an NT status value into a HRESULT

;HRESULT_FROM_NT(x)((HRESULT) ((x) | FACILITY_NT_BIT))


; ---------------------- HRESULT value definitions -----------------
; HRESULT definitions

NOERROR	equ	0

; Error definitions follow

; Codes	equ	4000-	equ	40ff are reserved for OLE
; Error codes
;Catastrophic failure
E_UNEXPECTED	equ	8000FFFFh

;Not implemented
E_NOTIMPL	equ	80004001h

;Ran out of memory
E_OUTOFMEMORY	equ	8007000Eh

;One or more arguments are invalid
E_INVALIDARG 	equ	80070057h

;No such interface supported
E_NOINTERFACE	equ	80004002h

;Invalid pointer
E_POINTER	equ	80004003h

;Invalid handle
E_HANDLE 	equ	80070006h

;Operation aborted
E_ABORT	equ	80004004h

;Unspecified error
E_FAIL 	equ	80004005h

;General access denied error
E_ACCESSDENIED 	equ	80070005h

;The data necessary to complete this operation is not yet available.
E_PENDING	equ	8000000Ah

;Thread local storage failure
CO_E_INIT_TLS	equ	80004006h

;Get shared memory allocator failure
CO_E_INIT_SHARED_ALLOCATOR 	equ	80004007h

;Get memory allocator failure
CO_E_INIT_MEMORY_ALLOCATOR 	equ	80004008h

;Unable to initialize class cache
CO_E_INIT_CLASS_CACHE	equ	80004009h

;Unable to initialize RPC services
CO_E_INIT_RPC_CHANNEL	equ	8000400Ah

;Cannot set thread local storage channel controh
CO_E_INIT_TLS_SET_CHANNEL_CONTROL 	equ	8000400Bh

;Could not allocate thread local storage channel controh
CO_E_INIT_TLS_CHANNEL_CONTROL	equ	8000400Ch

;The user supplied memory allocator is unacceptable
CO_E_INIT_UNACCEPTED_USER_ALLOCATOR 	equ	8000400Dh

;The OLE service mutex already exists
CO_E_INIT_SCM_MUTEX_EXISTS 	equ	8000400Eh

;The OLE service file mapping already exists
CO_E_INIT_SCM_FILE_MAPPING_EXISTS 	equ	8000400Fh

;Unable to map view of file for OLE service
CO_E_INIT_SCM_MAP_VIEW_OF_FILE 	equ	80004010h

;Failure attempting to launch OLE service
CO_E_INIT_SCM_EXEC_FAILURE 	equ	80004011h

;There was an attempt to call CoInitialize a second time while single threaded
CO_E_INIT_ONLY_SINGLE_THREADED 	equ	80004012h

;A Remote activation was necessary but was not allowed
CO_E_CANT_REMOTE 	equ	80004013h

;A Remote activation was necessary but the server name provided was invalid
CO_E_BAD_SERVER_NAME 	equ	80004014h

;The class is configured to run as a security id different from the caller
CO_E_WRONG_SERVER_IDENTITY 	equ	80004015h

;Use of Ole1 services requiring DDE windows is disabled
CO_E_OLE1DDE_DISABLED	equ	80004016h

;A RunAs specification must be <domain name>\<user name> or simply <user name>
CO_E_RUNAS_SYNTAX	equ	80004017h

;The server process could not be started.The pathname may be incorrect.
CO_E_CREATEPROCESS_FAILURE 	equ	80004018h

;The server process could not be started as the configured identity.The pathname may be incorrect or unavailable.
CO_E_RUNAS_CREATEPROCESS_FAILURE 	equ	80004019h

;The server process could not be started because the configured identity is incorrect.Check the username and password.
CO_E_RUNAS_LOGON_FAILURE 	equ	8000401Ah

;The client is not allowed to launch this server.
CO_E_LAUNCH_PERMSSION_DENIED 	equ	8000401Bh

;The service providing this server could not be started.
CO_E_START_SERVICE_FAILURE 	equ	8000401Ch

;This computer was unable to communicate with the computer providing the server.
CO_E_REMOTE_COMMUNICATION_FAILURE 	equ	8000401Dh

;The server did not respond after being launched.
CO_E_SERVER_START_TIMEOUT	equ	8000401Eh

;The registration information for this server is inconsistent or incomplete.
CO_E_CLSREG_INCONSISTENT 	equ	8000401Fh

;The registration information for this interface is inconsistent or incomplete.
CO_E_IIDREG_INCONSISTENT 	equ	80004020h

;The operation attempted is not supported.
CO_E_NOT_SUPPORTED 	equ	80004021h


; Success codes
S_OK	equ	0
S_FALSE	equ	1

; ******************
; FACILITY_ITF
; ******************

; Codes	equ	0-	equ	01ff are reserved for the OLE group of
; interfaces.


; Generic OLE errors that may be returned by many inerfaces

OLE_E_FIRST 	equ	80040000h
OLE_E_LAST	equ	800400FFh
OLE_S_FIRST 	equ	00040000h
OLE_S_LAST	equ	000400FFh

; Old OLE errors
;Invalid OLEVERB structure
OLE_E_OLEVERB	equ	80040000h

;Invalid advise flags
OLE_E_ADVF 	equ	80040001h

;Can't enumerate any more, because the associated data is missing
OLE_E_ENUM_NOMORE	equ	80040002h

;This implementation doesn't take advises
OLE_E_ADVISENOTSUPPORTED 	equ	80040003h

;There is no connection for this connection ID
OLE_E_NOCONNECTION 	equ	80040004h

;Need to run the object to perform this operation
OLE_E_NOTRUNNING 	equ	80040005h

;There is no cache to operate on
OLE_E_NOCACHE	equ	80040006h

;Uninitialized object
OLE_E_BLANK	equ	80040007h

;Linked object's source class has changed
OLE_E_CLASSDIFF	equ	80040008h

;Not able to get the moniker of the object
OLE_E_CANT_GETMONIKER	equ	80040009h

;Not able to bind to the source
OLE_E_CANT_BINDTOSOURCE	equ	8004000Ah

;Object is static; operation not allowed
OLE_E_STATIC 	equ	8004000Bh

;User cancelled out of save dialog
OLE_E_PROMPTSAVECANCELLED	equ	8004000Ch

;Invalid rectangle
OLE_E_INVALIDRECT	equ	8004000Dh

;compobj.dll is too old for the ole2.dll initialized
OLE_E_WRONGCOMPOBJ 	equ	8004000Eh

;Invalid window handle
OLE_E_INVALIDHWND	equ	8004000Fh

;Object is not in any of the inplace active states
OLE_E_NOT_INPLACEACTIVE	equ	80040010h

;Not able to convert object
OLE_E_CANTCONVERT	equ	80040011h

;Not able to perform the operation because object is not given storage yet
OLE_E_NOSTORAGE	equ	80040012h

;Invalid FORMATETC structure
DV_E_FORMATETC 	equ	80040064h

;Invalid DVTARGETDEVICE structure
DV_E_DVTARGETDEVICE	equ	80040065h

;Invalid STDGMEDIUM structure
DV_E_STGMEDIUM 	equ	80040066h

;Invalid STATDATA structure
DV_E_STATDATA	equ	80040067h

;Invalid lindex
DV_E_LINDEX	equ	80040068h

;Invalid tymed
DV_E_TYMED 	equ	80040069h

;Invalid clipboard format
DV_E_CLIPFORMAT	equ	8004006Ah

;Invalid aspect(s)
DV_E_DVASPECT	equ	8004006Bh

;tdSize parameter of the DVTARGETDEVICE structure is invalid
DV_E_DVTARGETDEVICE_SIZE 	equ	8004006Ch

;Object doesn't support IViewObject interface
DV_E_NOIVIEWOBJECT 	equ	8004006Dh

DRAGDROP_E_FIRST	equ	80040100h
DRAGDROP_E_LAST	equ	8004010Fh
DRAGDROP_S_FIRST	equ	00040100h
DRAGDROP_S_LAST	equ	0004010Fh
;Trying to revoke a drop target that has not been registered
DRAGDROP_E_NOTREGISTERED 	equ	80040100h

;This window has already been registered as a drop target
DRAGDROP_E_ALREADYREGISTERED 	equ	80040101h

;Invalid window handle
DRAGDROP_E_INVALIDHWND 	equ	80040102h

CLASSFACTORY_E_FIRST	equ	80040110h
CLASSFACTORY_E_LAST	equ	8004011Fh
CLASSFACTORY_S_FIRST	equ	00040110h
CLASSFACTORY_S_LAST	equ	0004011Fh
;Class does not support aggregation (or class object is remote)
CLASS_E_NOAGGREGATION	equ	80040110h

;ClassFactory cannot supply requested class
CLASS_E_CLASSNOTAVAILABLE	equ	80040111h

MARSHAL_E_FIRST	equ	80040120h
MARSHAL_E_LAST	equ	8004012Fh
MARSHAL_S_FIRST	equ	00040120h
MARSHAL_S_LAST	equ	0004012Fh
DATA_E_FIRST	equ	80040130h
DATA_E_LAST	equ	8004013Fh
DATA_S_FIRST	equ	00040130h
DATA_S_LAST	equ	0004013Fh
VIEW_E_FIRST	equ	80040140h
VIEW_E_LAST	equ	8004014Fh
VIEW_S_FIRST	equ	00040140h
VIEW_S_LAST	equ	0004014Fh
;Error drawing view
VIEW_E_DRAW	equ	80040140h

REGDB_E_FIRST	equ	80040150h
REGDB_E_LAST	equ	8004015Fh
REGDB_S_FIRST	equ	00040150h
REGDB_S_LAST	equ	0004015Fh
;Could not read key from registry
REGDB_E_READREGDB	equ	80040150h

;Could not write key to registry
REGDB_E_WRITEREGDB 	equ	80040151h

;Could not find the key in the registry
REGDB_E_KEYMISSING 	equ	80040152h

;Invalid value for registry
REGDB_E_INVALIDVALUE 	equ	80040153h

;Class not registered
REGDB_E_CLASSNOTREG	equ	80040154h

;Interface not registered
REGDB_E_IIDNOTREG	equ	80040155h

CACHE_E_FIRST	equ	80040170h
CACHE_E_LAST	equ	8004017Fh
CACHE_S_FIRST	equ	00040170h
CACHE_S_LAST	equ	0004017Fh
;Cache not updated
CACHE_E_NOCACHE_UPDATED	equ	80040170h

OLEOBJ_E_FIRST	equ	80040180h
OLEOBJ_E_LAST	equ	8004018Fh
OLEOBJ_S_FIRST	equ	00040180h
OLEOBJ_S_LAST	equ	0004018Fh
;No verbs for OLE object
OLEOBJ_E_NOVERBS 	equ	80040180h

;Invalid verb for OLE object
OLEOBJ_E_INVALIDVERB 	equ	80040181h

CLIENTSITE_E_FIRST	equ	80040190h
CLIENTSITE_E_LAST	equ	8004019Fh
CLIENTSITE_S_FIRST	equ	00040190h
CLIENTSITE_S_LAST	equ	0004019Fh
;Undo is not available
INPLACE_E_NOTUNDOABLE	equ	800401A0h

;Space for tools is not available
INPLACE_E_NOTOOLSPACE	equ	800401A1h

INPLACE_E_FIRST	equ	800401A0h
INPLACE_E_LAST	equ	800401AFh
INPLACE_S_FIRST	equ	000401A0h
INPLACE_S_LAST	equ	000401AFh
ENUM_E_FIRST	equ	800401B0h
ENUM_E_LAST	equ	800401BFh
ENUM_S_FIRST	equ	000401B0h
ENUM_S_LAST	equ	000401BFh
CONVERT10_E_FIRST	equ	800401C0h
CONVERT10_E_LAST	equ	800401CFh
CONVERT10_S_FIRST	equ	000401C0h
CONVERT10_S_LAST	equ	000401CFh
;OLESTREAM Get method failed
CONVERT10_E_OLESTREAM_GET	equ	800401C0h

;OLESTREAM Put method failed
CONVERT10_E_OLESTREAM_PUT	equ	800401C1h

;Contents of the OLESTREAM not in correct format
CONVERT10_E_OLESTREAM_FMT	equ	800401C2h

;There was an error in a Windows GDI call while converting the bitmap to a DIB
CONVERT10_E_OLESTREAM_BITMAP_TO_DIB 	equ	800401C3h

;Contents of the IStorage not in correct format
CONVERT10_E_STG_FMT	equ	800401C4h

;Contents of IStorage is missing one of the standard streams
CONVERT10_E_STG_NO_STD_STREAM	equ	800401C5h

;There was an error in a Windows GDI call while converting the DIB to a bitmap.
CONVERT10_E_STG_DIB_TO_BITMAP	equ	800401C6h

CLIPBRD_E_FIRST	equ	800401D0h
CLIPBRD_E_LAST	equ	800401DFh
CLIPBRD_S_FIRST	equ	000401D0h
CLIPBRD_S_LAST	equ	000401DFh
;OpenClipboard Failed
CLIPBRD_E_CANT_OPEN	equ	800401D0h

;EmptyClipboard Failed
CLIPBRD_E_CANT_EMPTY 	equ	800401D1h

;SetClipboard Failed
CLIPBRD_E_CANT_SET 	equ	800401D2h

;Data on clipboard is invalid
CLIPBRD_E_BAD_DATA 	equ	800401D3h

;CloseClipboard Failed
CLIPBRD_E_CANT_CLOSE 	equ	800401D4h

MK_E_FIRST	equ	800401E0h
MK_E_LAST	equ	800401EFh
MK_S_FIRST	equ	000401E0h
MK_S_LAST	equ	000401EFh
;Moniker needs to be connected manually
MK_E_CONNECTMANUALLY 	equ	800401E0h

;Operation exceeded deadline
MK_E_EXCEEDEDDEADLINE	equ	800401E1h

;Moniker needs to be generic
MK_E_NEEDGENERIC 	equ	800401E2h

;Operation unavailable
MK_E_UNAVAILABLE 	equ	800401E3h

;Invalid syntax
MK_E_SYNTAX	equ	800401E4h

;No object for moniker
MK_E_NOOBJECT	equ	800401E5h

;Bad extension for file
MK_E_INVALIDEXTENSION	equ	800401E6h

;Intermediate operation failed
MK_E_INTERMEDIATEINTERFACENOTSUPPORTED 	equ	800401E7h

;Moniker is not bindable
MK_E_NOTBINDABLE 	equ	800401E8h

;Moniker is not bound
MK_E_NOTBOUND	equ	800401E9h

;Moniker cannot open file
MK_E_CANTOPENFILE	equ	800401EAh

;User input required for operation to succeed
MK_E_MUSTBOTHERUSER	equ	800401EBh

;Moniker class has no inverse
MK_E_NOINVERSE 	equ	800401ECh

;Moniker does not refer to storage
MK_E_NOSTORAGE 	equ	800401EDh

;No common prefix
MK_E_NOPREFIX	equ	800401EEh

;Moniker could not be enumerated
MK_E_ENUMERATION_FAILED	equ	800401EFh

CO_E_FIRST	equ	800401F0h
CO_E_LAST	equ	800401FFh
CO_S_FIRST	equ	000401F0h
CO_S_LAST	equ	000401FFh
;CoInitialize has not been called.
CO_E_NOTINITIALIZED	equ	800401F0h

;CoInitialize has already been called.
CO_E_ALREADYINITIALIZED	equ	800401F1h

;Class of object cannot be determined
CO_E_CANTDETERMINECLASS	equ	800401F2h

;Invalid class string
CO_E_CLASSSTRING 	equ	800401F3h

;Invalid interface string
CO_E_IIDSTRING 	equ	800401F4h

;Application not found
CO_E_APPNOTFOUND 	equ	800401F5h

;Application cannot be run more than once
CO_E_APPSINGLEUSE	equ	800401F6h

;Some error in application program
CO_E_ERRORINAPP	equ	800401F7h

;DLL for class not found
CO_E_DLLNOTFOUND 	equ	800401F8h

;Error in the DLh
CO_E_ERRORINDLL	equ	800401F9h

;Wrong OS or OS version for application
CO_E_WRONGOSFORAPP 	equ	800401FAh

;Object is not registered
CO_E_OBJNOTREG 	equ	800401FBh

;Object is already registered
CO_E_OBJISREG	equ	800401FCh

;Object is not connected to server
CO_E_OBJNOTCONNECTED 	equ	800401FDh

;Application was launched but it didn't register a class factory
CO_E_APPDIDNTREG 	equ	800401FEh

;Object has been released
CO_E_RELEASED	equ	800401FFh

; Old OLE Success Codes
;Use the registry database to provide the requested information
OLE_S_USEREG 	equ	00040000h

;Success, but static
OLE_S_STATIC 	equ	00040001h

;Macintosh clipboard format
OLE_S_MAC_CLIPFORMAT 	equ	00040002h

;Successful drop took place
DRAGDROP_S_DROP	equ	00040100h

;Drag-drop operation canceled
DRAGDROP_S_CANCEL	equ	00040101h

;Use the default cursor
DRAGDROP_S_USEDEFAULTCURSORS 	equ	00040102h

;Data has same FORMATETC
DATA_S_SAMEFORMATETC 	equ	00040130h

;View is already frozen
VIEW_S_ALREADY_FROZEN	equ	00040140h

;FORMATETC not supported
CACHE_S_FORMATETC_NOTSUPPORTED 	equ	00040170h

;Same cache
CACHE_S_SAMECACHE	equ	00040171h

;Some cache(s) not updated
CACHE_S_SOMECACHES_NOTUPDATED	equ	00040172h

;Invalid verb for OLE object
OLEOBJ_S_INVALIDVERB 	equ	00040180h

;Verb number is valid but verb cannot be done now
OLEOBJ_S_CANNOT_DOVERB_NOW 	equ	00040181h

;Invalid window handle passed
OLEOBJ_S_INVALIDHWND 	equ	00040182h

;Message is too long; some of it had to be truncated before displaying
INPLACE_S_TRUNCATED	equ	000401A0h

;Unable to convert OLESTREAM to IStorage
CONVERT10_S_NO_PRESENTATION	equ	000401C0h

;Moniker reduced to itself
MK_S_REDUCED_TO_SELF 	equ	000401E2h

;Common prefix is this moniker
MK_S_ME	equ	000401E4h

;Common prefix is input moniker
MK_S_HIM 	equ	000401E5h

;Common prefix is both monikers
MK_S_US	equ	000401E6h

;Moniker is already registered in running object table
MK_S_MONIKERALREADYREGISTERED	equ	000401E7h

; ******************
; FACILITY_WINDOWS
; ******************
; Codes	equ	0-	equ	01ff are reserved for the OLE group of
; interfaces.
;Attempt to create a class object failed
CO_E_CLASS_CREATE_FAILED 	equ	80080001h

;OLE service could not bind object
CO_E_SCM_ERROR 	equ	80080002h

;RPC communication failed with OLE service
CO_E_SCM_RPC_FAILURE 	equ	80080003h

;Bad path to object
CO_E_BAD_PATH	equ	80080004h

;Server execution failed
CO_E_SERVER_EXEC_FAILURE 	equ	80080005h

;OLE service could not communicate with the object server
CO_E_OBJSRV_RPC_FAILURE	equ	80080006h

;Moniker path could not be normalized
MK_E_NO_NORMALIZED 	equ	80080007h

;Object server is stopping when OLE service contacts it
CO_E_SERVER_STOPPING 	equ	80080008h

;An invalid root block pointer was specified
MEM_E_INVALID_ROOT 	equ	80080009h

;An allocation chain contained an invalid link pointer
MEM_E_INVALID_LINK 	equ	80080010h

;The requested allocation size was too large
MEM_E_INVALID_SIZE 	equ	80080011h

;Not all the requested interfaces were available
CO_S_NOTALLINTERFACES	equ	00080012h

; ******************
; FACILITY_DISPATCH
; ******************
;Unknown interface.
DISP_E_UNKNOWNINTERFACE	equ	80020001h

;Member not found.
DISP_E_MEMBERNOTFOUND	equ	80020003h

;Parameter not found.
DISP_E_PARAMNOTFOUND 	equ	80020004h

;Type mismatch.
DISP_E_TYPEMISMATCH	equ	80020005h

;Unknown name.
DISP_E_UNKNOWNNAME 	equ	80020006h

;No named arguments.
DISP_E_NONAMEDARGS 	equ	80020007h

;Bad variable type.
DISP_E_BADVARTYPE	equ	80020008h

;Exception occurred.
DISP_E_EXCEPTION 	equ	80020009h

;Out of present range.
DISP_E_OVERFLOW	equ	8002000Ah

;Invalid index.
DISP_E_BADINDEX	equ	8002000Bh

;Unknown language.
DISP_E_UNKNOWNLCID 	equ	8002000Ch

;Memory is locked.
DISP_E_ARRAYISLOCKED 	equ	8002000Dh

;Invalid number of parameters.
DISP_E_BADPARAMCOUNT 	equ	8002000Eh

;Parameter not optional.
DISP_E_PARAMNOTOPTIONAL	equ	8002000Fh

;Invalid callee.
DISP_E_BADCALLEE 	equ	80020010h

;Does not support a collection.
DISP_E_NOTACOLLECTION	equ	80020011h

;Buffer too small.
TYPE_E_BUFFERTOOSMALL	equ	80028016h

;Old format or invalid type library.
TYPE_E_INVDATAREAD 	equ	80028018h

;Old format or invalid type library.
TYPE_E_UNSUPFORMAT 	equ	80028019h

;Error accessing the OLE registry.
TYPE_E_REGISTRYACCESS	equ	8002801Ch

;Library not registered.
TYPE_E_LIBNOTREGISTERED	equ	8002801Dh

;Bound to unknown type.
TYPE_E_UNDEFINEDTYPE 	equ	80028027h

;Qualified name disallowed.
TYPE_E_QUALIFIEDNAMEDISALLOWED 	equ	80028028h

;Invalid forward reference, or reference to uncompiled type.
TYPE_E_INVALIDSTATE	equ	80028029h

;Type mismatch.
TYPE_E_WRONGTYPEKIND 	equ	8002802Ah

;Element not found.
TYPE_E_ELEMENTNOTFOUND 	equ	8002802Bh

;Ambiguous name.
TYPE_E_AMBIGUOUSNAME 	equ	8002802Ch

;Name already exists in the library.
TYPE_E_NAMECONFLICT	equ	8002802Dh

;Unknown LCID.
TYPE_E_UNKNOWNLCID 	equ	8002802Eh

;Function not defined in specified DLL.
TYPE_E_DLLFUNCTIONNOTFOUND 	equ	8002802Fh

;Wrong module kind for the operation.
TYPE_E_BADMODULEKIND 	equ	800288BDh

;Size may not exceed 64K.
TYPE_E_SIZETOOBIG	equ	800288C5h

;Duplicate ID in inheritance hierarchy.
TYPE_E_DUPLICATEID 	equ	800288C6h

;Incorrect inheritance depth in standard OLE hmember.
TYPE_E_INVALIDID 	equ	800288CFh

;Type mismatch.
TYPE_E_TYPEMISMATCH	equ	80028CA0h

;Invalid number of arguments.
TYPE_E_OUTOFBOUNDS 	equ	80028CA1h

;I/O Error.
TYPE_E_IOERROR 	equ	80028CA2h

;Error creating unique tmp file.
TYPE_E_CANTCREATETMPFILE 	equ	80028CA3h

;Error loading type library/DLL.
TYPE_E_CANTLOADLIBRARY 	equ	80029C4Ah

;Inconsistent property functions.
TYPE_E_INCONSISTENTPROPFUNCS 	equ	80029C83h

;Circular dependency between types/modules.
TYPE_E_CIRCULARTYPE	equ	80029C84h

; ******************
; FACILITY_STORAGE
; ******************
;Unable to perform requested operation.
STG_E_INVALIDFUNCTION	equ	80030001h

;%1 could not be found.
STG_E_FILENOTFOUND 	equ	80030002h

;The path %1 could not be found.
STG_E_PATHNOTFOUND 	equ	80030003h

;There are insufficient resources to open another file.
STG_E_TOOMANYOPENFILES 	equ	80030004h

;Access Denied.
STG_E_ACCESSDENIED 	equ	80030005h

;Attempted an operation on an invalid object.
STG_E_INVALIDHANDLE	equ	80030006h

;There is insufficient memory available to complete operation.
STG_E_INSUFFICIENTMEMORY 	equ	80030008h

;Invalid pointer error.
STG_E_INVALIDPOINTER 	equ	80030009h

;There are no more entries to return.
STG_E_NOMOREFILES	equ	80030012h

;Disk is write-protected.
STG_E_DISKISWRITEPROTECTED 	equ	80030013h

;An error occurred during a seek operation.
STG_E_SEEKERROR	equ	80030019h

;A disk error occurred during a write operation.
STG_E_WRITEFAULT 	equ	8003001Dh

;A disk error occurred during a read operation.
STG_E_READFAULT	equ	8003001Eh

;A share violation has occurred.
STG_E_SHAREVIOLATION 	equ	80030020h

;A lock violation has occurred.
STG_E_LOCKVIOLATION	equ	80030021h

;%1 already exists.
STG_E_FILEALREADYEXISTS	equ	80030050h

;Invalid parameter error.
STG_E_INVALIDPARAMETER 	equ	80030057h

;There is insufficient disk space to complete operation.
STG_E_MEDIUMFULL 	equ	80030070h

;Illegal write of non-simple property to simple property set.
STG_E_PROPSETMISMATCHED	equ	800300F0h

;An API call exited abnormally.
STG_E_ABNORMALAPIEXIT	equ	800300FAh

;The file %1 is not a valid compound file.
STG_E_INVALIDHEADER	equ	800300FBh

;The name %1 is not valid.
STG_E_INVALIDNAME	equ	800300FCh

;An unexpected error occurred.
STG_E_UNKNOWN	equ	800300FDh

;That function is not implemented.
STG_E_UNIMPLEMENTEDFUNCTION	equ	800300FEh

;Invalid flag error.
STG_E_INVALIDFLAG	equ	800300FFh

;Attempted to use an object that is busy.
STG_E_INUSE	equ	80030100h

;The storage has been changed since the last commit.
STG_E_NOTCURRENT 	equ	80030101h

;Attempted to use an object that has ceased to exist.
STG_E_REVERTED 	equ	80030102h

;Can't save.
STG_E_CANTSAVE 	equ	80030103h

;The compound file %1 was produced with an incompatible version of storage.
STG_E_OLDFORMAT	equ	80030104h

;The compound file %1 was produced with a newer version of storage.
STG_E_OLDDLL 	equ	80030105h

;Share.exe or equivalent is required for operation.
STG_E_SHAREREQUIRED	equ	80030106h

;Illegal operation called on non-file based storage.
STG_E_NOTFILEBASEDSTORAGE	equ	80030107h

;Illegal operation called on object with extant marshallings.
STG_E_EXTANTMARSHALLINGS 	equ	80030108h

;The docfile has been corrupted.
STG_E_DOCFILECORRUPT 	equ	80030109h

;OLE32.DLL has been loaded at the wrong address.
STG_E_BADBASEADDRESS 	equ	80030110h

;The file download was aborted abnormally.The file is incomplete.
STG_E_INCOMPLETE 	equ	80030201h

;The file download has been terminated.
STG_E_TERMINATED 	equ	80030202h

;The underlying file was converted to compound file format.
STG_S_CONVERTED	equ	00030200h

;The storage operation should block until more data is available.
STG_S_BLOCK	equ	00030201h

;The storage operation should retry immediately.
STG_S_RETRYNOW 	equ	00030202h

;The notified event sink will not influence the storage operation.
STG_S_MONITORING 	equ	00030203h

; ******************
; FACILITY_RPC
; ******************
; Codes	equ	0-	equ	11 are propogated from 16 bit OLE.
;Call was rejected by callee.
RPC_E_CALL_REJECTED	equ	80010001h

;Call was canceled by the message filter.
RPC_E_CALL_CANCELED	equ	80010002h

;The caller is dispatching an intertask SendMessage call and
;cannot call out via PostMessage.
RPC_E_CANTPOST_INSENDCALL	equ	80010003h

;The caller is dispatching an asynchronous call and cannot
;make an outgoing call on behalf of this call.
RPC_E_CANTCALLOUT_INASYNCCALL	equ	80010004h

;It is illegal to call out while inside message filter.
RPC_E_CANTCALLOUT_INEXTERNALCALL 	equ	80010005h

;The connection terminated or is in a bogus state
;and cannot be used any more. Other connections
;are still valid.
RPC_E_CONNECTION_TERMINATED	equ	80010006h

;The callee (server [not server application]) is not available
;and disappeared; all connections are invalid.The call may
;have executed.
RPC_E_SERVER_DIED	equ	80010007h

;The caller (client) disappeared while the callee (server) was
;processing a call.
RPC_E_CLIENT_DIED	equ	80010008h

;The data packet with the marshalled parameter data is incorrect.
RPC_E_INVALID_DATAPACKET 	equ	80010009h

;The call was not transmitted properly; the message queue
;was full and was not emptied after yielding.
RPC_E_CANTTRANSMIT_CALL	equ	8001000Ah

;The client (caller) cannot marshall the parameter data - low memory, etc.
RPC_E_CLIENT_CANTMARSHAL_DATA	equ	8001000Bh

;The client (caller) cannot unmarshall the return data - low memory, etc.
RPC_E_CLIENT_CANTUNMARSHAL_DATA	equ	8001000Ch

;The server (callee) cannot marshall the return data - low memory, etc.
RPC_E_SERVER_CANTMARSHAL_DATA	equ	8001000Dh

;The server (callee) cannot unmarshall the parameter data - low memory, etc.
RPC_E_SERVER_CANTUNMARSHAL_DATA	equ	8001000Eh

;Received data is invalid; could be server or client data.
RPC_E_INVALID_DATA 	equ	8001000Fh

;A particular parameter is invalid and cannot be (un)marshalled.
RPC_E_INVALID_PARAMETER	equ	80010010h

;There is no second outgoing call on same channel in DDE conversation.
RPC_E_CANTCALLOUT_AGAIN	equ	80010011h

;The callee (server [not server application]) is not available
;and disappeared; all connections are invalid.The call did not execute.
RPC_E_SERVER_DIED_DNE	equ	80010012h

;System call failed.
RPC_E_SYS_CALL_FAILED	equ	80010100h

;Could not allocate some required resource (memory, events, ...)
RPC_E_OUT_OF_RESOURCES 	equ	80010101h

;Attempted to make calls on more than one thread in single threaded mode.
RPC_E_ATTEMPTED_MULTITHREAD	equ	80010102h

;The requested interface is not registered on the server object.
RPC_E_NOT_REGISTERED 	equ	80010103h

;RPC could not call the server or could not return the results of calling the server.
RPC_E_FAULT	equ	80010104h

;The server threw an exception.
RPC_E_SERVERFAULT	equ	80010105h

;Cannot change thread mode after it is set.
RPC_E_CHANGED_MODE 	equ	80010106h

;The method called does not exist on the server.
RPC_E_INVALIDMETHOD	equ	80010107h

;The object invoked has disconnected from its clients.
RPC_E_DISCONNECTED 	equ	80010108h

;The object invoked chose not to process the call now.Try again later.
RPC_E_RETRY	equ	80010109h

;The message filter indicated that the application is busy.
RPC_E_SERVERCALL_RETRYLATER	equ	8001010Ah

;The message filter rejected the call.
RPC_E_SERVERCALL_REJECTED	equ	8001010Bh

;A call control interfaces was called with invalid data.
RPC_E_INVALID_CALLDATA 	equ	8001010Ch

;An outgoing call cannot be made since the application is dispatching an input-synchronous call.
RPC_E_CANTCALLOUT_ININPUTSYNCCALL 	equ	8001010Dh

;The application called an interface that was marshalled for a different thread.
RPC_E_WRONG_THREAD 	equ	8001010Eh

;CoInitialize has not been called on the current thread.
RPC_E_THREAD_NOT_INIT	equ	8001010Fh

;The version of OLE on the client and server machines does not match.
RPC_E_VERSION_MISMATCH 	equ	80010110h

;OLE received a packet with an invalid header.
RPC_E_INVALID_HEADER 	equ	80010111h

;OLE received a packet with an invalid extension.
RPC_E_INVALID_EXTENSION	equ	80010112h

;The requested object or interface does not exist.
RPC_E_INVALID_IPID 	equ	80010113h

;The requested object does not exist.
RPC_E_INVALID_OBJECT 	equ	80010114h

;OLE has sent a request and is waiting for a reply.
RPC_S_CALLPENDING	equ	80010115h

;OLE is waiting before retrying a request.
RPC_S_WAITONTIMER	equ	80010116h

;Call context cannot be accessed after call completed.
RPC_E_CALL_COMPLETE	equ	80010117h

;Impersonate on unsecure calls is not supported.
RPC_E_UNSECURE_CALL	equ	80010118h

;Security must be initialized before any interfaces are marshalled or
;unmarshalled.It cannot be changed once initialized.
RPC_E_TOO_LATE 	equ	80010119h

;No security packages are installed on this machine or the user is not logged
;on or there are no compatible security packages between the client and server.
RPC_E_NO_GOOD_SECURITY_PACKAGES	equ	8001011Ah

;Access is denied.
RPC_E_ACCESS_DENIED	equ	8001011Bh

;Remote calls are not allowed for this process.
RPC_E_REMOTE_DISABLED	equ	8001011Ch

;The marshaled interface data packet (OBJREF) has an invalid or unknown format.
RPC_E_INVALID_OBJREF 	equ	8001011Dh

;An internal error occurred.
RPC_E_UNEXPECTED 	equ	8001FFFFh


 ;;;;;;;;/
  ;FACILITY_SSPI
  ;;;;;;;;/

;Bad UID.
NTE_BAD_UID	equ	80090001h

;Bad Hash.
NTE_BAD_HASH 	equ	80090002h

;Bad Key.
NTE_BAD_KEY	equ	80090003h

;Bad Length.
NTE_BAD_LEN	equ	80090004h

;Bad Data.
NTE_BAD_DATA 	equ	80090005h

;Invalid Signature.
NTE_BAD_SIGNATURE	equ	80090006h

;Bad Version of provider.
NTE_BAD_VER	equ	80090007h

;Invalid algorithm specified.
NTE_BAD_ALGID	equ	80090008h

;Invalid flags specified.
NTE_BAD_FLAGS	equ	80090009h

;Invalid type specified.
NTE_BAD_TYPE 	equ	8009000Ah

;Key not valid for use in specified state.
NTE_BAD_KEY_STATE	equ	8009000Bh

;Hash not valid for use in specified state.
NTE_BAD_HASH_STATE 	equ	8009000Ch

;Key does not exist.
NTE_NO_KEY 	equ	8009000Dh

;Insufficient memory available for the operation.
NTE_NO_MEMORY	equ	8009000Eh

;Object already exists.
NTE_EXISTS 	equ	8009000Fh

;Access denied.
NTE_PERM 	equ	80090010h

;Object was not found.
NTE_NOT_FOUND	equ	80090011h

;Data already encrypted.
NTE_DOUBLE_ENCRYPT 	equ	80090012h

;Invalid provider specified.
NTE_BAD_PROVIDER 	equ	80090013h

;Invalid provider type specified.
NTE_BAD_PROV_TYPE	equ	80090014h

;Provider's public key is invalid.
NTE_BAD_PUBLIC_KEY 	equ	80090015h

;Keyset does not exist
NTE_BAD_KEYSET 	equ	80090016h

;Provider type not defined.
NTE_PROV_TYPE_NOT_DEF	equ	80090017h

;Provider type as registered is invalid.
NTE_PROV_TYPE_ENTRY_BAD	equ	80090018h

;The keyset is not defined.
NTE_KEYSET_NOT_DEF 	equ	80090019h

;Keyset as registered is invalid.
NTE_KEYSET_ENTRY_BAD 	equ	8009001Ah

;Provider type does not match registered value.
NTE_PROV_TYPE_NO_MATCH 	equ	8009001Bh

;The digital signature file is corrupt.
NTE_SIGNATURE_FILE_BAD 	equ	8009001Ch

;Provider DLL failed to initialize correctly.
NTE_PROVIDER_DLL_FAIL	equ	8009001Dh

;Provider DLL could not be found.
NTE_PROV_DLL_NOT_FOUND 	equ	8009001Eh

;The Keyset parameter is invalid.
NTE_BAD_KEYSET_PARAM 	equ	8009001Fh

;An internal error occurred.
NTE_FAIL 	equ	80090020h

;A base error occurred.
NTE_SYS_ERR	equ	80090021h

NTE_OP_OK	equ	0

; Note that additional FACILITY_SSPI errors are in issperr.h
; ******************
; FACILITY_CERT
; ******************
;The specified trust provider is not known on this system.
TRUST_E_PROVIDER_UNKNOWN 	equ	800B0001h

;The trust verification action specified is not supported by the specified trust provider.
TRUST_E_ACTION_UNKNOWN 	equ	800B0002h

;The form specified for the subject is not one supported or known by the specified trust provider.
TRUST_E_SUBJECT_FORM_UNKNOWN 	equ	800B0003h

;The subject is not trusted for the specified action.
TRUST_E_SUBJECT_NOT_TRUSTED	equ	800B0004h

;Error due to problem in ASN.1 encoding process.
DIGSIG_E_ENCODE	equ	800B0005h

;Error due to problem in ASN.1 decoding process.
DIGSIG_E_DECODE	equ	800B0006h

;Reading / writing Extensions where Attributes are appropriate, and visa versa.
DIGSIG_E_EXTENSIBILITY 	equ	800B0007h

;Unspecified cryptographic failure.
DIGSIG_E_CRYPTO	equ	800B0008h

;The size of the data could not be determined.
PERSIST_E_SIZEDEFINITE 	equ	800B0009h

;The size of the indefinite-sized data could not be determined.
PERSIST_E_SIZEINDEFINITE 	equ	800B000Ah

;This object does not read and write self-sizing data.
PERSIST_E_NOTSELFSIZING	equ	800B000Bh

;No signature was present in the subject.
TRUST_E_NOSIGNATURE	equ	800B0100h

;A required certificate is not within its validity period.
CERT_E_EXPIRED 	equ	800B0101h

;The validity periods of the certification chain do not nest correctly.
CERT_E_VALIDIYPERIODNESTING	equ	800B0102h

;A certificate that can only be used as an end-entity is being used as a CA or visa versa.
CERT_E_ROLE	equ	800B0103h

;A path length constraint in the certification chain has been violated.
CERT_E_PATHLENCONST	equ	800B0104h

;An extension of unknown type that is labeled 'critical' is present in a certificate.
CERT_E_CRITICAL	equ	800B0105h

;A certificate is being used for a purpose other than that for which it is permitted.
CERT_E_PURPOSE 	equ	800B0106h

;A parent of a given certificate in fact did not issue that child certificate.
CERT_E_ISSUERCHAINING	equ	800B0107h

;A certificate is missing or has an empty value for an important field, such as a subject or issuer name.
CERT_E_MALFORMED 	equ	800B0108h

;A certification chain processed correctly, but terminated in a root certificate which isn't trusted by the trust provider.
CERT_E_UNTRUSTEDROOT 	equ	800B0109h

;A chain of certs didn't chain as they should in a certain application of chaining.
CERT_E_CHAINING	equ	800B010Ah
