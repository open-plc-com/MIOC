/*
	Name:			mx_can_mcp2515.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


#include "mx_can_mcp2515.h"

/* ===========================================================================
   Init MCP2515
   =========================================================================== */
void init_can( void )
{
	EXTI_InitTypeDef	EXTI_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;

	if( !CAN_Run )
	{
		// Init_EXTI
		GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource5 );
		EXTI_InitStructure.EXTI_Line	= EXTI_Line5;
		EXTI_InitStructure.EXTI_Mode	= EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Trigger	= EXTI_Trigger_Falling;
//		EXTI_InitStructure.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;
		EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
		EXTI_Init( &EXTI_InitStructure );

		// Init_NVIC
		NVIC_InitStructure.NVIC_IRQChannel						= EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0x08;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 0x00;
		NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
		NVIC_Init( &NVIC_InitStructure );

		NVIC_EnableIRQ( EXTI9_5_IRQn );

		CAN_Run = TRUE;
	}

	// Set config to CANINTE reg - interrupt flags
	spi2_tx_data[0]		= SPI_WRITE;
	spi2_tx_data[1]		= CANINTE;
	//spi2_tx_data[2]	= 0xA5;
	spi2_tx_data[2]		= 0x41;
	send_spi2( 3 );

	// Set config to RXB0CTRL reg
	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = RXB0CTRL;
	spi2_tx_data[2] = 0x60;		// Turn mask/filters off; receive any message
	send_spi2( 3 );

	// Set config to RXB1CTRL
	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = RXB1CTRL;
	spi2_tx_data[2] = 0x60;		// Turn mask/filters off; receive any message
	send_spi2( 3 );

	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = BFPCTRL;
	spi2_tx_data[2] = 0x30;
	send_spi2( 3 );

	// Set config to RXB0DLC reg
	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = RXB0SIDL;
	spi2_tx_data[2] = 0x08;		// set data length code
	send_spi2( 3 );

	switch( Speedc )
	{
		case	0:	// Speed 500000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x80;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0x91;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x01;
					send_spi2( 3 );

					break;

		case	1:	// Speed 250000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x80;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xB5;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x01;
					send_spi2( 3 );

					break;

		case	2:	// Speed 125000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x81;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xb5;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x01;
					send_spi2( 3 );

					break;

		case	3:	// Speed 100000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x81;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xbf;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x02;
					send_spi2( 3 );

					break;

		case	4:	// Speed 50000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x84;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xb5;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x01;
					send_spi2( 3 );

					break;

		case	5:	// Speed 20000
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x89;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xbf;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x02;
					send_spi2( 3 );

					break;

		case	6:	// Speed 10000
		default:
					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF1;
					spi2_tx_data[2] = 0x98;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF2;
					spi2_tx_data[2] = 0xB5;
					send_spi2( 3 );

					spi2_tx_data[0] = SPI_WRITE;
					spi2_tx_data[1] = CNF3;
					spi2_tx_data[2] = 0x01;
					send_spi2( 3 );
	}

	// All done. Set to normal mode
	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = CANCTRL;
	spi2_tx_data[2] = 0x08;		// One-Shot mode bit
	send_spi2( 3 );
}
// ===========================================================================


// ===========================================================================
void delay_us_mcp2515( uint32_t delay )		// Delay in microseconds
// ===========================================================================
{
	volatile uint32_t i;
	i = ( F_APB1 / 10000000 ) * delay;
	for( ; i != 0; i-- ) {}
}
// ===========================================================================


/* ===========================================================================
   Soft reset MCP2515
   =========================================================================== */
void reset_can( void )
{
	spi2_tx_data[0] = SPI_RESET;
	send_spi2( 1 );
}
// ===========================================================================


/* ===========================================================================
   Get data from MCP2515
   CAN identifier only extended mode!

   Result:
    If data present, then return 1; if not, return 0
    In can_id[4] placed header of packet
        0 and 1 - Standart identifier
        2 and 3 - Extended identifier
    In can_data[0..8] - read data

   Return:
    0 - Successful execute
    1 - Unknown operation
    2 - Address not coincide
   =========================================================================== */
