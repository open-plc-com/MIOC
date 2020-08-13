/*
	Name:			mx_cli.c
	Purpose:		FirmWare for STM32F103C8T6: DS18B20, iButton, GPIO
	Author:			Alexander Suvorov (www.open-plc.com)
	Created:		2016/07
	Modified by:	2017/12
	RCS-ID:
	Copyright:		(c) Alexander Suvorov
	Licence:		The MIT License (MIT)
*/




// ===========================================================================
void Show_Params( void )
// ===========================================================================
{
	int			i, j, n;
	char		s[RX_LEN];

	#ifdef CAN_2515
		switch( Speedc )
		{
			case 0:		n = 500000;		break;
			case 1:		n = 250000;		break;
			case 2:		n = 125000;		break;
			case 3:		n = 100000;		break;
			case 4:		n = 50000;		break;
			case 5:		n = 20000;		break;
			case 6:		n = 10000;		break;
			default:	n = 0;
		}
	#endif
	print_str( "\r\n\r\n" );
	sprintf( s, "Name         Value\r\n" );								print_str( s );
	sprintf( s, "-----------  ----------\r\n" );						print_str( s );
//	sprintf( s, "Device Type  %u\r\n", ( unsigned int ) DeviceType );	print_str( s );
//	sprintf( s, "S/N          %u\r\n", ( unsigned int ) Sn );			print_str( s );
	#ifdef CAN_2515
		sprintf( s, "Nn on CAN    %u\r\n", ( unsigned int ) Noc );		print_str( s );
		sprintf( s, "CAN Speed    %d bps\r\n", n );						print_str( s );
	#endif
	sprintf( s, "BTN timeout  %d sec\r\n", ( iButton_Timeout / 8 ) );	print_str( s );
	//sprintf( s, "Show Data    %d\r\n", Show_Data );						print_str( s );
	print_str( "\r\n" );
	print_str( "ch port GPIO Type\r\n" );
	print_str( "-- ---- ---------\r\n" );

	for( i = 0; i < Nn_Ch; i++ )
	{
		sprintf( s, "%2u ", ( i + 1 ) ); print_str(s);
		j = 0;
		if( GPIO_X[i].gpio_x == GPIOA )
		{
			print_str( "PA" );
			j = 1;
		}
		else
		if( GPIO_X[i].gpio_x == GPIOB )
		{
			print_str( "PB" );
			j = 1;
		}
		else
		if( GPIO_X[i].gpio_x == GPIOC )
		{
			print_str( "PC" );
			j = 1;
		}
		else
		{
			print_str( "----" );
		}

		if( j )
		{
			sprintf( s, "%-2u", GPIO_X[i].gpio_pin_nn ); print_str( s );
		}

		switch( GPIO_X[i].dev_type )
		{
			case 0:		print_str( " ----" );								break;
			case 1:		print_str( " (1) DS18B20" );						break;
			case 2:		print_str( " (2) iButton" );						break;
			case 3:		print_str( " (3) bidirectional GPIO pulldown" );	break;
			case 4:		print_str( " (4) bidirectional GPIO pullup" );	break;
			case 5:		print_str( " (5) GPIO_Mode Input Floating" );		break;
			case 6:		print_str( " (6) ADC" );							break;
			default:	print_str( " ----" );
		}
	print_str( "\r\n" );
	}	// for( i = 0; i < Nn_Ch; i++ )
}
// ===========================================================================


