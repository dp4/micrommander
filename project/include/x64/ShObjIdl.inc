; interface IPersistFolder
; "000214EA-0000-0000-C000-000000000046"

iperfol_QueryInterface	equ	0
iperfol_AddRef		equ	4
iperfol_Release		equ	8
iperfol_GetClassID		equ	12
iperfol_Initialize		equ	16

; interface IPersistFolder2
; "1AC3D9F0-175C-11d1-95BE-00609797EA4F"

iperfol2_QueryInterface	equ	0
iperfol2_AddRef		equ	4
iperfol2_Release		equ	8
iperfol2_GetClassID		equ	12
iperfol2_Initialize		equ	16
iperfol2_GetCurFolder	equ	20

; interface IPersistIDList
; "1079acfc-29bd-11d3-8e0d-00c04f6837d5"

iperidl_QueryInterface	equ	0
iperidl_AddRef		equ	4
iperidl_Release		equ	8
iperidl_GetClassID		equ	12
iperidl_SetIDList		equ	16
iperidl_GetIDList		equ	20

; interface IEnumIDList
; "000214F2-0000-0000-C000-000000000046"

ienidl_QueryInterface	equ	0
ienidl_AddRef		equ	4
ienidl_Release		equ	8
ienidl_Next		equ	12
ienidl_Skip		equ	16
ienidl_Reset		equ	20
ienidl_Clone		equ	24

SHGDN_NORMAL		equ	0000h		; default (display purpose)
SHGDN_INFOLDER		equ	0001h		; displayed under a folder (relative)
SHGDN_FOREDITING	equ	1000h		; for in-place editing
SHGDN_FORADDRESSBAR	equ	4000h		; UI friendly parsing name (remove ugly stuff)
SHGDN_FORPARSING	equ	8000h		; parsing name for ParseDisplayName()

SHCONTF_FOLDERS	equ	0020h		; only want folders enumerated (SFGAO_FOLDER)
SHCONTF_NONFOLDERS	equ	0040h		; include non folders
SHCONTF_INCLUDEHIDDEN	equ	0080h		; show items normally hidden
SHCONTF_INIT_ON_FIRST_NEXT	equ	0100h		; allow EnumObject() to return before validating enum
SHCONTF_NETPRINTERSRCH	equ	0200h		; hint that client is looking for printers
SHCONTF_SHAREABLE	equ	0400h		; hint that client is looking sharable resources (remote shares)
SHCONTF_STORAGE	equ	0800h		; include all items with accessible storage and their ancestors

SHCIDS_ALLFIELDS		equ	80000000h
SHCIDS_CANONICALONLY	equ	10000000h
SHCIDS_BITMASK		equ	0FFFF0000h
SHCIDS_COLUMNMASK 	equ	0000FFFFh
SFGAO_CANCOPY		equ	DROPEFFECT_COPY	; Objects can be copied (1)
SFGAO_CANMOVE		equ	DROPEFFECT_MOVE	; Objects can be moved (2)
SFGAO_CANLINK		equ	DROPEFFECT_LINK		; Objects can be linked (4)
SFGAO_STORAGE 		equ	00000008h		; supports BindToObject(IID_IStorage)
SFGAO_CANRENAME 	equ	00000010h		; Objects can be renamed
SFGAO_CANDELETE 	equ	00000020h		; Objects can be deleted
SFGAO_HASPROPSHEET	equ	00000040h		; Objects have property sheets
SFGAO_DROPTARGET	equ	00000100h		; Objects are drop target
SFGAO_CAPABILITYMASK	equ	00000177h
SFGAO_ENCRYPTED 	equ	00002000h		; object is encrypted (use alt color)
SFGAO_ISSLOW		equ	00004000h		; 'slow' object
SFGAO_GHOSTED 		equ	00008000h		; ghosted icon
SFGAO_LINK		equ	00010000h		; Shortcut (link)
SFGAO_SHARE 		equ	00020000h		; shared
SFGAO_READONLY		equ	00040000h		; read-only
SFGAO_HIDDEN		equ	00080000h		; hidden object
SFGAO_DISPLAYATTRMASK 	equ	000FC000h
SFGAO_FILESYSANCESTOR 	equ	10000000h		; may contain children with SFGAO_FILESYSTEM
SFGAO_FOLDER		equ	20000000h		; support BindToObject(IID_IShellFolder)
SFGAO_FILESYSTEM	equ	40000000h		; is a win32 file system object (file/folder/root)
SFGAO_HASSUBFOLDER	equ	80000000h		; may contain children with SFGAO_FOLDER
SFGAO_CONTENTSMASK	equ	80000000h
SFGAO_VALIDATE		equ	01000000h		; invalidate cached information
SFGAO_REMOVABLE 	equ	02000000h		; is this removeable media?
SFGAO_COMPRESSED	equ	04000000h		; Object is compressed (use alt color)
SFGAO_BROWSABLE 	equ	08000000h		; supports IShellFolder, but only implements CreateViewObject() (non-folder view)
SFGAO_NONENUMERATED 	equ	00100000h		; is a non-enumerated object
SFGAO_NEWCONTENT	equ	00200000h		; should show bold in explorer tree
SFGAO_CANMONIKER	equ	00400000h		; defunct
SFGAO_HASSTORAGE	equ	00400000h		; defunct
SFGAO_STREAM		equ	00400000h		; supports BindToObject(IID_IStream)
SFGAO_STORAGEANCESTOR 	equ	00800000h		; may contain children with SFGAO_STORAGE or SFGAO_STREAM
SFGAO_STORAGECAPMASK	equ	70C50008h		; for determining storage capabilities, ie for open/save semantics

;STR_SKIP_BINDING_CLSID		textequ	"Skip Binding CLSID"
;STR_PARSE_PREFER_FOLDER_BROWSING	textequ	"Parse Prefer Folder Browsing"
;STR_DONT_PARSE_RELATIVE		textequ	"Don't Parse Relative"
;STR_PARSE_TRANSLATE_ALIASES		textequ	"Parse Translate Aliases"

; interface IShellFolder
; "000214E6-0000-0000-C000-000000000046")

ishfol_QueryInterface	equ	0
ishfol_AddRef		equ	4
ishfol_Release		equ	8
ishfol_ParseDisplayName	equ	12
ishfol_EnumObjects	equ	16
ishfol_BindToObject	equ	20
ishfol_BindToStorage	equ	24
ishfol_CompareIDs		equ	28
ishfol_CreateView		equ	32
ishfol_ObjectGetAttributesOf	equ	36
ishfol_GetUIObjectOf	equ	40
ishfol_GetDisplayNameOf	equ	44
ishfol_SetNameOf		equ	48

;;EXTRASEARCH		struc
;; exse_guidSearch		GUID	<?>
;; exse_wszFriendlyName	dw	80 dup(?)
 ;;exse_wszUrl		dw	2084 dup(?)
