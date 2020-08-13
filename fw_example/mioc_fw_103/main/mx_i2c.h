/*
Не блокирующая реализация I2C для микроконтроллеров STM32F030
Прерывания не используются
SPL используется только для выбора альтернативной функции
При желании можно настроить AF ручками и выкинуть SPL совсем
--------------------------
Автор Zlodey
masya-chel@mail.ru
masya-chel@yandex.ru
--------------------------
Март 2015г.
*/

#ifndef I2C_H	// Блокирую повторное включение этого модуля
#define I2C_H

#include "main.h"

#define I2C_BUS I2C1


// Вспомогательные переменные
typedef enum _I2C_Direction {I2C_Transmitter=0, I2C_Receiver=1} I2C_Direction;
/*
Битовые смещения для настройки разных регистров
Чтобы не использовать в коде магические числа, и код был читаемым
Например:
I2C->CR2 |= 1<<I2C_OFFSET_CR2_NBYTES;	// Здесь понятно, что передаётся 1 байт
I2C->CR2 |= 1<<16;						// Здесь возникает путаница, то ли 1 байт, то ли 16
*/
#define I2C_OFFSET_TIMINGR_SCLL		0
#define I2C_OFFSET_TIMINGR_SCLH		8
#define I2C_OFFSET_TIMINGR_SDADEL	16
#define I2C_OFFSET_TIMINGR_SCLDEL	20
#define I2C_OFFSET_TIMINGR_PRESC	28
#define I2C_OFFSET_CR2_NBYTES		16


////////////////////////////////////////////////
//    Секция прототипов локальных функций     //
////////////////////////////////////////////////
void I2C_Initialization (void);
void I2C_Start (void);
void I2C_Stop (void);
u8 I2C_Write_Transaction (u8 Adress, u8 Register, u8 *Data, u8 Size);
u8 I2C_Read_Transaction (u8 Adress, u8 Register, u8 *Data, u8 Size);


#endif



