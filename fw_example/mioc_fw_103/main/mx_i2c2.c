#ifdef I2C2_D
// ===========================================================================
void init_I2C2( void )
// ===========================================================================
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	I2C_Cmd( I2C2, DISABLE );
	I2C_DeInit( I2C2 );
	I2C_StructInit( &I2C_InitStructure );

	/* Configure I2C_EE pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* I2C configuration */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	//I2C_InitStructure.I2C_OwnAddress1 = 0x38;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_Init( I2C2, &I2C_InitStructure );

	I2C_Cmd( I2C2, ENABLE );
}
// ===========================================================================
#endif
