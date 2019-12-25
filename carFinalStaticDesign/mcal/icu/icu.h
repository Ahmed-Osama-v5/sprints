/*
 *      ICU.h
 *
 *      Created on: Dec 21, 2019
 *      Author: Wave 7
 *      Version: 1
 */

#ifndef _ICU_H_
#define _ICU_H_

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/

#include "std_types.h"
#include "Timer.h"
#include "interrupt.h"
#include "externalInterrupt.h"

/************************************************************************/
/*				               Constants                                */
/************************************************************************/
#define ICU_CH0 0			/* defines External Interrupt 0 */
#define ICU_CH1 1       	/* defines External Interrupt 1 */
#define ICU_CH2 2			/* defines External Interrupt 2 */

#define ICU_TIMER_CH0 0		/* defines Timer 0 */
#define ICU_TIMER_CH1 1		/* defines Timer 1 */
#define ICU_TIMER_CH2 2		/* defines Timer 2 */

/************************************************************************/
/*				               Structures                               */
/************************************************************************/
typedef struct Icu_cfg_s{
	uint8 ICU_Ch_No;		/* To choose the External Interrupt number */
	uint8 ICU_Ch_Timer;     /* To choose the Timer number */
}Icu_cfg_s;

/************************************************************************/
/*				          Functions' Prototypes                         */
/************************************************************************/

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
ERROR_STATUS Icu_Init(Icu_cfg_s * Icu_Cfg);

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
ERROR_STATUS Icu_RiseToFall(uint16 * Icu_Time);

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
ERROR_STATUS Icu_FallToRise(uint32 * Icu_Time);

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
ERROR_STATUS Icu_RiseToRise(uint32 * Icu_Time);

#endif /* _ICU_H_ */
