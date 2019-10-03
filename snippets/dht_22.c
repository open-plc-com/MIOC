/*
	Name:			dht_22.c
	Purpose:		Get data from sensor DHT22
	Author:			Open-PLC.com
	Created:		2016/07
	Modified by:	2019/02
	RCS-ID:
	Copyright:		(c) open-plc.com
	Licence:		The MIT License (MIT)

	The result is recorded in a variables:
		DHT_h	- humidity
		DHT_t	- temperature

	Increment timer frequency ( CntTime ) = 10 mS
*/

#define SENSOR_PIN (GPIOA, GPIO_Pin_5)

void dht_init( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit( &GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_10MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
	GPIO_SetBits SENSOR_PIN;
}

// ===========================================================================
int8_t get_dht_data( int16_t *DHT_t, int16_t *DHT_h )
// ===========================================================================
{
	uint8_t		*ui8;
	uint16_t	ui16_t, ui16_h;
	uint32_t	i, n, n0, n1, start_time;
	uint64_t	result;

	result = 0;
	*DHT_h = 0;
	*DHT_t = 0;

	// Request for get data
	GPIO_SetBits SENSOR_PIN;
	delay_ms( 500 );
	GPIO_ResetBits SENSOR_PIN;
	delay_ms( 20 );
	GPIO_SetBits SENSOR_PIN;
	start_time = CntTime;

	while( GPIO_ReadInputDataBit SENSOR_PIN )	// Skip sensor response "1" ( 20-40 uS )
	{
		if( abs( CntTime - start_time ) > 20 )	// Waiting for more than 200 mS - the sensor does not send data
		{
			return 1;
		}
	}
	while( !GPIO_ReadInputDataBit SENSOR_PIN )	// Skip sensor response "0" ( 80 uS )
	{
		if( abs( CntTime - start_time ) > 20 )	// Waiting for more than 200 mS - the sensor does not send data
		{
			return 1;
		}
	}
	while( GPIO_ReadInputDataBit SENSOR_PIN )	// Skip sensor response "1" ( 80 uS )
	{
		if( abs( CntTime - start_time ) > 20 )	// Waiting for more than 200 mS - the sensor does not send data
		{
			return 1;
		}
	}

	// Read data
	for( i = 0; i < 40; i++ )
	{
		n0 = 0;										// Duration "0"
		while( !GPIO_ReadInputDataBit SENSOR_PIN )	// Skip sensor response "0"
		{
			n0++;
			if( abs( CntTime - start_time ) > 20 )	// Waiting for more than 200 mS - the sensor does not send data
			{
				return 1;
			}
		}

		n1 = 0;										// Duration "1"
		while( GPIO_ReadInputDataBit SENSOR_PIN )	// Skip sensor response "1"
		{
			n1++;
			if( abs( CntTime - start_time ) > 20 )	// Waiting for more than 200 mS - the sensor does not send data
			{
				return 1;
			}
		}

		if( n0 < n1 )	// If the duration of "0" is less than the duration "1", this reading "1"
		{
			n = 1;
		}
		else			// Otherwise reading "0"
		{
			n = 0;
		}

		result = result << 1;
		if( n )
		{
			result |= n;
		}
	}

	// calculate CS
	n = 0;
	ui8 = ( uint8_t* ) &result;
	for( i = 1; i < 5; i++ )
	{
		n += ui8[i];
	}
	n = n & 0xFF;

	if( n != ui8[0] )	// CS not equal - error 2
	{
		return 2;
	}
	else	// CS is equal
	{
		ui16_t = ui8[2];
		ui16_t = ui16_t << 8;
		ui16_t |= ui8[1];

		if( ui16_t & 0x8000 )
		{
			ui16_t = ui16_t & 0x7FFF;
			*DHT_t = -ui16_t;
		}
		else
		{
			*DHT_t = ui16_t;
		}

		ui16_h = ui8[4];
		ui16_h = ui16_h << 8;
		ui16_h |= ui8[3];
		*DHT_h = ui16_h;
	}
	return 0;
}
// ===========================================================================
