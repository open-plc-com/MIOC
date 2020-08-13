#ifndef __ssd1306_I2C_H__
#define __ssd1306_I2C_H__

#ifndef ssd1306_I2C_TIMEOUT
	#define ssd1306_I2C_TIMEOUT		200000
#endif

void		init_I2C1( void );
void		ssd1306_I2C_Write( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t data );
void		ssd1306_I2C_WriteMulti( I2C_TypeDef *I2Cx, uint8_t address, uint8_t reg, uint8_t *data, uint16_t count );
int16_t		ssd1306_I2C_Start( I2C_TypeDef *I2Cx, uint8_t address, uint8_t direction, uint8_t ack );
void		ssd1306_I2C_WriteData( I2C_TypeDef *I2Cx, uint8_t data );

#endif	// __ssd1306_I2C_H__
