/*
 * sleep.h
 *
 *  Created on: Jan 13, 2020
 *      Author: Ahmed Osama
 */

#ifndef COMMON_SLEEP_SLEEP_H_
#define COMMON_SLEEP_SLEEP_H_

/*- INCLUDES -----------------------------------------------*/

/*- CONSTANTS ----------------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/
typedef enum
{
  IDLE, ADC_NOISE_REDUC, POWER_DOWN, POWER_SAVE, STANDBY, EXT_STANDBY
}E_SleepMode_t;

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/
/**
* @brief: CPU_Sleep provides six modes
* 	  IDLE, ADC_NOISE_REDUC, POWER_DOWN, POWER_SAVE, STANDBY, EXT_STANDBY
* 	  Note: STANDBY and EXT_STANDBY sleep modes are only available with
* 	  	external crystal/resonator fuse selection
* @param: E_SleepMode_t enum defines sleep modes
* Input : E_SleepMode_t
* Output: None
* @return: void
*/
void CPU_Sleep(E_SleepMode_t e_mode);


#endif /* COMMON_SLEEP_SLEEP_H_ */
