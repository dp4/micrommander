;--------------------------------T--------------T-----------------------------------T------------------------------------

;===========================================================================
;
; Copyright (c) Microsoft Corporation 1991-1996
;
; File: shlobj.h
;
;===========================================================================

SHFormatDrive	proto	:QWORD, :DWORD, :DWORD, :DWORD

	IFDEF	UNICODE

SHGetSpecialFolderPath	equ	SHGetSpecialFolderPathW

	ELSE

SHGetSpecialFolderPath	equ	_SHGetSpecialFolderPathA@16

	ENDIF

;
; SHITEMID -- Item ID
;
;typedef struct _SHITEMID; mkid
;{
;USHORTcb; ; Size of the ID (including cb itself)
;BYTEabID[1];; The item ID (variable length)
;} SHITEMID;

;typedef UNALIGNED SHITEMID *LPSHITEMID;
;typedef const UNALIGNED SHITEMID *LPCSHITEMID;

;
; ITEMIDLIST -- List if item IDs (combined with 0-terminator)
;
;typedef struct _ITEMIDLIST; idl
;{
;SHITEMIDmkid;
;} ITEMIDLIST;

;typedef UNALIGNED ITEMIDLIST * LPITEMIDLIST;
;typedef const UNALIGNED ITEMIDLIST * LPCITEMIDLIST;


;===========================================================================
;
; Task allocator API
;
; All the shell extensions MUST use the task allocator (see OLE 2.0
; programming guild for its definition) when they allocate or free
; memory objects (mostly ITEMIDLIST) that are returned across any
; shell interfaces. There are two ways to access the task allocator
; from a shell extension depending on whether or not it is linked with
; OLE32.DLL or not (purely for efficiency).
;
; (1) A shell extension which calls any OLE API (i.e., linked with
; OLE32.DLL) should call OLE's task allocator (by retrieving
; the task allocator by calling CoGetMalloc API).
;
; (2) A shell extension which does not call any OLE API (i.e., not linked
; with OLE32.DLL) should call the shell task allocator API (defined
; below), so that the shell can quickly loads it when OLE32.DLL is not
; loaded by any application at that point.
;
; Notes:
; In next version of Windowso release, SHGetMalloc will be replaced by
; the following macro.
;
; SHGetMalloc(ppmem) CoGetMalloc(MEMCTX_TASK, ppmem)
;
;===========================================================================

;WINSHELLAPI HRESULT WINAPI SHGetMalloc(LPMALLOC * ppMalloc);



;===========================================================================
;
; IContextMenu interface
;
; [OverView]
;
; The shell uses the IContextMenu interface in following three cases.
;
; case-1: The shell is loading context menu extensions.
;
; When the user clicks the right mouse button on an item within the shell's
; name space (i.g., file, directory, server, work-group, etc.), it creates
; the default context menu for its type, then loads context menu extensions
; that are registered for that type (and its base type) so that they can
; add extra menu items. Those context menu extensions are registered at
; HKCR\{ProgID}\shellex\ContextMenuHandlers.
;
; case-2: The shell is retrieving a context menu of sub-folders in extended
; name-space.
;
; When the explorer's name space is extended by name space extensions,
; the shell calls their IShellFolder::GetUIObjectOf to get the IContextMenu
; objects when it creates context menus for folders under those extended
; name spaces.
;
; case-3: The shell is loading non-default drag and drop handler for directories.
;
; When the user performed a non-default drag and drop onto one of file
; system folders (i.e., directories), it loads shell extensions that are
; registered at HKCR\{ProgID}\DragDropHandlers.
;
;
; [Member functions]
;
;
; IContextMenu::QueryContextMenu
;
; This member function may insert one or more menuitems to the specified
; menu (hmenu) at the specified location (indexMenu which is never be -1).
; The IDs of those menuitem must be in the specified range (idCmdFirst and
; idCmdLast). It returns the maximum menuitem ID offset (ushort) in the
; 'code' field (low word) of the scode.
;
; The uFlags specify the context. It may have one or more of following
; flags.
;
; CMF_DEFAULTONLY: This flag is passed if the user is invoking the default
; action (typically by double-clicking, case 1 and 2 only). Context menu
; extensions (case 1) should not add any menu items, and returns NOERROR.
;
; CMF_VERBSONLY: The explorer passes this flag if it is constructing
; a context menu for a short-cut object (case 1 and case 2 only). If this
; flag is passed, it should not add any menu-items that is not appropriate
; from a short-cut.
; A good example is the "Delete" menuitem, which confuses the user
; because it is not clear whether it deletes the link source item or the
; link itself.
;
; CMF_EXPLORER: The explorer passes this flag if it has the left-side pane
; (case 1 and 2 only). Context menu extensions should ignore this flag.
;
; High word (16-bit) are reserved for context specific communications
; and the rest of flags (13-bit) are reserved by the system.
;
;
; IContextMenu::InvokeCommand
;
; This member is called when the user has selected one of menuitems that
; are inserted by previous QueryContextMenu member. In this case, the
; LOWORD(lpici->lpVerb) contains the menuitem ID offset (menuitem ID -
; idCmdFirst).
;
; This member function may also be called programmatically. In such a case,
; lpici->lpVerb specifies the canonical name of the command to be invoked,
; which is typically retrieved by GetCommandString member previously.
;
; Parameters in lpci:
; cbSize -- Specifies the size of this structure (sizeof(*lpci))
; hwnd -- Specifies the owner window for any message/dialog box.
; fMask-- Specifies whether or not dwHotkey/hIcon paramter is valid.
; lpVerb -- Specifies the command to be invoked.
; lpParameters -- Parameters (optional)
; lpDirectory-- Working directory (optional)
; nShow -- Specifies the flag to be passed to ShowWindow (SW_*).
; dwHotKey -- Hot key to be assigned to the app after invoked (optional).
; hIcon -- Specifies the icon (optional).
;
;
; IContextMenu::GetCommandString
;
; This member function is called by the explorer either to get the
; canonical (language independent) command name (uFlags == GCS_VERB) or
; the help text ((uFlags & GCS_HELPTEXT) != 0) for the specified command.
; The retrieved canonical string may be passed to its InvokeCommand
; member function to invoke a command programmatically. The explorer
; displays the help texts in its status bar; therefore, the length of
; the help text should be reasonably short (<40 characters).
;
; Parameters:
; idCmd -- Specifies menuitem ID offset (from idCmdFirst)
; uFlags -- Either GCS_VERB or GCS_HELPTEXT
; pwReserved -- Reserved (must pass NULL when calling, must ignore when called)
; pszName -- Specifies the string buffer.
; cchMax -- Specifies the size of the string buffer.
;
;===========================================================================

; QueryContextMenu uFlags

CMF_NORMAL		equ	00000000h
CMF_DEFAULTONLY 		equ	00000001h
CMF_VERBSONLY 		equ	00000002h
CMF_EXPLORE 		equ	00000004h
CMF_NOVERBS 		equ	00000008h
CMF_CANRENAME 		equ	00000010h
CMF_NODEFAULT 		equ	00000020h
CMF_INCLUDESTATIC 	equ	00000040h
CMF_RESERVED		equ	0FFFF0000h	; View specific

; GetCommandString uFlags

GCS_VERBA	equ	00000000h	; canonical verb
GCS_HELPTEXTA	equ	00000001h	; help text (for status bar)
GCS_VALIDATEA	equ	00000002h	; validate command exists
GCS_VERBW	equ	00000004h	; canonical verb (unicode)
GCS_HELPTEXTW	equ	00000005h	; help text (unicode version)
GCS_VALIDATEW	equ	00000006h	; validate command exists (unicode)
GCS_UNICODE	equ	00000004h	; for bit testing - Unicode string

;#ifdef UNICODE
;GCS_VERB	equ	GCS_VERBW
;GCS_HELPTEXT	equ	GCS_HELPTEXTW
;GCS_VALIDATE	equ	GCS_VALIDATEW
;#else
GCS_VERB	equ	GCS_VERBA
GCS_HELPTEXT	equ	GCS_HELPTEXTA
GCS_VALIDATE	equ	GCS_VALIDATEA
;#endif

;CMDSTR_NEWFOLDERA 	textequ	"NewFolder"
;CMDSTR_VIEWLISTA	textequ	"ViewList"
;CMDSTR_VIEWDETAILSA	textequ	"ViewDetails"

;CMDSTR_NEWFOLDERW L"NewFolder"
;CMDSTR_VIEWLISTWL"ViewList"
;CMDSTR_VIEWDETAILSW L"ViewDetails"

;#ifdef UNICODE
;CMDSTR_NEWFOLDER	equ	CMDSTR_NEWFOLDERW
;CMDSTR_VIEWLIST 	equ	CMDSTR_VIEWLISTW
;CMDSTR_VIEWDETAILS	equ	CMDSTR_VIEWDETAILSW
;#else
CMDSTR_NEWFOLDER	equ	CMDSTR_NEWFOLDERA
CMDSTR_VIEWLIST 		equ	CMDSTR_VIEWLISTA
CMDSTR_VIEWDETAILS	equ	CMDSTR_VIEWDETAILSA
;#endif

CMIC_MASK_HOTKEY	equ	SEE_MASK_HOTKEY
CMIC_MASK_ICON		equ	SEE_MASK_ICON
CMIC_MASK_FLAG_NO_UI	equ	SEE_MASK_FLAG_NO_UI
CMIC_MASK_UNICODE 	equ	SEE_MASK_UNICODE
CMIC_MASK_NO_CONSOLE	equ	SEE_MASK_NO_CONSOLE
CMIC_MASK_HASLINKNAME	equ	SEE_MASK_HASLINKNAME
CMIC_MASK_FLAG_SEP_VDM	equ	SEE_MASK_FLAG_SEPVDM
CMIC_MASK_HASTITLE	equ	SEE_MASK_HASTITLE
CMIC_MASK_ASYNCOK 	equ	SEE_MASK_ASYNCOK


;typedef struct _CMINVOKECOMMANDINFO {
;DWORD cbSize;; sizeof(CMINVOKECOMMANDINFO)
;DWORD fMask; ; any combination of CMIC_MASK_*
;HWND hwnd; ; might be NULL (indicating no owner window)
;LPCSTR lpVerb; ; either a string or MAKEINTRESOURCE(idOffset)
;LPCSTR lpParameters; ; might be NULL (indicating no parameter)
;LPCSTR lpDirectory;; might be NULL (indicating no specific directory)
;int nShow; ; one of SW_ values for ShowWindow() API
;DWORD dwHotKey;
;HANDLE hIcon;
;} CMINVOKECOMMANDINFO,*LPCMINVOKECOMMANDINFO;

;typedef struct _CMInvokeCommandInfoEx {
;DWORD cbSize;; must be sizeof(CMINVOKECOMMANDINFOEX)
;DWORD fMask; ; any combination of CMIC_MASK_*
;HWND hwnd; ; might be NULL (indicating no owner window)
;LPCSTR lpVerb; ; either a string or MAKEINTRESOURCE(idOffset)
;LPCSTR lpParameters; ; might be NULL (indicating no parameter)
;LPCSTR lpDirectory;; might be NULL (indicating no specific directory)
;int nShow; ; one of SW_ values for ShowWindow() API
;DWORD dwHotKey;
;HANDLE hIcon;
;LPCSTR lpTitle;; For CreateProcess-StartupInfo.lpTitle
;LPCWSTR lpVerbW;; Unicode verb (for those who can use it)
;LPCWSTR lpParametersW;; Unicode parameters (for those who can use it)
;LPCWSTR lpDirectoryW; ; Unicode directory (for those who can use it)
;LPCWSTR lpTitleW; ; Unicode title (for those who can use it)
;} CMINVOKECOMMANDINFOEX,*LPCMINVOKECOMMANDINFOEX;

