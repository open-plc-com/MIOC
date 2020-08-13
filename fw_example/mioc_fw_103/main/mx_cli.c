/*
	Name:			mx_cli.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


int set_bit_func( unsigned int *name, bool bit );

// ===========================================================================
void Cli( void )
// ===========================================================================
{
	int			n_prm, i, n;
	char		str[RX_LEN];

	bool			*bool_ptr;
	int8_t			*i8_ptr;
	uint8_t			*ui8_ptr;
	int16_t			*i16_ptr;
	uint16_t		*ui16_ptr;
	int32_t			*i32_ptr, i32;
	uint32_t		*ui32_ptr;
	int64_t			*i64_ptr, i64;
	uint64_t		*ui64_ptr;
	float			*float_ptr;
	double			*double_ptr, d;

	if( ret_button )	// Return button is pressed
	{
		n_prm = parce_str( &str[0], 1 );
		if( !strlen( str ) )
		{
			n_prm = 0;
			clr_input();
		}
		else
		{
			// ---------------------------------------------------------------------------
			// Sn of Firmware
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "SNFW" ) == 0 )
			{
				print( "\r\nSN_FW %d\r\n", SN_FW );
			}
			else
			// ---------------------------------------------------------------------------
			// Echo
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "ECHO" ) == 0 )
			{
				if( n_prm == 1 )
				{
					if( Echo )
					{
						print_str( "\r\nECHO ON\r\n" );
					}
					else
					{
						print_str( "\r\nECHO OFF\r\n" );
					}
				}
				else
				{
					parce_str( &str[0], 2 );
					if( strcmp( ( char* ) str, "ON" ) == 0 )
					{
						Echo = TRUE;
					}
					else
					if( strcmp( ( char* ) str, "OFF" ) == 0 )
					{
						print_str( "\r\n" );
						Echo = FALSE;
					}
					else
					{
						print_str( "\r\nECHO ERR\r\n" );
					}
				}
			}
			else
			// ---------------------------------------------------------------------------
			// Show variables
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "SH" ) == 0 )
			{
				if( n_prm == 1 )
				{
					if( Show_Data )
					{
						print_str( "\r\nSH ON\r\n" );
					}
					else
					{
						print_str( "\r\nSH OFF\r\n" );
					}
				}
				else
				{
					parce_str( &str[0], 2 );
					if( strcmp( ( char* ) str, "ON" ) == 0 )
					{
						Show_Data = TRUE;
					}
					else
					if( strcmp( ( char* ) str, "OFF" ) == 0 )
					{
						print_str( "\r\n" );
						Show_Data = FALSE;
					}
					else
					{
						print_str( "\r\nSH ERR\r\n" );
					}
				}
			}
			else
			// ---------------------------------------------------------------------------
			// CLS; clear screen on show variables
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "CLS" ) == 0 )
			{
				if( n_prm == 1 )
				{
					if( CLS )
					{
						print_str( "\r\nCLS ON\r\n" );
					}
					else
					{
						print_str( "\r\nCLS OFF\r\n" );
					}
				}
				else
				{
					parce_str( &str[0], 2 );
					if( strcmp( ( char* ) str, "ON" ) == 0 )
					{
						CLS = TRUE;
					}
					else
					if( strcmp( ( char* ) str, "OFF" ) == 0 )
					{
						print_str( "\r\n" );
						CLS = FALSE;
					}
					else
					{
						print_str( "\r\nCLS ERR\r\n" );
					}
				}
			}
			else
			// ---------------------------------------------------------------------------
			// Print version
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "VER" ) == 0 )
			{
				print_str( "\r\n" );
				print_str( VER );
				print_str( "\r\n" );
			}
			else
			// ---------------------------------------------------------------------------
			// SET Variable Nn
			// ---------------------------------------------------------------------------
			if( strcmp( ( char* ) str, "SET" ) == 0 )
			{
				if( n_prm > 1 )
				{
					parce_str( &str[0], 2 );
					n = atoi( str );
					if( n > VAR_NN )
					{
						print_str( "ERR SET\r\n" );
					}
					else
					{
						n--;
						i = Var[n].gpio_type;
						if( !i || ( ( i > 2 ) && ( i < 7 ) ) )
						{
							parce_str( &str[0], 3 );

							switch( Var[n].var_type )
							{
								case 1:		// bool
										bool_ptr = (bool*) Var[n].name_ptr;
										i32 = atoi( str );
										if( !i )
										{
											if( i32 )
											{
												*bool_ptr = 1;
											}
											else
											{
												*bool_ptr = 0;
											}
										}
										else
										{
											if( i32 )
											{
												set_bit_func( (unsigned int*) Var[n].name_ptr, 1 );
											}
											else
											{
												set_bit_func( (unsigned int*) Var[n].name_ptr, 0 );
											}
										}
										break;
								case 2:		// int8
										i8_ptr = (int8_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*i8_ptr = i32;
										break;
								case 3:		// uint8
										ui8_ptr = (uint8_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*ui8_ptr = i32;
										break;
								case 4:		// int16
										i16_ptr = (int16_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*i16_ptr = i32;
										break;
								case 5:		// uint16
										ui16_ptr = (uint16_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*ui16_ptr = i32;
										break;
								case 6:		// int32
										i32_ptr = (int32_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*i32_ptr = i32;
										break;
								case 7:		// uint32
										ui32_ptr = (uint32_t*) Var[n].name_ptr;
										i32 = atoi( str );
										*ui32_ptr = i32;
										break;
								case 8:		// int64
										i64_ptr = (int64_t*) Var[n].name_ptr;
										i64 = atol( str );
										*i64_ptr = i64;
										break;
								case 9:		// uint64
										ui64_ptr = (uint64_t*) Var[n].name_ptr;
										i64 = atol( str );
										*ui64_ptr = i64;
										break;
								case 10:	//float
										float_ptr = (float*) Var[n].name_ptr;
										d = atof( str );
										*float_ptr = d;
										break;
								case 11:	// double
										double_ptr = (double*) Var[n].name_ptr;
										d = atof( str );
										*double_ptr = d;
							}
						}
					}
				}
				else
				{
					print_str( "ERR SET\r\n" );
				}
			}
			else
			{
				print_str( "\r\nUNKNOWN COMMAND\r\n" );
			}
			if( Echo )
			{
				print_str( "\r\n" );
			}

			clr_input();
		}
	}
}
// ===========================================================================