// ===========================================================================
int ADC_Menu( void )
// ===========================================================================
{
	char	s[RX_LEN];
	char	*s1 = "\r\nThe coefficients of the equation y = a * x + b\r\n";
	int		i, j, k, n, n1, m;
	int		space_index[6];		// max 6 params

double	x1, y1, x2, y2;

//	uint16_t		n1, n2, n3, n4;

	volatile bool	change_prm;
	volatile bool	quit;



	change_prm	= FALSE;
	m			= sizeof( space_index ) / sizeof( int );
	quit		= FALSE;

	strcpy( ( char* ) cli_data, "\r\nADC Config> " );
	clr_input();
	print_str( "\r\n? - help\r\n" );
	print_str( ( char* ) cli_data );

	while( !quit )
	{
		if( ret_button )	// Press Enter
		{
			ret_button	= FALSE;
			n			= strlen( ( char* ) usart_rx_data );
			if( n )	// Length > 0
			{
				s[0] = 0;
				parce_str( ( char* ) &s, 1 );
				//parce_cmd( ( char* ) &s, ( int* ) &space_index, m );
				//print_str( s ); print_str( "\r\n" );
				//print_str( ( char* ) cli_data );

				// -----------------------------------------------------------
				if( strcmp( s, "Q" ) == 0 )
				{
					quit = true;
				}	// if( strcmp( s, "Q" ) == 0 )
				// -----------------------------------------------------------

				// -----------------------------------------------------------
				else
				if( strcmp( s, "?" ) == 0 )
				{
					print_str( "\r\n" );
					print_str( "\r\n?                 - This page" );
					print_str( "\r\nq                 - Exit from Config" );
					print_str( "\r\nsh                - Show parameters" );
					print_str( "\r\nac N#             - Set channel as AC" );
					print_str( "\r\ndc N#             - Set channel as DC" );
					print_str( "\r\nsc N# a b         - Set parameters a;b\r\n" );
					print_str( "\r\nsx N# x1 y1 x2 y2 - Set parameters x1;y1, x2;y2" );
					print_str( "\r\n\r\n         where N# - channel number\r\n" );


//					print_str( "\r\n    |     sc N# a b" );
//					print_str( "\r\n    |     sx N# x1 y1 x2 y2" );
//					print_str( "\r\n    |     ac N#" );
//					print_str( "\r\n    |     sc N#\r\n" );
					print_str( ( char* ) cli_data );
				}	// if( strcmp( s, "?" ) == 0 )
				// -----------------------------------------------------------

				// -----------------------------------------------------------
				else
				if( strcmp( s, "SH" ) == 0 )
				{

//print_str( "\r\n" );
//print_str( "\r\n?  - This page" );
//print_str( "\r\nq  - Exit from ADC Config" );
//print_str( "\r\nsh - Show parameters" );
//print_str( "\r\nsp - Set parameters\r\n" );
//print_str( ( char* ) cli_data );

					//print_str( "\r\nThe coefficients of the equation y = a * x + b\r\n" );
					print_str( s1 );
					print_str( "\r\nch port GPIO Type" );
					print_str( "\r\n-- ---- ---------\r\n" );


	for( i = 0; i < Nn_Ch; i++ )
	{
		if( GPIO_X[i].dev_type == 6 )
		{
			if( GPIO_X[i].gpio_pin_nn && GPIO_X[i].gpio_x )
			{
			sprintf( s, "%2u ", ( i + 1 ) ); print_str(s);
			j = 0;
			k = 0;
			if( GPIO_X[i].gpio_x == GPIOA )
			{
				print_str( "PA" );
				j = 1;
			}
			else
			if( GPIO_X[i].gpio_x == GPIOB )
			{
				print_str( "PB" );
				j = 1;
			}
			else
			if( GPIO_X[i].gpio_x == GPIOC )
			{
				print_str( "PC" );
				j = 1;
			}
			else
			{
				print_str( "----" );
			}


x1 = 123.1123;
y1 = 1234567890123.12;

j = sizeof( double );
sprintf( s, "%-2u %-38.18f", GPIO_X[i].gpio_pin_nn, x1 ); print_str( s );
sprintf( s, " %-18.10f - %d", y1, j ); print_str( s );

		print_str( "\r\n" );
				}
		}
	}	// for( i = 0; i < Nn_Ch; i++ )


					print_str( "\r\n" );
					print_str( ( char* ) cli_data );
				}	// if( strcmp( s, "SH" ) == 0 )
				// -----------------------------------------------------------

				else
				if( strcmp( s, "SC" ) == 0 )
				{
					print_str( "Set " );
					print_str( s1 );

print_str( "mode a; b         - enter '1'\r\nmode x1;y1, x2;y2 - enter '2'\r\nmode=" );
while( !ret_button ) {}
n1 = strlen( ( char* ) usart_rx_data );
if( n1 )	// Length > 0
{
s[0] = 0;
//parce_cmd( ( char* ) &s, ( int* ) &space_index, m );
//parce_cmd( ( char* ) &s, ( int* ) &space_index, m );
print_str("\r\n");
print_str( s );

}
ret_button = FALSE;


					//print_str( "\r\n" );
					print_str( ( char* ) cli_data );
				}	// if( strcmp( s, "SC" ) == 0 )

				// -----------------------------------------------------------
				else
				{
					print_str( "\r\nCommand error" );
					print_str( "\r\n? - help\r\n" );
					print_str( ( char* ) cli_data );
				}
				// -----------------------------------------------------------
			}	// if( n )	// Length > 0
			else
			{
				print_str( ( char* ) cli_data );
			}
		}	// if( ret_button )	// Press Enter
	}	// while( !quit )
	strcpy( ( char* ) cli_data, "\r\nConfig> " );
	clr_input();
	return 0;
}
// ===========================================================================