;#undefINTERFACE
;INTERFACE IContextMenu

;DECLARE_INTERFACE_(IContextMenu, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD(QueryContextMenu)(THIS_
;HMENU hmenu,
;UINT indexMenu,
;UINT idCmdFirst,
;UINT idCmdLast,
;UINT uFlags) PURE;

;STDMETHOD(InvokeCommand)(THIS_
; LPCMINVOKECOMMANDINFO lpici) PURE;

;STDMETHOD(GetCommandString)(THIS_
;UINTidCmd,
;UINTuType,
;UINT* pwReserved,
;LPSTR pszName,
;UINTcchMax) PURE;
;};

;typedef IContextMenu *LPCONTEXTMENU;

;
; IContextMenu2 (IContextMenu with one new member)
;
; IContextMenu2::HandleMenuMsg
;
;This function is called, if the client of IContextMenu is aware of
; IContextMenu2 interface and receives one of following messages while
; it is calling TrackPopupMenu (in the window proc of hwndOwner):
;WM_INITPOPUP, WM_DRAWITEM and WM_MEASUREITEM
;The callee may handle these messages to draw owner draw menuitems.
;

;#undefINTERFACE
;INTERFACE IContextMenu2

;DECLARE_INTERFACE_(IContextMenu2, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD(QueryContextMenu)(THIS_
;HMENU hmenu,
;UINT indexMenu,
;UINT idCmdFirst,
;UINT idCmdLast,
;UINT uFlags) PURE;

;STDMETHOD(InvokeCommand)(THIS_
; LPCMINVOKECOMMANDINFO lpici) PURE;

;STDMETHOD(GetCommandString)(THIS_
;UINTidCmd,
;UINTuType,
;UINT* pwReserved,
;LPSTR pszName,
;UINTcchMax) PURE;
;STDMETHOD(HandleMenuMsg)(THIS_
; UINT uMsg,
; WPARAM wParam,
; LPARAM lParam) PURE;
;};

;typedef IContextMenu2 * LPCONTEXTMENU2;



;===========================================================================
;
; Interface: IShellExtInit
;
;The IShellExtInit interface is used by the explorer to initialize shell
; extension objects. The explorer (1) calls CoCreateInstance (or equivalent)
; with the registered CLSID and IID_IShellExtInit, (2) calls its Initialize
; member, then (3) calls its QueryInterface to a particular interface (such
; as IContextMenu or IPropSheetExt and (4) performs the rest of operation.
;
;
; [Member functions]
;
; IShellExtInit::Initialize
;
;This member function is called when the explorer is initializing either
; context menu extension, property sheet extension or non-default drag-drop
; extension.
;
;Parameters: (context menu or property sheet extension)
; pidlFolder -- Specifies the parent folder
; lpdobj -- Spefifies the set of items selected in that folder.
; hkeyProgID -- Specifies the type of the focused item in the selection.
;
;Parameters: (non-default drag-and-drop extension)
; pidlFolder -- Specifies the target (destination) folder
; lpdobj -- Specifies the items that are dropped (see the description
;about shell's clipboard below for clipboard formats).
; hkeyProgID -- Specifies the folder type.
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IShellExtInit

;DECLARE_INTERFACE_(IShellExtInit, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IShellExtInit methods ***
;STDMETHOD(Initialize)(THIS_ LPCITEMIDLIST pidlFolder,
;LPDATAOBJECT lpdobj, HKEY hkeyProgID) PURE;
;};

;typedef IShellExtInit * LPSHELLEXTINIT;


;===========================================================================
;
; Interface: IShellPropSheetExt
;
;The explorer uses the IShellPropSheetExt to allow property sheet
; extensions or control panel extensions to add additional property
; sheet pages.
;
;
; [Member functions]
;
; IShellPropSheetExt::AddPages
;
;The explorer calls this member function when it finds a registered
; property sheet extension for a particular type of object. For each
; additional page, the extension creates a page object by calling
; CreatePropertySheetPage API and calls lpfnAddPage.
;
;Parameters:
; lpfnAddPage -- Specifies the callback function.
; lParam -- Specifies the opaque handle to be passed to the callback function.
;
;
; IShellPropSheetExt::ReplacePage
;
;The explorer never calls this member of property sheet extensions. The
; explorer calls this member of control panel extensions, so that they
; can replace some of default control panel pages (such as a page of
; mouse control panel).
;
;Parameters:
; uPageID -- Specifies the page to be replaced.
; lpfnReplace Specifies the callback function.
; lParam -- Specifies the opaque handle to be passed to the callback function.
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IShellPropSheetExt

;DECLARE_INTERFACE_(IShellPropSheetExt, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IShellPropSheetExt methods ***
;STDMETHOD(AddPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam) PURE;
;STDMETHOD(ReplacePage)(THIS_ UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam) PURE;
;};

;typedef IShellPropSheetExt * LPSHELLPROPSHEETEXT;


;===========================================================================
;
; IPersistFolder Interface
;
;The IPersistFolder interface is used by the file system implementation of
; IShellFolder::BindToObject when it is initializing a shell folder object.
;
;
; [Member functions]
;
; IPersistFolder::Initialize
;
;This member function is called when the explorer is initializing a
; shell folder object.
;
;Parameters:
; pidl -- Specifies the absolute location of the folder.
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IPersistFolder

;DECLARE_INTERFACE_(IPersistFolder, IPersist); fld
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef)(THIS)PURE;
;STDMETHOD_(ULONG,Release)(THIS) PURE;

; *** IPersist methods ***
;STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID) PURE;

; *** IPersistFolder methods ***
;STDMETHOD(Initialize)(THIS_ LPCITEMIDLIST pidl) PURE;
;};

;typedef IPersistFolder *LPPERSISTFOLDER;


;===========================================================================
;
; IExtractIcon interface
;
;This interface is used in two different places in the shell.
;
; Case-1: Icons of sub-folders for the scope-pane of the explorer.
;
;It is used by the explorer to get the "icon location" of
; sub-folders from each shell folders. When the user expands a folder
; in the scope pane of the explorer, the explorer does following:
;(1) binds to the folder (gets IShellFolder),
;(2) enumerates its sub-folders by calling its EnumObjects member,
;(3) calls its GetUIObjectOf member to get IExtractIcon interface
; for each sub-folders.
;In this case, the explorer uses only IExtractIcon::GetIconLocation
; member to get the location of the appropriate icon. An icon location
; always consists of a file name (typically DLL or EXE) and either an icon
; resource or an icon index.
;
;
; Case-2: Extracting an icon image from a file
;
;It is used by the shell when it extracts an icon image
; from a file. When the shell is extracting an icon from a file,
; it does following:
;(1) creates the icon extraction handler object (by getting its CLSID
; under the {ProgID}\shell\ExtractIconHanler key and calling
; CoCreateInstance requesting for IExtractIcon interface).
;(2) Calls IExtractIcon::GetIconLocation.
;(3) Then, calls IExtractIcon::ExtractIcon with the location/index pair.
;(4) If (3) returns NOERROR, it uses the returned icon.
;(5) Otherwise, it recursively calls this logic with new location
; assuming that the location string contains a fully qualified path name.
;
;From extension programmer's point of view, there are only two cases
; where they provide implementations of IExtractIcon:
;Case-1) providing explorer extensions (i.e., IShellFolder).
;Case-2) providing per-instance icons for some types of files.
;
; Because Case-1 is described above, we'll explain only Case-2 here.
;
; When the shell is about display an icon for a file, it does following:
;(1) Finds its ProgID and ClassID.
;(2) If the file has a ClassID, it gets the icon location string from the
;"DefaultIcon" key under it. The string indicates either per-class
;icon (e.g., "FOOBAR.DLL,2") or per-instance icon (e.g., "%1,1").
;(3) If a per-instance icon is specified, the shell creates an icon
;extraction handler object for it, and extracts the icon from it
;(which is described above).
;
;It is important to note that the shell calls IExtractIcon::GetIconLocation
; first, then calls IExtractIcon::Extract. Most application programs
; that support per-instance icons will probably store an icon location
; (DLL/EXE name and index/id) rather than an icon image in each file.
; In those cases, a programmer needs to implement only the GetIconLocation
; member and it Extract member simply returns S_FALSE. They need to
; implement Extract member only if they decided to store the icon images
; within files themselved or some other database (which is very rare).
;
;
;
; [Member functions]
;
;
; IExtractIcon::GetIconLocation
;
;This function returns an icon location.
;
;Parameters:
; uFlags [in]-- Specifies if it is opened or not (GIL_OPENICON or 0)
; szIconFile [out] -- Specifies the string buffer buffer for a location name.
; cchMax [in]-- Specifies the size of szIconFile (almost always MAX_PATH)
; piIndex[out] -- Sepcifies the address of UINT for the index.
; pwFlags[out] -- Returns GIL_* flags
;Returns:
; NOERROR, if it returns a valid location; S_FALSE, if the shell use a
; default icon.
;
;Notes: The location may or may not be a path to a file. The caller can
; not assume anything unless the subsequent Extract member call returns
; S_FALSE.
;
; if the returned location is not a path to a file, GIL_NOTFILENAME should
; be set in the returned flags.
;
; IExtractIcon::Extract
;
;This function extracts an icon image from a specified file.
;
;Parameters:
; pszFile [in] -- Specifies the icon location (typically a path to a file).
; nIconIndex [in] -- Specifies the icon index.
; phiconLarge [out] -- Specifies the HICON variable for large icon.
; phiconSmall [out] -- Specifies the HICON variable for small icon.
; nIconSize [in] -- Specifies the size icon required (size of large icon)
; LOWORD is the requested large icon size
; HIWORD is the requested small icon size
;Returns:
; NOERROR, if it extracted the from the file.
; S_FALSE, if the caller should extract from the file specified in the
; location.
;
;===========================================================================

; GetIconLocation() input flags

GIL_OPENICON 	equ	0001h	; allows containers to specify an "open" look
GIL_FORSHELL 	equ	0002h	; icon is to be displayed in a ShellFolder
GIL_ASYNC	equ	0020h	; this is an async extract, return E_ASYNC

; GetIconLocation() return flags

GIL_SIMULATEDOC	equ	0001h	; simulate this document icon for this
GIL_PERINSTANCE	equ	0002h	; icons from this class are per instance (each file has its own)
GIL_PERCLASS 	equ	0004h	; icons from this class per class (shared for all files of this type)
GIL_NOTFILENAME	equ	0008h	; location is not a filename, must call ::ExtractIcon
GIL_DONTCACHE	equ	0010h	; this icon should not be cached

;#undefINTERFACE
;INTERFACE IExtractIconA

;DECLARE_INTERFACE_(IExtractIconA, IUnknown) ; exic
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IExtractIcon methods ***
;STDMETHOD(GetIconLocation)(THIS_
; UINT uFlags,
; LPSTRszIconFile,
; UINT cchMax,
; int * piIndex,
; UINT* pwFlags) PURE;

;STDMETHOD(Extract)(THIS_
; LPCSTR pszFile,
; UINT nIconIndex,
; HICON *phiconLarge,
; HICON *phiconSmall,
; UINTnIconSize) PURE;
;};

;typedef IExtractIconA * LPEXTRACTICONA;

;#undefINTERFACE
;INTERFACE IExtractIconW

;DECLARE_INTERFACE_(IExtractIconW, IUnknown) ; exic
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IExtractIcon methods ***
;STDMETHOD(GetIconLocation)(THIS_
; UINT uFlags,
; LPWSTR szIconFile,
; UINT cchMax,
; int * piIndex,
; UINT* pwFlags) PURE;

