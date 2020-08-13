/*
	Name:			mx_timers.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:	2019/09
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


// ===========================================================================
void Init_Timer3( void )
// ===========================================================================
{
	NVIC_InitTypeDef			NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef		TIMER_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );

	TIM_TimeBaseStructInit( &TIMER_InitStructure );
	TIMER_InitStructure.TIM_CounterMode		= TIM_CounterMode_Up;
	#if F_APB1 == 72000000
		TIMER_InitStructure.TIM_Prescaler	= 7200-1;
	#endif
	#if F_APB1 == 48000000
		TIMER_InitStructure.TIM_Prescaler	= 4800-1;
	#endif
	#if F_APB1 == 24000000
		TIMER_InitStructure.TIM_Prescaler	= 2400-1;
	#endif
	TIMER_InitStructure.TIM_Period			= 10-1;
	TIM_TimeBaseInit( TIM3, &TIMER_InitStructure );
	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );
	TIM_Cmd( TIM3, ENABLE );

	// NVIC Configuration
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );
	NVIC_InitStructure.NVIC_IRQChannel						= TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init( &NVIC_InitStructure );
}
// ===========================================================================


// ===========================================================================
void Init_Timer4( void )
// ===========================================================================
{
	NVIC_InitTypeDef			NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef		TIMER_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );	// Clocking TIM4

	TIM_TimeBaseStructInit( &TIMER_InitStructure );
	TIMER_InitStructure.TIM_CounterMode		= TIM_CounterMode_Up;
	#if F_APB1 == 72000000
		TIMER_InitStructure.TIM_Prescaler	= 7200-1;
	#endif
	#if F_APB1 == 48000000
		TIMER_InitStructure.TIM_Prescaler	= 4800-1;
	#endif
	#if F_APB1 == 24000000
		TIMER_InitStructure.TIM_Prescaler	= 2400-1;
	#endif

	TIMER_InitStructure.TIM_Period			= 10-1;
	TIM_TimeBaseInit( TIM4, &TIMER_InitStructure );
	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE );
	TIM_Cmd( TIM4, ENABLE );

	// NVIC Configuration
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 );
	NVIC_InitStructure.NVIC_IRQChannel						= TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_Init( &NVIC_InitStructure );
}
// ===========================================================================


// ===========================================================================
void TIM3_IRQHandler( void )
// CLI; Read DATA; Print DATA
// ===========================================================================
{
	TIM_Cmd( TIM3, DISABLE );

	Cli();
	Read_Data();
	if( Show_Data ) { Print_Data(); }

	#ifdef WD_TIMER
	if( WD_Time++ > 20 )
	{
		WD_Time = 0;
		IWDG_ReloadCounter();
	}
	#endif

	if( TIM_GetITStatus( TIM3, TIM_IT_Update ) != RESET )
	{
		TIM_ClearITPendingBit( TIM3, TIM_IT_Update );
	}
	TIM_Cmd( TIM3, ENABLE );
}
// ===========================================================================


// ===========================================================================
void TIM4_IRQHandler( void )
// ===========================================================================
{
	int			i, j, k;
	uint32_t	sum[8], n[8];

	//DMA_Cmd( DMA1_Channel1, DISABLE );
	TIM_Cmd( TIM4, DISABLE );

	for( i = 0; i < ADC_NN; i++ )
	{
		sum[i]	= 0;
		n[i]	= 0;
	}

//	A = 0;
	k = 0;
	for( i = 0; i < ADC_ARRAY; i++ )
	{
		for( j = 0; j < ADC_NN; j++ )
		{
			if( !( ADC_VALUES[k] & 0x8000 ) )
			{
				sum[j] += ADC_VALUES[k];
				n[j]++;
//				A++;
				ADC_VALUES[k] = 0xFFFF;
			}
			k++;
		}
	}

	for( i = 0; i < ADC_NN; i++ )
	{
		ADC_AVG[i] = sum[i] / ADC_ARRAY;
		if( n[i] )
		{
			sum[i] /= n[i];
		}
		else
		{
			sum[i] = 0;
		}
	}

	for( i = 0; i < ADC_NN; i++ )
	{
		ADC_AVG[i] = sum[i];
	}

//GPIOC->ODR ^= GPIO_Pin_13;

	#ifdef WD_TIMER
	if( WD_Time++ > 20 )
	{
		WD_Time = 0;
		IWDG_ReloadCounter();
	}
	#endif

	if( TIM_GetITStatus( TIM4, TIM_IT_Update ) != RESET )
	{
		TIM_ClearITPendingBit( TIM4, TIM_IT_Update );
	}
	//DMA_Cmd( DMA1_Channel1, ENABLE );
	TIM_Cmd( TIM4, ENABLE );
}
// ===========================================================================
