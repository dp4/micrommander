
; IMarshal

imar_QueryInterface		equ	0
imar_AddRef		equ	4
imar_Release		equ	8
imar_GetUnmarshalClass		equ	12
imar_GetMarshalSizeMax		equ	16
imar_MarshalInterface		equ	20
imar_UnmarshalInterface	equ	24
imar_ReleaseMarshalData	equ	28
imar_DisconnectObject		equ	32

; IMalloc

imal_QueryInterface		equ	0
imal_AddRef		equ	4
imal_Release		equ	8
imal_Alloc		equ	12
imal_Realloc		equ	16
imal_Free		equ	20
imal_GetSize		equ	24
imal_DidAlloc		equ	28
imal_HeapMinimize		equ	32

; IMallocSpy

imsp_QueryInterface		equ	0
imsp_AddRef		equ	4
imsp_Release		equ	8
imsp_PreAlloc		equ	12
imsp_PostAlloc		equ	16
imsp_PreFree		equ	20
imsp_PostFree		equ	24
imsp_PreRealloc		equ	28
imsp_PostRealloc		equ	32
imsp_PreGetSize		equ	36
imsp_PostGetSize		equ	40
imsp_PreDidAlloc		equ	44
imsp_PostDidAlloc		equ	48
imsp_PreHeapMinimize		equ	52
imsp_PostHeapMinimize		equ	56

; IStdMarshalInfo

ismi_QueryInterface		equ	0
ismi_AddRef		equ	4
ismi_Release		equ	8
ismi_GetClassForHandler		equ	12

EXTCONN_STRONG		= 1
EXTCONN_WEAK		= 2
EXTCONN_CALLABLE	= 4

; IExternalConnection

iexc_QueryInterface		equ	0
iexc_AddRef		equ	4
iexc_Release		equ	8
iexc_AddConnection		equ	12
iexc_ReleaseConnection		equ	16

MULTI_QI	struc
 mqi_pIID	dd	?
 mqi_pItf	dd	?
 mqi_hr	dd	?
MULTI_QI	ends

; IMultiQI

imqi_QueryInterface		equ	0
imqi_AddRef		equ	4
imqi_Release		equ	8
imqi_QueryMultipleInterfaces	equ	12

; IEnumUnknown

ienu_QueryInterface		equ	0
ienu_AddRef		equ	4
ienu_Release		equ	8
ienu_Next		equ	12
ienu_Skip		equ	16
ienu_Reset		equ	20
ienu_Clone		equ	24

BIND_OPTS		struc
 bop_cbStruct		dd	?
 bop_grfFlags		dd	?
 bop_grfMode		dd	?
 bop_dwTickCountDeadline	dd	?
BIND_OPTS		ends

;BIND_OPTS2		struc
 ;bo2_cbStruct		dd	?
 ;bo2_grfFlags		dd	?
 ;bo2_grfMode		dd	?
 ;bo2_dwTickCountDeadline	dd	?
 ;bo2_dwTrackFlags		dd	?
; bo2_dwClassContext	dd	?
; bo2_locale		LCID	<?>
; bo2_pServerInfo		dd	?
;BIND_OPTS2		ends

BIND_MAYBOTHERUSER	= 1
BIND_JUSTTESTEXISTENCE	= 2

; IBindCtx

ibic_QueryInterface		equ	0
ibic_AddRef		equ	4
ibic_Release		equ	8
ibic_RegisterObjectBound	equ	12
ibic_RevokeObjectBound	equ	16
ibic_ReleaseBoundObjects	equ	20
ibic_SetBindOptions		equ	24
ibic_GetBindOptions		equ	28
ibic_GetRunningObjectTable	equ	32
ibic_RegisterObjectParam	equ	36
ibic_GetObjectParam		equ	40
ibic_EnumObjectParam		equ	44
ibic_RevokeObjectParam	equ	48

; IEnumMoniker

iemo_QueryInterface		equ	0
iemo_AddRef		equ	4
iemo_Release		equ	8
iemo_Next		equ	12
iemo_Skip		equ	16
iemo_Reset		equ	20
iemo_Clone		equ	24

; IRunnableObject

irob_QueryInterface		equ	0
irob_AddRef		equ	4
irob_Release		equ	8
irob_GetRunningClass		equ	12
irob_Run		equ	16
irob_IsRunning		equ	20
irob_LockRunning		equ	24
irob_SetContainedObject	equ	28


