//-----------------------------------------------------------------------------------------------------------------------------------------
// description:	x64 asm source for "commander style" windows file manager - setup resources
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

#	define IDI_MAIN					1001
#	define IDI_HOOK					1002
#	define IDB_WELCOME			1003
#	define IDB_LICENSE				1004
	
#	define IDR_BIN_FILE1			2000
#	define IDR_BIN_FILE2			2001
#	define IDR_BIN_FILE3			2002
#	define IDR_BIN_LICENSE		2901


//-----------------------------------------------------------------------------------------------------------------------------------------
//		dialog IDs
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDD_WELCOME			4000
#	define IDD_LICENSE				4100
#	define IDD_PROGRESS			4400
	
#	define IDC_CAPTION				101
#	define IDC_PROGRESSBAR		109
#	define IDC_LIC_FIELD			110
#	define IDC_HOOK1				112
#	define IDC_HOOK2				114
#	define IDC_HOOK3				116
#	define IDC_HOOK4				117
#	define IDC_STEP1					118
#	define IDC_STEP2					120
#	define IDC_STEP3					122
#	define IDC_STEP4					124
#	define IDC_INST_LIST			130
#	define IDC_NEXTPAGE			200
#	define IDC_PREVPAGE			201

#	define IDD_DIRECTORY			4200
#	define ID_DI_FRAME				(IDD_DIRECTORY + 10)
#	define ID_DI_PATH				(IDD_DIRECTORY + 11)
#	define ID_DI_BUTTON			(IDD_DIRECTORY + 12)

#	define IDD_OPTIONS				4300
#	define ID_OP_DESKTOP			(IDD_OPTIONS + 10)
#	define ID_OP_START				(IDD_OPTIONS + 11)
#	define ID_OP_CONTEXT			(IDD_OPTIONS + 12)


//-----------------------------------------------------------------------------------------------------------------------------------------
//		strings
//-----------------------------------------------------------------------------------------------------------------------------------------

#	define IDS_PRODUCTNAME		20000
#	define IDS_CONFIRM_TITLE	20003
#	define IDS_WANT_QUIT			20004
#	define IDS_SUCCESS_TITLE	20005
#	define IDS_SUCCESS_TEXT	20006
#	define IDS_DEFAULT_PATH		20007
#	define IDS_CREATE_DIR			20008
#	define IDS_ERROR_TITLE		20009
#	define IDS_NOT_EMPTY			20010
#	define IDS_CHOOSE_PATH		20011
#	define IDS_PROGRAM_PATH	20012
