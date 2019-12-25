/*
 * externalInterrupt.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed
 */

#include "externalInterrupt.h"

/************************************************************************/
/*				 DEFINES			        							*/
/************************************************************************/
#define NOT_INITIALIZED		0
#define INITIALIZED			1

#define MAX_Int_CHANNELS	3

/************************************************************************/
/*				 GLOBAL STATIC VARIABLES			        			*/
/************************************************************************/

static uint8 gsau8_initState[MAX_Int_CHANNELS] = {NOT_INITIALIZED, NOT_INITIALIZED, NOT_INITIALIZED};

/**
 * Input: Pointer to callback function.
 * Output:
 * In/Out:
 * Return: void
 * Description: Calls the callback function.
 */
static void (*ExtInt_CBK_Ptr[MAX_Int_CHANNELS])(void) = {NULL};

/*
 * Function: ExternInt_Init
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to structure that contain the initialized data.
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Initiate the required external interrupt configuration as it specify
 *	event of interrupt.
 *	Enable the required external interrupt from GICR but to allow the interrupt global interrupt must be set
 */
ERROR_STATUS ExternInt_Init(ExternInt_Cfg_s *ExternIntCfg)
{
	if(NULL != ExternIntCfg)
	{
		switch(ExternIntCfg->ExternInt_No)
		{
		case (EXTRN_INT_0):
			/* Pass pointer to callback function */
			if(NULL != ExternIntCfg->ExternInt_CBF_Ptr)
			{
				ExtInt_CBK_Ptr[ExternIntCfg->ExternInt_No] = ExternIntCfg->ExternInt_CBF_Ptr;
			}
			else
			{
				return E_NOK;
			}
			/* Set INT0 pin as digital Input */
			DIO_Cfg_s ST_Int0_dio;
			ST_Int0_dio.GPIO = GPIOD;
			ST_Int0_dio.dir = INPUT;
			ST_Int0_dio.pins = PIN2;
			DIO_init(&ST_Int0_dio);
			if(ExternIntCfg->ExternInt_Event == LOW_LEVEL)
			{
				MCUCR &= ~(ISC01 | ISC00);
			}
			else if(ExternIntCfg->ExternInt_Event == LOGICAL_CHANGE)
			{
				MCUCR &= ~ISC01;
				MCUCR |= ISC00;
			}
			else if(ExternIntCfg->ExternInt_Event == FALLING_EDGE)
			{
				MCUCR |= ISC01;
				MCUCR &= ~ISC00;
			}
			else if(ExternIntCfg->ExternInt_Event == RISING_EDGE)
			{
				MCUCR |= (ISC01 | ISC00);
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternIntCfg->ExternInt_No] = INITIALIZED;
			break;
		case (EXTRN_INT_1):
			/* Pass pointer to callback function */
			if(NULL != ExternIntCfg->ExternInt_CBF_Ptr)
			{
				ExtInt_CBK_Ptr[ExternIntCfg->ExternInt_No] = ExternIntCfg->ExternInt_CBF_Ptr;
			}
			else
			{
				return E_NOK;
			}
			/* Set INT1 pin as digital Input */
			DIO_Cfg_s ST_Int1_dio;
			ST_Int1_dio.GPIO = GPIOD;
			ST_Int1_dio.dir = INPUT;
			ST_Int1_dio.pins = PIN3;
			DIO_init(&ST_Int1_dio);
			if(ExternIntCfg->ExternInt_Event == LOW_LEVEL)
			{
				MCUCR &= ~(ISC11 | ISC10);
			}
			else if(ExternIntCfg->ExternInt_Event == LOGICAL_CHANGE)
			{
				MCUCR &= ~ISC11;
				MCUCR |= ISC10;
			}
			else if(ExternIntCfg->ExternInt_Event == FALLING_EDGE)
			{
				MCUCR |= ISC11;
				MCUCR &= ~ISC10;
			}
			else if(ExternIntCfg->ExternInt_Event == RISING_EDGE)
			{
				MCUCR |= (ISC11 | ISC10);
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternIntCfg->ExternInt_No] = INITIALIZED;
			break;
		case (EXTRN_INT_2):
			/* Pass pointer to callback function */
			if(NULL != ExternIntCfg->ExternInt_CBF_Ptr)
			{
				ExtInt_CBK_Ptr[ExternIntCfg->ExternInt_No] = ExternIntCfg->ExternInt_CBF_Ptr;
			}
			else
			{
				return E_NOK;
			}
			/* Set INT2 pin as digital Input */
			DIO_Cfg_s ST_Int2_dio;
			ST_Int2_dio.GPIO = GPIOB;
			ST_Int2_dio.dir = INPUT;
			ST_Int2_dio.pins = PIN2;
			DIO_init(&ST_Int2_dio);
			if(ExternIntCfg->ExternInt_Event == FALLING_EDGE)
			{
				MCUCSR &= ~ISC2;
			}
			else if(ExternIntCfg->ExternInt_Event == RISING_EDGE)
			{
				MCUCSR |= ISC2;
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternIntCfg->ExternInt_No] = INITIALIZED;
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
 * Function: ExternInt_SetEvent
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * 	       InterruptEvent -> indicate required event for INT0 and INT1 there are 4 events to check (RISING_EDGE,FALLING_EDGE,LOW_LEVEL,LOGICAL_CHANGE).
							  But for Interrupt 2 there are only Two cases (Rising,Falling)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to set event of required external interrupt.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_SetEvent(uint8 ExternInt_No,uint8 InterruptEvent)
{
	switch(ExternInt_No)
	{
	case (EXTRN_INT_0):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			if(InterruptEvent == LOW_LEVEL)
			{
				MCUCR &= ~(ISC01 | ISC00);
			}
			else if(InterruptEvent == LOGICAL_CHANGE)
			{
				MCUCR &= ~ISC01;
				MCUCR |= ISC00;
			}
			else if(InterruptEvent == FALLING_EDGE)
			{
				MCUCR |= ISC01;
				MCUCR &= ~ISC00;
			}
			else if(InterruptEvent == RISING_EDGE)
			{
				MCUCR |= (ISC01 | ISC00);
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternInt_No] = INITIALIZED;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_1):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			if(InterruptEvent == LOW_LEVEL)
			{
				MCUCR &= ~(ISC11 | ISC10);
			}
			else if(InterruptEvent == LOGICAL_CHANGE)
			{
				MCUCR &= ~ISC11;
				MCUCR |= ISC10;
			}
			else if(InterruptEvent == FALLING_EDGE)
			{
				MCUCR |= ISC11;
				MCUCR &= ~ISC10;
			}
			else if(InterruptEvent == RISING_EDGE)
			{
				MCUCR |= (ISC11 | ISC10);
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternInt_No] = INITIALIZED;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_2):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			if(InterruptEvent == FALLING_EDGE)
			{
				MCUCSR &= ~ISC2;
			}
			else if(InterruptEvent == RISING_EDGE)
			{
				MCUCSR |= ISC2;
			}
			else
			{
				return E_NOK;
			}
			gsau8_initState[ExternInt_No] = INITIALIZED;
		}
		else
		{
			return E_NOK;
		}
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}


/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status)
{
	switch(ExternInt_No)
	{
	case (EXTRN_INT_0):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			*Status = GIFR & INTF0;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_1):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			*Status = GIFR & INTF1;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_2):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			*Status = GIFR & INTF2;
		}
		else
		{
			return E_NOK;
		}
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt.
 */
ERROR_STATUS ExternInt_Enable(uint8 ExternInt_No)
{
	switch(ExternInt_No)
	{
	case (EXTRN_INT_0):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR |= INT0;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_1):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR |= INT1;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_2):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR |= INT2;
		}
		else
		{
			return E_NOK;
		}
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

/*
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Disable the required external interrupt.
 */
ERROR_STATUS ExternInt_Disable(uint8 ExternInt_No)
{
	switch(ExternInt_No)
	{
	case (EXTRN_INT_0):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR &= ~INT0;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_1):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR &= ~INT1;
		}
		else
		{
			return E_NOK;
		}
		break;
	case (EXTRN_INT_2):
		if(gsau8_initState[ExternInt_No] == INITIALIZED)
		{
			GICR &= ~INT2;
		}
		else
		{
			return E_NOK;
		}
		break;
	default:
		return E_NOK;
		break;
	}
	return E_OK;
}

ISR(INT0_vect)
{
	ExtInt_CBK_Ptr[EXTRN_INT_0]();
}

ISR(INT1_vect)
{
	ExtInt_CBK_Ptr[EXTRN_INT_1]();
}

ISR(INT2_vect)
{
	ExtInt_CBK_Ptr[EXTRN_INT_2]();
}