;STDMETHOD(Extract)(THIS_
; LPCWSTR pszFile,
; UINT nIconIndex,
; HICON *phiconLarge,
; HICON *phiconSmall,
; UINTnIconSize) PURE;
;};

;typedef IExtractIconW * LPEXTRACTICONW;

;#ifdef UNICODE
;IExtractIcon	equ	IExtractIconW
;IExtractIcon	equ	VtblIExtractIconWVtbl
;LPEXTRACTICON 	equ	LPEXTRACTICONW
;#else
IExtractIcon	equ	IExtractIconA
IExtractIconVtbl	equ	IExtractIconAVtbl
LPEXTRACTICON 	equ	LPEXTRACTICONA
;#endif

;===========================================================================
;
; IShellIcon Interface
;
; used to get a icon index for a IShellFolder object.
;
; this interface can be implemented by a IShellFolder, as a quick way to
; return the icon for a object in the folder.
;
; a instance of this interface is only created once for the folder, unlike
; IExtractIcon witch is created once for each object.
;
; if a ShellFolder does not implement this interface, the standard
; GetUIObject(....IExtractIcon) method will be used to get a icon
; for all objects.
;
; the following standard imagelist indexs can be returned:
;
;0 document (blank page) (not associated)
;1 document (with stuff on the page)
;2 application (exe, com, bat)
;3 folder (plain)
;4 folder (open)
;
; IShellIcon:GetIconOf(pidl, flags, lpIconIndex)
;
;pidlobject to get icon for.
;flags GIL_* input flags (GIL_OPEN, ...)
;lpIconIndex place to return icon index.
;
;returns:
;NOERROR, if lpIconIndex contains the correct system imagelist index.
;S_FALSE, if unable to get icon for this object, go through
; GetUIObject, IExtractIcon, methods.
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IShellIcon

;DECLARE_INTERFACE_(IShellIcon, IUnknown); shi
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IShellIcon methods ***
;STDMETHOD(GetIconOf)(THIS_ LPCITEMIDLIST pidl, UINT flags,
;LPINT lpIconIndex) PURE;
;};

;typedef IShellIcon *LPSHELLICON;

;#ifdef _INC_SHELLAPI/* for LPSHELLEXECUTEINFO */


;===========================================================================
;
; IShellExecuteHook Interface
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IShellExecuteHookA

;DECLARE_INTERFACE_(IShellExecuteHookA, IUnknown) ; shexhk
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG, AddRef) (THIS)PURE;
;STDMETHOD_(ULONG, Release) (THIS) PURE;

; *** IShellExecuteHookA methods ***
;STDMETHOD(Execute)(THIS_ LPSHELLEXECUTEINFOA pei) PURE;
;};

;#undefINTERFACE
;INTERFACE IShellExecuteHookW

;DECLARE_INTERFACE_(IShellExecuteHookW, IUnknown) ; shexhk
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG, AddRef) (THIS)PURE;
;STDMETHOD_(ULONG, Release) (THIS) PURE;

; *** IShellExecuteHookW methods ***
;STDMETHOD(Execute)(THIS_ LPSHELLEXECUTEINFOW pei) PURE;
;};

;#ifdef UNICODE
;IShellExecuteHook		equ	IShellExecuteHookW
;IShellExecuteHookVtbl 	equ	IShellExecuteHookWVtbl
;#else
IShellExecuteHook 		equ	IShellExecuteHookA
IShellExecuteHookVtbl 	equ	IShellExecuteHookAVtbl
;#endif
;#endif

;===========================================================================
;
; INewShortcutHook Interface
;
;===========================================================================

;#undefINTERFACE
;INTERFACE INewShortcutHookA

;DECLARE_INTERFACE_(INewShortcutHookA, IUnknown) ; nshhk
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG, AddRef) (THIS)PURE;
;STDMETHOD_(ULONG, Release) (THIS) PURE;

; *** INewShortcutHook methods ***
;STDMETHOD(SetReferent)(THIS_ LPCSTR pcszReferent, HWND hwnd) PURE;
;STDMETHOD(GetReferent)(THIS_ LPSTR pszReferent, int cchReferent) PURE;
;STDMETHOD(SetFolder)(THIS_ LPCSTR pcszFolder) PURE;
;STDMETHOD(GetFolder)(THIS_ LPSTR pszFolder, int cchFolder) PURE;
;STDMETHOD(GetName)(THIS_ LPSTR pszName, int cchName) PURE;
;STDMETHOD(GetExtension)(THIS_ LPSTR pszExtension, int cchExtension) PURE;
;};

;#undefINTERFACE
;INTERFACE INewShortcutHookW

;DECLARE_INTERFACE_(INewShortcutHookW, IUnknown) ; nshhk
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG, AddRef) (THIS)PURE;
;STDMETHOD_(ULONG, Release) (THIS) PURE;

; *** INewShortcutHook methods ***
;STDMETHOD(SetReferent)(THIS_ LPCWSTR pcszReferent, HWND hwnd) PURE;
;STDMETHOD(GetReferent)(THIS_ LPWSTR pszReferent, int cchReferent) PURE;
;STDMETHOD(SetFolder)(THIS_ LPCWSTR pcszFolder) PURE;
;STDMETHOD(GetFolder)(THIS_ LPWSTR pszFolder, int cchFolder) PURE;
;STDMETHOD(GetName)(THIS_ LPWSTR pszName, int cchName) PURE;
;STDMETHOD(GetExtension)(THIS_ LPWSTR pszExtension, int cchExtension) PURE;
;};

;#ifdef UNICODE
;INewShortcutHook		equ	INewShortcutHookW
;INewShortcutHookVtbl	equ	INewShortcutHookWVtbl
;#else
INewShortcutHook		equ	INewShortcutHookA
INewShortcutHookVtbl	equ	INewShortcutHookAVtbl
;#endif

;===========================================================================
;
; ICopyHook Interface
;
;The copy hook is called whenever file system directories are
;copy/moved/deleted/renamed via the shell.It is also called by the shell
;on changes of status of printers.
;
;Clients register their id under STRREG_SHEX_COPYHOOK for file system hooks
;and STRREG_SHEx_PRNCOPYHOOK for printer hooks.
;the CopyCallback is called prior to the action, so the hook has the chance
;to allow, deny or cancel the operation by returning the falues:
; IDYES-means allow the operation
; IDNO -means disallow the operation on this file, but continue with
;any other operations (eg. batch copy)
; IDCANCEL - means disallow the current operation and cancel any pending
;operations
;
; arguments to the CopyCallback
;hwnd - window to use for any UI
;wFunc - what operation is being done
;wFlags - and flags (FOF_*) set in the initial call to the file operation
;pszSrcFile - name of the source file
;dwSrcAttribs - file attributes of the source file
;pszDestFile - name of the destiation file (for move and renames)
;dwDestAttribs - file attributes of the destination file
;
;
;===========================================================================

;#ifndef FO_MOVE ;these need to be kept in sync with the ones in shellapi.h

; file operations

;FO_MOVE 	equ	0001h
;FO_COPY 	equ	0002h
;FO_DELETE 	equ	0003h
;FO_RENAME 	equ	0004h

;FOF_MULTIDESTFILES 	equ	0001h
;FOF_CONFIRMMOUSE 	equ	0002h
;FOF_SILENT 		equ	0004h	; don't create progress/report
;FOF_RENAMEONCOLLISION	equ	0008h
;FOF_NOCONFIRMATION 	equ	0010h	; Don't prompt the user.
;FOF_WANTMAPPINGHANDLE	equ	0020h	; Fill in SHFILEOPSTRUCT.hNameMappings

; Must be freed using SHFreeNameMappings

;FOF_ALLOWUNDO		equ	0040h
;FOF_FILESONLY		equ	0080h	; on *.*, do only files
;FOF_SIMPLEPROGRESS 	equ	0100h	; means don't show names of files
;FOF_NOCONFIRMMKDIR 	equ	0200h	; don't confirm making any needed dirs
;FOF_NOERRORUI		equ	0400h	; don't put up error UI

;typedef UINT FILEOP_FLAGS;

; printer operations

;PO_DELETE 	equ	0013h	; printer is being deleted
;PO_RENAME 	equ	0014h	; printer is being renamed
;PO_PORTCHANGE 	equ	0020h	; port this printer connected to is being changed

; if this id is set, the strings received by
; the copyhook are a doubly-null terminated
; list of strings.The first is the printer
; name and the second is the printer port.

;PO_REN_PORT 	equ	0034h	; PO_RENAME and PO_PORTCHANGE at same time.

; no POF_ flags currently defined

;typedef UINT PRINTEROP_FLAGS;

;#endif ; FO_MOVE

;#undefINTERFACE
;INTERFACE ICopyHookA

;DECLARE_INTERFACE_(ICopyHookA, IUnknown); sl
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD_(UINT,CopyCallback) (THIS_ HWND hwnd, UINT wFunc, UINT wFlags, LPCSTR pszSrcFile, DWORD dwSrcAttribs,
; LPCSTR pszDestFile, DWORD dwDestAttribs) PURE;
;};

;typedef ICopyHookA *LPCOPYHOOKA;

;#undefINTERFACE
;INTERFACE ICopyHookW

;DECLARE_INTERFACE_(ICopyHookW, IUnknown); sl
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD_(UINT,CopyCallback) (THIS_ HWND hwnd, UINT wFunc, UINT wFlags, LPCWSTR pszSrcFile, DWORD dwSrcAttribs,
; LPCWSTR pszDestFile, DWORD dwDestAttribs) PURE;
;};

;typedef ICopyHookW *LPCOPYHOOKW;

;#ifdef UNICODE
;ICopyHook 	equ	ICopyHookW
;ICopyHookVtbl 	equ	ICopyHookWVtbl
;LPCOPYHOOK	equ	LPCOPYHOOKW
;#else
ICopyHook 	equ	ICopyHookA
ICopyHookVtbl 	equ	ICopyHookAVtbl
LPCOPYHOOK	equ	LPCOPYHOOKA
;#endif

;===========================================================================
;
; IFileViewerSite Interface
;
;===========================================================================

;#undefINTERFACE
;INTERFACE IFileViewerSite

;DECLARE_INTERFACE(IFileViewerSite)
;{
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD(SetPinnedWindow) (THIS_ HWND hwnd) PURE;
;STDMETHOD(GetPinnedWindow) (THIS_ HWND *phwnd) PURE;
;};

;typedef IFileViewerSite * LPFILEVIEWERSITE;


;===========================================================================
;
; IFileViewer Interface
;
; Implemented in a FileViewer component object.Used to tell a
; FileViewer to PrintTo or to view, the latter happening though
; ShowInitialize and Show.The filename is always given to the
; viewer through IPersistFile.
;
;===========================================================================

;typedef struct
;{
; Stuff passed into viewer (in)
;DWORD cbSize; ; Size of structure for future expansion...
;HWND hwndOwner; ; who is the owner window.
;int iShow;; The show command

; Passed in and updated(in/Out)
;DWORD dwFlags;; flags
;RECT rect;; Where to create the window may have defaults
;LPUNKNOWN punkRel;; Relese this interface when window is visible

; Stuff that might be returned from viewer (out)
;OLECHAR strNewFile[MAX_PATH]; ; New File to view.

;} FVSHOWINFO, *LPFVSHOWINFO;

; Define File View Show Info Flags.

FVSIF_RECT	equ	00000001h	; The rect variable has valid data.
FVSIF_PINNED	equ	00000002h	; We should Initialize pinned

FVSIF_NEWFAILED 	equ	08000000h	; The new file passed back failed
; to be viewed.

FVSIF_NEWFILE 	equ	80000000h	; A new file to view has been returned
FVSIF_CANVIEWIT 	equ	40000000h	; The viewer can view it.

