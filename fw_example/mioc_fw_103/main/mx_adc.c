/*
	Name:			mx_adc.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2019/07
	Modified by:
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/


//============================================================================
void Init_ADC(void)
// ===========================================================================
{
	GPIO_InitTypeDef			GPIO_InitStructure;
	ADC_InitTypeDef				ADC_InitStructure;
	DMA_InitTypeDef				DMA_InitStructure;

	int			i, j;
	uint16_t	ui;

	for( i = 0; i < 8; i++ )
	{
		ADC_NAME_PTR[i] = 0;
		ADC_AVG[i] = 0;
	}

	ui = 0;
	j = 0;
	ADC_NN = 0;
	for( i = 0; i < VAR_NN; i++ )
	{
		if( ADC_NN < 8 )
		{
			if( Var[i].gpio_type == 1 )
			{
				ADC_NAME_PTR[j++] = Var[i].name_ptr;
				ADC_NN++;
				ui |= Var[i].gpio_pin;
			}
		}
	}

	ADC_ARRAY = ADC_ARRAY_SIZE / ADC_NN;
	ADC_SUB_ARRAY = ADC_ARRAY * ADC_NN;

	// Enable ADC1 and DMA clock
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1 | RCC_APB2Periph_AFIO, ENABLE );	// Clocking ADC1
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );							// Clocking DMA1
	//ADC_TempSensorVrefintCmd( ENABLE );

	GPIO_StructInit( &GPIO_InitStructure );
	GPIO_InitStructure.GPIO_Pin		= ui;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	// Start DMA
	DMA_DeInit( DMA1_Channel1 );
	DMA_InitStructure.DMA_BufferSize			= ADC_SUB_ARRAY;
	DMA_InitStructure.DMA_DIR					= DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_M2M					= DMA_M2M_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr		= ( uint32_t ) ADC_VALUES;
	DMA_InitStructure.DMA_MemoryDataSize		= DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc				= DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode					= DMA_Mode_Circular;
	DMA_InitStructure.DMA_PeripheralBaseAddr	= ( uint32_t ) &ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize	= DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc			= DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority				= DMA_Priority_High;
	DMA_Init( DMA1_Channel1, &DMA_InitStructure );
	DMA_Cmd( DMA1_Channel1, ENABLE );

	// Start ADC
	ADC_DeInit( ADC1 );
	ADC_StructInit( &ADC_InitStructure );
	ADC_InitStructure.ADC_ContinuousConvMode	= ENABLE;
	ADC_InitStructure.ADC_DataAlign				= ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv		= ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode					= ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel			= ADC_NN;
	ADC_InitStructure.ADC_ScanConvMode			= ENABLE;
	ADC_Init( ADC1, &ADC_InitStructure );
	for( i = 0; i < ADC_NN; i++ )
	{
		for( j = 0; j < VAR_NN; j++ )
		{
			if( ADC_NAME_PTR[i] == Var[j].name_ptr )
			{
				switch( Var[j].gpio_pin )
				{
					case GPIO_Pin_0:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_0, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_1:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_1, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_2:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_2, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_3:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_3, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_4:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_4, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_5:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_5, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_6:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_6, (i+1), ADC_SampleTime_55Cycles5 );
						break;
					case GPIO_Pin_7:
						ADC_RegularChannelConfig( ADC1, ADC_Channel_7, (i+1), ADC_SampleTime_55Cycles5 );
				}
			}
		}
	}
	ADC_Cmd( ADC1, ENABLE );
	ADC_DMACmd( ADC1, ENABLE );
	ADC_ResetCalibration( ADC1 );
	while( ADC_GetResetCalibrationStatus( ADC1 ) ) {}
	ADC_StartCalibration( ADC1 );
	while( ADC_GetCalibrationStatus( ADC1 ) ) {}
	ADC_SoftwareStartConvCmd( ADC1 , ENABLE );
}
// ===========================================================================
