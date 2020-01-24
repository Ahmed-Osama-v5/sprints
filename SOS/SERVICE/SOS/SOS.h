/*
 * tmu.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

#ifndef SERVICE_SOS_SOS_H_
#define SERVICE_SOS_SOS_H_

/*- INCLUDES -----------------------------------------------*/
#include "std_types.h"
#include "system_ErrorHandling.h"
#include "retval.h"
#include "timer.h"
#include "SOS_Cfg.h"

/*- CONSTANTS ----------------------------------------------*/
#define DELAY_NOT_COMPLETE				(0)
#define DELAY_COMPLETE	        		(1)

/* SOSTask states */
#define WAITING_STATE	(0)
#define READY_STATE		(1)

/*- PRIMITIVE TYPES ----------------------------------------*/
/* User callback function typedef */
typedef void (*gptrSOSTask_t) (void);

/*- ENUMS --------------------------------------------------*/

/*- STRUCTS AND UNIONS -------------------------------------*/
/* Task block struct which has pointer to the callback */
typedef struct
{
	/* Pointer to task */
	gptrSOSTask_t ptrSOS_Task;

	/* Priority of task */
	uint8 u8_SOSTask_Priority;

	/* Task state */
	uint8 u8_SOSTask_State;

	/* Periodicity of task */
	uint16 u16_SOSTask_Periodicity;

	/* System_Tick counter */
	uint16 u16_SystemTick_Counter;
}strSOS_TCB_t;

/* Create array of instances of strSOS_TCB_t */
strSOS_TCB_t gstrSOS_TCB_s[MAX_TASK_COUNT];

/*- FUNCTION-LIKE MACROS -----------------------------------*/

/*- FUNCTION DECLARATIONS ----------------------------------*/

/**
* @brief: TMU Initialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_Init(void);

/**
* @brief: Appends Task block elements to the TCB array
* @param: ptrFun_User_CBK: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_CreateTask(strSOS_TCB_t* gstrSOS_TaskCB_s);

/**
* @brief: TMU Stop
* @param: ptrFun_User_CBK: pointer to callback function
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_DeleteTask(gptrSOSTask_t ptrFun_User_CBK);

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_Run(void);

#endif /* SERVICE_SOS_SOS_H_ */