;#undefINTERFACE
;INTERFACE IFileViewerA

;DECLARE_INTERFACE(IFileViewerA)
;{
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD(ShowInitialize) (THIS_ LPFILEVIEWERSITE lpfsi) PURE;
;STDMETHOD(Show) (THIS_ LPFVSHOWINFO pvsi) PURE;
;STDMETHOD(PrintTo) (THIS_ LPSTR pszDriver, BOOL fSuppressUI) PURE;
;};

;typedef IFileViewerA * LPFILEVIEWERA;

;#undefINTERFACE
;INTERFACE IFileViewerW

;DECLARE_INTERFACE(IFileViewerW)
;{
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

;STDMETHOD(ShowInitialize) (THIS_ LPFILEVIEWERSITE lpfsi) PURE;
;STDMETHOD(Show) (THIS_ LPFVSHOWINFO pvsi) PURE;
;STDMETHOD(PrintTo) (THIS_ LPWSTR pszDriver, BOOL fSuppressUI) PURE;
;};

;typedef IFileViewerW * LPFILEVIEWERW;

;#ifdef UNICODE
;IFileViewer	equ	IFileViewerW
;LPFILEVIEWER	equ	LPFILEVIEWERW
;#else
IFileViewer	equ	IFileViewerA
LPFILEVIEWER	equ	LPFILEVIEWERA
;#endif



; CommandTarget ids. for shell doc view wedge
;enum {
;SHDVID_SETPROGRESSPOS,
;SHDVID_SETPROGRESSRANGE,
;SHDVID_SETSTATUSTEXT,; variantInbstr

;SHDVID_REFRESH,
;SHDVID_STOP,
;SHDVID_UPDATECOMMANDS, ;/ this forces a re-querystatus of the command targets.
 ;/ the arg in can specify a specific one to update or NULL for evrything
;SHDVID_SETTITLE,; variantIn bstr
;SHDVID_FINALTITLEAVAIL, ; variantIn bstr - sent after final SETTITLE is sent
;SHDVID_STARTLOAD, ; NULL for everything
;SHDVID_STOPLOAD ; NULL for everything
;#if MSOCT2
;,SHDVID_CCALLBACK,; callback to arbitrary C func
;SHDVID_MENUEXEC,; do menu command
;SHDVID_MENUQS ; query menu commands
;#endif
;};



;==========================================================================
;
; IShellBrowser/IShellView/IShellFolder interface
;
;These three interfaces are used when the shell communicates with
; name space extensions. The shell (explorer) provides IShellBrowser
; interface, and extensions implements IShellFolder and IShellView
; interfaces.
;
;==========================================================================


;--------------------------------------------------------------------------
;
; Command/menuitem IDs
;
;The explorer dispatches WM_COMMAND messages based on the range of
; command/menuitem IDs. All the IDs of menuitems that the view (right
; pane) inserts must be in FCIDM_SHVIEWFIRST/LAST (otherwise, the explorer
; won't dispatch them). The view should not deal with any menuitems
; in FCIDM_BROWSERFIRST/LAST (otherwise, it won't work with the future
; version of the shell).
;
;FCIDM_SHVIEWFIRST/LASTfor the right pane (IShellView)
;FCIDM_BROWSERFIRST/LAST for the explorer frame (IShellBrowser)
;FCIDM_GLOBAL/LAST for the explorer's submenu IDs
;
;--------------------------------------------------------------------------

FCIDM_SHVIEWFIRST 	equ	0000h
FCIDM_SHVIEWLAST	equ	7fffh
FCIDM_BROWSERFIRST	equ	a000h
FCIDM_BROWSERLAST 	equ	bf00h
FCIDM_GLOBALFIRST 	equ	8000h
FCIDM_GLOBALLAST		equ	9fffh

;
; Global submenu IDs and separator IDs
;
FCIDM_MENU_FILE		equ	(FCIDM_GLOBALFIRST + 0000h)
FCIDM_MENU_EDIT		equ	(FCIDM_GLOBALFIRST + 0040h)
FCIDM_MENU_VIEW		equ	(FCIDM_GLOBALFIRST + 0080h)
FCIDM_MENU_VIEW_SEP_OPTIONS	equ	(FCIDM_GLOBALFIRST + 0081h)
FCIDM_MENU_TOOLS	equ	(FCIDM_GLOBALFIRST + 00c0h)
FCIDM_MENU_TOOLS_SEP_GOTO	equ	(FCIDM_GLOBALFIRST + 00c1h)
FCIDM_MENU_HELP		equ	(FCIDM_GLOBALFIRST + 0100h)
FCIDM_MENU_FIND		equ	(FCIDM_GLOBALFIRST + 0140h)
FCIDM_MENU_EXPLORE	equ	(FCIDM_GLOBALFIRST + 0150h)
FCIDM_MENU_FAVORITES	equ	(FCIDM_GLOBALFIRST + 0170h)

;--------------------------------------------------------------------------
; control IDs known to the view
;--------------------------------------------------------------------------

FCIDM_TOOLBAR	equ	(FCIDM_BROWSERFIRST + 0)
FCIDM_STATUS	equ	(FCIDM_BROWSERFIRST + 1)


;--------------------------------------------------------------------------
;
; FOLDERSETTINGS
;
;FOLDERSETTINGS is a data structure that explorer passes from one folder
; view to another, when the user is browsing. It calls ISV::GetCurrentInfo
; member to get the current settings and pass it to ISV::CreateViewWindow
; to allow the next folder view "inherit" it. These settings assumes a
; particular UI (which the shell's folder view has), and shell extensions
; may or may not use those settings.
;
;--------------------------------------------------------------------------

;typedef LPBYTE LPVIEWSETTINGS;

; NB Bitfields.
; FWF_DESKTOP implies FWF_TRANSPARENT/NOCLIENTEDGE/NOSCROLL
;typedef enum
;{
;FWF_AUTOARRANGE = 0x0001,
;FWF_ABBREVIATEDNAMES =0x0002,
;FWF_SNAPTOGRID =0x0004,
;FWF_OWNERDATA = 0x0008,
;FWF_BESTFITWINDOW = 0x0010,
;FWF_DESKTOP = 0x0020,
;FWF_SINGLESEL = 0x0040,
;FWF_NOSUBFOLDERS =0x0080,
;FWF_TRANSPARENT=0x0100,
;FWF_NOCLIENTEDGE =0x0200,
;FWF_NOSCROLL =0x0400,
;FWF_ALIGNLEFT=0x0800,
;FWF_SINGLECLICKACTIVATE=0x8000; TEMPORARY -- NO UI FOR THIS
;} FOLDERFLAGS;

;typedef enum
;{
;FVM_ICON =1,
;FVM_SMALLICON = 2,
;FVM_LIST =3,
;FVM_DETAILS = 4,
;} FOLDERVIEWMODE;

;typedef struct
;{
;UINT ViewMode; ; View mode (FOLDERVIEWMODE values)
;UINT fFlags; ; View options (FOLDERFLAGS bits)
;} FOLDERSETTINGS, *LPFOLDERSETTINGS;

;typedef const FOLDERSETTINGS * LPCFOLDERSETTINGS;


;--------------------------------------------------------------------------
;
; Interface: IShellBrowser
;
;IShellBrowser interface is the interface that is provided by the shell
; explorer/folder frame window. When it creates the "contents pane" of
; a shell folder (which provides IShellFolder interface), it calls its
; CreateViewObject member function to create an IShellView object. Then,
; it calls its CreateViewWindow member to create the "contents pane"
; window. The pointer to the IShellBrowser interface is passed to
; the IShellView object as a parameter to this CreateViewWindow member
; function call.
;
;+--------------------------+<-- Explorer window
;| [] Explorer|
;|--------------------------+ IShellBrowser
;| File Edit View ..|
;|--------------------------|
;|| |
;||<-------- Content pane
;|| |
;|| | IShellView
;|| |
;|| |
;+--------------------------+
;
;
;
; [Member functions]
;
;
; IShellBrowser::GetWindow(phwnd)
;
; Inherited from IOleWindow::GetWindow.
;
;
; IShellBrowser::ContextSensitiveHelp(fEnterMode)
;
; Inherited from IOleWindow::ContextSensitiveHelp.
;
;
; IShellBrowser::InsertMenusSB(hmenuShared, lpMenuWidths)
;
; Similar to the IOleInPlaceFrame::InsertMenus. The explorer will put
;"File" and "Edit" pulldown in the File menu group, "View" and "Tools"
;in the Container menu group and "Help" in the Window menu group. Each
;pulldown menu will have a uniqu ID, FCIDM_MENU_FILE/EDIT/VIEW/TOOLS/HELP.
;The view is allowed to insert menuitems into those sub-menus by those
;IDs must be between FCIDM_SHVIEWFIRST and FCIDM_SHVIEWLAST.
;
;
; IShellBrowser::SetMenuSB(hmenuShared, holemenu, hwndActiveObject)
;
; Similar to the IOleInPlaceFrame::SetMenu. The explorer ignores the
;holemenu parameter (reserved for future enhancement)and performs
;menu-dispatch based on the menuitem IDs (see the description above).
;It is important to note that the explorer will add different
;set of menuitems depending on whether the view has a focus or not.
;Therefore, it is very important to call ISB::OnViewWindowActivate
;whenever the view window (or its children) gets the focus.
;
;
; IShellBrowser::RemoveMenusSB(hmenuShared)
;
; Same as the IOleInPlaceFrame::RemoveMenus.
;
;
; IShellBrowser::SetStatusTextSB(lpszStatusText)
;
; Same as the IOleInPlaceFrame::SetStatusText. It is also possible to
;send messages directly to the status window via SendControlMsg.
;
;
; IShellBrowser::EnableModelessSB(fEnable)
;
; Same as the IOleInPlaceFrame::EnableModeless.
;
;
; IShellBrowser::TranslateAcceleratorSB(lpmsg, wID)
;
; Same as the IOleInPlaceFrame::TranslateAccelerator, but will be
;never called because we don't support EXEs (i.e., the explorer has
;the message loop). This member function is defined here for possible
;future enhancement.
;
;
; IShellBrowser::BrowseObject(pidl, wFlags)
;
; The view calls this member to let shell explorer browse to another
;folder. The pidl and wFlags specifies the folder to be browsed.
;
;Following three flags specifies whether it creates another window or not.
; SBSP_SAMEBROWSER-- Browse to another folder with the same window.
; SBSP_NEWBROWSER -- Creates another window for the specified folder.
; SBSP_DEFBROWSER -- Default behavior (respects the view option).
;
;Following three flags specifies open, explore, or default mode. These .
;are ignored if SBSP_SAMEBROWSER or (SBSP_DEFBROWSER && (single window .
;browser || explorer))..
; SBSP_OPENMODE -- Use a normal folder window
; SBSP_EXPLOREMODE-- Use an explorer window
; SBSP_DEFMODE-- Use the same as the current window
;
;Following three flags specifies the pidl.
; SBSP_ABSOLUTE -- pidl is an absolute pidl (relative from desktop)
; SBSP_RELATIVE -- pidl is relative from the current folder.
; SBSP_PARENT -- Browse the parent folder (ignores the pidl)
;
;
; IShellBrowser::GetViewStateStream(grfMode, ppstm)
;
; The browser returns an IStream interface as the storage for view
;specific state information.
;
; grfMode -- Specifies the read/write access (STGM_READ/WRITE/READWRITE)
; ppstm -- Specifies the LPSTREAM variable to be filled.
;
;
; IShellBrowser::GetControlWindow(id, phwnd)
;
; The shell view may call this member function to get the window handle
;of Explorer controls (toolbar or status winodw -- FCW_TOOLBAR or
;FCW_STATUS).
;
;
; IShellBrowser::SendControlMsg(id, uMsg, wParam, lParam, pret)
;
; The shell view calls this member function to send control messages to
;one of Explorer controls (toolbar or status window -- FCW_TOOLBAR or
;FCW_STATUS).
;
;
; IShellBrowser::QueryActiveShellView(IShellView * ppshv)
;
; This member returns currently activated (displayed) shellview object.
;A shellview never need to call this member function.
;
;
; IShellBrowser::OnViewWindowActive(pshv)
;
; The shell view window calls this member function when the view window
;(or one of its children) got the focus. It MUST call this member before
;calling IShellBrowser::InsertMenus, because it will insert different
;set of menu items depending on whether the view has the focus or not.
;
;
; IShellBrowser::SetToolbarItems(lpButtons, nButtons, uFlags)
;
; The view calls this function to add toolbar items to the exporer's
;toolbar. "lpButtons" and "nButtons" specifies the array of toolbar
;items. "uFlags" must be one of FCT_MERGE, FCT_CONFIGABLE, FCT_ADDTOEND.
;
;-------------------------------------------------------------------------

;#undefINTERFACE
;INTERFACE IShellBrowser

;
; Values for wFlags parameter of ISB::BrowseObject() member.
;
SBSP_DEFBROWSER		equ	0000h
SBSP_SAMEBROWSER 	equ	0001h
SBSP_NEWBROWSER	equ	0002h

SBSP_DEFMODE 		equ	0000h
SBSP_OPENMODE		equ	0010h
SBSP_EXPLOREMODE 	equ	0020h

SBSP_ABSOLUTE		equ	0000h
SBSP_RELATIVE		equ	1000h
SBSP_PARENT		equ	2000h

SBSP_INITIATEDBYHLINKFRAME	equ	80000000h
SBSP_REDIRECT 		equ	40000000h

;
; Values for id parameter of ISB::GetWindow/SendControlMsg members.
;
; WARNING:
;Any shell extensions which sends messages to those control windows
; might not work in the future version of windows. If you really need
; to send messages to them, (1) don't assume that those control window
; always exist (i.e. GetControlWindow may fail) and (2) verify the window
; class of the window before sending any messages.
;
FCW_STATUS	equ	0001h
FCW_TOOLBAR 	equ	0002h
FCW_TREE	equ	0003h

;
; Values for uFlags paremeter of ISB::SetToolbarItems member.
;
FCT_MERGE 	equ	0001h
FCT_CONFIGABLE	equ	0002h
FCT_ADDTOEND	equ	0004h


;DECLARE_INTERFACE_(IShellBrowser, IOleWindow)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IOleWindow methods ***
;STDMETHOD(GetWindow) (THIS_ HWND * lphwnd) PURE;
;STDMETHOD(ContextSensitiveHelp) (THIS_ BOOL fEnterMode) PURE;

; *** IShellBrowser methods *** (same as IOleInPlaceFrame)
;STDMETHOD(InsertMenusSB) (THIS_ HMENU hmenuShared,
;LPOLEMENUGROUPWIDTHS lpMenuWidths) PURE;
;STDMETHOD(SetMenuSB) (THIS_ HMENU hmenuShared, HOLEMENU holemenuReserved,
;HWND hwndActiveObject) PURE;
;STDMETHOD(RemoveMenusSB) (THIS_ HMENU hmenuShared) PURE;
;STDMETHOD(SetStatusTextSB) (THIS_ LPCOLESTR lpszStatusText) PURE;
;STDMETHOD(EnableModelessSB) (THIS_ BOOL fEnable) PURE;
;STDMETHOD(TranslateAcceleratorSB) (THIS_ LPMSG lpmsg, WORD wID) PURE;

; *** IShellBrowser methods ***
;STDMETHOD(BrowseObject)(THIS_ LPCITEMIDLIST pidl, UINT wFlags) PURE;
;STDMETHOD(GetViewStateStream)(THIS_ DWORD grfMode,
;LPSTREAM*ppStrm) PURE;
;STDMETHOD(GetControlWindow)(THIS_ UINT id, HWND * lphwnd) PURE;
;STDMETHOD(SendControlMsg)(THIS_ UINT id, UINT uMsg, WPARAM wParam,
;LPARAM lParam, LRESULT * pret) PURE;
;STDMETHOD(QueryActiveShellView)(THIS_ struct IShellView ** ppshv) PURE;
;STDMETHOD(OnViewWindowActive)(THIS_ struct IShellView * ppshv) PURE;
;STDMETHOD(SetToolbarItems)(THIS_ LPTBBUTTON lpButtons, UINT nButtons,
;UINT uFlags) PURE;
;};