;;EXTRASEARCH		ends

; interface IEnumExtraSearch
; "0E700BE1-9DB6-11d1-A1CE-00C04FD75D13")

ienexse_QueryInterface	equ	0
ienexse_AddRef		equ	4
ienexse_Release		equ	8
ienexse_Next		equ	12
ienexse_Skip		equ	16
ienexse_Reset		equ	20
ienexse_Clone		equ	24

SHCOLSTATE_TYPE_STR	equ	1
SHCOLSTATE_TYPE_INT	equ	2
SHCOLSTATE_TYPE_DATE	equ	3
SHCOLSTATE_TYPEMASK	equ	0fh
SHCOLSTATE_ONBYDEFAULT	equ	10h
SHCOLSTATE_SLOW	equ	20h
SHCOLSTATE_EXTENDED	equ	40h
SHCOLSTATE_SECONDARYUI	equ	80h
SHCOLSTATE_HIDDEN	equ	100h
SHCOLSTATE_PREFER_VARCMP	equ	200h

;SHCOLUMNID		struc
; shcolid_fmtid		GUID	<?>
; shcolid_pid		dd	?
;SHCOLUMNID		ends

; interface IShellFolder2
; "93F2F68C-1D1B-11d3-A30E-00C04F79ABD1")

ishfol2_QueryInterface	equ	0
ishfol2_AddRef		equ	4
ishfol2_Release		equ	8
ishfol2_ParseDisplayName	equ	12
ishfol2_EnumObjects	equ	16
ishfol2_BindToObject	equ	20
ishfol2_BindToStorage	equ	24
ishfol2_CompareIDs	equ	28
ishfol2_CreateViewObject	equ	32
ishfol2_GetAttributesOf	equ	36
ishfol2_GetUIObjectOf	equ	40
ishfol2_GetDisplayNameOf	equ	44
ishfol2_SetNameOf		equ	48
ishfol2_GetDefault		equ	52
ishfol2_SearchGUID	equ	56
ishfol2_EnumSearches	equ	60
ishfol2_GetDefaultColumn	equ	64
ishfol2_GetDefaultColumnState	equ	68
ishfol2_GetDetailsEx	equ	72
ishfol2_GetDetailsOf	equ	76
ishfol2_MapColumnToSCID	equ	80

FWF_AUTOARRANGE	equ	1h
FWF_ABBREVIATEDNAMES	equ	2h
FWF_SNAPTOGRID		equ	4h
FWF_OWNERDATA		equ	8h
FWF_BESTFITWINDOW	equ	10h
FWF_DESKTOP		equ	20h
FWF_SINGLESEL		equ	40h
FWF_NOSUBFOLDERS	equ	80h
FWF_TRANSPARENT	equ	100h
FWF_NOCLIENTEDGE	equ	200h
FWF_NOSCROLL		equ	400h
FWF_ALIGNLEFT		equ	800h
FWF_NOICONS		equ	1000h
FWF_SHOWSELALWAYS	equ	2000h
FWF_NOVISIBLE		equ	4000h
FWF_SINGLECLICKACTIVATE	equ	8000h
FWF_NOWEBVIEW		equ	10000h
FWF_HIDEFILENAMES	equ	20000h
FWF_CHECKSELECT	equ	40000h

FVM_FIRST		equ	1
FVM_ICON		equ	1
FVM_SMALLICON		equ	2
FVM_LIST		equ	3
FVM_DETAILS		equ	4
FVM_THUMBNAIL		equ	5
FVM_TILE		equ	6
FVM_THUMBSTRIP		equ	7
FVM_LAST		equ	7

FOLDERSETTINGS		struc
 folset_ViewMode		dd	?
 folset_fFlags		dd	?
FOLDERSETTINGS		ends

SVSI_DESELECT 		equ	00000000h
SVSI_SELECT 		equ	00000001h
SVSI_EDIT 		equ	00000003h	; includes select
SVSI_DESELECTOTHERS 	equ	00000004h
SVSI_ENSUREVISIBLE	equ	00000008h
SVSI_FOCUSED		equ	00000010h
SVSI_TRANSLATEPT	equ	00000020h
SVSI_SELECTIONMARK	equ	00000040h
SVSI_POSITIONITEM 	equ	00000080h
SVSI_CHECK		equ	00000100h
SVSI_NOSTATECHANGE	equ	80000000h

SVGIO_BACKGROUND	equ	0
SVGIO_SELECTION		equ	1
SVGIO_ALLVIEW		equ	2
SVGIO_CHECKED		equ	3
SVGIO_TYPE_MASK	equ	15
SVGIO_FLAG_VIEWORDER	equ	80000000h

SVUIA_DEACTIVATE	equ	0
SVUIA_ACTIVATE_NOFOCUS	equ	1
SVUIA_ACTIVATE_FOCUS	equ	2
SVUIA_INPLACEACTIVATE	equ	3

; interface IShellView
; "000214E3-0000-0000-C000-000000000046")

ishvi_QueryInterface	equ	0
ishvi_AddRef		equ	4
ishvi_Release		equ	8
ishvi_GetWindow		equ	12
ishvi_ContextSensitiveHelp	equ	16
ishvi_TranslateAccelerator	equ	20
ishvi_EnableModelessUI	equ	24
ishvi_Activate		equ	28
ishvi_Refresh		equ	32
ishvi_CreateViewWindow	equ	36
ishvi_DestroyViewWindow	equ	40
ishvi_GetCurrentInfo	equ	44
ishvi_AddPropertySheetPages	equ	48
ishvi_SaveViewState	equ	52
ishvi_SelectItem		equ	56
ishvi_GetItemObject	equ	60

SV2GV_CURRENTVIEW 	equ	-1
SV2GV_DEFAULTVIEW 	equ	-2

SV2CVW2_PARAMS		struc
 sv2cvw2_cbSize		dd	?
 sv2cvw2_psvPrev		dd	?
 sv2cvw2_pfs		dd	?
 sv2cvw2_psbOwner	dd	?
 sv2cvw2_prcView		dd	?
 sv2cvw2_pvid		dd	?
 sv2cvw2_hwndView	dd	?
SV2CVW2_PARAMS		ends

; interface IShellView2
; "88E39E80-3578-11CF-AE69-08002B2E1262")

ishvi2_QueryInterface	equ	0
ishvi2_AddRef		equ	4
ishvi2_Release		equ	8
ishvi2_GetWindow		equ	12
ishvi2_ContextSensitiveHelp	equ	16
ishvi2_TranslateAccelerator	equ	20
ishvi2_EnableModelessUI	equ	24
ishvi2_Activate		equ	28
ishvi2_Refresh		equ	32
ishvi2_CreateViewWindow	equ	36
ishvi2_DestroyViewWindow	equ	40
ishvi2_GetCurrentInfo	equ	44
ishvi2_AddPropertySheetPages	equ	48
ishvi2_SaveViewState	equ	52
ishvi2_SelectItem		equ	56
ishvi2_GetItemObject	equ	60
ishvi2_GetView		equ	64
ishvi2_CreateViewWindow2	equ	68
ishvi2_HandleRename	equ	72
ishvi2_SelectAndPositionItem	equ	76

