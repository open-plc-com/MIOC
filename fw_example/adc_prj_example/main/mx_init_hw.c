/*
	Name:			mx_init_hw.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_iwdg.h>
#include <stm32f10x_exti.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_dma.h>
#include <stm32f10x_dac.h>
#include <stm32f10x_flash.h>
#include <stm32f10x_i2c.h>
#include <misc.h>

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "gbl.h"
#include "mx_misc.c"
#if defined I2C1_D || defined I2C2_D
	#include "mx_i2c.c"
#endif
#include "mx_adc.c"
#include "mx_parcer.c"
#include "mx_cli.c"
#ifdef BME280
	#include "bme280.c"
#endif
#ifdef BH1750
	#include "bh1750.c"
#endif
#ifdef CCS811
	#include "ccs811.c"
#endif
#include "mx_io.c"
#include "mx_timers.c"
#include "mx_flash.c"
#include "mx_init.c"
//#include "mx_i2c2.c"


/* --- external CAN MCP2515 --- */
#ifdef CAN_2515
	#include "mx_spi2.c"
	#include "mx_can_mcp2515.c"
#endif

#ifdef LCD_1602
	//#include "mx_i2c1.c"
	#include "mx_lcd_i2c.c"
#else
	void LCD_write_string( uint16_t n, char *str ) {}
#endif

#ifdef LCD_SSD1306
	//#include "mx_ssd1306_i2c.c"
	#include "fonts.c"
	#include "mx_ssd1306.c"
	//#include "mx_i2c1.c"
#else
	SSD1306_write_string( uint16_t n, char *str ) {}
#endif

//#ifdef BME280
	//#include "bme280.c"
//#endif

//#ifdef BH1750
	//#include "bh1750.c"
//#endif

//#ifdef CCS811
	//#include "ccs811.c"
//#endif

/* --- USB --- */
#ifndef USB_VCP
void send_usb( char *data, int len );
#else
	#include "hw_config.h"
	#include "usb_lib.h"
	#include "usb_desc.h"
	#include "usb_pwr.h"
#endif
	#include "../usb/src/usb_endp.c"	// Comment this string if full delete USB support


// ===========================================================================
void Init_HW( void )
// ===========================================================================
{
	SystemInit();
	Read_Flash();
	init_bsp();
	MX_Init();
	sys_delay_ms( 100 );

	// --- USE_UART1 ---------------------------------------------------------
	#ifdef USE_UART1
		USART_ClearITPendingBit( USART1, USART_IT_RXNE );	// Clear UART
		if( CLS )
		{
			send_uart1( "\33c\r\n", 4 );
			delay_ms( 100 );
		}
		send_uart1( "+++\r\n", 5 );
	#endif


	Get_SN();
//print( " %lu\r\n", Sn );
//print( s, " %llu\r\n", Sn8 );

	// --- USB_VC ------------------------------------------------------------
	#ifdef USB_VCP
		sys_delay_ms( 2000 );
		USB_Interrupts_Config();
		sys_delay_ms( 1000 );
		USB_Init();
		sys_delay_ms( 1000 );
		if( CLS )
		{
			send_usb( "\33c\r\n", 4 );
			delay_ms( 100 );
		}
		send_usb( "+++\r\n", 5 );
	#endif

	delay_ms( 100 );
	Init_Timer3();
	Init_Timer4();

//	// --- CAN_2515 ----------------------------------------------------------
//	#ifdef CAN_2515
//		Init_Spi2();
//		reset_can();
//		delay_us( 100 );
//		Init_Can();
//	#endif

	#ifdef I2C1_D
		init_I2C1();
	#endif

	#ifdef I2C2_D
		init_I2C2();
	#endif

	// --- LCD_1602 ----------------------------------------------------------
	#ifdef LCD_1602		// Init LCD 1602
		LCDI2C_init( PCF8574_ADDR, 20, 2 );
		if( !I2C1_ERR )
		{
			LCDI2C_backlight();		// finish with backlight on
		}
	#endif

	#ifdef LCD_SSD1306
		SSD1306_Init();

		/* Set default values */
		SSD1306.CurrentX = 0;
		SSD1306.CurrentY = 0;

		/* Initialized OK */
		SSD1306.Initialized = 1;
		//if( I2C1_ERR ) print_str( "\r\nSSD1306_ERR\r\n" );
	#endif

	#ifdef BME280
		BME280_Init();
	#endif

	#ifdef BH1750
		BH1750_Init();
	#endif

	#ifdef CCS811
		CCS811_init();
	#endif
}
// ===========================================================================
