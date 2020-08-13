/*
	Name:			mx_init.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


// ===========================================================================
void MX_Init( void )
// ===========================================================================
{
	GPIO_InitTypeDef			GPIO_InitStructure;
	#ifdef USE_UART1
		USART_InitTypeDef			USART_InitStructure;
	#endif
	NVIC_InitTypeDef			NVIC_InitStructure;

	int			i, j;
	uint16_t	gpio_type, gpio_type_cmp;
	uint16_t	ui;
    GPIO_TypeDef  *gpio;

	#ifdef USB_VCP
		#if F_APB1 == 24000000
			#undef USB_VCP
			//#undef VCP_CONS
		#endif
	#endif

	// -----------------------------------------------------------------------
	// Oscilator
	// -----------------------------------------------------------------------
	#if( F_APB1 != 72000000 ) && ( F_APB1 != 48000000 ) && ( F_APB1 != 24000000 )
		#error Wrong clock configuration
	#endif

	RCC_DeInit();														// Resets the RCC clock configuration to the default reset state.

	#if F_APB1 == 72000000
		#ifdef OSC_INT													// === Internal ===
			#define F_APB1 48000000										// !!!
			RCC_HSEConfig( RCC_HSE_OFF );								// Configures the Internal oscillator (HSI).
			RCC_HSICmd( ENABLE );										// Enables the Internal High Speed oscillator (HSI).
			RCC_PLLConfig( RCC_PLLSource_HSI_Div2, RCC_PLLMul_12 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div2 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div4 );							// Configures the ADC clock (ADCCLK).
		#else															// === External ===
			RCC_HSICmd( DISABLE );										// Enables the External High Speed oscillator (HSE).
			RCC_HSEConfig( RCC_HSE_ON );								// Configures the External High Speed oscillator (HSE).
			RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div2 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div6 );							// Configures the ADC clock (ADCCLK).
			#ifdef USB_VCP
				RCC_USBCLKConfig( RCC_USBCLKSource_PLLCLK_1Div5 );		// Configures the USB clock.
			#endif
		#endif
	#endif
	#if F_APB1 == 48000000
		#ifdef OSC_INT													// === Internal ===
			RCC_HSEConfig( RCC_HSE_OFF );								// Configures the Internal oscillator (HSI).
			RCC_HSICmd( ENABLE );										// Enables the Internal High Speed oscillator (HSI).
			RCC_PLLConfig( RCC_PLLSource_HSI_Div2, RCC_PLLMul_12 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div2 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div4 );							// Configures the ADC clock (ADCCLK).
			#ifdef USB_VCP
				RCC_USBCLKConfig( RCC_USBCLKSource_PLLCLK_Div1 );
			#endif
		#else															// === External ===
			RCC_HSICmd( DISABLE );										// Enables the External High Speed oscillator (HSE).
			RCC_HSEConfig( RCC_HSE_ON );								// Configures the External High Speed oscillator (HSE).
			RCC_PLLConfig( RCC_PLLSource_HSE_Div2, RCC_PLLMul_12 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div2 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div4 );							// Configures the ADC clock (ADCCLK).
			#ifdef USB_VCP
				RCC_USBCLKConfig( RCC_USBCLKSource_PLLCLK_Div1 );		// Configures the USB clock.
			#endif
		#endif
	#endif
	#if F_APB1 == 24000000
		#ifdef OSC_INT													// === Internal ===
			RCC_HSEConfig( RCC_HSE_OFF );								// Configures the Internal oscillator (HSI).
			RCC_HSICmd( ENABLE );										// Enables the Internal High Speed oscillator (HSI).
			RCC_PLLConfig( RCC_PLLSource_HSI_Div2, RCC_PLLMul_6 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div2 );							// Configures the ADC clock (ADCCLK).
		#else															// === External ===
			RCC_HSICmd( DISABLE );										// Enables the External High Speed oscillator (HSE).
			RCC_HSEConfig( RCC_HSE_ON );								// Configures the External High Speed oscillator (HSE).
			RCC_PLLConfig( RCC_PLLSource_HSE_Div2, RCC_PLLMul_6 );		// Configures the PLL clock source and multiplication factor.
			RCC_HCLKConfig( RCC_SYSCLK_Div1 );							// Configures the AHB clock (HCLK).
			RCC_PCLK1Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK1).
			RCC_PCLK2Config( RCC_HCLK_Div1 );							// Configures the Low Speed APB clock (PCLK2).
			RCC_ADCCLKConfig( RCC_PCLK2_Div2 );							// Configures the ADC clock (ADCCLK).
		#endif
	#endif
	RCC_PLLCmd( ENABLE );												// Enables the PLL.
	while( RCC_GetFlagStatus( RCC_FLAG_PLLRDY ) == RESET ) {}			// Wait till PLL is ready
	RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );						// Configures the system clock as PLL source (SYSCLK).
	while( RCC_GetSYSCLKSource() != 0x08 ) {}							// Wait till PLL is used as system clock source


	// -----------------------------------------------------------------------
	// Enable peripheral clock
	// -----------------------------------------------------------------------
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );				// Clocking GPIOA
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );				// Clocking GPIOB
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );				// Clocking GPIOC
	#ifdef USE_UART1
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );		// Clocking USART1
	#endif
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );				// Clocking AF APB2
	#if( F_APB1 == 48000000 ) || ( F_APB1 == 72000000 )
		#ifdef USB_VCP
			RCC_APB1PeriphClockCmd( RCC_APB1Periph_USB, ENABLE );		// Clocking USB
		#endif
	#endif


	// -----------------------------------------------------------------------
	// Start DWT
	// -----------------------------------------------------------------------
	#ifdef DWT
		SCB_DEMCR		|= 0x01000000;	// enable trace
		DWT_LAR			 = 0xC5ACCE55;	// unlock access to DWT (ITM, etc.) registers
		DWT_CONTROL		|= 1;			// enable DWT cycle counter
		DWT_CYCCNT		 = 0;			// clear DWT cycle counter
	#endif


	// -----------------------------------------------------------------------
	// Set NVIC Priority Group
	// -----------------------------------------------------------------------
	/* PriorityGroup_0: 0 bits for pre-emption priority
	                    4 bits for subpriority
	   PriorityGroup_1: 1 bits for pre-emption priority
	                    3 bits for subpriority
	   PriorityGroup_2: 2 bits for pre-emption priority
	                    2 bits for subpriority
	   PriorityGroup_3: 3 bits for pre-emption priority
	                    1 bits for subpriority
	   PriorityGroup_4: 4 bits for pre-emption priority
	                    0 bits for subpriority */
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );


	#ifdef USE_UART1
		// -----------------------------------------------------------------------
		// Init UARTS
		// -----------------------------------------------------------------------
		// USART1 GPIO Configuration
		// PA9	-> USART1_Tx
		// PA10	<- USART1_Rx

		// Init pins PA9 and PA10 ( Rx / Tx USART1 )
		GPIO_StructInit( &GPIO_InitStructure );
		GPIO_InitStructure.GPIO_Mode					= GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin						= GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed					= GPIO_Speed_2MHz;
		GPIO_Init( GPIOA, &GPIO_InitStructure );

		GPIO_InitStructure.GPIO_Mode					= GPIO_Mode_IN_FLOATING;
		GPIO_InitStructure.GPIO_Pin						= GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Speed					= GPIO_Speed_2MHz;
		GPIO_Init( GPIOA, &GPIO_InitStructure );

		// Setup USART1 parameters
		USART_StructInit( &USART_InitStructure );
		USART_InitStructure.USART_BaudRate				= UART1_SPEED;
		USART_InitStructure.USART_WordLength			= USART_WordLength_8b;
		USART_InitStructure.USART_StopBits				= USART_StopBits_1;
		USART_InitStructure.USART_Parity				= USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode					= USART_Mode_Rx | USART_Mode_Tx;
		USART_Init( USART1, &USART_InitStructure );
		USART_Cmd( USART1, ENABLE );

		// Start UART interrupt
		NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );
		NVIC_InitStructure.NVIC_IRQChannel						= USART1_IRQn;	// Setup interrupt
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;		// Setup enable interrupt
		NVIC_Init( &NVIC_InitStructure );										// Init interrupt
		USART_Cmd( USART1, ENABLE );											// Enable USART1

		NVIC_EnableIRQ( USART1_IRQn );											// Enable interrupt UART1
		USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );						// Enable interrupt for Rx
		//USART_ITConfig( USART1, USART_IT_TC, ENABLE );						// Enable interrupt for Tx
	#endif


	// -----------------------------------------------------------------------
	// Init GPIOs
	// -----------------------------------------------------------------------