int receive_can( void )
{
	int			ret, cmd1, cmd2;
	uint32_t	i, j;
	uint16_t	id1, id2;
	uint8_t		ddi;
	uint8_t		*val;
	uint8_t		it1, it2;

	ret			= 0;

	// Read status register of interrupt
	spi2_tx_data[0]	= SPI_READ;
	spi2_tx_data[1]	= CANINTF;
	spi2_tx_data[2]	= 0x00;
	send_spi2( 3 );
	ddi				= spi2_rx_data[2];	// Delivered register to ddi

	// Interrupt on filling buffer 0:
	if( ddi & 1 )
	{
        CANDownTime = 0;

		// Get identifier
		for( i = 2; i < SPI_LEN; i++ )
		{
			spi2_tx_data[i] = 0;
		}
		spi2_tx_data[0] = SPI_READ;
		spi2_tx_data[1] = RXB0SIDH;
		send_spi2( 6 );

		// Normal identifier
		can_id[0] = spi2_rx_data[2];
		can_id[1] = spi2_rx_data[3];

		// Extend identifier
		can_id[2] = spi2_rx_data[4];
		can_id[3] = spi2_rx_data[5];

		// Identifier to normal view
		id1		= ( can_id[0] << 5 );
		id2		= ( can_id[1] >> 3 );
		id1	   |= ( id2 & 0xFC );
		id1	   |= ( can_id[1] & 0x03 );

		cmd1 = can_id[2];
		cmd2 = can_id[3];

		if( id1 == 0 )	// Broadcast
		{
			// Get 8 byte data
			for( i = 1; i < SPI_LEN; i++ )
			{
				spi2_tx_data[i] = 0;
			}
			spi2_tx_data[0] = SPI_READ_RX | 0x02;		// Read Rx bufer0
			send_spi2( 9 );

			for( i = 0; i < 8; i++ )
			{
				can_data[i] = spi2_rx_data[i + 1];
			}
		}	// if( id1 == 0 ) - Broadcast

		else
		if( id1 == Noc )								// Controller address coincide
		{
			// Get 8 byte data
			for( i = 1; i < SPI_LEN; i++ )
			{
				spi2_tx_data[i] = 0;
			}
			spi2_tx_data[0] = SPI_READ_RX | 0x02;		// Read Rx bufer0
			send_spi2( 9 );

			for( i = 0; i < 8; i++ )
			{
				can_data[i] = spi2_rx_data[i + 1];
			}

			CanErr = FALSE;

			switch( cmd1 )
			{
				case 1:		// Write parameters ( can set only GPIO )
							if( GPIO_X[cmd2-1].gpio_x && GPIO_X[cmd2-1].dev_type )
							{
								if( ( GPIO_X[cmd2-1].dev_type == 3 ) || ( GPIO_X[cmd2-1].dev_type == 4 ) )
								{
									if( can_data[0] )
									{
										GPIO_SetBits( GPIO_X[cmd2-1].gpio_x, GPIO_X[cmd2-1].gpio_pin_x );
									}
									else
									{
										GPIO_ResetBits( GPIO_X[cmd2-1].gpio_x, GPIO_X[cmd2-1].gpio_pin_x );
									}
								}
								else
								{
									CanErr = TRUE;
									ret = 1;
								}
							}
							else
							{
								CanErr = TRUE;
								ret = 1;
							}
							break;

				case 2:		// Read parameters

							cmd2 &= 0x7F;

							if( cmd2 > Nn_Ch )
							{
								CanErr = TRUE;
								ret = 1;
							}
							else
							{
								if( cmd2 == 0 )		// Get devices type
								{
									//val = ( uint8_t* ) &Dev_Type;
									j = 0;
									for( i = 0; i < 8; i++ )
 									{
										it1 = 0;
										it2 = 0;
										if( j < MAX_NN_CH )
										{
											it1 = GPIO_X[j++].dev_type;
											it1 = it1 << 4;
										}
										if( j < MAX_NN_CH )
										{
											it2 = GPIO_X[j++].dev_type;
										}
										can_data[i] = it1 | it2;
									}
								}
								else	// Get port value
								if( GPIO_X[cmd2-1].gpio_x && GPIO_X[cmd2-1].dev_type )
								{
									val = ( uint8_t* ) &GPIO_X[cmd2-1].raw_data;
									for( i = 0; i < 8; i++ )
									{
										can_data[i] = val[i];
									}
								}
								else
								{
									CanErr = TRUE;
									ret = 1;
									for( i = 0; i < 8; i++ )
									{
										//can_data[i] = 0xFF;
										can_data[i] = 0;
									}
								}
							}
							break;

				case 3:		// System Reset

							NVIC_SystemReset();
							break;

				default:	// unknown command

							CanErr = TRUE;
							ret = 1;
							break;
			}	// switch( cmd )
		}	// if( id1 == NOC ) - Controller address coincide

		else
		{
			ret = 2;	// unknown address
		}
	}	// if( ddi & 1 ) --- Interrupt on filling buffer 0:
	return	ret;
}
// ===========================================================================


