/*
 * tmu.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Ahmed Osama
 */

/*- INCLUDES ----------------------------------------------*/
#include "SOS.h"

/*- LOCAL MACROS ------------------------------------------*/
#define SYSTEM_TICK_NOT_TRIGGERED	(0)
#define SYSTEM_TICK_TRIGGERED		(1)

/*- LOCAL Data types --------------------------------------*/

/*- LOCAL FUNCTIONS PROTOTYPES ----------------------------*/
/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void SOS_System_TimerOvf_CBK(void);

/*- GLOBAL STATIC VARIABLES -------------------------------*/

/* Indicates system timer overflow has occurred or not */
static volatile uint8 gu8_SOS_SYSTEM_TimerOvf_Flag = SYSTEM_TICK_NOT_TRIGGERED;

/* OverFlow counter */
static volatile uint8 gu8_OvfCounter = 0;

/* Array elements count */
static uint8 gu8_ArrayElementCount = 0;

/*- GLOBAL EXTERN VARIABLES -------------------------------*/

/*- LOCAL FUNCTIONS IMPLEMENTATION ------------------------*/

/*- APIs IMPLEMENTATION -----------------------------------*/
/**
* @brief: SOS Initialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_Init(void)
{
  sint8 i8_retVal = SOS_BASE_ERROR + SUCCESS;

  /* Initialize SOS_TCB array with zeros */
  uint8 u8_i;
  for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
  {
	  gstrSOS_TCB_s[u8_i].ptrSOS_Task = NULL;
	  gstrSOS_TCB_s[u8_i].u16_SOSTask_Periodicity = 0;
	  gstrSOS_TCB_s[u8_i].u8_SOSTask_Priority = 0;
	  gstrSOS_TCB_s[u8_i].u8_SOSTask_State = 0;
  }

  /* Create instance of Timer configuration structure and initialize it with zeros*/
  Timer_cfg_s str_Timer_Cfg_s = {0};

  /* Configure corresponding timer */
  #if defined TMU_TIMER_CH0
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH0;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  #elif defined TMU_TIMER_CH1
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH1;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64; /* Needs to be changed */
  #elif defined TMU_TIMER_CH2
    str_Timer_Cfg_s.Timer_CH_NO = TIMER_CH2;
    str_Timer_Cfg_s.Timer_Prescaler = TIMER_PRESCALER_64;
  #endif
  str_Timer_Cfg_s.Timer_Mode = TIMER_MODE;
  str_Timer_Cfg_s.Timer_Polling_Or_Interrupt = TIMER_INTERRUPT_MODE;
  str_Timer_Cfg_s.CBK_Ptr = SOS_System_TimerOvf_CBK;

  /* Initialize timer */
  Timer_Init(&str_Timer_Cfg_s);

  return i8_retVal;
}

/**
* @brief: TMU DeInitialization
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 TMU_DeInit(void)
{
    /* Remember to make a Timer_DeInit function */
    sint8 i8_retVal = SOS_BASE_ERROR + SUCCESS;

    /* Fill SOS_TCB array with zeros */
    uint8 u8_i;
    for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
    {
    	gstrSOS_TCB_s[u8_i].ptrSOS_Task = NULL;
		gstrSOS_TCB_s[u8_i].u16_SOSTask_Periodicity = 0;
		gstrSOS_TCB_s[u8_i].u8_SOSTask_Priority = 0;
		gstrSOS_TCB_s[u8_i].u8_SOSTask_State = 0;
    }

    /* TODO: */
    /* DeInit used timer */
    #if defined TMU_TIMER_CH0
      /* DeInit Timer0 */
    #elif defined TMU_TIMER_CH1
      /* DeInit Timer1 */
    #elif defined TMU_TIMER_CH2
      /* DeInit Timer2 */
    #endif

    return i8_retVal;
}

