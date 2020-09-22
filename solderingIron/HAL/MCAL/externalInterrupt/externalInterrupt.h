#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

/*
 * file: externalInterrupt.h
 * Author: Hassan and Ghanem.
 * Modified by: Ahmed Osama
 * version: 1.0.5
 * Last modified: Jul 11, 2020
 */

/************************************************************************/
/*				 		      INCLUDES                                  */
/************************************************************************/
#include "std_types.h"
#include "mega8.h"
#include "interrupt.h"
#include "dio.h"

/************************************************************************/
/*				 		       Defines                                  */
/************************************************************************/

#define EXTRN_INT_0    0
#define EXTRN_INT_1    1
#if defined(_ATMEGA16_) || defined(_ATMEGA32_)
#define EXTRN_INT_2    2
#endif
/* NOTE:
 * for INT 0 set the event directly
 * but for INT 1 shift the value by 2
 * SET_BIT(MCUCR,EVENT<<(2*INT_INDEX))
 */

#define LOW_LEVEL      0
#define LOGICAL_CHANGE 1
#define FALLING_EDGE   2
#define RISING_EDGE    3

/************************************************************************/
/*				 		           Types                                */
/************************************************************************/

typedef struct ExternInt_Cfg_s{

	uint8 ExternInt_No; //INT0, INT1,INT2
	uint8 ExternInt_Event; //RISING, FALLING,...
	void (*ExternInt_CBF_Ptr)(void); // call back function to be executed at ISR.
}ExternInt_Cfg_s;

/************************************************************************/
/*				 		Functions ProtoTypes                            */
/************************************************************************/

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
void ExternInt_Init(ExternInt_Cfg_s *ExternIntCfg);

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
void ExternInt_SetEvent(uint8 ExternInt_No,uint8 InterruptEvent);


/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status. 
 * 				note: usually used to poll on the flag.
 */
void ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status);

/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt.
 */
void ExternInt_Enable(uint8 ExternInt_No);

/*
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Disable the required external interrupt.
 */
void ExternInt_Disable(uint8 ExternInt_No);


#endif /*EXTERNAL_INTERRUPT_H_*/
