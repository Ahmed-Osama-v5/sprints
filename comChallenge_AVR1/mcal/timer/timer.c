/*
 * timer.c
 *
 *  Created on: Dec 22, 2019
 *      Author: Ahmed
 */

/************************************************************************/
/*				 INCLUDES			        							*/
/************************************************************************/

#include "timer.h"

/************************************************************************/
/*				 DEFINES			        							*/
/************************************************************************/
#define NOT_INITIALIZED		0
#define INITIALIZED			1

#define MAX_TIMER_CHANNELS	3

/************************************************************************/
/*				 GLOBAL STATIC VARIABLES			        			*/
/************************************************************************/

static uint8 gsau8_mode[MAX_TIMER_CHANNELS] = {TIMER_MODE, TIMER_MODE, TIMER_MODE};
static uint8 gsau8_preScaler[MAX_TIMER_CHANNELS] = {TIMER_NO_CLOCK, TIMER_NO_CLOCK, TIMER_NO_CLOCK};
static uint8 gsau8_initState[MAX_TIMER_CHANNELS] = {NOT_INITIALIZED, NOT_INITIALIZED, NOT_INITIALIZED};

/**
 * Input: Pointer to callback function.
 * Output:
 * In/Out:
 * Return: void
 * Description: Calls the callback function.
 */
static void (*Timer_OVF_CBK_Ptr[MAX_TIMER_CHANNELS])(void) = {NULL};


/**
 * Input: Pointer to a structure contains the information needed to initialize the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Initiates the module.
 */
ERROR_STATUS Timer_Init(Timer_cfg_s* Timer_cfg)
{
	if(NULL != Timer_cfg)
	{
		gsau8_preScaler[Timer_cfg->Timer_CH_NO] = Timer_cfg->Timer_Prescaler;
		/* Pass pointer to callback function */
		if(NULL != Timer_cfg->CBK_Ptr)
		{
			Timer_OVF_CBK_Ptr[Timer_cfg->Timer_CH_NO] = Timer_cfg->CBK_Ptr;
		}
		else
		{
			return E_NOK;
		}
		switch(Timer_cfg->Timer_Mode)
		{
		case(TIMER_MODE):
			switch(Timer_cfg->Timer_CH_NO)
			{
			case (TIMER_CH0):
				/* Normal mode */
				TCCR0 &= ~(WGM01 | WGM00);

				if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_INTERRUPT_MODE)
				{
					TIMSK |= TOIE0;
				}
				else
				{
					TIMSK &= ~TOIE0;
				}
				break;
			case (TIMER_CH1):
				/* Normal mode */
				TCCR1A &= ~(WGM11 | WGM10);
				TCCR1B &= ~(WGM13 | WGM12);
				if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_POLLING_MODE)
				{
					TIMSK &= ~TOIE1;
				}
				else
				{
					TIMSK |= TOIE1;
				}
				break;
			case (TIMER_CH2):
				/* Normal mode */
				TCCR2 &= ~(WGM21 | WGM20);
				if(Timer_cfg->Timer_Polling_Or_Interrupt == TIMER_POLLING_MODE)
				{
					TIMSK &= ~TOIE2;
				}
				else
				{
					TIMSK |= TOIE2;
				}
				break;
			default:
				return E_NOK;
				break;
			}
			gsau8_mode[Timer_cfg->Timer_CH_NO] = TIMER_MODE;
			break;
		case(COUNTER_UP_MODE):
			gsau8_mode[Timer_cfg->Timer_CH_NO] = COUNTER_UP_MODE;
			break;
		case(COUNTER_DOWN_MODE):
			gsau8_mode[Timer_cfg->Timer_CH_NO] = COUNTER_DOWN_MODE;
			break;
		default:
			return E_NOK;
			break;
		}
		gsau8_initState[Timer_cfg->Timer_CH_NO] = INITIALIZED;
		return E_OK;
	}
	else
	{
		return E_NOK;
	}
}

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be started.
 *	Timer_Count: The start value of the timer.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function starts the needed timer.
 *
 */