//	// -----------------------------------------------------------------------
//	// PB5 - MCP2515 interrupt
//	// -----------------------------------------------------------------------
//	#ifdef CAN_2515
//		//GPIO_PinRemapConfig( GPIO_Remap_SWJ_Disable, ENABLE );
//		GPIO_StructInit( &GPIO_InitStructure );
//		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_5;
//		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
//		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;
//		GPIO_Init( GPIOB, &GPIO_InitStructure );
//	#endif


	// -----------------------------------------------------------------------
	// Configure GPIO pin PC13 ( LED blink )
	// -----------------------------------------------------------------------
	//#ifdef LED_BLINK
		GPIO_StructInit( &GPIO_InitStructure );
		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_10MHz;
		GPIO_Init( GPIOC, &GPIO_InitStructure );
		GPIO_SetBits( GPIOC, GPIO_Pin_13 );		// Clear bit "blinking"; LED On
	//#endif


	#ifdef MCO
		GPIO_StructInit( &GPIO_InitStructure );
		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
		//GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
		GPIO_Init( GPIOA, &GPIO_InitStructure );
		RCC_MCOConfig( RCC_MCO_HSE );
		//RCC_MCOConfig( RCC_MCO_HSI );
		//RCC_MCOConfig( RCC_MCO_PLLCLK_Div2 );
	#endif


	// -----------------------------------------------------------------------
	// Configure USB GPIO pin
	//   PA11 - USB DM
	//   PA12 - USB DP
	// -----------------------------------------------------------------------
	#ifdef USB_VCP
		//GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
		//GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
		GPIO_Init( GPIOA, &GPIO_InitStructure );
		GPIO_ResetBits( GPIOA, GPIO_Pin_12 );
	#endif


