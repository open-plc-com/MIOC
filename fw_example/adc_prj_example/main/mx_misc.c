/*
	Name:			mx_misc.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


void sys_delay_ms( uint32_t delay );
void sys_delay_us( uint32_t delay );

//void reset_can( void );
//void Init_Can( void );
#ifdef USB_VCP
	void send_usb( char *data, int len );
#endif

// ===========================================================================
void sys_delay_ms( uint32_t delay )		// Delay in milliseconds
// ===========================================================================
{
	volatile uint32_t	i;

	for( i = 0; i < delay; i++ )
	{
		sys_delay_us( 1000 );
	}
}
// ===========================================================================


// ===========================================================================
void sys_delay_us( uint32_t delay )		// Delay in microseconds
// ===========================================================================
{
	#ifdef DWT_
		volatile uint32_t cnt;
		cnt			= F_DWT;
		cnt			*= delay;
		//cnt		+= DWT_CYCCNT;
		DWT_CYCCNT	= 0;
		while( DWT_CYCCNT < cnt ) {}
	#else
		volatile uint32_t i;
		i = ( F_APB1 / 12000000 ) * delay;
		for( ; i != 0; i-- ) {}
	#endif
}
// ===========================================================================


// ===========================================================================
void delay_ms( uint32_t delay )		// Delay in milliseconds
// ===========================================================================
{
	volatile uint32_t	i;

	i = ( F_APB1 / 12000 ) * delay;
	for( ; i != 0; i-- ) {}
}
// ===========================================================================


// ===========================================================================
void delay_us( uint32_t delay )		// Delay in microseconds
// ===========================================================================
{
	volatile uint32_t i;

	i = ( F_APB1 / 12000000 ) * delay;
	for( ; i != 0; i-- ) {}
}
// ===========================================================================


// ===========================================================================
void send_uart1( char *data, int len )	// Print str to USART1; without interrupt
// ===========================================================================
{
	#ifdef USE_UART1
	int		i;
		while( !( USART1->SR & USART_SR_TC ) ) {}
		for( i = 0; i < len; i++ )
		{
			while( !( USART1->SR & USART_SR_TC ) ) {}
			USART1->DR = data[i];
		}
	#endif
}
// ===========================================================================


// ===========================================================================
void print_str( char *str )		// Print str to console
// ===========================================================================
{
	#ifdef USE_UART1
		#ifndef VCP_CONS
			int		i, n;

			while( !( USART1->SR & USART_SR_TC ) ) {}
			n = strlen( str );
			for( i = 0; i < n; i++ )
			{
				while( !( USART1->SR & USART_SR_TC ) ) {}
				USART1->DR = str[i];
			}
		#endif
	#endif
	#ifdef USB_VCP
		#ifdef VCP_CONS
			//int		i, n, n1, n2;
			int		i, n, n1;
			char	s[64];

			n = strlen( str );

			if( n <= 60 )
			{
				send_usb( str, n );
			}
			else
			{
				for( i = 0; i < 60; i++ )
				{
					s[i] = str[i];
				}
				s[i] = 0;
				n1 = strlen( s );
				send_usb( s, n1 );
				if( n >= 120 )
				{
					n = 120;
				}
				n1 = n - 60;
				for( i = 0; i < n1; i++ )
				{
					s[i] = str[i+60];
				}
				s[i] = 0;
				n1 = strlen( s );
				send_usb( s, n1 );
			}
		#endif
	#endif
}
// ===========================================================================


// ===========================================================================
void clr_input( void )
// ===========================================================================
{
	int i;

	for( i = 0; i < RX_LEN; i++ )
	{
		usart_rx_data[i] = 0;
	}
	ret_button = FALSE;
	rx_idx = 0;
}
// ===========================================================================


// ===========================================================================
#ifdef USE_UART1
void USART1_IRQHandler( void )	// USART1 IRQ Handler
// ===========================================================================
{
	#ifndef VCP_CONS	// UART1 as console
		char	s[2];

		// Interruption is caused by receive data
		if( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )
		{	
			s[0] = USART_ReceiveData( USART1 );		// Read char
			//s[0] = c;								// Put char to buffer for "echo"
			s[1] = 0;								// End of string

			if( s[0] == 13 )
			{
				// if( rx_idx == 0 )
				usart_rx_data[rx_idx] = 0;
				ret_button = TRUE;					// Set flag "press Enter"
				rx_idx = 0;
			}
			else
			{
				if( s[0] != 10 )
				{
					if( rx_idx < ( RX_LEN - 1 ) )
					{
						usart_rx_data[rx_idx++] = s[0];	// Char to read buffer
						usart_rx_data[rx_idx] = 0;		// End of string
						if( Echo )
						{
							print_str( s );				// Echo
						}
					}
				}
			}
			USART_ClearITPendingBit( USART1, USART_IT_RXNE );
		}
	#else		// If UART1 not console
		char	c;
		if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )
		{	
			c = USART_ReceiveData( USART1 );
			c++;
			// ... User code
			USART_ClearITPendingBit( USART1, USART_IT_RXNE );
		}
	#endif
}
#endif
// ===========================================================================


// ===========================================================================
void SysTick_Handler( void )	// Priority = 7,0;  Frequency = 100 Hz
// ===========================================================================
{
//	uint32_t i;
//	i = SysTick->CTRL;
//	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;	// Disable SysTick

	#ifdef LED_BLINK
		if( DelayTime )
		{
			DelayTime--;
		}
		else
		{
			DelayTime = 75;
			GPIOC->ODR ^= GPIO_Pin_13;
		}
	#endif

	CntTime++;

	#ifdef I2C1_D
		if( I2C1_ERR > 5 )
		{
			NVIC_SystemReset();
		}
	#endif
	#ifdef I2C2_D
		if( I2C2_ERR > 20 )
		{
			NVIC_SystemReset();
		}
	#endif

	#ifdef CAN_2515
		CANDownTime++;
		if( CANDownTime > 500 )
		{
			reset_can();
			delay_us( 100 );
			Init_Can();
			CANDownTime = 0;
		}
	#endif

	#ifdef WD_TIMER
		if( WD_Time++ > 20 )
		{
			WD_Time = 0;
			IWDG_ReloadCounter();
		}
	#endif

//	SysTick->CTRL = i;	// Enable SysTick
}
// ===========================================================================
