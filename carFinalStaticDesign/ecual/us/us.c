/*
 * us.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Ahmed
 */

#include "us.h"
#include "icu.h"
#include "dio.h"
#include "softwareDelay.h"

/****************************************************************************************************
 * Function Name   : Us_Init.                                                                       *
 * Input Parameters : None.                                                                         *                                                                   *                                                                                                *
 * Output Parameters: None.                                                                         *
 * In_Out Parameters: None.                                                                         *
 * Return           : ERROR_STATUS.                                                                 *
 * Description      : This function initiate the UltraSonic by set the value of the Dio_Dirction of *
 *                    the pin trigger as an output then initiate the ICU to use it to calculate the *
 *                    On time of the ECHO signal.                                                   *
 *                                                                                                  *
 *                                                                                                  *
 ***************************************************************************************************/



ERROR_STATUS Us_Init(void)
{
	DIO_Cfg_s str_Dio;
	str_Dio.GPIO = GPIOB;
	str_Dio.dir = OUTPUT;
	str_Dio.pins = PIN3;
	DIO_init(&str_Dio);

	Icu_cfg_s str_Icu = {0};
	str_Icu.ICU_Ch_No = ICU_CH2;
	str_Icu.ICU_Ch_Timer = ICU_TIMER_CH0;
	if(Icu_Init(&str_Icu) == E_OK)
	{

	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}




/**************************************************************************************************
 * Function Name    : Us_Trigger.                                                                 *
 * Input Parameters : None.                                                                       *                                                                              *                                                                                                *
 * Output Parameters: None.                                                                       *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS                                                                *
 * Description      : This function send the  pulse, to trigger pin of the UltraSonic to enhance  *
 *                    the  ECUO signal                                                            *
 *************************************************************************************************/


ERROR_STATUS Us_Trigger(void)
{
	/* Trigger pulse */
	DIO_Write(GPIOB, PIN3, HIGH);
	SwDelay_us(20);
	DIO_Write(GPIOB, PIN3, LOW);
	return E_OK;
}





/**************************************************************************************************
 * Function Name    : Us_GetDistance.                                                             *
 * Input Parameters : pointer to uint16 that will return the distance on it.                      *                                                                                              *                                                                                                *
 * Output Parameters: Distance.                                                                   *
 * In_Out Parameters: None.                                                                       *
 * Return           : ERROR_STATUS.                                                               *
 * Description      : This function get the time of high signal of ECUO pulse, then               *
 *                    use it to calculate the distance, then return the value in the              *
 *                    Distance parameter.                                                         *
 *************************************************************************************************/


ERROR_STATUS Us_GetDistance(uint16 *Distance)
{
	if(Icu_RiseToFall(Distance) == E_OK)
	{

	}
	else
	{
		return E_NOK;
	}
	return E_OK;
}
