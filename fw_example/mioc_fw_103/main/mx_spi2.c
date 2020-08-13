/*
	Name:			mx_spi.c
	Purpose:		IO module
	Author:			www.open-plc.com
	Created:		2018/07
	Modified by:	2018/11
	RCS-ID:
	Copyright:		(c) Open-PLC
	Licence:		The MIT License (MIT)
*/

#ifndef __SPI2__
#define __SPI2__

#include <stm32f10x_spi.h>

// ===========================================================================
void delay_us_spi2( uint32_t delay )		// Delay in microseconds
// ===========================================================================
{
	volatile uint32_t i;

	i = ( F_APB1 / 12000000 ) * delay;
	for( ; i != 0; i-- ) {}
}
// ===========================================================================


// ===========================================================================
// Init SPI
// ===========================================================================
void Init_Spi2( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef		SPI_InitStructure;

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );	// Clocking SPI2

	// --- SPI2 --------------------------------------------------------------

	/* SPI2 GPIO Configuration
		 PB12 ------> SPI2_NSS
		 PB13 ------> SPI2_SCK
		 PB14 ------> SPI2_MISO
		 PB15 ------> SPI2_MOSI
	*/

	// SPI2_NSS
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure );
	GPIO_SetBits( GPIOB, GPIO_Pin_12 );	// NSS Up

	// SPI2_SCK; SPI2_MOSI
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	// SPI2_MISO
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure );

	// SPI2 Structure Init
	SPI_StructInit( &SPI_InitStructure );
	SPI_InitStructure.SPI_Direction			= SPI_Direction_2Lines_FullDuplex;	// Fullduplex mode
	SPI_InitStructure.SPI_DataSize			= SPI_DataSize_8b;					// Transfer 8 bits
	SPI_InitStructure.SPI_CPOL				= SPI_CPOL_Low;						// Polarity low
	SPI_InitStructure.SPI_CPHA				= SPI_CPHA_1Edge;					// The phase of the clock signal for the front
	SPI_InitStructure.SPI_NSS				= SPI_NSS_Soft;						// State of NSS signal - software control
	SPI_InitStructure.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_32;			// Devider SCK
	SPI_InitStructure.SPI_FirstBit			= SPI_FirstBit_MSB;					// Is first send upper bit
	SPI_InitStructure.SPI_Mode				= SPI_Mode_Master;					// master mode
	//SPI_InitStructure.SPI_CRCPolynomial = 7;									// The checksum (default)
	SPI_Init( SPI2, &SPI_InitStructure );										// Initialize SPI2
	SPI_Cmd( SPI2, ENABLE );													// Switch on module SPI2
}
// ===========================================================================


/* ===========================================================================
   Read/Write data to SPIx
   use arrays spiX_tx_data[] and spiX_rx_data[]
   array size - SPI_LEN
   Work without interruption, so at the same time write and read.
   In read only mode send zeros for strobing. */

// ===========================================================================
void send_spi2( uint8_t cnt )
// ===========================================================================
{
	int	i;

	if( cnt > SPI_LEN )
	{
		cnt = SPI_LEN;
	}

	GPIO_ResetBits( GPIOB, GPIO_Pin_12 );										// NSS Down
	delay_us_spi2( 2 );

	for( i = 0; i < cnt; i++ )
	{
		SPI_I2S_SendData( SPI2, spi2_tx_data[i] );								// Send byte
		while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY) == SET );			// While transceiver is busy

		while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_RXNE ) != SET );		// Wait byte to send
		spi2_rx_data[i] =  SPI_I2S_ReceiveData( SPI2 );							// Get byte
	}	// for( i = 0; i < cnt; i++)

	delay_us_spi2( 2 );
	GPIO_SetBits( GPIOB, GPIO_Pin_12 );											// NSS Up
	delay_us_spi2( 10 );
}
// ===========================================================================

#endif /// SPI2