; IRunningObjectTable

irot_QueryInterface		equ	0
irot_AddRef		equ	4
irot_Release		equ	8
irot_Register		equ	12
irot_Revoke		equ	16
irot_IsRunning		equ	20
irot_GetObject		equ	24
irot_NoteChangeTime		equ	28
irot_GetTimeOfLastChange	equ	32
irot_EnumRunning		equ	36

; IPersist

iper_QueryInterface		equ	0
iper_AddRef		equ	4
iper_Release		equ	8
iper_GetClassID		equ	12

; IPersistStream

ipes_QueryInterface		equ	0
ipes_AddRef		equ	4
ipes_Release		equ	8
ipes_GetClassID		equ	12
ipes_IsDirty		equ	16
ipes_Load		equ	20
ipes_Save		equ	24
ipes_GetSizeMax		equ	28

MKSYS_NONE		= 0
MKSYS_GENERICCOMPOSITE	= 1
MKSYS_FILEMONIKER	= 2
MKSYS_ANTIMONIKER	= 3
MKSYS_ITEMMONIKER	= 4
MKSYS_POINTERMONIKER	= 5
MKSYS_CLASSMONIKER	= 7

MKRREDUCE_ONE		= 30000h
MKRREDUCE_TOUSER	= 20000h
MKRREDUCE_THROUGHUSER	= 10000h
MKRREDUCE_ALL		= 0


; IMoniker

imon_QueryInterface		equ	0
imon_AddRef		equ	4
imon_Release		equ	8
imon_GetClassID		equ	12
imon_IsDirty		equ	16
imon_Load		equ	20
imon_Save		equ	24
imon_GetSizeMax		equ	28
imon_BindToObject		equ	32
imon_BindToStorage		equ	36
imon_Reduce		equ	40
imon_ComposeWith		equ	44
imon_Enum		equ	48
imon_IsEqual		equ	52
imon_Hash		equ	56
imon_IsRunning		equ	60
imon_GetTimeOfLastChange	equ	64
imon_Inverse		equ	68
imon_CommonPrefixWith		equ	72
imon_RelativePathTo		equ	76
imon_GetDisplayName		equ	80
imon_ParseDisplayName		equ	84
imon_IsSystemMoniker		equ	88

; IROTData

irda_QueryInterface		equ	0
irda_AddRef		equ	4
irda_Release		equ	8
irda_GetComparisonData	equ	12

; IEnumString

iest_QueryInterface		equ	0
iest_AddRef		equ	4
iest_Release		equ	8
iest_Next		equ	12
iest_Skip		equ	16
iest_Reset		equ	20
iest_Clone		equ	24

; ISequentialStream

isst_QueryInterface		equ	0
isst_AddRef		equ	4
isst_Release		equ	8
isst_Read		equ	12
isst_Write		equ	16

;STATSTG		struc
; stg_pwcsName		dd	?
; stg_type		dd	?
; stg_cbSize		dd	?, ?
; stg_mtime		FILETIME	<?>
; stg_ctime		FILETIME	<?>
; stg_atime		FILETIME	<?>
; stg_grfMode		dd	?
; stg_grfLocksSupported	dd	?
; stg_clsid:		CLSID	<?>
; stg_grfStateBits		dd	?
; stg_reserved		dd	?
;STATSTG		ends

STGTY_STORAGE		= 1
STGTY_STREAM		= 2
STGTY_LOCKBYTES	= 3
STGTY_PROPERTY		= 4

STREAM_SEEK_SET	= 0
STREAM_SEEK_CUR	= 1
STREAM_SEEK_END	= 2

LOCK_WRITE		= 1
LOCK_EXCLUSIVE		= 2
LOCK_ONLYONCE		= 4

; IStream

istr_QueryInterface		equ	0
istr_AddRef		equ	4
istr_Release		equ	8
istr_Read		equ	12
istr_Write		equ	16
istr_Seek		equ	20
istr_SetSize		equ	24
istr_CopyTo		equ	28
istr_Commit		equ	32
istr_Revert		equ	36
istr_LockRegion		equ	40
istr_UnlockRegion		equ	44
istr_Stat		equ	48
istr_Clone		equ	52

; IEnumSTATSTG