;typedef IShellBrowser * LPSHELLBROWSER;

;enum {
;SBSC_HIDE = 0,
;SBSC_SHOW = 1,
;SBSC_TOGGLE = 2,
;SBSC_QUERY =3
;};

; CommandTarget ids.
;enum {
;SBCMDID_ENABLESHOWTREE,
;SBCMDID_SHOWCONTROL,; variant vt_i4 = loword = FCW_* hiword = SBSC_*
;SBCMDID_CANCELNAVIGATION, ; cancel last navigation
;SBCMDID_MAYSAVECHANGES, ; about to close and may save changes
;SBCMDID_SETHLINKFRAME,; variant vt_i4 = phlinkframe
;SBCMDID_ENABLESTOP, ; variant vt_bool = fEnable
;SBCMDID_OPTIONS,; the view.options page
;};


;-------------------------------------------------------------------------
; ICommDlgBrowser interface
;
;ICommDlgBrowser interface is the interface that is provided by the new
; common dialog window to hook and modify the behavior of IShellView.When
; a default view is created, it queries its parent IShellBrowser for the
; ICommDlgBrowser interface.If supported, it calls out to that interface
; in several cases that need to behave differently in a dialog.
;
; Member functions:
;
;ICommDlgBrowser::OnDefaultCommand()
;Called when the user double-clicks in the view or presses Enter.The
; browser should return S_OK if it processed the action itself, S_FALSE
; to let the view perform the default action.
;
;ICommDlgBrowser::OnStateChange(ULONG uChange)
;Called when some states in the view change.'uChange' is one of the
; CDBOSC_* values.This call is made after the state (selection, focus,
; etc) has changed.There is no return value.
;
;ICommDlgBrowser::IncludeObject(LPCITEMIDLIST pidl)
;Called when the view is enumerating objects.'pidl' is a relative
; IDLIST.The browser should return S_OK to include the object in the
; view, S_FALSE to hide it
;
;-------------------------------------------------------------------------

;#undefINTERFACE
;INTERFACE ICommDlgBrowser

CDBOSC_SETFOCUS 	equ	00000000h
CDBOSC_KILLFOCUS	equ	00000001h
CDBOSC_SELCHANGE	equ	00000002h
CDBOSC_RENAME 		equ	00000003h

;DECLARE_INTERFACE_(ICommDlgBrowser, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** ICommDlgBrowser methods ***
;STDMETHOD(OnDefaultCommand) (THIS_ struct IShellView * ppshv) PURE;
;STDMETHOD(OnStateChange) (THIS_ struct IShellView * ppshv,
;ULONG uChange) PURE;
;STDMETHOD(IncludeObject) (THIS_ struct IShellView * ppshv,
;LPCITEMIDLIST pidl) PURE;
;};

;typedef ICommDlgBrowser * LPCOMMDLGBROWSER;


;==========================================================================
;
; Interface: IShellView
;
; IShellView::GetWindow(phwnd)
;
; Inherited from IOleWindow::GetWindow.
;
;
; IShellView::ContextSensitiveHelp(fEnterMode)
;
; Inherited from IOleWindow::ContextSensitiveHelp.
;
;
; IShellView::TranslateAccelerator(lpmsg)
;
; Similar to IOleInPlaceActiveObject::TranlateAccelerator. The explorer
;calls this function BEFORE any other translation. Returning S_OK
;indicates that the message was translated (eaten) and should not be
;translated or dispatched by the explorer.
;
;
; IShellView::EnableModeless(fEnable)
; Similar to IOleInPlaceActiveObject::EnableModeless.
;
;
; IShellView::UIActivate(uState)
;
; The explorer calls this member function whenever the activation
;state of the view window is changed by a certain event that is
;NOT caused by the shell view itself.
;
; SVUIA_DEACTIVATE will be passed when the explorer is about to
;destroy the shell view window; the shell view is supposed to remove
;all the extended UIs (typically merged menu and modeless popup windows).
;
; SVUIA_ACTIVATE_NOFOCUS will be passsed when the shell view is losing
;the input focus or the shell view has been just created without the
;input focus; the shell view is supposed to set menuitems appropriate
;for non-focused state (no selection specific items should be added).
;
; SVUIA_ACTIVATE_FOCUS will be passed when the explorer has just
;created the view window with the input focus; the shell view is
;supposed to set menuitems appropriate for focused state.
;
; SVUIA_INPLACEACTIVATE(new) will be passed when the shell view is opened
;within an ActiveX control, which is not a UI active. In this case,
;the shell view should not merge menus or put toolbas. To be compatible
;with Win95 client, we don't pass this value unless the view supports
;IShellView2.
;
; The shell view should not change focus within this member function.
;The shell view should not hook the WM_KILLFOCUS message to remerge
;menuitems. However, the shell view typically hook the WM_SETFOCUS
;message, and re-merge the menu after calling IShellBrowser::
;OnViewWindowActivated.
;
;
; IShellView::Refresh()
;
; The explorer calls this member when the view needs to refresh its
;contents (such as when the user hits F5 key).
;
;
; IShellView::CreateViewWindow
;
; This member creates the view window (right-pane of the explorer or the
;client window of the folder window).
;
;
; IShellView::DestroyViewWindow
;
; This member destroys the view window.
;
;
; IShellView::GetCurrentInfo
;
; This member returns the folder settings.
;
;
; IShellView::AddPropertySHeetPages
;
; The explorer calls this member when it is opening the option property
;sheet. This allows the view to add additional pages to it.
;
;
; IShellView::SaveViewState()
;
; The explorer calls this member when the shell view is supposed to
;store its view settings. The shell view is supposed to get a view
;stream by calling IShellBrowser::GetViewStateStream and store the
;current view state into that stream.
;
;
; IShellView::SelectItem(pidlItem, uFlags)
;
; The explorer calls this member to change the selection state of
;item(s) within the shell view window.If pidlItem is NULL and uFlags
;is SVSI_DESELECTOTHERS, all items should be deselected.
;
;-------------------------------------------------------------------------

;#undefINTERFACE
;INTERFACE IShellView

;
; shellview select item flags
;
SVSI_DESELECT 		equ	0000h
SVSI_SELECT 		equ	0001h
SVSI_EDIT 		equ	0003h	; includes select
SVSI_DESELECTOTHERS 	equ	0004h
SVSI_ENSUREVISIBLE	equ	0008h
SVSI_FOCUSED		equ	0010h

;
; shellview get item object flags
;
SVGIO_BACKGROUND	equ	00000000h
SVGIO_SELECTION 		equ	00000001h
SVGIO_ALLVIEW 		equ	00000002h

;
; uState values for IShellView::UIActivate
;
;typedef enum {
;SVUIA_DEACTIVATE = 0,
;SVUIA_ACTIVATE_NOFOCUS = 1,
;SVUIA_ACTIVATE_FOCUS = 2,
;SVUIA_INPLACEACTIVATE= 3; new flag for IShellView2
;} SVUIA_STATUS;

;DECLARE_INTERFACE_(IShellView, IOleWindow)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IOleWindow methods ***
;STDMETHOD(GetWindow) (THIS_ HWND * lphwnd) PURE;
;STDMETHOD(ContextSensitiveHelp) (THIS_ BOOL fEnterMode) PURE;

