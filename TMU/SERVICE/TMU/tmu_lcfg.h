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

/*- CONSTANTS ----------------------------------------------*/
/* Define timer channels to be used with Tmu */
#define TMU_TIMER_CH0   (0)
#define TMU_TIMER_CH1   (1)
#define TMU_TIMER_CH2   (2)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
  /* Hardware timer to be used i.e TMR0, TMR1, or TMR2 */
  uint8 timerCh;
  /* Base resolution in milliseconds */
  uint8 timerResolution;
}StrTmuConfig_t;

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif /* SERVICE_TMU_TMU_LCFG_H_ */