/* ===========================================================================
   Send data to MCP2515
   Return values:
    0 - successfully completed
    1 - could not send data

   In return package to the extended identifier is added eighth bit.
   For example, we received identifier XXX00200, be returned XXX00280
   If the command is not correct or is unsuccessful, we return: XXX8280
   =========================================================================== */
int send_can( void )
{
	int			i, ret;
	uint16_t	id1, id2;
	uint8_t		*ui8, ui8t;
	uint32_t	*ui32;
	uint32_t	cn_t;
	bool		to_send;

//char s[128];

	ret		= 0;
	to_send	= FALSE;

	// Identifier to normal view
	id1		= ( can_id[0] << 5 );
	id2		= ( can_id[1] >> 3 );
	id1	   |= ( id2 & 0xFC );
	id1	   |= ( can_id[1] & 0x03 );
	id2 = ( can_id[2] << 8 ) | can_id[3];	// Both commands

	// Setup data
	for( i = 6; i < SPI_LEN; i++ )
	{
		spi2_tx_data[i] = 0;
	}
	spi2_tx_data[0] = SPI_WRITE;
	spi2_tx_data[1] = TXB0SIDH;

	if( id1 && id2 )	// to target address
	{
		spi2_tx_data[2] = can_id[0];
		spi2_tx_data[3] = can_id[1];
		if( CanErr )
		{
			spi2_tx_data[4] = can_id[2] | 0x80;
		}
		else
		{
			spi2_tx_data[4] = can_id[2];
		}
		spi2_tx_data[5] = can_id[3] | 0x80;
		spi2_tx_data[6] = 0x08;		// Data Length

		for( i = 0; i < 8; i++ )
		{
			spi2_tx_data[i + 7] = can_data[i];
		}
		to_send = TRUE;
	}
	else	// to broadcast ?

	// -----------------------------------------------------------------------
	if( id1 == 0 )	// broadcast
	// -----------------------------------------------------------------------
	{
		ui8 = ( uint8_t* ) &id2;
		if( ui8[1] == 1 )	// write data
		{
			if( ui8[0] == 1 )	// not answer for broadcast SN
			{
				ui32 = ( uint32_t* ) &can_data[0];
				if( *ui32 == Sn )
				{
					spi2_tx_data[2]		= can_id[0];
					spi2_tx_data[3]		= can_id[1];
					spi2_tx_data[4]		= can_id[2];
					spi2_tx_data[5]		= can_id[3] | 0x80;
					spi2_tx_data[6]		= 0x08;		// Data Length

					spi2_tx_data[7]		= can_data[0];
					spi2_tx_data[8]		= can_data[1];
					spi2_tx_data[9]		= can_data[2];
					spi2_tx_data[10]	= can_data[3];

					ui8					= ( uint8_t* ) &Noc;
					spi2_tx_data[11]	= ui8[0];
					spi2_tx_data[12]	= ui8[1];

					to_send				= TRUE;
					NoAnswer			= TRUE;
				}	// if( *ui32 == Sn )

			}	// if( ui8[0] == 1 ) - not respond to the broadcast request of serial number.
			else

			if( ui8[0] == 2 )	// setup CAN number
			{
				ui32 = ( uint32_t* ) &can_data[0];
				if( *ui32 == Sn )
				{
					spi2_tx_data[2]		= can_id[0];
					spi2_tx_data[3]		= can_id[1];
					spi2_tx_data[4]		= can_id[2];
					spi2_tx_data[5]		= can_id[3] | 0x80;
					spi2_tx_data[6]		= 0x08;		// Data Length

					spi2_tx_data[7]		= can_data[0];
					spi2_tx_data[8]		= can_data[1];
					spi2_tx_data[9]		= can_data[2];
					spi2_tx_data[10]	= can_data[3];

					ui8					= ( uint8_t* ) &Noc;
					spi2_tx_data[11]	= ui8[0];
					spi2_tx_data[12]	= ui8[1];

					Noc					= can_data[4];
					Write_Flash();
					Read_Flash();
					to_send				= TRUE;
				}	// if( *ui32 == Sn )
			}	// if( ui8[0] == 2 ) -- setup CAN number
			else

			if( ui8[0] == 3 )	// Reset NoAnswer
			{
				NoAnswer = FALSE;
			}
		}
		else

		if( ( ui8[1] == 2 ) && ( NoAnswer == FALSE ) )	// data read
		{
			if( ui8[0] == 0 )	// Post a serial number; the unit will be return to the first 4 bytes Sn
								// in the following 4 bytes, is code (identifier) of the device
			{
				ui8				= ( uint8_t* ) &Sn;
				spi2_tx_data[2]	= ui8[2];
				spi2_tx_data[3]	= can_id[1];
				spi2_tx_data[4]	= ui8[1];
				ui8t			= ui8[0] & 0x1F;
				spi2_tx_data[5]	= ui8t;

				spi2_tx_data[6]	= 0x08;		// Data Length

				ui8				= ( uint8_t* ) &Sn;
				for( i = 0; i < 4; i++ )	// Set Sn
				{
					spi2_tx_data[i + 7] = ui8[i];
				}

				ui8 = ( uint8_t* ) &DeviceType;
				for( i = 0; i < 4; i++ )	// Set device type
				{
					spi2_tx_data[i + 11] = ui8[i];
				}
				to_send = TRUE;
			}	// if( ui8[0] == 0 )
			else

			if( ui8[0] == 1 )	// Get CAN number
			{
				ui32 = ( uint32_t* ) &can_data[0];
				if( *ui32 == Sn )
				{
					spi2_tx_data[2]		= can_id[0];
					spi2_tx_data[3]		= can_id[1];
					spi2_tx_data[4]		= can_id[2];
					spi2_tx_data[5]		= can_id[3] | 0x80;
					spi2_tx_data[6]		= 0x08;		// Data Length

					spi2_tx_data[7]		= can_data[0];
					spi2_tx_data[8]		= can_data[1];
					spi2_tx_data[9]		= can_data[2];
					spi2_tx_data[10]	= can_data[3];

					ui8					= ( uint8_t* ) &Noc;
					spi2_tx_data[11]	= ui8[0];
					spi2_tx_data[12]	= ui8[1];
					to_send				= TRUE;
				}	// if( *ui32 == Sn )
			}	// if( ui8[0] == 1 ) -- Get CAN number
		}	// if( ui8[1] == 2 )
	}	// else - to broadcast

	if( to_send )
	{
		send_spi2( 15 );

		// Send data
		spi2_tx_data[0] = SPI_RTS | 0x01;
		send_spi2( 1 );

		cn_t = CntTime;
		i = 0;
		while( ( abs( CntTime - cn_t ) < 2 ) && ( i == 0 ) )
		{
			// Read interrupt status
			delay_us_mcp2515( 10 );
			spi2_tx_data[0] = SPI_READ;
			spi2_tx_data[1] = CANINTF;
			spi2_tx_data[2] = 0x00;
			send_spi2( 3 );

			// If bufer empty, cleat interrupt flag
			if( spi2_rx_data[2] & 4 )
			{
				i = 1;
			}
			else

			if( spi2_rx_data[2] == 1 )	// Not able to send a packet, Reset
			{
				reset_can();
				delay_us_mcp2515( 100 );
				Init_Can();
				i = 1;
			}	// if( spi2_rx_data[2] == 1 ) -- Not able to send a packet, Reset
		}

		if( abs( CntTime - cn_t ) > 1 )
			ret = 1;
	}	// if( to_send )
	return ret;
}
// ===========================================================================