iens_QueryInterface		equ	0
iens_AddRef		equ	4
iens_Release		equ	8
iens_Next		equ	12
iens_Skip		equ	16
iens_Reset		equ	20
iens_Clone		equ	24

RemSNB	struc
 rsnb_ulCntStr	dd	?
 rsnb_ulCntChar	dd	?
 rsnb_rgString	dw	?	;; OLECHAR[1]
RemSNB	ends

;IStorage

isto_QueryInterface		equ	0
isto_AddRef		equ	4
isto_Release		equ	8
isto_CreateStream		equ	12
isto_OpenStream		equ	16
isto_CreateStorage		equ	20
isto_OpenStorage		equ	24
isto_CopyTo		equ	28
isto_MoveElementTo		equ	32
isto_Commit		equ	36
isto_Revert		equ	40
isto_EnumElements		equ	44
isto_DestroyElement		equ	48
isto_RenameElement		equ	52
isto_SetElementTimes		equ	56
isto_SetClass		equ	60
isto_SetStateBits		equ	64
isto_Stat		equ	68

IPersistFile	STRUC
 QueryInterface	dq	?
 AddRef		dq	?
 Release	dq	?
 GetClassID	dq	?
 IsDirty	dq	?
 Load	dq	?
 Save	dq	?
 SaveCompleted	dq	?
 GetCurFile	dq	?
IPersistFile	ENDS

; IPersistStorage

ipst_QueryInterface		equ	0
ipst_AddRef		equ	4
ipst_Release		equ	8
ipst_GetClassID		equ	12
ipst_IsDirty		equ	16
ipst_InitNew		equ	20
ipst_Load		equ	24
ipst_Save		equ	28
ipst_SaveCompleted		equ	32
ipst_HandsOffStorage		equ	36

; ILockBytes

ilob_QueryInterface		equ	0
ilob_AddRef		equ	4
ilob_Release		equ	8
ilob_ReadAt		equ	12
ilob_WriteAt		equ	16
ilob_Flush		equ	20
ilob_SetSize		equ	24
ilob_LockRegion		equ	28
ilob_UnlockRegion		equ	32
ilob_Stat		equ	36

DVTARGETDEVICE		struc
 dvtd_tdSize		dd	?
 dvtd_tdDriverNameOffset	dw	?
 dvtd_tdDeviceNameOffset	dw	?
 dvtd_tdPortNameOffset	dw	?
 dvtd_tdExtDevmodeOffset	dw	?
 dvtd_tdData		db	?, ?
DVTARGETDEVICE		ends

FORMATETC		struc
 fetc_cfFormat		dd	?
 fetc_ptd		dd	?
 fetc_dwAspect		dd	?
 fetc_lindex		dd	?
 fetc_tymed		dd	?
FORMATETC		ends

; IEnumFORMATETC

iefe_QueryInterface		equ	0
iefe_AddRef		equ	4
iefe_Release		equ	8
iefe_Next		equ	12
iefe_Skip		equ	16
iefe_Reset		equ	20
iefe_Clone		equ	24

ADVF_NODATA		= 1
ADVF_PRIMEFIRST		= 2
ADVF_ONLYONCE		= 4
ADVF_DATAONSTOP	= 64

ADVFCACHE_NOHANDLER	= 8
ADVFCACHE_FORCEBUILTIN	= 16
ADVFCACHE_ONSAVE	= 32

comment #
STATDATA	struc
 std_formatetc	FORMATETC	<?>
 std_advf	dd	?
 std_pAdvSink	dd	?
 std_dwConnection	dd	?
STATDATA	ends
-#

; IEnumSTATDATA

iesd_QueryInterface		equ	0
iesd_AddRef		equ	4
iesd_Release		equ	8
iesd_Next		equ	12
iesd_Skip		equ	16
iesd_Reset		equ	20
iesd_Clone		equ	24

; IRootStorage

irst_QueryInterface		equ	0
irst_AddRef		equ	4
irst_Release		equ	8
irst_SwitchToFile		equ	12

TYMED_HGLOBAL	= 1
TYMED_FILE	= 2
TYMED_ISTREAM	= 4
TYMED_ISTORAGE	= 8
TYMED_GDI	= 16
TYMED_MFPICT	= 32
TYMED_ENHMF	= 64
TYMED_NULL	= 0