; interface IFolderView
; "cde725b0-ccc9-4519-917e-325d72fab4ce")

ifovi_QueryInterface	equ	0
ifovi_AddRef		equ	4
ifovi_Release		equ	8
ifovi_GetCurrentViewMode	equ	12
ifovi_SetCurrentViewMode	equ	16
ifovi_GetFolderItem	equ	20
ifovi_ItemCount		equ	24
ifovi_Items		equ	28
ifovi_GetSelection		equ	32
ifovi_MarkedItem		equ	36
ifovi_GetFocusedItem	equ	40
ifovi_GetItemPosition	equ	44
ifovi_GetSpacing		equ	48
ifovi_GetDefaultSpacing	equ	52
ifovi_GetAutoArrange	equ	56
ifovi_SelectItem		equ	60
ifovi_SelectAndPositionItems	equ	64

; interface IFolderFilterSite
; "C0A651F5-B48B-11d2-B5ED-006097C686F6")

ifofisi_QueryInterface	equ	0
ifofisi_AddRef		equ	4
ifofisi_Release		equ	8
ifofisi_SetFilter		equ	12

; interface IFolderFilter
; "9CC22886-DC8E-11d2-B1D0-00C04F8EEB3E")

ifofi_QueryInterface	equ	0
ifofi_AddRef		equ	4
ifofi_Release		equ	8
ifofi_ShouldShow		equ	12
ifofi_GetEnumFlags		equ	16

SBSP_DEFBROWSER 	equ	0000h
SBSP_SAMEBROWSER	equ	0001h
SBSP_NEWBROWSER 	equ	0002h
SBSP_DEFMODE		equ	0000h
SBSP_OPENMODE 		equ	0010h
SBSP_EXPLOREMODE	equ	0020h
SBSP_HELPMODE 		equ	0040h		; IEUNIX : Help window uses this.
SBSP_NOTRANSFERHIST 	equ	0080h
SBSP_ABSOLUTE 		equ	0000h
SBSP_RELATIVE 		equ	1000h
SBSP_PARENT 		equ	2000h
SBSP_NAVIGATEBACK 	equ	4000h
SBSP_NAVIGATEFORWARD	equ	8000h
SBSP_ALLOW_AUTONAVIGATE 	equ	10000h
SBSP_NOAUTOSELECT 	equ	04000000h
SBSP_WRITENOHISTORY 	equ	08000000h
SBSP_REDIRECT 		equ	40000000h
SBSP_INITIATEDBYHLINKFRAME	equ	80000000h

FCW_STATUS		equ	0001h
FCW_TOOLBAR 		equ	0002h
FCW_TREE		equ	0003h
FCW_INTERNETBAR 	equ	0006h
FCW_PROGRESS		equ	0008h
FCT_MERGE 		equ	0001h
FCT_CONFIGABLE		equ	0002h
FCT_ADDTOEND		equ	0004h

; interface IShellBrowser
; "000214E2-0000-0000-C000-000000000046")

ishbr_QueryInterface	equ	0
ishbr_AddRef		equ	4
ishbr_Release		equ	8
ishbr_GetWindow		equ	12
ishbr_ContextSensitiveHelp	equ	16
ishbr_InsertMenusSB	equ	20
ishbr_SetMenuSB		equ	24
ishbr_RemoveMenusSB	equ	28
ishbr_SetStatusTextSB	equ	32
ishbr_EnableModelessSB	equ	36
ishbr_TranslateAcceleratorSB	equ	40
ishbr_BrowseObject	equ	44
ishbr_GetViewStateStream	equ	48
ishbr_GetControlWindow	equ	52
ishbr_SendControlMsg	equ	56
ishbr_QueryActiveShellView	equ	60
ishbr_OnViewWindowActive	equ	64
ishbr_SetToolbarItems	equ	68

; interface IProfferService
; "cb728b20-f786-11ce-92ad-00aa00a74cd0")

iproser_QueryInterface	equ	0
iproser_AddRef		equ	4
iproser_Release		equ	8
iproser_ProfferService	equ	12
iproser_RevokeService	equ	16

PUIFNF_DEFAULT		equ	0
PUIFNF_MNEMONIC		equ	1

PUIF_DEFAULT		equ	0
PUIF_RIGHTALIGN		equ	1
PUIF_NOLABELININFOTIP	equ	2

PUIFFDF_DEFAULT		equ	0
PUIFFDF_RIGHTTOLEFT	equ	1
PUIFFDF_SHORTFORMAT	equ	2
PUIFFDF_NOTIME		equ	4
PUIFFDF_FRIENDLYDATE	equ	8
PUIFFDF_NOUNITS		equ	10

;interface IPropertyUI
; "757a7d9f-919a-4118-99d7-dbb208c8cc66")

ipropui_QueryInterface	equ	0
ipropui_AddRef		equ	4
ipropui_Release		equ	8
ipropui_ParsePropertyName	equ	12
ipropui_GetCannonicalName	equ	16
ipropui_GetDisplayName	equ	20
ipropui_GetPropertyDescription	equ	24
ipropui_GetDefaultWidth	equ	28
ipropui_GetFlags		equ	32
ipropui_FormatForDisplay	equ	36
ipropui_GetHelpInfo	equ	40

; interface ICategoryProvider
; "9af64809-5864-4c26-a720-c1f78c086ee3")

icatpro_QueryInterface	equ	0
icatpro_AddRef		equ	4
icatpro_Release		equ	8
icatpro_CanCategorizeOnSCID	equ	12
icatpro_GetDefaultCategory	equ	16
icatpro_GetCategoryForSCID	equ	20
icatpro_EnumCategories	equ	24
icatpro_GetCategoryName	equ	28
icatpro_CreateCategory	equ	32

CATINFO_NORMAL		equ	0
CATINFO_COLLAPSED	equ	1
CATINFO_HIDDEN		equ	2

CATSORT_DEFAULT	equ	0
CATSORT_NAME		equ	1

comment #
CATEGORY_INFO	struc
CATEGORYINFO_FLAGS cif;
WCHAR wszName[ 260 ];
CATEGORY_INFO	ends
-#

; interface ICategorizer
; "a3b14589-9174-49a8-89a3-06a1ae2b9ba7")

icateg_QueryInterface	equ	0
icateg_AddRef		equ	4
icateg_Release		equ	8
icateg_GetDescription	equ	12
icateg_GetCategory	equ	16
icateg_GetCategoryInfo	equ	20
icateg_CompareCategory	equ	24