/* ===========================================================================
   Handler interrupt of CAN
   data is receive
   =========================================================================== */
void EXTI9_5_IRQHandler( void )
{
	int	ret_code;

	ret_code = receive_can();

	// Reset bits of interrupt
	spi2_tx_data[0] = SPI_BIT_MODIFY;
	spi2_tx_data[1] = CANINTF;
	spi2_tx_data[2] = 0xFF;
	spi2_tx_data[3] = 0x00;
	send_spi2( 4 );

	if( ( ret_code == 0 ) || ( ret_code == 1 ) )
	{
		ret_code = send_can();

		if( ret_code == 1 )				// Not able to send a packet
		{
			reset_can();				// Reset CAN
			delay_us_mcp2515( 100 );	// wait 100 microsecond
			Init_Can();					// Init CAN
		}	// if( ret_code == 1 )
	}	// if( ( ret_code == 0 ) || ( ret_code == 1 ) )

	// Reset bits of interrupt
	spi2_tx_data[0] = SPI_BIT_MODIFY;
	spi2_tx_data[1] = CANINTF;
	spi2_tx_data[2] = 0xFF;
	spi2_tx_data[3] = 0x00;
	send_spi2( 4 );

	if( EXTI_GetITStatus( EXTI_Line5 ) )
	{
		EXTI_ClearITPendingBit( EXTI_Line5 );
	}
}
// ===========================================================================
