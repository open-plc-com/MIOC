/*
	Purpose:		IO module
	Author:			www.open-plc.com;
	Created:		2018/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


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
