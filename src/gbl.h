/*
	Name:			gbl.h
	Purpose:		MIOC
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#ifndef __GBL__
#define __GBL__

#ifdef WIN32	// if Win then declare nix-like types
	#define		int8_t		__int8
	#define		int16_t		__int16
	#define		int32_t		__int32
	#define		int64_t		__int64
	#define		uint8_t		unsigned __int8
	#define		uint16_t	unsigned __int16
	#define		uint32_t	unsigned __int32
	#define		uint64_t	unsigned __int64
#endif			// WIN32

#define MAX_GRID_NN 256

#include "dataio_com.h"

static wxString		EXEC_PATH;
static wxString		DATA_DIR;
static wxString		WORK_PATH;
static wxChar		PATH_SEP;
static wxString		S_NAME;
static wxString		S_EXT;

static bool			Win_MaxSize			= false;
static bool			Read_Win_MaxSize	= false;
static int			Win_PosX			= 0;
static int			Win_PosY			= 0;
static int			Win_SizeX			= 0;
static int			Win_SizeY			= 0;

volatile bool		PRJ_CHANGED			= false;
static wxString		PRJ_NAME			= wxEmptyString;
static wxString		PRJ_MCU				= wxEmptyString;
static wxString		PRJ_COMMENT			= wxEmptyString;

#define				MAX_PORT_NN   49
static int			PORT_NN		= 0;
static unsigned int	SN_FW		= 0;
static wxString		SEL_PORT[MAX_PORT_NN];

static int			COM_NN		= -1;
static int			COM_SPEED	= -1;
DataIO_Com			*IO_COM		= new DataIO_Com();
//volatile bool		ISCONNECTED = false;

const wxString VAR_1XX_TYPES[] =
{
	wxEmptyString,
	wxT( "bool" ),
	wxT( "int8" ),
	wxT( "unsigned int8" ),
	wxT( "int16" ),
	wxT( "unsigned int16" ),
	wxT( "int32" ),
	wxT( "unsigned int32" ),
	wxT( "int64" ),
	wxT( "unsigned int64" ),
	wxT( "float" ),
	wxT( "double" ),
	wxT( "GPIO_Mode_AIN" ),
	wxT( "GPIO_Mode_IN_FLOATING" ),
	wxT( "GPIO_Mode_IPD" ),
	wxT( "GPIO_Mode_IPU" ),
	wxT( "GPIO_Mode_Out_OD" ),
	wxT( "GPIO_Mode_Out_PP" ),
	wxT( "DS18B20" ),
//	wxT( "iButton" ),
//	wxT( "LCD_1602_STR_1" ),
//	wxT( "LCD_1602_STR_2" ),
};
/*
GPIO_Mode_AIN           — Analog input
GPIO_Mode_IN_FLOATING   — Input without pull (Float)
GPIO_Mode_IPD           — Input with a Pull-down
GPIO_Mode_IPU           — Input with a Pull-up
GPIO_Mode_Out_OD        — Open Drain output
GPIO_Mode_Out_PP        — Push-Pull output
GPIO_Mode_AF_OD         — Open drain output for alternative functions.
                          Used when pins are controlled by peripherals,
                          which may be involved in this conclusion.
                          For example USART, I2C and the like.
GPIO_Mode_AF_PP         — The same as before, but with two states.
*/

/*
const wxString VAR_3XX_TYPES[] =
{
	wxT("bool"),
	wxT("int8"),
	wxT("unsigned int8"),
	wxT("int16"),
	wxT("unsigned int16"),
	wxT( wxEmptyString ),
	wxT("int32"),
	wxT("unsigned int32"),
	wxT("int64"),
	wxT("unsigned int64"),
	wxT("float"),
	//wxT("GPIO_Mode_AIN"),
	//wxT("GPIO_Mode_IN_FLOATING"),
	//wxT("GPIO_Mode_IPD"),
	//wxT("GPIO_Mode_IPU"),
	//wxT("GPIO_Mode_Out_OD"),
	//wxT("GPIO_Mode_Out_PP"),
	//wxT("DS18B20"),
	//wxT("iButton"),
	//wxT("LCD 1602 STR-1"),
	//wxT("LCD 1602 STR-2"),
	//wxT(""),
};
*/

wxTextCtrl *_log;

#endif //__GBL__
