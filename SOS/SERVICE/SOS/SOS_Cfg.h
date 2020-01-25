/*
 * tmu_cfg.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_SOS_SOS_CFG_H_
#define SERVICE_SOS_SOS_CFG_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"

/*- CONSTANTS ----------------------------------------------*/
#define   MAX_TASK_COUNT   (30)

/* Define timer channels to be used with TMU */
/* Uncomment the  one you want to use and comment the other two */
#define TMU_TIMER_CH0
/* #define TMU_TIMER_CH1 */
/* #define TMU_TIMER_CH2 */

/* TMU timer resolution in milliSeconds */
/* Range: 1 mS to 65535 mS */
/* TODO: Test the whole range */
#define SOS_SYSTEM_TICK_RESOLUTION		(1)

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

#endif /* SERVICE_SOS_SOS_CFG_H_ */
