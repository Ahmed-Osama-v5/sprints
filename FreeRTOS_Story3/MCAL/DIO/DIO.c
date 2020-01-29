/*
 *	File name: DIO.c
 *	Author : Khalaf
 *	version: 1.2
 */

/************************************************************************/
/*						Files Includes	                                */
/************************************************************************/
#include "DIO.h"
/************************************************************************/
/*				 		Internal Types defines	                        */
/************************************************************************/

/************************************************************************/
/*						Internal Macros defines	                        */
/************************************************************************/

/************************************************************************/
/*				 		Variables defines	                            */
/************************************************************************/

/************************************************************************/
/*						Static Prototype                                */
/************************************************************************/

/************************************************************************/
/*				 		static functions defines                        */
/************************************************************************/

/************************************************************************/
/*				 		APIs defines	  	                            */
/************************************************************************/

/*
 *Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
 *Output: No output
 *In/Out:
 *Description: This function can set the direction of a full port, a nibble
 * 			  or even one pin.
 */
ERROR_STATUS DIO_init(DIO_Cfg_s *DIO_info)
{
	/*
	 * Error state: No Error
	 */
	ERROR_STATUS s8_ErrorStatus = DIO_BASE_ERROR + ERR_SUCCESS;

	if (DIO_info == NULL)
	{
		/*
		 * trying to access a null pointer
		 */
		s8_ErrorStatus = DIO_BASE_ERROR + ERR_NULL_PTR;
	}
	/*
	 * 	check Direction
	 */
	else if (DIO_info->dir == INPUT || DIO_info->dir == OUTPUT)
	{
		/*
		 * Check on the Required PORT Number
		 */
		switch (DIO_info->GPIO)
		{
		case GPIOA:
			ASSIGN_BIT(PORTA_DIR, DIO_info->pins, DIO_info->dir);
			break;
		case GPIOB:
			ASSIGN_BIT(PORTB_DIR, DIO_info->pins, DIO_info->dir);
			break;
		case GPIOC:
			ASSIGN_BIT(PORTC_DIR, DIO_info->pins, DIO_info->dir);
			break;
		case GPIOD:
			ASSIGN_BIT(PORTD_DIR, DIO_info->pins, DIO_info->dir);
			break;
		default:
			/*
			 *  Wrong Port Number
			 */
			s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
			break;
		}
	}
	else
	{
		/*
		 *  Wrong Direction
		 */
		s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
	}
	/*
	 * Function shall return the Error state
	 */
	return s8_ErrorStatus;
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
ERROR_STATUS DIO_Write(uint8 GPIO, uint8 pins, uint8 value)
{
	/*
	 * Error state: No Error
	 */
	ERROR_STATUS s8_ErrorStatus = DIO_BASE_ERROR + ERR_SUCCESS;
	/*
	 * 	check Value
	 */
	if (value == HIGH || value == LOW)
	{
		/*
		 * Check on the Required PORT Number
		 */
		switch (GPIO)
		{
		case GPIOA:
			ASSIGN_BIT(PORTA_DATA, pins, value);
			break;
		case GPIOB:
			ASSIGN_BIT(PORTB_DATA, pins, value);
			break;
		case GPIOC:
			ASSIGN_BIT(PORTC_DATA, pins, value);
			break;
		case GPIOD:
			ASSIGN_BIT(PORTD_DATA, pins, value);
			break;
		default:
			/*
			 *  Wrong Port Number
			 */
			s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
			break;
		}
	}
	else
	{
		/*
		 *  Wrong Direction
		 */
		s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
	}
	/*
	 * Function shall return the Error state
	 */
	return s8_ErrorStatus;
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
ERROR_STATUS DIO_Read(uint8 GPIO, uint8 pins, uint8 *data)
{
	/*
	 * Error state: No Error
	 */
	ERROR_STATUS s8_ErrorStatus = DIO_BASE_ERROR + ERR_SUCCESS;

	if (data == NULL)
	{
		/*
		 * trying to access a null pointer
		 */
		s8_ErrorStatus = DIO_BASE_ERROR + ERR_NULL_PTR;
	}
	else
	{
		/*
		 * Check on the Required PORT Number
		 */
		switch (GPIO)
		{
		case GPIOA:
			*data = (PORTA_PIN & pins);
			break;
		case GPIOB:
			*data = (PORTB_PIN & pins);
			break;
		case GPIOC:
			*data = (PORTC_PIN & pins);
			break;
		case GPIOD:
			*data = (PORTD_PIN & pins);
			break;
		default:
			/*
			 *  Wrong Port Number
			 */
			s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
			break;
		}
	}
	/*
	 * Function shall return the Error state
	 */
	return s8_ErrorStatus;
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
ERROR_STATUS DIO_Toggle(uint8 GPIO, uint8 pins)
{
	/*
	 * Error state: No Error
	 */
	ERROR_STATUS s8_ErrorStatus = DIO_BASE_ERROR + ERR_SUCCESS;

	/*
	 * Check on the Required PORT Number
	 */
	switch (GPIO)
	{
	case GPIOA:
		PORTA_DATA ^= (pins);
		break;
	case GPIOB:
		PORTB_DATA ^= (pins);
		break;
	case GPIOC:
		PORTC_DATA ^= (pins);
		break;
	case GPIOD:
		PORTD_DATA ^= (pins);
		break;
	default:
		/*
		 *  Wrong Port Number
		 */
		s8_ErrorStatus = DIO_BASE_ERROR + ERR_INVALID_ARGU;
		break;
	}
	/*
	 * Function shall return the Error state
	 */
	return s8_ErrorStatus;
}

