/*
	Name:			mx_i2c.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/10
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#ifdef SSD1306_FAST
#ifndef __ssd1306_I2C_H__
#define __ssd1306_I2C_H__

#define ssd1306_I2C_TIMEOUT		200000
#define I2C_TRANSMITTER_MODE	0
#define I2C_RECEIVER_MODE		1
#define I2C_ACK_ENABLE			1
#define I2C_ACK_DISABLE			0

static uint32_t	ssd1306_I2C_Timeout;

void	init_I2C1( void );
void	ssd1306_I2C_Write( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t data );
void	ssd1306_I2C_WriteMulti( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count );
uint8_t	ssd1306_I2C_Start( I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction, uint8_t ack );
void	ssd1306_I2C_WriteData( I2C_TypeDef *I2Cx, uint8_t data );

#endif	// __ssd1306_I2C_H__
#endif	// SSD1306_FAST

#ifndef I2C_TIMEOUT
	#define I2C_TIMEOUT 200000
	//#define I2C_TIMEOUT 2000	// for scanner
#endif

#ifdef I2C1_D
// ===========================================================================
void init_I2C1( void )
// ===========================================================================
{
	// --- I2C1 ---
	// PB6 - SCL
	// PB7 - SDA

	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

	I2C_Cmd( I2C1, DISABLE );
	I2C_StructInit( &I2C_InitStructure );

	// Configure I2C pins
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_OD;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	// I2C configuration
	I2C_InitStructure.I2C_Mode					= I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle				= I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1			= 0;
	I2C_InitStructure.I2C_Ack					= I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed			= 100000;
	I2C_Init( I2C1, &I2C_InitStructure );

	I2C_Cmd( I2C1, ENABLE );
}
// ===========================================================================
#endif


#ifdef I2C2_D
// ===========================================================================
void init_I2C2( void )
// ===========================================================================
{
	// --- I2C1 ---
	// PB10 - SCL
	// PB11 - SDA

	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

	I2C_Cmd( I2C2, DISABLE );
	I2C_StructInit( &I2C_InitStructure );

	// Configure I2C pins
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// I2C configuration
	I2C_InitStructure.I2C_Mode					= I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle				= I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1			= 0;
	I2C_InitStructure.I2C_Ack					= I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed			= 100000;
	I2C_Init( I2C2, &I2C_InitStructure );

	I2C_Cmd( I2C2, ENABLE );
}
// ===========================================================================
#endif


#if defined I2C1_D || defined I2C2_D
// ===========================================================================
void I2C_write_one( I2C_TypeDef *I2Cx, uint8_t hw_address, uint8_t addr, uint8_t data )
// ===========================================================================
{
	static uint32_t I2C_Timeout;

	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Transmitter );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_SendData( I2Cx, addr );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_SendData( I2Cx, data );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_GenerateSTOP( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	//delay_ms( 5 );

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}
}
// ===========================================================================


// ===========================================================================
void I2C_write_many( I2C_TypeDef *I2Cx, uint8_t hw_address, uint8_t addr, uint8_t n_data, uint8_t *data )
// ===========================================================================
{
	static uint32_t I2C_Timeout;

	//I2C_AcknowledgeConfig( I2Cx, ENABLE );
	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Transmitter);
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_SendData( I2Cx, addr );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}
	while( n_data-- )
	{
		I2C_SendData( I2Cx, *data++ );
		I2C_Timeout = I2C_TIMEOUT;
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
		{
			if( --I2C_Timeout == 0 )
			{
				if( I2Cx == I2C1 )
				{
					I2C1_ERR++;
				}
				else
				if( I2Cx == I2C2 )
				{
					I2C2_ERR++;
				}
				return;
			}
		}
	}
	I2C_GenerateSTOP( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	//delay_ms( 5 );

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}
}
// ===========================================================================


// ===========================================================================
uint8_t I2C_read_one( I2C_TypeDef *I2Cx, uint8_t hw_address, uint8_t addr )
// ===========================================================================
{
	uint8_t data;
	static uint32_t I2C_Timeout;

	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Transmitter );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	I2C_SendData( I2Cx, addr );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Receiver );
	I2C_AcknowledgeConfig( I2Cx, ENABLE );

	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}
	data = I2C_ReceiveData( I2Cx );

	I2C_AcknowledgeConfig( I2Cx, DISABLE );
	I2C_GenerateSTOP( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 0;
		}
	}

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}

	return data;
}
// ===========================================================================


// ===========================================================================
void I2C_read_many( I2C_TypeDef *I2Cx, uint8_t hw_address, uint8_t addr, uint8_t n_data, uint8_t *data )
// ===========================================================================
{
	static uint32_t I2C_Timeout;

	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Transmitter );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_SendData( I2Cx, addr );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	//I2C_GenerateSTOP( I2Cx, ENABLE );
	I2C_GenerateSTART( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2C_AcknowledgeConfig( I2Cx, ENABLE );
	I2C_Send7bitAddress( I2Cx, hw_address, I2C_Direction_Receiver );
	I2C_Timeout = I2C_TIMEOUT;
	while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}
	while( n_data-- )
	{
		if( !n_data )
		{
			I2C_AcknowledgeConfig( I2Cx, DISABLE );
		}
		I2C_Timeout = I2C_TIMEOUT;
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED ) )
		{
			if( --I2C_Timeout == 0 )
			{
				if( I2Cx == I2C1 )
				{
					I2C1_ERR++;
				}
				else
				if( I2Cx == I2C2 )
				{
					I2C2_ERR++;
				}
				return;
			}
		}
		*data++ = I2C_ReceiveData( I2Cx );
		delay_us( 20 );
	}
	I2C_AcknowledgeConfig( I2Cx, DISABLE );
	I2C_GenerateSTOP( I2Cx, ENABLE );
	I2C_Timeout = I2C_TIMEOUT;
	while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
	{
		if( --I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}
}
// ===========================================================================


#ifdef SSD1306_FAST
// ===========================================================================
uint8_t ssd1306_I2C_Start( I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction, uint8_t ack )
// ===========================================================================
{
	I2Cx->CR1 |= I2C_CR1_START;
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while( !( I2Cx->SR1 & I2C_SR1_SB ) )
	{
		if( --ssd1306_I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 1;
		}
	}

	if( ack )
	{
		I2Cx->CR1 |= I2C_CR1_ACK;
	}

	if( direction == I2C_TRANSMITTER_MODE )
	{
		I2Cx->DR = address & ~I2C_OAR1_ADD0;
		ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
		while( !( I2Cx->SR1 & I2C_SR1_ADDR ) )
		{
			if( --ssd1306_I2C_Timeout == 0 )
			{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 1;
			}
		}
	}
	if( direction == I2C_RECEIVER_MODE )
	{
		I2Cx->DR = address | I2C_OAR1_ADD0;
		ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) )
		{
			if( --ssd1306_I2C_Timeout == 0 )
			{
				if( I2Cx == I2C1 )
				{
					I2C1_ERR++;
				}
				else
				if( I2Cx == I2C2 )
				{
					I2C2_ERR++;
				}
				return 1;
			}
		}
	}
	I2Cx->SR2;

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}

	return 0;
}
// ===========================================================================


// ===========================================================================
uint8_t ssd1306_I2C_Stop( I2C_TypeDef *I2Cx )
// ===========================================================================
{
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while( ( ( !(I2Cx->SR1 & I2C_SR1_TXE ) ) || ( !( I2Cx->SR1 & I2C_SR1_BTF ) ) ) )
	{
		if( --ssd1306_I2C_Timeout == 0 )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return 1;
		}
	}
	I2Cx->CR1 |= I2C_CR1_STOP;

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}

	return 0;
}
// ===========================================================================


// ===========================================================================
void ssd1306_I2C_WriteMulti( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count )
// ===========================================================================
{
	uint8_t i;

	ssd1306_I2C_Start( I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE );
	ssd1306_I2C_WriteData( I2Cx, reg );
	for( i = 0; i < count; i++ )
	{
		ssd1306_I2C_WriteData( I2Cx, data[i] );
	}
	ssd1306_I2C_Stop( I2Cx );
}
// ===========================================================================


// ===========================================================================
void ssd1306_I2C_WriteData( I2C_TypeDef *I2Cx, uint8_t data )
// ===========================================================================
{
	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while( !( I2Cx->SR1 & I2C_SR1_TXE ) && ssd1306_I2C_Timeout )
	{
		ssd1306_I2C_Timeout--;
		if( !ssd1306_I2C_Timeout )
		{
			if( I2Cx == I2C1 )
			{
				I2C1_ERR++;
			}
			else
			if( I2Cx == I2C2 )
			{
				I2C2_ERR++;
			}
			return;
		}
	}

	I2Cx->DR = data;

	if( I2Cx == I2C1 )
	{
		I2C1_ERR = 0;
	}
	else
	if( I2Cx == I2C2 )
	{
		I2C2_ERR = 0;
	}
}
// ===========================================================================


// ===========================================================================
void ssd1306_I2C_Write( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t data )
// ===========================================================================
{
	ssd1306_I2C_Start( I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE );
	ssd1306_I2C_WriteData( I2Cx, reg );
	ssd1306_I2C_WriteData( I2Cx, data );
	ssd1306_I2C_Stop( I2Cx );
}
// ===========================================================================


// ===========================================================================
uint8_t ssd1306_I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t address)
// ===========================================================================
{
	uint8_t	connected = 0;
	if( !ssd1306_I2C_Start( I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE ) )
	{
		connected = 1;
	}
	ssd1306_I2C_Stop( I2Cx );
	return connected;
}
// ===========================================================================
#endif	// SSD1306_FAST

#endif	// defined I2C1_D || defined I2C2_D
