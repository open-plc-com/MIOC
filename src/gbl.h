/*
	Name:			
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

//#define WIN32
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

#include "dataio_com.h"

static wxString		EXEC_PATH;
static wxString		DATA_DIR;
static wxString		WORK_PATH;
static wxChar		PATH_SEP;
//static wxString		USER_DATA_PATH;
//static wxString		USER_CONFIG_PATH;
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
static wxString		PRJ_COMMENT;

#define				MAX_PORT_NN   49
static int			PORT_NN		= 0;
static int			SN_FW		= 0;
static int			PA_BUSY[]	= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int			PB_BUSY[]	= { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
static int			PC_BUSY[]	= { 1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1 };
static wxString		SEL_PORT[MAX_PORT_NN];

static int			COM_NN		= -1;
static int			COM_SPEED	= -1;
DataIO_Com			*IO_COM		= new DataIO_Com();
//volatile bool		ISCONNECTED = false;

//static bool			USE_UART1	= false;
//static bool			USB_VCP		= false;
//static bool			USB_CONSOLE	= false;
//static bool			LED_BLINK	= false;
//static bool			LCD_1602	= false;
//static bool			PCF8574A	= false;
//static bool			CAN_2515	= false;



//wxString

const wxString VAR_1XX_TYPES[] =
{
	wxEmptyString,					//  0
	wxT("bool"),					//  1
	wxT("int8"),					//  2
	wxT("unsigned int8"),			//  3
	wxT("int16"),					//  4
	wxT("unsigned int16"),			//  5
	wxT("int32"),					//  6
	wxT("unsigned int32"),			//  7
	wxT("int64"),					//  8
	wxT("unsigned int64"),			//  9
	wxT("float"),					// 10
	wxT("double"),					// 11
	wxT("GPIO_Mode_AIN"),			// 12
	wxT("GPIO_Mode_IN_FLOATING"),	// 13
	wxT("GPIO_Mode_IPD"),			// 14
	wxT("GPIO_Mode_IPU"),			// 15
	wxT("GPIO_Mode_Out_OD"),		// 16
	wxT("GPIO_Mode_Out_PP"),		// 17
	wxT("DS18B20"),					// 18
	wxT("iButton"),					// 19
	wxT("LCD 1602 STR-1"),			// 20
	wxT("LCD 1602 STR-2"),			// 21
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




//static wxString	gs;	// ???
//volatile bool IsConnected;


//static volatile char	DATA_STR[DATA_NN][DATA_LEN];
//static volatile int		Data_NN, Data_Show;
//static volatile bool	IsRun, Stop;

wxTextCtrl *_log;

#endif //__GBL__