// ===========================================================================
void Cli( void )
// ===========================================================================
{
	char			s[RX_LEN];
	int				i, j, k, n, m;
	//int				space_index[6];
	uint16_t		n1, n2, n3, n4;
	volatile bool	cmd, change_prm;

	cli_mode	= TRUE;
	change_prm	= FALSE;
	print_str( VER );
	strcpy( ( char* ) cli_data, "\r\nConfig> " );	// Set prompt
	clr_input();
	print_str( "\r\n? - help\r\n" );
	print_str( ( char* ) cli_data );
	//m = sizeof( space_index ) / sizeof( int );

	while( cli_mode )
	{
		if( ret_button )	// Press Enter
		{
			ret_button	= FALSE;
			cmd			= FALSE;

			n = strlen( ( char* ) usart_rx_data );
			if( n )		// Length > 0
			{
				s[0] = 0;
				//parce_cmd( ( char* ) &s, ( int* ) &space_index, m );
				parce_str( ( char* ) &s, 1 );


				// -----------------------------------------------------------
				// Complete CLI mode
				// -----------------------------------------------------------
				if( strcmp( s, "Q" ) == 0 )
				{
//					strcpy( ( char* ) cli_data, CLI );	// Return prompt
//					print_str( ( char* ) cli_data );
					cli_data[0]		= 0;
					cli_mode		= FALSE;			// Not CLI mode
					print_str( "\r\n\r\n" );
					clr_input();
					if( change_prm )
					{
						NVIC_SystemReset();
					}
					return;
				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Help
				// -----------------------------------------------------------
				else
				if( strcmp( s, "?" ) == 0 )
				{
					print_str( "\r\n" );
					print_str( "\r\n?       - This page" );
					print_str( "\r\nq       - Exit from Config" );
					print_str( "\r\nsh      - Show parameters" );
					print_str( "\r\n" );
					#ifdef CAN_2515
						print_str( "\r\ncn <Nn> - set Nn on CAN bus (1..100)" );
						print_str( "\r\ncs <Nn> - set CAN speed" );
						print_str( "\r\n          Nn = 0; Speed 500000" );
						print_str( "\r\n          Nn = 1; Speed 250000" );
						print_str( "\r\n          Nn = 2; Speed 125000" );
						print_str( "\r\n          Nn = 3; Speed 100000" );
						print_str( "\r\n          Nn = 4; Speed 50000" );
						print_str( "\r\n          Nn = 5; Speed 20000" );
						print_str( "\r\n          Nn = 6; Speed 10000" );
						print_str( "\r\n" );
					#endif
					sprintf( s, "\r\nln <Number>                             - set number of channels (1-%d)", MAX_NN_CH ); print_str( s );
					print_str( "\r\nlc <channel> <port> <GPIOx> [GPIO Type] - set channel" );
					print_str( "\r\nlt <channel> <GPIO Type>                - set channel type" );
					print_str( "\r\n" );
					print_str( "\r\nwhere" );
					print_str( "\r\n       channel   : Number of channel (1-16)" );
					print_str( "\r\n       port      : A,B,(0-delete)" );
					print_str( "\r\n       GPIOx     : x - pin of ports (0-15)" );
					print_str( "\r\n       GPIO Type : 0 - Not connected" );
					print_str( "\r\n                   1 - DS18B20" );
					print_str( "\r\n                   2 - iButton" );
					print_str( "\r\n                   3 - bidirectional GPIO pulldown" );
					print_str( "\r\n                   4 - bidirectional GPIO pullup" );
					print_str( "\r\n                   5 - GPIO_Mode Input Floating" );
					print_str( "\r\n                   6 - ADC" );
					print_str( "\r\n" );
					print_str( "\r\nsa      - Setup ADC\r\n" );
					//print_str( "\r\nsd <Nn> - Show Data, Nn=0/1" );
					print_str( "\r\ntm <Nn> - Set timeout for iButton, Nn=0..10" );
					//print_str( "\r\nwrsn <Nn>  - Write S/N" );
					//print_str( "\r\nwrdt <Nn>  - Write Device Type" );
					print_str( "\r\n" );
					cmd = TRUE;
					clr_input();
				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Show parameters
				// -----------------------------------------------------------
				else
				if( strcmp( s, "SH" ) == 0 )
				{
					Show_Params();
					if( !Nn_Ch )
					{
						print_str( "\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "SH" ) == 0 )
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// CAN number
				// -----------------------------------------------------------
				else
				if( strcmp( s, "CN" ) == 0 )
				{
					//change_prm	= FALSE;
					// Get first param
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );
					parce_str( ( char*) &s, 2 );
					if( s[0] )
					{
						i = atoi( s );
						if( ( i > 0 ) && ( i < 101 ) )
						{
							Noc = i;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError CAN number. Enable 1..100\r\n" );
						}
					}	// if( s[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "CN" ) == 0 )
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// CAN speed
				// -----------------------------------------------------------
				else
				if( strcmp( s, "CS" ) == 0 )
				{
					//change_prm = FALSE;
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						i = atoi( s );
						if( ( i >= 0 ) && ( i < 7 ) )
						{
							Speedc = i;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError CAN speed\r\n" );
						}
					}	// if( s[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "CS" ) == 0 )
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Input LN ( number of channels )
				// -----------------------------------------------------------
				else
				if( strcmp( s, "LN" ) == 0 )
				{
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						n = atoi( s );
						if( ( n > 0 ) && ( n < ( MAX_NN_CH + 1 ) ) )
						{
							Nn_Ch = n;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nWrong number, cancel.\r\n" );
						}
					}	// if( s[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "LN" ) == 0 )
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Input LC
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "LC" ) == 0 )
				{
					//change_prm = FALSE;

					n1 = 0;
					n2 = 0;
					n3 = 0;
					n4 = 0;

					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						n1 = abs( atoi( s ) );
					}

					//parce_prm( ( char*) &s, 2, ( int* ) &space_index, m );	// Get second param
					parce_str( ( char*) &s, 3 );	// Get second param
					if( s[0] )
					{
						if( s[1] == ' ' )
						{
							s[1] = 0;
						}
						if( strlen( s ) == 1 )
						{
							if( s[0] == '0' )
							{
								n2 = 0;
							}
							else
							if( ( s[0] == 'a' ) || ( s[0] == 'A' ) )
							{
								n2 = 1;
							}
							else
							if( ( s[0] == 'b' ) || ( s[0] == 'B' ) )
							{
								n2 = 2;
							}
							else
							if( ( s[0] == 'c' ) || ( s[0] == 'C' ) )
							{
								n2 = 3;
							}
							else
							{
								n2 = 0xFF;
							}
						}
						else
						{
							n2 = 0xFF;
						}
					}	// if( s[0] )

					//parce_prm( ( char*) &s, 3, ( int* ) &space_index, m );	// Get third param
					parce_str( ( char*) &s, 4 );	// Get third param
					if( s[0] )
					{
						n3 = abs( atoi( s ) );
					}

					//parce_prm( ( char*) &s, 4, ( int* ) &space_index, m );	// Get fourth param
					parce_str( ( char*) &s, 5 );	// Get fourth param
					if( s[0] )
					{
						n4 = abs( atoi( s ) );
					}

					n = 1;
					if( ( n1 == 0 ) ||  ( n1 > Nn_Ch ) )
					{
						print_str( "\r\nWrong Nn channel\r\n" );
						n = 0;
					}

					if( n )
					{
						if( n2 > 3 )
						{
							print_str( "\r\nWrong port name\r\n" );
							n = 0;
						}
					}

					if( n )
					{
						if( n3 > 15 )
						{
							print_str( "\r\nWrong Nn pin\r\n" );
							n = 0;
						}
					}

					if( n )
					{
						if( n2 == 1 )
						{
							if( ( n3 == 13 ) || ( n3 == 14 ) )
							{
								print_str( "\r\nWrong Nn pin\r\n" );
								n = 0;
							}
						}
					}

					if( n )
					{
						if( n2 == 2 )
						{
							if( n3 == 2 )
							{
								print_str( "\r\nWrong Nn pin\r\n" );
								n = 0;
							}
						}
					}

					if( n )
					{
						if( n4 > MAX_DEV_TYPE )
						{
							print_str( "\r\nWrong GPIO Type\r\n" );
							n = 0;
						}
					}

					if( n )
					{
						k = 1;
						if( n2 == 1 )
						{
							GPIO_Data.gpio_x = GPIOA;
						}
						else
						if( n2 == 2 )
						{
							GPIO_Data.gpio_x = GPIOB;
						}
						else
						if( n2 == 3 )
						{
							GPIO_Data.gpio_x = GPIOC;
						}
						else
						{
							GPIO_Data.gpio_x = 0;
						}
						GPIO_Data.gpio_pin_nn = n3;
						GPIO_Data.dev_type = n4;

						for( i = 0; i < Nn_Ch; i++ )
						{
							if( GPIO_Data.gpio_x )
							{
								if( ( GPIO_Data.gpio_x == GPIO_X[i].gpio_x ) && ( GPIO_Data.gpio_pin_nn == GPIO_X[i].gpio_pin_nn ) )
								{
									k = 0;
									break;
								}
							}
						}	// for( i = 0; i < Nn_Ch; i++ )

//}	Reserved_Ch[MAX_NN_CH] =






						if( k )
						{
							if( n2 == 1 )
							{
								GPIO_X[n1-1].gpio_x = GPIOA;
							}
							else
								if( n2 == 2 )
							{
								GPIO_X[n1-1].gpio_x = GPIOB;
							}
							else
							{
								GPIO_X[n1-1].gpio_x = 0;
							}
							GPIO_X[n1-1].gpio_pin_nn = n3;
							GPIO_X[n1-1].dev_type = n4;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}	// if( k )
						else
						{
							print_str( "\r\nPort/Pin already in use.\r\n" );
						}	// else - if( k )
					}	// if( n )
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "LC" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Input LT
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "LT" ) == 0 )
				{
					//change_prm = FALSE;

					n1 = 0;
					n2 = 0;

					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
							n1 = abs( atoi( s ) );
					}

					//parce_prm( ( char*) &s, 2, ( int* ) &space_index, m );	// Get second param
					parce_str( ( char*) &s, 3 );	// Get second param
					if( s[0] )
					{
						n2 = abs( atoi( s ) );
					}

					n = 1;
					if( ( n1 == 0 ) || ( n1 > Nn_Ch ) )
					{
						print_str( "\r\nWrong Nn channel\r\n" );
						n = 0;
					}

					if( n )
					{
						if( n2 > MAX_DEV_TYPE )
						{
							print_str( "\r\nWrong GPIO Type\r\n" );
							n = 0;
						}
					}

					if( n )
					{

//sprintf( s, "n2=%d\r\n", n2 ); print_str( s );

						GPIO_X[n1-1].dev_type = n2;
						Write_Flash();
						Read_Flash();
						change_prm = TRUE;
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "LT" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Write SN ( Serial Number )
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "WRSN" ) == 0 )
				{
					//change_prm = FALSE;
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						i = atoi( s );
						if( i > 0 )
						{
							Sn = i;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError number\r\n" );
						}
					}	// if( space_index[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "WRSN" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Write DT ( Device Type )
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "WRDT" ) == 0 )
				{
					//change_prm = FALSE;
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						i = atoi( s );
						if( i > 0 )
						{
							DeviceType = i;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError number\r\n" );
						}
					}	// if( space_index[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "WRDT" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Input TM ( Ibutton timeout )
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "TM" ) == 0 )
				{
					//change_prm = FALSE;
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						i = atoi( s );
						if( ( i >= 0 ) && ( i < 11 ) )
						{
							iButton_Timeout = i * 8;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError TM number\r\n" );
						}
					}	// if( s[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "TM" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// Input SD ( Show Data )
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "SD" ) == 0 )
				{
					//change_prm = FALSE;
					//parce_prm( ( char*) &s, 1, ( int* ) &space_index, m );	// Get first param
					parce_str( ( char*) &s, 2 );	// Get first param
					if( s[0] )
					{
						i = atoi( s );
						if( ( i == 0 ) || ( i == 1 ) )
						{
							Show_Data = i;
							Write_Flash();
							Read_Flash();
							change_prm = TRUE;
						}
						else
						{
							print_str( "\r\nError SD value\r\n" );
						}
					}	// if( s[0] )
					else
					{
						print_str( "\r\nCommand error\r\n" );
					}
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "SD" ) == 0 )
//				}
				// -----------------------------------------------------------


				// -----------------------------------------------------------
				// SA
				// -----------------------------------------------------------
