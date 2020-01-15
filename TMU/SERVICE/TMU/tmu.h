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
#include "system_ErrorHandling.h"
#include "retval.h"
#include "timer.h"

/*- CONSTANTS ----------------------------------------------*/
#define DELAY_NOT_COMPLETE	(0)
#define DELAY_COMPLETE	        (1)

#define PERIODIC		(0)
#define ONE_SHOT		(1)

/* TMU timer resolution in milliSeconds */
/* Range: 1 mS to 65535 mS */
#define TMU_RESOLUTION		(1)

/*- PRIMITIVE TYPES ----------------------------------------*/
/* User callback function typedef */
typedef void (*gptrTMU_DelayCompleteFun_User_CBK) (void);

/* Delay typedef */
typedef	uint16 u16_Delay_t;

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
/* TODO: Add Periodicity as a member */
/* Task block struct which has pointer to the callback */
typedef struct
{
  gptrTMU_DelayCompleteFun_User_CBK ptrTMU_DelayComplete_UserFunc_CBK;
  u16_Delay_t u16_Delay;
  u16_Delay_t u16_MilliSecond_Count;
  uint8 u8_Periodicity;
}strTMU_TCB_t;

/* Create array of instances of strTMU_TCB_t */
strTMU_TCB_t gstrTMU_TCB_s[MAX_TASK_COUNT];

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
* @brief: TMU Initialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Init(void);

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_DeInit(void);

/**
* @brief: Appends Task block elements to the TCB array
* @param: ptrFun_User_CBK: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Start(gptrTMU_DelayCompleteFun_User_CBK ptrFun_User_CBK, u16_Delay_t u16_Delay, uint8 u8_Periodicity);

/**
* @brief: TMU Stop
* @param: ptrFun_User_CBK: pointer to callback function
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Stop(gptrTMU_DelayCompleteFun_User_CBK ptrFun_User_CBK);

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_Dispatcher(void);

#endif /* SERVICE_TMU_TMU_H_ */