/**
* @brief: Appends Task block elements to the TCB array
* @param: ptrFun_User_CBK: pointer to callback function,
* 	  u16_Delay: requested delay,
* 	  u8_Periodicity: periodic or one shot
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_CreateTask(strSOS_TCB_t* gstrSOS_TaskCB_s)
{
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;

	if(NULL == gstrSOS_TaskCB_s)
	{
	    /* Error NULL pointer */
	    i8_retVal = SOS_BASE_ERROR + ERROR_NULL_POINTER;
	}
	else
	{
	    /* Assign TCB struct members */
		gstrSOS_TCB_s[gu8_ArrayElementCount].ptrSOS_Task = gstrSOS_TaskCB_s->ptrSOS_Task;
		gstrSOS_TCB_s[gu8_ArrayElementCount].u16_SOSTask_Periodicity = gstrSOS_TaskCB_s->u16_SOSTask_Periodicity;
		gstrSOS_TCB_s[gu8_ArrayElementCount].u8_SOSTask_Priority = gstrSOS_TaskCB_s->u8_SOSTask_Priority;
		gstrSOS_TCB_s[gu8_ArrayElementCount].u8_SOSTask_State = gstrSOS_TaskCB_s->u8_SOSTask_State;
		gstrSOS_TCB_s[gu8_ArrayElementCount].u16_SystemTick_Counter = 0;


	    /* Check if this is the first element in the array to start the timer */
	    if(gu8_ArrayElementCount == 0)
	    {
			/* Start and pre-load timer with 6 counts to get exactly 1 mS at every overflow */
			#if defined TMU_TIMER_CH0
			Timer_Start(TIMER_CH0, 6);
			#elif defined TMU_TIMER_CH1
			Timer_Start(TIMER_CH1, 65286);
			#elif defined TMU_TIMER_CH2
			Timer_Start(TIMER_CH2, 6);
			#endif
	    }
	    else
	    {
	    	/* Arrange array based on priority */
	    	strSOS_TCB_t u8_TaskTempCB = {0};
	    	uint8 u8_i, u8_j;

	    	/* Bubble sort the array based on priority */
			for(u8_i=0;u8_i<gu8_ArrayElementCount;u8_i++){
				for(u8_j=0;u8_j<gu8_ArrayElementCount-1;u8_j++){
					if(gstrSOS_TCB_s[u8_j].u8_SOSTask_Priority > gstrSOS_TCB_s[u8_j+1].u8_SOSTask_Priority){
						u8_TaskTempCB = gstrSOS_TCB_s[u8_j+1];
						gstrSOS_TCB_s[u8_j+1] = gstrSOS_TCB_s[u8_j];
						gstrSOS_TCB_s[u8_j] = u8_TaskTempCB;
					}
				}
			}
	    }

	    /* Increment Array index */
	    gu8_ArrayElementCount++;
	}

    return i8_retVal;
}

/**
* @brief: TMU Stop
* @param: ptrFun_User_CBK: pointer to callback function
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_DeleteTask(gptrSOSTask_t ptrFun_User_CBK)
{
    sint8 i8_retVal = SOS_BASE_ERROR + SUCCESS;

	uint8 u8_i, u8_TaskIndex;

	/* Check if TCB struct array is empty */
	if(gu8_ArrayElementCount == 0)
	{
		/* Error struct array is empty */
		i8_retVal = SOS_BASE_ERROR + ERROR_ARRAY_EMPTY;
	}
	else
	{
		if(NULL == ptrFun_User_CBK)
		{
			i8_retVal = SOS_BASE_ERROR + ERROR_NULL_POINTER;
		}
		else
		{
			/* Loop through TCB struct array to find task to be removed */
			for(u8_i=0;u8_i<MAX_TASK_COUNT;u8_i++)
			{

				if(gstrSOS_TCB_s[u8_i].ptrSOS_Task == ptrFun_User_CBK)
				{
					/* Handle special cases */
					/* Check if one element only is present in the array or if the array is full */
					if((gu8_ArrayElementCount == 1) || (gu8_ArrayElementCount == MAX_TASK_COUNT))
					{
						/* Restore default values */
						gstrSOS_TCB_s[gu8_ArrayElementCount-1].ptrSOS_Task = NULL;
						gstrSOS_TCB_s[gu8_ArrayElementCount-1].u16_SOSTask_Periodicity = 0;
						gstrSOS_TCB_s[gu8_ArrayElementCount-1].u8_SOSTask_Priority = 0;
						gstrSOS_TCB_s[gu8_ArrayElementCount-1].u8_SOSTask_State = WAITING_STATE;
						gstrSOS_TCB_s[gu8_ArrayElementCount-1].u16_SystemTick_Counter = 0;

						/* Decrement array index */
						gu8_ArrayElementCount--;
					  }
					  /* General case */
					  else
					  {
						  /* Get index of the Task to be removed */
						  u8_TaskIndex = u8_i;

						  /* Shift TCBs up by one starting from the TCB next to the one to be removed */
						  uint8 u8_temp;
						  for(u8_temp=(u8_TaskIndex+1);u8_temp<gu8_ArrayElementCount-1;u8_temp++)
						  {
							  gstrSOS_TCB_s[u8_temp].ptrSOS_Task = gstrSOS_TCB_s[u8_temp+1].ptrSOS_Task;
							  gstrSOS_TCB_s[u8_temp].u16_SOSTask_Periodicity = gstrSOS_TCB_s[u8_temp+1].u16_SOSTask_Periodicity;
							  gstrSOS_TCB_s[u8_temp].u8_SOSTask_Priority = gstrSOS_TCB_s[u8_temp+1].u8_SOSTask_Priority;
							  gstrSOS_TCB_s[u8_temp].u8_SOSTask_State = gstrSOS_TCB_s[u8_temp+1].u8_SOSTask_State;
							  gstrSOS_TCB_s[u8_temp].u16_SystemTick_Counter = gstrSOS_TCB_s[u8_temp+1].u16_SystemTick_Counter;
						  }

						  /* Decrement array index */
						  gu8_ArrayElementCount--;
					  }
				}
				else
				{
					/* Do nothing */
				}
			}
		}
	}

	/* Check if array is empty to stop the timer */
	if(gu8_ArrayElementCount == 0)
	{
		/* Stop timer */
		#if defined TMU_TIMER_CH0
		Timer_Stop(TIMER_CH0);
		#elif defined TMU_TIMER_CH1
		Timer_Stop(TIMER_CH1); /* Needs to be changed */
		#elif defined TMU_TIMER_CH2
		Timer_Stop(TIMER_CH2);
		#endif
	}
	else
	{
		/* Do nothing */
	}
    return i8_retVal;
}

