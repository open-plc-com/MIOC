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


// ===========================================================================
void Cli( void )
// ===========================================================================
{
	int			n_prm;
	char		str[RX_LEN];

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
