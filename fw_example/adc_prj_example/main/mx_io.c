/*
	Name:			mx_io.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


// ===========================================================================
uint8_t w1_crc_update( uint8_t crc, uint8_t b )
// ===========================================================================
{
	uint8_t		i;

	for ( i = 8; i; i-- )
	{
		crc = ( ( crc ^ b ) & 1 ) ? ( ( crc >> 1 ) ^ 0x8C ) : ( crc >> 1 );
		b >>= 1;
	}
	return crc;
}
// ===========================================================================


// ===========================================================================
void w1_write_byte( uint16_t nn, uint8_t byte )
// ===========================================================================
{
	uint8_t		i, k;

	for( i = 0; i < 8; i++ )
	{
		if( i )
		{
			k = byte >> i;
		}
		else
		{
			k = byte;
		}
		k &= 1;
		if( k )		// send "1"
		{
			GPIO_ResetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 15 );
			GPIO_SetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 60 );
		}
		else		// send "0"
		{
			GPIO_ResetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 60 );
			GPIO_SetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 15 );
		}
	}
}
// ===========================================================================


// ===========================================================================
void w1_read_data( uint16_t nn )
// ===========================================================================
{
	uint8_t				i, j, l, n, crc;
	volatile uint8_t	m[10];	// Data buffer for 1-Wire
	volatile int16_t	data;
	volatile uint64_t	data_64;
	uint64_t			*ui64_ptr;
	volatile float		f;
	double		*d_ptr;

	for( i = 0; i < 9; i++ )
	{
		n = 0;
		for( j = 0; j < 8; j++ )
		{
			GPIO_ResetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 5 );
			GPIO_SetBits( Var[nn].gpio, Var[nn].gpio_pin );
			sys_delay_us( 10 );
			l = GPIO_ReadInputDataBit( Var[nn].gpio, Var[nn].gpio_pin );
			if( l )
			{
				n |= l << j;
			}
			sys_delay_us( 60 );
		}
		m[i] = n;
	}

	crc = 0;
	for( i = 0; i < 8; i++ )
	{
		crc = w1_crc_update( crc, m[i] );
	}

	if( Var[nn].gpio_type == 7 )	// DS18B20
	{
		d_ptr = (double*) Var[nn].name_ptr;
		if( crc == m[8] )	// CRC Ok
		{
			data = m[1];
			data <<= 8;
			data |= m[0];
			f = data / 16.0;
			*d_ptr = f;
			Var[nn].err_1w = 0;
		}
		else
		{
			if( Var[nn].err_1w < MAX_W1_ERR )
			{
				Var[nn].err_1w++;
			}
			else
			{
				*d_ptr = 512.0;
			}
		}
	}
	else
	if( Var[nn].gpio_type == 8 )	// iButton
	{
		ui64_ptr = (uint64_t*) Var[nn].name_ptr;
		data_64 = 0;
		for( i = 0; i < 8; i++ )
		{
			data_64 <<= 8;
			data_64 |= m[i];
		}
		if( data_64 == 0xFFFFFFFFFFFFFFFF )
		{
			if( Var[nn].ibutton_time )
			{
				Var[nn].ibutton_time--;
			}
			else
			{
				*ui64_ptr = data_64;
				Var[nn].ibutton_time = iButton_Timeout;
			}
		}
		else
		{
			*ui64_ptr = data_64;
		}
	}
}
// ===========================================================================


// ===========================================================================
void Read_Data( void )
// ===========================================================================
{
	int			i, j;
	bool		b, *b_ptr;
	uint16_t	*ui16_ptr;
	#ifdef BME280
	int32_t		p1, p2, p3;
	#endif

	if( !Lc1 ) Lc1 = CntTime;
	if( !Lc2 ) Lc2 = CntTime;
	if( !Lc3 ) Lc3 = CntTime;
	if( !Lc4 ) Lc4 = CntTime;
	if( !Lc5 ) Lc5 = CntTime;
	if( !Lc6 ) Lc6 = CntTime;

	// ---------------------------------------------------------------------------
	// --- DS18B20
	// ---------------------------------------------------------------------------
	if( Step_DS == 0 )
	{
		for( i = 0; i < VAR_NN; i++ )
		{
			if( Var[i].gpio_type == 7 )
			{
				// Reset sensor
				GPIO_ResetBits( Var[i].gpio, Var[i].gpio_pin );
				sys_delay_us( 500 );
				GPIO_SetBits( Var[i].gpio, Var[i].gpio_pin );
				sys_delay_us( 500 );

				// Start calculate
				w1_write_byte( i, 0xCC );
				sys_delay_us( 30 );
				w1_write_byte( i, 0x44 );
			}
			Step_DS = 1;
			Lc1 = CntTime;
		}
	}
	else
	if( Step_DS == 1 )	// Wait for calculate
	{
		if( ( CntTime - Lc1 ) >= 100 )
		{
			Step_DS = 2;
			Lc1 = CntTime;
		}
	}
	else
	if( Step_DS == 2 )	// Read values
	{
		for( i = 0; i < VAR_NN; i++ )
		{
			if( Var[i].gpio_type == 7 )
			{
				// Reset sensor
				GPIO_ResetBits( Var[i].gpio, Var[i].gpio_pin );
				sys_delay_us( 500 );
				GPIO_SetBits( Var[i].gpio, Var[i].gpio_pin );
				sys_delay_us( 500 );

				// Get data
				w1_write_byte( i, 0xCC );
				sys_delay_us( 30 );
				w1_write_byte( i, 0xBE );
				sys_delay_us( 30 );
				w1_read_data( i );
			}
			Step_DS = 3;
			Lc1 = CntTime;
		}
	}
	else
	if( Step_DS == 3 )	// Wait 3 sec
	{
		if( ( CntTime - Lc1 ) >= 300 )
		{
			Step_DS = 0;
			Lc1 = CntTime;
		}
	}

	// ---------------------------------------------------------------------------
	// --- iButton
	// ---------------------------------------------------------------------------
	if( Step_BTN == 0 )
	{
		for( i = 0; i < VAR_NN; i++ )
		{
			if( Var[i].gpio_type == 8 )
			{
				GPIO_ResetBits( Var[i].gpio, Var[i].gpio_pin );
			}
		}
		Step_BTN = 1;
		Lc2 = CntTime;
	}
	else
	if( Step_BTN == 1 )
	{
		if( ( CntTime - Lc2 ) >= 25 )
		{
			for( i = 0; i < VAR_NN; i++ )
			{
				if( Var[i].gpio_type == 8 )
				{
					GPIO_SetBits( Var[i].gpio, Var[i].gpio_pin );
				}
			}

			sys_delay_us( 500 );

			for( i = 0; i < VAR_NN; i++ )
			{
			 	if( Var[i].gpio_type == 8 )
				{
					// Get data
					w1_write_byte( i, 0x33 );
					sys_delay_us( 60 );
					w1_read_data( i );
				}
			}
			Step_BTN = 0;
		}
	}

	// ---------------------------------------------------------------------------
	// --- Read ADC & GPIO
	// ---------------------------------------------------------------------------
	for( i = 0; i < VAR_NN; i++ )
	{
		if( Var[i].gpio_type == 1 )
		{
			ui16_ptr = (uint16_t*) Var[i].name_ptr;
			for( j = 0; j < ADC_NN; j++ )
			{
				if( Var[i].name_ptr == ADC_NAME_PTR[j] )
				{
					ui16_ptr[0] = ADC_AVG[j];
					break;
				}
			}
		}
		else
		if( ( Var[i].gpio_type > 1 ) && ( Var[i].gpio_type < 7 ) )
		{
			b = GPIO_ReadInputDataBit( Var[i].gpio, Var[i].gpio_pin );
			b_ptr = (bool*) Var[i].name_ptr;
			*Var[i].name_ptr = 0;
			b_ptr[0] = b;
		}
	}

	// ---------------------------------------------------------------------------
	// --- Read BME
	// ---------------------------------------------------------------------------
	#ifdef BME280
		if( ( CntTime - Lc4 ) >= 400 )
		{
			Lc4 = CntTime;
			bme280Convert( &p1, &p2, &p3 );
			if( !p2 || !p3 )
			{
				p1 = 0;
				if( ( I2C_BME280 == I2C1 ) && ( I2C1_ERR > 5 ) )
				{
					I2C1_ERR = 0;
					BME280_Init();
				}
				else
				if( ( I2C_BME280 == I2C2 ) && ( I2C2_ERR > 5 ) )
				{
					I2C2_ERR = 0;
					BME280_Init();
				}
			}
			BME_T = p1;
			BME_P = p2;
			BME_H = p3;
		}
	#endif

	// ---------------------------------------------------------------------------
	// --- Read BH1750
	// ---------------------------------------------------------------------------
	#ifdef BH1750
		if( ( CntTime - Lc5 ) >= 50 )
		{
			Lc5 = CntTime;
			BH_L = BH1750_Read();
		}
	#endif

	// ---------------------------------------------------------------------------
	// --- Read CCS811
	// ---------------------------------------------------------------------------
	#ifdef CCS811
		if( ( CntTime - Lc6 ) >= 100 )
		{
			Lc6 = CntTime;
			CCS811_read( &CCS_CO2, &CCS_TVOC );
		}
	#endif
}
// ===========================================================================


// ===========================================================================
void Print_Data( void )
// ===========================================================================
{
	unsigned int	 i;
	bool			*bool_ptr;
	int8_t			*i8_ptr;
	uint8_t			*ui8_ptr;
	int16_t			*i16_ptr;
	uint16_t		*ui16_ptr;
	int32_t			*i32_ptr;
	uint32_t		*ui32_ptr;
	int64_t			*i64_ptr;
	uint64_t		*ui64_ptr;
	float			*float_ptr;
	double			*double_ptr;

	if( ( ( CntTime - Lc3 ) > ( SHOW_DATA_INTERVAL ) ) && ( !usart_rx_data[0] || !Echo ) )
	{
		if( CLS )
		{
			print_str( "\33[H\33[2J" );	// Esc[H - Move cursor to upper left corner; Esc[2J - Clear entire screen
		}

		for( i = 0; i < VAR_NN; i++ )
		{
			switch( Var[i].var_type )
			{
			case 1:		// bool
					bool_ptr = (bool*) Var[i].name_ptr;
					print( "%-8u %u\r\n", (i+1), *bool_ptr );
					break;
			case 2:		// int8
					i8_ptr = (int8_t*) Var[i].name_ptr;
					print( "%-8u %d\r\n", (i+1), *i8_ptr );
					break;
			case 3:		// uint8
					ui8_ptr = (uint8_t*) Var[i].name_ptr;
					print( "%-8u %u\r\n", (i+1), *ui8_ptr );
					break;
			case 4:		// int16
					i16_ptr = (int16_t*) Var[i].name_ptr;
					print( "%-8u %d\r\n", (i+1), *i16_ptr );
					break;
			case 5:		// uint16
					ui16_ptr = (uint16_t*) Var[i].name_ptr;
					print( "%-8u %u\r\n", (i+1), *ui16_ptr );
					break;
			case 6:		// int32
					i32_ptr = (int32_t*) Var[i].name_ptr;
					print( "%-8u %d\r\n", (i+1), *i32_ptr );
					break;
			case 7:		// uint32
					ui32_ptr = (uint32_t*) Var[i].name_ptr;
					print( "%-8u %u\r\n", (i+1), *ui32_ptr );
					break;
			case 8:		// int64
					i64_ptr = (int64_t*) Var[i].name_ptr;
					print( "%-8u %lld\r\n", (i+1), *i64_ptr );
					break;
			case 9:		// uint64
					ui64_ptr = (uint64_t*) Var[i].name_ptr;
					print( "%-8u %llu\r\n", (i+1), *ui64_ptr );
					break;
			case 10:	//float
					float_ptr = (float*) Var[i].name_ptr;
					print( "%-8u %f\r\n", (i+1), *float_ptr );
					break;
			case 11:	// double
					double_ptr = (double*) Var[i].name_ptr;
					print( "%-8u %f\r\n", (i+1), *double_ptr );
			}
		}

		#ifdef BME280
			print( "BME_T    %.1f\r\n", (float) ( BME_T / 10.0 ) );
			print( "BME_P    %.1f\r\n", (float) ( BME_P / 100.0 ) );
			print( "BME_H    %.1f\r\n", (float) ( BME_H / 10.0 ) );
		#endif

		#ifdef BH1750
			print( "BH_L     %u\r\n", BH_L );
		#endif

		#ifdef CCS811
			print( "CCS_CO2  %u\r\n", CCS_CO2 );
			print( "CCS_TVOC %u\r\n", CCS_TVOC );
		#endif

		#ifdef LCD_1602
			if( strlen( (char*)LCD1[0].data ) ) print( "LCD1     %s\r\n", LCD1[0].data );
			if( strlen( (char*)LCD1[1].data ) ) print( "LCD2     %s\r\n", LCD1[1].data );
		#endif

		Lc3 = CntTime;

		print_str( "\r\n" );
	}
}
// ===========================================================================


// ===========================================================================
int set_bit_func( unsigned int *name, bool bit )
// ===========================================================================
{
	uint32_t i, n;
	n = 0;
	for( i = 0; i < VAR_NN; i++ )
	{
		if( Var[i].name_ptr == name )
		{
			n = i + 1;
			break;
		}
	}
	if( n )
	{
		n--;
		if( ( Var[n].gpio_type == 3 ) ||\
			( Var[n].gpio_type == 4 ) ||\
			( Var[n].gpio_type == 5 ) ||\
			( Var[n].gpio_type == 6 ) )
		{
			if( bit )
			{
				GPIO_SetBits( Var[n].gpio, Var[n].gpio_pin );
			}
			else
			{
				GPIO_ResetBits( Var[n].gpio, Var[n].gpio_pin );
			}
		}
		else
		{
			return 1;
		}
	}
	return 0;
}
// ===========================================================================
