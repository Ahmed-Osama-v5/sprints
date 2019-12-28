/*
 * spi.c
 *
 *  Created on: Dec 28, 2019
 *      Author: Ahmed Osama
 */

#include "spi.h"
#include "dio.h"
#include "interrupt.h"

static uint8 gu8_initState = NOT_INITIALIZED;

/**
 * Input: Pointer to callback function.
 * Output: none
 * In/Out: none
 * Return: void
 * Description: Calls the callback function.
 */
static void (*SPI_CBK_Ptr)(void) = {NULL};

/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configration
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_Init(SPI_Cfg_s* pstr_SPI_Confg)
{
	if(NULL != pstr_SPI_Confg)
	{
		/* Create instance of Dio_Cfg_s to Initialize MOSI, MISO and SCK Pins */
		DIO_Cfg_s str_Dio_MOSI_s = {0};
		DIO_Cfg_s str_Dio_MISO_s = {0};
		DIO_Cfg_s str_Dio_SCK_s = {0};

		/* Initialize MOSI as OUTPUT */
		str_Dio_MOSI_s.GPIO = GPIOB;
		str_Dio_MOSI_s.dir = OUTPUT;
		str_Dio_MOSI_s.pins = PIN5;
		DIO_init(&str_Dio_MOSI_s);

		/* Initialize MISO as INPUT */
		str_Dio_MISO_s.GPIO = GPIOB;
		str_Dio_MISO_s.dir = INPUT;
		str_Dio_MISO_s.pins = PIN6;
		DIO_init(&str_Dio_MISO_s);

		/* Pass pointer to callback function */
		if(NULL != pstr_SPI_Confg->CBK_Func)
		{
			SPI_CBK_Ptr = pstr_SPI_Confg->CBK_Func;
		}
		else
		{

		}

		/* Handle interrupt or polling */
		if(pstr_SPI_Confg->u8_InterruptMode == INTERRUPT)
		{
			/* Enable SPI interrupt */
			SPCR |= SPIE;
		}
		else
		{
			/* Disable SPI interrupt */
			SPCR &= ~SPIE;
		}

		/* Handle Data order */
		if(pstr_SPI_Confg->u8_DataOrder == MSB)
		{
			/* DORD = MSB */
			SPCR &= ~DORD;
		}
		else
		{
			/* DORD = LSB */
			SPCR |= DORD;
		}

		/* Handle Data mode */
		switch (pstr_SPI_Confg->u8_DataMode) {
			case (MODE_0):
				/* CPOL = 0, CPHA = 0 */
				SPCR &= ~(CPOL | CPHA);
				break;
			case (MODE_1):
				/* CPOL = 0, CPHA = 1 */
				SPCR |= CPHA;
				SPCR &= ~CPOL;
				break;
			case (MODE_2):
				/* CPOL = 1, CPHA = 0 */
				SPCR &= ~CPHA;
				SPCR |= CPOL;
				break;
			case (MODE_3):
				/* CPOL = 1, CPHA = 1 */
				SPCR |= (CPOL | CPHA);
				break;
			default:
				return E_NOK;
				break;
		}

		switch (pstr_SPI_Confg->u8_SPIMode)
		{
		case (MASTER):
			/* Set SPI module in Master mode */
			SPCR |= MSTR;

			/* Initialize SCK as OUTPUT */
			str_Dio_SCK_s.GPIO = GPIOB;
			str_Dio_SCK_s.dir = OUTPUT;
			str_Dio_SCK_s.pins = PIN7;
			DIO_init(&str_Dio_SCK_s);

			/* Handle prescaler */
			if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_2)
			{
				SPSR |= SPI2X;
				SPCR &= ~SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_4)
			{
				SPSR &= ~SPI2X;
				SPCR &= ~SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_8)
			{
				SPSR |= SPI2X;
				SPCR |= SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_16)
			{
				SPSR &= ~SPI2X;
				SPCR |= SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_32)
			{
				SPSR |= SPI2X;
				SPCR &= ~SPR0;
				SPCR |= SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_64)
			{
				SPSR &= ~SPI2X;
				SPCR &= ~SPR0;
				SPCR |= SPR1;
			}
			else if(pstr_SPI_Confg->u8_Prescaler == SPI_PRESCALER_128)
			{
				SPSR &= ~SPI2X;
				SPCR |= SPR0;
				SPCR |= SPR1;
			}
			else
			{
				return E_NOK;
			}
			break;
		case (SLAVE):
			/* Set SPI module in Slave mode */
			SPCR &= ~MSTR;

			/* Initialize SCK as INPUT */
			str_Dio_SCK_s.GPIO = GPIOB;
			str_Dio_SCK_s.dir = INPUT;
			str_Dio_SCK_s.pins = PIN7;
			DIO_init(&str_Dio_SCK_s);
			break;
		default:
			return E_NOK;
			break;
		}
		/* Enable SPI module */
		SPCR |= SPE;
	}
	else
	{
		return E_NOK;
	}
	gu8_initState = INITIALIZED;
	return E_OK;
}


/**
* @brief: Transmit one byte over SPI
* @param:
* Input : u8_Data "Byte to be sent"
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_SendByte(uint8 u8_Data)
{
	if(gu8_initState == INITIALIZED)
	{
		/* Load SPI shift register with data */
		SPDR = u8_Data;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/**
* @brief: Receive one byte over SPI
* @param:
* Input : None
* Output: *ptru8_Data "points to where received byte is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_ReceiveByte(uint8 *ptru8_Data)
{
	if(gu8_initState == INITIALIZED)
	{
		/* Get data from SPI shift register */
		*ptru8_Data = SPDR;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/**
* @brief: Get status of SPI interrupt flag
* @param:
* Input : None
* Output: *u8_Data "points to where flag value is going to be stored in"
* @return: Error codes if present
*/
ERROR_STATUS SPI_GetStatus(uint8 *u8_Data)
{
	if(gu8_initState == INITIALIZED)
	{
		if(SPSR & SPIF)
		{
			/* SPI flag triggered */
			*u8_Data = TRIGGERED;
		}
		else

		{
			/* SPI flag not triggered */
			*u8_Data = NOT_TRIGGERED;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}

/**
* @brief: Clears flag of SPI
* @param:
* Input : void
* Output: None
* @return: Error codes if present
*/
ERROR_STATUS SPI_ClearFlag(void)
{
	if(gu8_initState == INITIALIZED)
	{
		/* Clear SPI interrupt flag */
		SPSR |= SPIF;
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}


ISR(SPI_STC_vect)
{
	/* Call the callback function */
	SPI_CBK_Ptr();
}