RemSTGMEDIUM		struc
 rsm_tymed		dd	?
 rsm_dwHandleType	dd	?
 rsm_pData		dd	?
 rsm_pUnkForRelease	dd	?
 rsm_cbData		dd	?
 rsm_data		db	?, ?
RemSTGMEDIUM		ends

STGMEDIUM		struc
 tsm_tymed		dd	?
 tsm_hBitmap		equ	tsm_pstg
 tsm_hMetaFilePict		equ	tsm_pstg
 tsm_hEnhMetaFile		equ	tsm_pstg
 tsm_hGlobal		equ	tsm_pstg
 tsm_lpszFileName		equ	tsm_pstg
 tsm_pstm		equ	tsm_pstg
 tsm_pstg		dd	?
 tsm_pUnkForRelease	dd	?
STGMEDIUM		ends

;; skipped some strange structures

; IAdviseSink

iads_QueryInterface		equ	0
iads_AddRef		equ	4
iads_Release		equ	8
iads_OnDataChange		equ	12
iads_OnViewChange		equ	16
iads_OnRename		equ	20
iads_OnSave		equ	24
iads_OnClose		equ	28

; IAdviseSink2

ias2_QueryInterface		equ	0
ias2_AddRef		equ	4
ias2_Release		equ	8
ias2_OnDataChange		equ	12
ias2_OnViewChange		equ	16
ias2_OnRename		equ	20
ias2_OnSave		equ	24
ias2_OnClose		equ	28
ias2_OnLinkSrcChange		equ	32

DATADIR_GET	= 1
DATADIR_SET	= 2

; IDataObject

idao_QueryInterface		equ	0
idao_AddRef		equ	4
idao_Release		equ	8
idao_GetData		equ	12
idao_GetDataHere		equ	16
idao_QueryGetData		equ	20
idao_GetCanonicalFormatEtc	equ	24
idao_SetData		equ	28
idao_EnumFormatEtc		equ	32
idao_DAdvise		equ	36
idao_DUnadvise		equ	40
idao_EnumDAdvise		equ	44

; IDataAdviseHolder

idah_QueryInterface		equ	0
idah_AddRef		equ	4
idah_Release		equ	8
idah_Advise		equ	12
idah_Unadvise		equ	16
idah_EnumAdvise		equ	20
idah_SendOnDataChange	equ	24

CALLTYPE_TOPLEVEL	= 1
CALLTYPE_NESTED		= 2
CALLTYPE_ASYNC		= 3
CALLTYPE_TOPLEVEL_CALLPENDING	= 4
CALLTYPE_ASYNC_CALLPENDING	= 5

SERVERCALL_ISHANDLED	= 0
SERVERCALL_REJECTED	= 1
SERVERCALL_RETRYLATER	= 2

PENDINGTYPE_TOPLEVEL	= 1
PENDINGTYPE_NESTED	= 2

PENDINGMSG_CANCELCALL	= 0
PENDINGMSG_WAITNOPROCESS	= 1
PENDINGMSG_WAITDEFPROCESS	= 2

;INTERFACEINFO		struc
; ifi_pUnk		dd	?
; ifi_iid		GUID	<?>
; ifi_wMethod		dw	?
;INTERFACEINFO		ends

; IMessageFilter

imfi_QueryInterface		equ	0
imfi_AddRef		equ	4
imfi_Release		equ	8
imfi_HandleInComingCall		equ	12
imfi_RetryRejectedCall		equ	16
imfi_MessagePending		equ	20

comment #
RPCOLEMESSAGE		struc
void __RPC_FAR *reserved1	dd	?
RPCOLEDATAREP dataRepresentation;
void __RPC_FAR *Buffer	dd	?
ULONG cbBuffer	dd	?
ULONG iMethod	dd	?
void __RPC_FAR *reserved2[ 5 ];
ULONG rpcFlags;
RPCOLEMESSAGE;
-#

; IRpcChannelBuffer

ircb_QueryInterface		equ	0
ircb_AddRef		equ	4
ircb_Release		equ	8
ircb_GetBuffer		equ	12
ircb_SendReceive		equ	16
ircb_FreeBuffer		equ	20
ircb_GetDestCtx		equ	24
ircb_IsConnected		equ	28

; IRpcProxyBuffer

irpb_QueryInterface		equ	0
irpb_AddRef		equ	4
irpb_Release		equ	8
irpb_Connect		equ	12
irpb_Disconnect		equ	16

; IRpcStubBuffer

