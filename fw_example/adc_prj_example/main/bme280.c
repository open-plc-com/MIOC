/*
	Name:			bme280.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:	2019/09
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#ifdef BME280

#include "bme280.h"

#define be16toword(a)((((a)>>8)&0xff)|(((a)<<8)&0xff00))

uint16_t dig_T1 = 0;
int16_t  dig_T2 = 0;
int16_t  dig_T3 = 0;

uint16_t dig_P1 = 0;
int16_t  dig_P2 = 0;
int16_t  dig_P3 = 0;
int16_t  dig_P4 = 0;
int16_t  dig_P5 = 0;
int16_t  dig_P6 = 0;
int16_t  dig_P7 = 0;
int16_t  dig_P8 = 0;
int16_t  dig_P9 = 0;

uint8_t  dig_H1 = 0;
int16_t  dig_H2 = 0;
uint8_t  dig_H3 = 0;
int16_t  dig_H4 = 0;
int16_t  dig_H5 = 0;
int8_t   dig_H6 = 0;


// ===========================================================================
void bme280Convert( int32_t *temperature, int32_t *pressure, int32_t *humidity )
// ===========================================================================
{
	uint32_t	adc_T = 0;
	uint32_t	adc_P = 0;
	uint32_t	adc_H = 0;
	uint32_t	v_x1_u32r;
	uint8_t		data[4];
	double		p, t_fine;
	//double		var_H, p, t_fine;
	double		var1;
	double		var2;

	*temperature	= 0;
	*pressure		= 0;
	*humidity		= 0;

	I2C_read_many( I2C_BME280, BME280_addr, BME280_REG_RESULT_TEMPRERATURE, 3, data );
	adc_T = ( data[0] << 16 ) | ( data[1] << 8 ) | ( data[2] << 4 );
	adc_T = adc_T >> 4;

	I2C_read_many( I2C_BME280, BME280_addr, BME280_REG_RESULT_PRESSURE, 3, data );
	adc_P = ( data[0] << 16 ) | ( data[1] << 8 ) | ( data[2] << 4 );
	adc_P = adc_P >> 4;

	I2C_read_many( I2C_BME280, BME280_addr, BME280_REG_RESULT_HUMIDDATA, 2, data );		// Comment for BMP
	adc_H = ( data[0] << 8 ) | data[1];													// Comment for BMP

	var1 = ( ( (double) adc_T ) / 16384.0 - ( (double) dig_T1 ) / 1024.0 ) * ( (double) dig_T2 );
	var2 = ( ( ( (double) adc_T ) / 131072.0 - ( (double) dig_T1 ) / 8192.0 ) *
			( ( (double) adc_T ) / 131072.0 - ( (double) dig_T1 ) / 8192.0 ) ) * ( (double) dig_T3 );
	t_fine = ( var1 + var2 ) - DT;
	//t_fine = ( var1 + var2 );
	//*temperature = (int32_t) ( t_fine * 1000.0 ) / 5120.0;
	*temperature = (int32_t) ( t_fine * 10.0 ) / 5120.0;

	var1 = ( (double) t_fine / 2.0 ) - 64000.0;
	var2 = var1 * var1 * ( (double) dig_P6 ) / 32768.0;
	var2 = var2 + var1 * ( (double) dig_P5 ) * 2.0;
	var2 = ( var2 / 4.0 ) + ( ((double) dig_P4 ) * 65536.0 );
	var1 = ( ( (double) dig_P3 ) * var1 * var1 / 524288.0 + ( (double) dig_P2 ) * var1 ) / 524288.0;
	var1 = ( 1.0 + var1 / 32768.0 ) * ( (double) dig_P1 );
	if( var1 < 1.0 )
	{
		return;
	}
	p = 1048576.0 - (double) adc_P;
	p = ( p - ( var2 / 4096.0 ) ) * 6250.0 / var1;
	var1 = ( (double) dig_P9 ) * p * p / 2147483648.0;
	var2 = p * ( (double) dig_P8 ) / 32768.0;
	//p = ( ( p + ( var1 + var2 + ( (double) dig_P7 ) ) / 16.0 ) * 1.44472 ) / 2;
	p = p + ( var1 + var2 + ( (double) dig_P7 ) ) / 16.0;
	*pressure = (int32_t) p;

	v_x1_u32r = (uint32_t) ( t_fine - 76800.0 );
	v_x1_u32r = ( ( ( ( ( adc_H << 14 ) - ( ( (int32_t) dig_H4 ) << 20 ) -
					( ( (int32_t) dig_H5) * v_x1_u32r ) ) + ( (int32_t) 16384 ) ) >> 15 ) *
					( ( ( ( ( ( ( v_x1_u32r * ( (int32_t) dig_H6 ) ) >> 10 ) * ( ( ( v_x1_u32r *
					( (int32_t) dig_H3 ) ) >> 11 ) + ( (int32_t) 32768 ) ) ) >> 10 ) + ( (int32_t) 2097152 ) ) *
					( (int32_t) dig_H2) + 8192 ) >> 14 ) );
	v_x1_u32r = ( v_x1_u32r - ( ( ( ( ( v_x1_u32r >> 15 ) * ( v_x1_u32r >> 15 ) ) >> 7 ) *
								( (int32_t) dig_H1 ) ) >> 4 ) );
	v_x1_u32r /= 1000000;
	*humidity = v_x1_u32r;

	if( I2C_BME280 == I2C1 )
	{
		if( I2C1_ERR )
		{
			*temperature	= 0;
			*pressure		= 0;
			*humidity		= 0;
		}
	}
	else
	if( I2C_BME280 == I2C2 )
	{
		if( I2C2_ERR )
		{
			*temperature	= 0;
			*pressure		= 0;
			*humidity		= 0;
		}
	}
}
// ===========================================================================


// ===========================================================================
void BME280_Init( void )
// ===========================================================================
{
	uint8_t data[8];

	I2C_read_many( I2C_BME280, BME280_addr, 0x88, 2, data ); dig_T1 = (uint16_t) ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x8A, 2, data ); dig_T2 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x8C, 2, data ); dig_T3 = (int16_t)  ( data[1] << 8 ) | data[0];

	I2C_read_many( I2C_BME280, BME280_addr, 0x8E, 2, data ); dig_P1 = (uint16_t) ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x90, 2, data ); dig_P2 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x92, 2, data ); dig_P3 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x94, 2, data ); dig_P4 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x96, 2, data ); dig_P5 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x98, 2, data ); dig_P6 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x9A, 2, data ); dig_P7 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x9C, 2, data ); dig_P7 = (int16_t)  ( data[1] << 8 ) | data[0];
	I2C_read_many( I2C_BME280, BME280_addr, 0x9E, 2, data ); dig_P7 = (int16_t)  ( data[1] << 8 ) | data[0];

	dig_H1 = (uint8_t) I2C_read_one( I2C_BME280, BME280_addr, 0xA1 );					// Comment for BMP
					   I2C_read_many( I2C_BME280, BME280_addr, 0xE1, 7, data );			// Comment for BMP
	dig_H2 = (int16_t) ( data[0] | ( data[1] << 8 ) );									// Comment for BMP
	dig_H3 = (uint8_t) data[2];															// Comment for BMP
	dig_H4 = (int16_t) ( ( data[3] & 0x0FF0 ) | ( data[4] & 0x0F ) ); 					// Comment for BMP
	dig_H5 = (int16_t) ( ( data[4] & 0xF0 ) >> 4 ) | ( ( data[5] & 0x0FF0 ) );			// Comment for BMP
	dig_H6 = (int8_t) data[6];															// Comment for BMP

	I2C_write_one( I2C_BME280, BME280_addr, BME280_REG_CONFIG, BME280_CONFIG );
	I2C_write_one( I2C_BME280, BME280_addr, BME280_REG_CTRL_HUM, BME280_CONFIG_HUM );	// Comment for BMP
	I2C_write_one( I2C_BME280, BME280_addr, BME280_REG_CONTROL, BME280_MEAS );
}
// ===========================================================================
#endif
