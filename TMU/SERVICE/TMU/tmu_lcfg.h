/*
 * tmu_lcfg.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_TMU_TMU_LCFG_H_
#define SERVICE_TMU_TMU_LCFG_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "timer.h"

/*- CONSTANTS ----------------------------------------------*/
/* Define timer channels to be used with Tmu */
/* Uncomment the  one you want to use and comment the other two */
#define TMU_TIMER_CH0
/* #define TMU_TIMER_CH1 */
/* #define TMU_TIMER_CH2 */

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
  /* Hardware timer to be used i.e TIMER_CH0, TIMER_CH1, or TIMER_CH2 */
  uint8 timerCh;
  /* Base resolution in milliseconds */
  uint8 timerResolution;
}gstrTMUConfig_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif /* SERVICE_TMU_TMU_LCFG_H_ */