; *** IShellView methods ***
;STDMETHOD(TranslateAccelerator) (THIS_ LPMSG lpmsg) PURE;
;#ifdef _FIX_ENABLEMODELESS_CONFLICT
;STDMETHOD(EnableModelessSV) (THIS_ BOOL fEnable) PURE;
;#else
;STDMETHOD(EnableModeless) (THIS_ BOOL fEnable) PURE;
;#endif
;STDMETHOD(UIActivate) (THIS_ UINT uState) PURE;
;STDMETHOD(Refresh) (THIS) PURE;

;STDMETHOD(CreateViewWindow)(THIS_ IShellView*lpPrevView,
;LPCFOLDERSETTINGS lpfs, IShellBrowser* psb,
;RECT * prcView, HWND*phWnd) PURE;
;STDMETHOD(DestroyViewWindow)(THIS) PURE;
;STDMETHOD(GetCurrentInfo)(THIS_ LPFOLDERSETTINGS lpfs) PURE;
;STDMETHOD(AddPropertySheetPages)(THIS_ DWORD dwReserved,
;LPFNADDPROPSHEETPAGE lpfn, LPARAM lparam) PURE;
;STDMETHOD(SaveViewState)(THIS) PURE;
;STDMETHOD(SelectItem)(THIS_ LPCITEMIDLIST pidlItem, UINT uFlags) PURE;
;STDMETHOD(GetItemObject)(THIS_ UINT uItem, REFIID riid,
;LPVOID *ppv) PURE;
;};

;typedef IShellView *LPSHELLVIEW;

;typedef GUID SHELLVIEWID;

;SV2GV_CURRENTVIEW ((UINT)-1)
;SV2GV_DEFAULTVIEW ((UINT)-2)

;typedef struct _SV2CVW2_PARAMS
;{
;DWORD cbSize;

;IShellView *psvPrev;
;FOLDERSETTINGS const *pfs;
;IShellBrowser *psbOwner;
;RECT *prcView;
;SHELLVIEWID const *pvid;

;HWND hwndView;
;} SV2CVW2_PARAMS;
;typedef SV2CVW2_PARAMS *LPSV2CVW2_PARAMS;

;#undefINTERFACE
;INTERFACE IShellView2

;DECLARE_INTERFACE_(IShellView2, IShellView)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IOleWindow methods ***
;STDMETHOD(GetWindow) (THIS_ HWND * lphwnd) PURE;
;STDMETHOD(ContextSensitiveHelp) (THIS_ BOOL fEnterMode) PURE;

; *** IShellView methods ***
;STDMETHOD(TranslateAccelerator) (THIS_ LPMSG lpmsg) PURE;
;#ifdef _FIX_ENABLEMODELESS_CONFLICT
;STDMETHOD(EnableModelessSV) (THIS_ BOOL fEnable) PURE;
;#else
;STDMETHOD(EnableModeless) (THIS_ BOOL fEnable) PURE;
;#endif
;STDMETHOD(UIActivate) (THIS_ UINT uState) PURE;
;STDMETHOD(Refresh) (THIS) PURE;

;STDMETHOD(CreateViewWindow)(THIS_ IShellView*lpPrevView,
;LPCFOLDERSETTINGS lpfs, IShellBrowser* psb,
;RECT * prcView, HWND*phWnd) PURE;
;STDMETHOD(DestroyViewWindow)(THIS) PURE;
;STDMETHOD(GetCurrentInfo)(THIS_ LPFOLDERSETTINGS lpfs) PURE;
;STDMETHOD(AddPropertySheetPages)(THIS_ DWORD dwReserved,
;LPFNADDPROPSHEETPAGE lpfn, LPARAM lparam) PURE;
;STDMETHOD(SaveViewState)(THIS) PURE;
;STDMETHOD(SelectItem)(THIS_ LPCITEMIDLIST pidlItem, UINT uFlags) PURE;
;STDMETHOD(GetItemObject)(THIS_ UINT uItem, REFIID riid,
;LPVOID *ppv) PURE;

; *** IShellView2 methods ***
;STDMETHOD(GetView)(THIS_ SHELLVIEWID* pvid, ULONG uView) PURE;
;STDMETHOD(CreateViewWindow2)(THIS_ LPSV2CVW2_PARAMS lpParams) PURE;
;};

;-------------------------------------------------------------------------
;
; struct STRRET
;
; structure for returning strings from IShellFolder member functions
;
;-------------------------------------------------------------------------

STRRET_WSTR 	equ	0000h	; Use STRRET.pOleStr
STRRET_OFFSET 	equ	0001h	; Use STRRET.uOffset to Ansi
STRRET_CSTR 	equ	0002h	; Use STRRET.cStr


;typedef struct _STRRET
;{
;UINT uType; ; One of the STRRET_* values
;union
;{
;LPWSTRpOleStr;; OLESTR that will be freed
;LPSTR pStr; ; ANSI string that will be freed (needed?)
;UINTuOffset;; Offset into SHITEMID
;charcStr[MAX_PATH]; ; Buffer to fill in (ANSI)
;} DUMMYUNIONNAME;
;} STRRET, *LPSTRRET;


;-------------------------------------------------------------------------
;
; SHGetPathFromIDList
;
;This function assumes the size of the buffer (MAX_PATH). The pidl
; should point to a file system object.
;
;-------------------------------------------------------------------------

SHGetPathFromIDListA	proto	:QWORD, :QWORD
SHGetPathFromIDListW	proto	:QWORD, :QWORD

ifdef UNICODE
SHGetPathFromIDList	equ	SHGetPathFromIDListW
else
SHGetPathFromIDList	equ	SHGetPathFromIDListA
endif


;-------------------------------------------------------------------------
;
; SHGetSpecialFolderLocation
;
;Caller should call SHFree to free the returned pidl.
;
;-------------------------------------------------------------------------
;
; registry entries for special paths are kept in :
;REGSTR_PATH_SPECIAL_FOLDERSREGSTR_PATH_EXPLORER TEXT("\\Shell Folders")


CSIDL_DESKTOP 		equ	0000h
CSIDL_PROGRAMS		equ	0002h
CSIDL_CONTROLS		equ	0003h
CSIDL_PRINTERS		equ	0004h
CSIDL_PERSONAL		equ	0005h
CSIDL_FAVORITES 		equ	0006h
CSIDL_STARTUP 		equ	0007h
CSIDL_RECENT		equ	0008h
CSIDL_SENDTO		equ	0009h
CSIDL_BITBUCKET 		equ	000Ah
CSIDL_STARTMENU 	equ	000Bh
CSIDL_DESKTOPDIRECTORY	equ	0010h
CSIDL_DRIVES		equ	0011h
CSIDL_NETWORK 		equ	0012h
CSIDL_NETHOOD 		equ	0013h
CSIDL_FONTS 		equ	0014h
CSIDL_TEMPLATES 	equ	0015h
CSIDL_COMMON_STARTMENU	equ	0016h
CSIDL_COMMON_PROGRAMS 	equ	0017h
CSIDL_COMMON_STARTUP	equ	0018h
CSIDL_COMMON_DESKTOPDIRECTORY equ	0019h
CSIDL_APPDATA 		equ	001Ah
CSIDL_PRINTHOOD 	equ	001Bh

; new shell csidl's

CSIDL_MYDOCUMENTS 	equ	000ch	; logical "My Documents" desktop icon
CSIDL_MYMUSIC	 	equ	000dh	; "My Music" folder
CSIDL_MYVIDEO 		equ	000eh	; "My Videos" folder
CSIDL_LOCAL_APPDATA 	equ	001ch	; <user name>\Local Settings\Applicaiton Data (non roaming)
CSIDL_ALTSTARTUP	equ	001dh	; non localized startup
CSIDL_COMMON_ALTSTARTUP 	equ	001eh	; non localized common startup
CSIDL_COMMON_FAVORITES	equ	001fh
CSIDL_INTERNET_CACHE	equ	0020h
CSIDL_COOKIES 		equ	0021h
CSIDL_HISTORY 		equ	0022h
CSIDL_COMMON_APPDATA	equ	0023h	; All Users\Application Data
CSIDL_WINDOWS 		equ	0024h	; GetWindowsDirectory()
CSIDL_SYSTEM		equ	0025h	; GetSystemDirectory()
CSIDL_PROGRAM_FILES 	equ	0026h	; C:\Program Files
CSIDL_MYPICTURES	equ	0027h	; C:\Program Files\My Pictures
CSIDL_PROFILE 		equ	0028h	; USERPROFILE
CSIDL_SYSTEMX86 	equ	0029h	; x86 system directory on RISC
CSIDL_PROGRAM_FILESX86	equ	002ah	; x86 C:\Program Files on RISC
CSIDL_PROGRAM_FILES_COMMON	equ	002bh	; C:\Program Files\Common
CSIDL_PROGRAM_FILES_COMMONX86 	equ	002ch	; x86 Program Files\Common on RISC
CSIDL_COMMON_TEMPLATES	equ	002dh	; All Users\Templates
CSIDL_COMMON_DOCUMENTS	equ	002eh	; All Users\Documents
CSIDL_COMMON_ADMINTOOLS 	equ	002fh	; All Users\Start Menu\Programs\Administrative Tools
CSIDL_ADMINTOOLS	equ	0030h	; <user name>\Start Menu\Programs\Administrative Tools
CSIDL_CONNECTIONS 	equ	0031h	; Network and Dial-up Connections
CSIDL_COMMON_MUSIC	equ	0035h	; All Users\My Music
CSIDL_COMMON_PICTURES 	equ	0036h	; All Users\My Pictures
CSIDL_COMMON_VIDEO	equ	0037h	; All Users\My Video
CSIDL_RESOURCES 	equ	0038h	; Resource Direcotry
CSIDL_RESOURCES_LOCALIZED 	equ	0039h	; Localized Resource Direcotry
CSIDL_COMMON_OEM_LINKS	equ	003ah	; Links to All Users OEM specific apps
CSIDL_CDBURN_AREA 	equ	003bh	; USERPROFILE\Local Settings\Application Data\Microsoft\CD Burning
; unused 		equ	003ch
CSIDL_COMPUTERSNEARME 	equ	003dh	; Computers Near Me (computered from Workgroup membership)

SHGetSpecialFolderLocation	proto	:QWORD, :DWORD, :QWORD
SHCreateDirectoryExA	proto	:QWORD, :QWORD, :QWORD
SHCreateDirectoryExW	proto	:QWORD, :QWORD, :QWORD

;-------------------------------------------------------------------------
;
; SHBrowseForFolder API
;
;-------------------------------------------------------------------------

