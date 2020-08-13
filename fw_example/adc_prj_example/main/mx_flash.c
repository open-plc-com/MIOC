// ===========================================================================
void Get_SN( void )
// ===========================================================================
{
	static uint32_t		*uid = ( uint32_t* ) 0x1FFFF7E8;

	Sn		 = ( uid[0] ^ uid[2] );
	Sn8		 = uid[0];
	Sn8		 = Sn8 << 32;
	Sn8		|= uid[2];
}
// ===========================================================================


// ===========================================================================
void Write_Flash( void )
// ===========================================================================
{
//	uint32_t	i;
//	uint16_t	j, k, l;
//char s[128];

//	// FLASH_Unlock
//	FLASH->KEYR = FLASH_KEY1;
//	FLASH->KEYR = FLASH_KEY2;
//
//	// FLASH_Erase Page
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	FLASH->CR |= FLASH_CR_PER;			//Page Erase Set
//	FLASH->AR = Page_PRM;				//Page Address
//	FLASH->CR |= FLASH_CR_STRT;			//Start Page Erase
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	FLASH->CR &= ~FLASH_CR_PER;			//Page Erase Clear
//	FLASH->CR |= FLASH_CR_PG;			// FLASH_Program HalfWord
//
//	i = DeviceType; j = i & 0xFFFF;
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) Page_PRM = j;
//	i = i >> 16; j = i & 0xFFFF;
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 2 ) = j;
//
//	i = Sn; j = i & 0xFFFF;
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 4 )= j;
//	i = i >> 16; j = i & 0xFFFF;
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 6 ) = j;
//
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 8 ) = Noc;
//
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 10 ) = Speedc;
//
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 12 ) = Nn_Ch;
//
//	while( FLASH->SR&FLASH_SR_BSY ) {}
//	*( __IO uint16_t* ) ( Page_PRM + 14 ) = iButton_Timeout;
//
//	//while( FLASH->SR&FLASH_SR_BSY ) {}
//	//*( __IO uint16_t* ) ( Page_PRM + 16 ) = Show_Data;
//
//	k = 16;
//	for( i = 0; i < MAX_NN_CH; i++ )
//	{
//		if( GPIO_X[i].gpio_x == GPIOA )
//		{
//			l = 1;
//		}
//		else
//		if( GPIO_X[i].gpio_x == GPIOB )
//		{
//			l = 2;
//		}
//		else
//		if( GPIO_X[i].gpio_x == GPIOC )
//		{
//			l = 3;
//		}
//		else
//		{
//			l = 0;
//		}
//		while( FLASH->SR&FLASH_SR_BSY ) {}
//		*( __IO uint16_t* ) ( Page_PRM + k ) = l; k += 2;
//
//		l = GPIO_X[i].gpio_pin_nn;
//		while( FLASH->SR&FLASH_SR_BSY ) {}
//		*( __IO uint16_t* ) ( Page_PRM + k ) = l; k += 2;
//
////sprintf( s, " GPIO_X[%d].dev_type=%d\r\n", i, GPIO_X[i].dev_type ); print_str( s );
//		l = GPIO_X[i].dev_type;
//		while( FLASH->SR&FLASH_SR_BSY ) {}
//		*( __IO uint16_t* ) ( Page_PRM + k ) = l; k += 2;
//
//	}	// for( i = 0; i < Ch_Nn; i++ )
//
//	while( ( FLASH->SR&FLASH_SR_BSY ) ) {}
//	FLASH->CR &= ~FLASH_CR_PG;
//	FLASH->CR |= FLASH_CR_LOCK;
//
//	//if( Nn_Ch )
//	//{
//		//free( GPIO_X );
//	//}
}
// ===========================================================================


// ===========================================================================
void Read_Flash( void )
// ===========================================================================
{
//	uint32_t			i;
//	uint16_t			k, l;
//	static uint32_t		*uid  = ( uint32_t* ) 0x1FFFF7E8;
//	static uint64_t		*uid8 = ( uint64_t* ) 0x1FFFF7E8;
//
//	DeviceType		= *( uint32_t* )   Page_PRM;
//	Sn				= *( uint32_t* ) ( Page_PRM + 4 );
//	Noc				= *( uint16_t* ) ( Page_PRM + 8 );
//	Speedc			= *( uint16_t* ) ( Page_PRM + 10 );
//	Nn_Ch			= *( uint16_t* ) ( Page_PRM + 12 );
//	iButton_Timeout	= *( uint16_t* ) ( Page_PRM + 14 );
//	//Show_Data		= *( uint16_t* ) ( Page_PRM + 16 );
//
//	if( ( Nn_Ch > MAX_NN_CH ) || ( Nn_Ch == 0 ) )
//	{
//		Nn_Ch = 1;
//	}
//
//	k = 16;
//	for( i = 0; i < MAX_NN_CH; i++ )
//	{
//		l = *( uint16_t* ) ( Page_PRM + k ); k += 2;
//
//		if( l == 1 )
//		{
//			GPIO_X[i].gpio_x = GPIOA;
//		}
//		else
//		if( l == 2 )
//		{
//			GPIO_X[i].gpio_x = GPIOB;
//		}
//		else
//		if( l == 2 )
//		{
//			GPIO_X[i].gpio_x = GPIOC;
//		}
//		else
//		{
//			GPIO_X[i].gpio_x = 0;
//		}
//
//		l = *( uint16_t* ) ( Page_PRM + k ); k += 2;
//		if( l < 16 )	// Max port_x number
//		{
//			GPIO_X[i].gpio_pin_nn = l;
//		}
//		else
//		{
//			GPIO_X[i].gpio_x = 0;
//			GPIO_X[i].gpio_pin_nn = 0;
//		}
//
//		l = *( uint16_t* ) ( Page_PRM + k ); k += 2;
//		if( l <= MAX_DEV_TYPE )
//		{
//			GPIO_X[i].dev_type = l;
//		}
//		else
//		{
//			GPIO_X[i].dev_type = 0;
//		}
//
//		switch( GPIO_X[i].gpio_pin_nn )
//		{
//			case 0:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_0;	break;
//			case 1:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_1;	break;
//			case 2:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_2;	break;
//			case 3:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_3;	break;
//			case 4:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_4;	break;
//			case 5:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_5;	break;
//			case 6:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_6;	break;
//			case 7:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_7;	break;
//			case 8:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_8;	break;
//			case 9:		GPIO_X[i].gpio_pin_x	= GPIO_Pin_9;	break;
//			case 10:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_10;	break;
//			case 11:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_11;	break;
//			case 12:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_12;	break;
//			case 13:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_13;	break;
//			case 14:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_14;	break;
//			case 15:	GPIO_X[i].gpio_pin_x	= GPIO_Pin_15;	break;
//			default:	GPIO_X[i].gpio_pin_x	= 0;
//		}
//	}	// for( i = 0; i < MAX_NN_CH; i++ )
//
//	if( iButton_Timeout > 80 )
//	{
//		iButton_Timeout = 80;	// 10 sec
//	}
//
//	#ifdef DEV_TYPE
//		DeviceType = DEV_TYPE;
//	#endif
//	#ifdef DEV_ID
//		Sn = uid[2];
//	#endif
//	Sn8 = *uid8;
}
// ===========================================================================
