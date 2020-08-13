#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
#include "mx_misc.h"

#include <stdio.h>

#define VCOMPORT_IN_FRAME_INTERVAL	5	// Interval between sending IN packets in frame number (1 frame = 1ms)

uint8_t					USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern uint8_t			USB_Tx_State;
static volatile bool	USB_Rx = false;

void delay_ms( uint32_t delay );


// ===========================================================================
void send_usb( char *data, int len )
// ===========================================================================
{
	#ifdef USB_VCP
		volatile uint32_t	i;

		UserToPMABufferCopy( (uint8_t*) &data[0], ENDP1_TXADDR, len );
		SetEPTxCount( ENDP1, len );
		SetEPTxValid( ENDP1 ); 
		delay_ms( 1 );
	#endif
}
// ===========================================================================


// ===========================================================================
void EP1_IN_Callback ( void )
// ===========================================================================
{
	Handle_USBAsynchXfer();
}
// ===========================================================================


// ===========================================================================
void EP3_OUT_Callback( void )
// ===========================================================================
{
//	#ifdef USB_VCP		// USB as console
	uint16_t	USB_Rx_Cnt;
	uint16_t	j = 0;
//	#endif

	#ifdef VCP_CONS		// USB as console
		char	s[2];
		int		i;
	#endif

	USB_Rx_Cnt = j;
	while( USB_Rx ) {}
	USB_Rx = true;
	USB_Rx_Cnt = USB_SIL_Read( EP3_OUT, USB_Rx_Buffer );	// Get the received data buffer and update the counter
	j = USB_Rx_Cnt;

	#ifdef VCP_CONS		// USB as console
		s[1] = 0;
		if( USB_Rx_Cnt < RX_LEN )
		{
			for( i = 0; i < USB_Rx_Cnt; i++ )
			{
				s[0] = USB_Rx_Buffer[i];
				if( s[0] == 13 )
				{
					s[0] = 0;
					ret_button = TRUE;						// Set flag "press Enter"
					rx_idx = 0;
				}
				else
				{
					if( rx_idx < ( RX_LEN - 1 ) )
					{
						usart_rx_data[rx_idx++] = s[0];		// Char to read buffer
						usart_rx_data[rx_idx] = 0;			// End of string
						if( Echo )
						{
							print_str( s );					// Echo
						}
					}
				}
			}
		}
	#endif

	// Enable the receive of data on EP3
	SetEPRxValid( ENDP3 );
	USB_Rx = false;
}
// ===========================================================================


// ===========================================================================
void SOF_Callback(void)
// ===========================================================================
{
	static uint32_t		FrameCount = 0;

	if( bDeviceState == CONFIGURED )
	{
		if( FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL )
		{
			FrameCount = 0;				// Reset the frame counter
			Handle_USBAsynchXfer();		// Check the data to be sent through IN pipe
		}
	}
}
// ===========================================================================