irsb_QueryInterface		equ	0
irsb_AddRef		equ	4
irsb_Release		equ	8
irsb_Connect		equ	12
irsb_Disconnect		equ	16
irsb_Invoke		equ	20
irsb_IsIIDSupported		equ	24
irsb_CountRefs		equ	28
irsb_DebugServerQueryInterface	equ	32
irsb_DebugServerRelease	equ	36

; IPSFactoryBuffer

ipfb_QueryInterface		equ	0
ipfb_AddRef		equ	4
ipfb_Release		equ	8
ipfb_CreateProxy		equ	12
ipfb_CreateStub		equ	16

; IChannelHook

ichh_QueryInterface		equ	0
ichh_AddRef		equ	4
ichh_Release		equ	8
ichh_ClientGetSize		equ	12
ichh_ClientFillBuffer		equ	16
ichh_ClientNotify		equ	20
ichh_ServerNotify		equ	24
ichh_ServerGetSize		equ	28
ichh_ServerFillBuffer		equ	32

; Flags for IPropertySetStorage::Create

PROPSETFLAG_DEFAULT	= 0
PROPSETFLAG_NONSIMPLE	= 1
PROPSETFLAG_ANSI	= 2

comment #
typedef structtagCAUB
{
ULONG cElems;
/* [size_is] */ unsigned char __RPC_FAR *pElems;
}	CAUB;

typedef structtagCAI
{
ULONG cElems;
/* [size_is] */ short __RPC_FAR *pElems;
}	CAI;

typedef structtagCAUI
{
ULONG cElems;
/* [size_is] */ USHORT __RPC_FAR *pElems;
}	CAUI;

typedef structtagCAL
{
ULONG cElems;
/* [size_is] */ long __RPC_FAR *pElems;
}	CAL;

typedef structtagCAUL
{
ULONG cElems;
/* [size_is] */ ULONG __RPC_FAR *pElems;
}	CAUL;

typedef structtagCAFLT
{
ULONG cElems;
/* [size_is] */ float __RPC_FAR *pElems;
}	CAFLT;

typedef structtagCADBL
{
ULONG cElems;
/* [size_is] */ double __RPC_FAR *pElems;
}	CADBL;

typedef structtagCACY
{
ULONG cElems;
/* [size_is] */ CY __RPC_FAR *pElems;
}	CACY;

typedef structtagCADATE
{
ULONG cElems;
/* [size_is] */ DATE __RPC_FAR *pElems;
}	CADATE;

typedef structtagCABSTR
{
ULONG cElems;
/* [size_is] */ BSTR __RPC_FAR *pElems;
}	CABSTR;

typedef structtagCABOOL
{
ULONG cElems;
/* [size_is] */ VARIANT_BOOL __RPC_FAR *pElems;
}	CABOOL;

typedef structtagCASCODE
{
ULONG cElems;
/* [size_is] */ SCODE __RPC_FAR *pElems;
}	CASCODE;

typedef structtagCAPROPVARIANT
{
ULONG cElems;
/* [size_is] */ PROPVARIANT __RPC_FAR *pElems;
}	CAPROPVARIANT;

typedef structtagCAH
{
ULONG cElems;
/* [size_is] */ LARGE_INTEGER __RPC_FAR *pElems;
}	CAH;

typedef structtagCAUH
{
ULONG cElems;
/* [size_is] */ ULARGE_INTEGER __RPC_FAR *pElems;
}	CAUH;

typedef structtagCALPSTR
{
ULONG cElems;
/* [size_is] */ LPSTR __RPC_FAR *pElems;
}	CALPSTR;

typedef structtagCALPWSTR
{
ULONG cElems;
/* [size_is] */ LPWSTR __RPC_FAR *pElems;
}	CALPWSTR;

typedef structtagCAFILETIME
{
ULONG cElems;
/* [size_is] */ FILETIME __RPC_FAR *pElems;
}	CAFILETIME;

typedef structtagCACLIPDATA
{
ULONG cElems;
/* [size_is] */ CLIPDATA __RPC_FAR *pElems;
}	CACLIPDATA;

typedef structtagCACLSID
{
ULONG cElems;
/* [size_is] */ CLSID __RPC_FAR *pElems;
}	CACLSID;


