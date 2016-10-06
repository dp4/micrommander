//-----------------------------------------------------------------------------------------------------------------------------------------
// description:	x64 asm source for "commander style" windows file manager - resources, resource compiler style
// note:	copyright © by digital performance 1997 - 2014, author S. Deutsch, A. Voelskow
// license:
//
// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY// without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// assembler:	Visual Studio 2013
// last update:	2013-02-20 - Deutsch - make x64
//-----------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------
//		version information, manifest
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDV_VERSION					1
#	define IDMF_MAIN					1


//-----------------------------------------------------------------------------------------------------------------------------------------
//		graphics
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDI_APP							100
#	define IDB_STARTLOGO				200
#	define IDB_CMDICONS				201
#	define IDB_DEFAULT_INI			300


//-----------------------------------------------------------------------------------------------------------------------------------------
//		menu
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDM_APP						10000
#	define IDM_FILE_CONFIG			10010
#	define IDM_FILE_EXIT				10020
#	define IDM_LEFT_SYMBOL			10100
#	define IDM_LEFT_SIZE				10101
#	define IDM_LEFT_DATE				10102
#	define IDM_LEFT_TYPE				10103
#	define IDM_LEFT_FONT				10110
#	define IDM_LEFT_BGCOLOR			10120
#	define IDM_LEFT_FGCOLOR			10130
#	define IDM_RIGHT_SYMBOL		10200
#	define IDM_RIGHT_SIZE		 		10201
#	define IDM_RIGHT_DATE		 	10202
#	define IDM_RIGHT_TYPE		 	10203
#	define IDM_RIGHT_FONT		 	10210
#	define IDM_RIGHT_FGCOLOR		10220
#	define IDM_RIGHT_BGCOLOR		10230
#	define IDM_HELP_ABOUT			10300


//-----------------------------------------------------------------------------------------------------------------------------------------
//		button pop up menu
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDM_BUTTONPOP				11000
#	define IDM_BPOP_COMMAND		11010
#	define IDM_BPOP_FONT				11020
#	define IDM_BPOP_FGCOLOR		11030
#	define IDM_BPOP_BGCOLOR		11040
#	define IDM_BPOP_SHORTCUT		11050


//-----------------------------------------------------------------------------------------------------------------------------------------
//		dialogs
//-----------------------------------------------------------------------------------------------------------------------------------------
	
#	define IDD_PROGRESS				4000
#	define ID_CP_PROGRESS			(IDD_PROGRESS + 2)
#	define ID_CP_STATE					(IDD_PROGRESS + 4)
#	define ID_CP_TABS					(IDD_PROGRESS + 6)
	
#	define IDD_BUTTON_CMD			5100
#	define ID_BC_CMDLIST				(IDD_BUTTON_CMD + 10)
#	define ID_BC_TEXT					(IDD_BUTTON_CMD + 15)
#	define ID_BC_PARAM					(IDD_BUTTON_CMD + 20)
#	define ID_BC_HINT					(IDD_BUTTON_CMD + 30)

#	define IDD_BYTEINFO				5200
#	define ID_BI_DIRECTORY			(IDD_BYTEINFO + 10)
#	define ID_BI_FILES					(IDD_BYTEINFO + 20)
#	define ID_BI_BYTES					(IDD_BYTEINFO + 30)
	
#	define IDD_RENAME					5300
#	define ID_RM_FILENAME				(IDD_RENAME + 10)
	
#	define IDD_MAKE_DIR				5400
#	define ID_MK_NEWDIR				(IDD_MAKE_DIR + 10)
#	define ID_MK_HINT					(IDD_MAKE_DIR + 20)

#	define IDD_CONFIGURE				5500
#	define ID_CF_BUTTONROWS		(IDD_CONFIGURE + 2)
#	define ID_CF_BUTTONCOLS		(IDD_CONFIGURE + 4)
#	define ID_CF_DELCONFIRM			(IDD_CONFIGURE + 6)

#	define IDD_SHORTCUT				5600
#	define ID_SC_KEY						(IDD_SHORTCUT + 2)