//				if( !cmd )
//				{
				else
				if( strcmp( s, "SA" ) == 0 )	// ADC Menu
				{
					//change_prm = FALSE;
					ADC_Menu();
					cmd = TRUE;
					clr_input();
				}	// if( strcmp( s, "SA" ) == 0 )
//				}
				// -----------------------------------------------------------

				// -----------------------------------------------------------
				if( !cmd )
				{
					print_str( "\r\nUnknown command" );
					print_str( "\r\n? - for help\r\n" );
					print_str( ( char* ) cli_data );
				}
				else
				{
					print_str( ( char* ) cli_data );
				}
				// -----------------------------------------------------------
			}	// if( n ) -- Length > 0
			else
			{
				print_str( ( char* ) cli_data );
			}
		}	// if( ret_button )
	}	// while( cli_mode )
	clr_input();
}
// ===========================================================================


// ===========================================================================
void Show_Reserved()
// ===========================================================================
{
	int		i;
	char	s[RX_LEN];
	print_str( "\n\r" );
	for( i = 0; i < RESERVED_CH_NN; i++ )
	{
		if( Reserved_Ch[i].gpio_x )
		{
			switch( (int) Reserved_Ch[i].gpio_x )
			{
				case (int) GPIOA:
					sprintf( s, "RC A" ); print_str( s );
					break;
				case (int) GPIOB:
					sprintf( s, "RC B" ); print_str( s );
					break;
				case (int) GPIOC:
					sprintf( s, "RC C" ); print_str( s );
					break;
				default:
					break;
			}
			sprintf( s, "%d\n\r", Reserved_Ch[i].gpio_pin_nn ); print_str( s );
		}
	}
}
// ===========================================================================