structtagPROPVARIANT
{
VARTYPE vt;
WORD wReserved1;
WORD wReserved2;
WORD wReserved3;
/* [switch_is] */ /* [switch_type] */ union 
{
/* [case()] *//* Empty union arm */ 
/* [case()] */ UCHAR bVal;
/* [case()] */ short iVal;
/* [case()] */ USHORT uiVal;
/* [case()] */ VARIANT_BOOL boolVal;
/* [case()] */ long lVal;
/* [case()] */ ULONG ulVal;
/* [case()] */ float fltVal;
/* [case()] */ SCODE scode;
/* [case()] */ LARGE_INTEGER hVal;
/* [case()] */ ULARGE_INTEGER uhVal;
/* [case()] */ double dblVal;
/* [case()] */ CY cyVal;
/* [case()] */ DATE date;
/* [case()] */ FILETIME filetime;
/* [case()] */ CLSID __RPC_FAR *puuid;
/* [case()] */ BLOB blob;
/* [case()] */ CLIPDATA __RPC_FAR *pclipdata;
/* [case()] */ IStream __RPC_FAR *pStream;
/* [case()] */ IStorage __RPC_FAR *pStorage;
/* [case()] */ BSTR bstrVal;
/* [case()] */ LPSTR pszVal;
/* [case()] */ LPWSTR pwszVal;
/* [case()] */ CAUB caub;
/* [case()] */ CAI cai;
/* [case()] */ CAUI caui;
/* [case()] */ CABOOL cabool;
/* [case()] */ CAL cal;
/* [case()] */ CAUL caul;
/* [case()] */ CAFLT caflt;
/* [case()] */ CASCODE cascode;
/* [case()] */ CAH cah;
/* [case()] */ CAUH cauh;
/* [case()] */ CADBL cadbl;
/* [case()] */ CACY cacy;
/* [case()] */ CADATE cadate;
/* [case()] */ CAFILETIME cafiletime;
/* [case()] */ CACLSID cauuid;
/* [case()] */ CACLIPDATA caclipdata;
/* [case()] */ CABSTR cabstr;
/* [case()] */ CALPSTR calpstr;
/* [case()] */ CALPWSTR calpwstr;
/* [case()] */ CAPROPVARIANT capropvar;
}	;
};
;tagPROPVARIANT __RPC_FAR *LPPROPVARIANT;
-#

; Reserved global Property IDs

PID_DICTIONARY		equ	0
PID_CODEPAGE		equ	1
PID_FIRST_USABLE		equ	2
PID_FIRST_NAME_DEFAULT	equ	0fffh
PID_LOCALE		equ	80000000h
PID_MODIFY_TIME		equ	80000001h
PID_SECURITY		equ	80000002h
PID_ILLEGAL		equ	0ffffffffh

; Property IDs for the SummaryInformation Property Set

PIDSI_TITLE		equ	00000002h ; VT_LPSTR
PIDSI_SUBJECT		equ	00000003h ; VT_LPSTR
PIDSI_AUTHOR		equ	00000004h ; VT_LPSTR
PIDSI_KEYWORDS		equ	00000005h ; VT_LPSTR
PIDSI_COMENTS		equ	00000006h ; VT_LPSTR
PIDSI_TEMPLATE		equ	00000007h ; VT_LPSTR
PIDSI_LASTAUTHOR	equ	00000008h ; VT_LPSTR
PIDSI_REVNUMBER		equ	00000009h ; VT_LPSTR
PIDSI_EDITTIME		equ	0000000ah ; VT_FILETIME (UTC)
PIDSI_LASTPRINTED	equ	0000000bh ; VT_FILETIME (UTC)
PIDSI_CREATE_DTM	equ	0000000ch ; VT_FILETIME (UTC)
PIDSI_LASTSAVE_DTM	equ	0000000dh ; VT_FILETIME (UTC)
PIDSI_PAGECOUNT		equ	0000000eh ; VT_I4
PIDSI_WORDCOUNT	equ	0000000fh ; VT_I4
PIDSI_CHARCOUNT		equ	00000010h ; VT_I4
PIDSI_THUMBNAIL		equ	00000011h ; VT_CF
PIDSI_APPNAME		equ	00000012h ; VT_LPSTR
PIDSI_DOC_SECURITY	equ	00000013h ; VT_I4

PRSPEC_INVALID		equ	0ffffffffh
PRSPEC_LPWSTR		equ	0
PRSPEC_PROPID		equ	1