//	// -----------------------------------------------------------------------
//	// Configure GPIO pin : PB2 - BOOT1
//	// -----------------------------------------------------------------------
//	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
//	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_10MHz;
//	GPIO_Init( GPIOB, &GPIO_InitStructure );


	// -----------------------------------------------------------------------
	// Init GPIOs
	// -----------------------------------------------------------------------

	GPIO_StructInit( &GPIO_InitStructure );

	for( gpio_type = 1; gpio_type < 9; gpio_type++ )
	{
		gpio = 0;
		for( j = 0; j < 3; j++ )
		{
			if( j == 0 )
			{
				gpio = GPIOA;
			}
			else
			if( j == 1 )
			{
				gpio = GPIOB;
			}
			else
			if( j == 2 )
			{
				gpio = GPIOC;
			}

			ui = 0;
			for( i = 0; i < VAR_NN; i++ )
			{
				if( Var[i].gpio_type == 1 )
				{
					gpio_type_cmp = 0;
				}
				else
				{
					gpio_type_cmp = Var[i].gpio_type;
				}
				if( ( gpio_type_cmp == gpio_type ) && ( Var[i].gpio == gpio ) )
				{
					switch( Var[i].gpio_pin )
					{
						case GPIO_Pin_0:  ui |= GPIO_Pin_0;  break;
						case GPIO_Pin_1:  ui |= GPIO_Pin_1;  break;
						case GPIO_Pin_2:  ui |= GPIO_Pin_2;  break;
						case GPIO_Pin_3:  ui |= GPIO_Pin_3;  break;
						case GPIO_Pin_4:  ui |= GPIO_Pin_4;  break;
						case GPIO_Pin_5:  ui |= GPIO_Pin_5;  break;
						case GPIO_Pin_6:  ui |= GPIO_Pin_6;  break;
						case GPIO_Pin_7:  ui |= GPIO_Pin_7;  break;
						case GPIO_Pin_8:  ui |= GPIO_Pin_8;  break;
						case GPIO_Pin_9:  ui |= GPIO_Pin_9;  break;
						case GPIO_Pin_10: ui |= GPIO_Pin_10; break;
						case GPIO_Pin_11: ui |= GPIO_Pin_11; break;
						case GPIO_Pin_12: ui |= GPIO_Pin_12; break;
						case GPIO_Pin_13: ui |= GPIO_Pin_13; break;
						case GPIO_Pin_14: ui |= GPIO_Pin_14; break;
						case GPIO_Pin_15: ui |= GPIO_Pin_15; break;
					}
//print( "i=%d gpio_pin=%0X\r\n", i+1, Var[i].gpio_pin );
				}
			}
			if( ui )
			{
				switch( gpio_type )
				{
					case 1: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;         break;
					case 2: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
					case 3: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         break;
					case 4: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         break;
					case 5: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;      break;
					case 6: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      break;
					case 7: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      break;	// DS18B20
					case 8: GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      break;	// iButton
				}
				GPIO_InitStructure.GPIO_Pin		= ui;
				GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_10MHz;
				GPIO_Init( gpio, &GPIO_InitStructure );
//print( "gpio_type=%d gpio=%d ui=%0X\r\n", gpio_type, gpio, ui );
			}
		}
	}

	// -----------------------------------------------------------------------
	// Set or reset pins
	// -----------------------------------------------------------------------
	for( i = 0; i < VAR_NN; i++ )
	{
		if( ( Var[i].gpio_type == 4 ) || ( Var[i].gpio_type == 7 ) || ( Var[i].gpio_type == 8 ) )
		{
			GPIO_SetBits( Var[i].gpio, Var[i].gpio_pin );
		}
		else
		if( Var[i].gpio_type == 3 )
		{
			GPIO_ResetBits( Var[i].gpio, Var[i].gpio_pin );
		}

		if( Var[i].gpio_type == 1 )
		{
			ADC_NN = 1;
			break;
		}
	}

	if( ADC_NN )
	{
		Init_ADC();
		Init_Timer4();
//print( "ADC_NN=%d\r\n", ADC_NN );
	}


	// -----------------------------------------------------------------------
	// Init SysTick timer
	// SysTick_Config( SysyTick ) SysyTick - Number of ticks between two interrupts
	// -----------------------------------------------------------------------
	//SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK_Div8 );
	SysTick_Config( F_APB1 / 100 );

	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );
	NVIC_InitStructure.NVIC_IRQChannel						= ( uint8_t ) SysTick_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init( &NVIC_InitStructure );


	// -----------------------------------------------------------------------
	// Start watchdog timer
	// -----------------------------------------------------------------------
	#ifdef WD_TIMER
		IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
		//IWDG_SetPrescaler( IWDG_Prescaler_64 );
		IWDG_SetPrescaler( IWDG_Prescaler_32 );
		IWDG_SetReload( 40000 / 16 );
		//IWDG_SetReload( 40000 / 128 );								// 312 ms
		//IWDG_SetReload( 40000 / 256 );							// 150 ms
		IWDG_ReloadCounter();
		IWDG_Enable();
	#endif


	// -----------------------------------------------------------------------
	// Init Program Data
	// -----------------------------------------------------------------------
	CntTime			= 0;		// SysTick count
	DelayTime		= 0;
	ret_button		= FALSE;	// Press "Enter"?

//	NoAnswer		= FALSE;	// No answer in CAN broadcast
//	CANDownTime		= 0;
//	CAN_Run			= FALSE;

	Step_DS			= 0;
	Step_BTN		= 0;

	Lc1				= CntTime;
	Lc2				= CntTime;
	Lc3				= CntTime;
}
// ===========================================================================