// ===========================================================================
void Cli_State( void )
// ===========================================================================
{
	int			i, l, n, m, n_prm;
	char		s[RX_LEN], str[RX_LEN];
	uint8_t		*b;

	if( ret_button )	// Return button is pressed
	{
		m = 1;
		n_prm = parce_str( &str[0], 1 );
		if( !strlen( str ) )
		{
			n_prm = 0;
		}

		if( !n_prm )
		{
			print_str( "\r" );
			clr_input();
		}

		l = strlen( ( char* ) str );
		if( l )
		{
			for( i = 0; i < l; i++ )
			{
				if( ( str[i] < '0' ) || ( str[i] > '9' ) )
				{
					m = 0;
				}
			}

			if( strcmp( ( char* ) str, "CFG" ) == 0 )		// Goto to Config mode
			{
				cli_mode = TRUE;	// CLI mode
			}
			else
			if( strcmp( ( char* ) str, "VER" ) == 0 )		// Print version
			{
				print_str( VER );
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "SH" ) == 0 )		// Set Show mode
			{
				Show_Data = 1;
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "SHPD" ) == 0 )		// Set Show Program Data. Addition for SH
			{
#ifdef PD_NN


				//Show_Data = 1;
				//print_str( "\r\n" );
#endif
			}
			else
			if( strcmp( ( char* ) str, "SHP" ) == 0 )		// Show Parameters
			{
				Show_Params();
			}
			else
			if( strcmp( ( char* ) str, "SHR" ) == 0 )		// Show Reserved PINs
			{
				Show_Reserved();
			}
			else
			if( strcmp( ( char* ) str, "SHPDD" ) == 0 )	// Show Description of Program Data
			{
				print_str( "\r\n" );
				#ifdef PD_NN
					for( i = 0; i < PD_NN; i++ )
					{
						sprintf( s, "PDD %s %c %s\r\n", PD[i].name, PD[i].data_type, PD[i].comment ); print_str( s );
					}
				#endif
				#ifdef LCD_1602
					for( i = 0; i < 2; i++ )
					{
						sprintf( s, "LCD %s\r\n", LCD1[i].name ); print_str( s );
					}
				//Show_Data = 1;
				//print_str( "\r\n" );
				#endif
			}
			else
			if( strcmp( ( char* ) str, "SHDEF" ) == 0 )	// Show #DEFINE
			{
				print_str( "\r\n" );
				sprintf( s, "DEF F_APB1 %d\r\n", F_APB1 ); print_str( s );

				#ifdef DEV_TYPE
					sprintf( s, "DEF DEV_TYPE %d\r\n", DEV_TYPE ); print_str( s );
				#endif

				#ifdef OSC_INT
					sprintf( s, "DEF OSC_INT\r\n" ); print_str( s );
				#else
					sprintf( s, "DEF OSC_EXT\r\n" ); print_str( s );
				#endif

				#ifdef WD_TIMER
					sprintf( s, "DEF WD_TIMER\r\n" ); print_str( s );
				#endif

				#ifdef USE_UART1
					sprintf( s, "DEF USE_UART1\r\n" ); print_str( s );
				#endif

				#ifdef LED_BLINK
					sprintf( s, "DEF LED_BLINK\r\n" ); print_str( s );
				#endif

				#ifdef LCD_1602
					sprintf( s, "DEF LCD_1602\r\n" ); print_str( s );
				#endif

				#ifdef PCF8574
					sprintf( s, "DEF PCF8574\r\n" ); print_str( s );
				#endif

				#ifdef PCF8574A
					sprintf( s, "DEF PCF8574A\r\n" ); print_str( s );
				#endif

				#ifdef USB_VCP
					sprintf( s, "DEF USB_VCP\r\n" ); print_str( s );
				#endif

				#ifdef VCP_CONS
					sprintf( s, "DEF VCP_CONS\r\n" ); print_str( s );
				#endif

				#ifdef CAN_2515
					sprintf( s, "DEF CAN_2515\r\n" ); print_str( s );
				#endif

				#ifdef UART1_SPEED
					sprintf( s, "DEF UART1_SPEED %d\r\n", UART1_SPEED ); print_str( s );
				#endif
			}
			else
			if( strcmp( ( char* ) str, "NSH" ) == 0 )		// Set NoShow mode
			{
				Show_Data = 0;
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "ECHO" ) == 0 )		// Set Echo mode
			{
				Echo = TRUE;
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "NECHO" ) == 0 )		// Set NoEcho mode
			{
				Echo = FALSE;
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "SN" ) == 0 )		// Show S/N
			{
				b = (uint8_t*) &Sn8;
				print_str( "\r\nSN " );
				for( i = 0; i < 8; i++ )
				{
					sprintf( s, "%02X", b[i] ); print_str( s );
				}
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "ST" ) == 0 )		// Show SYS_Tick (CntTime)
			{
				sprintf( s, "\r\nSYS_TICK %u\r\n", CntTime ); print_str( s );
			}
			else
			if( strcmp( ( char* ) str, "SD" ) == 0 )		// Show Program Data On
			{
				Show_PData = 1;
				print_str( "\r\n" );
			}
			else
			if( strcmp( ( char* ) str, "NSD" ) == 0 )		// Show Program Data Off
			{
				Show_PData = 0;
				print_str( "\r\n" );
			}
			else
			if( m )
			{
				if( !cli_mode )
				{
					{
						n = atoi( ( char* ) str );
						if( ( n ) && ( n <= MAX_NN_CH ) )
						{
							n--;
							if( ( GPIO_X[n].gpio_x ) && ( n < Nn_Ch ) )
							{
								if( ( GPIO_X[n].dev_type == 3 ) || ( GPIO_X[n].dev_type == 4 ) )
								{
									l = GPIO_ReadInputDataBit( GPIO_X[n].gpio_x, GPIO_X[n].gpio_pin_x );
									if( l )
									{
										GPIO_ResetBits( GPIO_X[n].gpio_x, GPIO_X[n].gpio_pin_x );
									}
									else
									{
										GPIO_SetBits( GPIO_X[n].gpio_x, GPIO_X[n].gpio_pin_x );
									}
									if( !Show_Data )
									{
										print_str( "\r\n" );
									}
								}
								else
								{
									print_str( "\r\nERR: Channel may be GPIO only.\r\n" );
								}
							}
							else
							{
								print_str( "\r\nERR: Channel not defined.\r\n" );
							}
						}	// if( ( n ) && ( n <= MAX_NN_CH ) )
						else
						{
							print_str( "\r\nERR: Wrong Nn of channel.\r\n" );
						}
					}
				}	// if( !cli_mode )
			}	// if( m )
			else
			{
				print_str( "\r\nUnknown command\r\n\r\n" );
				print_str( "  <ver> - Version of module\r\n" );
				print_str( "  <cfg> - Config\r\n" );
				print_str( "  <nn>  - reverse state GPIO; nn is number of channel\r\n" );
				print_str( "  <sh>  - show on witout saving\r\n" );

				if( cli_data[0] )
				{
					print_str( ( char* ) cli_data );	// Identifier
				}
			}	// else - if( m )
			clr_input();
		}
		else
		{
			print_str( ( char* ) cli_data );	// Identifier
			clr_input();
		}
	}	// if( ret_button ) -- Return button is pressed
}
// ===========================================================================
