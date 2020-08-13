/*
	Purpose:		IO module
	Author:			www.open-plc.com;
	Created:		2018/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/

//#ifdef LCD_SSD1306
//uint8_t SSD1306_Init( void );
//#endif

#ifdef I2C1_D_
I2C_InitTypeDef			i2c1;
// ===========================================================================
void init_I2C1( void )
// ===========================================================================
{
	GPIO_InitTypeDef	i2c_gpio;

	I2C_Cmd( I2C1, DISABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, DISABLE );
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

	// --- I2C1 ---
	// PB6 - SCL
	// PB7 - SDA
	GPIO_StructInit( &i2c_gpio );
	i2c_gpio.GPIO_Pin				= GPIO_Pin_6 | GPIO_Pin_7;
	i2c_gpio.GPIO_Mode				= GPIO_Mode_AF_OD;
	i2c_gpio.GPIO_Speed				= GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &i2c_gpio );

	i2c1.I2C_ClockSpeed				= 100000;
	i2c1.I2C_Mode					= I2C_Mode_I2C;
	i2c1.I2C_DutyCycle				= I2C_DutyCycle_2;
	i2c1.I2C_OwnAddress1			= 0;
	i2c1.I2C_Ack					= I2C_Ack_Enable;
	i2c1.I2C_AcknowledgedAddress	= I2C_AcknowledgedAddress_7bit;
	I2C_Init( I2C1, &i2c1 );

	I2C_Cmd( I2C1, ENABLE );
}
// ===========================================================================
#endif


#ifdef LCD_1602
// ===========================================================================
int I2C_StartTransmission( I2C_TypeDef *I2Cx, uint8_t transmissionDirection, uint8_t slaveAddress )
// ===========================================================================
{
	uint32_t	lc;

	if( !I2C1_ERR )
	{
		//if( I2C1_ERR )
		//{
			//I2C_GenerateSTOP( I2Cx, ENABLE );
		//}
		
		lc = CntTime;
		while( I2C_GetFlagStatus( I2Cx, I2C_FLAG_BUSY ) )
		{
			if( ( CntTime - lc ) > 20 ) { I2C1_ERR++; return 1; }
		}
		lc = CntTime;
		I2C_GenerateSTART( I2Cx, ENABLE );
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_MODE_SELECT ) )
		{
			if( ( CntTime - lc ) > 20 ) { I2C1_ERR++; return 2; }
		}
		I2C_Send7bitAddress( I2Cx, ( slaveAddress << 1 ), transmissionDirection );

		if( transmissionDirection == I2C_Direction_Transmitter )
		{
			lc = CntTime;
			while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
			{
				if( ( CntTime - lc ) > 20 ) { I2C1_ERR++; return 3; }
			}
		}
		else
		if( transmissionDirection == I2C_Direction_Receiver )
		{
			lc = CntTime;
			while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED ) )
			{
				if( ( CntTime - lc ) > 20 ) { I2C1_ERR++;  return 4; }
			}
		}
		I2C1_ERR = 0; return 0;
	}
	return 0;
}
// ===========================================================================


// ===========================================================================
int I2C_WriteData( I2C_TypeDef *I2Cx, uint8_t data )
// ===========================================================================
{
	uint32_t	lc;

	if( !I2C1_ERR )
	{
		lc = CntTime;
		I2C_SendData( I2Cx, data );
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
		{
			if( ( CntTime - lc ) > 20 ) { I2C1_ERR++; return 1; }
		}
		I2C1_ERR = 0; return 0;
	}
	return 0;
}
// ===========================================================================


// ===========================================================================
uint8_t I2C_ReadData( I2C_TypeDef *I2Cx )
// ===========================================================================
{
	uint32_t	lc;
	uint8_t		data;

	if( !I2C1_ERR )
	{
		lc = CntTime;
		data = I2C_ReceiveData( I2Cx );
		while( !I2C_CheckEvent( I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED ) )
		{
			if( ( CntTime - lc ) > 20 ) { I2C1_ERR++; return 1; }
		}
		return data;
	}
	return 0;
}
// ===========================================================================
#endif


#ifdef _SSD1306
// ===========================================================================
int16_t ssd1306_I2C_Start( I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction, uint8_t ack )
// ===========================================================================
{
	I2Cx->CR1 |= I2C_CR1_START;

	ssd1306_I2C_Timeout = ssd1306_I2C_TIMEOUT;
	while ( !( I2Cx->SR1 & I2C_SR1_SB ) )
	{
		if( --ssd1306_I2C_Timeout == 0x00 )
		{
			I2C1_ERR++;
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
			if( --ssd1306_I2C_Timeout == 0x00 )
			{
				I2C1_ERR++;
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
			if( --ssd1306_I2C_Timeout == 0x00 )
			{
				I2C1_ERR++;
				return 1;
			}
		}
	}
	I2Cx->SR2;
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
		if( --ssd1306_I2C_Timeout == 0x00 )
		{
			I2C1_ERR++;
			return 1;
		}
	}
	I2Cx->CR1 |= I2C_CR1_STOP;
	return 0;
}
// ===========================================================================


// ===========================================================================
void ssd1306_I2C_WriteMulti( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count )
// ===========================================================================
{
	uint8_t		i;

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
			I2C1_ERR++;
		}
	}
	I2Cx->DR = data;
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
	uint8_t		connected = 0;
	if( !ssd1306_I2C_Start( I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE ) )
	{
		connected = 1;
	}
	ssd1306_I2C_Stop(I2Cx);
	return connected;
}
// ===========================================================================


#endif