SLR_NO_UI		equ	1
SLR_ANY_MATCH		equ	2
SLR_UPDATE		equ	4
SLR_NOUPDATE		equ	8
SLR_NOSEARCH		equ	10h
SLR_NOTRACK		equ	20h
SLR_NOLINKINFO		equ	40h
SLR_INVOKE_MSI		equ	80h
SLR_NO_UI_WITH_MSG_PUMP	equ	101h

SLGP_SHORTPATH		equ	1
SLGP_UNCPRIORITY	equ	2
SLGP_RAWPATH		equ	4

; interface IShellLinkA
; "000214EE-0000-0000-C000-000000000046")

IShellLink	STRUC
 QueryInterface	dq	?
 AddRef	dq	?
 Release	dq	?
 GetPath	dq	?
 GetIDList	dq	?
 SetIDList	dq	?
 GetDescription	dq	?
 SetDescription	dq	?
 GetWorkingDirectory	dq	?
 SetWorkingDirectory	dq	?
 GetArguments	dq	?
 SetArguments	dq	?
 GetHotkey	dq	?
 SetHotkey	dq	?
 GetShowCmd	dq	?
 SetShowCmd	dq	?
 GetIconLocation	dq	?
 SetIconLocation	dq	?
 SetRelativePath	dq	?
 Resolve	dq	?
 SetPath	dq	?
IShellLink	ENDS

SPINITF_NORMAL		equ	0
SPINITF_MODAL		equ	1
SPINITF_NOMINIMIZE	equ	8

; interface IActionProgressDialog
; "49ff1172-eadc-446d-9285-156453a6431c")

iacprdi_QueryInterface	equ	0
iacprdi_AddRef		equ	4
iacprdi_Release		equ	8
iacprdi_Initialize		equ	12
iacprdi_Stop		equ	16

; interface IHWEventHandler
; "C1FB73D0-EC3A-4ba2-B512-8CDB9187B6D1")

ihwevha_QueryInterface	equ	0
ihwevha_AddRef		equ	4
ihwevha_Release		equ	8
ihwevha_Initialize		equ	12
ihwevha_HandleEvent	equ	16
ihwevha_HandleEventWithContent	equ	20

ARCONTENT_AUTORUNINF 	equ	00000002h
ARCONTENT_AUDIOCD 	equ	00000004h
ARCONTENT_DVDMOVIE	equ	00000008h
ARCONTENT_BLANKCD 	equ	00000010h
ARCONTENT_BLANKDVD	equ	00000020h
ARCONTENT_UNKNOWNCONTENT 	equ	00000040h
ARCONTENT_AUTOPLAYPIX 	equ	00000080h
ARCONTENT_AUTOPLAYMUSIC	equ	00000100h
ARCONTENT_AUTOPLAYVIDEO	equ	00000200h

; interface IQueryCancelAutoPlay
; "DDEFE873-6997-4e68-BE26-39B633ADBE12")

iqucaaupl_QueryInterface	equ	0
iqucaaupl_AddRef		equ	4
iqucaaupl_Release		equ	8
iqucaaupl_AllowAutoPlay	equ	12


SPBEGINF_NORMAL		equ	0
SPBEGINF_AUTOTIME	equ	2,
SPBEGINF_NOPROGRESSBAR	equ	10h
SPBEGINF_MARQUEEPROGRESS	equ	20h

SPACTION_NONE		equ	0
SPACTION_MOVING	equ	SPACTION_NONE + 1
SPACTION_COPYING	equ	SPACTION_MOVING + 1
SPACTION_RECYCLING	equ	SPACTION_COPYING + 1
SPACTION_APPLYINGATTRIBS	equ	SPACTION_RECYCLING + 1
SPACTION_DOWNLOADING	equ	SPACTION_APPLYINGATTRIBS + 1
SPACTION_SEARCHING_INTERNET	equ	SPACTION_DOWNLOADING + 1
SPACTION_CALCULATING	equ	SPACTION_SEARCHING_INTERNET + 1
SPACTION_UPLOADING	equ	SPACTION_CALCULATING + 1
SPACTION_SEARCHING_FILES	equ	SPACTION_UPLOADING + 1

SPTEXT_ACTIONDESCRIPTION	equ	1
SPTEXT_ACTIONDETAIL	equ	SPTEXT_ACTIONDESCRIPTION + 1

; interface IActionProgress
; "49ff1173-eadc-446d-9285-156453a6431c")

iacpro_QueryInterface	equ	0
iacpro_AddRef		equ	4
iacpro_Release		equ	8
iacpro_Begin		equ	12
iacpro_UpdateProgress	equ	16
iacpro_UpdateText		equ	20
iacpro_QueryCancel	equ	24
iacpro_ResetCancel	equ	28
iacpro_End		equ	32

; interface IShellExtInit
; "000214E8-0000-0000-C000-000000000046")

ishexin_QueryInterface	equ	0
ishexin_AddRef		equ	4
ishexin_Release		equ	8
ishexin_Initialize		equ	12

EXPPS_FILETYPES		equ	1

; interface IShellPropSheetExt
; "000214E9-0000-0000-C000-000000000046")

ishprshex_QueryInterface	equ	0
ishprshex_AddRef		equ	4
ishprshex_Release		equ	8
ishprshex_AddPages	equ	12
ishprshex_ReplacePage	equ	16

; interface IRemoteComputer
; "000214FE-0000-0000-C000-000000000046"

iremco_QueryInterface	equ	0
iremco_AddRef		equ	4
iremco_Release		equ	8
iremco_Initialize		equ	12

; interface IQueryContinue
; "7307055c-b24a-486b-9f25-163e597a28a9")

iquco_QueryInterface	equ	0
iquco_AddRef		equ	4
iquco_Release		equ	8
iquco_QueryContinue	equ	12

; interface IUserNotification
; "ba9711ba-5893-4787-a7e1-41277151550b")

iusin_QueryInterface	equ	0
iusin_AddRef		equ	4
iusin_Release		equ	8
iusin_SetBalloonInfo	equ	12
iusin_SetBalloonRetry	equ	16
iusin_SetIconInfo		equ	20
iusin_Show		equ	24
iusin_PlaySound		equ	28

; interface IItemNameLimits
; "1df0d7f1-b267-4d28-8b10-12e23202a5c4")

iitnali_QueryInterface	equ	0
iitnali_AddRef		equ	4
iitnali_Release		equ	8
iitnali_GetValidCharacters	equ	12
iitnali_GetMaxLength	equ	16

SNCF_REFRESHLIST 	equ	1	; refresh the list (eg. from F5 or opening a folder)

; interface INetCrawler
; "49c929ee-a1b7-4c58-b539-e63be392b6f3")

inetcr_QueryInterface	equ	0
inetcr_AddRef		equ	4
inetcr_Release		equ	8
inetcr_Update		equ	12