comment #
PROPSPEC		struc
{
ULONG ulKind;
/* [switch_is] */ /* [switch_type] */ union 
{
/* [case()] */ PROPID propid;
/* [case()] */ LPOLESTR lpwstr;
/* [default] *//* Empty union arm */ 
}	;
PROPSPEC		ends

typedef structtagSTATPROPSTG
{
LPOLESTR lpwstrName;
PROPID propid;
VARTYPE vt;
}	STATPROPSTG;

typedef structtagSTATPROPSETSTG
{
FMTID fmtid;
CLSID clsid;
DWORD grfFlags;
FILETIME mtime;
FILETIME ctime;
FILETIME atime;
DWORD dwOSVersion;
}	STATPROPSETSTG;
-#


; IPropertyStorage

iprs_QueryInterface		equ	0
iprs_AddRef		equ	4
iprs_Release		equ	8
iprs_ReadMultiple		equ	12
iprs_WriteMultiple		equ	16
iprs_DeleteMultiple		equ	20
iprs_ReadPropertyNames	equ	24
iprs_WritePropertyNames	equ	28
iprs_DeletePropertyNames	equ	32
iprs_Commit		equ	36
iprs_Revert		equ	40
iprs_Enum		equ	44
iprs_SetTimes		equ	48
iprs_SetClass		equ	52
iprs_Stat		equ	56

; IPropertySetStorage

ipss_QueryInterface		equ	0
ipss_AddRef		equ	4
ipss_Release		equ	8
ipss_Create		equ	12
ipss_Open		equ	16
ipss_Delete		equ	20
ipss_Enum		equ	24

; IEnumSTATPROPSTG

iesp_QueryInterface		equ	0
iesp_AddRef		equ	4
iesp_Release		equ	8
iesp_Next		equ	12
iesp_Skip		equ	16
iesp_Reset		equ	20
iesp_Clone		equ	24

; IEnumSTATPROPSETSTG

iess_QueryInterface		equ	0
iess_AddRef		equ	4
iess_Release		equ	8
iess_Next		equ	12
iess_Skip		equ	16
iess_Reset		equ	20
iess_Clone		equ	24

comment #
SOLE_AUTHENTICATION_SERVICE	struc
DWORD dwAuthnSvc;
DWORD dwAuthzSvc;
OLECHAR __RPC_FAR *pPrincipalName;
HRESULT hr;
SOLE_AUTHENTICATION_SERVICE	ends
-#

EOAC_NONE		= 0
EOAC_MUTUAL_AUTH	= 1
EOAC_SECURE_REFS	= 2
EOAC_ACCESS_CONTROL	= 4

; IClientSecurity

icls_QueryInterface		equ	0
icls_AddRef		equ	4
icls_Release		equ	8
icls_QueryBlanket		equ	12
icls_SetBlanket		equ	16
icls_CopyProxy		equ	20

; IServerSecurity

isse_QueryInterface		equ	0
isse_AddRef		equ	4
isse_Release		equ	8
isse_QueryBlanket		equ	12
isse_ImpersonateClient		equ	16
isse_RevertToSelf		equ	20
isse_IsImpersonating		equ	24

; IClassActivator

icla_QueryInterface		equ	0
icla_AddRef		equ	4
icla_Release		equ	8
icla_GetClassObject		equ	12

; IFillLockBytes

iflb_QueryInterface		equ	0
iflb_AddRef		equ	4
iflb_Release		equ	8
iflb_FillAppend		equ	12
iflb_FillAt		equ	16
iflb_SetFillSize		equ	20
iflb_Terminate		equ	24

; IProgressNotify

iprn_QueryInterface		equ	0
iprn_AddRef		equ	4
iprn_Release		equ	8
iprn_OnProgress		equ	12

comment #
typedef structtagStorageLayout
{
DWORD LayoutType;
OLECHAR __RPC_FAR *pwcsElementName;
LARGE_INTEGER cOffset;
LARGE_INTEGER cBytes;
}	StorageLayout;
-#

; ILayoutStorage

ilas_QueryInterface		equ	0
ilas_AddRef		equ	4
ilas_Release		equ	8
ilas_LayoutScript		equ	12
ilas_BeginMonitor		equ	16
ilas_EndMonitor		equ	20
ilas_ReLayoutDocfile		equ	24
ilas_ReLayoutDocfileOnILockBytes	equ	28
