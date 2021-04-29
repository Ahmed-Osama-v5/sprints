/*
 * spi.c
 *
 *  Created on: Dec 28, 2019
 *      Author: Ahmed Osama
 */

#include "spi.h"

static uint8 gu8_initState = NOT_INITIALIZED;

/**
* @brief: SPI callback function
* @param:
* Input : void
* Output: None
* @return: void
*/
static void (*SPI_CBK_Ptr)(void) = {NULL};

/**
* @brief: Initialize SPI module
* @param:
* Input : SPI_Cfg_s* "Pointer to Struct of SPI Configuration
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
		str_Dio_MOSI_s.pins = PIN3;
		DIO_init(&str_Dio_MOSI_s);

		/* Initialize MISO as INPUT */
		str_Dio_MISO_s.GPIO = GPIOB;
		str_Dio_MISO_s.dir = INPUT;
		str_Dio_MISO_s.pins = PIN4;
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
		if(pstr_SPI_Confg->SPI_InterruptMode == SPI_INTERRUPT)
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
		if(pstr_SPI_Confg->SPI_DataOrder == SPI_MSB)
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
		switch (pstr_SPI_Confg->SPI_DataMode) {
			case (SPI_MODE_0):
				/* CPOL = 0, CPHA = 0 */
				SPCR &= ~(CPOL | CPHA);
				break;
			case (SPI_MODE_1):
				/* CPOL = 0, CPHA = 1 */
				SPCR |= CPHA;
				SPCR &= ~CPOL;
				break;
			case (SPI_MODE_2):
				/* CPOL = 1, CPHA = 0 */
				SPCR &= ~CPHA;
				SPCR |= CPOL;
				break;
			case (SPI_MODE_3):
				/* CPOL = 1, CPHA = 1 */
				SPCR |= (CPOL | CPHA);
				break;
			default:
				return E_NOK;
				break;
		}

		switch (pstr_SPI_Confg->SPI_Mode)
		{
		case (SPI_MASTER):
			/* Set SPI module in Master mode */
			SPCR |= MSTR;

			/* Initialize SCK as OUTPUT */
			str_Dio_SCK_s.GPIO = GPIOB;
			str_Dio_SCK_s.dir = OUTPUT;
			str_Dio_SCK_s.pins = PIN5;
			DIO_init(&str_Dio_SCK_s);

			/* Handle prescaler */
			if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_2)
			{
				SPSR |= SPI2X;
				SPCR &= ~SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_4)
			{
				SPSR &= ~SPI2X;
				SPCR &= ~SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_8)
			{
				SPSR |= SPI2X;
				SPCR |= SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_16)
			{
				SPSR &= ~SPI2X;
				SPCR |= SPR0;
				SPCR &= ~SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_32)
			{
				SPSR |= SPI2X;
				SPCR &= ~SPR0;
				SPCR |= SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_64)
			{
				SPSR &= ~SPI2X;
				SPCR &= ~SPR0;
				SPCR |= SPR1;
			}
			else if(pstr_SPI_Confg->SPI_Prescaler == SPI_PRESCALER_128)
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
		case (SPI_SLAVE):
			/* Set SPI module in Slave mode */
			SPCR &= ~MSTR;

			/* Initialize SCK as INPUT */
			str_Dio_SCK_s.GPIO = GPIOB;
			str_Dio_SCK_s.dir = INPUT;
			str_Dio_SCK_s.pins = PIN5;
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
			*u8_Data = 1U;
		}
		else

		{
			/* SPI flag not triggered */
			*u8_Data = 0U;
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

/**
 * @brief Blocking transmit a certain amount of data to a register over SPI
 * @param address
 * @param data
 * @param size
 */
void SPI_memTransmit(uint8 address, uint8 *data, uint16 size)
{
	/* Transmit address */
	SPDR = address;
	/* Wait until transmit is complete */
    while(! (SPSR & SPIF));
	uint16 i = 0;
	for(i=size;i>0;i--)
	{
		/* Transmit address */
        SPDR = data[i-1];
        /* Wait until transmit is complete */
        while(! (SPSR & SPIF));
	}
}

ISR(SPI_STC_vect)
{
	/* Call the callback function */
	SPI_CBK_Ptr();
}