IEI_PRIORITY_MAX		equ	ITSAT_MAX_PRIORITY
IEI_PRIORITY_MIN		equ	ITSAT_MIN_PRIORITY
IEIT_PRIORITY_NORMAL	equ	ITSAT_DEFAULT_PRIORITY
IEIFLAG_ASYNC 		equ	0001h	;  ask the extractor if it supports ASYNC extract (free threaded)
IEIFLAG_CACHE 		equ	0002h	;  returned from the extractor if it does NOT cache the thumbnail
IEIFLAG_ASPECT		equ	0004h	;  passed to the extractor to beg it to render to the aspect ratio of the supplied rect
IEIFLAG_OFFLINE 		equ	0008h	;  if the extractor shouldn't hit the net to get any content neede for the rendering
IEIFLAG_GLEAM 		equ	0010h	;  does the image have a gleam ? this will be returned if it does
IEIFLAG_SCREEN		equ	0020h	;  render as if for the screen(this is exlusive with IEIFLAG_ASPECT )
IEIFLAG_ORIGSIZE		equ	0040h	;  render to the approx size passed, but crop if neccessary
IEIFLAG_NOSTAMP 	equ	0080h	;  returned from the extractor if it does NOT want an icon stamp on the thumbnail
IEIFLAG_NOBORDER	equ	0100h	;  returned from the extractor if it does NOT want an a border around the thumbnail
IEIFLAG_QUALITY 		equ	0200h	;  passed to the Extract method to indicate that a slower, higher quality image is desired, re-compute the thumbnail
IEIFLAG_REFRESH 		equ	0400h	;  returned from the extractor if it would like to have Refresh Thumbnail available

; interface IExtractImage
; "BB2E617C-0920-11d1-9A0B-00C04FC2D6C1")

iexim_QueryInterface	equ	0
iexim_AddRef		equ	4
iexim_Release		equ	8
iexim_GetLocation		equ	12
iexim_Extract		equ	16

; interface IExtractImage2
; "953BB1EE-93B4-11d1-98A3-00C04FB687DA")

iexim2_QueryInterface	equ	0
iexim2_AddRef		equ	4
iexim2_Release		equ	8
iexim2_GetLocation		equ	12
iexim2_Extract		equ	16
iexim2_GetDateStamp	equ	20


; interface IUserEventTimerCallback
; "e9ead8e6-2a25-410e-9b58-a9fbef1dd1a2"

iusevtica_QueryInterface	equ	0
iusevtica_AddRef		equ	4
iusevtica_Release		equ	8
iusevtica_UserEventTimerProc	equ	12

; interface IUserEventTimer
; "0F504B94-6E42-42E6-99E0-E20FAFE52AB4"

iusevti_QueryInterface	equ	0
iusevti_AddRef		equ	4
iusevti_Release		equ	8
iusevti_SetUserEventTimer	equ	12
iusevti_KillUserEventTimer	equ	16
iusevti_GetUserEventTimerElapsed	equ	20
iusevti_InitTimerTickInterval	equ	24

; interface IDockingWindow
; "012dd920-7b26-11d0-8ca9-00a0c92dbfe8"

idowin_QueryInterface	equ	0
idowin_AddRef		equ	4
idowin_Release		equ	8
idowin_GetWindow		equ	12
idowin_ContextSensitiveHelp	equ	16
idowin_ShowDW		equ	20
idowin_CloseDW		equ	24
idowin_ResizeBorderDW	equ	28

DBIM_MINSIZE		equ	0001h
DBIM_MAXSIZE		equ	0002h
DBIM_INTEGRAL 		equ	0004h
DBIM_ACTUAL 		equ	0008h
DBIM_TITLE		equ	0010h
DBIM_MODEFLAGS		equ	0020h
DBIM_BKCOLOR		equ	0040h

DESKBANDINFO		struc
 dbi_dwMask		dd	?
 dbi_ptMinSize		dd	?, ?
 dbi_ptMaxSize		dd	?, ?
 dbi_ptIntegral		dd	?, ?
 dbi_ptActual		dd	?, ?
 dbi_wszTitle		dw	256 dup(?)
 dbi_dwModeFlags		dd	?
 dbi_crBkgnd		dd	?
DESKBANDINFO		ends

DBIMF_NORMAL		equ	0000h
DBIMF_FIXED 		equ	0001h
DBIMF_FIXEDBMP		equ	0004h	; a fixed background bitmap (if supported)
DBIMF_VARIABLEHEIGHT	equ	0008h
DBIMF_UNDELETEABLE	equ	0010h
DBIMF_DEBOSSED		equ	0020h
DBIMF_BKCOLOR 		equ	0040h
DBIMF_USECHEVRON	equ	0080h
DBIMF_BREAK 		equ	0100h
DBIMF_ADDTOFRONT	equ	0200h
DBIMF_TOPALIGN		equ	0400h

DBIF_VIEWMODE_NORMAL 	equ	0000h
DBIF_VIEWMODE_VERTICAL 	equ	0001h
DBIF_VIEWMODE_FLOATING 	equ	0002h
DBIF_VIEWMODE_TRANSPARENT	equ	0004h

DBID_BANDINFOCHANGED	equ	0
DBID_SHOWONLY		equ	1
DBID_MAXIMIZEBAND	equ	2
DBID_PUSHCHEVRON	equ	3
DBID_DELAYINIT		equ	4
DBID_FINISHINIT		equ	5
DBID_SETWINDOWTHEME	equ	6
DBID_PERMITAUTOHIDE	equ	7

DBPC_SELECTFIRST	equ	-1
DBPC_SELECTLAST		equ	-2

; interface IDeskBand
; "EB0FE172-1A3A-11D0-89B3-00A0C90A90AC")

ideba_QueryInterface	equ	0
ideba_AddRef		equ	4
ideba_Release		equ	8
ideba_GetWindow		equ	12
ideba_ContextSensitiveHelp	equ	16
ideba_ShowDW		equ	20
ideba_CloseDW		equ	24
ideba_ResizeBorderDW	equ	28
ideba_GetBandInfo		equ	32

; interface ITaskbarList
; "56FDF342-FD6D-11d0-958A-006097C9A090")

itabali_QueryInterface	equ	0
itabali_AddRef		equ	4
itabali_Release		equ	8
itabali_HrInit		equ	12
itabali_AddTab		equ	16
itabali_DeleteTab		equ	20
itabali_ActivateTab	equ	24
itabali_SetActiveAlt	equ	28


; interface ITaskbarList2
; "602D4995-B13A-429b-A66E-1935E44F4317"

itabali2_QueryInterface	equ	0
itabali2_AddRef		equ	4
itabali2_Release		equ	8
itabali2_HrInit		equ	12
itabali2_AddTab		equ	16
itabali2_DeleteTab		equ	20
itabali2_ActivateTab	equ	24
itabali2_SetActiveAlt	equ	28
itabali2_MarkFullscreenWindow	equ	32