;typedef int (CALLBACK* BFFCALLBACK)(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	IFDEF	UNICODE
BROWSEINFO	equ	BROWSEINFOW
SHCreateDirectoryEx	equ	SHCreateDirectoryExW
	ELSE
BROWSEINFO	equ	BROWSEINFOA
SHCreateDirectoryEx	equ	SHCreateDirectoryExA
	ENDIF

BROWSEINFOA	struc
 hwndOwner	dq	?
 pidlRoot	dq	?
 lpszDisplay	dq	?
 lpszTitle	dq	?
 ulFlags	dd	?
	dd	?
 lpfn	dq	?
 lParam	dq	?
 iImage	dd	?
	dd	?
BROWSEINFOA	ends

BROWSEINFOW	STRUC
 hwndOwner	dq	?
 pidlRoot	dq	?
 lpszDisplay	dq	?
 lpszTitle	dq	?
 ulFlags	dd	?
	dd	?
 lpfn	dq	?
 lParam	dq	?
 iImage	dd	?
	dd	?
BROWSEINFOW	ENDS


; Browsing for directory.

BIF_RETURNONLYFSDIRS 	equ	0001h	; For finding a folder to start document searching
BIF_DONTGOBELOWDOMAIN	equ	0002h	; For starting the Find Computer
BIF_STATUSTEXT 		equ	0004h
BIF_RETURNFSANCESTORS	equ	0008h

BIF_BROWSEFORCOMPUTER	equ	1000h	; Browsing for Computers.
BIF_BROWSEFORPRINTER 	equ	2000h	; Browsing for Printers
BIF_BROWSEINCLUDEFILES 	equ	4000h	; Browsing for Everything

; message from browser
BFFM_INITIALIZED		equ	1
BFFM_SELCHANGED		equ	2

; messages to browser
BFFM_SETSTATUSTEXTA 	equ	(WM_USER + 100)
BFFM_ENABLEOK		equ	(WM_USER + 101)
BFFM_SETSELECTIONA	equ	(WM_USER + 102)
BFFM_SETSELECTIONW	equ	(WM_USER + 103)
BFFM_SETSTATUSTEXTW	equ	(WM_USER + 104)


SHBrowseForFolderA	proto	:QWORD
SHBrowseForFolderW	proto	:QWORD

		IFDEF	UNICODE
SHBrowseForFolder	equ	SHBrowseForFolderW
BFFM_SETSTATUSTEXT	equ	BFFM_SETSTATUSTEXTW
BFFM_SETSELECTION	equ	BFFM_SETSELECTIONW
		ELSE
SHBrowseForFolder		equ	SHBrowseForFolderA
BFFM_SETSTATUSTEXT	equ	BFFM_SETSTATUSTEXTA
BFFM_SETSELECTION	equ	BFFM_SETSELECTIONA
		ENDIF

;-------------------------------------------------------------------------
;
; SHLoadInProc
;
; When this function is called, the shell calls CoCreateInstance
;(or equivalent) with CLSCTX_INPROC_SERVER and the specified CLSID
;from within the shell's process and release it immediately.
;
;-------------------------------------------------------------------------

;WINSHELLAPI HRESULT WINAPI SHLoadInProc(REFCLSID rclsid);


;-------------------------------------------------------------------------
;
; IEnumIDList interface
;
;IShellFolder::EnumObjects member returns an IEnumIDList object.
;
;-------------------------------------------------------------------------

;typedef struct IEnumIDList*LPENUMIDLIST;

;#undefINTERFACE
;INTERFACE IEnumIDList

;DECLARE_INTERFACE_(IEnumIDList, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IEnumIDList methods ***
;STDMETHOD(Next)(THIS_ ULONG celt,
;LPITEMIDLIST *rgelt,
;ULONG *pceltFetched) PURE;
;STDMETHOD(Skip)(THIS_ ULONG celt) PURE;
;STDMETHOD(Reset) (THIS) PURE;
;STDMETHOD(Clone) (THIS_ IEnumIDList **ppenum) PURE;
;};


;-------------------------------------------------------------------------
;
; IShellFolder interface
;
;
; [Member functions]
;
; IShellFolder::BindToObject(pidl, pbc, riid, ppvOut)
; This function returns an instance of a sub-folder which is specified
;by the IDList (pidl).
;
; IShellFolder::BindToStorage(pidl, pbc, riid, ppvObj)
; This function returns a storage instance of a sub-folder which is
;specified by the IDList (pidl). The shell never calls this member
;function in the first release of Win95.
;
; IShellFolder::CompareIDs(lParam, pidl1, pidl2)
; This function compares two IDLists and returns the result. The shell
;explorer always passes 0 as lParam, which indicates "sort by name".
;It should return 0 (as CODE of the scode), if two id indicates the
;same object; negative value if pidl1 should be placed before pidl2;
;positive value if pidl2 should be placed before pidl1.
;
; IShellFolder::CreateViewObject(hwndOwner, riid, ppvOut)
; This function creates a view object of the folder itself. The view
;object is a difference instance from the shell folder object.
; "hwndOwner" can be usedas the owner window of its dialog box or
;menu during the lifetime of the view object.
;instance which has only one reference count. The explorer may create
;more than one instances of view object from one shell folder object
;and treat them as separate instances.
;
; IShellFolder::GetAttributesOf(cidl, apidl, prgfInOut)
; This function returns the attributes of specified objects in that
;folder. "cidl" and "apidl" specifies objects. "apidl" contains only
;simple IDLists. The explorer initializes *prgfInOut with a set of
;flags to be evaluated. The shell folder may optimize the operation
;by not returning unspecified flags.
;
; IShellFolder::GetUIObjectOf(hwndOwner, cidl, apidl, riid, prgfInOut, ppvOut)
; This function creates a UI object to be used for specified objects.
;The shell explorer passes either IID_IDataObject (for transfer operation)
;or IID_IContextMenu (for context menu operation) as riid.
;
; IShellFolder::GetDisplayNameOf
; This function returns the display name of the specified object.
;If the ID contains the display name (in the locale character set),
;it returns the offset to the name. Otherwise, it returns a pointer
;to the display name string (UNICODE), which is allocated by the
;task allocator, or fills in a buffer.
;
; IShellFolder::SetNameOf
; This function sets the display name of the specified object.
;If it changes the ID as well, it returns the new ID which is
;alocated by the task allocator.
;
;-------------------------------------------------------------------------

;#undefINTERFACE
;INTERFACE IShellFolder

; IShellFolder::GetDisplayNameOf/SetNameOf uFlags
;typedef enum tagSHGDN
;{
;SHGDN_NORMAL= 0,; default (display purpose)
;SHGDN_INFOLDER= 1,; displayed under a folder (relative)
;SHGDN_FORADDRESSBAR = 0x4000, ; for displaying in the address (drives dropdown) bar
;SHGDN_FORPARSING= 0x8000, ; for ParseDisplayName or path
;} SHGNO;

; IShellFolder::EnumObjects
;typedef enum tagSHCONTF
;{
;SHCONTF_FOLDERS = 32, ; for shell browser
;SHCONTF_NONFOLDERS= 64, ; for default view
;SHCONTF_INCLUDEHIDDEN = 128,; for hidden/system objects
;} SHCONTF;

;DECLARE_INTERFACE_(IShellFolder, IUnknown)
;{
; *** IUnknown methods ***
;STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD_(ULONG,AddRef) (THIS)PURE;
;STDMETHOD_(ULONG,Release) (THIS) PURE;

; *** IShellFolder methods ***
;STDMETHOD(ParseDisplayName) (THIS_ HWND hwndOwner,
;LPBC pbcReserved, LPOLESTR lpszDisplayName,
;ULONG * pchEaten, LPITEMIDLIST * ppidl, ULONG *pdwAttributes) PURE;

;STDMETHOD(EnumObjects) ( THIS_ HWND hwndOwner, DWORD grfFlags, LPENUMIDLIST * ppenumIDList) PURE;

;STDMETHOD(BindToObject) (THIS_ LPCITEMIDLIST pidl, LPBC pbcReserved,
; REFIID riid, LPVOID * ppvOut) PURE;
;STDMETHOD(BindToStorage)(THIS_ LPCITEMIDLIST pidl, LPBC pbcReserved,
; REFIID riid, LPVOID * ppvObj) PURE;
;STDMETHOD(CompareIDs) (THIS_ LPARAM lParam, LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2) PURE;
;STDMETHOD(CreateViewObject) (THIS_ HWND hwndOwner, REFIID riid, LPVOID * ppvOut) PURE;
;STDMETHOD(GetAttributesOf)(THIS_ UINT cidl, LPCITEMIDLIST * apidl,
;ULONG * rgfInOut) PURE;
;STDMETHOD(GetUIObjectOf)(THIS_ HWND hwndOwner, UINT cidl, LPCITEMIDLIST * apidl,
; REFIID riid, UINT * prgfInOut, LPVOID * ppvOut) PURE;
;STDMETHOD(GetDisplayNameOf) (THIS_ LPCITEMIDLIST pidl, DWORD uFlags, LPSTRRET lpName) PURE;
;STDMETHOD(SetNameOf)(THIS_ HWND hwndOwner, LPCITEMIDLIST pidl,
; LPCOLESTR lpszName, DWORD uFlags,
; LPITEMIDLIST * ppidlOut) PURE;
;};

;typedef IShellFolder * LPSHELLFOLDER;

;
;Helper function which returns a IShellFolder interface to the desktop
; folder. This is equivalent to call CoCreateInstance with CLSID_ShellDesktop.
;
;CoCreateInstance(CLSID_Desktop, NULL,
; CLSCTX_INPROC, IID_IShellFolder, &pshf);
;
;WINSHELLAPI HRESULT WINAPI SHGetDesktopFolder(LPSHELLFOLDER *ppshf);




;==========================================================================
; Clipboard format which may be supported by IDataObject from system
; defined shell folders (such as directories, network, ...).
;==========================================================================

;CFSTR_SHELLIDLIST TEXT("Shell IDList Array"); CF_IDLIST
;CFSTR_SHELLIDLISTOFFSET TEXT("Shell Object Offsets"); CF_OBJECTPOSITIONS
;CFSTR_NETRESOURCESTEXT("Net Resource"); CF_NETRESOURCE
;CFSTR_FILEDESCRIPTORA TEXT("FileGroupDescriptor") ; CF_FILEGROUPDESCRIPTORA
;CFSTR_FILEDESCRIPTORW TEXT("FileGroupDescriptorW"); CF_FILEGROUPDESCRIPTORW
;CFSTR_FILECONTENTSTEXT("FileContents"); CF_FILECONTENTS
;CFSTR_FILENAMEA TEXT("FileName"); CF_FILENAMEA
;CFSTR_FILENAMEW TEXT("FileNameW") ; CF_FILENAMEW
;CFSTR_PRINTERGROUPTEXT("PrinterFriendlyName") ; CF_PRINTERS
;CFSTR_FILENAMEMAPATEXT("FileNameMap") ; CF_FILENAMEMAPA
;CFSTR_FILENAMEMAPWTEXT("FileNameMapW"); CF_FILENAMEMAPW
;CFSTR_PREFERREDDROPEFFECT TEXT("Preferred DropEffect")

;#ifdef UNICODE
;CFSTR_FILEDESCRIPTOR	equ	CFSTR_FILEDESCRIPTORW
;CFSTR_FILENAME		equ	CFSTR_FILENAMEW
;CFSTR_FILENAMEMAP	equ	CFSTR_FILENAMEMAPW
;#else
CFSTR_FILEDESCRIPTOR	equ	CFSTR_FILEDESCRIPTORA
CFSTR_FILENAME		equ	CFSTR_FILENAMEA
CFSTR_FILENAMEMAP	equ	CFSTR_FILENAMEMAPA
;#endif

;
; CF_OBJECTPOSITIONS
;
;



;DVASPECT_SHORTNAME2 ; use for CF_HDROP to get short name version
;
; format of CF_NETRESOURCE
;
;typedef struct _NRESARRAY { ; anr
;UINT cItems;
;NETRESOURCE nr[1];
;} NRESARRAY, * LPNRESARRAY;

;
; format of CF_IDLIST
;
;typedef struct _IDA {
;UINT cidl;; number of relative IDList
;UINT aoffset[1];; [0]: folder IDList, [1]-[cidl]: item IDList
;} CIDA, * LPIDA;

;
; FILEDESCRIPTOR.dwFlags field indicate which fields are to be used
;
;typedef enum {
;FD_CLSID= 0x0001,
;FD_SIZEPOINT= 0x0002,
;FD_ATTRIBUTES = 0x0004,
;FD_CREATETIME = 0x0008,
;FD_ACCESSTIME = 0x0010,
;FD_WRITESTIME = 0x0020,
;FD_FILESIZE = 0x0040,
;FD_LINKUI = 0x8000, ; 'link' UI is prefered
;} FD_FLAGS;

;typedef struct _FILEDESCRIPTORA { ; fod
;DWORD dwFlags;

;CLSID clsid;
;SIZEL sizel;
;POINTL pointl;

;DWORD dwFileAttributes;
;FILETIME ftCreationTime;
;FILETIME ftLastAccessTime;
;FILETIME ftLastWriteTime;
;DWORD nFileSizeHigh;
;DWORD nFileSizeLow;
;CHAR cFileName[ MAX_PATH ];
;} FILEDESCRIPTORA, *LPFILEDESCRIPTORA;

;typedef struct _FILEDESCRIPTORW { ; fod
;DWORD dwFlags;

;CLSID clsid;
;SIZEL sizel;
;POINTL pointl;

;DWORD dwFileAttributes;
;FILETIME ftCreationTime;
;FILETIME ftLastAccessTime;
;FILETIME ftLastWriteTime;
;DWORD nFileSizeHigh;
;DWORD nFileSizeLow;
;WCHARcFileName[ MAX_PATH ];
;} FILEDESCRIPTORW, *LPFILEDESCRIPTORW;

;#ifdef UNICODE
;FILEDESCRIPTORFILEDESCRIPTORW
;LPFILEDESCRIPTORLPFILEDESCRIPTORW
;#else
;FILEDESCRIPTORFILEDESCRIPTORA
;LPFILEDESCRIPTORLPFILEDESCRIPTORA
;#endif

;
; format of CF_FILEGROUPDESCRIPTOR
;
;typedef struct _FILEGROUPDESCRIPTORA { ; fgd
; UINT cItems;
; FILEDESCRIPTORA fgd[1];
;} FILEGROUPDESCRIPTORA, * LPFILEGROUPDESCRIPTORA;

;typedef struct _FILEGROUPDESCRIPTORW { ; fgd
; UINT cItems;
; FILEDESCRIPTORW fgd[1];
;} FILEGROUPDESCRIPTORW, * LPFILEGROUPDESCRIPTORW;

;#ifdef UNICODE
;FILEGROUPDESCRIPTOR FILEGROUPDESCRIPTORW
;LPFILEGROUPDESCRIPTOR LPFILEGROUPDESCRIPTORW
;#else
;FILEGROUPDESCRIPTOR FILEGROUPDESCRIPTORA
;LPFILEGROUPDESCRIPTOR LPFILEGROUPDESCRIPTORA
;#endif

;
; format of CF_HDROP and CF_PRINTERS, in the HDROP case the data that follows
; is a double null terinated list of file names, for printers they are printer
; friendly names
;
;typedef struct _DROPFILES {
; DWORD pFiles; ; offset of file list
; POINT pt; ; drop point (client coords)
; BOOL fNC; ; is it on NonClient area
 ; and pt is in screen coords
; BOOL fWide; ; WIDE character switch
;} DROPFILES, FAR * LPDROPFILES;


;====== File System Notification APIs ===============================
;

;
;File System Notification flags
;

SHCNE_RENAMEITEM	equ	00000001h
SHCNE_CREATE		equ	00000002h
SHCNE_DELETE		equ	00000004h
SHCNE_MKDIR 		equ	00000008h
SHCNE_RMDIR 		equ	00000010h
SHCNE_MEDIAINSERTED 	equ	00000020h
SHCNE_MEDIAREMOVED	equ	00000040h
SHCNE_DRIVEREMOVED	equ	00000080h
SHCNE_DRIVEADD		equ	00000100h
SHCNE_NETSHARE		equ	00000200h
SHCNE_NETUNSHARE	equ	00000400h
SHCNE_ATTRIBUTES		equ	00000800h
SHCNE_UPDATEDIR 		equ	00001000h
SHCNE_UPDATEITEM	equ	00002000h
SHCNE_SERVERDISCONNECT	equ	00004000h
SHCNE_UPDATEIMAGE 	equ	00008000h
SHCNE_DRIVEADDGUI 	equ	00010000h
SHCNE_RENAMEFOLDER	equ	00020000h
SHCNE_FREESPACE 		equ	00040000h
SHCNE_EXTENDED_EVENT	equ	00080000h ; Extended Event.

SHCNE_ASSOCCHANGED	equ	08000000h

SHCNE_DISKEVENTS	equ	0002381Fh
SHCNE_GLOBALEVENTS	equ	0C0D81E0h ; Events that dont match pidls first
SHCNE_ALLEVENTS		equ	7FFFFFFFh
SHCNE_INTERRUPT		equ	80000000h ; The presence of this flag indicates

; that the event was generated by an
; interrupt.It is stripped out before
; the clients of SHCNNotify_ see it.

SHCNEE_THEMECHANGED 	equ	00000001h	; The theme changed


; Flags
; uFlags & SHCNF_TYPE is an ID which indicates what dwItem1 and dwItem2 mean

SHCNF_IDLIST		equ	0000h	; LPITEMIDLIST
SHCNF_PATHA 		equ	0001h	; path name
SHCNF_PRINTERA		equ	0002h	; printer friendly name
SHCNF_DWORD 		equ	0003h	; DWORD
SHCNF_PATHW 		equ	0005h	; path name
SHCNF_PRINTERW		equ	0006h	; printer friendly name
SHCNF_TYPE		equ	00FFh
SHCNF_FLUSH 		equ	1000h
SHCNF_FLUSHNOWAIT 	equ	2000h

;#ifdef UNICODE
;SHCNF_PATH	equ	SHCNF_PATHW
;SHCNF_PRINTER	equ	SHCNF_PRINTERW
;#else
SHCNF_PATH	equ	SHCNF_PATHA
SHCNF_PRINTER	equ	SHCNF_PRINTERA
;#endif

;
;APIs
;
;WINSHELLAPI void WINAPI SHChangeNotify(LONG wEventId, UINT uFlags,
;LPCVOID dwItem1, LPCVOID dwItem2);

;
; SHAddToRecentDocs
;
SHARD_PIDL	equ	00000001h
SHARD_PATHA 	equ	00000002h
SHARD_PATHW 	equ	00000003h

;#ifdef UNICODE
;SHARD_PATH	equ	SHARD_PATHW
;#else
SHARD_PATH	equ	SHARD_PATHA
;#endif

;WINSHELLAPI void WINAPI SHAddToRecentDocs(UINT uFlags, LPCVOID pv);

;WINSHELLAPI HRESULT WINAPI SHGetInstanceExplorer(IUnknown **ppunk);

;
; SHGetDataFromIDListA/W
;
SHGDFIL_FINDDATA		equ	1
SHGDFIL_NETRESOURCE	equ	2
SHGDFIL_DESCRIPTIONID	equ	3

SHDID_ROOT_REGITEM	equ	1
SHDID_FS_FILE		equ	2
SHDID_FS_DIRECTORY	equ	3
SHDID_FS_OTHER		equ	4
SHDID_COMPUTER_DRIVE35	equ	5
SHDID_COMPUTER_DRIVE525 	equ	6
SHDID_COMPUTER_REMOVABLE	equ	7
SHDID_COMPUTER_FIXED	equ	8
SHDID_COMPUTER_NETDRIVE 	equ	9
SHDID_COMPUTER_CDROM	equ	10
SHDID_COMPUTER_RAMDISK	equ	11
SHDID_COMPUTER_OTHER	equ	12
SHDID_NET_DOMAIN	equ	13
SHDID_NET_SERVER	equ	14
SHDID_NET_SHARE		equ	15
SHDID_NET_RESTOFNET 	equ	16
SHDID_NET_OTHER		equ	17

;typedef struct _SHDESCRIPTIONID {
;DWORD dwDescriptionId;
;CLSID clsid;
;} SHDESCRIPTIONID, *LPSHDESCRIPTIONID;

;WINSHELLAPI HRESULT WINAPI SHGetDataFromIDListA(LPSHELLFOLDER psf, LPCITEMIDLIST pidl,
;int nFormat, PVOID pv, int cb);
;WINSHELLAPI HRESULT WINAPI SHGetDataFromIDListW(LPSHELLFOLDER psf, LPCITEMIDLIST pidl,
;int nFormat, PVOID pv, int cb);

;#ifdef UNICODE
;SHGetDataFromIDList	equ	SHGetDataFromIDListW
;#else
SHGetDataFromIDList	equ	SHGetDataFromIDListA
;#endif

;#ifdef __cplusplus
;}