//-----------------------------------------------------------------------------------------------------------------------------------------
//		strings
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDS_SHELLOPEN				20003
#	define IDS_DECMASK					20004
#	define IDS_VERMASK					20005
#	define IDS_DEFPATH					20006
#	define IDS_COLDATE					20007
#	define IDS_COLNAME					20008
#	define IDS_COLSIZE					20009
#	define IDS_COLACTION				20010
#	define IDS_COLSOURCE				20011
#	define IDS_COLTARGET				20012
#	define IDS_COLTYPE					20017
#	define IDS_CONFIGFILE				20018
#	define IDS_EDITCLASS				20019
#	define IDS_LISTCLASS				20020
#	define IDS_DEF_LISTFONT			20021
#	define IDS_DEF_BTNFONT			20023
#	define IDS_DEF_EDITFONT			20024
#	define IDS_LOGOCLASS				20025
#	define IDS_APPWINCLASS			20026
#	define IDS_APPTITLE					20027
#	define IDS_DIRTAG					20028
#	define IDS_DATEFORMAT			20030
#	define IDS_TIMEFORMAT			20031
#	define IDS_ABOUT_TEXT			20032
#	define IDS_ABOUT_TITLE			20033	//
#	define IDS_DELCONF_TEXT			20042
#	define IDS_CONFIRM_TITLE		20043
#	define IDS_CURRENT_RUN			20044
#	define IDS_STATUS_READY		20045
#	define IDS_COPY_COLLECT			20046
#	define IDS_MOVE_COLLECT		20047
#	define IDS_DELETE_COLLECT		20048
#	define IDS_CONFIRM_TEXT			20049
#	define IDS_PROGRESS_DO			20050
#	define IDS_PROGRESS_FAIL		20051
#	define IDS_CFG_LEFTPATH			20056
#	define IDS_CFG_RIGHTPATH		20057
#	define IDS_CFG_SELECTCUR		20058
#	define IDS_CFG_SELECTOTH		20059
#	define IDS_CFG_LEFTLIST			20060
#	define IDS_CFG_RIGHTLIST		20061
#	define IDS_CFG_PARAM				20062
#	define IDS_CFG_BUTTONS			20063
#	define IDS_CFG_LEFTEDIT			20064
#	define IDS_CFG_RIGHTEDIT		20065
#	define IDS_CFG_SHOWMODE		20066
#	define IDS_CFG_BUTTONROWS	20067
#	define IDS_CFG_BUTTONCOLS		20068
#	define IDS_CFG_DELCONFIRM		20071
#	define IDS_CFG_BUTTONTEXT		20072
#	define IDS_CFG_BUTTONPARAM	20073
#	define IDS_CFG_BUTTONCMD		20074
#	define IDS_CFG_WINLEFT			20075
#	define IDS_CFG_WINTOP			20076
#	define IDS_CFG_WINRIGHT			20077
#	define IDS_CFG_WINBOTTOM		20078
#	define IDS_CFG_VIEWBACK			20079
#	define IDS_CFG_VIEWFORE			20080
#	define IDS_CFG_VIEWSIZE			20081
#	define IDS_CFG_VIEWITALIC		20082
#	define IDS_CFG_VIEWWEIGHT		20083
#	define IDS_CFG_VIEWFONT		20084
#	define IDS_CFG_BUTTONSCUT	20085
#	define IDS_CFG_LISTNAMECOL	20086
#	define IDS_CFG_LISTTYPECOL	20087
#	define IDS_CFG_LISTDATECOL	20088
#	define IDS_CFG_LISTSIZECOL		20089
#	define IDS_CFG_LISTMODE			20090
#	define IDS_ERROR_BASE			20100
#	define IDS_CMDCAT_DRIVES		20195
#	define IDS_CMDCAT_EXTERN		20196
#	define IDS_CMDCAT_FILES			20197
#	define IDS_CMDCAT_FOLDERS		20198
#	define IDS_CMDCAT_DEFAULT		20199
#	define IDS_CMD_EMPTY				20200
#	define IDS_CMD_COPY				20201
#	define IDS_CMD_MOVE				20202
#	define IDS_CMD_PARENT			20203
#	define IDS_CMD_CD					20204
#	define IDS_CMD_ALL					20205
#	define IDS_CMD_NONE				20206
#	define IDS_CMD_BYTE				20207
#	define IDS_CMD_MKDIR				20208
#	define IDS_CMD_DELETE			20209
#	define IDS_CMD_EXIT				20210
#	define IDS_CMD_ROOT				20211
#	define IDS_CMD_RENAME			20212
#	define IDS_CMD_EXECUTE			20213
#	define IDS_CMD_FORMAT			20214
#	define IDS_KEY_SHIFT				20400
#	define IDS_KEY_CTRL				20401
#	define IDS_CMDERR_RETRY			20500
#	define IDS_CMDERR_IGNORE		20501
#	define IDS_CMDERR_IGNORE_ALL	20502
#	define IDS_CMD_BASE				21000
	

//-----------------------------------------------------------------------------------------------------------------------------------------
//		command numbers
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define CMD_EMPTY					0
#	define CMD_COPY						1
#	define CMD_MOVE					2
#	define CMD_PARENT					3
#	define CMD_CD						4
#	define CMD_ALL						5
#	define CMD_NONE						6
#	define CMD_BYTE						7
#	define CMD_MKDIR					8
#	define CMD_DELETE					9
#	define CMD_ROOT						10
#	define CMD_EXIT						11
#	define CMD_RENAME					12
#	define CMD_EXECUTE				13
#	define CMD_FORMAT					14
