/*
 * dio.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed
 */
#include "dio.h"

/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	if(NULL != DIO_info)
	{
		switch (DIO_info->GPIO)
		{
#if defined(_ATMEGA16_) || defined(_ATMEGA32_)
		case (GPIOA):
			if(DIO_info->dir == OUTPUT)
			{
				PORTA_DIR |= DIO_info->pins;
			}
			else
			{
				PORTA_DIR &= ~DIO_info->pins;
			}
			break;
#endif
		case (GPIOB):
			if(DIO_info->dir == OUTPUT)
			{
				PORTB_DIR |= DIO_info->pins;
			}
			else
			{
				PORTB_DIR &= ~DIO_info->pins;
			}
			break;
		case (GPIOC):
			if(DIO_info->dir == OUTPUT)
			{
				PORTC_DIR |= DIO_info->pins;
			}
			else
			{
				PORTC_DIR &= ~DIO_info->pins;
			}
			break;
		case (GPIOD):
			if(DIO_info->dir == OUTPUT)
			{
				PORTD_DIR |= DIO_info->pins;
			}
			else
			{
				PORTD_DIR &= ~DIO_info->pins;
			}
			break;
		default:
			return E_NOK;
			break;
		}
	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}


/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value 	-> The desired value
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value)
{
	switch(GPIO)
	{
#if defined(_ATMEGA16_) || defined(_ATMEGA32_)
	case (GPIOA):
		if(value)
		{
			PORTA_DATA |= pins;
		}
		else
		{
			PORTA_DATA &= ~pins;
		}
		break;
#endif
	case (GPIOB):
		if(value)
		{
			PORTB_DATA |= pins;
		}
		else
		{
			PORTB_DATA &= ~pins;
		}
		break;
	case (GPIOC):
		if(value)
		{
			PORTC_DATA |= pins;
		}
		else
		{
			PORTC_DATA &= ~pins;
		}
		break;
	case (GPIOD):
		if(value)
		{
			PORTD_DATA |= pins;
		}
		else
		{
			PORTD_DATA &= ~pins;
		}
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8 GPIO,uint8 pins, uint8 *data)
{
	switch(GPIO)
	{
#if defined(_ATMEGA16_) || defined(_ATMEGA32_)
	case (GPIOA):
		*data = (PORTA_PIN & pins);
		break;
#endif
	case (GPIOB):
		*data = (PORTB_PIN & pins);
		break;
	case (GPIOC):
		*data = (PORTC_PIN & pins);
		break;
	case (GPIOD):
		*data = (PORTD_PIN & pins);
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8 GPIO, uint8 pins)
{
	switch(GPIO)
	{
#if defined(_ATMEGA16_) || defined(_ATMEGA32_)
	case (GPIOA):
		PORTA_DATA ^= pins;
		break;
#endif
	case (GPIOB):
		PORTB_DATA ^= pins;
		break;
	case (GPIOC):
		PORTC_DATA ^= pins;
		break;
	case (GPIOD):
		PORTD_DATA ^= pins;
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}
