/*
 * tmu.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_TMU_TMU_H_
#define SERVICE_TMU_TMU_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "tmu_cfg.h"
#include "tmu_lcfg.h"

/*- CONSTANTS ----------------------------------------------*/

/*- PRIMITIVE TYPES ----------------------------------------*/

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
* @brief: TMU Initialization
* @param:
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Init(void);

/**
* @brief: TMU DeInitialization
* @param:
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_DeInit(void);

/**
* @brief: TMU Start
* @param:
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Start(void);

/**
* @brief: TMU Stop
* @param:
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Stop(void);

/**
* @brief: TMU Loops through task list and service each one as requested
* @param:
* Input : void
* Output: None
* @return: ERROR_STATUS ( E_OK if every thing is OK, E_NOK otherwise )
*/
ERROR_STATUS Tmu_Dispatch(void);

#endif /* SERVICE_TMU_TMU_H_ */