; interface ICDBurn
; "3d73a659-e5d0-4d42-afc0-5121ba425c8d"

icdbu_QueryInterface	equ	0
icdbu_AddRef		equ	4
icdbu_Release		equ	8
icdbu_GetRecorderDriveLetter	equ	12
icdbu_Burn		equ	16
icdbu_HasRecordableDrive	equ	20

IDD_WIZEXTN_FIRST	equ	5000h
IDD_WIZEXTN_LAST 	equ	5100h

; interface IWizardSite
; "88960f5b-422f-4e7b-8013-73415381c3c3"

iwisi_QueryInterface	equ	0
iwisi_AddRef		equ	4
iwisi_Release		equ	8
iwisi_GetPreviousPage	equ	12
iwisi_GetNextPage		equ	16
iwisi_GetCancelledPage	equ	20

; interface IWizardExtension
; "c02ea696-86cc-491e-9b23-74394a0444a8"

iwizext_QueryInterface	equ	0
iwizext_AddRef		equ	4
iwizext_Release		equ	8
iwizext_AddPages		equ	12
iwizext_GetFirstPage	equ	16
iwizext_GetLastPage	equ	20

; interface IWebWizardExtension
; "0e6b3f66-98d1-48c0-a222-fbde74e2fbc5"

iwewiex_QueryInterface	equ	0
iwewiex_AddRef		equ	4
iwewiex_Release		equ	8
iwewiex_AddPages		equ	12
iwewiex_GetFirstPage	equ	16
iwewiex_GetLastPage	equ	20
iwewiex_SetInitialURL	equ	24
iwewiex_SetErrorURL	equ	28

SHPWHF_NORECOMPRESS 	equ	00000001h		; don't allow/prompt for recompress of streams
SHPWHF_NONETPLACECREATE 	equ	00000002h		; don't create a network place when transfer is complete
SHPWHF_NOFILESELECTOR 	equ	00000004h		; don't show the file selector
SHPWHF_VALIDATEVIAWEBFOLDERS	equ	00010000h		; enable web folders to validate network places (ANP support)


; interface IPublishingWizard
; "aa9198bb-ccec-472d-beed-19a4f6733f7a")

ipuwiz_QueryInterface	equ	0
ipuwiz_AddRef		equ	4
ipuwiz_Release		equ	8
ipuwiz_AddPages		equ	12
ipuwiz_GetFirstPage	equ	16
ipuwiz_GetLastPage	equ	20
ipuwiz_Initialize		equ	24
ipuwiz_GetTransferManifest	equ	28

; interface IFolderViewHost
; "1ea58f02-d55a-411d-b09e-9e65ac21605b"

ifoviho_QueryInterface	equ	0
ifoviho_AddRef		equ	4
ifoviho_Release		equ	8
ifoviho_Initialize		equ	12

ACDD_VISIBLE		equ	0001

; interface IAutoCompleteDropDown
; "3CD141F4-3C6A-11d2-BCAA-00C04FD929DB"

iaucodd_QueryInterface	equ	0
iaucodd_AddRef		equ	4
iaucodd_Release		equ	8
iaucodd_GetDropDownStatus	equ	12
iaucodd_ResetEnumerator	equ	16

PPW_LAUNCHEDBYUSER 	equ	00000001h		; The wizard was launch explicitly by the user, not on demand by the key manager

; interface IModalWindow
; "b4db1657-70d7-485e-8e3e-6fcb5a5c1802"

imowin_QueryInterface	equ	0
imowin_AddRef		equ	4
imowin_Release		equ	8
imowin_Show		equ	12

; interface IPassportWizard
; "a09db586-9180-41ac-9114-460a7f362b76"

ipawiz_QueryInterface	equ	0
ipawiz_AddRef		equ	4
ipawiz_Release		equ	8
ipawiz_Show		equ	12
ipawiz_SetOptions		equ	16

CDBE_RET_DEFAULT	equ	0
CDBE_RET_DONTRUNOTHEREXTS	equ	1
CDBE_RET_STOPWIZARD	equ	2

CDBE_TYPE_MUSIC		equ	1
CDBE_TYPE_DATA		equ	2
CDBE_TYPE_ALL		equ	0ffffffffh

; interface ICDBurnExt
; "2271dcca-74fc-4414-8fb7-c56b05ace2d7"

icdbex_QueryInterface	equ	0
icdbex_AddRef		equ	4
icdbex_Release		equ	8
icdbex_GetSupportedActionTypes	equ	12

; interface IDVGetEnum
; "70F55181-5FEA-4900-B6B8-7343CB0A348C"

idvge_QueryInterface	equ	0
idvge_AddRef		equ	4
idvge_Release		equ	8
idvge_SetEnumReadyCallback	equ	12
idvge_CreateEnumIDListFromContents	equ	16

; interface IInsertItem
; "D2B57227-3D23-4b95-93C0-492BD454C356"

iinit_QueryInterface	equ	0
iinit_AddRef		equ	4
iinit_Release		equ	8
iinit_InsertItem		equ	12

; interface IDeskBar
; "EB0FE173-1A3A-11D0-89B3-00A0C90A90AC"

idebar_QueryInterface	equ	0
idebar_AddRef		equ	4
idebar_Release		equ	8
idebar_GetWindow		equ	12
idebar_ContextSensitiveHelp	equ	16
idebar_SetClient		equ	20
idebar_GetClient		equ	24
idebar_OnPosRectChangeDB	equ	28

MBHANDCID_PIDLSELECT	equ	0

; interface IMenuBand
; "568804CD-CBD7-11d0-9816-00C04FD91972")

imeba_QueryInterface	equ	0
imeba_AddRef		equ	4
imeba_Release		equ	8
imeba_IsMenuMessage	equ	12
imeba_TranslateMenuMessage	equ	16

; interface IFolderBandPriv
; "47c01f95-e185-412c-b5c5-4f27df965aea

ifobapr_QueryInterface	equ	0
ifobapr_AddRef		equ	4
ifobapr_Release		equ	8
ifobapr_SetCascade	equ	12
ifobapr_SetAccelerators	equ	16
ifobapr_SetNoIcons	equ	20
ifobapr_SetNoText		equ	24

BANDSITEINFO		struc
 bsin_dwMask		dd	?
 bsin_dwState		dd	?
 bsin_dwStyle		dd	?
BANDSITEINFO		ends

BSID_BANDADDED		equ	0
BSID_BANDREMOVED	equ	BSID_BANDADDED + 1

BSIM_STATE		equ	00000001h
BSIM_STYLE		equ	00000002h

BSSF_VISIBLE		equ	00000001h
BSSF_NOTITLE		equ	00000002h
BSSF_UNDELETEABLE 	equ	00001000h