;#endif/* __cplusplus */

SHFMT_ID_DEFAULT	equ	0FFFFh

; Option bits for options parameter

SHFMT_OPT_FULL		equ	1
SHFMT_OPT_SYSONLY	equ	2

; Special return values. PLEASE NOTE that these are DWORD values.

SHFMT_ERROR		equ	0FFFFFFFFh
SHFMT_CANCEL		equ	0FFFFFFFEh
SHFMT_NOFORMAT	equ	0FFFFFFFDh

; IActiveDesktop

iacde_QueryInterface	equ	0
iacde_AddRef		equ	4
iacde_Release		equ	8
iacde_ApplyChanges	equ	12
iacde_GetWallpaper	equ	16
iacde_SetWallpaper	equ	20
iacde_GetWallpaperOptions	equ	24
iacde_SetWallpaperOptions	equ	28
iacde_GetPattern		equ	32
iacde_SetPattern		equ	36
iacde_GetDesktopItemOptions	equ	40
iacde_SetDesktopItemOptions	equ	44
iacde_AddDesktopItem	equ	48
iacde_AddDesktopItemWithUI	equ	52
iacde_ModifyDesktopItem	equ	56
iacde_RemoveDesktopItem	equ	60
iacde_GetDesktopItemCount	equ	64
iacde_GetDesktopItem	equ	68
iacde_GetDesktopItemByID	equ	72
iacde_GenerateDesktopItemHtml	equ	76
iacde_AddUrl		equ	80
iacde_GetDesktopItemBySource	equ	84

; Flags for IActiveDesktop::ApplyChanges()

AD_APPLY_SAVE		equ	1
AD_APPLY_HTMLGEN	equ	2
AD_APPLY_REFRESH	equ	4
AD_APPLY_ALL		equ	AD_APPLY_SAVE OR AD_APPLY_HTMLGEN OR AD_APPLY_REFRESH
AD_APPLY_FORCE		equ	8
AD_APPLY_BUFFERED_REFRESH	equ	16
AD_APPLY_DYNAMICREFRESH	equ	32

COMPONENTSOPT	struc
 coop_dwSize		dd	?
 coop_fEnableComponents	dd	?
 coop_fActiveDesktop	dd	?
COMPONENTSOPT	ends


; flags for RemoveToolbar
DWFRF_NORMAL		equ	0
DWFRF_DELETECONFIGDATA	equ	1


; flags for AddToolbar
DWFAF_HIDDEN		equ	1

; IDockingWindowFrame
; GUID	<047d2657ah, 07b27h, 011d0h, 08ch, 0a9h, 00h, 0a0h, 0c9h, 02dh, 0bfh, 0e8h>

dofrwi_QueryInterface	equ	0
dofrwi_AddRef		equ	4
dofrwi_Release		equ	8
dofrwi_GetWindow		equ	12
dofrwi_ContextSensitiveHelp	equ	16
dofrwi_AddToolbar		equ	20
dofrwi_RemoveToolbar	equ	24
dofrwi_FindToolbar		equ	28


; IInputObjectSite

iinsi_QueryInterface	equ	0
iinsi_AddRef		equ	4
iinsi_Release		equ	8
iinsi_OnFocusChangeIS	equ	12

