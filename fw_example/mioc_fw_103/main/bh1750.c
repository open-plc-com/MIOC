/*
	Name:			bh1750.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/10
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#define BH1750Address 0x23
//#define BH1750Address 0x5C


// ===========================================================================
void I2C_start( I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction )
// ===========================================================================
{
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) ){}
	I2C_GenerateSTART( I2Cx, ENABLE );
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) ){}
	I2C_Send7bitAddress( I2Cx, address, direction );
	if( direction == I2C_Direction_Transmitter )
	{
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) ){}
	}
	else
	if( direction == I2C_Direction_Receiver )
	{
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) ){}
	}
}
// ===========================================================================


// ===========================================================================
void I2C_write( I2C_TypeDef *I2Cx, uint8_t data )
// ===========================================================================
{
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTING ) ){}
	I2C_SendData( I2Cx, data );
}
// ===========================================================================


// ===========================================================================
void I2C_stop( I2C_TypeDef *I2Cx )
// ===========================================================================
{
	I2C_GenerateSTOP( I2Cx, ENABLE );
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) ){}
}
// ===========================================================================


// ===========================================================================
void BH1750_Init( void )
// ===========================================================================
{
	I2C_start( I2C_BH1750, ( BH1750Address << 1 ), I2C_Direction_Transmitter );
	I2C_write( I2C_BH1750, 0x10 );
	I2C_stop( I2C_BH1750 );
	delay_ms( 200 );
}
// ===========================================================================


// ===========================================================================
uint32_t BH1750_Read( void )
// ===========================================================================
{
	uint8_t		buf[2];
	I2C_read_many( I2C_BH1750, ( BH1750Address << 1 ), 0x11, 2, buf );
	return ( ( ( buf[0] << 8 ) | buf[1] ) / 1.2 );
}
// ===========================================================================