/**
* @brief: TMU Loops through task list and service each one as requested
* @param: void
* Input : void
* Output: None
* @return: sint8 status code with error code if one occurred
*/
sint8 SOS_Run(void)
{
    sint8 i8_retVal = TMU_BASE_ERROR + SUCCESS;
    if(gu8_SOS_SYSTEM_TimerOvf_Flag == SYSTEM_TICK_TRIGGERED)
    {
	uint8 u8_i;
	/* Loop through Tasks in the array and increment System_Tick counter */
	for(u8_i=0;u8_i<gu8_ArrayElementCount;u8_i++)
	{
	    if(NULL == gstrSOS_TCB_s[u8_i].ptrSOS_Task)
	    {
	    	/* Last task in the list is reached */
	    	/* Break the loop */
	    	break;
	    }
	    else
	    {
			/* Increment System_Tick counter */
	    	gstrSOS_TCB_s[u8_i].u16_SystemTick_Counter++;

	    	/* Check periodicity */
	    	if(gstrSOS_TCB_s[u8_i].u16_SystemTick_Counter >= gstrSOS_TCB_s[u8_i].u16_SOSTask_Periodicity)
	    	{
	    		/* Change task state to READY_STATE */
	    		gstrSOS_TCB_s[u8_i].u8_SOSTask_State = READY_STATE;
	    	}
	    	else
	    	{
	    		/* Do nothing */
	    	}
	    }
	}

	/* Loop through TCB array and handle each one */
	for(u8_i=0;u8_i<gu8_ArrayElementCount;u8_i++)
	{
	    if(NULL == gstrSOS_TCB_s[u8_i].ptrSOS_Task)
	    {
	    	/* Last task in the list is reached */
			/* Break the loop */
			break;
	    }
	    else
	    {
			/* Check if Task is ready */
			if(gstrSOS_TCB_s[u8_i].u8_SOSTask_State == READY_STATE)
			{
				/* Zero System_Tick counter */
				gstrSOS_TCB_s[u8_i].u16_SystemTick_Counter = 0;

				/* Execute corresponding callback function */
				gstrSOS_TCB_s[u8_i].ptrSOS_Task();

				/* Change task state to be waiting */
				gstrSOS_TCB_s[u8_i].u8_SOSTask_State = WAITING_STATE;

				/* break the loop */
				break;
			}
			else
			{
				/* Do nothing */
			}
	    }
	}
	/* Reset flag */
	gu8_SOS_SYSTEM_TimerOvf_Flag = SYSTEM_TICK_NOT_TRIGGERED;
    }
    else
    {
    	/* Do nothing */
    }
    return i8_retVal;
}

/**
* @brief: Timer callback function
* @param: void
* Input : void
* Output: None
* @return: void
*/
static void SOS_System_TimerOvf_CBK(void)
{
  /* Increment overflow counter */
  gu8_OvfCounter++;
  if(gu8_OvfCounter == SOS_SYSTEM_TICK_RESOLUTION)
  {
      /* Indicate timer overflow has occurred */
      gu8_SOS_SYSTEM_TimerOvf_Flag = SYSTEM_TICK_TRIGGERED;

      /* Reset overflow counter */
      gu8_OvfCounter = 0;
  }
  else
  {
      /* Do nothing */
  }
  /* Start and pre-load timer to get exactly 1 mS at every overflow */
#if defined TMU_TIMER_CH0
  Timer_Start(TIMER_CH0, 6);
#elif defined TMU_TIMER_CH1
  Timer_Start(TIMER_CH1, 65286);
#elif defined TMU_TIMER_CH2
  Timer_Start(TIMER_CH2, 6);
#endif
}

