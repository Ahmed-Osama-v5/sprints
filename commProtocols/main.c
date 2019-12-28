/*
 * main.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed
 */

#include "std_types.h"
#include "spi.h"
#include "interrupt.h"
#include "dio.h"
#include "softwareDelay.h"

int main(void)
{
	SPI_Cfg_s str_SPI_s = {0};
	str_SPI_s.u8_SPIMode = MASTER;
	str_SPI_s.u8_DataMode = MODE_0;
	str_SPI_s.u8_DataOrder = MSB;
	str_SPI_s.u8_InterruptMode = POLLING;
	str_SPI_s.u8_Prescaler = SPI_PRESCALER_32; /* 500 KHz clock */
	str_SPI_s.CBK_Func = NULL;
	SPI_Init(&str_SPI_s);

	DIO_Cfg_s str_Dio_s = {0};
	str_Dio_s.GPIO = GPIOB;
	str_Dio_s.dir = OUTPUT;
	str_Dio_s.pins = PIN4;
	DIO_init(&str_Dio_s);

	/* SS high */
	DIO_Write(GPIOB, PIN4, HIGH);

	DIO_Write(GPIOB, PIN4, LOW);

	//DIO_Write(GPIOB, PIN4, HIGH);

	while(1)
	{
		SPI_SendByte(0xA0);

		/* Poll SPIF */
		uint8 u8_FlagState = NOT_TRIGGERED;

		while(u8_FlagState == NOT_TRIGGERED)
		{
			/* Get SPI flag status */
			SPI_GetStatus(&u8_FlagState);
		}
	}
	return 0;
}
