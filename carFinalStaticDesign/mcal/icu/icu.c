/*
 * icu.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed
 */

#include "icu.h"

#define MAX_ICU_CHANNELS	3


static uint16 gu16_uSeconds = 0; /* Holds count of uSeconds */
static uint8 gu8_extInt_Edge_Flag = 0;
static uint8 gu8_OVFs = 0;

/**************************************************************************
 * Function 	: count_us_CBK_Func                                       *
 * Input 		: void											          *
 * Return 		: void													  *
 * Description  : Counts uSeconds and stores them in a global variable    *
 **************************************************************************/
static void count_us_CBK_Func(void)
{
	//DIO_Toggle(GPIOC, PIN1); /* Debug LED */
	gu8_OVFs++;
}

/**************************************************************************
 * Function 	: extInt_CBK_Func                                         *
 * Input 		: void											          *
 * Return 		: void													  *
 * Description  : Starts and stops timer							      *
 **************************************************************************/
static void extInt_CBK_Func(void)
{
	//DIO_Toggle(GPIOC, PIN0); /* Debug LED */
	if(gu8_extInt_Edge_Flag == 1)
	{
		Timer_Start(TIMER_CH0, 0); /* Start the timer to count from 0 */
		ExternInt_SetEvent(EXTRN_INT_2, FALLING_EDGE);
		gu8_extInt_Edge_Flag = 0;
	}
	else
	{
		Timer_Stop(TIMER_CH0);
		if(Timer_GetValue(TIMER_CH0, &gu16_uSeconds) == E_OK)
		{
			gu16_uSeconds += (gu8_OVFs * 256);
			gu8_OVFs = 0;
			ExternInt_SetEvent(EXTRN_INT_2, RISING_EDGE);
			gu8_extInt_Edge_Flag = 1;
		}
		else
		{

		}
	}
}


/**************************************************************************
 * Function 	: Icu_Init                                                *
 * Input 		: Icu_cfg : pointer to structure of type Icu_cfg_s        *
 * Return 		: value of type ERROR_STATUS							  *
 * 				  which is one of the following values:					  *
 * 				  - E_OK  : initialized successfully					  *
 *				  - E_NOK : not initialized successfully				  *
 * Description  : Initializes the ICU by initializing the timer			  *
 * 				  and enabling the global interrupt						  *
 **************************************************************************/
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg)
{
	if(NULL != Icu_Cfg)
	{
		bool dummyFlag = 0; /* Just to check if timer is initialized or not */
		switch(Icu_Cfg->ICU_Ch_Timer)
		{
		case (ICU_TIMER_CH0):
			if(Timer_GetStatus(TIMER_CH0, &dummyFlag) == E_NOK)
			{
				Timer_cfg_s ST_Timer0 = {0};
				ST_Timer0.Timer_CH_NO = TIMER_CH0;
				ST_Timer0.Timer_Mode = TIMER_MODE;
				ST_Timer0.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
				ST_Timer0.Timer_Prescaler = TIMER_PRESCALER_1024;
				ST_Timer0.CBK_Ptr = count_us_CBK_Func;
				if(Timer_Init(&ST_Timer0) == E_OK)
				{
					if(Icu_Cfg->ICU_Ch_No == ICU_CH2)
					{
						ExternInt_Cfg_s ST_ExtInt2 = {0};
						ST_ExtInt2.ExternInt_No = EXTRN_INT_2;
						ST_ExtInt2.ExternInt_Event = RISING_EDGE;
						ST_ExtInt2.ExternInt_CBF_Ptr = extInt_CBK_Func;
						ExternInt_Init(&ST_ExtInt2);
						/* Enable INT0 */
						ExternInt_Enable(ST_ExtInt2.ExternInt_No);
					}
				}
				else
				{
					return E_NOK;
				}
			}
			else
			{
				return E_NOK;
			}
			break;
		case (ICU_TIMER_CH1):
			break;
		case (ICU_TIMER_CH2):
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

/***************************************************************************
 * Function		: Icu_RiseToFall										   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from rising edge to falling edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK  : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between the rising and the falling   *
 * 				  edges												 	   *
 ***************************************************************************/
ERROR_STATUS Icu_RiseToFall(uint16 * Icu_Time)
{
	*Icu_Time = gu16_uSeconds;
	return E_OK;
}

/***************************************************************************
 * Function		: Icu_FallToRise										   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from falling edge to rising edge						   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between the falling and the rising   *
 * 				  edges													   *
 ***************************************************************************/
ERROR_STATUS Icu_FallToRise(uint32 * Icu_Time)
{
	return E_OK;
}

/***************************************************************************
 * Function		: Icu_RiseToRise										   *
 * Output 		: Icu_Time : pointer to uint32 variable to give the time   *
 * 				  from rising edge to next rising edge					   *
 * Return 		: value of type ERROR_STATUS							   *
 * 				  which is one of the following values:					   *
 * 				  - E_OK : successful									   *
 *				  - E_NOK : not successful								   *
 * Description	: calculates the time between the rising edge and the next *
 * 				  rising edge											   *
 ***************************************************************************/
ERROR_STATUS Icu_RiseToRise(uint32 * Icu_Time)
{
	return E_OK;
}
