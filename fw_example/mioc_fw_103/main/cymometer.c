static volatile uint32_t Freq = 0;

// ===========================================================================
void Init_Cymometer( void )
// ===========================================================================
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    TIM1->PSC    = 7200 - 1;
    TIM1->ARR    = 10000 - 1;
    TIM1->CR1   |= TIM_CR1_DIR;
    TIM1->CR1   |= TIM_CR1_OPM;
    TIM1->CR2   |= TIM_CR2_MMS_0;
    TIM1->DIER  |= TIM_DIER_UIE;

    TIM2->PSC    = 0;
    TIM2->ARR    = 0xFFFF;
    TIM2->CR1   &= ~TIM_CR1_DIR;
    TIM2->CR1   &= ~TIM_CR1_OPM;
    TIM2->CR2   |= TIM_CR2_MMS_1;
    TIM2->SMCR  |= TIM_SMCR_ECE;
    TIM2->SMCR  &= ~TIM_SMCR_ETPS;
    TIM2->SMCR  &= ~TIM_SMCR_ETF;
    TIM2->SMCR  |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_2;

    TIM4->PSC    = 0;
    TIM4->ARR    = 0xFFFF;
    TIM4->CR1   &= ~TIM_CR1_DIR;
    TIM4->SMCR  &= ~TIM_SMCR_ETPS;
    TIM4->SMCR  &= ~TIM_SMCR_ETF;
    TIM4->SMCR  |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2 | TIM_SMCR_TS_0;

    NVIC_EnableIRQ( TIM1_UP_IRQn );

    TIM4->CR1   |= TIM_CR1_CEN;
    TIM2->CR1   |= TIM_CR1_CEN;
    TIM1->CR1   |= TIM_CR1_CEN;
}
// ===========================================================================


// ===========================================================================
void TIM1_UP_IRQHandler(void)
// ===========================================================================
{
    TIM1->SR &= ~TIM_SR_UIF;
    Freq = ( ( uint32_t )( TIM4->CNT ) << 16 ) | ( ( uint32_t )( TIM2->CNT ) );
    TIM2->CNT = 0;
    TIM4->CNT = 0;
    TIM1->CR1 |= TIM_CR1_CEN;
}
// ===========================================================================