BSIS_AUTOGRIPPER	equ	00000000h
BSIS_NOGRIPPER		equ	00000001h
BSIS_ALWAYSGRIPPER	equ	00000002h
BSIS_LEFTALIGN		equ	00000004h
BSIS_SINGLECLICK		equ	00000008h
BSIS_NOCONTEXTMENU	equ	00000010h
BSIS_NODROPTARGET 	equ	00000020h
BSIS_NOCAPTION		equ	00000040h
BSIS_PREFERNOLINEBREAK 	equ	00000080h
BSIS_LOCKED 		equ	00000100h

; interface IBandSite

ibasi_QueryInterface	equ	0
ibasi_AddRef		equ	4
ibasi_Release		equ	8
ibasi_AddBand		equ	12
ibasi_EnumBands		equ	16
ibasi_QueryBand		equ	20
ibasi_SetBandState	equ	24
ibasi_RemoveBand		equ	28
ibasi_GetBandObject	equ	32
ibasi_SetBandSiteInfo	equ	36
ibasi_GetBandSiteInfo	equ	40

; interface INamespaceWalkCB
; "d92995f8-cf5e-4a76-bf59-ead39ea2b97e"

inawacb_QueryInterface	equ	0
inawacb_AddRef		equ	4
inawacb_Release		equ	8
inawacb_FoundItem	equ	12
inawacb_EnterFolder	equ	16
inawacb_LeaveFolder	equ	20
inawacb_InitializeProgressDialog	equ	24

NSWF_NONE_IMPLIES_ALL	equ	1
NSWF_ONE_IMPLIES_ALL	equ	2
NSWF_DONT_TRAVERSE_LINKS	equ	4
NSWF_DONT_ACCUMULATE_RESULT	equ	8
NSWF_TRAVERSE_STREAM_JUNCTIONS equ	10h
NSWF_FILESYSTEM_ONLY	equ	20h
NSWF_SHOW_PROGRESS	equ	40h
NSWF_FLAG_VIEWORDER	equ	80h
NSWF_IGNORE_AUTOPLAY_HIDA	equ	100h


; interface INamespaceWalk
; "57ced8a7-3f4a-432c-9350-30f24483f74f"

inaspwa_QueryInterface	equ	0
inaspwa_AddRef		equ	4
inaspwa_Release		equ	8
inaspwa_Walk		equ	12
inaspwa_GetIDArrayResult	equ	16

; interface IRegTreeItem
; "A9521922-0812-4d44-9EC3-7FD38C726F3D"

iretrit_QueryInterface	equ	0
iretrit_AddRef		equ	4
iretrit_Release		equ	8
iretrit_GetCheckState	equ	12
iretrit_SetCheckState	equ	16

MPOS_EXECUTE		equ	0
MPOS_FULLCANCEL	equ	MPOS_EXECUTE + 1
MPOS_CANCELLEVEL	equ	MPOS_FULLCANCEL + 1
MPOS_SELECTLEFT	equ	MPOS_CANCELLEVEL + 1
MPOS_SELECTRIGHT	equ	MPOS_SELECTLEFT + 1
MPOS_CHILDTRACKING	equ	MPOS_SELECTRIGHT + 1

MPPF_SETFOCUS		equ	1
MPPF_INITIALSELECT	equ	2
MPPF_NOANIMATE		equ	4
MPPF_KEYBOARD		equ	10h
MPPF_REPOSITION		equ	20h
MPPF_FORCEZORDER	equ	40h
MPPF_FINALSELECT	equ	80h
MPPF_TOP		equ	20000000h
MPPF_LEFT		equ	40000000h
MPPF_RIGHT		equ	60000000h
MPPF_BOTTOM		equ	80000000h
MPPF_POS_MASK		equ	0e0000000h

; interface IMenuPopup
; "D1E7AFEB-6A2E-11d0-8C78-00C04FD918B4"

imepo_QueryInterface	equ	0
imepo_AddRef		equ	4
imepo_Release		equ	8
imepo_GetWindow		equ	12
imepo_ContextSensitiveHelp	equ	16
imepo_SetClient		equ	20
imepo_GetClient		equ	24
imepo_OnPosRectChangeDB	equ	28
imepo_Popup		equ	32
imepo_OnSelect		equ	36
imepo_SetSubMenu	equ	40

SIGDN_NORMALDISPLAY		equ	0
SIGDN_PARENTRELATIVEPARSING		equ	80018001h
SIGDN_PARENTRELATIVEFORADDRESSBAR	equ	8001c001h
SIGDN_DESKTOPABSOLUTEPARSING		equ	80028000h
SIGDN_PARENTRELATIVEEDITING		equ	80031001h
SIGDN_DESKTOPABSOLUTEEDITING		equ	8004c000h
SIGDN_FILESYSPATH		equ	80058000h
SIGDN_URL			equ	80068000h

SICHINT_DISPLAY		equ	0
SICHINT_ALLFIELDS	equ	80000000h
SICHINT_CANONICAL	equ	10000000h

; interface IShellItem
; "43826d1e-e718-42ee-bc55-a1e261c37bfe"

ishit_QueryInterface	equ	0
ishit_AddRef		equ	4
ishit_Release		equ	8
ishit_BindToHandler	equ	12
ishit_GetParent		equ	16
ishit_GetDisplayName	equ	20
ishit_GetAttributes		equ	24
ishit_Compare		equ	28

; interface IImageRecompress
; "505f1513-6b3e-4892-a272-59f8889a4d3e"

iimre_QueryInterface	equ	0
iimre_AddRef		equ	4
iimre_Release		equ	8
iimre_RecompressImageIShellItem	equ	12

; interface IDefViewSafety
; "9A93B3FB-4E75-4c74-871A-2CDA667F39A5"

idevisa_QueryInterface	equ	0
idevisa_AddRef		equ	4
idevisa_Release		equ	8
idevisa_IsSafePage		equ	12

; interface IContextMenuSite
; "0811AEBE-0B87-4C54-9E72-548CF649016B"

icomesi_QueryInterface	equ	0
icomesi_AddRef		equ	4
icomesi_Release		equ	8
icomesi_DoContextMenuPopup	equ	12

DELEGATEITEMID		struc
 diid_cbSize		dw	?
 diid_wOuter		dw	?
 diid_cbInner		dw	?
DELEGATEITEMID		ends

; interface IDelegateFolder
; "ADD8BA80-002B-11D0-8F0F-00C04FD7D062"

idefo_QueryInterface	equ	0
idefo_AddRef		equ	4
idefo_Release		equ	8
idefo_SetItemAlloc		equ	12