ERROR_STATUS Timer_Start(uint8 Timer_CH_NO, uint16 Timer_Count)
{
	switch(Timer_CH_NO)
	{
	case(TIMER_CH0):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			//TCNT0 = (0xFF - (uint8)Timer_Count); /* pre-load timer */
			TCNT0 = (uint8)Timer_Count; /* pre-load timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set prescaler */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
					TCCR0 &= ~(CS02 | CS01);
					TCCR0 |= CS00;
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
					TCCR0 &= ~(CS02 | CS00);
					TCCR0 |= CS01;
					break;
				case (TIMER_PRESCALER_64):
					/* 3 */
					TCCR0 &= ~CS02;
					TCCR0 |= (CS01 | CS00);
					break;
				case (TIMER_PRESCALER_256):
					/* 4 */
					TCCR0 &= ~(CS01 | CS00);
					TCCR0 |= CS02;
					break;
				case (TIMER_PRESCALER_1024):
					/* 5 */
					TCCR0 &= ~CS01;
					TCCR0 |= (CS02 | CS00);
					break;
				default:
					return E_NOK;
					break;
				}
			break;
			case (COUNTER_UP_MODE):
				/* 7 */
				TCCR0 |= (CS02 | CS01 | CS00);
				break;
			case (COUNTER_DOWN_MODE):
				/* 6 */
				TCCR0 |= (CS02 | CS01);
				TCCR0 &= ~CS00;
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
		break;
	case(TIMER_CH1):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCNT1 = (0xFFFF - Timer_Count); /* pre-load timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set prescaler */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
					TCCR1B &= ~(CS12 | CS11);
					TCCR1B |= CS10;
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
					TCCR1B &= ~(CS12 | CS10);
					TCCR1B |= CS11;
					break;
				case (TIMER_PRESCALER_64):
					/* 3 */
					TCCR1B &= ~CS12;
					TCCR1B |= (CS11 | CS10);
					break;
				case (TIMER_PRESCALER_256):
					/* 4 */
					TCCR1B &= ~(CS11 | CS10);
					TCCR1B |= CS12;
					break;
				case (TIMER_PRESCALER_1024):
					/* 5 */
					TCCR1B &= ~CS11;
					TCCR1B |= (CS12 | CS10);
					break;
					default:
						return E_NOK;
						break;
				}
				break;
			case(COUNTER_UP_MODE):
				/* 7 */
				TCCR1B |= (CS12 | CS11 | CS10);
				break;
			case(COUNTER_DOWN_MODE):
				/* 6 */
				TCCR1B |= (CS12 | CS11);
				TCCR1B &= ~CS10;
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
		break;
	case(TIMER_CH2):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCNT2 = (0xFF - (uint8)Timer_Count); /* pre-load timer */
			switch (gsau8_mode[Timer_CH_NO])
			{
			case (TIMER_MODE):
				/* set prescaler */
				switch (gsau8_preScaler[Timer_CH_NO])
				{
				case (TIMER_PRESCALER_NO):
					/* 1 */
					TCCR2 &= ~(CS22 | CS21);
					TCCR2 |= CS20;
					break;
				case (TIMER_PRESCALER_8):
					/* 2 */
					TCCR2 &= ~(CS22 | CS20);
					TCCR2 |= CS21;
					break;
				case (TIMER_PRESCALER_32):
					/* 3 */
					TCCR2 &= ~CS22;
					TCCR2 |= (CS21 | CS20);
					break;
				case (TIMER_PRESCALER_64):
					/* 4 */
					TCCR2 &= ~(CS21 | CS20);
					TCCR2 |= CS22;
					break;
				case (TIMER_PRESCALER_128):
					/* 5 */
					TCCR2 &= ~CS21;
					TCCR2 |= (CS22 | CS20);
					break;
				case (TIMER_PRESCALER_256):
					/* 6 */
					TCCR2 &= ~CS20;
					TCCR2 |= (CS22 | CS21);
					break;
				case (TIMER_PRESCALER_1024):
					/* 7 */
					TCCR2 |= (CS22 | CS21 | CS20);
					break;
				default:
					return E_NOK;
					break;
				}
				break;
			case(COUNTER_UP_MODE):
				/* Implement your algorithm */
				break;
			case(COUNTER_DOWN_MODE):
				/* Implement your algorithm */
				break;
			default:
				return E_NOK;
			}
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

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to be stopped.
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: This function stops the needed timer.
 *
 */
ERROR_STATUS Timer_Stop(uint8 Timer_CH_NO)
{
	switch(Timer_CH_NO)
	{
	case(TIMER_CH0):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCCR0 &= ~(CS02 | CS01 | CS00);
		}
		else
		{
			return E_NOK;
		}
		break;
	case(TIMER_CH1):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCCR1B &= ~(CS12 | CS11 | CS10);
		}
		else
		{
			return E_NOK;
		}
		break;
	case(TIMER_CH2):
		if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
		{
			TCCR2 &= ~(CS22 | CS21 | CS20);
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

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its status.
 * Output:
 * 	Data: A variable of type bool returns if the flag of the timer is raised or not.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return if the flag of the timer is raised or not.
 *
 */
ERROR_STATUS Timer_GetStatus(uint8 Timer_CH_NO, bool* Data)
{
	if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
	{
		*Data = 0;
		switch (Timer_CH_NO) {
		case (TIMER_CH0):
			if(TIFR & TOV0)
			{
				*Data = 1;
			}
			else
			{
				*Data = 0;
			}
			break;
		case (TIMER_CH1):
			if(TIFR & TOV1)
			{
				*Data = 1;
			}
			else
			{
				*Data = 0;
			}
			break;
		case (TIMER_CH2):
			if(TIFR & TOV2)
			{
				*Data = 1;
			}
			else
			{
				*Data = 0;
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

/**
 * Input:
 * 	Timer_CH_NO: The channel number of the timer needed to get its value.
 * Output:
 * 	Data: This is the output variable of the function which holds the value of the timer.
 * In/Out:
 * Return: The error status of the function.
 * Description: This function is used to return the value of the timer.
 *
 */
ERROR_STATUS Timer_GetValue(uint8 Timer_CH_NO, uint16* Data)
{
	if(gsau8_initState[Timer_CH_NO] == INITIALIZED)
	{
		*Data = 0;
		switch (Timer_CH_NO)
		{
		case (TIMER_CH0):
			*Data = TCNT0;
			break;
		case (TIMER_CH1):
			*Data = TCNT1;
			break;
		case (TIMER_CH2):
			*Data = TCNT2;
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

ISR(TIMER0_OVF_vect)
{
	Timer_OVF_CBK_Ptr[0]();
}

ISR(TIMER1_OVF_vect)
{
	Timer_OVF_CBK_Ptr[1]();
}

ISR(TIMER2_OVF_vect)
{
	Timer_OVF_CBK_Ptr[2]();
}
