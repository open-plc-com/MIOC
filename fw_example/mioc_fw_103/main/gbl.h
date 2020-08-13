#ifndef __GBL__
#define __GBL__

#ifdef __cplusplus
	extern "C" {
#endif

//#define BME280
//#define BH1750
//#define CCS811

//#define USB_VCP		// Use USB as VCP
//#define VCP_CONS	// USB VCP as Console

// ---------------------------------------------------------------------------
#include "bsp.h"
// ---------------------------------------------------------------------------

#ifndef TRUE
	#define TRUE	1
#endif
#ifndef FALSE
	#define FALSE	0
#endif

#define VER					"IO module v0.7.9 (open-plc.com)"
#define WD_TIMER												// Switch on WatchDog
//#define OSC_INT												// Use internal oscillator
//#define MCO													// Use PA8 as MCO

#ifndef F_APB1
	#define F_APB1			72000000							// Sys frequency in 72 MHz
#endif

#define F_DWT				( F_APB1 / 1000000 )
#ifndef DWT
	#define DWT														// DWT as sys_delay_timer
#endif

#ifndef Page_PRM
	#define Page_PRM		0x0800FC00							// Page for param saving
//	#define Page_PRM		0x0801FC00							// Page for param saving
#endif

#ifndef UART1_SPEED
	#define UART1_SPEED		115200								// UART1 speed
#endif

#ifndef RX_LEN
	#define RX_LEN			64									// Size of buffer Console Rx
#endif

#ifndef SPI_LEN
	#define SPI_LEN			24									// Size of buffer SPI
#endif

#define MAX_W1_ERR			5									// Maximum 1-Wire continuing error counter
#define SHOW_DATA_INTERVAL	50									// 10 * SHOW_DATA_INTERVAL mSec

//static uint32_t			*uid = ( uint32_t* ) 0x1FFFF7AC;

#define DWT_CYCCNT			*( volatile uint32_t* ) 0xE0001004
#define DWT_CONTROL			*( volatile uint32_t* ) 0xE0001000
#define SCB_DEMCR			*( volatile uint32_t* ) 0xE000EDFC
#define DWT_LAR				*( volatile uint32_t* ) 0xE0001FB0

static volatile uint32_t	Sn;									// Serial number (SN)
static volatile uint64_t	Sn8;								// Serial number (SN8)

static volatile uint16_t	Noc;								// CAN number
#ifdef CAN_2515
	static volatile uint16_t	Speedc;							// CAN speed
	static volatile bool		NoAnswer		= FALSE;		// Not answer for broadcast SN
	static volatile bool		CanErr			= FALSE;
	static volatile uint32_t	CANDownTime		= 0;
	static volatile bool		CAN_Run			= FALSE;
	static volatile uint8_t		can_id[4];						// Header of CAN packet
	static volatile uint8_t		can_data[8];					// CAN data
#endif

static volatile char		usart_rx_data[RX_LEN];				// recieve buffer data
static volatile uint8_t		rx_idx			= 0;				// Index in UART recieve buffer
static volatile bool		ret_button		= FALSE;			// Return is pressed

static volatile uint32_t	CntTime			= 0;				// Counter of quants of System Timer 10 ms
//static volatile uint32_t	CntTime_1ms		= 0;				// Counter of quants of TIM4_IRQHandler 1 ms
static volatile uint32_t	DelayTime		= 0;				// For LED blink
static volatile uint32_t	WD_Time			= 0;				// Time of watchdog

static volatile uint8_t		spi2_tx_data[SPI_LEN];				// Buffer of Tx SPI2
static volatile uint8_t		spi2_rx_data[SPI_LEN];				// Buffer of Rx SPI2

static volatile uint16_t	Nn_ADC;								// Number of ADC channels
static volatile uint16_t	iButton_Timeout	= 1;
//#define iButton_Timeout 1
static volatile bool		Show_Data	= TRUE;
static volatile bool		Echo		= FALSE;
static volatile bool		CLS			= FALSE;

static volatile uint32_t	Lc1			= 0;
static volatile uint32_t	Lc2			= 0;
static volatile uint32_t	Lc3			= 0;
static volatile uint32_t	Lc4			= 0;
static volatile uint32_t	Lc5			= 0;
static volatile uint32_t	Lc6			= 0;
static volatile uint32_t	Step_DS		= 0;
static volatile uint32_t	Step_BTN	= 0;

#define ADC_ARRAY_SIZE		512
volatile uint16_t			ADC_NN			= 0;
volatile uint16_t			ADC_ARRAY		= 0;
volatile uint16_t			ADC_SUB_ARRAY	= 0;
volatile uint16_t			ADC_VALUES[ADC_ARRAY_SIZE];
volatile uint32_t			ADC_AVG[8];
volatile unsigned int		*ADC_NAME_PTR[8];
//volatile uint32_t			A;

#define LCD_PRINT
#if defined LCD_1602 || defined LCD_PRINT
	struct LCD1_Struct
	{
		char data[18];
	}	volatile LCD1[2];
	#ifdef PCF8574
		#define PCF8574_ADDR 0x27
	#endif
	#ifdef PCF8574A
		#define PCF8574_ADDR 0x3F
	#endif
#endif

	//#define I2C1_D
	//#define I2C2_D

#define SSD1306_FAST
#ifdef LCD_1602
	#define LCD_1602_FAST
#endif

#if defined LCD_1602 || defined LCD_SSD1306
	#ifndef I2C1_D
		#define I2C1_D
	#endif
	#ifdef LCD_1602
		#define I2C_LCD_1602 I2C1
	#endif
	#ifdef LCD_SSD1306
		#define I2C_LCD_SSD1306 I2C1
	#endif
#endif

#if defined BME280 || defined BH1750 || defined CCS811
	#ifndef I2C2_D
		#define I2C2_D
	#endif
	#ifdef BME280
		#define I2C_BME280 I2C2
	#endif
	#ifdef BH1750
		#define I2C_BH1750 I2C2
	#endif
	#ifdef CCS811
		#define I2C_CCS811 I2C2
	#endif
#endif
#if defined I2C1_D || defined I2C2_D
	static volatile int I2C1_ERR		= 0;
	static volatile int I2C2_ERR		= 0;
#endif
	static volatile int32_t  BME_T		= 0;
	static volatile int32_t  BME_P		= 0;
	static volatile int32_t  BME_H		= 0;
	static volatile uint32_t BH_L		= 0;
	static volatile uint32_t CCS_CO2	= 0;
	static volatile uint32_t CCS_TVOC	= 0;

#define print(fmt,argv...){char s[128];sprintf(s,fmt,##argv);print_str(s);}
#define printf(fmt,argv...){char s[128];sprintf(s,fmt,##argv);print_str(s);}
#define set_bit(name,bit) (set_bit_func((unsigned int*)&name,bit))

#ifdef __cplusplus
	}
#endif

#endif /* __GBL__ */