BFO_NONE			equ	0
BFO_BROWSER_PERSIST_SETTINGS		equ	1
BFO_RENAME_FOLDER_OPTIONS_TOINTERNET	equ	2
BFO_BOTH_OPTIONS		equ	4
BIF_PREFER_INTERNET_SHORTCUT		equ	8
BFO_BROWSE_NO_IN_NEW_PROCESS		equ	10h
BFO_ENABLE_HYPERLINK_TRACKING		equ	20h
BFO_USE_IE_OFFLINE_SUPPORT		equ	40h
BFO_SUBSTITUE_INTERNET_START_PAGE	equ	80h
BFO_USE_IE_LOGOBANDING		equ	100h
BFO_ADD_IE_TOCAPTIONBAR		equ	200h
BFO_USE_DIALUP_REF		equ	400h
BFO_USE_IE_TOOLBAR		equ	800h
BFO_NO_PARENT_FOLDER_SUPPORT		equ	1000h
BFO_NO_REOPEN_NEXT_RESTART		equ	2000h
BFO_GO_HOME_PAGE		equ	4000h
BFO_PREFER_IEPROCESS		equ	8000h
BFO_SHOW_NAVIGATION_CANCELLED		equ	10000h
BFO_QUERY_ALL			equ	0ffffffffh

; interface IBrowserFrameOptions
; "10DF43C8-1DBE-11d3-8B34-006097DF5BD4"

ibrfrop_QueryInterface	equ	0
ibrfrop_AddRef		equ	4
ibrfrop_Release		equ	8
ibrfrop_GetFrameOptions	equ	12

SMDATA		struc
 smdat_dwMask		dd	?
 smdat_dwFlags		dd	?
 smdat_hmenu		dd	?
 smdat_hwnd		dd	?
 smdat_uId		dd	?
 smdat_uIdParent		dd	?
 smdat_uIdAncestor	dd	?
 smdat_punk		dd	?
 smdat_pidlFolder		dd	?
 smdat_pidlItem		dd	?
 smdat_psf		dd	?
 smdat_pvUserData	dd	?
SMDATA		ends

SMDM_SHELLFOLDER 	equ	1	; This is for an item in the band
SMDM_HMENU 		equ	2	; This is for the Band itself
SMDM_TOOLBAR 		equ	4	; Plain toolbar, not associated with a shell folder or hmenu Flags (bitmask)

SMINFO		struc
 sminf_dwMask		dd	?
 sminf_dwType		dd	?
 sminf_dwFlags		dd	?
 sminf_iIcon		dd	?
SMINFO		ends

SMCSHCHANGENOTIFYSTRUCT	struc
 smccn_lEvent		dd	?
 smccn_pidl1		dd	?
 smccn_pidl2		dd	?
SMCSHCHANGENOTIFYSTRUCT	ends

SMIM_TYPE		equ	1
SMIM_FLAGS		equ	2
SMIM_ICON		equ	4

SMIT_SEPARATOR		equ	1
SMIT_STRING		equ	2

SMIF_ICON		equ	1
SMIF_ACCELERATOR	equ	2
SMIF_DROPTARGET	equ	4
SMIF_SUBMENU		equ	8
SMIF_CHECKED		equ	20h
SMIF_DROPCASCADE	equ	40h
SMIF_HIDDEN		equ	80h
SMIF_DISABLED		equ	100h
SMIF_TRACKPOPUP		equ	200h
SMIF_DEMOTED		equ	400h
SMIF_ALTSTATE		equ	800h
SMIF_DRAGNDROP		equ	1000h
SMIF_NEW		equ	2000h

SMC_INITMENU		equ	00000001h	; The callback is called to init a menuband
SMC_CREATE		equ	00000002h
SMC_EXITMENU		equ	00000003h	; The callback is called when menu is collapsing
SMC_GETINFO 		equ	00000005h	; The callback is called to return DWORD values
SMC_GETSFINFO 		equ	00000006h	; The callback is called to return DWORD values
SMC_GETOBJECT 		equ	00000007h	; The callback is called to get some object
SMC_GETSFOBJECT 	equ	00000008h	; The callback is called to get some object
SMC_SFEXEC		equ	00000009h	; The callback is called to execute an shell folder item
SMC_SFSELECTITEM	equ	0000000Ah	; The callback is called when an item is selected
SMC_REFRESH 		equ	00000010h	; Menus have completely refreshed. Reset your state.
SMC_DEMOTE		equ	00000011h	; Demote an item
SMC_PROMOTE 		equ	00000012h	; Promote an item, wParam = SMINV_* flag
SMC_DEFAULTICON 	equ	00000016h	; Returns Default icon location in wParam, index in lParam
SMC_NEWITEM 		equ	00000017h	; Notifies item is not in the order stream.
SMC_CHEVRONEXPAND 	equ	00000019h	; Notifies of a expansion via the chevron
SMC_DISPLAYCHEVRONTIP 	equ	0000002Ah	; S_OK display, S_FALSE not.
SMC_SETSFOBJECT 	equ	0000002Dh	; Called to save the passed object
SMC_SHCHANGENOTIFY	equ	0000002Eh	; Called when a Change notify is received. lParam points to SMCSHCHANGENOTIFYSTRUCT
SMC_CHEVRONGETTIP 	equ	0000002Fh	; Called to get the chevron tip text. wParam = Tip title, Lparam = TipText Both MAX_PATH
SMC_SFDDRESTRICTED	equ	00000030h	; Called requesting if it's ok to drop. wParam = IDropTarget.

; interface IShellMenuCallback
; "4CA300A1-9B8D-11d1-8B22-00C04FD918D0"

ishmeca_QueryInterface	equ	0
ishmeca_AddRef		equ	4
ishmeca_Release		equ	8
ishmeca_CallbackSMU	equ	12

SMINIT_DEFAULT		equ	00000000h	; No Options
SMINIT_RESTRICT_DRAGDROP	equ	00000002h	; Don't allow Drag and Drop
SMINIT_TOPLEVEL 		equ	00000004h	; This is the top band.
SMINIT_CACHED 		equ	00000010h
SMINIT_VERTICAL 		equ	10000000h	; This is a vertical menu
SMINIT_HORIZONTAL 	equ	20000000h	; This is a horizontal menu(does not inherit)

ANCESTORDEFAULT	equ	-1

SMSET_TOP 		equ	10000000h	; Bias this namespace to the top of the menu
SMSET_BOTTOM		equ	20000000h	; Bias this namespace to the bottom of the menu
SMSET_DONTOWN 	equ	00000001h	; The Menuband doesn't own the non-ref counted object

SMINV_REFRESH		equ	00000001h
SMINV_ID 		equ	00000008h

; interface IShellMenu
; "EE1F7637-E138-11d1-8379-00C04FD918D0"

ishme_QueryInterface	equ	0
ishme_AddRef		equ	4
ishme_Release		equ	8
ishme_Initialize		equ	12
ishme_GetMenuInfo	equ	16
ishme_SetShellFolderIShellFolder	equ	20
ishme_GetShellFolder	equ	24
ishme_SetMenu		equ	28
ishme_GetMenu		equ	32
ishme_InvalidateItem	equ	36
ishme_GetState		equ	40
ishme_SetMenuToolbar	equ	44
