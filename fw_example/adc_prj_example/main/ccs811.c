/*
	Name:			ccs811.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:	2019/09
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/



#define CCS_811_ADDRESS		0x5A<<1	// CCS811 ADDR pin is logic zero otherwise address would be 0x5B
#define STATUS_REG			0x00
#define MEAS_MODE_REG		0x01
#define ALG_RESULT_DATA		0x02
#define ENV_DATA			0x05
#define THRESHOLDS			0x10
#define BASELINE			0x11
#define HW_ID_REG			0x20
#define ERROR_ID_REG		0xE0
#define APP_START_REG		0xF4
#define SW_RESET			0xFF

//#define GPIO_WAKE				0x5
//#define DRIVE_MODE_IDLE		0x0
//#define DRIVE_MODE_1SEC		0x10
//#define DRIVE_MODE_10SEC		0x20
//#define DRIVE_MODE_60SEC		0x30
//#define INTERRUPT_DRIVEN		0x8
//#define THRESHOLDS_ENABLED	0x4


// ===========================================================================
void CCS811_init( void )
// ===========================================================================
{
	uint8_t data[8];

	data[0] = 0x11;
	data[0] = 0xE5;
	data[0] = 0x72;
	data[0] = 0x8A;

	I2C_write_many( I2C_CCS811, CCS_811_ADDRESS, SW_RESET, 4, data );
	delay_ms( 20 );
	I2C_write_many( I2C_CCS811, CCS_811_ADDRESS, APP_START_REG, 0, data );
	delay_ms( 20 );
	data[0] = 0x40;
	I2C_write_one( I2C_CCS811, CCS_811_ADDRESS, 1, data[0] );
	delay_ms( 20 );
	data[0] = 0;
	data[0] = I2C_read_one( I2C_CCS811, CCS_811_ADDRESS,  0 );
	data[0] = I2C_read_one( I2C_CCS811, CCS_811_ADDRESS,  1 );
}
// ===========================================================================


// ===========================================================================
void CCS811_read( volatile uint32_t *co2, volatile uint32_t *tvoc )
// ===========================================================================
{
	uint8_t data[8];

	data[0] = I2C_read_one( I2C_CCS811, CCS_811_ADDRESS, STATUS_REG );
	if( data[0] & 0x08 )
	{
		I2C_read_many( I2C_CCS811, CCS_811_ADDRESS, ALG_RESULT_DATA, 4, data );
		*co2 = ( data[1] | ( data[0]<<8 ) );
		*tvoc = ( data[3] | ( data[2]<<8 ) );
	}
	else
	{
		*co2 = 0;
		*tvoc = 0;
	}
}
// ===========================================================================
//#enfif
